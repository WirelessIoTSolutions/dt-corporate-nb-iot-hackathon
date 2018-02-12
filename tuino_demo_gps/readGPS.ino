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


/* Message detected, check this message for consistency.
* TODO: Checksum validation might be nice...!!!
*/
  res = str.substring(str.indexOf('A')+13,str.indexOf('A') + 37);
  String gps_coords_1 = "";
  String gps_coords_2 = "";
  
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

    if (gps_coords_1[10] == 'N') {
      gps.longitude.fl = (gps_coords_1.toFloat());
      
    }
    else {
      gps.longitude.fl = (gps_coords_1.toFloat() * -1);
    }
    gps.longitude.fl = normalize(gps.longitude.fl);       
    if (gps_coords_2[10] == 'E') {
      gps.latitude.fl = (gps_coords_2.toFloat());
    }
    else {
      gps.latitude.fl = (gps_coords_2.toFloat() * -1);
    }
    gps.latitude.fl = normalize(gps.latitude.fl);

  Serial.println("****************************************");
  Serial.println("Raw GPS data: " + str + " len: " + str.length());
  Serial.println("Your position: " + String(gps.longitude.fl, 4) + "  ,  " + String(gps.latitude.fl, 4));
  
  }
  else
  {
  Serial.println("****************************************");  
  Serial.println("Invalid GPS data: " + res);
  // Serial.println("commaCount: " + String(commaCount) + " res[10]: " + String(res[10]) + " res[23]: " + String(res[23]));
  gps.latitude.fl = 0.0;
  gps.longitude.fl = 0.0;
  }

  SoftSerial.end();

  return gps;
}



char* gps_to_mqtt(gps_coord_t coord, char *buff) {
  
  gps_coord_t *ret;
   
  if (buff == NULL) {
    return NULL;
  }

  ret = (gps_coord_t *)buff;
  ret->longitude.u32 =  htonl(coord.longitude.u32);
  ret->latitude.u32  =  htonl(coord.latitude.u32);
  
  return (char *)ret;
}



float normalize(float coord){
  float ret;
  
  ret = ((int)coord/100);
  ret += (((coord/100) - ret)*100)/60;
  
  return ret;
}



char* byte_to_hex(char byt,char *buff) {

  uint8_t nibble = (uint8_t)byt >> 4;
  
  if(nibble < 10){
    buff[0] = nibble + '0'; 
  }
  else {
    buff[0] = nibble - 10 + 'A';
  }
  nibble = (uint8_t)byt & 0x0f;

  if(nibble < 10){
    buff[1] = nibble + '0'; 
  }
  else {
    buff[1] = nibble - 10 + 'A';
  }
  buff[2] = 0;
}
  

