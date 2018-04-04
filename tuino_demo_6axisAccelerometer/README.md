##6Axis_Accelerometer

* Tuino application that demonstrates the setup and usage of the 6Axis_Accelerometer_And_Compass

## Setup

* Connect the 6Axis_Accelerometer to the I2C interface of the Tuino.
* Connect the Tuino with a PC using the USB cable.
* Open this project with the Arduino IDE.
* Open menu Tools->Serial Monitor of the Arduino IDE.
* Compile and upload the project to the Tuino.

## Feature(s)

* The output in the serial monitor contains:
    * the components of acceleration relativ to the cartesian plane of the accelerometer (see the board of the accelerometer). The acceleration is expressed as a multiple of g (g: acceleration of gravity ).
    * The clockwise angle between the magnetic north and x-axis and
    * the clockwise angle between the magnetic north and the projection of the positive x-axis in the horizontal plane (approx. equal to 0 or 360 degrees if the x-axis shows to the north. The same like the angle above if you keep your accelerator horizontally)


###Grove - 6Axis_Accelerometer_And_Compass

The Grove 6-Axis Accelerometer & Compass is a 3-axis accelerometer combined with a 3-axis magnetic sensor.  It is based on the sensor module LSM303DLH which has a selectable linear acceleration full scale range of ±2g / ±4g / ±8g and a selectable magnetic field full scale range of ±1.3 / ±1.9 / ±2.5 / ±4.0 / ±4.7 / ±5.6 / ±8.1 gauss. Both the magnetic parts and the accelerometer parts can be powered down separately to reduce the power consumption. The Arduino can get these data via the I2C interface.

For more information, please refer to [Grove_6Axis_Accelerometer_And_Compass][1]
See also: [LSM303DLH Sensor Module Datasheet][2]

----
This software is written by Frankie Chu for [Seeed Technology Inc.](http://www.seeed.cc) and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php). Check License.txt/LICENSE for the details of MIT license.<br>

Contributing to this software is warmly welcomed. You can do this basically by<br>
[forking](https://help.github.com/articles/fork-a-repo), committing modifications and then [pulling requests](https://help.github.com/articles/using-pull-requests) (follow the links above<br>
for operating guide). Adding change log and your contact into file header is encouraged.<br>
Thanks for your contribution.

Seeed is a hardware innovation platform for makers to grow inspirations into differentiating products. By working closely with technology providers of all scale, Seeed provides accessible technologies with quality, speed and supply chain knowledge. When prototypes are ready to iterate, Seeed helps productize 1 to 1,000 pcs using in-house engineering, supply chain management and agile manufacture forces. Seeed also team up with incubators, Chinese tech ecosystem, investors and distribution channels to portal Maker startups beyond.


[1]:http://wiki.seeed.cc/Grove-6-Axis_AccelerometerAndCompass_V2.0/
[2]:http://www.st.com/web/en/resource/technical/document/datasheet/CD00260288.pdf