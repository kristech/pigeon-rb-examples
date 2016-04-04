#!/usr/bin/python

from sys import stdout
from time import sleep

id = "28.06D63C020000"

while True:

    try:
        temp = open("/mnt/1wire/" + id + "/temperature", "r")
        t_raw = temp.read()
        temp.close()

        t = float(t_raw)
        print(('T = %.2f\n') % t),
        stdout.flush()
        sleep(1)

    except KeyboardInterrupt:
        break