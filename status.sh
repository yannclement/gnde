#!/bin/sh

# get battery status
BAT_STATUS="$(cat /sys/class/power_supply/ac/online)"

# get battery level
BAT_PERCENT="$(cat /sys/class/power_supply/battery/capacity)"

# set a text for battery level and status
if [ $BAT_STATUS = 1 ]; then
  BATTERY="🔌 $BAT_PERCENT%"
else
  BATTERY="🔋 $BAT_PERCENT%"
fi

# get WLAN status
WLAN_IP="$(ip -4 addr show wlan0 | grep -oP '(?<=inet\s)\d+(\.\d+){3}')"

# set a text for WLAN status
if [ -z $WLAN_IP ]; then
  WLAN="No 🖧"
else
  WLAN="🖧"
fi

# get the audio volume
VOLUME="$(amixer get Master | tail -n1 | sed -r 's/.*\[(.*)%\].*/\1/')"

# get the time
TIME="$(date '+%k:%M')"

# print the status
echo " $WLAN | $BATTERY | 🎜 $VOLUME% | $TIME "

# wait 5 seconds
sleep 5
