Introduction

This HardwareLibs project is meant as an example for using the QSPI Flash APIs.

The project demonstrates the following QSPI Flash API features:
The project demonstrates the following QSPI Flash API features:
- Reading and writing using Generic Block I/O functions
- Reading and writing using Indirect Mode
- Reading and writing using DMA Mode
- Erasing

The project also demonstrates the following additional API features:
- Setting up MMU and caches
- Performing cache cleanup and purging
- Setting up DMA, and using Memory2Peripheral and Peripheral2Memory operations

Note: This example was tested against SoC EDS 16.0b211.

====

Target Boards:
- Altera Arria V SoC Development Board rev C.

The following devices are supported:
- MICRON M25P40
- MICRON M25P16
- MICRON M25PX16
- SPANSION S25FL116K
- SPANSION S25FL256S
- SPANSION S25FL512S
- MACRONIX MX25L25635
- MACRONIX MX66L51235
- MICRON N25Q128
- MICRON N25Q512A (*)
- MICRON N25Q00AA

(*) This is the original device soldered on the Development Board.

====

Limitations:

1. The DMA mode write function only programs one page at a time. This should only be necessary
for the Micron multi-die devices, but there seems to be a limitation with the DMA driver code.

2. There is a known issue with large QSPI writes over DMA. Therefore the DMA write was temporarily 
disabled in the code and replaced with block I/O write. This is expected to be fixed in the next version
of this example.

3. The device SPANSION_S25FL256S requires 7 read dummy bits when using LC=10 according to the datasheet.
Please edit the file alt_qspi.c and change the structure qspi_config_SPANSION_S25FL256S to have 7 dummy 
read bits instead of the default of 6.

4. The following HWLIBs functions are required, but they are not made public in alt_qspi.h. They were
added in the application include file called "qspi_demo.h":
extern bool alt_qspi_is_micron_multidie(void);
extern uint32_t alt_qspi_get_die_size(void);
extern uint32_t alt_qspi_get_page_size(void); 

====

QSPI Background Information

Different QSPI devices have different capabilities, so the code has to be customized to deal with
each type of device.

Some of the things that vary between different QSPI flash chips are:
- Instructions used for initialization:
    - reset chip, if available
    - configure chip to quad mode if available
    - configure number of address bytes if extended address instructions not available
- Instructions used for erasing: 
    - opcodes
    - supported erase sizes: sector, subsector, bulk etc
    - number of address bytes
- Instructions used for reading: 
    - opcodes
    - number of lines for address, data
    - number of dummy bits, if applicable    
- Instructions used for writing 
    - opcodes
    - page size
    - number of lines for address, data
    - number of dummy bits, if applicable
    
Another aspect is that some of the Micron multi-die devices involve further customizations:
- They require reading a special Flag Status Register to determine when a write operation has completed. 
Since the Cyclone V/Arria V SoC QSPI Flash Controller does not automatically poll this register, each 
write operation needs to be split into page-sized chunks, and after each write the register needs to 
be polled manually.
- They do not have a single command for erasing the whole chip, instead each die can be erased separately
- They cannot read past a die boundary, so reads need to be split into chunks fitting into a single die.

Please consult the following files for details:
- alt_qspi.h
- alt_qspi.c
    
====

Source Files

The following are descriptions of the source and header files contained in this
project:

alt_pt.{c,h}

  Contain the functions to setup the MMU translation tables.

qspi_demo.{c,h}

  Contain the main, system initialization and system cleanup functions.

qspi_demo_blockio.c

  Contains the functions demonstrating QSPI Flash generic block I/O APIs.

qspi_demo_dma.c

  Contains the functions demonstrating QSPI Flash DMA APIs.

qspi_demo_erase.c

  Contains the functions demonstrating QSPI Flash erase APIs.

qspi_demo_indirect.c

  Contains the functions demonstrating QSPI Flash indirect mode APIs.
  
=====

Building Example

Before running the example, the target executable first needs to be built.

