//---------------------------------------------------------------------
// Arduino Source - LCDManager.cpp
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

#include "LCDManager.h"

//---------------------------------------------------------------------
// Public Members


LCDManager::LCDManager() {
	lcdDisplay = NULL;
	/*Serial.begin(9600);
	Serial.println("Finding Device address...");*/
	I2C_ADDRESS = findDeviceAddress();
	if (I2C_ADDRESS != -1) {
		lcdDisplay = new LiquidCrystal_I2C(I2C_ADDRESS,
			En_pin,
			Rw_pin,
			Rs_pin,
			D4_pin,
			D5_pin,
			D6_pin,
			D7_pin);

		lcdDisplay->begin(LED_CHARS_PER_LINE, LED_NUM_LINES);
		// backlight pin, positive polarity
		// If the LED flickers in and out, the likely fix is a change 
		// of the polarity to NEGATIVE
		lcdDisplay->setBacklightPin(BACKLIGHT_PIN, POSITIVE);
		lcdDisplay->setBacklight(LED_ON);
		lcdDisplay->clear();
		lcdDisplay->setCursor(0, 0);
		printStringToLCD("Robot Initialized");
	}
}

LCDManager::~LCDManager() {
}


void LCDManager::printStringToLCD(const String& serialBuffer) {
	lcdDisplay->clear();
	// O(n) algorithm -> It's the best... around... no one's ever gonna bring it down...
	uint8_t wordLength = 0, currRow = 0, lastSpace = 0, indexSpace = 0, offset = 0;
	int strLength = serialBuffer.length();
	char stringBuffer[strLength + 1]; serialBuffer.toCharArray(stringBuffer, strLength);
	for (offset; offset < strLength + 1; offset++)
	{
		if (stringBuffer[offset] == ' ')
		{
			printWord(serialBuffer, indexSpace, lastSpace, wordLength, currRow, offset);
		}
		wordLength++;
	}
	printWord(serialBuffer, indexSpace, lastSpace, wordLength, currRow, offset);
}

uint8_t LCDManager::getErrorCode() {
	return errorCode;
}

//---------------------------------------------------------------------
// Private Members


byte LCDManager::findDeviceAddress() {
	// I2C does 7-bit addressing.. 2^7
	// Dr. Kwon would know this sooo fast. 
	// "What is 01111111?"  "You are EE!  You should know this!"
	int POSSIBLE_ADDRESSES = 128;
	Wire.begin();
	byte addressOfDevice = 1;
	bool addressFound = false;
	for (addressOfDevice; addressOfDevice < POSSIBLE_ADDRESSES; addressOfDevice++)
	{
		Wire.beginTransmission(addressOfDevice);
		if (Wire.endTransmission() == 0)
		{
			addressFound = true;
			break;
		}
	}
	if (addressFound) {
		Serial.print("Device Address: ");
		Serial.println(addressOfDevice);
		errorCode = OK;
		return addressOfDevice;
	}
	else {
		errorCode = INITIALIZATION_ERROR;
		return errorCode;
	}
}

void LCDManager::printWord(const String& serialBuffer,
	uint8_t& indexSpace, uint8_t& lastSpace,
	uint8_t& wordLength, uint8_t& currRow, uint8_t& offset) {
	// space enough for the word
	if ((indexSpace + wordLength - 1) < LED_CHARS_PER_LINE)
	{
		lcdDisplay->print(serialBuffer.substring(lastSpace, lastSpace + wordLength));
	}
	// not enough space, need to take more.
	else
	{
		if (currRow == 1) {
			lcdDisplay->clear();
		}
		currRow = currRow == 1 ? 0 : 1;
		lcdDisplay->setCursor(0, currRow);
		lcdDisplay->print(serialBuffer.substring(lastSpace + 1, lastSpace + wordLength));
		indexSpace = 0;
	}
	indexSpace += wordLength;
	lastSpace = offset;
	wordLength = 0;
}


