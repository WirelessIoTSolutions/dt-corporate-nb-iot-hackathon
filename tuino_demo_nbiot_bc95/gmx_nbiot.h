/* _____  _____  __  __             _____  _____ 
  / ____||_   _||  \/  |    /\     / ____||_   _|
 | |  __   | |  | \  / |   /  \   | (___    | |  
 | | |_ |  | |  | |\/| |  / /\ \   \___ \   | |  
 | |__| | _| |_ | |  | | / ____ \  ____) | _| |_ 
  \_____||_____||_|  |_|/_/    \_\|_____/ |_____|
  (c) 2017 GIMASI SA                                               

 * gmx_nbiot.h
 *
 *  Created on: July 27, 2017
 *      Author: Massimo Santoli
 *      Brief: Tuino 1 interface for GMX-NB module family
 *      Version: 1.0
 *
 *      License: it's free - do whatever you want! ( provided you leave the credits)
 *
 */
#ifndef _GMX_NBIOT_H
#define _GMX_NBIOT_H

#include <Arduino.h>


#define GMXNB_KO                      -1 

#define GMXNB_OK                      0 

#define GMXNB_NOT_PRESENT             10
#define GMXNB_NO_SERIAL               20

#define GMXNB_AT_ERROR                30
#define GMXNB_AT_GENERIC_ERROR        99
#define GMXNB_AT_TIMEOUT              55

#define GMXNB_LED_ON                  1
#define GMXNB_LED_OFF                 0

#define GMX_UART_INTERFACE            1
#define GMX_SPI_INTERFACE             2

#define GMX_UART_SPEED                9600
#define GMX_UART_TIMEOUT              10000

#define GMX_BOOT_DELAY                4000


#define NB_NETWORK_JOINED             1
#define NB_NETWORK_NOT_JOINED         0



/*
 * GMX-LR1 Init function
 *  the only parameter is the function for the RxData callback
 */
 
byte gmxNB_init(bool forceReset, String ipAddress, int udpPort, void( *callback)());
byte gmxNB_connect(String ipAddress, int udpPort);
byte gmxNB_getVersion(String& version);
byte gmxNB_getIMEI(String& imei);

byte gmxNB_getIMSI(String& imsi);
byte gmxNB_radioON(String& param);
byte gmxNB_radioOFF(String& param);
byte gmxNB_setAPN(String APN);
byte gmxNB_isNetworkJoined(void);
byte gmxNB_ping(String hostIp);
byte gmxNB_getCSQ(String& csq);


void gmxNB_startDT();


// TX & RX Data
int gmxNB_SocketOpen(void);
byte gmxNB_SocketClose(int sock);
byte gmxNB_SocketClose(void);
int gmxNB_Available(void);
byte gmxNB_TXData(const char *binaryData, int len);
byte gmxNB_RXData(String &remoteIp, int &udpPortNr, byte *binaryData, int &len);

/*data conversion binary <-> hex */
String AtResponseTokenize(String atResponse, String delimiter, int &indexStart);
String gmxNB_BinaryToHex(const char *binaryData, int binaryLen );
byte gmxNB_HexToBinary(String hexStr, byte *binaryData);




/*
 * Utilities
 */
 
void gmxNB_Led1(byte led_state);
void gmxNB_Led2(byte led_state);
void gmxNB_Led3(byte led_state);

void gmxNB_Reset(void);

#endif /*_GMX_NBIOT_H*/

