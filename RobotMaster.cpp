//---------------------------------------------------------------------
// Arduino Source - RobotMaster.cpp
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

#include "RobotMaster.h" 

//---------------------------------------------------------------------
// Public Members

/* Constructor */
RobotMaster::RobotMaster(int initialMode,
	byte i2cAddress)
{
	Serial.begin(BAUD_RATE);
	Serial.println("Initialized Robot Master.");
	Serial.println("Starting LCD with no params..");

	Serial.print("Memory free before robotmaster constructor: ");
	Serial.println(freeMemory());

	if (lcdManager.getErrorCode() == LCDManager::OK) {
		Serial.println("Creating motorMaster with an LCDManager");
		//motorMaster = MotorMaster(lcdManager);
	}
	else {
		motorMaster = MotorMaster();
	}

	//WallFollower wallFollowerCopy(motorMaster);
	//LineFollower lineFollowerCopy(motorMaster);
	//lineFollower = lineFollowerCopy;
	//wallFollower = wallFollowerCopy;
	if (initialMode != NO_MODE_ENABLED)
	{
		if (setMode(initialMode))
		{
			beginMode();
		}
	}

	Serial.print("Memory free after robotmaster constructor: ");
	Serial.println(freeMemory());
}

/* Sets the mode for the robot controller*/
bool RobotMaster::setMode(int mode) {
	// validate input
	if (mode != LINE_FOLLOWER_MODE && mode != WALL_FOLLOWER_MODE) {
		lastError = INVALID_MODE_SPECIFIER;
		return false;
	}

	this->mode = mode;
	return true;
}

/* Gets the mode for the robot controller */
int RobotMaster::getMode()
{
	return mode;
}

/* Gets the last error code */
ErrorCode RobotMaster::getErrorCode()
{
	return lastError;
}

/* Begins line following or wall following depending on the current mode or
the user-specified parameter */
bool RobotMaster::begin(int mode)
{
	if (mode != CURRENT_MODE) {
		if (!setMode(mode))
		{
			return false; // bad mode specified
		}
	}
	else
		return hasBegun = beginMode();
}



/* Stops whatever the robot is doing, if it's doing anything */
bool RobotMaster::stop()
{
	if (!hasBegun) // called stop on a process that hasn't started
		return true;

	switch (mode)
	{
	case LINE_FOLLOWER_MODE:
		//hasBegun = !lineFollower.stop();
		break;
	case WALL_FOLLOWER_MODE:
		//hasBegun = !wallFollower.stop();
		break;
	default:
		break;
	}
	return !hasBegun;
}

// REGION : Private methods

//bool RobotMaster::initializeLineFollower()
//{
//	// STUB
//	lineFollower = LineFollower(motorMaster);
//}
//bool RobotMaster::initializeWallFollower() {
//	// STUB
//	wallFollower = WallFollower(motorMaster);
//}

bool RobotMaster::beginMode() {
	switch (mode)
	{
	case LINE_FOLLOWER_MODE:
		/*if (lineFollower == NULL)
			initializeLineFollower();*/
			//lineFollower.start();
		break;
	case WALL_FOLLOWER_MODE:
		//if (wallFollower == NULL)
		//	initializeWallFollower();
		//wallFollower.start();
	default:
		lastError = INVALID_MODE_SPECIFIER;
		break;
	}
}