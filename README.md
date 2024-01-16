# NEO-6MV2

Interact with [neo-6mv2 GPS](https://components101.com/modules/neo-6mv2-gps-module) module for RPI

Here you have a description about the [NMEA messages](https://receiverhelp.trimble.com/alloy-gnss/en-us/NMEA-0183messages_MessageOverview.html)

And [here](https://aprs.gids.nl/nmea) more info about all the **$GPxxx** sentences. 

## NMEA messages implemented

- [GPGGA](http://aprs.gids.nl/nmea/#gga)
- [GLL](https://receiverhelp.trimble.com/alloy-gnss/en-us/NMEA-0183messages_GLL.html)

## Connection RPI

| NEO-6MV2 |       RPi      |
|----------|----------------|
| Vcc 3.3v |  1 3v3 Power   |
|    Rx    |  8 GPIO 14 TxD |
|    Tx    | 10 GPIO 15 RxD |
|   GND    |  6 GND         |

Note: Rx conncetion between neo-6vm2 and RPi's pin 8 (GPIO 14 TxD) is not need it.

## Build

$ `gcc -Wall neo-6mv2_reader.c data_process.c interface_comm.c nmea_messages.c`

## Tested on

- Raspberry Pi 3 Model B Rev 1.2 (Raspbian GNU/Linux 11 (bullseye)) armv7l Linux6.1.21-v7+ ARMv7 rev 4

## TODOs

- Not working at **Raspberry Pi Zero W Rev 1.1 (Raspbian GNU/Linux 11 (bullseye))** armv6l Linux 6.1.21+ ARMv6-compatible rev 7 (v6l)

### NMEA messages

- [GSV](https://receiverhelp.trimble.com/alloy-gnss/en-us/NMEA-0183messages_GSV.html)
- [GSA](https://receiverhelp.trimble.com/alloy-gnss/en-us/NMEA-0183messages_GSA.html)
- [RMC](https://receiverhelp.trimble.com/alloy-gnss/en-us/NMEA-0183messages_RMC.html)
- [VTG](https://aprs.gids.nl/nmea/#vtg)

---

Feedback from usage and contributions are very welcome.
Also if you like it, please leave a :star: I would appreciate it ;)

<3 & Hack the Planet!
