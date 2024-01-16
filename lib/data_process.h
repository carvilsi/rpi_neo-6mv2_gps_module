#include <stdint.h>

#include "nmea_messages.h"

#define BUFF_SIZE 1024
#define DATA_DELIMITER ","

void process_buffer(uint8_t *buff, nmea_mssg *mssg);
void read_gps_data(int fd, nmea_mssg *mssg);

