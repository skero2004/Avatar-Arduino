# Avatar-Arduino
## What is Project Avatar?
Project Avatar is a telepresence robot that we, FRC Team 568, have developed for our virtual members. Because there is only one FRC team in the state of Alaska, we have virtual members from over 100 miles away who join our weekly meetings through Zoom. Project Avatar is a robot that can be controlled from anywhere in the world to increase the interactivity between our virtual and in-person members.
## About this repository
This repository features arduino code that is responsible for controlling the various motors on the robot. The arduino is connected to a raspberry pi which runs a flask webserver and retreives data about how the robot should move from a web application (see the Avatar repository). This data is then sent using Serial communication which the arduino receives. Depending on the message sent from the pi, the Arduino performs different tasks.
