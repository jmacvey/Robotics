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
#include <Math.h> // powe function
#include <SoftwareSerial.h>
#include "Timer.h" 
#include "NewPing.h"

enum Direction { LEFT , RIGHT, STRAIGHT, REVERSE };

class WallFollower {

public:
	WallFollower();

	~WallFollower();

	WallFollower(MotorMaster* motorMaster, SoftwareSerial* BT);

	WallFollower& operator=(WallFollower& rhs);

	bool start();

	bool stop();

	void tunePD(float kp, float kd, float ki);

	void look(uint8_t degrees);

	unsigned long getDistance();

	void navigateToWall();

	void setDuration(int duration) { this->duration = duration; }

	unsigned long getCurrentDistance();

	int duration = 0;

private:

	void config();

	void lookLeft();

	void lookRight();

	void lookStraight();

	void bluetoothCallback();

	void checkCollisionMakeChange(signed long errorDiff);
	

	unsigned long calculateShortDistance();

	Servo servo;
	MotorMaster* motorMaster;
	SoftwareSerial* BT;

	float kp = 1.0; // proportional tuning parameter
	float kd = 1.0; // differential tuning parameter
	float ki = 1.0; // integral tuning parameter
	int dt = 125; // 125ms time differential
	Direction currentDirection = STRAIGHT;
	const static int SPEED_OF_SOUND = 340; // 3.4 cm / s
	const static int refSpeed = 160;
	const static int maxAdj = MOTOR_SPEED - refSpeed;
	unsigned long currentDistance = 0;
	bool callbackTrigger = false;
	NewPing* sonar;

	const int maxSideDistance = 25; // cm
	const int optimalSideDistance = 35;
	const int optimalFrontDistance = 40; // cm

}; // end class declaration


#endif