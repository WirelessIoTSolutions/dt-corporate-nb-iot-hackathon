#ifndef _temperature_h
#define _temperature_h

#include "Arduino.h"
#include "DTCoT.h"

extern bool registerTemperature(DTCoT::CoTCloud &cloud);
extern float sendTemperature(DTCoT::CoTCloud &cloud);
extern void checkTemperature();


#endif /*_temperature_h*/
