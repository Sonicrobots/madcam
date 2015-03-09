MadCam
An simultaneous multi webcam approach to open frameworks. 
======
# Overview
Madcam is an open frameworks (http://www.openframeworks.cc) project for using multiple USB web cams (e.g. PS3 Eye) simultaneously for displaying live video material provided by web cams. Its controllable by MIDI!
We wrote it as a Live Vj extension for the robotics media art installation project "Glitchrobot" by SonicRobots.
# Description
The goal is set up an VJ setup which is based on webcam material. So far we used 9-10 Web cams, but the amount can probably extended. The webcam content is displayed  n one screen, in different tilings. Tiling and FX can be 
controlled by Midi. The system uses the Open Frameworks project.
# Features
- Open Frameworks
- OpenGL shaders for filters and FX
- UVC Video Compatible (Linux Video driver) e.g. the very cheap and high frame rate USB Webcams "PS3 Eye"
- Different tilings: One cam full screen, 2-9 Cams tiling. 
- Decay Filter: Apply an OpenGL Shader to create an "fade out" effect on a single cam image, whenever a certain Midi Note is triggered
- Midi Controls
  - Control and switch the tilings with midi notes!
  - Control the cam assignment with MIDI CC commands
  - Control the Decay time
- OSC
# Requirements
The setup we build the system upon consists of the following parts, but may be build from diffrent hard/ software as well. As the Amount of data of several USB Webcam is considerably big, care has to be taken.
## Hardware
- CPU: standard CPU is sufficient. We used Amd 6 Core
======

- Scaling modes
  - scale to fit
  - crop to fit

- Composition modes
  - Tiling
  - Single
  - Dual, horiz split
  - Triple, horiz split

- Shader FX
  - "Billboard"   - https://www.shadertoy.com/view/Xlf3RS
  - "Pixelate"    - https://www.shadertoy.com/view/MslXRl#
  - "Comic Print" - https://www.shadertoy.com/view/lsBXzV
  - "TV Signal"   - https://www.shadertoy.com/view/MdjSRy
  - "ASCII ART"   - https://www.shadertoy.com/view/4ll3RB
  - "Glitch"      - https://www.shadertoy.com/view/MdXGWn
  - "VHS Style"   - https://www.shadertoy.com/view/4ss3RX
  - "Filters"     - https://www.shadertoy.com/view/XsX3z8

  
