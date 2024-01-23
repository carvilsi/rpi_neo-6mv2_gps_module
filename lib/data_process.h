#include <stdio.h>

#include "nmea_messages.h"

#define BUFF_SIZE 1024
#define DATA_DELIMITER ","

void read_gps_data(FILE *fd, nmea_mssg *mssg);

