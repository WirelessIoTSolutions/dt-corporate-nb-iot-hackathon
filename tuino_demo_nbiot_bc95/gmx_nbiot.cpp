/* _____  _____  __  __             _____  _____
  / ____||_   _||  \/  |    /\     / ____||_   _|
  | |  __   | |  | \  / |   /  \   | (___    | |
  | | |_ |  | |  | |\/| |  / /\ \   \___ \   | |
  | |__| | _| |_ | |  | | / ____ \  ____) | _| |_
  \_____||_____||_|  |_|/_/    \_\|_____/ |_____|
  (c) 2017 GIMASI SA

   gmx_nbiot.cpp

    Created on: July 27, 2017
        Author: Massimo Santoli
        Brief: Tuino 1 interface for GMX-NB module family
        Version: 1.1

        License: it's free - do whatever you want! ( provided you leave the credits)

*/

#include "gmx_nbiot.h"
#include "Regexp.h"
#include <string.h>

#define DEBUG 0
#define INVALID_SOCKET (-1)


String        dummyResponse;
byte          gmxNB_interface = GMX_UART_INTERFACE;
int           udp_socket_num = INVALID_SOCKET;
String        udp_socket_ip;
String        udp_port;
const int     udp_rx_timeout = 30; // seconds
const int     udp_max_packet_sz = 255;

void(*_NBRing)();




//
// ISR
//
ISR(PCINT1_vect) {
  if (digitalRead(GMX_INT) == 0) {
    if (_NBRing)
      _NBRing();
  }
}



void _resetGMX() {

  pinMode(GMX_RESET, OUTPUT);
  // Reset
  digitalWrite(GMX_RESET, HIGH);
  delay(100);
  digitalWrite(GMX_RESET, LOW);
  delay(100);
  digitalWrite(GMX_RESET, HIGH);
}



void _log(String data )
{
#ifdef DEBUG
  Serial.println(data);
#endif
}



void _sendCmd(String in) {
  int len = in.length();
  long int start_timeout;

  Serial.println("----->");
  Serial.print("SENDING: ");
  Serial.println(in);
  Serial.println("----->");

  //  send data
  for (int i = 0; i < len; i++) {
    if ( gmxNB_interface == GMX_UART_INTERFACE )
    {
      Serial1.write(in.charAt(i));
    }
    delay(1);
  }

  delay(100);

  if ( gmxNB_interface == GMX_UART_INTERFACE )
  {
    start_timeout = millis();
    while (Serial1.available() == 0) {
      if (( millis() - start_timeout ) > GMX_UART_TIMEOUT  )
      {
        Serial.println("TIMEOUT on :" + in);
        break;
      }
    }
  }
}



/*overloaded function for backward compatibility. This version can deal with different search strings.*/
byte _parseResponse(String& response, const char *searchPattern) {
  // RegExp Engine
  static MatchState ms;
  static char buf[512];
  char cmd[128];
  String gmxSerialString = "";

  response = "";

  // Read from Serial
  while (Serial1.available() > 0)
  {
    while (Serial1.available() > 0)
    {
      gmxSerialString += (char)Serial1.read();
    }

    delay(10);
  }

  gmxSerialString.toCharArray(cmd, gmxSerialString.length());
  Serial.println("<-----");
  Serial.print("RESPONSE: ");
  Serial.println(gmxSerialString);
  Serial.println("<-----");

  // Parse Response
  ms.Target(cmd);
  char result = ms.Match (searchPattern, 0);
  if ( result == REGEXP_MATCHED )
  {
    ms.GetCapture (buf, 0);

    response = String(buf);

    // remove second \r\n => Not very elegant to optimize
    response.toCharArray(cmd, response.length());
    response = String(cmd);

    return (GMXNB_OK);
  }
  // Check for Errors
  result = ms.Match ("(.*)\r\nERROR", 0);
  if ( result == REGEXP_MATCHED )
  {
    return (GMXNB_AT_ERROR);
  }

  return (GMXNB_AT_GENERIC_ERROR);
}



/* Overloaded function version for backward compatibility. 
 * This is the original version that searches for "OK" only.
 */
byte _parseResponse(String& response) {
  return _parseResponse(response, "(.*)\r\nOK");
}



/* GMXLR Commands Interface */

