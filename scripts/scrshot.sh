#!/bin/sh
img_name=$(date +'%d_%m_%R')
import -window root ~/Templates/$img_name.png && notify-send "screenshot captured"

