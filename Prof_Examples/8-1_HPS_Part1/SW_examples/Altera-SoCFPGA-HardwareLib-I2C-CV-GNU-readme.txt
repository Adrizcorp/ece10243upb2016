Introduction

This HardwareLibs project is meant as an example for using the I2C  APIs.

The project demonstrates the following I2C Flash API features:
- Communication with NHD-0216K3Z-NSW-BBW-V3 LCD screen (master write) - i2c_demo_master_lcd()
- Communication with 24LC32 EEPROM memory (master read and write) - i2c_demo_master_eeprom()
- Communication between two I2C modules (master and slave read and write) - i2c_demo_master_slave()

The project also demonstrates the following additional API features:
- Setting up MMU and caches
- Using Global Timer to implement delays
- Using Interrupts

Note: This example was tested against SoC EDS 16.0b211.

====

Target Boards:
- Altera Cyclone V SoC Development Board rev E.

Target I2C Devices:
- NHD-0216K3Z-NSW-BBW-V3 LCD screen
- 24LC32 EEPROM memory

====

Hardware Design:

A hardware design was required for the master slave example, since only I2C0 is connected on the I2C bus
on both the Arria V and Cyclone V SoC boards.

The hardware design is based on the GHRD (Golden Hardware Reference Design with the only modification that the I2C1 signals
are connected to the I2C bus through the FPGA. This was possible because the FPGA has two pins connected to the board I2C bus.

Note that the Preloader was also re-generated and compiled for this hardware design. The Preloader is ran by 
the debugger script before the program is started.

The hardware design is contained in the folder named 'cv_soc_devkit_i2c_lpbk'.

====


Limitations:

1. Due to the fact that an (RT)OS was not used, the master slave example is limited to a buffer size of 64bits.
This is because implementing a state machine to deal with interupts and with the data flow would be cumbersome and
not very helpful without and (RT)OS.  

=====

Source Files

The following are descriptions of the source and header files contained in this
project:

alt_pt.{c,h}

  Contain the functions to setup the MMU translation tables.

i2c_demo.{c,h}

  Contain the main, system initialization and cleanup, delay functions.

i2c_demo_masterlcd.c

  Contains the functions demonstrating communication with I2C LCD using master operation mode.

i2c_demo_master_eeprom.c

  Contains the functions demonstrating communication with I2C EEPROM using master operation mode.

i2c_demo_master_slave.c

  Contains the functions demonstrating communication between two I2C modules, one running as master and the other as slave.
  
=====

Building Example

Before running the example, the target executable first needs to be built.

1. In DS-5, build the application:
  1a. Switch to the C/C++ Perspective if not already in that perspective by
      selecting the menu: Window >> Open Perspective >> C/C++.
  1b. In the "Project Explorer" panel, right-mouse-click 
      "Altera-SoCFPGA-HardwareLib-I2C-CV-GNU" and select "Build Project".

The Console panel (bottom of the UI) should detail the progress of the build
and report any warnings or errors.

=====

System Setup

1. Connect the USB to serial bridge to the host computer.
2. Connect the USB-BlasterII to the host computer.
3. Install the USB to serial bridge driver on the host computer if that driver
   is not already present. Consult documentation for the DevKit for
   instructions on installing the USB to serial bridge driver.
4. Install the USB-BlasterII driver on the host computer if that driver is not
   already present. Consult documentation for QuartusII for instructions on
   installing the USB-BlasterII driver.
5. In DS-5, configure the launch configuration.
  5a. Select the menu: Run >> Debug Configurations...
  5b. In the options on the left, expand "DS-5 Debugger" and select
      "Altera-SoCFPGA-HardwareLib-I2C-CV-GNU".
  5c. In the "Connections" section near the bottom, click Browse.
  5d. Select the appropriate USB-BlasterII to use. Multiple items will be
      presented if there is more than one USB-BlasterII connection attached to
      the host computer.
  5e. Click "Apply" then "OK" to apply the USB-BlasterII selection.
  5f. Click "Close" to close the Debug Configuration. Otherwise click "Debug"
      run the example in the debugger.

=====

Running the Example

After building the example and setting up the host computer system, the example
can be run by following these steps.
1. Configure the FPGA using the Quartus II Programmer with the following SOF file:  
cv_soc_devkit_i2c_lpbk/output_files/soc_system.sof.

2. In DS-5, launch the debug configuration.
  2a. Switch to the Debug Perspective if not already in that perspective by
      selecting the menu: Window >> Open Perspective >> DS-5 Debug.
  2b. In the "Debug Control" panel, right-mouse-click
      "Altera-SoCFPGA-HardwareLib-I2C-CV-GNU" and select
      "Connect to Target".

Connecting to the target takes a moment to load the preloader, run the
preloader, load the executable, and run executable. After the debug connection
is established, the debugger will pause the execution at the main() function.
Users can then set additional break points, step into, step out of, or step one
line using the DS-5 debugger. Consult documentation for DS-5 for more
information on debugging operations.

=====

Sample output

The address and size of the test buffers are randomly generated for each test, to help 
with wear leveling of the I2C EEPROM memory device. 

The following is a sample output:
INFO: System Initialization.
INFO: Setting up Global Timer.
INFO: Using random seed = 0x60e60cb.

INFO: I2C Demo Master LCD started.
INFO: Init I2C module.
INFO: Enable I2C module.
INFO: Configuring I2C parameters.
INFO: Current I2C speed = 65530 Hz.
INFO: New I2C speed = 40000 Hz.
INFO: Turning display on.
INFO: Clearing screen.
INFO: Turning cursor on.
INFO: Printing text.
INFO: Printing random number.
INFO: Moving cursor to the 2nd line.
INFO: Printing text.
INFO: I2C Demo Master LCD succeeded.

INFO: I2C Demo Master EEPROM started.
INFO: Init I2C module.
INFO: Enable I2C module.
INFO: Configuring I2C parameters.
INFO: Using I2C speed = 100000 Hz.
INFO: Using random address = 0x0129, size = 1502 bytes.
INFO: Writing to EEPROM address 0x0129, size = 1502 bytes.
INFO: Writing single byte at address = 0x0129.
INFO: Writing single byte at address = 0x012a.
INFO: Writing single byte at address = 0x012b.
INFO: Writing single byte at address = 0x012c.
INFO: Writing single byte at address = 0x012d.
INFO: Writing single byte at address = 0x012e.
INFO: Writing single byte at address = 0x012f.
INFO: Writing single byte at address = 0x0130.
INFO: Writing single byte at address = 0x0131.
INFO: Writing single byte at address = 0x0132.
INFO: Writing single byte at address = 0x0133.
INFO: Writing single byte at address = 0x0134.
INFO: Writing single byte at address = 0x0135.
INFO: Writing single byte at address = 0x0136.
INFO: Writing single byte at address = 0x0137.
INFO: Writing single byte at address = 0x0138.
INFO: Writing single byte at address = 0x0139.
INFO: Writing single byte at address = 0x013a.
INFO: Writing single byte at address = 0x013b.
INFO: Writing single byte at address = 0x013c.
INFO: Writing single byte at address = 0x013d.
INFO: Writing single byte at address = 0x013e.
INFO: Writing single byte at address = 0x013f.
INFO: Writing 32 byte page at address = 0x0140.
INFO: Writing 32 byte page at address = 0x0160.
INFO: Writing 32 byte page at address = 0x0180.
INFO: Writing 32 byte page at address = 0x01a0.
INFO: Writing 32 byte page at address = 0x01c0.
INFO: Writing 32 byte page at address = 0x01e0.
INFO: Writing 32 byte page at address = 0x0200.
INFO: Writing 32 byte page at address = 0x0220.
INFO: Writing 32 byte page at address = 0x0240.
INFO: Writing 32 byte page at address = 0x0260.
INFO: Writing 32 byte page at address = 0x0280.
INFO: Writing 32 byte page at address = 0x02a0.
INFO: Writing 32 byte page at address = 0x02c0.
INFO: Writing 32 byte page at address = 0x02e0.
INFO: Writing 32 byte page at address = 0x0300.
INFO: Writing 32 byte page at address = 0x0320.
INFO: Writing 32 byte page at address = 0x0340.
INFO: Writing 32 byte page at address = 0x0360.
INFO: Writing 32 byte page at address = 0x0380.
INFO: Writing 32 byte page at address = 0x03a0.
INFO: Writing 32 byte page at address = 0x03c0.
INFO: Writing 32 byte page at address = 0x03e0.
INFO: Writing 32 byte page at address = 0x0400.
INFO: Writing 32 byte page at address = 0x0420.
INFO: Writing 32 byte page at address = 0x0440.
INFO: Writing 32 byte page at address = 0x0460.
INFO: Writing 32 byte page at address = 0x0480.
INFO: Writing 32 byte page at address = 0x04a0.
INFO: Writing 32 byte page at address = 0x04c0.
INFO: Writing 32 byte page at address = 0x04e0.
INFO: Writing 32 byte page at address = 0x0500.
INFO: Writing 32 byte page at address = 0x0520.
INFO: Writing 32 byte page at address = 0x0540.
INFO: Writing 32 byte page at address = 0x0560.
INFO: Writing 32 byte page at address = 0x0580.
INFO: Writing 32 byte page at address = 0x05a0.
INFO: Writing 32 byte page at address = 0x05c0.
INFO: Writing 32 byte page at address = 0x05e0.
INFO: Writing 32 byte page at address = 0x0600.
INFO: Writing 32 byte page at address = 0x0620.
INFO: Writing 32 byte page at address = 0x0640.
INFO: Writing 32 byte page at address = 0x0660.
INFO: Writing 32 byte page at address = 0x0680.
INFO: Writing 32 byte page at address = 0x06a0.
INFO: Writing 32 byte page at address = 0x06c0.
INFO: Writing 32 byte page at address = 0x06e0.
INFO: Writing single byte at address = 0x0700.
INFO: Writing single byte at address = 0x0701.
INFO: Writing single byte at address = 0x0702.
INFO: Writing single byte at address = 0x0703.
INFO: Writing single byte at address = 0x0704.
INFO: Writing single byte at address = 0x0705.
INFO: Writing single byte at address = 0x0706.
INFO: Reading from EEPROM address 0x0129, size = 1502 bytes.
INFO: Setting EEPROM pointer address to 0x0129.
INFO: Sequentially reading 1502 bytes from EEPROM.
INFO: Comparing written data with read back data.
INFO: I2C Demo Master EEPROM succeeded.

INFO: I2C demo master slave started.
INFO: Setting up I2C interrupt.
INFO: Init master I2C module.
INFO: Init slave I2C module.
TEST: Buffer size = 64.
INFO: Master transmitting.
INFO: Master receiving.
INFO [ISR]: Reading data from bus ...
INFO [ISR]: Writing 64 data item(s) to bus..
INFO: Comparing received data with transmitted data.
TEST: Buffer size = 32.
INFO: Master transmitting.
INFO: Master receiving.
INFO [ISR]: Reading data from bus ...
INFO [ISR]: Writing 32 data item(s) to bus..
INFO: Comparing received data with transmitted data.
INFO: Cleaning up master.
INFO: Cleaning up slave.
INFO: Cleaning up I2C interrupt.
INFO: I2C demo master slave succeeded.

INFO: System shutdown.

RESULT: All tests successful.