bool gmxNB_tryQuickInit(String ipAddress, int udpPort, void( *callback)())
{
  String response;
  byte init_status = GMXNB_KO;
  byte status;

  udp_socket_ip = ipAddress;
  udp_port = udpPort;

  _log("GMXNB Init");

  pinMode(GMX_GPIO1, OUTPUT);
  pinMode(GMX_GPIO2, OUTPUT);
  pinMode(GMX_GPIO3, OUTPUT);
  digitalWrite(GMX_GPIO1, LOW);
  digitalWrite(GMX_GPIO2, LOW);
  digitalWrite(GMX_GPIO3, LOW);

  // Init Interface
  if ( gmxNB_interface == GMX_UART_INTERFACE )
  {
    // Setup Serial
    if (Serial1) {
      Serial1.begin(GMX_UART_SPEED);
      _log("GMX Serial Interface");
      init_status = GMXNB_OK;
    }
    else
    {
      return (GMXNB_NO_SERIAL);
    }
  }
  
  // Setup Interrupt PIN for Rx
  *digitalPinToPCICR(GMX_INT) |= (1 << digitalPinToPCICRbit(GMX_INT));
  *digitalPinToPCMSK(GMX_INT) |= (1 << digitalPinToPCMSKbit(GMX_INT));

  // set RX callback
  _NBRing = callback;

  // delay to wait BootUp of GMX-LR
  delay(GMX_BOOT_DELAY);

  _sendCmd( "AT\r" );
  _parseResponse(response);
  _sendCmd( "AT\r" );
  status = _parseResponse(response);

  if(status != GMXNB_OK)
  {
    return gmxNB_init(ipAddress, udpPort, callback);
  }
  else
  {
    return init_status;
  }
}



byte gmxNB_init(String ipAddress, int udpPort, void( *callback)())
{
  String response;
  byte init_status = GMXNB_KO;

  udp_socket_ip = ipAddress;
  udp_port = udpPort;

  _log("GMXNB Init");

  pinMode(GMX_GPIO1, OUTPUT);
  pinMode(GMX_GPIO2, OUTPUT);
  pinMode(GMX_GPIO3, OUTPUT);
  digitalWrite(GMX_GPIO1, LOW);
  digitalWrite(GMX_GPIO2, LOW);
  digitalWrite(GMX_GPIO3, LOW);

  _resetGMX();

  // Init Interface
  if ( gmxNB_interface == GMX_UART_INTERFACE )
  {
    // Setup Serial
    if (Serial1) {
      Serial1.begin(GMX_UART_SPEED);
      _log("GMX Serial Interface");
      init_status = GMXNB_OK;
    }
    else
    {
      return (GMXNB_NO_SERIAL);
    }
  }

  // Setup Interrupt PIN for Rx
  *digitalPinToPCICR(GMX_INT) |= (1 << digitalPinToPCICRbit(GMX_INT));
  *digitalPinToPCMSK(GMX_INT) |= (1 << digitalPinToPCMSKbit(GMX_INT));

  // set RX callback
  _NBRing = callback;

  // delay to wait BootUp of GMX-LR
  delay(GMX_BOOT_DELAY);

  _sendCmd( "AT\r" );
  _parseResponse(response);
  _sendCmd( "AT\r" );
  _parseResponse(response);
  return init_status;
}



/* Version */
byte gmxNB_getVersion(String& version)
{
  _sendCmd( "AT+CGMR\r" );
  return ( _parseResponse(version) );
}



/* IMEI */
byte gmxNB_getIMEI(String& imei)
{
  _sendCmd( "AT+CGSN=1\r" );
  return ( _parseResponse(imei) );
}



/* IMSI */
byte gmxNB_getIMSI(String& imsi)
{
  _sendCmd( "AT+CIMI\r" );
  return ( _parseResponse(imsi) );
}



/* Signal Strength Indicator */
byte gmxNB_getCSQ(String& csq)
{
  _sendCmd( "AT+CSQ\r" );
  return ( _parseResponse(csq) );
}



/* Radio on */
byte gmxNB_radioON(String& param)
{
  _sendCmd( "AT+CFUN=1\r" );
  return ( _parseResponse(param) );
}



/* all powered down */
byte gmxNB_radioOFF(String& param)
{
  _sendCmd( "AT+CFUN=0\r" );
  return ( _parseResponse(param) );
}



/* APN */
byte gmxNB_setAPN(String APN)
{
  _sendCmd( "at+cgdcont=1,\"IP\",\"" + APN + "\"\r" );
  return ( _parseResponse(dummyResponse) );
}



/*ping*/
byte gmxNB_ping(String hostIp)
{
  _sendCmd("at+nping=" + hostIp + "\r");
  return ( _parseResponse(dummyResponse) );
}



