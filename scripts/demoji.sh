#!/bin/sh
cat ~/Path/to/emoji_file | dmenu -p Emoji | awk '{print $1}' |tr -d '\n' |  xclip -sel clip     
emoji=$(xclip -sel clip -o) 
[ -z "$emoji" ] || notify-send "'$emoji' copied to clipboard"

