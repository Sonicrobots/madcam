Many web cams mixed in realtime - on the cheap!
=====
![http://sonicrobots.com/2015/04/01/a-multi-usb-webcam-approach-with-open-frameworks/](http://i.imgur.com/XDPpcQx.jpg)
#
Video Test https://youtu.be/nk4oQDKUXEw

Video of Performance https://youtu.be/kqoPPkRODSE

Programmed by https://github.com/krgn

#Overview
‘Madcam‘ is an open frameworks (C++) based project for mixing USB Web Cameras (e.g. the 10$ cheap USB - PS3-Eye Webcam) im realtime. Why this is awesome? Its usually hard and/or expensive to mix many video signals in realtime and display them side by side. We found a way to make it cheap, quick and reliable!
The project is a visual extension for another  project called “Glitchrobot” where robots are used to make electronic music, but thats another issue. Lets start!
#Description
The goal is set up an VJ setup which is based on live webcam material. One webcam? – Boring! 10 Webcams? – “Unlimited” fun!

So far we use 10 web cams, but the amount can probably be extended. The webcam content is mixed onto one screen, in different tilings and with Video-FX, all in realtime. Tiling and FX can be controlled by Midi and OSC. The system uses Open Frameworks. The allover costs were under 400€ (500$), with the main part being the computer.

![](http://sonicrobots.com/wp-content/uploads/2015/03/IMG_3450-1024x576.jpg)
#HARDWARE
The main problem is to get a constant stream of video data into the computer. The bottleneck here is the USB Host controller. One USB Host can theoretically take up to 127 client, but we found out only 1-2 Cameras per host controller (PCI / PICe card) work without glitches and missing frames.
In the current setup, one host controller can take data from 2 Webcams running at 480×600 resolution at 30FPS. PCI can process less data then PCIExpress, so it is best to build your system on PCIe cards.

For the system a standard CPU is sufficient. We used an AMD 6 Core, 4GB Ram, SSD 128GB.
and Xubuntu as a base system and a WRT Router for the OSC Network.
#Features
- OpenGL shaders for filters and FX
- UVC Video Compatible (Linux Video driver) e.g. the very cheap and high frame rate USB Webcams "PS3 Eye"
- Different tilings: One cam full screen, 2-9 Cams tilings.
- Decay Video Filter: Apply an OpenGL Shader to create an "fade out" effect on a single cam image, whenever a certain Midi Note is triggered
- Midi and OSC Controls
  - Control and switch the tilings with midi notes!
  - Control the cam assignment with MIDI CC commands
  - Control the Decay time OSC
  - Control everything with TouchOSC
-  Tested for PS3 Eye Cams running 640x480, 30 Fps

# Requirements 
The setup we build consists of the following parts, but may be build from different hard/ software as well. As the amount of data of several USB Webcam is considerably big, care has to be taken when choosing the USB controllers.

## Hardware
- System: standard CPU is sufficient. We used an AMD 6 Core, 4GB Ram, SSD 128GB.
- USB: One MIDI Host controller (USB chain) can take data from 2 Webcams (PS 3Eye) running at 480x600 resolution at 30FPS. PCI can process less data then PCIExpress, so it is best to build your system on PCIe cards. 
- We added PCIe USB cards so that one USB Host controller is in charge of 2 webcams. There are also expensice USB-PCI cards out there which have one Hostcontroller for every USB-chain
- We used Xubuntu as a base system and a WRT Router for the OSC Network

# LINKS
- Project Homepage (http://sonicrobots.com/2015/04/01/a-multi-usb-webcam-approach-with-open-frameworks/)
- Glitch Robot Installation (http://sonicrobots.com/glitch-robot/)
- Open Frameworks (http://openframeworks.cc)
