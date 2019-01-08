#!/bin/bash
udevadm info /dev/video0 | grep ID_PATH_TAG | cut -d\= -f 2
udevadm info /dev/video1 | grep ID_PATH_TAG | cut -d\= -f 2
udevadm info /dev/video2 | grep ID_PATH_TAG | cut -d\= -f 2
udevadm info /dev/video3 | grep ID_PATH_TAG | cut -d\= -f 2
udevadm info /dev/video4 | grep ID_PATH_TAG | cut -d\= -f 2
udevadm info /dev/video5 | grep ID_PATH_TAG | cut -d\= -f 2
udevadm info /dev/video6 | grep ID_PATH_TAG | cut -d\= -f 2
udevadm info /dev/video7 | grep ID_PATH_TAG | cut -d\= -f 2