#!/bin/sh
brightness=$(xbacklight -get | awk -F. '{print $1}')
echo "🔆 $brightness"

