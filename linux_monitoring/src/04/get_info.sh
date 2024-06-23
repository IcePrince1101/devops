#!/bin/bash

ram_total=$(free -t -m | grep Total | awk '{print $2}')
ram_used=$(free -t -m | grep Total | awk '{print $3}')
ram_free=$(free -t -m | grep Total | awk '{print $4}')

space_root=$(df -m | grep /dev | awk '{print $2}')
space_root_used=$(df -m | grep /dev | awk '{print $3}')
space_root_free=$(df -m | grep /dev | awk '{print $4}')


bash colors.sh $1 $2 $3 $4 "HOSTNAME" $(hostname)
bash colors.sh $1 $2 $3 $4 "TIMEZONE" $(timedatectl | grep zone | awk '{s=""; for (i=3; i<=NF; i++) s = s $i " "; print s}')
bash colors.sh $1 $2 $3 $4 "USER" $(whoami)
bash colors.sh $1 $2 $3 $4 "OS" $(uname -s)
bash colors.sh $1 $2 $3 $4 "DATE" $(date +"%d %b %Y %H:%M:%S")
bash colors.sh $1 $2 $3 $4 "UPTIME" $(uptime -p)
bash colors.sh $1 $2 $3 $4 "UPTIME_SEC" $(awk '{print $1}' /proc/uptime)
bash colors.sh $1 $2 $3 $4 "IP" $(hostname -I)
bash colors.sh $1 $2 $3 $4 "MASK" $(ifconfig | grep -w "netmask" | awk '{print $4}')
bash colors.sh $1 $2 $3 $4 "GATEWAY" $(ip r | grep default | awk '{print $3}')


chmod 777 convert_mb_gb.sh convert_kb_mb.sh
bash colors.sh $1 $2 $3 $4 "RAM_TOTAL" $(bash convert_mb_gb.sh $ram_total)
bash colors.sh $1 $2 $3 $4 "RAM_USED" $(bash convert_mb_gb.sh $ram_used)
bash colors.sh $1 $2 $3 $4 "RAM_FREE" $(bash convert_mb_gb.sh $ram_free)

bash colors.sh $1 $2 $3 $4 "SPACE_ROOT" $(bash convert_kb_mb.sh $space_root)
bash colors.sh $1 $2 $3 $4 "SPACE_ROOT_USED" $(bash convert_kb_mb.sh $space_root_used)
bash colors.sh $1 $2 $3 $4 "SPACE_ROOT_FREE" $(bash convert_kb_mb.sh $space_root_free) 