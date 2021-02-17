#/bin/sh
charge=$(cat /sys/class/power_supply/BAT0/charge_now)
status=$(cat /sys/class/power_supply/BAT0/status)
capacity=`expr $charge / 28000`

case $status in 

    "Charging")  
               echo "⚡ $capacity%" 
               ;;
    "Discharging")
               echo "🔋 $capacity%" 
               ;;
    "Unknown")
               echo "🔌 $capacity%" 

               ;;
    "Full")
               echo "FULL $capacity%" 
               ;;
esac

     




