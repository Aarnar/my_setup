#!/bin/sh
img_name=$(date +'%d_%m_%R')
import /home/aarnar/Templates/$img_name.png && notify-send "snippet captured"
