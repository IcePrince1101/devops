#!/bin/bash

ram_total=$(free -t -m | grep Total | awk '{print $2}')
ram_used=$(free -t -m | grep Total | awk '{print $3}')
ram_free=$(free -t -m | grep Total | awk '{print $4}')

space_root=$(df -m | grep /dev | awk '{print $2}')
space_root_used=$(df -m | grep /dev | awk '{print $3}')
space_root_free=$(df -m | grep /dev | awk '{print $4}')

echo "HOSTNAME = "$(hostname)
echo "TIMEZONE = "$(timedatectl | grep zone | awk '{s=""; for (i=3; i<=NF; i++) s = s $i " "; print s}')
echo "USER = "$(whoami)
echo "OS = "$(uname -s)
echo "DATE = "$(date +"%d %b %Y %H:%M:%S")
echo "UPTIME = "$(uptime -p)
echo "UPTIME_SEC = "$(awk '{print $1}' /proc/uptime)
echo "IP = "$(hostname -I)
echo "MASK = "$(ifconfig | grep -w "netmask" | awk '{print $4}')
echo "GATEWAY = "$(ip r | grep default | awk '{print $3}')

echo "RAM_TOTAL = "$(bash convert_mb_gb.sh $ram_total)
echo "RAM_USED = "$(bash convert_mb_gb.sh $ram_used)
echo "RAM_FREE = "$(bash convert_mb_gb.sh $ram_free)

echo "SPACE_ROOT = "$(bash convert_kb_mb.sh $space_root)
echo "SPACE_ROOT_USED = "$(bash convert_kb_mb.sh $space_root_used)
echo "SPACE_ROOT_FREE = "$(bash convert_kb_mb.sh $space_root_free)