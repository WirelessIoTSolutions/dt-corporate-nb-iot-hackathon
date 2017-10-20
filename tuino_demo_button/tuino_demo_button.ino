/**
 * @file tuino_demo_button.ino
 * @description Demo to show TUINO button setup and function.
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
 
/*Connect the button to D4.*/
int buttonPin = D4;


/**
 * @brief This function waits actively until the button is pressed (blocking). 
 * 
 * The function does not return unless the button was pressed. Therefore 
 * all other program execution (except interrupts) is on hold while waiting 
 * for the button to be pressed.
 */
void waitButton_Blocking() {

  while ( digitalRead(buttonPin) == 0 ) {
    /*NOTE Loop body intentionally left empty.*/
  };

  delay(200);
}



/**
 * @brief This function checks the current state of the button and returns 
 * it immediately. The function does not wait for any specific button state 
 * (non-blocking).
 */
bool isButtonPressed_Nonblocking() {
  return (digitalRead(buttonPin) != 0);
}


/**
 * @brief Initialisation, called once during system startup.
 *
 * Make sure your button is connected to D4. 
 */
void setup() {
  /*serial debug output*/
  Serial.begin(9600);
  Serial.println("Button Demo");
  
  /*Button DigIn configuration*/
  pinMode(buttonPin, INPUT);

  /*check button function*/
  Serial.println("Press button now...");
  waitButton_Blocking();
  Serial.println("Works");
}



/**
 * @brief Main code here, to run repeatedly. Avoid blocking code sequences!
 * 
 * The function prints one line each time the button was pressed or released.
 * Make sure your button is connected to D4. You will see the output text at 
 * the Arduino serial monitor.
 */
void loop() {
  static bool buttonIsPressed = false;
 
  /*check button function*/
  if(isButtonPressed_Nonblocking() && !buttonIsPressed) {
    /*button press detected (signalised once)*/
    buttonIsPressed = true;
    Serial.println("Button pressed.");
  }
  else if(!isButtonPressed_Nonblocking() && buttonIsPressed) {
    /*button release detected (signalised once)*/
    buttonIsPressed = false;
    Serial.println("Button released.");
  }
}

