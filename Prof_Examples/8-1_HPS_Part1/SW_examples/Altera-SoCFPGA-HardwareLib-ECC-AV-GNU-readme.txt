Introduction

This HardwareLibs project is meant as an example for using the ECC APIs.

The project demonstrates the following ECC API features for the following components:
- Onchip RAM
- SD/MMC
- QSPI
- DMA
- L2 cache

Each component will demonstrate on the following:
- Setup and enable ECC
- Setup and enable ECC interrupts
- Inject single and double bit errors
- Single and double bit errors detection

Note: This example was tested against SoC EDS 16.0b211.

====

Target Boards:
- Altera Arria V SoC Development Board rev C.

====

Limitations:
N/A
 
====

Source Files

The following are descriptions of the source and header files contained in this
project:

ecc_demo.c

  Contain the main, system initialization and cleanup.
  
ecc_demo_ocram.c

  Contain functions demonstrating ECC single and double bit injection and detection.
  
ecc_demo_sdmmc.c

  Contain functions demonstrating ECC single and double bit injection and detection.
  
ecc_demo_qspi.c

  Contain functions demonstrating ECC single and double bit injection and detection.
  
ecc_demo_dma.c

  Contain functions demonstrating ECC single and double bit injection and detection.
  
ecc_demo_l2.c

  Contain functions demonstrating ECC single and double bit injection and detection.
  
alt_pt.{c,h}

  Contain functions to setup MMU page tables.
  
alt_ecc_scratch_ram_get.c

  Contain function to be appended to alt_ecc.c during compile time. Refer Makefile for 
  details.
  
=====

Building Example

Before running the example, the target executable first needs to be built.

1. In DS-5, build the application:
  1a. Switch to the C/C++ Perspective if not already in that perspective by
      selecting the menu: Window >> Open Perspective >> C/C++.
  1b. In the "Project Explorer" panel, right-mouse-click 
      "Altera-SoCFPGA-HardwareLib-ECC-AV-GNU" and select "Build Project".

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
      "Altera-SoCFPGA-HardwareLib-ECC-AV-GNU".
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
      "Altera-SoCFPGA-HardwareLib-ECC-AV-GNU" and select
      "Connect to Target".

Connecting to the target takes a moment to load the preloader, run the
preloader, load the executable, and run executable. After the debug connection
is established, the debugger will pause the execution at the main() function.
Users can then set additional break points, step into, step out of, or step one
line using the DS-5 debugger. Consult documentation for DS-5 for more
information on debugging operations.

=====

Sample output

INFO: System Initialization.

INFO: ECC OCRAM Demo started.
INFO: Initialize and start ECC for OCRAM.
INFO: Injecting SERR ...
INFO: Error injected at 0xfffff42c.
INFO: Read OCRAM contents ...
INFO: SERR detected : 1.
INFO: Injecting DERR ...
INFO: Error injected at 0xffff8ccc.
INFO: Read OCRAM contents ...
INFO: DERR detected : 1.
INFO: Cleaning up ECC OCRAM interrupts.
INFO: ECC OCRAM Demo succeeded.

INFO: ECC QSPI Demo started.
INFO: Initializing QSPI.
INFO: Enabling QSPI.
INFO: Initialize and start ECC for QSPI.
INFO: Inject SERR into QSPI SRAM.
INFO: Write to subsector 0x03b5f600.
INFO: Read subsector 0x03b5f600.
INFO: SERR detected : 0.
INFO: Inject DERR into QSPI SRAM.
INFO: Write to subsector 0x03b5f600.
INFO: Read subsector 0x03b5f600.
INFO: DERR detected : 0.
INFO: Cleaning up QSPI ECC interrupts.
INFO: ECC QSPI Demo succeeded.

INFO: ECC SDMMC Demo started.
INFO: Initializing SDMMC...
INFO: Clearing SDMMC FIFO...
INFO: Initialize and start ECC for SDMMC.
INFO: Inject SERR into SDMMC FIFO.
INFO: Write to SDMMC FIFO.
ISR : Count over 20. Disabling interrupt.
INFO: ECC DMA Demo started.
INFO: Initializing DMA.
INFO: Allocate DMA channel ...
INFO: Initialize and start ECC for DMA.
INFO: Inject SERR into DMA MFIFO.
INFO: Write to DMA MFIFO.
INFO: Read from DMA MFIFO.
INFO: SERR detected : 1.
INFO: Inject DERR into DMA MFIFO.
INFO: Write to DMA MFIFO.
INFO: Read from DMA MFIFO.
INFO: DERR detected : 1.
INFO: Cleaning up DMA ECC interrupts.
INFO: ECC DMA Demo succeeded.

INFO: Enable MMU page tables.
INFO: buffer  at 0x141000, size = 0x100000.
INFO: scratch at 0x243000, size = 0x18000.
INFO: Initialize L2 cache ...
INFO: Initialize and start ECC for L2.
INFO: Cached buffer IO test starts ...
INFO: Writing to cached buffer ...
INFO: Verifying cached buffer ...
INFO: Writing to cached buffer ...
INFO: Verifying cached buffer ...
INFO: Writing to cached buffer ...
INFO: Verifying cached buffer ...
INFO: Cached buffer IO test pass.
INFO: Inject SERR into L2 Data RAM.
INFO: SERR detected : 1.
INFO: Inject DERR into L2 Data RAM.
INFO: DERR detected : 6.
INFO: Cleaning up L2 ECC interrupts.
INFO: ECC L2 Demo succeeded.

INFO: System shutdown.

RESULT: All tests successful.
