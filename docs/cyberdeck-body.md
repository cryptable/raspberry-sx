Cyber-deck
==========

Introduction
------------

We build a cyberdeck which is modifiable for other to extend. It is designed using a casco, which can be extended using other material.
The casco is designed to be waterproof (rainproof), maybe submergable proof.
It is all 3D printed, but the casco can also industrialised be build. You will a 3D printer with a bed 300x300 and a height 400. 

Casco
-----

The design of casco is done in FreeCAD and found in the .\design-folder. It exists out of a front panel containing the keyboard, a body with a front plate and back plate and a backpanel to store the power cable.

The frontpanel contains the Raspberry Pi, Screen, SSD and USB hub. It also has a place to store a mouse or other things.
The backpanel has the connector for ethernet, a cooler and the connector of the powersupply.

Mainboard and Screen
--------------------
- Raspberry Pi4 8Gb
- Wisecoco 5.5 inch FullHD screen
- Ice Tower

The Rapsberry Pi4 8Gb memory in attached to the Wisecoco 5.5 inch FullHD screen with ontop the Ice Tower. You can reuse all the screws and bolds of the Ice Tower and the Wisecoco screen to attach teh Raspi. You will need to shorten the small screws of the Ice Tower to fin into screws of the Wise coco.

You attach the HDMI connection from the screen to the Raspi, but you don't use the touch screen connection, because we will not sacrifice a USB 3.0 port just for a touch screen. We use a small USB-A to micro USB cable (10cm) to make the connection. We need the USB 3.0 ports for the USB 3.0 SSD and USB hub.

Keyboard
--------

see [keyboard](./cyberdeck-keyboard.md)

Power for cyberdeck
-------------------

Power is delivered by a powerbank supporting USB-PD and able to deliver 30W. The USB-C is used to power the Raspberry Pi with its periferals. This is charged by 70W power supply, which means you can use the powersupply for other usages. The 5V of the powersupply is connected to the micro-USB of the powerbank to charge the powerbank.

References
- MEAN WELL Well 1439455 LRS-75-5 AC Power Supply Block Closed 14A 70W 5 V/DC
- Poweradd Energycell II Powerbank PD 30 W, 26800 mAh Power Bank with Power Delivery

Power on and off
----------------

### Naive implementation

The first try was to powering on and off through a switch, which will shutdown the raspberry Pi. But I couldn't start it again. Also the active cooler on the CPU stayed running, proving the raspberry Pi was still drawing power of the powerbank.

### Second try

I build a latched controlled by a Raspberry Pico (with a small 0.96" displayed attached to it) using a MOSFET to switch on the Raspberry Pi and switch it the powerbank off after a shutdown of the Raspberry Pi.
Due to the voltage drop over the MOSFET, because the Pi with the periferals draws a substantial current, I didn't have enough voltage left to run the Raspberry Pi.

### Third solution

I use a USB-PD supported voltage requestor (DollaTek), which can be set to higher voltage, like 12V. In between comes the latch with the micro-controller and after the latch will a buck converter which will output 5V and power the Raspberry Pi.

### Fourth solution

The micro-controller controls a latching relay.

### References:
- https://www.embeddedcomputing.com/technology/open-source/development-kits/raspberry-pi-power-up-and-shutdown-with-a-physical-button
- DollaTek Snellaadtrigger PD/QC/AFC - ondersteunt vaste spanning 5V 9V 12V 15V 20V van USB-C
- Hailege XL4015 DC-DC Buck Converter Step Down Module 4 ~ 38 V op 1,25 – 36 V 5 A DC-DC verstelbare step-down module XL4015 4 ~ 38 V 96%
- Latching Relay FeatherWing

Lids of Cyberdesk with locks
----------------------------

The lids of the cyberdeck a locked using stainless steel levers.

reference:

- Miuse ZS0307-1 Toggle Latch, Stainless Steel Lever, Lock Cap, Lock for Case Box, Toolbox, Drawer, Cabinet, Chest, Pack of 8
- https://www.thingiverse.com/thing:4094861
- https://www.thingiverse.com/thing:5222235


Mouse case lid idea
-------------------

https://www.thingiverse.com/thing:2609754