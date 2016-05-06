//---------------------------------------------------------------------
// Arduino Header - LCDManager.h
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

#ifndef LCD_MANAGER_H
#define LCD_MANAGER_H

//-----------------------------------------------------------------
// Includes

#include "LiquidCrystal_I2C.h"
#include "Wire.h"
#include "Arduino.h"
#include "Config.h"

// This class wraps around F. Malpartida's LiquidCrystal_I2C library and
// provides a custom linear-time algorithm for displaying strings to the LCD
// Download F. Malpartida's LiquidCrystal_I2C libary 
// @https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home
// Extract contents and place into your local Arduino/libraries folder.
// Be sure to either restart the Arduino IDE or click
// Sketch -> Include Libaries -> Manage Libaries to update
class LCDManager {

public:
	static const uint8_t INITIALIZATION_ERROR = -1;
	static const uint8_t OK = 0;
	/* Constructor with optional address, if it is known */
	//LCDManager(uint8_t i2cAddress);
	LCDManager();

	/* Prints a string of any length to the LCD display */
	void printStringToLCD(const String& serialBuffer);

	uint8_t getErrorCode();

	/* Destructor required to release lcdDisplay memory upon completion */
	~LCDManager();
	
private:
	/* Utility method for printsStringToLCD() */
	void printWord(const String& serialBuffer,
		uint8_t& indexSpace, uint8_t& lastSpace,
		uint8_t& wordLength, uint8_t& currRow, uint8_t& offset);

	/* Finds the device address of the LCD on the I2C Bus. 
	   Currently works if the LCD is the only device connected to the bus. */
	byte findDeviceAddress();


	uint8_t I2C_ADDRESS; // Device address for the LCD
	LiquidCrystal_I2C* lcdDisplay;
	uint8_t errorCode = OK;

}; // end class declaration

#endif