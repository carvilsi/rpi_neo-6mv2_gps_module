#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "data_process.h"

bool RAW = false;

static void parse_data(char *dt_ln, int chck_sum, nmea_mssg *mssg)
{
        int cntr = 0;
        char *nmea_mssg_str = NULL;
        int nmea_mssg_cntr;
        get_nmea_message_values(mssg, &nmea_mssg_str, &nmea_mssg_cntr);
        char *nmea_mssg_typ;
        char *dt_itm = strtok(dt_ln, DATA_DELIMITER);
        while (dt_itm != NULL) {
                if (cntr == 0) {
                        if (strcmp(dt_itm, nmea_mssg_str) == 0) {
                                nmea_mssg_typ = nmea_mssg_str;
                        } else {
                                nmea_mssg_typ = NULL;
                        }
                }
                
               if (nmea_mssg_typ != NULL && strcmp(nmea_mssg_typ, nmea_mssg_str) == 0) {
                       switch (mssg->type) {
                               case GGA:
                                        get_nmea_gga_message(dt_itm, cntr, mssg, chck_sum);
                                        //TODO: We can remove this from here...
                                        if (cntr == nmea_mssg_cntr)
                                                print_nmea_gga_message(mssg->gga);
                                        break;
                                default:
                                        fprintf(stderr, "Unkown nmea message type\n");
                       }
                }
                
                cntr++;
                dt_itm = strtok(NULL, DATA_DELIMITER);
        }
}

// XXX: Not super proud about check sum approach
void process_buffer(uint8_t *buff, nmea_mssg *mssg)
{
        int cntr = 0;
	int i = 0;
        char dt_ln[100];
        bool nw = false;
        int chck_sum;
        bool dt_chck_sum = true;

	for (; i < BUFF_SIZE; i++) {
                uint8_t data = buff[i];
                if (RAW)
                        printf("%c", data);
		
                if (data == '$') {
                        nw = true;
                        cntr = 0;
                        memset(dt_ln, 0, sizeof(dt_ln));
                        chck_sum = 0;
                        dt_chck_sum = true;
                }
		if (data == '\n') { 
                        nw = false;
                        parse_data(dt_ln, chck_sum, mssg);
                }
                if (nw) {
                        if (data == '*')
                                dt_chck_sum = false;
                         if (data != '*'  && 
                            data != '$' && data != ' ' &&
                            data != '\n') {
                                 if (dt_chck_sum) 
                                         chck_sum = chck_sum ^ data;
                        }

                        if (data != '*' ) {
                                dt_ln[cntr] = data;
                                cntr++;
                        }
                } 
	}
}

void read_gps_data(int fd, nmea_mssg *mssg)
{
	uint8_t buff[BUFF_SIZE];
        for (;;) {
		read(fd, buff, sizeof buff);
		process_buffer(buff, mssg);
        }
}

