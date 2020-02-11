#!/bin/bash
PORT="/dev/ttyACM0"
for ((i=1;i<=50;i++)); do
	let "DELAY = 50 * i + 1500"
	echo "DELAY = $DELAY"
	/home/minamo/Downloads/hoge/arduino-1.8.9/hardware/Arduino_STM32-master/tools/linux64/upload-reset $PORT $DELAY
	dfu-util -l

	COUNTER=0
	while [ ! -r $PORT ] && ((COUNTER++ < 40)); do
		sleep 0.1
	done
done
