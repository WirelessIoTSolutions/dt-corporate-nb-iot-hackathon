/**
 * @file tuino_demo_tempsensor.ino
 * @description Demo to show temperature sensor setup and function.
 * @author akrause
 * @copyright (C) 2017 mm1 Technology GmbH - all rights reserved. 
 * @licence MIT licence
 * 
 * Find out more about mm1 Technology:
 * Company: http://mm1-technology.de/
 * GitHub:  https://github.com/mm1technology/
 * 
 * Code pieces partially based on GIMASI TUINO example project(s):
 * Company: http://www.tuino.io/
 * GitHub:  https://github.com/gimasi
 */


/*Temperature sensor constants*/
#define TEMPERATURE_SAMPLING    (10)

int tempSensorPin = A0;
float current_temperature = 0.0f;



float readTemp() {
  const int B = 4275;                                           // B value of the thermistor
  int sensorRaw = (float)analogRead(tempSensorPin);
  float R = 1023.0 / ((float)sensorRaw) - 1.0;
  float temperature = 1.0 / (log(R) / B + 1 / 298.15) - 273.15; //convert to temperature via datasheet ;

  return temperature;
}



/**
 * @brief Initialisation, called once during system startup.
 * 
 * Make sure the temperature sensor is connected to A0. Debugging 
 * output is visible at the serial monitor of Arduino IDE.
 */
void setup() {
  /*serial debug output*/
  Serial.begin(9600);
  Serial.println("Temperature Sensor Demo");
  // Init Temperature
  current_temperature = readTemp();
}




/**
 * @brief Main code here, to run repeatedly. Avoid blocking code sequences!
 * 
 * The function will be collects temperature values every 100 milliseconds and 
 * prints the them every second to the serial monitor. Make sure the temperature 
 * sensor is connected to A0.
 */
void loop() {
  static float temp_temperature = 0.0f;
  static int temperature_counts = 0;
  
  // update temperature
  // we sample and make an average of the temperature - since in this demo we use a NTC sensor that fluctuates
  temp_temperature += readTemp();
  temperature_counts++;

  if ( temperature_counts >= TEMPERATURE_SAMPLING ) {
    current_temperature = temp_temperature / TEMPERATURE_SAMPLING;
    temperature_counts = 0;
    temp_temperature = 0;

    Serial.println("Temp: " + String(current_temperature, 2));
  }

  delay(100);
}


