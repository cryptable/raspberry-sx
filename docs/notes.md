Cyber-deck
==========

Introduction
------------

We build a cyberdeck which is modifiable for other to extend. It is designed using a casco, which can be extended using other material.
The casco is waterproof (rainproof), maybe sebmergable proof.
It is all 3D printed, but the casco can also industrialised be build.

Casco
-----


Mainboard and Screen
--------------------
- Raspberry Pi4 8Gb
- Wisecoco 5.5 inch FullHD screen
- Ice Tower

The Rapsberry Pi4 8Gb memory in attached to the Wisecoco 5.5 inch FullHD screen with ontop the Ice Tower. You can reuse all the screws and bolds of the Ice Tower and the Wisecoco screen to attach teh Raspi. You will need to shorten the small screws of the Ice Tower to fin into screws of the Wise coco.

You attach the HDMI connection from the screen to the Raspi, but you don't use the touch screen connection, because we will not sacrifice a USB 3.0 port just for a touch screen. We use a small USB-A to micro USB cable (10cm) to make the connection. We need the USB 3.0 ports for the USB 3.0 SSD and USB hub.


Keyboard
--------
- JJ50
- QMK

### Compiling


references:
- https://beta.docs.qmk.fm/tutorial/newbs_getting_started

### flashing

```
sudo bootloadHID Downloads/jj50_test_jj50.hex
```

BootloadHID flashing jj50
- https://beta.docs.qmk.fm/using-qmk/guides/flashing/flashing_bootloadhid

references:
- https://beta.docs.qmk.fm/using-qmk/guides/flashing/flashing_bootloadhid


### Testing

#### Switches

The MO (7, 4, 5) switches don't show up in the qmk configurator and tester. So to test the switches we will allocate them to some keys from the keypad (1,2,3).

1) in the config.qmk.fm we select the jj50 and load default.
2) Select the MO 7 and click on '1' of the keypad
3) Select the MO 4 and click on '2' of the keypad
4) Select the MO 5 and click on '3' of the keypad

When flashed you can test the switches after removal en reinserting the keyboard. Take into account the MO keys are mapped to the keypad.
To test the keyboard use the keyboard tester of config.qmk.fm and compare it with the layout. It is simpler you print the layout in one browser and open the tester in another browser.
One by one you short the switch to see the correct key lights up.

Note:
* THIS ONLY FOR TESTING THE KEYBOARD TO SEND IT BACK IN CASE OF PROBLEMS !!! *
You need to reflash it afterwards with the default jj50 or your custom firmware.

#### LEDs

The leds underneat will turn on when flashed.

In bootloader mode all leds flashes. So you can test them one-by-one.
The leds underneat are turned off in bootloader mode.

Power on and off
----------------

References:
- https://www.embeddedcomputing.com/technology/open-source/development-kits/raspberry-pi-power-up-and-shutdown-with-a-physical-button


Lid of Cyberdesk with locks
---------------------------

ref:
https://www.thingiverse.com/thing:4094861

https://www.thingiverse.com/thing:5222235


Mouse case lid idea
-------------------

https://www.thingiverse.com/thing:2609754