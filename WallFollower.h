//---------------------------------------------------------------------
// Arduino Header - WallFollower.h
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
along with Foobar.If not, see <http://www.gnu.org/licenses/>. */

#ifndef LINE_FOLLOWER_H
#define LINE_FOLLOWER_H

//---------------------------------------------------------------------
// Includes

#include "MotorMaster.h"
#include "Servo.h"
#include "Config.h"

enum Direction { NORTH = 0, SOUTH, EAST, WEST };

class WallFollower {

public:

	WallFollower(MotorMaster& motorMaster);

	bool start();

	bool stop();

	void tunePD(float kp, float kd);

	void look(uint8_t degrees);

private:

	void config();

	void lookLeft();

	void lookRight();

	void lookStraight();

	Servo servo;

	MotorMaster motorMaster;

	float kp; // proportional tuning parameter
	float kd; // differential tuning parameter
	Direction currentDirection;
}; // end class declaration


#endif