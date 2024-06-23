#!/bin/bash

scp s21_* camillec@192.168.100.11:/usr/local/bin

ssh camillec@192.168.100.11 ls -lah /usr/local/bin 