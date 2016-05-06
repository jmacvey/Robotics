//---------------------------------------------------------------------
// Robotics Configuration File - RoboticsConfig.h
// @Author - J. MacVey
//---------------------------------------------------------------------

/* This file is part of the Robotics library developed for S. Norr's
Robotics course at University of Minnesota-Duluth

The Robotics Library is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

The Robotics Library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with the Robotics Library. If not, see <http://www.gnu.org/licenses/>. */

// @brief this file represents the configuration file for the robotics library
// Users should configure the pins according to their device layout

#ifndef ROBOTICS_CONFIG_H
#define ROBOTICS_CONFIG_H

//-----------------------------------------------------------------
// Serial configuration

#define BAUD_RATE			9600

//-----------------------------------------------------------------
// I2C Pins 

#define Rs_pin			0
#define Rw_pin			1
#define En_pin			2
#define BACKLIGHT_PIN	3 
#define D4_pin			4
#define D5_pin			5
#define D6_pin			6
#define D7_pin			7


//-----------------------------------------------------------------
// LCD-specific flags

#define LED_FRAME_DELAY			3000 
#define LED_OFF					0
#define LED_ON					1
#define LED_CHARS_PER_LINE		16
#define LED_NUM_LINES			2

//-----------------------------------------------------------------
// Motor Pins and flags

#define MOTOR_ONE_FWD		7	// forwad
#define MOTOR_ONE_REV		8	// reverse 
#define MOTOR_TWO_FWD		9	// forward 
#define MOTOR_TWO_REV		10	// reverse 
#define MOTOR_ONE_PWM		6	
#define MOTOR_TWO_PWM		11	
#define MOTOR_SPEED			255
#define LEFT_MOTOR_SPEED	240
#define RIGHT_MOTOR_SPEED	255

//-----------------------------------------------------------------
// Servo pins and flags

#define SERVO_ATTACH_PIN	12
#define SERVO_FWD_DEGREES	110
#define SERVO_RIGHT_DEGREES 35
#define SERVO_LEFT_DEGREES	180

//-----------------------------------------------------------------
// Ultrasonic Sensor pins and flags

#define ULTRA_SONIC_ECHO	A1
#define ULTRA_SONIC_TRIGGER	A0

//-----------------------------------------------------------------
// Bluetooth Sensor pins and flags

#define BLUETOOTH_RX		1
#define BLUETOOTH_TX		0
#define BLUETOOTH_DELAY		3000 // check bluetooth every 3 seconds

//-----------------------------------------------------------------
// Speed flags

#define LEFT_TURN_DURATION			75
#define RIGHT_TURN_DURATION			75


#endif // ROBOTICS_CONFIG_H