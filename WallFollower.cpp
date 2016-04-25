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

WallFollower::WallFollower(MotorMaster& motorMaster) :
	motorMaster(motorMaster) {
	config();
}

bool WallFollower::start() {
	// STUB
}

bool WallFollower::stop()
{
	// STUB
}

void WallFollower::tunePD(float kp, float kd)
{
	this->kp = kp;
	this->kd = kd;
}

void WallFollower::look(uint8_t degrees)
{
	servo.write(degrees);
}

//---------------------------------------------------------------------
// Public Member

void WallFollower::lookLeft() {
	servo.write(SERVO_LEFT_DEGREES);
}

void WallFollower::lookRight() {
	uint8_t rightDegrees = 180;
	servo.write(SERVO_RIGHT_DEGREES);
}

void WallFollower::lookStraight() {
	servo.write(SERVO_FWD_DEGREES);
}

void WallFollower::config() {
	servo.attach(SERVO_ATTACH_PIN);
	pinMode(ULTRA_SONIC_ECHO, INPUT);
	pinMode(ULTRA_SONIC_TRIGGER, OUTPUT);
}