Introduction

This HardwareLibs project is meant as an example for using the SPI APIs.

The project demonstrates the following SPI Flash API features:
- Communication between SPI Master and SPI Slave using loopback method

The project also demonstrates the following additional API features:
- Using HPS to configure FPGA

Note: This example was tested against SoC EDS 16.0b211.
====

Target Boards:
- Altera Cyclone V SoC Development Board rev E.

====

Hardware Design:

A hardware design was required for this example, to connect the SPI Master and 
SPI Slave by loopback in the FPGA on the Cyclone V SoC boards

The hardware design is based on the GHRD (Golden Hardware Reference Design) 
with the modification to route the SPIM1 and SPIS1 signals to the FPGA and 
loopback these signals in the FPGA.

Note that the Preloader was also re-generated and compiled for this hardware 
design. The Preloader is ran by the debugger script before the program is 
started.

The hardware design is contained in the folder named 'cv_soc_devkit_spi_lpbk'.

=====

Source Files

The following are descriptions of the source and header files contained in this
project:

spi_demo.c

  Contains the main, system initialization and cleanup, interrupt setup, 
  functions demonstrating the SPI APIs.
  
=====

Building Example

Before running the example, the target executable first needs to be built.

1. In DS-5, build the application:
  1a. Switch to the C/C++ Perspective if not already in that perspective by
      selecting the menu: Window >> Open Perspective >> C/C++.
  1b. In the "Project Explorer" panel, right-mouse-click 
      "Altera-SoCFPGA-HardwareLib-SPI-CV-GNU" and select "Build Project".

The Console panel (bottom of the UI) should detail the progress of the build
and report any warnings or errors.

=====

Board Setup

Before running the example, the target board MSEL switch (SW3) need to set to
mode FPP32 with Data Compression: UP,DOWN,UP,DOWN,UP,UP (Left->Right).

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
      "Altera-SoCFPGA-HardwareLib-SPI-CV-GNU".
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
1. In DS-5, launch the debug configuration.
  1a. Switch to the Debug Perspective if not already in that perspective by
      selecting the menu: Window >> Open Perspective >> DS-5 Debug.
  1b. In the "Debug Control" panel, right-mouse-click
      "Altera-SoCFPGA-HardwareLib-SPI-CV-GNU" and select
      "Connect to Target".

Connecting to the target takes a moment to load the preloader, run the
preloader, load the executable, and run executable. After the debug connection
is established, the debugger will pause the execution at the main() function.
Users can then set additional break points, step into, step out of, or step one
line using the DS-5 debugger. Consult documentation for DS-5 for more
information on debugging operations.

=====

Sample output

INFO: Setup FPGA System ...
INFO: MSEL [14] configured correctly for FPGA image.
INFO: FPGA Image binary at 0x11c7f8.
INFO: FPGA Image size is 2301008 bytes.
INFO: alt_fpga_configure() successful on the 1 of 5 retry(s).
INFO: Setup of FPGA successful.

INFO: Setting up SPI master and slave ...
INFO: Init and setup SPI Master.
INFO: Init and setup SPI Slave.
INFO: Setting up SPI interrupt.

TEST: Buffer size = 1.
INFO: Master transmitting ...
INFO: Master transmit complete.
INFO [ISR]: spi_int = 0x10.
INFO [ISR]: RX FIFO Full. Read [1] item(s) from RX FIFO. Reenabling TXEI interrupt.
INFO [ISR]: spi_int = 0x1.
INFO [ISR]: TX FIFO Empty. [1] item(s) transfered to TXFIFO. [0] item(s) remaining.
INFO: Master receiving ...
INFO: Master receive complete.
INFO [ISR]: spi_int = 0x10.
INFO [ISR]: RX FIFO Full. Read [1] item(s) from RX FIFO. Reenabling TXEI interrupt.
INFO [ISR]: spi_int = 0x1.
INFO [ISR]: TX FIFO Empty. [1] item(s) transfered to TXFIFO. [0] item(s) remaining.
INFO: Comparing send and receive buffer ...
INFO: Buffers match.

TEST: Buffer size = 2.
INFO: Master transmitting ...
INFO: Master transmit complete.
INFO [ISR]: spi_int = 0x10.
INFO [ISR]: RX FIFO Full. Read [2] item(s) from RX FIFO. Reenabling TXEI interrupt.
INFO [ISR]: spi_int = 0x1.
INFO [ISR]: TX FIFO Empty. [2] item(s) transfered to TXFIFO. [0] item(s) remaining.
INFO: Master receiving ...
INFO: Master receive complete.
INFO [ISR]: spi_int = 0x10.
INFO [ISR]: RX FIFO Full. Read [2] item(s) from RX FIFO. Reenabling TXEI interrupt.
INFO [ISR]: spi_int = 0x1.
INFO [ISR]: TX FIFO Empty. [2] item(s) transfered to TXFIFO. [0] item(s) remaining.
INFO: Comparing send and receive buffer ...
INFO: Buffers match.

