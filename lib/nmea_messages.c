#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "nmea_messages.h"

static void print_nmea_gga_message(nmea_gga *gga);
static void print_nmea_gll_message(nmea_gll *gll);
static void print_nmea_gsv_message(nmea_gsv *gsv);

void get_nmea_message_values(nmea_mssg *mssg, char **nmea_mssg_str, int *nmea_mssg_cntr)
{
        switch (mssg->type) {
                case GGA:
                        *nmea_mssg_str = GPGGA;
                        *nmea_mssg_cntr = GPGGA_CNTR;
                        break;
                case GLL:
                        *nmea_mssg_str = GPGLL;
                        *nmea_mssg_cntr = GPGLL_CNTR;
                        break;
                case GSV:
                        *nmea_mssg_str = GPGSV;
                        *nmea_mssg_cntr = GPGSV_CNTR;
                        break;
                default:
                        fprintf(stderr, "The nmea message type is unknown\n");
                        exit(EXIT_FAILURE);
        }
}

void print_nmea_message(nmea_mssg mssg)
{
        switch (mssg.type) {
                case GGA:
                        print_nmea_gga_message(mssg.gga);
                        break;
                case GLL:
                        print_nmea_gll_message(mssg.gll);
                        break;
                case GSV:
                        print_nmea_gsv_message(mssg.gsv);
                        break;
                default:
                        fprintf(stderr, "The nmea message type is unknown"
                                        " not possible to print it\n");
                        exit(EXIT_FAILURE);
        }
}

static void print_nmea_gga_message(nmea_gga *gga)
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

static void print_nmea_gsv_message(nmea_gsv *gsv)
{
        printf("id: %s\n"
               "ttl_nmbr_mssgs: %d\n"
               "mssg_nmbr: %d\n"
               "ttl_nmbr_svs_vis: %d\n"
               "sv_prn_nmbr: %d\n"
               "elvt: %d\n"
               "azmt: %d\n"
               "snr: %d\n"
               "sv_prn_nmbr_2: %d\n"
               "elvt_2: %d\n"
               "azmt_2: %d\n"
               "snr_2: %d\n"
               "sv_prn_nmbr_3: %d\n"
               "elvt_3: %d\n"
               "azmt_3: %d\n"
               "snr_3: %d\n"
               "sv_prn_nmbr_4: %d\n"
               "elvt_4: %d\n"
               "azmt_4: %d\n"
               "snr_4: %d\n"
               "chck_sum: %s\n"
               "data_valid: %s\n",
               gsv->id,
               gsv->ttl_nmbr_mssgs,
               gsv->mssg_nmbr,
               gsv->ttl_nmbr_svs_vis,
               gsv->sv_prn_nmbr,
               gsv->elvt,
               gsv->azmt,
               gsv->snr,
               gsv->sv_prn_nmbr_2,
               gsv->elvt_2,
               gsv->azmt_2,
               gsv->snr_2,
               gsv->sv_prn_nmbr_3,
               gsv->elvt_3,
               gsv->azmt_3,
               gsv->snr_3,
               gsv->sv_prn_nmbr_4,
               gsv->elvt_4,
               gsv->azmt_4,
               gsv->snr_4,
               gsv->chck_sum,
               gsv->data_valid ? "true" : "false");
}

static void print_nmea_gll_message(nmea_gll *gll) {
        printf("id: %s\n"
               "latitude: %f\n"
               "dir_lat: %s\n"
               "longitude: %f\n"
               "dir_long: %s\n"
               "utc_pstfx: %f\n"
               "chck_sum: %s\n"
               "data_valid: %s\n",
                gll->id,
                gll->latitude,
                gll->dir_lat,
                gll->longitude,
                gll->dir_long,
                gll->utc_pstfx,
                gll->chck_sum,
                gll->data_valid ? "true" : "false");
}

