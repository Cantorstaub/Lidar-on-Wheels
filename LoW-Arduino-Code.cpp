#include <Servo.h>

/**
* https://github.com/Cantorstaub/Lidar-on-Wheels
*
* version 1.1
*
* This is code for the Arduino of the Lidar on Wheels robot built at the
* Virtual Humanities Lab at the Ruhr-University Bochum.
*
* We did not write this code ourselves but retrieved it from
* @author Addison Sears-Collins
* @version 1.0 2019-05-13
* All the credit goes to Sears-Collins and his instructive tutorials.
*
* As we encountered technical issues (not related to the tutorials we used),
* we had to make some changes to the way the data of the ultrasonic sensor
* is processed. Some minor changes were necessary to adapt the movements of
* the robot to the sensitivity of the LiDAR sensor. To make our robot move
* more smoothly and avoid disturbing the LiDAR measurements, we added two
* new functions: void brake_forward_smoothly() and void backwards_start_smoothly().
* Our changes to the code are marked with the abbreviations TN or AS. All
* changes made by Thomas Nyckel and Alex Wynne Schmiedel.
*
* Note: This code was not checked for functionality after revising its
* commentary for GitHub.
* 
* Important: This code is designed in regard to the material specifications of
* our robot. This means, the values for the servo-motors are set to compensate
* for the fact that these servo-motors are not perfectly calibrated. If you use
* this code on another robot, this might result in deviating movements.
*/

/**
* This robot avoids obstacles
* using an ultrasonic sensor.
*
* @author Addison Sears-Collins
* @version 1.0 2019-05-13
*/

// Create two servo objects, one for each wheel
Servo right_servo;
Servo left_servo;

// Variables we added to use in the functions we addded to go more smoothly (TN)
int speed_right_servo = 93;
int speed_left_servo = 93;

/* Give a name to a constant value before
* the program is compiled. The compiler will
* replace references to Trigger and Echo with
* 7 and 8, respectively, at compile time.
* These defined constants don't take up
* memory space on the Arduino.
*/

#define Trigger 7
#define Echo 8

/*
* This setup code is run only once, when
* Arduino is supplied with power.
*/

void setup(){
// Set the baud rate to 9600. 9600 means that
// the serial port is capable of transferring
// a maximum of 9600 bits per second.
Serial.begin(9600);
right_servo.attach(9); // Right servo to pin 9
left_servo.attach(10); // Left servo to pin 10

// Define each pin as an input or output.
pinMode(Echo, INPUT);
pinMode(Trigger, OUTPUT);

// Initializes the pseudo-random number generator
// Needed for the robot to wander around the room
randomSeed(analogRead(3));
delay(200); // Pause 200 milliseconds
go_forward(); // Go forward
}

/*
* This is the main code that runs again and again while
* the Arduino is connected to power.
*/

void loop(){
int distance = doPing();

// If obstacle <= 2 inches away
if (distance >= 0 && distance <= 2) {
Serial.println("Obstacle detected ahead");
brake_forward_smoothly(); // Calling this function to brake smoothly (TN)
stop_all(); // Calling this function to generate some delay to make the robot change directions smoother not to disturb Lidar (TN)
delay(100); // Adding some delay (TN)
backwards_start_smoothly(); // Additional function call to render the robot's start when going to move backwards more smoothely.
go_backwards(); // Move in reverse for 0.5 seconds
delay(5333); // We increased this value from 500 up to 1500 (TN, AS)
stop_all();
delay(300);

/* Go left or right to avoid the obstacle*/
if (random(2) == 0) { // Generates 0 or 1, randomly
go_right(); // Turn right for one second
}
else {
go_left(); // Turn left for one second
}
delay(17000); // changed this from 1000 as the speed for turning was reduced (TN); before speed was reduced to +-1 I used 2678 ms here
go_forward(); // Move forward
}
delay(50); // Wait 50 milliseconds before pinging again
}

/*
* Returns the distance to the obstacle as an integer
*/
int doPing () {
int distance = 0;
int average = 0;

// Grab four measurements of distance and calculate
// the average.
for (int i = 0; i < 1; i++) { // changed from 4 to 1 measurement due to technical issues with the 4 measurements (TN and AS)

// Make the Trigger LOW (0 volts)
// for 2 microseconds
digitalWrite(Trigger, LOW);
delayMicroseconds(2);

// Emit high frequency 40kHz sound pulse
// (i.e. pull the Trigger)
// by making Trigger HIGH (5 volts)
// for 10 microseconds
digitalWrite(Trigger, HIGH);
delayMicroseconds(10);
digitalWrite(Trigger, LOW);

// Detect a pulse on the Echo pin 8.
// pulseIn() measures the time in
// microseconds until the sound pulse
// returns back to the sensor.
distance = pulseIn(Echo, HIGH);

// Speed of sound is:
// 13511.811023622 inches per second
// 13511.811023622/10^6 inches per microsecond
// 0.013511811 inches per microsecond
// Taking the reciprocal, we have:
// 74.00932414 microseconds per inch
// Below, we convert microseconds to inches by
// dividing by 74 and then dividing by 2
// to account for the roundtrip time.
distance = distance / 74 / 2;

// Compute running sum
average += distance;

// Wait 10 milliseconds between pings
delay(10);
}

// Return the average of the four distance
// measurements
return (average / 1); // changed from 4 to 1 measurement due to technical issues with the 4 measurements (TN and AS)
}

/*
* Forwards, backwards, right, left, stop, going smoother.
*/

void go_forward() {
right_servo.write(91);
left_servo.write(95);
}

void go_backwards() {
right_servo.write(95);
left_servo.write(91);
}

void go_right() {
right_servo.write(94);
left_servo.write(94);
}

void go_left() {
right_servo.write(92);
left_servo.write(92);
}

void stop_all() {
right_servo.write(93);
left_servo.write(93);
}

// The two functions we added for smoother movements to not disturb the measurements with LiDAR:

void brake_forward_smoothly() { // function to render the stopping of the robot smoother to not shake the LiDAR sensor (TN)
for (int i = 1; i > 0; i--){ // for loop to create int i that can be added and subtracted from the speed of the servos
	speed_right_servo = 93 - i;
	speed_left_servo = 93 + i;
	right_servo.write(speed_right_servo);
	left_servo.write(speed_left_servo);
	delay(27); // This should be 27, I change it sometimes for testing (TN)
	}
}

void backwards_start_smoothly() { // function to render the beginning of backwards movements smoother to not shake the LiDAR sensor (TN)
for (int i = 1; i < 2; i++){ // for loop to create int i that can be added and subtracted from the speed of the servos
	speed_right_servo = 93 + i;
	speed_left_servo = 93 - i;
	right_servo.write(speed_right_servo);
	left_servo.write(speed_left_servo);
	delay(27); // This should be 27, I change it sometimes for testing (TN)
	}
}