/*Network provider dependent setup: Deutsche Telekom*/
void gmxNB_startDT()
{
  _sendCmd( "AT+NCONFIG=CR_0354_0338_SCRAMBLING,TRUE\r" );
  _parseResponse(dummyResponse);

  _sendCmd( "AT+NCONFIG=CR_0859_SI_AVOID,TRUE\r" );
  _parseResponse(dummyResponse);

  gmxNB_getIMSI(dummyResponse);

  gmxNB_radioOFF(dummyResponse);

  // ak: should be auto-configured from provider
  // _sendCmd( "AT+CGDCONT=1,\"IP\",\"internet.nbiot.telekom.de.MNC040.MCC901.GPRS\"\r" );
  // _parseResponse(dummyResponse);
  // gmxNB_setAPN("internet.nbiot.telekom.de.MNC040.MCC901.GPRS");

  gmxNB_radioON(dummyResponse);

  _sendCmd( "AT+NBAND=8\r" );
  _parseResponse(dummyResponse);

  _sendCmd( "AT+COPS=1,2,\"26201\"\r" );
  _parseResponse(dummyResponse);

}



/* Check Network */

byte gmxNB_isNetworkJoined(void)
{
  byte status;
  char cmd[16];
  String tmp;

  _sendCmd( "at+cgatt?\r" );

  if ( (status = _parseResponse(dummyResponse)) == GMXNB_OK )
  {
    int index = dummyResponse.indexOf(":");
    if ( index != -1 )
    {
      tmp = dummyResponse.substring(index + 1, dummyResponse.length());
      tmp.toCharArray(cmd, tmp.length());

      switch(cmd[0])
      {
        case '1':
          return NB_NETWORK_JOINED;
          break;
  
        case '0':
          return NB_NETWORK_NOT_JOINED;
          break;
          
        default:
          return (status);
      }
    }
  }
  return (status);
}




void gmxNB_Reset(void) {
  String command = String("AT+NRB\r");
  int len = command.length();

  //  send data
  for (int i = 0; i < len; i++) {
    if ( gmxNB_interface == GMX_UART_INTERFACE )
    {
      Serial1.write(command.charAt(i));
    }
    delay(1);
  }

  delay(GMX_BOOT_DELAY);
}



byte gmxNB_HexToBinary(String hexStr, byte *binaryData)
{
  char temp;
  int j = 0;
  int binaryLen;

  if(hexStr.length() % 2 != 0)
  {
    Serial.println("Invalid format of received hex data.");
    return GMXNB_AT_GENERIC_ERROR;
  }
  else
  {
    hexStr.toUpperCase();
    binaryLen = hexStr.length() / 2;
    
    for (int i = 0; i < binaryLen * 2; i += 2)
    {
      /*Convert hex string to numeric binary (and make sure to have uppcase characters)*/
      temp = hexStr.charAt(i);
      binaryData[j] = (temp <= '9') ? (temp - '0') : (temp - 'A' + 10);
      binaryData[j] *= 16;
      temp = hexStr.charAt(i+1);
      binaryData[j] += (temp <= '9') ? (temp - '0') : (temp - 'A' + 10);
  
      j++;
    }
  
  }

  return GMXNB_OK;
}



String gmxNB_BinaryToHex(const char *binaryData, int binaryLen )
{
  char myData[256];

  for (int i = 0; i < binaryLen; i++)
  {
    sprintf(&(myData[2 * i]), "%02X", (byte)binaryData[i]);
  }

  /*add string termination*/
  myData[2 * binaryLen] = 0;
  /*convert to String object*/
  return (String(myData));
}




/*green LED*/
void gmxNB_Led1(byte led_state)
{
  digitalWrite(GMX_GPIO1, led_state);
}



/*yellow(?) LED - quite weak...*/
void gmxNB_Led2(byte led_state)
{
  digitalWrite(GMX_GPIO2, led_state);
}



/*orange LED*/
void gmxNB_Led3(byte led_state)
{
  digitalWrite(GMX_GPIO3, led_state);
}




// TX & RX Data
int gmxNB_SocketOpen(void)
{
  _sendCmd("at+nsocr=DGRAM,17," + udp_port + "\r");
  _parseResponse(dummyResponse);
  /*FIXME which socket number have we really got?*/
  udp_socket_num = 0;
  return udp_socket_num;
}



byte gmxNB_SocketClose(int sock)
{
  if (udp_socket_num != INVALID_SOCKET)
  {
    _sendCmd("at+nsocl=" + String(sock) + "\r");
    return ( _parseResponse(dummyResponse) );
  }
  else
  {
    return GMXNB_AT_ERROR;
  }
}



byte gmxNB_SocketClose(void)
{
  return gmxNB_SocketClose(udp_socket_num);
}



