#include <Servo.h>

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

// Variables we added to use in the function void backwards_start_smoothly() (TN)
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
* Arudino is supplied with power.
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
brake_forward_smoothly(); // Calling function to brake smoothly (TN)
stop_all(); // Calling this function to generate some delay to make the robot change directions smoother to not disturb Lidar (TN)
delay(100); // Adding some delay (TN)
backwards_start_smoothly(); // Additional function called to make robot's start to move backwards more smoothely.
go_backwards(); // Move in reverse for 0.5 seconds
delay(1500); // WIR ERHÖHEN DIESEN WERT von 500 höher (TN, AS)
stop_all();
delay(300);

/* Go left or right to avoid the obstacle*/
if (random(2) == 0) { // Generates 0 or 1, randomly
go_right(); // Turn right for one second
}
else {
go_left(); // Turn left for one second
}
delay(2678); // changed this from 1000 as the speed for turning was reduced (TN)
go_forward(); // Move forward
}
delay(50); // Wait 50 milliseconds before pinging again
}
// I chose 2678 ms here because that could result in the robot turning about 75°, which is the value I want to test out (TN)

/*
* Returns the distance to the obstacle as an integer
*/
int doPing () {
int distance = 0;
int average = 0;

// Grab four measurements of distance and calculate
// the average.
for (int i = 0; i < 1; i++) { //changed from 4 to 1

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
return (average / 1); //changed from 4 to 1
}

/*
* Forwards, backwards, right, left, stop.
*/

void go_forward() {
right_servo.write(90);
left_servo.write(96);
}

void go_backwards() {
right_servo.write(96);
left_servo.write(90);
}

void go_right() {
right_servo.write(95);
left_servo.write(95);
}

void go_left() {
right_servo.write(91);
left_servo.write(91);
}

void stop_all() {
right_servo.write(93);
left_servo.write(93);
}

void brake_forward_smoothly() { //funtion to make the stopping of the robot smoother to not shake Lidar sensor (TN)
for (int i = 2; i > 0; i--){ // for loop to create int i that can be added and subtracted from the speed of the servos
	speed_right_servo = 93 - i;
	speed_left_servo = 93 + i;
	right_servo.write(speed_right_servo);
	left_servo.write(speed_left_servo);
	delay(27); // This should be 27, I change it sometimes for testing (TN)
	}
}

void backwards_start_smoothly() { //funtion to make the start of going backwards smoother to not shake Lidar sensor (TN)
for (int i = 1; i < 3; i++){ // for loop to create int i that can be added and subtracted from the speed of the servos
	speed_right_servo = 93 + i;
	speed_left_servo = 93 - i;
	right_servo.write(speed_right_servo);
	left_servo.write(speed_left_servo);
	delay(27); // This should be 27, I change it sometimes for testing (TN)
	}
}