1. In DS-5, build the application:
  1a. Switch to the C/C++ Perspective if not already in that perspective by
      selecting the menu: Window >> Open Perspective >> C/C++.
  1b. In the "Project Explorer" panel, right-mouse-click 
      "Altera-SoCFPGA-HardwareLib-QSPI-AV-GNU" and select "Build Project".

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
      "Altera-SoCFPGA-HardwareLib-QSPI-AV-GNU".
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
      "Altera-SoCFPGA-HardwareLib-QSPI-AV-GNU" and select
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
with wear leveling of the QSPI Flash memory device. 

The following is a sample output:

INFO: System Initialization.
INFO: Setting up Global Timer.
INFO: Setting up interrupt system.
INFO: Populating page table and enabling MMU.
INFO: Enabling caches.
INFO: Configuring DMA.
INFO: Allocating DMA channel.
INFO: Initializing QSPI.
INFO: Configuring QSPI DMA single size = 4, burst_size = 4 bytes.
INFO: Enabling QSPI.
INFO: Checking QSPI is idle.
INFO: Detected Device = MICRON_N25Q512A. Size = 64 MBytes.
INFO: Using random seed = 0x4097f17a.

INFO: Demo block I/O using address = 0x03cb2ea8, size = 3092 bytes.
INFO: Saving 3752 bytes from address 0x3cb2000 which also need to be erased.
INFO: Saving 1348 bytes from address 0x3cb3abc which also need to be erased.
INFO: Erasing 8192 bytes at address 0x03cb2000.
INFO: Restoring 3752 bytes to address 0x03cb2000.
INFO: Restoring 1348 bytes to address 0x03cb3abc.
INFO: Erasing completed successfully.
INFO: Writing to address 0x03cb2ea8, size = 3092 bytes using block I/O.
INFO: Reading from address 0x03cb2ea8, size = 3092 bytes using block I/O.
INFO: Comparing written data with read back data.
INFO: Demo block I/O succeeded.

INFO: Demo indirect mode using address = 0x0086037c, size = 1796 bytes.
INFO: Saving 892 bytes from address 0x860000 which also need to be erased.
INFO: Saving 1408 bytes from address 0x860a80 which also need to be erased.
INFO: Erasing 4096 bytes at address 0x00860000.
INFO: Restoring 892 bytes to address 0x00860000.
INFO: Restoring 1408 bytes to address 0x00860a80.
INFO: Erasing completed successfully.
INFO: Writing to address 0x0086037c, size = 132 bytes using indirect mode.
INFO: Writing to address 0x00860400, size = 256 bytes using indirect mode.
INFO: Writing to address 0x00860500, size = 256 bytes using indirect mode.
INFO: Writing to address 0x00860600, size = 256 bytes using indirect mode.
INFO: Writing to address 0x00860700, size = 256 bytes using indirect mode.
INFO: Writing to address 0x00860800, size = 256 bytes using indirect mode.
INFO: Writing to address 0x00860900, size = 256 bytes using indirect mode.
INFO: Writing to address 0x00860a00, size = 128 bytes using indirect mode.
INFO: Reading from address 0x0086037c, size = 1796 bytes using indirect mode.
INFO: Comparing written data with read back data.
INFO: Demo indirect mode succeeded.

INFO: Demo DMA mode using address = 0x021e0128, size = 1996 bytes.
INFO: Saving 296 bytes from address 0x21e0000 which also need to be erased.
INFO: Saving 1804 bytes from address 0x21e08f4 which also need to be erased.
INFO: Erasing 4096 bytes at address 0x021e0000.
INFO: Restoring 296 bytes to address 0x021e0000.
INFO: Restoring 1804 bytes to address 0x021e08f4.
INFO: Erasing completed successfully.
INFO: Enabling QSPI DMA operation.
INFO: Writing to address 0x021e0128, size = 1996 bytes using BLOCKIO mode.
INFO: Reading from address 0x021e0128, size = 1996 bytes using DMA mode.
INFO: Comparing written data with read back data.
INFO: Demo DMA mode succeeded.

INFO: System shutdown.

RESULT: All tests successful.
