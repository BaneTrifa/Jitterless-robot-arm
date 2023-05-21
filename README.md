# Jitterless-robot-arm
Students project from the course "Computer System Design"
## About project
The goal of this project was to solve the problem of jitter on the robotic arm that occurs when connect the sg90 micro servo motors directly to the Raspberry Pi 2 that generates the software PWM. 
The problem was solved with the help of an Arduino Uno, which was placed as an intermediary between the RPI2 and the micro servo motor. 
The idea is: Arduino Uno measure the PWM signals coming from the RPI2, map the PWM values to the values of the angles, and then use the Servo library to pass those angles to the motors.
## Connecting RPI2, Arduino Uno and SG90 motors
	--------------------------------
	| RPI2 pins | Arduino Uno pins |
	|-----------|------------------|
	|	38      |        7         |
	|-----------|------------------|
	|	40		|        8         |
	|-----------|------------------|
	|	15		|        9         |
	|-----------|------------------|
	|	16		|        10        |
	|-----------|------------------|
	|  6(GND)	|        GND       |
	--------------------------------
  
Connect SG90 servos on following Arduino Uno pins: 3, 5, 6, 11