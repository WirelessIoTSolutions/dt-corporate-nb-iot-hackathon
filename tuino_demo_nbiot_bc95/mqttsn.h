/**
 * @file mqttsn.h
 * @description Basic setup and function of the MQTT-SN protocol to interact 
 * with the Deutsche Telekom Cloud of things.
 * @author akrause
 * @copyright (C) 2017 mm1 Technology GmbH - all rights reserved. 
 * @licence MIT licence
 * 
 * Find out more about mm1 Technology:
 * Company: http://mm1-technology.de/
 * GitHub:  https://github.com/mm1technology/
 */

#ifndef _MQTTSN_H
#define _MQTTSN_H

#include <Arduino.h>
// #include <string.h>
// #include "gmx_nbiot.h"


#define MQTTSN_TOPIC_INVALID_ID         0

/*Available topics (use with Mqttsn_RegisterTopic())*/
#define MQTTSN_TOPIC_MEASUREMENT        "MES"

/*Avialable measurement types (use with Mqttsn_RegisterTopic())*/
#define MQTTSN_MEAS_TYPE_TEMPERATURE    '1'
#define MQTTSN_MEAS_TYPE_VOLTAGE        '2'
#define MQTTSN_MEAS_TYPE_ACCELERATION   '3'
#define MQTTSN_MEAS_TYPE_LIGHT          '4'
#define MQTTSN_MEAS_TYPE_HUMIDITY       '5'
#define MQTTSN_MEAS_TYPE_MOISTURE       '6'
#define MQTTSN_MEAS_TYPE_DISTANCE       '7'
#define MQTTSN_MEAS_TYPE_CURRENT        '8'
#define MQTTSN_MEAS_TYPE_SIGNALSTRENGTH '9'
#define MQTTSN_MEAS_TYPE_PRESSURE       'A'
#define MQTTSN_MEAS_TYPE_VOLUME         'B'
#define MQTTSN_MEAS_TYPE_WEIGHT         'C'
#define MQTTSN_MEAS_TYPE_FREQUENCY      'D'


/**
 * @brief Opens the connection to the cloud of things.
 * @param imsi IMSI of the used SIM card.
 * @param cotPassword Password to access the cloud of things.
 * @returns true if the connection could be successfully 
 * established; false otherwise.
 */
bool Mqttsn_Connect(String imsi, String cotPassword);


/**
 * @brief Registers a topic after connecting to the cloud of things.
 * @param topic A topic string.
 * @returns The assigned topic id; @ref MQTTSN_TOPIC_INVALID_ID if 
 * topic registration failed.
 * @note At the moment, only topic "MEAS" is supported.
 */
int Mqttsn_RegisterTopic(String topic, char valueType);


/**
 * @brief Publishes or updates a value of a measurement.
 * @param topicId Topic ID which was assigned at time of registration 
 * (see @ref Mqttsn_RegisterTopic)
 * @param measuredData Measured data to be published.
 * @returns true if the measured data could be published successfully, 
 * false otherwise.
 */
bool Mqttsn_PublishMeasurementData(int topicId, String measuredData);

#endif /*_MQTTSN_H*/