byte gmxNB_TXData(const char *binaryData, int len)
{
  if (udp_socket_num == INVALID_SOCKET)
  {
    Serial.print("Opening socket:");
    gmxNB_SocketOpen();
  }

  _sendCmd("at+nsost=" + String(udp_socket_num) + "," + udp_socket_ip + "," + udp_port + "," + String(len) + "," + gmxNB_BinaryToHex(binaryData, len) + "\r" );
  return _parseResponse(dummyResponse);
}





String AtResponseTokenize(String atResponse, String delimiter, int &indexStart)
{
  String subString = "";
  int indexEnd = atResponse.indexOf(delimiter, indexStart);
  
  if(indexEnd == -1)
  {
    /*could not find delimiter in string*/
    Serial.println("delimiter \"" + delimiter + "\" not found.");
  }
  else
  {
    subString = atResponse.substring(indexStart, indexEnd);
    indexStart = indexEnd + 1;
  }
  
  return subString;
}




/*Wait for incoming data packet*/
byte gmxNB_RXData(String &remoteIp, int &udpPortNr, byte *binaryData, int &len)
{
  /*FIXME Data rx should better be non-blocking!*/

  byte status;
  String rxStr, tmpStr, subStr;
  int maxRetrials;
  int currentStrIndex;

  Serial.println("gmxNB_RXData(): wait for incoming packet(s)");

  maxRetrials = 300;
  while((Serial1.available() == 0) && (maxRetrials > 0))
  {
    maxRetrials--;
    delay(100);
    /*wait for incoming characters*/
  }


  if(maxRetrials <= 0)
  {
    Serial.println("ERR: Remote host didn't respond.");
    return GMXNB_AT_TIMEOUT;
  }
  else
  {
    Serial.println("data from modem pending");
    maxRetrials = 5;
  }

  do {
    /*
      Find a +NSONMI:[socket],[bytes] indication in incoming string
      if yes cancel sensing the serial
    */
    Serial.println("read/parse...");
    status = _parseResponse(dummyResponse, "+NSONMI:");
    Serial.println("parse status = " + String(status));
    delay(100);
    maxRetrials--;
  }  while ((status != GMXNB_OK) && (maxRetrials > 0));

  Serial.println("loop left with parse status = " + String(status));
  Serial.println(dummyResponse);

  if ((status != GMXNB_OK) || (maxRetrials <= 0))
  {
    Serial.println("ERR: Remote host didn't respond.");
  }
  else
  {
     Serial.println("Reading incoming UDP packet...");
    _sendCmd("at+nsorf=" + String(udp_socket_num) + "," + udp_max_packet_sz + "\r" );
    status = _parseResponse(rxStr);
    
    /*Dissecting received string
     * Format:  [socketNr],[srcIpAddr],[rxUdpPort],[numBytes],[hexPayload],[rxBytesStillPending]
     * Example: 0,172.25.102.147,1883,3,030500,0
     */
    remoteIp        = "";
    udpPortNr       = -1;
    len             = 0;
    currentStrIndex = 0;
    
    /*socket number (will be skipped)*/
    subStr = AtResponseTokenize(rxStr, ",", currentStrIndex);
    if(subStr == "")
    {
      Serial.println("error decoding socket nr");
      return GMXNB_AT_GENERIC_ERROR;
    }
  
    /*source ip address*/
    subStr = AtResponseTokenize(rxStr, ",", currentStrIndex);
    if(subStr == "")
    {
      Serial.println("error decoding src ip addr");
      return GMXNB_AT_GENERIC_ERROR;
    }
    else
    {
      remoteIp = subStr;
      Serial.println("srcip " + remoteIp);
    }
  
    /*UDP port*/
    subStr = AtResponseTokenize(rxStr, ",", currentStrIndex);
    if(subStr == "")
    {
      Serial.println("error decoding udp port");
      return GMXNB_AT_GENERIC_ERROR;
    }
    else
    {
      udpPortNr = subStr.toInt();
      Serial.println("port " + String(udpPortNr));
    }
  
    /*payload length*/
    subStr = AtResponseTokenize(rxStr, ",", currentStrIndex);
    if(subStr == "")
    {
      Serial.println("error decoding udp port");
      return GMXNB_AT_GENERIC_ERROR;
    }
    else
    {
      len = subStr.toInt();
      Serial.println("payloadlen " + String(len));
    }
  
    /*payload (hex encoded)*/
    subStr = AtResponseTokenize(rxStr, ",", currentStrIndex);
    if(subStr == "")
    {
      Serial.println("error decoding udp port");
      return GMXNB_AT_GENERIC_ERROR;
    }
    else
    {
      /*get hex encoded version of payload from rxStr*/
      Serial.println("payload: " + subStr);
      gmxNB_HexToBinary(subStr, binaryData);
    }
  }
  
  return GMXNB_OK;
}


