#include <stdint.h>

#define BUFF_SIZE 1024
#define DATA_DELIMITER ","

void process_buffer(uint8_t *buff);
void read_gps_data(int fd);

