#!/bin/bash
udevadm info /dev/video0 | grep ID_PATH_TAG | cut -d\= -f 2
