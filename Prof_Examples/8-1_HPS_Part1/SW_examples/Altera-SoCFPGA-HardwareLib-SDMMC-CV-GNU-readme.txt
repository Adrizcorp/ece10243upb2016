Introduction

This HardwareLibs project is meant as an example for using the SDMMC APIs.

The project demonstrates the following SDMMC Flash API features:
- Initializing SD/MMC card
- Reading and writing using Block I/O functions

Note: This example was tested against SoC EDS 16.0b211.

====

Target Boards:
- Altera Cyclone V SoC Development Board rev E.

====

Limitations:

1. Read/Write operations take a 32bit address parameter, which limit them to 4GB of data.

=====

Source Files

The following are descriptions of the source and header files contained in this
project:

sdmmc_demo.c

  Contains the functions demonstrating SDMMC APIs.
  
=====

Building Example

Before running the example, the target executable first needs to be built.

1. In DS-5, build the application:
  1a. Switch to the C/C++ Perspective if not already in that perspective by
      selecting the menu: Window >> Open Perspective >> C/C++.
  1b. In the "Project Explorer" panel, right-mouse-click 
      "Altera-SoCFPGA-HardwareLib-SDMMC-CV-GNU" and select "Build Project".

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
      "Altera-SoCFPGA-HardwareLib-SDMMC-CV-GNU".
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

1. Insert SDHC card in slot on the board
2. In DS-5, launch the debug configuration.
  2a. Switch to the Debug Perspective if not already in that perspective by
      selecting the menu: Window >> Open Perspective >> DS-5 Debug.
  2b. In the "Debug Control" panel, right-mouse-click
      "Altera-SoCFPGA-HardwareLib-SDMMC-CV-GNU" and select
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
with wear leveling of the SDMMC device. 

The following is a sample output:

INFO: System Initialization.
INFO: Setting up Global Timer.
INFO: Setting up SDMMC.
INFO: SDHC Card detected.
INFO: Card width = 4.
INFO: Card block size = 512.
INFO: Card size = 3980394496.
INFO: Using random seed = 0x1cd6e02c.

INFO: Demo block I/O using address = 0x75fbf800, size = 456192 bytes.
INFO: Writing to address 0x75fbf800, size = 456192 bytes using block I/O.
INFO: Reading from address 0x75fbf800, size = 456192 bytes using block I/O.
INFO: Comparing written data with read back data.
INFO: Demo block I/O succeeded.

INFO: System shutdown.

RESULT: All tests successful.
