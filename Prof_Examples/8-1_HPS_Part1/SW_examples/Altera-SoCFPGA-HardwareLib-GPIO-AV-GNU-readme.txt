Introduction

This HardwareLibs project is meant as an example for using the GPIO APIs.

The project demonstrates the following GPIO Flash API features:
- Using GPIO as output ports to drive HPS LEDs
- Using GPIO as input ports from HPS Push Buttons

The project also demonstrates the following additional API features:
- Using Global Timer to implement delays
- Using Interrupts

Note: This example was tested against SoC EDS 16.0b211.

====

Target Boards:
- Altera Arria V SoC Development Board rev C.

====

Source Files

The following are descriptions of the source and header files contained in this
project:

gpio_demo.c

  Contain the main, system initialization and cleanup, delay functions, interrupts setup, functions demonstrating GPIO APIs.
  
=====

Building Example

Before running the example, the target executable first needs to be built.

1. In DS-5, build the application:
  1a. Switch to the C/C++ Perspective if not already in that perspective by
      selecting the menu: Window >> Open Perspective >> C/C++.
  1b. In the "Project Explorer" panel, right-mouse-click 
      "Altera-SoCFPGA-HardwareLib-GPIO-AV-GNU" and select "Build Project".

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
      "Altera-SoCFPGA-HardwareLib-GPIO-AV-GNU".
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
      "Altera-SoCFPGA-HardwareLib-GPIO-AV-GNU" and select
      "Connect to Target".

Connecting to the target takes a moment to load the preloader, run the
preloader, load the executable, and run executable. After the debug connection
is established, the debugger will pause the execution at the main() function.
Users can then set additional break points, step into, step out of, or step one
line using the DS-5 debugger. Consult documentation for DS-5 for more
information on debugging operations.

This demo requires user to trigger the interrupts via HPS Push Buttons to drive
the HPS LEDs.
Press HPS Push Button 0: All HPS LEDs blink
Press HPS Push Button 1: HPS LEDs scroll right
Press HPS Push Button 2: HPS LEDs scroll left
Press HPS Push Button 3: HPS LEDs turn off

=====

Sample output

INFO: System Initialization.
INFO: Init GPIO module.
INFO: Setting up GPIO interrupt.
INFO: Set up GPIO for LEDs.
INFO: Set up GPIO for Push button.
INFO: Register interrupt handler.
INFO: Press HPS_PB_USER_0: HPS LEDs blink.
INFO: Press HPS_PB_USER_1: HPS LEDs scroll right.
INFO: Press HPS_PB_USER_2: HPS LEDs scroll left.
INFO: Press HPS_PB_USER_3: HPS LEDs turn off and exit demo.
INFO: HPS_PB_USER_0 was pushed.
INFO: HPS_PB_USER_1 was pushed.
INFO: HPS_PB_USER_2 was pushed.
INFO: HPS_PB_USER_3 was pushed.
INFO: System uninit.
INFO: Cleaning up GPIO interrupt.
INFO: GPIO demo exits.
