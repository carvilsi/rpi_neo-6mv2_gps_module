#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "nmea_messages.h"

char *get_nmea_message_string(nmea_mssg *mssg)
{
        char *str_nmea_message = NULL;

        switch (mssg->msg_type) {
                case GGA:
                        str_nmea_message = PGGGA;
                        break;
                case GLL:
                        str_nmea_message = PGGLL;
                        break;
                default:
                        fprintf(stderr, "The nmea message type is unknown\n");
                        exit(EXIT_FAILURE);
        }

        return str_nmea_message;
}

void print_nmea_gga_message(nmea_gga *gga)
{
        printf("id: %s\n"
               "utc_pstfx: %f\n"
               "latitude: %f\n"
               "dir_lat: %s\n"
               "longitude: %f\n"
               "dir_long: %s\n"
               "qlty: %d\n"
               "sat_num: %d\n"
               "hdop: %f\n"
               "alt: %f\n"
               "alt_units: %s\n"
               "geoid_sep: %f\n"
               "geoid_sep_units: %s\n"
               "chck_sum: %s\n"
               "data_valid: %s\n",
                gga->id,
                gga->utc_pstfx,
                gga->latitude,
                gga->dir_lat,
                gga->longitude,
                gga->dir_long,
                gga->qlty,
                gga->sat_num,
                gga->hdop,
                gga->alt,
                gga->alt_units,
                gga->geoid_sep,
                gga->geoid_sep_units,
                gga->chck_sum,
                gga->data_valid ? "true" : "false");
}

void get_nmea_gga_message(char *dt_itm, int itm, nmea_mssg *mssg, int chck_sum)
{
        switch (itm) {
                case 0:
                        mssg->gga->id = dt_itm;
                        break;
                case 1:
                        mssg->gga->utc_pstfx = atof(dt_itm);
                        break;
                case 2:
                        mssg->gga->latitude = atof(dt_itm);
                        break;
                case 3:
                        mssg->gga->dir_lat = dt_itm;
                        break;
                case 4:
                        mssg->gga->longitude = atof(dt_itm);
                        break;
                case 5:
                        mssg->gga->dir_long = dt_itm;
                        break;
                case 6:
                        mssg->gga->qlty = atoi(dt_itm);
                        break;
                case 7:
                        mssg->gga->sat_num = atoi(dt_itm);
                        break;
                case 8:
                        mssg->gga->hdop = atof(dt_itm);
                        break;
                case 9:
                        mssg->gga->alt = atof(dt_itm);
                        break;
                case 10:
                        mssg->gga->alt_units = dt_itm;
                case 11:
                        mssg->gga->geoid_sep = atof(dt_itm);
                        break;
                case 12:
                        mssg->gga->geoid_sep_units = dt_itm;
                        break;
                case 13:
                        mssg->gga->chck_sum = dt_itm;
                        mssg->gga->data_valid = (int)strtol(dt_itm, NULL, 16) == 
                                chck_sum ? true : false;
                        break;
                default:
                        break;
        }
}

