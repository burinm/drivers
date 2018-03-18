# drivers
## Cross platform embedded drivers written in C
A library of useful device drivers and data manipulation code. It is organized for reuse across different platforms. The protocol layer has been seperated from the platforms and devices so the code is extensible.

## Protocols including:
* I2C
* SPI
* UART

## Platforms including:
* FRDM-KL25Z
* Beagle Bone Black
* Linux x86-64
* 8051 barebones
* 6502/65c02 barebones

## Devices including:
* EEPROM, FRAM memory
* I/O expanders 
* Nordic nrf24L01 wireless tranceiver 

## Organization
This repository splits up the driver code into a pseudo-object-oriented design based on the follwing structure:

* **protocol** - Defines a protocol interface. This is simply done using the keyword "extern". Since all the protocols listed involve involve moving lines of data high or low, the interface defines those lines and states as related to thier protocol.
* **platform** - Implements the protocol’s interface. In this case, hardware specific code per platform that moves data lines high or low.
* **device** -  Extends a protocol layer. Different devices send different commands to the same protocol. It uses the protocol’s APIs (doesn't implement the interface).

This is the main library that all my other GitHub projects use to reference driver code. Please clone this repository the same parent directory as other projects:

```
./XXX/drivers
./XXX/sbc6502
./XXX/fatbit
./XXX/etc...
```

* **mylib** - This directory is an ongoing development for tiny C data manipulation routines. Right now, mostly a circular buffer implementation.

* **XXX.arch** - Platform specific code for bringup, and assembly routines

* **unittests** - Is a collection of unit tests for **mylib**
