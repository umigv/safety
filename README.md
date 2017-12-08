# safety
Code and possibly other files related to the 5 mph speed limit and wireless E-Stop microcontroller

# Introduction
For the 2018 IGVC competition, as well as for all of the IGVC competitions before it, all vehicles are required to have three main safety features: A wired emergency stop in the form of a big red button on the robot, a wireless emergency stop in the form of a remote control that can be given to the judges, and a way of controlling the robot to have a maximum speed of 5 mph that isn't a part of the robot's main code. This ensures that no matter what sort of software bug may arise, the robot will not pose a danger.
To implement the wireless E-Stop and the speed limit, we are allowed to use a separate, dedicated microcontroller. This microcontroller will most likely end up being an Arduino or other comprehensive platform due to ease of use.

# Contents
This repository currently contains code that we will eventually load onto an Arduino to implement the wireless E-Stop and speed limit. It uses platformio, an open source tool for programming embedded systems, due to a large amount of frustration with connecting to Arduinos from the Arduino IDE. 

# Comments
In order to get permission to upload the Arduino, the following command may be used:

```
$ sudo chmod 777 /dev/ttyACM0
```

If this is successful, the command

```
$ platformio run --target upload
```

Should compile and upload the code. Platformio must be installed; it is relatively simple and laid out on their website.

```
$ python -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/develop/scripts/get-platformio.py)"
cd /path/to/dir/where/is/located/get-platformio.py/script
python get-platformio.py
```
