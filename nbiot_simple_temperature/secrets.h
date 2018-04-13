#ifndef DT_COT_ARDUINO_LIBRARY_SECRET_HEADER_FILE
#define DT_COT_ARDUINO_LIBRARY_SECRET_HEADER_FILE


/**
 * Wifi Credentials
 */
#define SECRET_WIFI_SSID      "mm1-technology-gast"
#define SECRET_WIFI_PASSWORD  ""

/**
 * NB-IoT Credentials
 */
#define NB_IOT_SERVER_IP      "172.25.102.151"
#define NB_IOT_SERVER_PORT    1883

/* TODO 
 * Put your MQTT-SN access parameters here: 
 * IMSI and MQTTSN password of your SIM card.
 */
#define NB_IOT_IMSI           "<IMSI>" 
#define NB_IOT_MQTTSN_PWD     "<YOUR_MQTTSN_PWD>"


/* NOTE: Please keep this (legacy) define untouched.*/
#define NB_IOT_COT_PWD        NB_IOT_MQTTSN_PWD



/**
 * GSM Credentials
 */
#define GSM_PIN               "0000"

/**********************************/



const char* CLOUD_SERVER_PASSWORD = "";
const char* ADAFRUIT_USER_ID = "";

#endif /* DT_COT_ARDUINO_LIBRARY_SECRET_HEADER_FILE */
