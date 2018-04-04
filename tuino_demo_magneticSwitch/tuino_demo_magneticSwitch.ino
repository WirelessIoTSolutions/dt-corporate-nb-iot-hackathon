
/**
 * @file tuino_demo_magneticSwitch.ino
 * @description Demo to show magnetic switch setup and function.
 * @author 
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




int mSwitch = 4;   //attach a magnetic switch to D4
int LED = 5;      //attach an LED to D5

void setup()
{
    pinMode(mSwitch, INPUT);  //define magnetic switch as an INPUT device
    pinMode(LED, OUTPUT);    //define LED as an OUTPUT device
}

void loop()
{
    /*read the status of the button*/
    int mSwitchState = digitalRead(mSwitch);  
    
    if(mSwitchState == 1)
    {
      digitalWrite(LED,1);
    }
    else
    {
      digitalWrite(LED,0);
    }
}
