#!/bin/sh

#export GPIOs
echo "12" > /sys/class/gpio/export
echo "13" > /sys/class/gpio/export
echo "18" > /sys/class/gpio/export
echo "19" > /sys/class/gpio/export
echo "20" > /sys/class/gpio/export
echo "21" > /sys/class/gpio/export
echo "22" > /sys/class/gpio/export
echo "23" > /sys/class/gpio/export

echo "30" > /sys/class/gpio/export
echo "31" > /sys/class/gpio/export
echo "32" > /sys/class/gpio/export
echo "33" > /sys/class/gpio/export

# Read from inputs
echo "Opto-isolated inputs:"
echo -n "I1 = "
cat /sys/class/gpio/gpio12/value
echo -n "I2 = "
cat /sys/class/gpio/gpio13/value
echo -n "I3 = "
cat /sys/class/gpio/gpio18/value
echo -n "I4 = "
cat /sys/class/gpio/gpio19/value
echo -n "I5 = "
cat /sys/class/gpio/gpio20/value
echo -n "I6 = "
cat /sys/class/gpio/gpio21/value
echo -n "I7 = "
cat /sys/class/gpio/gpio22/value
echo -n "I8 = "
cat /sys/class/gpio/gpio23/value

echo "Dry contact inputs:"
echo -n "ID1 = "
cat /sys/class/gpio/gpio30/value
echo -n "ID2 = "
cat /sys/class/gpio/gpio31/value
echo -n "ID3 = "
cat /sys/class/gpio/gpio32/value
echo -n "ID4 = "
cat /sys/class/gpio/gpio33/value

# unexport GPIOs
echo "12" > /sys/class/gpio/unexport
echo "13" > /sys/class/gpio/unexport
echo "18" > /sys/class/gpio/unexport
echo "19" > /sys/class/gpio/unexport
echo "20" > /sys/class/gpio/unexport
echo "21" > /sys/class/gpio/unexport
echo "22" > /sys/class/gpio/unexport
echo "23" > /sys/class/gpio/unexport

echo "30" > /sys/class/gpio/unexport
echo "31" > /sys/class/gpio/unexport
echo "32" > /sys/class/gpio/unexport
echo "33" > /sys/class/gpio/unexport