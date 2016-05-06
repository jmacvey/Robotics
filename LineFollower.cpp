//--------------------------------------------------------------
// Arduino Source - LineFollower.cpp
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

//--------------------------------------------------------------
// Includes 

#include "LineFollower.h" 

//--------------------------------------------------------------
// Public Members

LineFollower::LineFollower() {
	// do nothing
}

LineFollower& LineFollower::operator=(LineFollower& rhs) {
	return *this;
}

LineFollower::LineFollower(MotorMaster& motorMaster) : 
	motorMaster(motorMaster) {}

bool LineFollower::start() {
	// STUB
}
bool LineFollower::stop() {
	// STUB
}