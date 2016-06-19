Introduction

This HardwareLibs project is meant as an example for using the Timer APIs.

The project demonstrates the following Timer API features:
-  General Purpose Free-running Timer
-  General Purpose One-shot Timer
-  Global Timer Measurements
-  Watchdog Timer Features

The project also demonstrates the following additional API features:
- Setting up interrupts

Note: This example was tested against SoC EDS 16.0b211.

====

Target Boards:
- Altera Cyclone V SoC Development Board rev E.

====

Limitations:

None  

=====

Source Files

The following are descriptions of the source and header files contained in this
project:

timers_demo.c - contains all timer routines

  
=====

Building Example

Before running the example, the target executable first needs to be built.

1. In DS-5, build the application:
  1a. Switch to the C/C++ Perspective if not already in that perspective by
      selecting the menu: Window >> Open Perspective >> C/C++.
  1b. In the "Project Explorer" panel, right-mouse-click 
      "Altera-SoCFPGA-HardwareLib-Timers-CV-GNU" and select "Build Project".

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
      "Altera-SoCFPGA-HardwareLib-Timers-CV-GNU".
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
      "Altera-SoCFPGA-HardwareLib-Timers-CV-GNU" and select
      "Connect to Target".

Connecting to the target takes a moment to load the preloader, run the
preloader, load the executable, and run executable. After the debug connection
is established, the debugger will pause the execution at the main() function.
Users can then set additional break points, step into, step out of, or step one
line using the DS-5 debugger. Consult documentation for DS-5 for more
information on debugging operations.

=====

Sample output

The following is a sample output:


INFO: System Initialization.
INFO: Setting up Global Timer.
INFO: Initializing General Purpose Timers.
INFO: Initializing Watchdog 0 Timer.

INFO: Interrupt Setup.

INFO: OSC 1 Timer 0 Free-run Demo.
INFO: Setting OSC1 Timer0 mode.
INFO: Setting OSC1 Timer0 restart count value.
INFO: Starting OSC1 Timer0.
INFO: Checking if OSC1 Timer0 is running.
INFO: OSC1 Timer0 is running.
INFO: OSC1 Timer0 running at 381Hz.
INFO: OSC1 Timer0 Period in seconds is 0.
INFO: OSC1 Timer0 Period in milliseconds is 2.
INFO: OSC1 Timer0 Period in microseconds is 2621.
INFO: OSC1 Timer0 Time to zero in seconds is 0.
INFO: OSC1 Timer0 Time to zero in milliseconds is 1.
INFO: OSC1 Timer0 Time to zero in microseconds is 887.
INFO: OSC1 Timer0 Max time in seconds is 171.
INFO: OSC1 Timer0 Max time in milliseconds is 171798.

INFO: SP Timer 1 One-shot Demo.
INFO: Setting SP Timer 1 mode.
INFO: Setting SP Timer 1 count value.
INFO: Enabling SP Timer1 Interrupt.
INFO: Starting SP Timer1.
INFO: Checking if SP Timer 1 is running.
INFO: SP Timer 1 is running.
INFO: Waiting for SP Timer1 Interrupt.
INFO: SP Timer1 Interrupt Fired.

INFO: Global Timer Demo.
INFO: Starting Global Timer.
INFO: Measuring for loop time.
INFO: For loop time elapsed = 34271.
INFO: Setting Global Timer Comparator.
INFO: Enabling Global Timer Interrupts.
INFO: Global Timer Interrupt Deltas.
INFO: Global Timer Comparator Interrupt Delta 1 = 31991.
INFO: Global Timer Comparator Interrupt Delta 2 = 31941.
INFO: Global Timer Comparator Interrupt Delta 3 = 31991.
INFO: Global Timer Comparator Interrupt Delta 4 = 32048.
INFO: Global Timer Comparator Interrupt Delta 5 = 31947.
INFO: Global Timer Comparator Interrupt Delta 6 = 31997.
INFO: Global Timer Comparator Interrupt Delta 7 = 32020.
INFO: Global Timer Comparator Interrupt Delta 8 = 32046.
INFO: Global Timer Comparator Interrupt Delta 9 = 31945.

INFO: CPU0 Watch Dog Demo.
INFO: Setting CPU0 Watchdog mode to Interrupt then Reset.
INFO: Setting CPU0 Watchdog Counter Initial Value.
INFO: Setting CPU0 Watchdog Counter Reset Value.
INFO: Starting Watchdog 0 Timer.
INFO: Watchdog 0 Timer is running.
INFO: Watchdog 0 Initial time = 5 millisecs.
INFO: Watchdog 0 Current time = 5 millisecs.
INFO: Watchdog 0 count = 88155.
INFO: Watchdog 0 count after reset= 131047.
INFO: Watchdog 0 Reset.
INFO: Waiting for Watchdog 0 Interrupt.
INFO: Watchdog 0 Interrupt Fired.
INFO: Stopping Watchdog 0 Timer.

INFO: Cleaning up Timer interrupts.

INFO: Shutting Down System.

RESULT: All tests successful.
