//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
        {"",        "date | awk '{print $4,$5}'",                   1,         0,     },      
        {"",        "date | awk '{print $1,$2,$3,$7}'",             1,         0,     },
	{"",        "cat /proc/loadavg | awk '{print $1,$2,$3}'",   1,         0,     },
	{"",        "~/Builds/dwmblocks/scripts/brightness.sh",     0,        10,     },
	{"",        "~/Builds/dwmblocks/scripts/volume.sh",         0,        10,     },
        {"",        "~/Builds/dwmblocks/scripts/battery.sh",        1,         0,     },	
        
	



};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim = '|';
