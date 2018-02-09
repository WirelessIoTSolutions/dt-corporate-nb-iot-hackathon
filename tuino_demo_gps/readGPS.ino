gps_coord_t readGPS() {

  
  // NOTE lineStartSeq as a String object to make sure it is treated correctly by overloaded functions./
  const String lineStartSeq = "$GPGGA";
  gps_coord_t gps;
  
  String str = "";
  String res = "";
  int indexStart = -1;
  int indexEnd = -1;
  char rxChar = '\0';
  bool coordValid;
  int commaCount = 0;

  Serial.println("Reading GPS...");

  SoftSerial.begin(9600);
  /*delay required due to UART timing constraints!*/
  delay(100);

  do {
    /*read character from serial*/
    rxChar = SoftSerial.read();
    /*delay required due to UART timing constraints!*/
    delay(5);
    
    str += rxChar;
    /*detect 'start of message'*/
    indexStart = str.indexOf(lineStartSeq);

    if(indexStart != str.lastIndexOf(lineStartSeq)) {
      /*ooops, we've missed an 'end of message', fix it*/
      indexStart = str.lastIndexOf(lineStartSeq);
    }
    if (indexStart > 0) {
      /*remove leading garbage*/
      str = str.substring(indexStart, str.length());
      indexStart = str.indexOf(lineStartSeq);
    }  
 
  /*detect 'end of message'*/
  indexEnd = str.indexOf('\r');

  } while ((indexStart < 0) || (indexStart >= indexEnd));

  Serial.println("Raw GPS data: " + str + " len: " + str.length());
  Serial.println("****************************************");

/* Message detected, check this message for consistency.
* TODO: Checksum validation might be nice...!!!
*/
  res = str.substring(str.indexOf('A')+13,str.indexOf('A') + 37);
  String gps_coords_1 = "";
  String gps_coords_2 = "";
  // Serial.println("testdaten: " +res);
/* count n/o ',' in the string */
  commaCount = 0;
  for (int strPos = 0; res[commaCount + strPos]; res[commaCount + strPos] == ',' ? commaCount++ : strPos++);

  coordValid = (commaCount == 3);
  coordValid = (res[12] > 0);
  coordValid = coordValid && ((res[10] == 'N') || (res[10] == 'S'));
  coordValid = coordValid && ((res[23] == 'E') || (res[23] == 'W'));

  if (coordValid)
  {
    gps_coords_1 = res.substring(res.indexOf(',') - 9, res.indexOf(',') + 2);
    gps_coords_2 = res.substring(res.indexOf(',') + 4, res.indexOf(',') +15);
    
    Serial.println("Your current position is at: ");
    Serial.println("Longitude -  " + gps_coords_1);
    Serial.println("Latidue   -  " + gps_coords_2);
    Serial.println("****************************************");


    if (gps_coords_1[10] == 'N') {
      gps.longitude.fl = gps_coords_1.toFloat();
    }
    else {
      gps.longitude.fl = (gps_coords_1.toFloat() * -1);
    }
     
       
    if (gps_coords_2[10] == 'E') {
      gps.latitude.fl = (gps_coords_2.toFloat());
    }
    else {
      gps.latitude.fl = (gps_coords_2.toFloat() * -1);
    }
    
    
    
  }
  else
  {
  Serial.println("invalid GPS data: " + res);
  Serial.println("commaCount:" + String(commaCount) + " res[10]:" + String(res[10]) + " res[10]:" + String(res[10]) + " res[12] " + String(res[12]));
  }

  SoftSerial.end();

  return gps;
}

