//--------------------------------------------------------------
// Arduino Source - MotorMaster.h
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

#ifndef MOTOR_MASTER_H
#define MOTOR_MASTER_H

//---------------------------------------------------------------------
// Includes

#include "Arduino.h"
#include "LCDManager.h"
#include "Config.h"

class MotorMaster {

public:
	MotorMaster();
	// default pins
	MotorMaster(LCDManager* lcdManager);
	// allows for pin configuration
	MotorMaster(int motorRight1, int motorRight2, int motorLeft1,
		int motorLeft2, int motorRightPWM, int motorLeftPWM);

	MotorMaster(LCDManager* lcdManager, int motorRight1, int motorRight2, int motorLeft1,
		int motorLeft2, int motorRightPWM, int motorLeftPWM);

	void advance(int d);

	void slightL(int d);

	void slightR(int d);

	void left(int d);

	void right(int d);

	void turnR(int d);

	void turnL(int d);

	void stopp(int d);

	void back(int d);

	void beginSerialInterface(int idelay);

private:

	void initializePorts();

	void serialTest();

	void tryToPrint(const String& lcdOutput);
	// Motor Pin set up
	int motorRight1;
	int motorRight2;
	int motorLeft1;
	int motorLeft2;
	int motorRightPWM;
	int motorLeftPWM;
	int iSpeed;

	LCDManager* lcdManager;
};


#endif