#!/bin/sh

# set DPI screeen to 250, 403 if the real DPI of the Gemini screen
xrandr --dpi 250

# set backlight to 0 > 91 > 255
./backlight.sh 91

# set audio volume to 50%
amixer -q sset 'Master' 50%

# set a blanck screen with a timeout of 5 minutes
xset s blank
xset s 300

# set the wallpaper
feh --randomize --bg-fill ~/Pictures/wallpapers/*
