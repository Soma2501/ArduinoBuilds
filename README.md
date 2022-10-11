# ArduinoBuilds

SerialArmController: 3 Button Input 
- Inputs:   CW, CCW, Change Motor Buttons
- Outputs:  Moves motor, displays motor # and respective motor angle in LCD
- Features: Limits for resepctive Motor ROM implemented in code
- Note:     Motors cannot be driven simultaneously as only 1 motor object with  
	    4 elements in the array representing each motor 

SerialArmController2: Remote IP Motor Control Panel 
- Inputs:   CW/CCW Buttons per Motor (8)
- Outputs:  
- Features: ()
- Note:     Enables simultaneous control with control panel GUI inputs through 
	    remote IP connection with ESP8266 wifi module

SerialArmController3: Remote IP XYZ Motor Control Panel 
- Features: Inverse Kinematics

Feature Ideas
- Implement ROS2 and simulate with Gazebo(physics)/rviz(no physics)
  - Gazebo requires Ubuntu
- Control System to reduce motion error
