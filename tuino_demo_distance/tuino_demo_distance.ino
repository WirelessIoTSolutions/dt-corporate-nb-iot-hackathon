/*
  Ultrasonic Sensor HC-SR04 for Arduino
*/

// defines pins numbers
const int trigPin = 7;
const int echoPin = 6;

// defines variables
long duration;
int distance;
/**
 * general setup function
 */
void setup() {
  // Sets the trigPin as an Output
  pinMode(trigPin, OUTPUT);
  // Sets the echoPin as an Input
  pinMode(echoPin, INPUT);
  // Starts the serial communication
  Serial.begin(9600);
}
/**
 * loop function
 */
void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delay(5);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = (duration / 2) * 0.034;

  if (distance >= 500 || distance <= 0) {
    Serial.println("no data");
  }
  else {
    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(1000);
}
