//--------------------------------------------------------------
// Arduino Source - MotorMaster.cpp
// @Author - J. MacVey
//--------------------------------------------------------------

/* This file is part of the Robotics library developed for S. Norr's
Robotics course at University of Minnesota-Duluth

The Robotics Library is free software : Ryou can redistribute it and / or modify
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

#include "MotorMaster.h" 

//---------------------------------------------------------------------
// Public Methods

MotorMaster::MotorMaster() : motorRight1(MOTOR_ONE_FWD),
motorRight2(MOTOR_ONE_REV), motorLeft1(MOTOR_TWO_FWD), motorLeft2(MOTOR_TWO_REV),
motorRightPWM(MOTOR_ONE_PWM),
motorLeftPWM(MOTOR_TWO_PWM) {
	//	set the mode pins to output
	//	motor connections
	lcdManager = NULL;
	hasLCDManager = false;
	initializePorts();
}

MotorMaster::MotorMaster(LCDManager* lcdManager) : lcdManager(lcdManager), motorRight1(MOTOR_ONE_FWD),
motorRight2(MOTOR_ONE_REV), motorLeft1(MOTOR_TWO_FWD), motorLeft2(MOTOR_TWO_REV),
motorRightPWM(MOTOR_ONE_PWM),
motorLeftPWM(MOTOR_TWO_PWM) {
	motorRight1 = 7;
	motorRight2 = 8;
	motorLeft1 = 9;
	motorLeft2 = 10;
	motorRightPWM = 6;
	motorLeftPWM = 11;
	iSpeed = 255;
	// set the mode pins to output
	//motor connections
	//Serial.begin(BAUD_RATE);
	hasLCDManager = true;
	initializePorts();
}

MotorMaster::MotorMaster(int motorRight1, int motorRight2, int motorLeft1,
	int motorLeft2, int motorRightPWM, int motorLeftPWM) : motorRight1(motorRight1),
	motorRight2(motorRight2), motorLeft1(motorLeft1), motorLeft2(motorLeft2),
	motorRightPWM(motorRightPWM),
	motorLeftPWM(motorLeftPWM)
{
	hasLCDManager = false;
	lcdManager = NULL;
	iSpeed = 255;
	//Serial.begin(BAUD_RATE);
	initializePorts();
}

MotorMaster::MotorMaster(LCDManager* lcdManager, int motorRight1, int motorRight2, int motorLeft1,
	int motorLeft2, int motorRightPWM, int motorLeftPWM) : lcdManager(lcdManager),
	motorRight1(motorRight1),
	motorRight2(motorRight2), motorLeft1(motorLeft1), motorLeft2(motorLeft2),
	motorRightPWM(motorRightPWM),
	motorLeftPWM(motorLeftPWM)
{
	iSpeed = 255;
	//Serial.begin(BAUD_RATE);
	hasLCDManager = true;
	initializePorts();
}

void MotorMaster::advance(int d) { //go straight
	digitalWrite(motorRight1, LOW);
	digitalWrite(motorRight2, HIGH);
	digitalWrite(motorLeft1, LOW);
	digitalWrite(motorLeft2, HIGH);
	analogWrite(motorRightPWM, iSpeed);
	analogWrite(motorLeftPWM, iSpeed - 20);
	delay(d * 10);
}

void MotorMaster::slightL(int d) { // turn right wheel fast compared to left
	digitalWrite(motorRight1, LOW);
	digitalWrite(motorRight2, HIGH);
	digitalWrite(motorLeft1, LOW);
	digitalWrite(motorLeft2, HIGH);
	analogWrite(motorRightPWM, iSpeed);
	analogWrite(motorLeftPWM, 80);
	//tryToPrint("Turning slightly left");
	delay(d * 10);
}

void MotorMaster::advance(int speedL, int speedR, bool reverseL, bool reverseR) {
	if (!advancing) {
		digitalWrite(motorRight1, LOW);
		digitalWrite(motorRight2, HIGH);
		digitalWrite(motorLeft1, LOW);
		digitalWrite(motorLeft2, HIGH);
		advancing = true;
	}
	if (reverseR)
	{
		analogWrite(motorRight1, HIGH);
		analogWrite(motorRight2, LOW);
		advancing = false;
	}
	if (reverseL)
	{
		analogWrite(motorLeft1, HIGH);
		analogWrite(motorLeft2, LOW);
		advancing = false;
	}
	analogWrite(motorRightPWM, speedR);
	analogWrite(motorLeftPWM, speedL);
}

void MotorMaster::slightR(int d) { // turn left wheel fast compared to right
	digitalWrite(motorRight1, LOW);
	digitalWrite(motorRight2, HIGH);
	digitalWrite(motorLeft1, LOW);
	digitalWrite(motorLeft2, HIGH);
	analogWrite(motorRightPWM, 100);
	analogWrite(motorLeftPWM, iSpeed);
	delay(d * 10);
}

void MotorMaster::right(int d) { //turn left wheel
	digitalWrite(motorLeft1, LOW);
	digitalWrite(motorLeft2, HIGH);
	digitalWrite(motorRight1, LOW);
	digitalWrite(motorRight2, LOW);
	analogWrite(motorRightPWM, iSpeed);
	analogWrite(motorLeftPWM, iSpeed);
	//tryToPrint("Turning left (1).");
	delay(d * 10);
}

void MotorMaster::left(int d) {//turn right(single wheel)
	digitalWrite(motorRight1, LOW);
	digitalWrite(motorRight2, HIGH);
	digitalWrite(motorLeft1, LOW);
	digitalWrite(motorLeft2, LOW);
	analogWrite(motorRightPWM, iSpeed);
	analogWrite(motorLeftPWM, iSpeed);
	//tryToPrint("Turning right (1).");
	delay(d * 10);
}

void MotorMaster::turnR(int d) {//turn right (two wheels)
	digitalWrite(motorRight1, HIGH);
	digitalWrite(motorRight2, LOW);
	digitalWrite(motorLeft1, LOW);
	digitalWrite(motorLeft2, HIGH);
	analogWrite(motorRightPWM, iSpeed);
	analogWrite(motorLeftPWM, iSpeed);
	//tryToPrint("Turning right (2)");
	advancing = false;
	delay(d * 10);
}

void MotorMaster::turnL(int d) {//turn left (two wheels)
	digitalWrite(motorRight1, LOW);
	digitalWrite(motorRight2, HIGH);
	digitalWrite(motorLeft1, HIGH);
	digitalWrite(motorLeft2, LOW);
	analogWrite(motorRightPWM, iSpeed);
	analogWrite(motorLeftPWM, iSpeed);
	//tryToPrint("Turning left!");
	delay(d * 10);
}

void MotorMaster::stopp(int d) { //stop
	digitalWrite(motorRight1, LOW);
	digitalWrite(motorRight2, LOW);
	digitalWrite(motorLeft1, LOW);
	digitalWrite(motorLeft2, LOW);
	analogWrite(motorRightPWM, iSpeed);
	analogWrite(motorLeftPWM, iSpeed);
	delay(d * 10);
	//tryToPrint("Stopped");
}

void MotorMaster::back(int d) { //go back
	digitalWrite(motorRight1, HIGH);
	digitalWrite(motorRight2, LOW);
	digitalWrite(motorLeft1, HIGH);
	digitalWrite(motorLeft2, LOW);
	analogWrite(motorRightPWM, iSpeed);
	analogWrite(motorLeftPWM, iSpeed);
	delay(d * 10);
	//tryToPrint("Reversing");
}

void MotorMaster::initializePorts() {
	pinMode(motorRight1, OUTPUT);  //
	pinMode(motorRight2, OUTPUT);  //
	pinMode(motorLeft1, OUTPUT);  //
	pinMode(motorLeft2, OUTPUT);  //
	pinMode(motorRightPWM, OUTPUT); //enable for right side motor
	pinMode(motorLeftPWM, OUTPUT); //enable for right side motor
}

void MotorMaster::beginSerialInterface(int idelay) {
	if (Serial.available() > 0) {
		int inByte = Serial.read();
		int speed; // Local variable
		int delay = 100;

		switch (inByte) {
		case '1':
			advance(delay);
			break;
		case '2':
			back(delay);
			break;
		case '3':
			turnR(delay);
			break;
		case '4':
			turnL(delay);
			break;
		case '5':
			slightL(delay);
			break;
		case '6':
			slightR(delay);
			break;
		case '7':
			stopp(delay);
			break;
		default:
			break;
		} // end switch
	} // end if
	delay(idelay);
}

void MotorMaster::adjustSpeed(int speed) { iSpeed = speed; }

//void MotorMaster::tryToPrint(const String& lcdOutput) {
//	if (hasLCDManager)
//	{
//		lcdManager->printStringToLCD(lcdOutput);
//	}
//}