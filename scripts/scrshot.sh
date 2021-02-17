#!/bin/sh
img_name=$(date +'%d_%m_%R')
import -window root /home/aarnar/Templates/$img_name.png && notify-send "screenshot captured"

