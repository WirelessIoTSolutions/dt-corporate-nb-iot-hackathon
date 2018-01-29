int button = 4;   //attach a button to D4
int LED = 5;      //attach an LED to D5

void setup()
{
    pinMode(button, INPUT);  //define button an INPUT device
    pinMode(LED, OUTPUT);    //define LED an OUTPUT device
}

void loop()
{
    int buttonState = digitalRead(button);  //read the status of the button
    if(buttonState == 1)
    digitalWrite(LED,1);
    else
    digitalWrite(LED,0);
}
