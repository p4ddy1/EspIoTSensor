## Local build configuration
## Parameters configured here will override default and ENV values.
## Uncomment and change examples:

## Add your source directories here separated by space
# MODULES = app
EXTRA_INCDIR = include

ENABLE_GDB = 0

## ESP_HOME sets the path where ESP tools and SDK are located.
## Windows:
# ESP_HOME = c:/Espressif

## MacOS / Linux:
# ESP_HOME = /opt/ESP8266/esp-open-sdk

## SMING_HOME sets the path where Sming framework is located.
## Windows:
# SMING_HOME = c:/tools/sming/Sming 

## MacOS / Linux
# SMING_HOME = /opt/ESP8266/Sming/Sming

## COM port parameter is reqruied to flash firmware correctly.
## Windows: 
COM_PORT = COM6

## MacOS / Linux:
# COM_PORT = /dev/ttyUSB0

## Com port speed
COM_SPEED	= 115200

## Configure flash parameters (for ESP12-E and other new boards):
SPI_MODE = dio

## SPIFFS options
DISABLE_SPIFFS = 1
# SPIFF_FILES = files
ENABLE_SSL = 1


