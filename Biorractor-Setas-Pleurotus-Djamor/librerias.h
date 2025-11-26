/////////////[DIMMER AC]////////////
#include <GyverDimmer.h>

////////[Memoria EEPROM]////////
#include <Preferences.h>

////////[Wifi Manager]////////
#include <WiFiManager.h> 
WiFiManager wm;
 
////////[BME680]////////
#include "bsec.h"

////////[Telegram Bot]////////
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h> 
#include <ArduinoJson.h>

////////[Google]////////
#include <HTTPClient.h>

/////////////[PANTALLA SPI]////////////
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

/////////////[NEOPIXEL]////////////
#include <Adafruit_NeoPixel.h>

#include "variables.h"
#include "checkSensor.h"
#include "registroGoogle.h"
#include "telegram_Bot.h"
#include "telegram_Bot_2.h"
#include "online_GraficosXY.h"

#include "funciones_Extra.h"

#include "ajuste_PID.h"
#include "ajuste_Variables.h"