void get_nmea_gga_message(char *dt_itm, int itm, nmea_mssg *mssg, int chck_sum)
{
        switch (itm) {
                case 0:
                        mssg->gga->id = strdup(dt_itm);
                        break;
                case 1:
                        mssg->gga->utc_pstfx = atof(dt_itm);
                        break;
                case 2:
                        mssg->gga->latitude = atof(dt_itm);
                        break;
                case 3:
                        mssg->gga->dir_lat = strdup(dt_itm);
                        break;
                case 4:
                        mssg->gga->longitude = atof(dt_itm);
                        break;
                case 5:
                        mssg->gga->dir_long = strdup(dt_itm);
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
                        mssg->gga->alt_units = strdup(dt_itm);
                case 11:
                        mssg->gga->geoid_sep = atof(dt_itm);
                        break;
                case 12:
                        mssg->gga->geoid_sep_units = strdup(dt_itm);
                        break;
                case 13:
                        mssg->gga->chck_sum = strdup(dt_itm);
                        mssg->gga->data_valid = (int)strtol(dt_itm, NULL, 16) == 
                                chck_sum ? true : false;
                        break;
                default:
                        break;
        }
}

void get_nmea_gll_message(char *dt_itm, int itm, nmea_mssg *mssg, int chck_sum)
{
        switch (itm) {
                case 0:
                        mssg->gll->id = strdup(dt_itm);
                        break;
                case 1:
                        mssg->gll->latitude = atof(dt_itm);
                        break;
                case 2:
                        mssg->gll->dir_lat = strdup(dt_itm);
                        break;
                case 3:
                        mssg->gll->longitude = atof(dt_itm);
                        break;
                case 4:
                        mssg->gll->dir_long = strdup(dt_itm);
                        break;
                case 5:
                        mssg->gll->utc_pstfx = atof(dt_itm);
                        break;
                case 6:
                        mssg->gll->status = strdup(dt_itm);
                        break;
                case 7:
                        memmove(dt_itm, dt_itm + 1, strlen(dt_itm));
                        mssg->gll->chck_sum = strdup(dt_itm);
                        mssg->gll->data_valid = (int)strtol(dt_itm, NULL, 16) == 
                                chck_sum ? true : false;
                        break;
                default:
                        break;
        }
}

void get_nmea_gsv_message(char *dt_itm, int itm, nmea_mssg *mssg, int chck_sum)
{
        /*printf("%d: %s\n",itm, dt_itm);*/
        switch (itm) {
                case 0:
                        mssg->gsv->id = strdup(dt_itm);
                        break;
                case 1:
                        mssg->gsv->ttl_nmbr_mssgs = atoi(dt_itm);
                        break;
                case 2:
                        mssg->gsv->mssg_nmbr = atoi(dt_itm);
                        break;
                case 3:
                        mssg->gsv->ttl_nmbr_svs_vis = atoi(dt_itm);
                        break;
                case 4:
                        mssg->gsv->sv_prn_nmbr = atoi(dt_itm);
                        break;
                case 5:
                        mssg->gsv->elvt = atoi(dt_itm);
                        break;
                case 6:
                        mssg->gsv->azmt = atoi(dt_itm);
                        break;
                case 7:
                        mssg->gsv->snr = atoi(dt_itm);
                        break;
                case 8:
                        mssg->gsv->sv_prn_nmbr_2 = atoi(dt_itm);
                        break;
                case 9:
                        mssg->gsv->elvt_2 = atoi(dt_itm);
                        break;
                case 10:
                        mssg->gsv->azmt_2 = atoi(dt_itm);
                        break;
                case 11:
                        mssg->gsv->snr_2 = atoi(dt_itm);
                        break;
                case 12:
                        mssg->gsv->sv_prn_nmbr_3 = atoi(dt_itm);
                        break;
                case 13:
                        mssg->gsv->elvt_3 = atoi(dt_itm);
                        break;
                case 14:
                        mssg->gsv->azmt_3 = atoi(dt_itm);
                        break;
                case 15:
                        mssg->gsv->snr_3 = atoi(dt_itm);
                        break;
                case 16:
                        mssg->gsv->sv_prn_nmbr_4 = atoi(dt_itm);
                        break;
                case 17:
                        mssg->gsv->elvt_4 = atoi(dt_itm);
                        break;
                case 18:
                        mssg->gsv->azmt_4 = atoi(dt_itm);
                        break;
                case 19:
                        mssg->gsv->snr_4 = atoi(dt_itm);
                        break;
                case 20:
                        mssg->gsv->chck_sum = strdup(dt_itm);
                        mssg->gsv->data_valid = (int)strtol(dt_itm, NULL, 16) == 
                                chck_sum ? true : false;
                        break;
                default:
                        break;
        }
}

