#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "nmea_messages.h"

char *get_nmea_message_string(char *typ_nmea_mssg)
{
        char *str_nmea_message = NULL;

        if (strcmp(GGA, typ_nmea_mssg) == 0) {
                str_nmea_message = PGGGA;
        } else if (strcmp(GSV, typ_nmea_mssg) == 0) {
                str_nmea_message = PGGSV;
        } else if (strcmp(GSA, typ_nmea_mssg) == 0) {
                str_nmea_message = PGGSA;
        } else if (strcmp(GLL, typ_nmea_mssg) == 0) {
                str_nmea_message = PGGLL;
        } else if (strcmp(RMC, typ_nmea_mssg) == 0) {
                str_nmea_message = PGRMC;
        } else if (strcmp(VTG, typ_nmea_mssg) == 0) {
                str_nmea_message = PGVTG;
        } else {
                fprintf(stderr, "The provided type of NMEA message: %s\n" 
                                "is not valid\n", typ_nmea_mssg);
                exit(EXIT_FAILURE);
        }
        return str_nmea_message;
}

void print_nmea_gga_message(NMEA_GGA gga)
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
               /*"diff_gps: %s\n"*/
               /*"id_station: %d\n"*/
               "chck_sum: %s\n"
               "data_valid: %s\n",
                gga.id,
                gga.utc_pstfx,
                gga.latitude,
                gga.dir_lat,
                gga.longitude,
                gga.dir_long,
                gga.qlty,
                gga.sat_num,
                gga.hdop,
                gga.alt,
                gga.alt_units,
                gga.geoid_sep,
                gga.geoid_sep_units,
                /*gga.diff_gps,*/
                /*gga.id_station,*/
                gga.chck_sum,
                gga.data_valid ? "true" : "false");
}

void get_nmea_gga_message(char *dt_itm, int itm, NMEA_GGA *gpgga, int chck_sum)
{
        switch (itm) {
                case 0:
                        gpgga->id = dt_itm;
                        break;
                case 1:
                        gpgga->utc_pstfx = atof(dt_itm);
                        break;
                case 2:
                        gpgga->latitude = atof(dt_itm);
                        break;
                case 3:
                        gpgga->dir_lat = dt_itm;
                        break;
                case 4:
                        gpgga->longitude = atof(dt_itm);
                        break;
                case 5:
                        gpgga->dir_long = dt_itm;
                        break;
                case 6:
                        gpgga->qlty = atoi(dt_itm);
                        break;
                case 7:
                        gpgga->sat_num = atoi(dt_itm);
                        break;
                case 8:
                        gpgga->hdop = atof(dt_itm);
                        break;
                case 9:
                        gpgga->alt = atof(dt_itm);
                        break;
                case 10:
                        gpgga->alt_units = dt_itm;
                case 11:
                        gpgga->geoid_sep = atof(dt_itm);
                        break;
                case 12:
                        gpgga->geoid_sep_units = dt_itm;
                        break;
                case 13:
                        gpgga->chck_sum = dt_itm;
                        gpgga->data_valid = (int)strtol(dt_itm, NULL, 16) == 
                                chck_sum ? true : false;
                        break;
                default:
                        break;
        }
}

