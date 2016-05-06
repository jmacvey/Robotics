//---------------------------------------------------------------------
// Arduino Source - WallFollower.cpp
// @Author - J. MacVey
//---------------------------------------------------------------------

/* This file is part of the Robotics library developed for S. Norr's
Robotics course at University of Minnesota-Duluth

The Robotics Library is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

The Robotics Library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with the Robotics Library.If not, see <http://www.gnu.org/licenses/>. */

//---------------------------------------------------------------------
// Includes

#include "WallFollower.h" 

//---------------------------------------------------------------------
// Public Members

WallFollower::WallFollower() {
	// do nothing
}

WallFollower::WallFollower(MotorMaster* motorMaster, SoftwareSerial* BT) :
	motorMaster(motorMaster), BT(BT) {
	config();
	sonar = new NewPing(ULTRA_SONIC_TRIGGER, ULTRA_SONIC_ECHO);
}

WallFollower::~WallFollower() {
	delete sonar;
}

WallFollower& WallFollower::operator=(WallFollower& rhs)
{
	this->motorMaster = rhs.motorMaster;
	return *this;
}

bool WallFollower::start() {
	signed long errorNew = 0, errorOld = 0, errorDiff = 0, speed = 0;
	signed long errorInt = 0;
	int minThreshold = maxSideDistance, maxThreshold = maxSideDistance;
	int errorCount = 0;
	lookRight();
	errorNew = errorOld = 0;
	bool initial = false;
	int count = 0;
	int reset = 5;
	while (!callbackTrigger) // the trigger gets set to true is BT picks up a signal
	{
		// reset the integral gain every five cycles
		if (count == reset) {
			count = 0;
			errorInt = 0;
		}
		else
			count++;
		currentDistance = getDistance();
		errorNew = (optimalSideDistance - currentDistance); // get new error
		errorDiff = errorNew - errorOld;
		errorInt += errorNew;
		// kp = 2.2, kd = 1.2
		int adjSpeed = kp*errorNew > maxAdj ? maxAdj : 
			kp*errorNew < -maxAdj ? -maxAdj : 
			kp*errorNew;
		int adjSpeedKd = initial ? 0 : kd*errorDiff;
		if (initial)
			initial = false;
		int speedR = (refSpeed + adjSpeed + adjSpeedKd 
			+ ki*errorInt);
		int speedL = (refSpeed - adjSpeed - adjSpeedKd 
			- ki*errorInt); 
		speedL = speedL > 255 ? 255 : speedL;
		speedR = speedR > 255 ? 255 : speedR;
		motorMaster->advance(speedL, speedR, false, false);
		// turn right if necessary
		errorOld = errorNew;
		bluetoothCallback();
		delay(dt);
	}
	// reset call back when breaking out of loop
	callbackTrigger = false;
}

bool WallFollower::stop()
{
	motorMaster->stopp(100);
}

void WallFollower::bluetoothCallback() {
	//currentDistance = getDistance();
	//checkCollisionMakeChange(abs(errorDiff));
	if (BT->available()) {
		if (BT->readString().equals("STOP"))
		motorMaster->stopp(0);
		callbackTrigger = true;
	}
}
unsigned long WallFollower::getCurrentDistance()
{
	return this->currentDistance;
}

void WallFollower::tunePD(float kp, float kd, float ki)
{
	this->kp = kp;
	this->kd = kd;
	this->ki = ki;
}

void WallFollower::look(uint8_t degrees)
{
	servo.write(degrees);
}

//---------------------------------------------------------------------
// Private Members

void WallFollower::lookLeft() {
	servo.write(SERVO_LEFT_DEGREES);
}

void WallFollower::lookRight() {
	servo.write(SERVO_RIGHT_DEGREES);
}

void WallFollower::lookStraight() {
	servo.write(SERVO_FWD_DEGREES);
}

void WallFollower::checkCollisionMakeChange(signed long errorDiff) {
	int farOffDistance = 1000;
	lookStraight();
	delay(50);
	int distanceFromFront = getDistance();
	int minDistance = optimalFrontDistance;
	if (distanceFromFront < minDistance)
	{
		// immediate left maneuver
		motorMaster->stopp(0);
		lookRight();
		BT->println("Turning hard left");
		motorMaster->adjustSpeed(255);
		motorMaster->left(0);
		while (getDistance() < 500);
			motorMaster->stopp(0);
	}
}

void WallFollower::navigateToWall() {
	currentDistance = calculateShortDistance();
	BT->print("Shortest distance: ");
	BT->println(currentDistance);
	motorMaster->adjustSpeed(255);
	String direction = currentDirection == STRAIGHT ? "STRAIGHT" :
		currentDirection == LEFT ? "LEFT" : "RIGHT";
	unsigned long distance = 0;
	int threshold = 10;
	switch (currentDirection)
	{
	case STRAIGHT:
		break;
	case LEFT:
		BT->print("Turning left:");
		motorMaster->left(10);
		while (abs(distance - currentDistance) > threshold) {
			distance = getDistance();
		}
		break;
	case RIGHT:
		BT->println("Turning right:");
		motorMaster->right(0);
		while (abs(distance - currentDistance) > threshold) {
			distance = getDistance();
		}
		break;
	}
	BT->println("Advancing");
	motorMaster->adjustSpeed(200);
	motorMaster->advance(0);
	while (distance > optimalFrontDistance) {
		distance = getDistance();
		BT->println(distance);
		delay(100);
	}
	motorMaster->stopp(0); // stop that shit
	//BT->println("broken out of loop");
	lookRight();
	currentDistance = getDistance();
	BT->println("Turning left");
	motorMaster->left(0);
	while (getDistance() > optimalFrontDistance) {}
	BT->println("Stopping.");
	motorMaster->stopp(0);
}

unsigned long WallFollower::calculateShortDistance() {
	lookLeft();
	unsigned long distance = getDistance();
	currentDirection = LEFT;
	lookRight();
	unsigned long distancetmp = getDistance();
	currentDirection = distancetmp < distance ? RIGHT : currentDirection;
	distance = distancetmp < distance ? distancetmp : distance;
	lookStraight();
	distancetmp = getDistance();
	currentDirection = distancetmp < distance ? STRAIGHT : currentDirection;
	distance = distancetmp < distance ? distancetmp : distance;
	return distance;
}

unsigned long WallFollower::getDistance() {
	// ultrasonic echo low level in 2us
	unsigned long MAX_LIMIT = 120;
	unsigned long distance = sonar->ping_cm();
	//Serial.print("distance: "); // 
	//Serial.print(distance);
	//Serial.println(" mm"); //  output distance (cm)
	if (distance == 0)
		return MAX_LIMIT;
	else
		return distance; // avg
}

void WallFollower::config() {
	servo.attach(SERVO_ATTACH_PIN);
	pinMode(ULTRA_SONIC_ECHO, INPUT);
	pinMode(ULTRA_SONIC_TRIGGER, OUTPUT);
}