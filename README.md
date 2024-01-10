# NEO-6MV2

check: [GPGGA](http://aprs.gids.nl/nmea/#gga)

## Connection RPI

| NEO-6MV2 | RPi |
|----------|-----|
| Vcc 3.3v |  1  |
|    Rx    |  8  |
|    Tx    | 10  |
|   GND    |  6  |

## Build

$ `gcc -o gps_reader gps_reader.c`


