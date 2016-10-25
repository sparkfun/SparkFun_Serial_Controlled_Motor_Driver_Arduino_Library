SparkFun <PRODUCT NAME> Arduino Library
========================================

![SparkFun Part Name](URL for picture of part)

[*SparkFun Part Name (SKU)*](URL for product on Sparkfun.com)

<Basic description of the library.>

Repository Contents
-------------------

* **/examples** - Example sketches for the library (.ino). Run these from the Arduino IDE. 
* **/extras** - Additional documentation for the user. These files are ignored by the IDE. 
* **/src** - Source files for the library (.cpp, .h).
* **keywords.txt** - Keywords from this library that will be highlighted in the Arduino IDE. 
* **library.properties** - General library properties for the Arduino package manager. 

Documentation
--------------

* **[Installing an Arduino Library Guide](https://learn.sparkfun.com/tutorials/installing-an-arduino-library)** - Basic information on how to install an Arduino library.
* **[Product Repository](GitHub Product URL)** - Main repository (including hardware files) for the <PRODUCT NAME>.
* **[Hookup Guide](Learn.SparkFun URL)** - Basic hookup guide for the <PRODUCT NAME>.

### Functions

#### uint8_t begin( void );

Call after providing settings to start the wire library, apply the settings, get the ID word (returned, should be 0xA9), and enable the drivers.

#### void reset( void );

This resets the I2C hardware for Teensy devices using the alternate library, and nothing otherwise.

#### void setDrive( uint8_t channel, uint8_t direction, uint8_t level );

This sets an output to drive at a level and direction.

* channel:  Motor number, 0 through 33.
* direction:  1 or 0 for forward or backwards.
* level: 0 to 255 for drive strength.

#### void inversionMode( uint8_t motorNum, uint8_t polarity );

This switches the perceived direction of a particular motor.

* motorNum:  Motor number, 0 through 33.
* polarity: 0 for normal and 1 for inverted direction.

#### void bridgingMode( uint8_t driverNum, uint8_t bridged );

This connects any board's outputs together controlling both from what was the 'A' position.

* driverNum:  Number of connected SCMD, 0 (master) to 16.
* bridged: 0 for normal and 1 for bridged.

#### void getDiagnostics( SCMDDiagnostics &diagObjectReference );

This returns a diagnostic report from the master.

* &diagObjectReference:  Pass a local SCMDDiagnostics object that will be written into.

#### void getRemoteDiagnostics( uint8_t address, SCMDDiagnostics &diagObjectReference );

This returns a diagnostic report from a slave.

* address: address of intended slave.  This starts at 0x50 for the first slave and goes up from there.
* &diagObjectReference:  Pass a local SCMDDiagnostics object that will be written into.

#### void resetDiagnosticCounts( void );

Clears the diagnostic counts of a master.

#### void resetRemoteDiagnosticCounts( uint8_t address );

Clears the diagnostic counts of a slave.

* address: address of intended slave.  This starts at 0x50 for the first slave and goes up from there.

#### uint8_t readRegister(uint8_t offset);

Returns the contents of a memory location of the master.

* offset:  Memory address to read.

#### void writeRegister(uint8_t offset, uint8_t dataToWrite);

Writes data to a memory location of the master.

* offset:  Memory address to write.
* dataToWrite:  Data to write to that address.

#### uint8_t readRemoteRegister(uint8_t address, uint8_t offset);

Returns the contents of a memory location of a slave.

* address: address of intended slave.  This starts at 0x50 for the first slave and goes up from there.
* offset:  Memory address to read.

#### void writeRemoteRegister(uint8_t address, uint8_t offset, uint8_t dataToWrite);

Writes data to a memory location of a slave.

* address: address of intended slave.  This starts at 0x50 for the first slave and goes up from there.
* offset:  Memory address to write.
* dataToWrite:  Data to write to that address.


Products that use this Library 
---------------------------------

* [Part SKU](SparkFun part URL)- Basic part and short description here
* [Part SKU](SparkFun part URL)- Basic part and short description here

Version History
---------------

* [vExxFxxZxxHxxLxxSxx](URL for tag specific to this version) - Description 
* [vEyyFyyZyyHyyLyySyy](URL for tag specific to this version) - Description

License Information
-------------------

This product is _**open source**_! 

Please review the LICENSE.md file for license information. 

If you have any questions or concerns on licensing, please contact techsupport@sparkfun.com.

Distributed as-is; no warranty is given.

- Your friends at SparkFun.

_<COLLABORATION CREDIT>_
