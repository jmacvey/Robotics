//--------------------------------------------------------------
// Arduino Source - MotorMaster.cpp
// @Author - J. MacVey
//--------------------------------------------------------------

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

#include "MotorMaster.h" 

//---------------------------------------------------------------------
// Public Methods

MotorMaster::MotorMaster() :lcdManager(NULL) {
	//	set the mode pins to output
	//	motor connections
	initializePorts();
}

MotorMaster::MotorMaster(LCDManager* lcdManager) : lcdManager(NULL), motorRight1(MOTOR_ONE_FWD),
motorRight2(MOTOR_ONE_REV), motorLeft1(MOTOR_TWO_FWD), motorLeft2(MOTOR_TWO_REV),
motorRightPWM(MOTOR_ONE_PWM),
motorLeftPWM(MOTOR_TWO_PWM) {
	// set the mode pins to output
	//motor connections
	//Serial.begin(BAUD_RATE);
	initializePorts();
}

MotorMaster::MotorMaster(int motorRight1, int motorRight2, int motorLeft1,
	int motorLeft2, int motorRightPWM, int motorLeftPWM) : lcdManager(NULL), motorRight1(motorRight1),
	motorRight2(motorRight2), motorLeft1(motorLeft1), motorLeft2(motorLeft2),
	motorRightPWM(motorRightPWM),
	motorLeftPWM(motorLeftPWM)
{
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
	//Serial.begin(BAUD_RATE);
	initializePorts();
}

void MotorMaster::advance(int d) { //go straight
	digitalWrite(motorRight1, LOW);
	digitalWrite(motorRight2, HIGH);
	digitalWrite(motorLeft1, LOW);
	digitalWrite(motorLeft2, HIGH);
	analogWrite(motorRightPWM, iSpeed);
	analogWrite(motorLeftPWM, iSpeed);
	delay(d * 10);
	tryToPrint("Advancing");
}

void MotorMaster::slightL(int d) {
	digitalWrite(motorRight1, LOW);
	digitalWrite(motorRight2, HIGH);
	digitalWrite(motorLeft1, LOW);
	digitalWrite(motorLeft2, HIGH);
	analogWrite(motorRightPWM, iSpeed);
	analogWrite(motorLeftPWM, 100);
	delay(d * 10);
	tryToPrint("Turning slightly left");
}

void MotorMaster::slightR(int d) {
	digitalWrite(motorRight1, LOW);
	digitalWrite(motorRight2, HIGH);
	digitalWrite(motorLeft1, LOW);
	digitalWrite(motorLeft2, HIGH);
	analogWrite(motorRightPWM, 100);
	analogWrite(motorLeftPWM, iSpeed);
	delay(d * 10);
	tryToPrint("Turning slightly right");
}

void MotorMaster::left(int d) { //turn right (single wheel)
	digitalWrite(motorLeft1, LOW);
	digitalWrite(motorLeft2, HIGH);
	digitalWrite(motorRight1, LOW);
	digitalWrite(motorRight2, LOW);
	analogWrite(motorRightPWM, iSpeed);
	analogWrite(motorLeftPWM, iSpeed);
	delay(d * 10);
	tryToPrint("Turning left with one wheel.");
}

void MotorMaster::right(int d) {//turn left(single wheel)
	digitalWrite(motorRight1, LOW);
	digitalWrite(motorRight2, HIGH);
	digitalWrite(motorLeft1, LOW);
	digitalWrite(motorLeft2, LOW);
	analogWrite(motorRightPWM, iSpeed);
	analogWrite(motorLeftPWM, iSpeed);
	delay(d * 10);
	tryToPrint("Turning right with one wheel.");
}

void MotorMaster::turnR(int d) {//turn right (two wheels)
	digitalWrite(motorRight1, HIGH);
	digitalWrite(motorRight2, LOW);
	digitalWrite(motorLeft1, LOW);
	digitalWrite(motorLeft2, HIGH);
	analogWrite(motorRightPWM, 255);
	analogWrite(motorLeftPWM, 255);
	delay(d * 10);
	tryToPrint("Turning right with two wheels");
}

void MotorMaster::turnL(int d) {//turn left (two wheels)
	digitalWrite(motorRight1, LOW);
	digitalWrite(motorRight2, HIGH);
	digitalWrite(motorLeft1, HIGH);
	digitalWrite(motorLeft2, LOW);
	analogWrite(motorRightPWM, iSpeed);
	analogWrite(motorLeftPWM, iSpeed);
	delay(d * 10);
	tryToPrint("Turning left!");
}

void MotorMaster::stopp(int d) { //stop
	digitalWrite(motorRight1, LOW);
	digitalWrite(motorRight2, LOW);
	digitalWrite(motorLeft1, LOW);
	digitalWrite(motorLeft2, LOW);
	analogWrite(motorRightPWM, iSpeed);
	analogWrite(motorLeftPWM, iSpeed);
	delay(d * 10);
	tryToPrint("Stopped");
}

void MotorMaster::back(int d) { //go back
	digitalWrite(motorRight1, HIGH);
	digitalWrite(motorRight2, LOW);
	digitalWrite(motorLeft1, HIGH);
	digitalWrite(motorLeft2, LOW);
	analogWrite(motorRightPWM, iSpeed);
	analogWrite(motorLeftPWM, iSpeed);
	delay(d * 10);
	tryToPrint("Reversing");
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


void MotorMaster::tryToPrint(const String& lcdOutput) {
	if (lcdManager != NULL)
	{
		lcdManager->printStringToLCD(lcdOutput);
	}
}