TEST: Buffer size = 4.
INFO: Master transmitting ...
INFO: Master transmit complete.
INFO [ISR]: spi_int = 0x10.
INFO [ISR]: RX FIFO Full. Read [4] item(s) from RX FIFO. Reenabling TXEI interrupt.
INFO [ISR]: spi_int = 0x1.
INFO [ISR]: TX FIFO Empty. [4] item(s) transfered to TXFIFO. [0] item(s) remaining.
INFO: Master receiving ...
INFO: Master receive complete.
INFO [ISR]: spi_int = 0x10.
INFO [ISR]: RX FIFO Full. Read [4] item(s) from RX FIFO. Reenabling TXEI interrupt.
INFO [ISR]: spi_int = 0x1.
INFO [ISR]: TX FIFO Empty. [4] item(s) transfered to TXFIFO. [0] item(s) remaining.
INFO: Comparing send and receive buffer ...
INFO: Buffers match.

TEST: Buffer size = 8.
INFO: Master transmitting ...
INFO: Master transmit complete.
INFO [ISR]: spi_int = 0x10.
INFO [ISR]: RX FIFO Full. Read [8] item(s) from RX FIFO. Reenabling TXEI interrupt.
INFO [ISR]: spi_int = 0x1.
INFO [ISR]: TX FIFO Empty. [8] item(s) transfered to TXFIFO. [0] item(s) remaining.
INFO: Master receiving ...
INFO: Master receive complete.
INFO [ISR]: spi_int = 0x10.
INFO [ISR]: RX FIFO Full. Read [8] item(s) from RX FIFO. Reenabling TXEI interrupt.
INFO [ISR]: spi_int = 0x1.
INFO [ISR]: TX FIFO Empty. [8] item(s) transfered to TXFIFO. [0] item(s) remaining.
INFO: Comparing send and receive buffer ...
INFO: Buffers match.

TEST: Buffer size = 16.
INFO: Master transmitting ...
INFO: Master transmit complete.
INFO [ISR]: spi_int = 0x10.
INFO [ISR]: RX FIFO Full. Read [16] item(s) from RX FIFO. Reenabling TXEI interrupt.
INFO [ISR]: spi_int = 0x1.
INFO [ISR]: TX FIFO Empty. [16] item(s) transfered to TXFIFO. [0] item(s) remaining.
INFO: Master receiving ...
INFO: Master receive complete.
INFO [ISR]: spi_int = 0x10.
INFO [ISR]: RX FIFO Full. Read [16] item(s) from RX FIFO. Reenabling TXEI interrupt.
INFO [ISR]: spi_int = 0x1.
INFO [ISR]: TX FIFO Empty. [16] item(s) transfered to TXFIFO. [0] item(s) remaining.
INFO: Comparing send and receive buffer ...
INFO: Buffers match.

TEST: Buffer size = 32.
INFO: Master transmitting ...
INFO: Master transmit complete.
INFO [ISR]: spi_int = 0x10.
INFO [ISR]: RX FIFO Full. Read [32] item(s) from RX FIFO. Reenabling TXEI interrupt.
INFO [ISR]: spi_int = 0x1.
INFO [ISR]: TX FIFO Empty. [32] item(s) transfered to TXFIFO. [0] item(s) remaining.
INFO: Master receiving ...
INFO: Master receive complete.
INFO [ISR]: spi_int = 0x10.
INFO [ISR]: RX FIFO Full. Read [32] item(s) from RX FIFO. Reenabling TXEI interrupt.
INFO [ISR]: spi_int = 0x1.
INFO [ISR]: TX FIFO Empty. [32] item(s) transfered to TXFIFO. [0] item(s) remaining.
INFO: Comparing send and receive buffer ...
INFO: Buffers match.

TEST: Buffer size = 64.
INFO: Master transmitting ...
INFO: Master transmit complete.
INFO [ISR]: spi_int = 0x10.
INFO [ISR]: RX FIFO Full. Read [64] item(s) from RX FIFO. Reenabling TXEI interrupt.
INFO [ISR]: spi_int = 0x1.
INFO [ISR]: TX FIFO Empty. [64] item(s) transfered to TXFIFO. [0] item(s) remaining.
INFO: Master receiving ...
INFO: Master receive complete.
INFO [ISR]: spi_int = 0x10.
INFO [ISR]: RX FIFO Full. Read [64] item(s) from RX FIFO. Reenabling TXEI interrupt.
INFO [ISR]: spi_int = 0x1.
INFO [ISR]: TX FIFO Empty. [64] item(s) transfered to TXFIFO. [0] item(s) remaining.
INFO: Comparing send and receive buffer ...
INFO: Buffers match.

TEST: Buffer size = 128.
INFO: Master transmitting ...
INFO: Master transmit complete.
INFO [ISR]: spi_int = 0x10.
INFO [ISR]: RX FIFO Full. Read [128] item(s) from RX FIFO. Reenabling TXEI interrupt.
INFO [ISR]: spi_int = 0x1.
INFO [ISR]: TX FIFO Empty. [128] item(s) transfered to TXFIFO. [0] item(s) remaining.
INFO: Master receiving ...
INFO: Master receive complete.
INFO [ISR]: spi_int = 0x10.
INFO [ISR]: RX FIFO Full. Read [128] item(s) from RX FIFO. Reenabling TXEI interrupt.
INFO [ISR]: spi_int = 0x1.
INFO [ISR]: TX FIFO Empty. [128] item(s) transfered to TXFIFO. [0] item(s) remaining.
INFO: Comparing send and receive buffer ...
INFO: Buffers match.

INFO: Cleaning up SPI master and slave ...
INFO: Cleaning up SPI interrupt.
INFO: Cleanup of FPGA ...
RESULT: All tests successful.

