# Microcontroller Interface

Open source alternative to the use of LabVIEW and MATLAB for receiving and sending data to microcontrollers attached by a USB port.

## Motivation

When code is being developed to be run on microcontrollers, one of the difficulties faced by the engineer is to see the data that is being read by a sensor or processed by the microcontroller. Sometimes, debug tools like GDB or OpenOCD are not available, so, scanf and printf would be the best alternatives to be used for data input and output from the code.
The Arduino IDE already has a built in "Serial Monitor", but it can only input and output text and numbers on text format, or plot a chart with very limited functionality.

## Description

The functionality is similar to the front panel of a LabVIEW VI, with controls, indicators, charts and graphs used to create a graphical interface for the program that is running on the microcontroller. Data is sent and received from the microcontroller using a Serial Port protocol, usually through a USB attached virtual COM port.