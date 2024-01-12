# NEO-6MV2

Interact with [neo-6mv2 GPS](https://components101.com/modules/neo-6mv2-gps-module) module for RPI

Here you have a description about the [NMEA messages](https://receiverhelp.trimble.com/alloy-gnss/en-us/NMEA-0183messages_MessageOverview.html)

And [here](https://aprs.gids.nl/nmea) more info about all the **$GPxxx** sentences. 

## NMEA messages implemented

- [GPGGA](http://aprs.gids.nl/nmea/#gga)

## Connection RPI

| NEO-6MV2 | RPi |
|----------|-----|
| Vcc 3.3v |  1  |
|    Rx    |  8  |
|    Tx    | 10  |
|   GND    |  6  |

## Build

$ `gcc -Wall neo-6mv2_reader.c data_process.c interface_comm.c nmea_messages.c`

## Tested on

- Raspberry Pi 3 Model B Rev 1.2 (Raspbian GNU/Linux 11 (bullseye))


## TODOs

- Deal with checksums ;)

### NMEA messages

- [GSV](https://receiverhelp.trimble.com/alloy-gnss/en-us/NMEA-0183messages_GSV.html)
- [GSA](https://receiverhelp.trimble.com/alloy-gnss/en-us/NMEA-0183messages_GSA.html)
- [GLL](https://receiverhelp.trimble.com/alloy-gnss/en-us/NMEA-0183messages_GLL.html)
- [RMC](https://receiverhelp.trimble.com/alloy-gnss/en-us/NMEA-0183messages_RMC.html)
- [VTG](https://aprs.gids.nl/nmea/#vtg)

