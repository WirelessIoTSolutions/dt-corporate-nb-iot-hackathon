
#ifndef gps_data_h
#define gps_data_h

#include "Arduino.h"
#include "DTCoT.h"


union coord {
  float fl;
  uint32_t u32;
  uint8_t u8[4];
};


typedef struct {
  coord longitude;
  coord latitude;
} gps_coord_t;


/*EmbLib support*/
extern bool registerGPS(DTCoT::CoTCloud &cloud);
extern bool sendGPS(DTCoT::CoTCloud &cloud);
extern void checkGPS(void);


#endif /*gps_data_h*/

