//---------------------------------------------------------------------
// Arduino Header - RobotMaster.cpp
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

#ifndef ROBOT_MASTER_H
#define ROBOT_MASTER_H

//---------------------------------------------------------------------
// Includes

#include "Arduino.h"
#include "WallFollower.h"
#include "LineFollower.h"
#include "MotorMaster.h"
#include "LCDManager.h"

/* 
	Error Codes:
	OK = 0 -- no error occured
	NO_MODE_ENABLED = 1 -- no mode is currently enabled for begin to work with
	INVALID_MODE_SPECIFIER = 2 -- an invalid mode was specified in setMode() method
*/

enum ErrorCode { OK, NO_MODE_ENABLED, INVALID_MODE_SPECIFIER };

//---------------------------------------------------------------------
// Config

#define BAUD_RATE     9600

/* Handles the robot in wall-following and line-following modes */
class RobotMaster {

public:
	/* Constructor */
	RobotMaster(int initialMode = NO_MODE_ENABLED, 
		byte i2cAddress = NO_ADDRESS_SUPPLIED);

	/* Sets the mode for the robot controller*/
	bool setMode(int mode);

	/* Gets the mode for the robot controller */
	int getMode();

	/* Gets the last error code */
	ErrorCode getErrorCode();
	
	/* Begins line following or wall following depending on the current mode or 
	   the user-specified parameter */
	bool begin(int mode = CURRENT_MODE);

	/* Stops whatever the robot is doing, if it's doing anything */
	bool stop();

	void listenSerial() {
		motorMaster.beginSerialInterface(100);
	}

private:

	// REGION: Utility methods

	bool initializeLineFollower();
	bool initializeWallFollower();
	bool beginMode();

	// REGION: Data Fields

	// Composition classes
	MotorMaster motorMaster;
	LineFollower* lineFollower;
	WallFollower* wallFollower;
	LCDManager* lcdManager;

	// the current mode 
	int mode;
	ErrorCode lastError = OK;
	// flag for checking if a current mode is in operation
	bool hasBegun;

	// modes
	const static int LINE_FOLLOWER_MODE = 0;
	const static int WALL_FOLLOWER_MODE = 1;

	// flags
	const static byte NO_ADDRESS_SUPPLIED = -1;
	const static int NO_MODE_ENABLED = -1;
	const static int CURRENT_MODE = 2;
};



#endif