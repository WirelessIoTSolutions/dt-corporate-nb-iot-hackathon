


char* oledList[OLED_LIST_MAX] = {
		(char*)"Temp:          ",
		(char*)"Light:         ",
		(char*)"Dist:          ",
		(char*)"GPS:           ",
		(char*)"Volt:          ",
};




void showValuesOLED() {
	static int currListIndex = 0;
	static unsigned long lastSecondsOLEDRotation = 0;
	static unsigned long intervall = 3;
	static unsigned long tickOLEDRotation = 0;

	// tickOLEDRotation = upTimeInSeconds();

	if((tickOLEDRotation - lastSecondsOLEDRotation) > intervall) {
		Serial.println("change OLED...");
		lastSecondsOLEDRotation = tickOLEDRotation;
		SeeedOled.setTextXY(4, 0);

		if(currListIndex >= OLED_LIST_MAX) {
			currListIndex = 0;
		}
		
		//Serial.print("Index: ");
		//Serial.print(currListIndex);
		//Serial.print("  -- ");
		//Serial.print("printing to OLED: ");
		//Serial.println(oledList[currListIndex]);
		SeeedOled.putString(oledList[currListIndex]);
		currListIndex++;
	}
}


void updateValuesOLED(int listPlace, char *value) {

	static int delayAfterListUpdate = 50;
	char OLEDtmpStr[OLED_LIST_MAX_CHAR];

	if(listPlace > OLED_LIST_MAX-1) {
		Serial.println("index for list too high!");
		return;
	}
	
	switch (listPlace) {

	case OLED_LIST_TEMP:     
		sprintf(OLEDtmpStr, "Temp: %s C   ", value); 
		strcpy(oledList[OLED_LIST_TEMP], OLEDtmpStr);
		//Serial.print("Length OLEDtmpStr Temp: ");
		//Serial.println(strlen(OLEDtmpStr));
		delay(delayAfterListUpdate);
		break;

	case OLED_LIST_LIGHT:
		sprintf(OLEDtmpStr, "LUX: %s     ", value); 
		strcpy(oledList[OLED_LIST_LIGHT], OLEDtmpStr);
		//Serial.print("Length OLEDtmpStr Light: ");
		//Serial.println(strlen(OLEDtmpStr));
		delay(delayAfterListUpdate);
		break;

	case OLED_LIST_DISTANCE:
		sprintf(OLEDtmpStr, "Dist: %s cm     ", value); 
		strcpy(oledList[OLED_LIST_DISTANCE], OLEDtmpStr);
		//Serial.print("Length OLEDtmpStr Dist: ");
		//Serial.println(strlen(OLEDtmpStr));
		delay(delayAfterListUpdate);
		break;

	case OLED_LIST_GPS:
		if(value == "valid") {
			sprintf(OLEDtmpStr, "GPS found      "); 
		}
		else {
			sprintf(OLEDtmpStr, "No GPS found   "); 
		}

		strcpy(oledList[OLED_LIST_GPS], OLEDtmpStr);
		//Serial.print("Length OLEDtmpStr GPS: ");
		//Serial.println(strlen(OLEDtmpStr));
		delay(delayAfterListUpdate);
		break;

	case OLED_LIST_VOLTAGE:
		//sprintf(OLEDtmpStr, "V: %s", value); 
		strcpy(oledList[OLED_LIST_VOLTAGE], value);
		//Serial.print("Length OLEDtmpStr Volt: ");
		//Serial.println(strlen(OLEDtmpStr));
		delay(delayAfterListUpdate);
		break;

	default:
		Serial.println("Unknown index");
	}
}

