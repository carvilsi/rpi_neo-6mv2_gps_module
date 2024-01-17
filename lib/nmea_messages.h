#include <stdbool.h>

#define GPGGA "$GPGGA"
#define GPGSV "$GPGSV"
#define GPGSA "$GPGSA"
#define GPGLL "$GPGLL"
#define GPRMC "$GPRMC"
#define GPVTG "$GPVTG"

#define GPGGA_CNTR 13
#define GPGLL_CNTR 7
#define GPGSV_CNTR 7 

#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

// $GPGGA
// check: https://aprs.gids.nl/nmea/#gga
typedef struct {
        char *id; // Message ID $GPGGA
        float utc_pstfx; // UTC of position fix
        float latitude;
        char *dir_lat; // Direction of latitude N: North S: South
        float longitude;
        char *dir_long; // Direction of longitude E: East W: West
        int qlty; // GPS Quality indicator 
        int sat_num; // Number of SVs in use, range from 00 through to 24+
        float hdop;
        float alt; // Orthometric height (MSL reference)
        char *alt_units; // M: unit of measure for orthometric height is meters
        float geoid_sep; // Geoid separation
        char *geoid_sep_units; // M: geoid separation measured in meters
        //char *diff_gps; // not used in module
        //int id_station; // not used in module
        char *chck_sum; // The checksum value of the data
        bool data_valid; // if the checksum is valid
}nmea_gga;

//$GPGLL
//check: https://receiverhelp.trimble.com/alloy-gnss/en-us/NMEA-0183messages_GLL.html
typedef struct {
        char *id; //Message ID $GPGLL
        float latitude; // Latitude in dd mm,mmmm format (0-7 decimal places)
        char *dir_lat; // Direction of latitude N: North S: South
        float longitude; // Longitude in ddd mm,mmmm format (0-7 decimal places)
        char *dir_long; // Direction of longitude E: East W: West
        float utc_pstfx; // UTC of position in hhmmss.ss format
        char *status; // A: valid data; V: invalid data;
        char *chck_sum; // The checksum value of the data
        bool data_valid; // if the checksum is valid
}nmea_gll; 

//$GPGSV
//check: https://receiverhelp.trimble.com/alloy-gnss/en-us/NMEA-0183messages_GSV.html
//XXX: not fully implemented, missing data about 2nd, 3th and 4th SVs and checksum
typedef struct {
        char *id; //0 Message ID $GPGSV
        int ttl_nmbr_mssgs; //1 Total number of messages of this type in this cycle
        int mssg_nmbr; //2 Message number
        int ttl_nmbr_svs_vis; //3 Total number of SVs visible
        int sv_prn_nmbr; //4 SV PRN number
        int elvt; //5 Elevation, in degrees, 90° maximum
        int azmt; //6 Azimuth, degrees from True North, 000° through 359°
        int snr; //7 SNR, 00 through 99 dB (null when not tracking)
}nmea_gsv;

typedef struct {
        enum {
                GGA,
                GLL,
                GSV
        }type;
        union {
                nmea_gga *gga;
                nmea_gll *gll;
                nmea_gsv *gsv;
        };
}nmea_mssg;

#endif /* STRUCT_H_INCLUDED */

void get_nmea_gga_message(char *dt_itm, int itm, nmea_mssg *mssg, int chck_sum);
void get_nmea_gll_message(char *dt_itm, int itm, nmea_mssg *mssg, int chck_sum);
void get_nmea_gsv_message(char *dt_itm, int itm, nmea_mssg *mssg, int chck_sum);
void get_nmea_message_values(nmea_mssg *mssg, char **nmea_mssg_str, int *nmea_mssg_cntr);
void print_nmea_message(nmea_mssg mssg);
