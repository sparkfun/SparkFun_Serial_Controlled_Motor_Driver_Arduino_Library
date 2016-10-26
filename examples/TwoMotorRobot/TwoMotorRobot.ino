/******************************************************************************
TwoMotorRobot.ino
Serial Controlled Motor Driver
Marshall Taylor @ SparkFun Electronics
May 20, 2015
https://github.com/sparkfun/Serial_Controlled_Motor_Driver

Resources:
Uses Wire.h for i2c operation
Uses SPI.h for SPI operation

Development environment specifics:
Arduino IDE _______
Teensy loader ________

This code is released under the [MIT License](http://opensource.org/licenses/MIT).
Please review the LICENSE.md file included with this example. If you have any questions 
or concerns with licensing, please contact techsupport@sparkfun.com.
Distributed as-is; no warranty is given.
******************************************************************************/
//This example steps through all motor positions moving them forward, then backwards.
//To use, connect a redboard to the user port, as many slaves as desired on the expansion
//port, and run the sketch.
//
// Note:  While using SPI, the defualt LEDPIN will not toggle
#include <Arduino.h>
#include <stdint.h>
#include "SCMD.h"
#include "SCMD_config.h" //Contains #defines for common SCMD register names and values
#include "Wire.h"

//#defines
#define LEDPIN 13

//Variables
//***** Create the Motor Driver object*****//
SCMD myMotorDriver;

void setup()
{
	Serial.begin(115200);
	pinMode(LEDPIN, OUTPUT);

	Serial.println("Starting sketch.");

	//***** Configure the Motor Driver's Settings *****//

	//  .commInter face can be I2C_MODE or SPI_MODE
	myMotorDriver.settings.commInterface = I2C_MODE;
	//myMotorDriver.settings.commInterface = SPI_MODE;

	//  set address if I2C configuration selected with the config jumpers
	myMotorDriver.settings.I2CAddress = 0x5A; //config pattern "0101" on board for address 0x5A
	//  set chip select if SPI selected with the config jumpers
	myMotorDriver.settings.chipSelectPin = 10;
	
	delay(2500); //Give the serial driver time to get happy
	
	//  initialize the driver and enable the motor outputs
	Serial.print("Starting driver... ID = 0x");
	Serial.println(myMotorDriver.begin(), HEX);
	Serial.println();
	
	//myMotorDriver.inversionMode(0, 1); //invert channel A
	myMotorDriver.inversionMode(1, 1); //invert channel B
	pinMode(8, INPUT_PULLUP);
	
}

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
void loop()
{
	myMotorDriver.setDrive( 0, 0, 0); //Stop motor
	myMotorDriver.setDrive( 1, 0, 0); //Stop motor
	while(digitalRead(8) == 0); //Hold if jumper is placed between pin 8 and ground
	
	//***** Operate the Motor Driver *****//
	//  This walks through all 34 motor positions driving them forward and back.
	//  It uses .setDrive( motorNum, direction, level ) to drive the motors.
	
	//Smoothly move one motor up to speed and back
	for(int i = 0; i < 256; i++)
	{
		myMotorDriver.setDrive( LEFT_MOTOR, 0, i);
		myMotorDriver.setDrive( RIGHT_MOTOR, 0, 20 + (i / 2));
		delay(5);
	}
	for(int i = 255; i >= 0; i--)
	{
		myMotorDriver.setDrive( LEFT_MOTOR, 0, i);
		myMotorDriver.setDrive( RIGHT_MOTOR, 0, 20 + (i / 2));
		delay(5);
	}
	//Smoothly move the other motor up to speed and back
	for(int i = 0; i < 256; i++)
	{
		myMotorDriver.setDrive( LEFT_MOTOR, 0, 20 + (i / 2));
		myMotorDriver.setDrive( RIGHT_MOTOR, 0, i);
		delay(5);
	}
	for(int i = 255; i >= 0; i--)
	{
		myMotorDriver.setDrive( LEFT_MOTOR, 0, 20 + (i / 2));
		myMotorDriver.setDrive( RIGHT_MOTOR, 0, i);
		delay(5);
	}
}
