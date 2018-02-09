
#ifndef gps_data_h
#define gps_data.h

union coord {
  float fl;
  uint32_t u32;
  uint8_t u8[4];
};


typedef struct {
  coord longitude;
  coord latitude;
} gps_coord_t;

char* gps_to_mqtt(gps_coord_t coord, char *buff);
char* byte_to_hex(char byt,char *buff);

#endif


