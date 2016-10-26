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
//This example drives a robot in left and right arcs, driving in an overall wiggly course.
//  It demonstrates the variable control abilities. When used with a RedBot chassis,
//  each turn is about 90 degrees per drive.

#include <Arduino.h>
#include <stdint.h>
#include "SCMD.h"
#include "SCMD_config.h" //Contains #defines for common SCMD register names and values
#include "Wire.h"

//#defines

//Variables
//***** Create the Motor Driver object*****//
SCMD myMotorDriver;

void setup()
{
	Serial.begin(115200);

	Serial.println("Starting sketch.");

	//***** Configure the Motor Driver's Settings *****//

	//  .commInter face can be I2C_MODE or SPI_MODE
	myMotorDriver.settings.commInterface = I2C_MODE;
	//myMotorDriver.settings.commInterface = SPI_MODE;

	//  set address if I2C configuration selected with the config jumpers
	myMotorDriver.settings.I2CAddress = 0x5A; //config pattern "0101" on board for address 0x5A
	//  set chip select if SPI selected with the config jumpers
	myMotorDriver.settings.chipSelectPin = 10;
	
	delay(2500); //Give the serial driver time to check for slaves
	
	//  initialize the driver and enable the motor outputs
	Serial.print("Starting driver... ID = 0x");
	Serial.println(myMotorDriver.begin(), HEX);
	
	//  Report number of slaves found
	uint8_t tempAddr = myMotorDriver.readRegister(SCMD_SLV_TOP_ADDR);
	if( tempAddr >= START_SLAVE_ADDR )
	{
		Serial.print("Detected ");
		Serial.print(tempAddr - START_SLAVE_ADDR + 1); //Top address minus bottom address + 1 = number of slaves
		Serial.println(" slaves.");
	}
	else
	{
		Serial.println("No slaves detected");
	}
	
	//Configure bridging modes
	myMotorDriver.bridgingMode( 1, 1 ); //( DriverNum 1, bridged state = 1 )  This will bridge the first slave

	//uncomment to set inversion
	
	//myMotorDriver.inversionMode(0, 1); //invert master, channel A
	//myMotorDriver.inversionMode(1, 1); //invert master, channel B
	//myMotorDriver.inversionMode(2, 1); //invert slave 1, channel A
	//    no need to configure motor 3, this position does nothing because the slave is bridged.
	//myMotorDriver.inversionMode(4, 1); //invert slave 2, channel A
	//myMotorDriver.inversionMode(5, 1); //invert slave 2, channel B

	//Enable the motors.
	myMotorDriver.enable();
	
	pinMode(8, INPUT_PULLUP);
	
}

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
void loop()
{
	//***** Operate the Motor Driver *****//
	//  This walks through all 34 motor positions driving them forward and back.
	//  It uses .setDrive( motorNum, direction, level ) to drive the motors.
	//
	//  Notice that when i == 3, no motor spins.  This position is made inactive by bridging the first slave.
	Serial.println("Now stepping through the motors.");
	for(int i = 0; i < 6; i++)
	{
		Serial.print("Driving motor ");
		Serial.println(i);
		
		myMotorDriver.setDrive( i, 1, 255); //Drive motor i forward at full speed
		delay(1000);
		myMotorDriver.setDrive( i, 0, 255); //Drive motor i backward at full speed
		delay(1000);
		myMotorDriver.setDrive( i, 1, 0);
	}
}
