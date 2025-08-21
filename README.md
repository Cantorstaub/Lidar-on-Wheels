# Lidar on Wheels

The Lidar on Wheels is a small experimental device we built in the [Virtual Humanities Lab](https://vhl.blogs.ruhr-uni-bochum.de/) at _Ruhr-University Bochum_ in 2023 and 2024.

<img src = "/18-als-thn-IMG_9466-cover-mccomb-ultrasound-posing.jpg?raw=true" width = "400" title = "The 'McComb-robot' is the inner core of the Lidar on Wheels." alt = "A small DIY robot with two ultrasonic sensors at the front looking like eyes."/>

Building this robot and experimenting with its behaviour was an integral part of our research on the media theoretical implications of sensors, autonomous vehicles, and the effects of scaling.[[1]](#_ftn1) The Lidar on Wheels is able to orient itself in a room by using ultrasound detection and an Arduino microcontroller. In addition to this, the robot carries an _RPLidar A1M8_ Sensor and a Jetson Nano Computer. 

While the robot is moving, the Lidar sensor detects this environment and creates a map of the room. Importantly, the ultrasonic sensor and the Arduino, on the one hand, and the Lidar sensor and the Jetson Nano, on the other, are separated in the current state of the robot. I.e., the Lidar sensor sits like a parasite on the Lidar on Wheels, profiting from movements of the robot when measuring the room, but not providing the robot with any data in return.

The inner core of the robot is based on instructions by Gordon McComb, consisting of a small vehicle with two servomotors, the ultrasonic sensor for obstacle detection, and the Arduino microcontroller. From here, we expanded and reconfigured this small robot by constructing a metal case to carry the Lidar sensor and the Jetson Nano.

<img src = "/18-als-thn-IMG_9466-cover-mccomb-ultrasound-posing.jpg?raw=true" width = "400" title = "The 'McComb-robot' is the inner core of the Lidar on Wheels." alt = "A small DIY robot with two ultrasonic sensors at the front looking like eyes."/>

_The 'McComb-robot' is the inner core of the Lidar on Wheels._

Pictures

## Further Reading

Arduino Text

Labbook Text

Roboterbuch

Link to Videos and to the Lab book

## References

[[1]](#_ftnref1)
