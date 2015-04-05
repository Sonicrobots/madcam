A multi USB webcam projection approach with open frameworks.
=====
![http://sonicrobots.com/2015/04/01/a-multi-usb-webcam-approach-with-open-frameworks/](http://i.imgur.com/XDPpcQx.jpg)
#
Karsten Gebbert https://github.com/krgn
Moritz Simon Geist 
[https://youtu.be/nk4oQDKUXEw] (Video Link)
#Overview
'Madcam' is an open frameworks (http://www.openframeworks.cc) project for using multiple USB web cams (e.g. PS3 Eye) simultaneously for displaying live video material. Its controllable by MIDI and OSC! We wrote it as a Live VJ extension for the robotics media art installation project "Glitchrobot" by SonicRobots.
#Description
The goal is set up an VJ setup which is based on live webcam material. One webcam? - Boring! 10 Webcams? - "Unlimited" fun! So far we use 10 Web cams, but the amount can probably extended. The webcam content is displayed on one screen, in different tilings and with Video-FX. Tiling and FX can be controlled by Midi and OSC. The system uses Open Frameworks.
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
#Shader FX
  - "Billboard"   - https://www.shadertoy.com/view/Xlf3RS
  - "Pixelate"    - https://www.shadertoy.com/view/MslXRl#
  - "Comic Print" - https://www.shadertoy.com/view/lsBXzV
  - "TV Signal"   - https://www.shadertoy.com/view/MdjSRy
  - "ASCII ART"   - https://www.shadertoy.com/view/4ll3RB
  - "Glitch"      - https://www.shadertoy.com/view/MdXGWn
  - "VHS Style"   - https://www.shadertoy.com/view/4ss3RX
  - "Filters"     - https://www.shadertoy.com/view/XsX3z8
  

