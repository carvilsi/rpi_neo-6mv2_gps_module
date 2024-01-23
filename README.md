# NEO-6MV2

Interact with [neo-6mv2 GPS](https://components101.com/modules/neo-6mv2-gps-module) module for RPI

Here you have a description about the [NMEA messages](https://receiverhelp.trimble.com/alloy-gnss/en-us/NMEA-0183messages_MessageOverview.html)

And [here](https://aprs.gids.nl/nmea) more info about all the **$GPxxx** sentences. 

## NMEA messages implemented

- [GPGGA](http://aprs.gids.nl/nmea/#gga)
- [GLL](https://receiverhelp.trimble.com/alloy-gnss/en-us/NMEA-0183messages_GLL.html)
- [GSV](https://receiverhelp.trimble.com/alloy-gnss/en-us/NMEA-0183messages_GSV.html)

## Build

Clone the repo on your rpi(3) and then:

$ `make`

## Run

$ `./rpi_neo-6mv2_reader [serial]`

e.g: $ `./rpi_neo-6mv2_reader /dev/ttyAMA0`

### lib usage

At **src/neo-6mv2_reader.c** file the code is commented in order to have an example for usage.

## Tested on

- Raspberry Pi 3 Model B Rev 1.2 armv7l Linux6.1.21-v7+ ARMv7 rev 4
    - Raspbian GNU/Linux 11 (bullseye)
    - Raspbian GNU/Linux 12 (bookworm)

### Setup UART

#### RPi3

- Edit `/boot/config.txt` and add: `enable_uart=1`
- To disable bluetooth; also at `/boot/config.txt` add: `dtoverlay=disable-bt`
- To disable the console for serial:
```
sudo systemctl stop serial-getty@ttyS0.service
sudo systemctl disable serial-getty@ttyS0.service
```
    - Edit `/boot/cmdline.txt` and remove `console=serial0,115200`
- Reboot: $ `sudo reboot`

##### Connection RPI

| NEO-6MV2 |       RPi      |
|----------|----------------|
| Vcc 3.3v |  1 3v3 Power   |
|    Rx    |  8 GPIO 14 TxD |
|    Tx    | 10 GPIO 15 RxD |
|   GND    |  6 GND         |

Note: Rx conncetion between neo-6vm2 and RPi's pin 8 (GPIO 14 TxD) is not need it.

## TODOs

- Not working at **Raspberry Pi Zero W Rev 1.1 (Raspbian GNU/Linux 11 (bullseye) & Raspbian GNU/Linux 12 (bookworm))** armv6l Linux 6.1.21+ ARMv6-compatible rev 7 (v6l) (but hey! maybe it's just something going weird with my rpiZW ;)

### NMEA messages

- [GSA](https://receiverhelp.trimble.com/alloy-gnss/en-us/NMEA-0183messages_GSA.html)
- [RMC](https://receiverhelp.trimble.com/alloy-gnss/en-us/NMEA-0183messages_RMC.html)
- [VTG](https://aprs.gids.nl/nmea/#vtg)

---

Feedback from usage and contributions are very welcome.
Also if you like it, please leave a :star: I would appreciate it ;)

<3 & Hack the Planet!
