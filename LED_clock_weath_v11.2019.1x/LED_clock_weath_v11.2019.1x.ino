/*_______By IvanUA_____________________________
 Піни LED------NodeMCU  1.0                    | 
       DataIn__________________D7/GPIO 13      |
       LOAD/CS_________________D8/GPIO 15      |
       CLK_____________________D5/GPIO 14      |
 Кнопка________________________D0/GPIO 16      |
 Бaзер_________________________D6/GPIO 12      |
 DS18B20_______________________D3/GPIO 0       |
 Si7021/BMP/BME280/DS3231 DA___D2/GPIO 4       | 
 Si7021/BMP/BME280/DS3231 CL___D1/GPIO 5       |
 GND - FotoRezistor ___________A0              |
 +3,3 - rezistor 2-100k _______A0              |
 DHT11/22______________________D4/GPIO 2       |
______________________________________________*/
#include <Wire.h>
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include <OneWire.h>
#include <PubSubClient.h>
#include <ArduinoOTA.h>
#include <ESP8266HTTPUpdateServer.h>
#include "Adafruit_Si7021.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_BMP085.h>
#include "BlueDot_BME280.h"
#include <SimpleDHT.h>
#include <ESP8266HTTPClient.h>
ESP8266HTTPUpdateServer httpUpdater;
WiFiClient ESPclient;
PubSubClient MQTTclient(ESPclient);
ESP8266WebServer server(80);                                                            // Веб сервер
File fsUploadFile;
IPAddress apIP(192, 168, 4, 1);
#include "P_js.h"
#include "P_css.h"
#include "P_index.h"
#include "P_time.h"
#include "P_weath.h"
#include "P_setup.h"
#include "P_help.h"
#include "P_mqtt.h"

// =====================================================================================
String ssid = "n104";                                                         // Назва локального WiFi
String password = "frankfurt!";                                               // Пароль локального WiFi
String ssidAP      = "WiFi-Clock";                                            // Назва точки доступу
String passwordAP  = "";                                                      // Пароль точки доступу
boolean weatherHost = 0;
String weatherHost0 = "api.weatherbit.io";
String weatherHost1 = "api.openweathermap.org";
String weatherKey0  = "11111111111111111111111111111111";
String weatherKey1  = "22222222222222222222222222222222";
String cityID0      = "Frankfurt";
String cityID1      = "2925533";
String weatherLang = "ua";                                                    // Мова отримання прогнозу погоди
String location_name = "";
String location_region = "";
String location_country = "";
String location_localtime = "";
float  location_temp;
float  location_app_temp;
int    location_rh;
float  location_pres;
float  location_wind_spd;
String location_wind_cdir_full = "";
String location_sunrise = "";
String location_sunset = "";
int    location_clouds;
int    location_vis;
int    location_uv;
String location_weather_description = "";
// ----------змінні для роботи з mqtt сервером
char mqtt_server[21] = "m13.cloudmqtt.com";                                             // Имя сервера MQTT
int  mqtt_port = 13011;                                                                 // Порт для подключения к серверу MQTT
char mqtt_user[25] = "aaaaaaaaaaaa";
char mqtt_pass[25] = "bbbbbbbbbbbb";                                               // Пароль от сервера MQTT
char mqtt_name[25] = "ESP-chasy";
char mqtt_sub_inform[25] = "Inform/mess";
char mqtt_sub[25] = "Ulica/temp";
char mqtt_pub_temp[25] = "ESP/temp";
char mqtt_pub_tempUl[25] = "ESP/tempUl";
char mqtt_pub_hum[25] = "ESP/hum";
char mqtt_pub_press[25] = "ESP/press";
char mqtt_pub_alt[25] = "ESP/alt";
bool mqttOn = true;
// --------------------------------------------
String uuid = "33333333333333333333333333333333";
String api_key = "4444444444444";
int sensors_ID0 = 88733;
int sensors_ID1 = 88459;
int sensors_ID2 = 0;
// =====================================================================================
bool printCom = true;
#define MAX_DIGITS 16
byte NUM_MAX = 4;
byte fontCLOCK = 0;      // 0-крупный, 1-крупный цифровой, 2-полу жирный, 3-полу жирный цифровой, 4-обычный, 5-обычный цифровой, 6-узкий, 7-узкий цифровой. 
byte aliData = 8;
byte volBrightnessD  = 8;
byte volBrightnessN  = 2;
bool volBrightnessAuto = 0;
byte levelBridhtness = 0;
byte timeDay = 5;
byte timeNight = 24;
int rotate = 90;
byte timeScrollStart = 6;
byte timeScrollStop = 23;
byte timeScrollSpeed = 20;
byte lang = 0;             // 0-ukr, 1-rus, 2-pol,  3-czech, 4-de, 5-en
#define DIN_PIN   13                                                                    //GPIO 13 / D7
#define CS_PIN    15                                                                    //GPIO 15 / D8
#define CLK_PIN   14                                                                    //GPIO 14 / D5
#define buzzerPin 12                                                                    //GPIO 12 / D6
bool buzzerSet = 1;
#define brightPin A0
OneWire  ds(0);                                                                         // DS18B20 подключен к 10 пину (резистор на 4.7к обязателен)
int pinDHT = 2;
SimpleDHT11 dht11;
SimpleDHT22 dht22;
#define BUT_PIN   16
// ----------
#include "max7219.h"
#include "fonts.h"
boolean WIFI_connected = false;
// ---------- Настройка оновлення часу
IPAddress timeServerIP;
String ntpServerName = "ntp3.time.in.ua";
const int NTP_PACKET_SIZE = 48;
byte packetBuffer[NTP_PACKET_SIZE];
WiFiUDP udp;
unsigned int localPort = 2390;
unsigned long epochNM;
static const uint8_t monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};        // Кількість днів у місяцях
#define LEAP_YEAR(Y) (((1970+Y)>0) && !((1970+Y)%4) && (((1970+Y)%100)||!((1970+Y)%400)))   // Високосні літа
String weatherMain = "";
String weatherDescription = "";
String weatherLocation = "";
String country;
String tempz;
int clouds;
int windDeg;
float windSpeed;
String dw, _month;
String jsonConfig = "{}";
String jsonTime = "{}";
// ---------- Змінні для роботи локального годинника
float timeZone = 1.0;                                                                       //  часовий пояс
bool isDayLightSaving = true;
long localEpoc = 0;
long localMillisAtUpdate = 0;
int hour=2, minute=40, second=42, month=4, day=6, dayOfWeek=6, year=2018;
int g_hour, g_minute, g_second, g_month=1, g_day, g_dayOfWeek, g_year;
bool statusUpdateNtpTime = 0;                                                               // якщо не "0" - то останнє оновленя часу було вдалим
String y, mon, wd, d, h, m, s, mes;
uint8_t hourTest[3], minuteTest[3];
int secFr, lastSecond, lastMinute;
String date;
byte kuOn = 7;
byte kuOff = 23;
bool clockNight=0;
// ----------
String cityName;
//int cityId;
String weatherString;
String weatherStringZ;
// ----------
byte dig[MAX_DIGITS] = {0};
byte digold[MAX_DIGITS] = {0};
byte digtrans[MAX_DIGITS] = {0};
int dx = 0;
int dy = 0;
byte del = 0;
int updateOTA = 1;
bool outForecast = true;
int updateForecast = 0;
int updateForecasttomorrow = 0;
float t0 = 0.0;    // температура в  доме  со знаком и плавающей запятой
int t1 = 85;    // температура в  доме  целая беззнаковая часть
int t2 = 0;     // температура в  доме  дробная часть
int t3 = 85;    // температура на улице целая беззнаковая часть
int t4 = 0;     // температура на улице дробная часть
float t5 = 0.0;    // температура на улице со знаком и плавающей запятой
byte h1 = 0;
byte h2 = 0;
byte h3 = 0;
int tMqtt3 = 85;
int tMqtt4 = 0;
float tMqtt5 = 0.0;
float tempNM = 0.0;
byte humidity;                        // влажность для прогноза
float pressure;                       // давление для прогноза
float temp;                           // температура для прогноза
float tempDs18b20;                    // температура с датчика DS18B20
BlueDot_BME280 bme;
float tempBme = 0;
float humBme = 0;
float pressBme = 0;
float altBme = 0;
Adafruit_BMP280 bmp;
Adafruit_BMP085 bmp180;
float tempBmp = 0;
float pressBmp = 0;
float altBmp = 0;
bool bmp280 = false;
bool BMP180 = false;
bool bme280 = false;
float tempDht = 0;
float humiDht = 0;
Adafruit_Si7021 sensor = Adafruit_Si7021();
float hum = 0;
float humSi7021 = 0;
float celsiusSi7021 = 0;
bool si7021 = false;
float corrTempD = -3.3;
float corrTempU = -1.5;
float corrHumi  = 0;
int   corrPress = -21;
byte sensorDom = 4;          //NONE = 0, DS18B20 = 1, Si7021 = 2, BMP280 = 3, BME280 = 4, DHT = 5,  MQTT = 6;
byte sensorUl = 7;           //NONE = 0, DS18B20 = 1, Si7021 = 2, BMP280 = 3, BME280 = 4, DHT = 5,  MQTT = 6; NMon = 7;
byte sensorHumi = 4;         //NONE = 0, NONE    = 1, Si7021 = 2, NONE   = 3, BME280 = 4, DHT = 5,  NONE = 6;
byte sensorPrAl = 4;         //NONE = 0, NONE    = 1, NONE   = 2, BMP280 = 3, BME280 = 4, NONE = 5, NONE = 6;
String tMes, tNow, tCurr, tPress, tSpeed, tMin, tTom, tYour, tPoint, tWeatrNot, tWeatrTN;
String tJanuary, tFebruary, tMarch, tApril, tMay, tJune, tJuly, tAugust, tSeptember, tOctober, tNovember, tDecember;
String tMonday, tTuesday, tWednesday, tThursday, tFriday, tSaturday, tSunday;
bool alarm_stat=0;
bool alarm_hold=0;
byte alarm_numer=255;
byte alarme[5][3]{{12, 30, 0},{7, 15, 0},{22, 55, 0},{0, 30, 0},{0, 0, 0}}; //1-часы, 2-минуты, 3-откл(0)/1раз(11)/пон-пят(8)/пон-сб(9)/сб-вс(10)/вс(1)/пон(2)/вто(3)/сре(4)/чет(5)/пят(6)/сб(7)/всегда(12)
byte memory_hour_start=9;
byte memory_hour_end=23;
byte m_date=0;
byte memory_date[9][2]{{1, 1},{2, 1},{6, 1},{7, 1},{13, 1},{19, 1},{8, 3},{1, 5},{1, 9}}; //1-день, 2-месяц
char memory_date_mes0[51] = "Новый Год!!!";
char memory_date_mes1[51] = "ПослеНовыйГод(((";
char memory_date_mes2[51] = "Ночь перед Рождеством";
char memory_date_mes3[51] = "Рождество";
char memory_date_mes4[51] = "Старый Новый Год!";
char memory_date_mes5[51] = "Крещение";
char memory_date_mes6[51] = "День цветов";
char memory_date_mes7[51] = "День шашлыка)))";
char memory_date_mes8[51] = "Отведи ребенка в школу";
bool firstStart=0;
byte amountNotStarts=0;
String jsonLine = "";
bool rtcStat = false;
int rtcAddr = 0x68;
int hour_rtc, minute_rtc, second_rtc, month_rtc, day_rtc, dayOfWeek_rtc, year_rtc;
#include "rtc.h"
byte errorRTC;
//======================================================================================
void setup(){
  Wire.begin();
  Serial.begin(115200);
  if(printCom) Serial.println("");
  pinMode(BUT_PIN, INPUT);
  digitalWrite(BUT_PIN, LOW);
  delay(500);
  initMAX7219();
  sendCmdAll(CMD_SHUTDOWN, 1);
  sendCmdAll(CMD_INTENSITY, 1);
  SPIFFS.begin();
  loadConfig();
  loadTime();
  Wire.beginTransmission(0x67);
  errorRTC = Wire.endTransmission();
  if(errorRTC==0){
    rtcAddr = 0x67;
    if(printCom) Serial.println("YES!!! find RTC module addr: 0x67!");
  } else {
    Wire.beginTransmission(0x68);
    errorRTC = Wire.endTransmission();
    if(errorRTC==0){
      rtcAddr = 0x68;
      if(printCom) Serial.println("YES!!! find RTC module addr: 0x68!");
    } else rtcStat = false;
  }
  if(rtcStat){
    if(printCom) Serial.println("RTC START");
    getRTCDateTime();
    hour=hour_rtc;
    minute=minute_rtc;
    second=second_rtc;
    day=day_rtc;
    month=month_rtc;
    year=year_rtc;
    dayOfWeek=dayOfWeek_rtc;
    if(printCom){
      Serial.println("RTC update: "+String(hour)+":"+String(minute)+":"+String(second)+"    "+String(day)+"."+String(month)+"."+String(year)+" D="+String(dayOfWeek));
    }
  } else if(printCom) Serial.println("RTC module off!");
  // ------------------
  sensorsDht();
  if(bmp.begin()) {
    if(printCom) Serial.println("YES!!! find BMP280 sensor!");
    bmp280 = true;
    sensorsBmp();
  } else if(printCom) Serial.println("Did not find BMP280 sensor!");
  if(bmp180.begin()) {
    if(printCom) Serial.println("YES!!! find BMP180 sensor!");
    BMP180 = true;
    sensorsBmp();
  } else if(printCom) Serial.println("Did not find BMP180 sensor!");
  bme.parameter.communication = 0;                            //Подключение сенсора по I2C 
  bme.parameter.I2CAddress = 0x76;                            //I2C Адрес сенсора или 0x77
  bme.parameter.sensorMode = 0b11;                            //0b00 спящий режим измерения не выполняются, 0b01: выполняется одно измерение, 0b11: датчик постоянно измеряет
  bme.parameter.IIRfilter = 0b100;                            //высокое значение коэффициента означает меньше шума, но измерения также менее чувствительны 0b000-0(off), 0b001-2, 0b010-4, 0b011-8, 0b100-16 (default value)
  bme.parameter.humidOversampling = 0b100;                    //коэффициент избыточной дискретизации для измерений влажности 0b000-0 (фильтр откл), 0b001-1, 0b010-2, 0b011-4, 0b100-8, 0b101-16 (максимум)
  bme.parameter.tempOversampling = 0b101;                     //коэффициент передискретизации для измерения температуры 0b000-0 (фильтр откл), 0b001-1, 0b010-2, 0b011-4, 0b100-8, 0b101-16 (максимум)
  bme.parameter.pressOversampling = 0b101;                    //коэффициент избыточной дискретизации для измерений давления. Для измерений высоты более высокий коэффициент обеспечивает более стабильные значения
  bme.parameter.pressureSeaLevel = 1013.25;                   //текущее давление, скорректированное для уровня моря 1013.25 hPa. Для точных измерений высоты
  bme.parameter.tempOutsideCelsius = 15;                      //средняя температура снаружи 15°C
  bme.parameter.tempOutsideFahrenheit = 59;                   //средняя температура снаружи 59°F
  if(bme.init() == 0x60) {
    if(printCom) Serial.println("YES!!! find BME280 sensor!");
    bme280 = true;
    sensorsBme();
  } else if(printCom) Serial.println("Did not find BME280 sensor!");
  if (sensor.begin()) {
    if(printCom) Serial.println("YES!!! find Si7021 sensor!");
    si7021 = true;
    sensorsSi7021();
  } else if(printCom) Serial.println("Did not find Si7021 sensor!");
  server_init();
// ----------
  localMillisAtUpdate = millis();
  localEpoc = (hour * 60 * 60 + minute * 60 + second);
  udp.begin(localPort);
  pinMode(buzzerPin, OUTPUT);
// ---------- Перемикаємо мови в залежності від вибраної
  if (lang == 0) ukrText();
  else if (lang == 1) rusText();
  else if (lang == 2) polText();
  else if (lang == 3) czText();
  else if (lang == 4) deText();
  else if (lang == 5) enText();
  bip();
// ---------- Підключення до WiFi
  wifiConnect();
// ***********  OTA SETUP
  if(updateOTA) {
    ArduinoOTA.setPort(8266);
    ArduinoOTA.setHostname("ESP"); 
    ArduinoOTA.onEnd([](){ESP.restart();});
    ArduinoOTA.onError([](ota_error_t error){Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR && printCom) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR && printCom) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR && printCom) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR && printCom) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR && printCom) Serial.println("End Failed");
      ESP.restart(); 
    });
    ArduinoOTA.begin();
  }
  if(WiFi.status() == WL_CONNECTED) {
    if(outForecast){
      if(!weatherHost) {
        getWeatherData0();
        getWeatherDataz0();
      } else {
        getWeatherData1();
        getWeatherDataz1();
      }
    }
  }
// ---------- MQTT client
  MQTTclient.setServer(mqtt_server, mqtt_port);
  MQTTclient.setCallback(callback);
  MQTTclient.connect(mqtt_name);
  MQTTclient.subscribe(mqtt_sub_inform);
  MQTTclient.subscribe(mqtt_sub);

  if(sensorUl==7)getNarodmon();
}
//======================================================================================
void callback(char* topic, byte* payload, unsigned int length) { // получаем знаковое число с десятичной плавающей запятой
  if(!mqttOn) return;
  if(String(topic) == mqtt_sub_inform) {
    String Text = "        ";
    for(int i = 0; i < length; i++) {
      Text += ((char)payload[i]);
    }
    Text += "        ";
    for(int i = 0; i < 4; i++) {
      bip();
    }
    printStringWithShift(Text.c_str(), 30);
    if(printCom) {
      printTime();
      Serial.println("MQTT Incoming Message: " + Text);
    }
  }
  if(String(topic) == mqtt_sub) {
    tMqtt3 = 0;
    tMqtt4 = 0;
    tMqtt5 = 0.0;
    if((payload[0] >= 48 && payload[0] < 58) || payload[0] == 45) { // в payload[0] - хранится первый полученный символ. 48, 58 и 45 - это коды знаков можете их посмотреть в fontUA_RU_PL_DE[]
      if(payload[0] == 45) {                                        // если первый символ = "-"
        if(payload[1] >= 48 && payload[1] < 58) {                   //  здесь проверяем уже второй символ что он является числом...
          tMqtt3 = payload[1] - 48;                                 // если от кода числа отнять 48 то получим число.... К примеру код "0" = 48 если от 48-48 то получим 0
          if(payload[2] >= 48 && payload[2] < 58) {
            tMqtt3 = tMqtt3 * 10 + (payload[2] - 48);               // если третий знак тоже число, то второй знак был десятками, умножаем его на 10 (получаем ествественно десятки
          }
        }
        if(payload[3] == 46) {                                      // если третий знак не число, то проверяем его на то что но является точкой...
          if(payload[4] >= 48 && payload[4] < 58) tMqtt4 = payload[4] - 48; // если третий знак точка и четвертый знак является числом, то это десятые значения
        }
        if(payload[2] == 46) {                                      // тоже самое со втрорым знаком...
          if(payload[3] >= 48 && payload[3] < 58) tMqtt4 = payload[3] - 48;
        }
        tMqtt5 = (tMqtt3 + ((float)tMqtt4 / 10)) * (-1);
      } else {                                                      // здесь таже самая процедура но уже с положительными числами)))))
        tMqtt3 = payload[0] - 48;
        if(payload[1] >= 48 && payload[1] < 58) {
          tMqtt3 = tMqtt3 * 10 + (payload[1] - 48);
          if(payload[2] == 46) {
            if(payload[3] >= 48 && payload[3] < 58) tMqtt4 = payload[3] - 48;
          }
        }
        if(payload[1] == 46) {
          if(payload[2] >= 48 && payload[2] < 58) tMqtt4 = payload[2] - 48;
        }
        tMqtt5 = (tMqtt3 + ((float)tMqtt4 / 10)) + (sensorUl == 6 ? corrTempU : 0); 
      }
    }
    if(printCom) {
      printTime();
      Serial.println("MQTT Incoming Temperature: " + String(tMqtt5, 1) + " *C");
    }
  }
}
//======================================================================================
void reconnect() {
  if(!ESPclient.connected() && WiFi.status() == WL_CONNECTED) {
    if(printCom) {
      printTime();
      Serial.print("MQTT reconnection...");
    }
    if(MQTTclient.connect(mqtt_name, mqtt_user, mqtt_pass)) {
      if(printCom) Serial.println("connected");
      MQTTclient.subscribe(mqtt_sub_inform);
      MQTTclient.subscribe(mqtt_sub);
    } else {
      if(printCom){
        Serial.print("failed, rc = ");
        Serial.println(MQTTclient.state());
      }
    }
  }
}
//======================================================================================
//======================================================================================
void loop() {
  if(updateOTA) ArduinoOTA.handle();
  server.handleClient();                                                                // дозволяємо HTTP серверу відповідать на запити
  updateTime();                                                                         // оновлюємо час
  if(second != lastSecond) {                                                            // на початку нової секунди скидаємо secFr в "0"
    lastSecond = second;
    if(volBrightnessAuto) {
      levelBridhtness = map(analogRead(brightPin), 1023, 0, 2, 15);
      sendCmdAll(CMD_INTENSITY, levelBridhtness);
    } else {
      if(hour >= timeDay && hour < timeNight) sendCmdAll(CMD_INTENSITY, volBrightnessD);
      else sendCmdAll(CMD_INTENSITY, volBrightnessN);
    }
    secFr = 0;
    if(lastMinute!=minute) {
      if(hour==0 && minute==0 && second==0) {
        day++;
        if(day==32 || (day==31 && (month==4 || month==6 || month==9 || month==11)) || (month==2 && ((day==29 && year%4!=0) || (day==30 && year%4==0)))) {
          day=1;
          month++;
          if(month>12){
            month=1;
            year++;
          }
        }
        dayOfWeek++;
        if(dayOfWeek>7) dayOfWeek=1;
      }
      lastMinute=minute;
    }
  } else secFr++;                                                                       // якщо секунда ще не скінчилась то нарощуємо лічильник циклів secFr
  if(minute == 0 && second == 0 && secFr == 0 && (hour >= kuOn && hour < kuOff)) {      // сигнал кожду годину 
    bip();
    bip();
  }
  if(secFr == 0 && second == 10 && !alarm_stat) sensors();
  //----------- РОБОТА З БУДИЛЬНИКОМ------------------------------------------------------
  if(secFr == 0) {
    if(second > 0 && alarms()) {
      if(!alarm_stat && alarm_numer != 255 && !alarm_hold) alarm_stat = 1;
    } else if(alarm_stat) {
      alarm_stat = 0;
      if(alarme[alarm_numer][2] == 11) alarme[alarm_numer][2] = 0;
    } else if(alarm_hold != 0);
  }
  //------------- РОБОТА ЗІ СВЯТКОВИМИ ДАТАМИ ---------------------------------------------
  if(secFr == 0) {
    if(minute == 0) {
      if(hour >= memory_hour_start && hour <= memory_hour_end && second < 15 && second > 2 && !alarm_stat){
        for(byte i = 0; i < 9; i++) {
          if(memory_date[i][0] == day && memory_date[i][1] == month){
            m_date = i;
            bip();
            bip();
            bip();
            printStringWithShift(("         "), timeScrollSpeed);
            printStringWithShift((m_date==0?memory_date_mes0:m_date==1?memory_date_mes1:m_date==2?memory_date_mes2:m_date==3?memory_date_mes3:m_date==4?memory_date_mes4:m_date==5?memory_date_mes5:m_date==6?memory_date_mes6:m_date==7?memory_date_mes7:memory_date_mes8), timeScrollSpeed);
            printStringWithShift(("         "), timeScrollSpeed);
            break;
          }
        }
      } 
    } else m_date = 0;
  }
  //------------- РОБОТА З КНОПКОЮ --------------------------------------------------------
  if(digitalRead(BUT_PIN) == HIGH) {
    if(alarm_stat) {
      alarm_stat = 0;
      alarm_hold = 1;
      if(alarme[alarm_numer][2] == 11) alarme[alarm_numer][2] = 0;
    } else {
      bip();
      showSimpleTemp();
      return;
    }
  }
  //------------- НАШ ЧАС ----------------------------------------------------------------
  if(hour == 32 && minute == 55) {                                                      // якщо наш час - то іде повідомлення для коханої
    //bip();
    //bip();
    //bip();
    printStringWithShift(("       22:55 \200\200\200 " + tMes + " \200\200\200").c_str(), timeScrollSpeed);
    return;
  }
  // ---------- ВИВІД НА ЕКРАН ГОДИННИКА АБО ТЕМПЕРАТУРИ ЧИ ВОЛОГОСТІ------------------------
  if(!alarm_stat && millis() % 50 == 0) {
    if((clockNight && hour>=timeDay && hour<timeNight) || !clockNight) {
      if(second >= 40 && second < 42 && sensorDom && t1 != 85) {
        showSimpleTemp();
      } else if(second >= 42 && second < 44 && sensorUl && t3 != 85) {
        showSimpleTempU();
      } else if(second >= 44 && second < 46 && (sensorHumi == 2 || sensorHumi == 4 || sensorHumi == 5)) {
        showSimpleHum();
      } else if(second >= 46 && second < 48 && (sensorPrAl == 3 || sensorPrAl == 4)) {
        showSimplePre();
      } else if((hour < timeScrollStart || hour >= timeScrollStop) && second >= 10 && second < 15) {
        showSimpleDate();
      } else showAnimClock();
    } else showAnimClock();
  } else if(alarm_stat) {
    if(millis() % 50 == 0) showAnimClock();
    if(secFr == 0 && second > 1 && second <= 59) {
      clr();
      refreshAll();
      bip();
      bip();
    }
  }
  // --------------------------------------------------------------------------------------------------------
  if(secFr == 0) {
    if(second == 10 && minute == 1 && hour == 3) {
      if(rtcStat){
        getRTCDateTime();
        hour=hour_rtc;
        minute=minute_rtc;
        second=second_rtc;
        day=day_rtc;
        month=month_rtc;
        year=year_rtc;
        dayOfWeek=dayOfWeek_rtc;
        if(printCom){
          Serial.println("RTC update: "+String(hour)+":"+String(minute)+":"+String(second)+"    "+String(day)+"."+String(month)+"."+String(year)+" D="+String(dayOfWeek));
        }
      }
    }
    // ---------- 10 секунда - виводимо дату/погоду----------------------------------------------------------
    if(second == 10 && !alarm_stat && hour >= timeScrollStart && hour < timeScrollStop) {        // працує тілки в дозволений час
      if(minute % 2 == 0 || !outForecast) {                        // по чотним хвилинам виводимо повідомлення дати та курсу валют
        convertDw();
        convertMonth();
        date = "     " + dw + ", " + String(day) + " " + _month + " " + String(year) + "          ";
        printStringWithShift(date.c_str(), timeScrollSpeed);
      } else {                                                      // по не чотним хвилинам виводимо погоду
          printStringWithShift(weatherString.c_str(), timeScrollSpeed);
          printStringWithShift(weatherStringZ.c_str(), timeScrollSpeed);
          if(updateForecast > 0 && updateForecast < 360) printStringWithShift(("  (" + tWeatrTN + String(updateForecast) + tMin + ")        ").c_str(), timeScrollSpeed);
      }
    }
    // ---------- 30 перевірка доступності WiFi мережі ---// повторне підк. до WiFi кожну 1, 6, 11, 16...56 хв.
    if((second>30 && second<38) && (WiFi.status() != WL_CONNECTED || !WIFI_connected) && !alarm_stat && firstStart) {
      WIFI_connected = false;
      WiFi.disconnect();
      if(minute % 5 == 1) {
        wifiConnect();
        if(WiFi.status() == WL_CONNECTED) WIFI_connected = true;
      }
    }
    // ---------- 43 секунда оновленя мережевого часу кожну хвилину або в 5 хвилину кожного часу
    if(((statusUpdateNtpTime == 0 && second == 43) || (minute == 02 && second == 43)) && !alarm_stat) timeUpdateNTP();
    // ---------- 46 cек. оновлюємо прогноз погоди ------------------------------------- 
    if(second == 46 && hour >= timeScrollStart && hour <= timeScrollStop && !alarm_stat) {
      if(minute == 20 || minute == 25 || updateForecast || updateForecasttomorrow) {
        if((minute == 20 || minute == 25) && outForecast) {
          if(!weatherHost) {
            getWeatherData0();
          } else {
            getWeatherData1();
          }
          if(!weatherHost) {
            getWeatherDataz0();
          } else {
            getWeatherDataz1();
          }
        } else {
          if(updateForecast){
            if(!weatherHost) {
              getWeatherData0();
            } else {
              getWeatherData1();
            }
          }
          if(updateForecasttomorrow){
            if(!weatherHost) {
              getWeatherDataz0();
            } else {
              getWeatherDataz1();
            }
          }
        }
        if(sensorUl==7) getNarodmon();   
        if(!MQTTclient.connected() && mqttOn) reconnect();
      }
    }
    // ---------- 50 сек. перевірка доступності MQTT та публікація температури ---------
    if(second == 50 && mqttOn && !alarm_stat && WIFI_connected) {
      if(WiFi.status() != WL_CONNECTED) {
        WIFI_connected = false;
      }
      if(!MQTTclient.connected() && WIFI_connected) {
        reconnect();
      }
      if(MQTTclient.connected() && WIFI_connected) {
        if(sensorDom && t1 != 85) MQTTclient.publish(mqtt_pub_temp, (String(t1) + "." + String(t2)).c_str());
        if(sensorUl != 0 && sensorUl != 6 && t3 != 85) MQTTclient.publish(mqtt_pub_tempUl, (String(t3) + "." + String(t4)).c_str());
        if(sensorHumi == 2 && humSi7021 != 0) MQTTclient.publish(mqtt_pub_hum, (String(humSi7021)).c_str());
        if(sensorHumi == 4 && humBme != 0) MQTTclient.publish(mqtt_pub_hum, (String(humBme)).c_str());
        if(sensorHumi == 5 && humiDht != 0) MQTTclient.publish(mqtt_pub_hum, (String(humiDht)).c_str());
        if(sensorPrAl == 3 && pressBmp != 0) {
          MQTTclient.publish(mqtt_pub_press, String(pressBmp).c_str());
          MQTTclient.publish(mqtt_pub_alt, String(altBmp).c_str());
        }
        if(sensorPrAl == 4 && pressBme != 0) {
          MQTTclient.publish(mqtt_pub_press, String(pressBme).c_str());
          MQTTclient.publish(mqtt_pub_alt, String(altBme).c_str());
        }
        if(printCom) {
          printTime();
          Serial.print("Publish in topic ");
          if(sensorDom && t1 != 85) Serial.print("Temperature: " + String(t1) + "." + String(t2) + "*C,   ");
          if(sensorUl != 0 && sensorUl != 6 && t3 != 85) Serial.print("Na ulice: " + String(t3) + "." + String(t4) + "*C,   ");
          if(sensorHumi == 2 && humSi7021 != 0) Serial.print("Humidity: " + String(humSi7021) + " %,  ");
          if(sensorHumi == 4 && humBme != 0) Serial.print("Humidity: " + String(humBme) + " %,  ");
          if(sensorHumi == 5 && humiDht != 0) Serial.print("Humidity: " + String(humiDht) + " %,  ");
          if(sensorPrAl == 3 && pressBmp != 0) Serial.print("  Pressure: " + String(pressBmp) + " mmHg,  Altitude: " + String(altBmp) + " m.");
          if(sensorPrAl == 4 && pressBme != 0) Serial.print("  Pressure: " + String(pressBme) + " mmHg,  Altitude: " + String(altBme) + " m.");
          Serial.println("");
        }
      }
    }
  }
  // ---------- якщо мережа WiFi доступна то виконуємо наступні функції ----------------------------
  if(WIFI_connected){
    if(mqttOn) MQTTclient.loop();           // перевіряємо чи намає вхідних повідомлень, як є, то кoлбек функція
  }
}
//======================================================================================
//==========ВИВІД НА ЕКРАН ТЕМПЕРАТУРИ В БУДИНКУ========================================
void showSimpleTemp() {
  byte indent=aliData*(NUM_MAX-4);
  dx = dy = 0;
  clr();
  showDigit((t0 < 0.0 ? 4 : 3), indent, znaki5x8); // друкуємо D+ альбо D-
  if(t1 <= -10.0 || t1 >= 10) showDigit((t1 < 0 ? (t1 * -1) / 10 : t1 / 10), 4+indent, dig5x8);
  showDigit((t1 < 0 ? (t1 * -1) % 10 : t1 % 10), 10+indent, dig5x8);
  showDigit(2, 16+indent, znaki5x8);
  showDigit(t2, 18+indent, dig5x8);
  showDigit(0, 24+indent, znaki5x8);
  showDigit(1, 27+indent, znaki5x8);
  refreshAll();
}
//==========ВИВІД НА ЕКРАН ТЕМПЕРАТУРИ НА ВУЛИЦІ========================================
void showSimpleTempU() {
  if(WiFi.status() == WL_CONNECTED) {
    byte indent=aliData*(NUM_MAX-4);
    dx = dy = 0;
    clr();
    showDigit((t5 < 0.0 ? 6 : 5), indent, znaki5x8); //друкуємо U+ альбо U-
    if(t3 <= -10.0 || t3 >= 10) showDigit((t3 < 0 ? (t3 * -1) / 10 : t3 / 10), 4+indent, dig5x8);
    showDigit((t3 < 0 ? (t3 * -1) % 10 : t3 % 10), 10+indent, dig5x8);
    showDigit(2, 16+indent, znaki5x8);
    showDigit(t4, 18+indent, dig5x8);
    showDigit(0, 24+indent, znaki5x8);
    showDigit(1, 27+indent, znaki5x8);
    refreshAll();
  }
}
//==========ВИВІД НА ЕКРАН ВОЛОГОСТІ В БУДИНКУ========================================
void showSimpleHum() {
  byte indent=aliData*(NUM_MAX-4);
  dx = dy = 0;
  clr();
  showDigit(7, indent, znaki5x8);     // друкуємо знак вологості
  if(h1 >= 0) showDigit(h1, 6+indent, dig5x8);
  showDigit(h2, 12+indent, dig5x8);
  showDigit(2, 18+indent, znaki5x8);
  showDigit(h3, 20+indent, dig5x8);
  showDigit(8, 26+indent, znaki5x8);
  refreshAll();
}
//==========ВИВІД НА ЕКРАН ТИСКУ В БУДИНКУ========================================
void showSimplePre() {
  byte indent=aliData*(NUM_MAX-4);
  dx = dy = 0;
  clr();
  showDigit(9, indent, znaki5x8);     // друкуємо знак тиску
  showDigit(int((sensorPrAl==3?pressBmp:pressBme) / 100), 6+indent, dig5x8);
  showDigit((int((sensorPrAl==3?pressBmp:pressBme) / 10) - int((sensorPrAl==3?pressBmp:pressBme) / 100) * 10) , 12+indent, dig5x8);
  showDigit(((sensorPrAl==3?pressBmp:pressBme) - int((sensorPrAl==3?pressBmp:pressBme) / 10) *10) , 18+indent, dig5x8);
  showDigit(10, 24+indent, znaki5x8);
  showDigit(11, 29+indent, znaki5x8);
  refreshAll();
}
//==========ВИВІД НА ЕКРАН ДАТИ=========================================================
void showSimpleDate() { 
  byte indent=aliData*(NUM_MAX-4);
  dx = dy = 0;
  clr();
  showDigit(day / 10, indent, dig4x8);
  showDigit(day % 10,  5+indent, dig4x8);
  showDigit(month / 10, 12+indent, dig4x8);
  showDigit(month % 10, 17+indent, dig4x8);
  showDigit((year - 2000) / 10, 23+indent, dig4x8);
  showDigit((year - 2000) % 10, 28+indent, dig4x8);
  setCol(10+indent, 0xC0);
  setCol(22+indent, 0xC0);
  refreshAll();
}
//==========ВИВІД НА ЕКРАН АНІМАЦІЙНОГО ГОДИННИКА=======================================
void showAnimClock() {
  byte indent=(hour<10?12:15)+4*(NUM_MAX-4);
  byte digPos[5]={(indent-(fontCLOCK<2?14:fontCLOCK<6?12:10)),(indent-(fontCLOCK<2?7:fontCLOCK<6?6:5)),(indent+3),(indent+(fontCLOCK<2?10:fontCLOCK<6?9:8)),indent};
  int digHt = 16;
  int num = hour < 10 ? 1 : 0;;
  int i;
  if(del == 0) {
    del = digHt;
    for(i = num; i < 4; i++) digold[i] = dig[i];
    dig[0] = hour / 10;
    dig[1] = hour % 10;
    dig[2] = minute / 10;
    dig[3] = minute % 10;
    for(i = num; i < 4; i++)  digtrans[i] = (dig[i] == digold[i]) ? 0 : digHt;
  } else del--;
  clr();
  for(i = num; i < 4; i++) {
    if(digtrans[i] == 0) {
      dy = 0;
      if(fontCLOCK == 0) showDigit(dig[i], digPos[i], dig6x8);
        else if(fontCLOCK == 1) showDigit(dig[i], digPos[i], dig6x8dig);
        else if(fontCLOCK == 2) showDigit(dig[i], digPos[i], dig5x8rn);
        else if(fontCLOCK == 3) showDigit(dig[i], digPos[i], dig5x8rndig);
        else if(fontCLOCK == 4) showDigit(dig[i], digPos[i], dig5x8);
        else if(fontCLOCK == 5) showDigit(dig[i], digPos[i], dig5x8dig);
        else if(fontCLOCK == 6) showDigit(dig[i], digPos[i], dig4x8);
        else if(fontCLOCK == 7) showDigit(dig[i], digPos[i], dig4x8dig);
    } else {
      dy = digHt - digtrans[i];
      if(fontCLOCK == 0) showDigit(digold[i], digPos[i], dig6x8);
        else if(fontCLOCK == 1) showDigit(digold[i], digPos[i], dig6x8dig);
        else if(fontCLOCK == 2) showDigit(digold[i], digPos[i], dig5x8rn);
        else if(fontCLOCK == 3) showDigit(digold[i], digPos[i], dig5x8rndig);
        else if(fontCLOCK == 4) showDigit(digold[i], digPos[i], dig5x8);
        else if(fontCLOCK == 5) showDigit(digold[i], digPos[i], dig5x8dig);
        else if(fontCLOCK == 6) showDigit(digold[i], digPos[i], dig4x8);
        else if(fontCLOCK == 7) showDigit(digold[i], digPos[i], dig4x8dig);
      dy =- digtrans[i];
      if(fontCLOCK == 0) showDigit(dig[i], digPos[i], dig6x8);
        else if(fontCLOCK == 1) showDigit(dig[i], digPos[i], dig6x8dig);
        else if(fontCLOCK == 2) showDigit(dig[i], digPos[i], dig5x8rn);
        else if(fontCLOCK == 3) showDigit(dig[i], digPos[i], dig5x8rndig);
        else if(fontCLOCK == 4) showDigit(dig[i], digPos[i], dig5x8);
        else if(fontCLOCK == 5) showDigit(dig[i], digPos[i], dig5x8dig);
        else if(fontCLOCK == 6) showDigit(dig[i], digPos[i], dig4x8);
        else if(fontCLOCK == 7) showDigit(dig[i], digPos[i], dig4x8dig);
      digtrans[i]--;
    }
  }
  dy = 0;
  int flash = millis() % 1000;
  if(!alarm_stat){
    if((flash >= 180 && flash < 360) || flash >= 540) {                       // мерегтіння двокрапок в годиннику підвязуємо до личильника циклів
      setCol(digPos[4], WIFI_connected ? 0x66 : 0x60);
      setCol(digPos[4]+1, WIFI_connected ? 0x66 : 0x60);
    }
    if(statusUpdateNtpTime) {                                                 // якщо останнє оновленя часу було вдалим, то двокрапки в годиннику будуть анімовані
      if(flash >= 0 && flash < 180) {
        setCol(digPos[4], WIFI_connected ? 0x24 : 0x20);
        setCol(digPos[4]+1, WIFI_connected ? 0x42 : 0x40);
      }
      if(flash >= 360 && flash < 540) {
        setCol(digPos[4], WIFI_connected ? 0x42 : 0x40);
        setCol(digPos[4]+1, WIFI_connected ? 0x24 : 0x20);
      }
    }
    if(updateForecast && WIFI_connected) setCol(00, flash < 500 ? 0x80 : 0x00);
    if(updateForecasttomorrow && WIFI_connected) setCol((NUM_MAX*8-1), flash < 500 ? 0x80 : 0x00);
  } else {
    setCol(digPos[4], 0x66);
    setCol(digPos[4]+1, 0x66);
  }
  refreshAll();
}

//=================================================
void showAnimWifi(byte probaWifi) {
  byte digPos[2] = {18, 25};
  int digHt = 16;
  int num = 2;
  int ii;
  if(del == 0) {
    del = digHt;
    for(ii = 0; ii < num; ii++) digold[ii] = dig[ii];
    dig[0] = probaWifi / 10;
    dig[1] = probaWifi % 10;
    for(ii = 0; ii < num; ii++)  digtrans[ii] = (dig[ii] == digold[ii]) ? 0 : digHt;
  } else del--;
  clr();
  for(ii = 0; ii < num; ii++){
    if(digtrans[ii] == 0) {
      dy = 0;
      showDigit(dig[ii], digPos[ii], dig6x8);
    } else {
      dy = digHt-digtrans[ii];
      showDigit(digold[ii], digPos[ii], dig6x8);
      dy =- digtrans[ii];
      showDigit(dig[ii], digPos[ii], dig6x8);
      digtrans[ii]--;
    }
  }
  dy = 0;
  refreshAll();
}
//==========ДРУКУВАННЯ БІГУЧОЇ СТРОКИ *s - текст, shiftDelay - швидкість==========================================
void printStringWithShift(const char* s, int shiftDelay) {
  while(*s) {                                                   // коли працює ця функція, основний цикл зупиняється
    printCharWithShift(*s, shiftDelay);
    s++;
    server.handleClient();                                      // зберігаемо можливість відповіді на HTML запити під час бігучої стоки
    if(mqttOn) MQTTclient.loop();                                          // зберігаемо можливість слухати MQTT топік під час бігучої стоки
  }
}
//==========ДРУКУВАННЯ БІГУЧОГО СИМВОЛУ с - символ, shiftDelay - швидкість=====================================
void printCharWithShift(unsigned char c, int shiftDelay) {
  c = convert_UA_RU_PL_DE(c);
  if(c < ' ') return;
  c -= 32;
  int w = showChar(c, fontUA_RU_PL_DE);
  for(int i = 0; i < w + 1; i++){
    delay(shiftDelay);
    scrollLeft();
    refreshAll();
  }
}
//======================================================================================
int showChar(char ch, const uint8_t *data) {
  int len = pgm_read_byte(data);
  int i,w = pgm_read_byte(data + 1 + ch * len);
  for(i = 0; i < w; i++)
    scr[NUM_MAX * 8 + i] = pgm_read_byte(data + 1 + ch * len + 1 + i);
    scr[NUM_MAX * 8 + i] = 0;
  return w;
}
//======================================================================================
void showDigit(char ch, int col, const uint8_t *data) {
  if(dy < -8 | dy > 8) return;
  int len = pgm_read_byte(data);
  int w = pgm_read_byte(data + 1 + ch * len);
  col += dx;
  for(int i = 0; i < w; i++) {
    if(col + i >= 0 && col + i < 8 * NUM_MAX) {
      byte v = pgm_read_byte(data + 1 + ch * len + 1 + i);
      if(!dy) scr[col + i] = v; else scr[col + i] |= dy > 0 ? v >> dy : v << -dy;
    }
  }
}
//======================================================================================
void setCol(int col, byte v) {
  if(dy < -8 | dy > 8) return;
  col += dx;
  if(col >= 0 && col < 8 * NUM_MAX) {
    if(!dy) scr[col] = v; else scr[col] |= dy > 0 ? v >> dy : v << -dy;
  }
}

//==========КОНВЕРТАЦІЯ СИМВОЛІВ В РАЗІ ВИКОРИСТАННЯ УКРАЇНСЬКИХ ЛІТЕР==================
byte dualChar = 0;
unsigned char convert_UA_RU_PL_DE(unsigned char _c) {
  unsigned char c = _c;
  // конвертирование латиницы
  if(c == 208) {
    dualChar = 1;
    return 0;
  }
  else if(c == 209 || c == 210) {
    dualChar = 2;
    return 0;
  }
  if(c == 32 && dualChar != 3) {
    dualChar = 3;
    return c;
  }
  if(dualChar == 1) {
    if(c >= 144 && c < 192) {c += 48;}
    dualChar = 0;
    return c;
  }
  if(dualChar == 2) {
    if(c >= 128 && c < 144) {
      c += 112;
    } 
    switch(_c) {
      case 144: c = 133; break;
      case 145: c = 149; break;
    }
    dualChar = 0;
    return c;
  }
  // конвертирование польского и немецкого
  if(c == 195) {
    dualChar = 4;
    return 0;
  }
  if(c == 196) {
    dualChar = 5;
    return 0;
  }
  if(c == 197) {
    dualChar = 6;
    return 0;
  }
  if(dualChar == 4) {
    switch(_c) {
      case 132: c = 177; break;
      case 147: c = 166; break;
      case 150: c = 179; break;
      case 156: c = 181; break;
      case 159: c = 183; break;
      case 164: c = 178; break;
      case 179: c = 167; break;
      case 182: c = 180; break;
      case 188: c = 182; break;
    }
    dualChar = 0;
    return c;
  }
  if(dualChar == 5) {
    if(c >= 132 && c < 136) {
      c += 26;
    }
    switch(_c) {
      case 152: c = 168; break;
      case 153: c = 169; break;
    }
    dualChar = 0;
    return c;
  }
  if(dualChar == 6) {
    if(c >= 129 && c < 133) {
      c += 33;
    }
    if(c >= 154 && c < 156) {
      c += 16;
    }
    if(c >= 185 && c < 189) {
      c -= 13;
    }  
    dualChar = 0;
    return c;
  }
}


//==========
void saveChrMas(String string_t, byte lenght_off, byte number_s) {
  byte lenght = string_t.length();
  if(lenght>lenght_off) return;
  const char *s = string_t.c_str();
  
  for(int i=0; i<lenght; i++) {
    //snprintf(*memory_date_mes[number_s], 1, "%s", *s);
    s++;
  }
}
//==========ОНОВЛЕННЯ ЛОКАЛЬНОГО ЧАСУ (ЛОКАЛЬНІ ЧАСИ)===============================================================
void updateTime() {
  long curEpoch = localEpoc + ((millis() - localMillisAtUpdate) / 1000);
  long epoch = round(curEpoch + 86400L);
  epoch = (epoch                                                                                                   % 86400L);
  hour = ((epoch % 86400L) / 3600) % 24;
  minute = (epoch % 3600) / 60;
  second = epoch % 60;
}
//==========ОНОВЛЕННЯ МЕРЕЖЕВОГО ЧАСУ (перевірка в три проходи)====================================================
void timeUpdateNTP() {
  if(!WIFI_connected) return;
  if(printCom) printTime();
  statusUpdateNtpTime = 1;
  for(int timeTest = 0; timeTest < 3; timeTest++) {
    getNTPtime();
    if(printCom) {
      if(timeTest) Serial.print("          ");
      Serial.println("Proba #"+String(timeTest+1)+"   "+String(g_hour)+":"+((g_minute<10)?"0":"")+String(g_minute)+":"+((g_second<10)?"0":"")+String(g_second));
    }
   // updateTime();

    hourTest[timeTest] = g_hour;
    minuteTest[timeTest] = (g_minute || (g_minute==59?0:g_minute++));
    if(statusUpdateNtpTime == 0) {
      if(printCom) {
        printTime();
        Serial.print("ERROR TIME!!!\r\n");
      }
        return;
    }
    if(timeTest > 0) {
      if((hourTest[timeTest] != hourTest[timeTest - 1]||minuteTest[timeTest] != minuteTest[timeTest - 1])) {
        statusUpdateNtpTime = 0;
        if(printCom) {
          printTime();
          Serial.print("ERROR TIME!!!\r\n");
        }
        return;
      }
    }
  }
  hour=g_hour;
  minute=g_minute;
  second=g_second;
  day=g_day;
  dayOfWeek=g_dayOfWeek;
  month=g_month;
  year=g_year;
  if(rtcStat){
    hour_rtc = hour;
    minute_rtc = minute;
    second_rtc = second;
    month_rtc = month;
    day_rtc = day;
    dayOfWeek_rtc = dayOfWeek;
    year_rtc = year;
    setRTCDateTime();
  }
  localMillisAtUpdate = millis();
  localEpoc = (hour * 60 * 60 + minute * 60 + second);
  convertDw();
  convertMonth();
  saveTime();
  if(printCom) {
    printTime();
    Serial.println((day < 10 ? "0" : "") + String(day) + "." + (month < 10 ? "0" : "") + String(month) + "." + String(year) + " DW = " + String(dayOfWeek));
    Serial.println("          Time update OK.");
  }
}
//==========ОТРИМАННЯ ДАТИ ТА ЧАСУ ВІД СЕРВЕРА ТОЧНОГО ЧАСУ =============================================================
void getNTPtime() {
  WiFi.hostByName(ntpServerName.c_str(), timeServerIP); 
  int cb;
  for(int i = 0; i < 3; i++){
    memset(packetBuffer, 0, NTP_PACKET_SIZE);
    packetBuffer[0] = 0b11100011;
    packetBuffer[1] = 0;
    packetBuffer[2] = 6;
    packetBuffer[3] = 0xEC;
    packetBuffer[12] = 49;
    packetBuffer[13] = 0x4E;
    packetBuffer[14] = 49;
    packetBuffer[15] = 52;
    udp.beginPacket(timeServerIP, 123);                     //NTP порт 123
    udp.write(packetBuffer, NTP_PACKET_SIZE);
    udp.endPacket();
    delay(800);                                             // чекаємо пів секуни
    cb = udp.parsePacket();
    if(!cb && printCom) Serial.println("          no packet yet..." + String (i + 1)); 
    if(!cb && i == 2) {                                              // якщо час не отримано
      statusUpdateNtpTime = 0;
      return;                                             // вихіз з getNTPtime()
    }
    if(cb) i = 3;
  }
  if(cb) {                                                   // якщо отримали пакет з серверу
    udp.read(packetBuffer, NTP_PACKET_SIZE);
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    const unsigned long seventyYears = 2208988800UL;        // Unix час станом на 1 січня 1970. в секундах, то 2208988800:
    unsigned long epoch = secsSince1900 - seventyYears;
    epochNM = epoch - (millis()/1000);
    boolean summerTime;
    if(month < 3 || month > 10) summerTime = false;             // не переходимо на літній час в січні, лютому, листопаді і грудню
    if(month > 3 && month < 10) summerTime = true;              // Sommerzeit лічимо в квіні, травні, червені, липні, серпені, вересені
    if(month == 3 && (hour + 24 * day) >= (3 + 24 * (31 - (5 * year / 4 + 4) % 7)) || month == 10 && (hour + 24 * day) < (3 + 24 * (31 - (5 * year / 4 + 1) % 7))) summerTime = true; 
    epoch += (int)(timeZone*3600 + (3600*(isDayLightSaving && summerTime)));      
    g_year = 0;
    int days = 0;
    uint32_t time;
    time = epoch/86400;
    g_hour = (epoch % 86400L) / 3600;
    g_minute = (epoch % 3600) / 60;
    g_second = epoch % 60;
    g_dayOfWeek = (((time) + 4) % 7) + 1;
    while((unsigned)(days += (LEAP_YEAR(g_year) ? 366 : 365)) <= time) {
      g_year++;
    }
    days -= LEAP_YEAR(g_year) ? 366 : 365;
    time -= days;
    days = 0;
    g_month = 0;
    uint8_t monthLength = 0;
    for(g_month = 0; g_month < 12; g_month++){
      if(g_month == 1){
        if(LEAP_YEAR(g_year)) monthLength = 29;
        else monthLength = 28;
      }
      else monthLength = monthDays[g_month];
      if(time >= monthLength) time -= monthLength;
      else break;
    }
    g_month++;
    g_day = time + 1;
    g_year += 1970;
    return;
  }
  if(printCom) Serial.println("Nie ma czasu(((");
}
//===============================================================================================================================//
//                              БЕРЕМО ПОГОДУ З САЙТУ  https://www.weatherbit.io                                                 //
//===============================================================================================================================//
void getWeatherData0() {
  location_name = "";
  location_region = "";
  location_country = "";
  location_localtime = "";
  location_temp = 0;
  location_app_temp = 0;
  location_rh = 0;
  location_pres = 0;
  location_wind_spd = 0;
  location_wind_cdir_full = "";
  location_sunrise = "";
  location_sunset = "";
  location_clouds = 0;
  location_vis = 0;
  location_uv = 0;
  location_weather_description = "";
  if(!WIFI_connected) {
    updateForecast++;
    if(updateForecast >= 360) weatherString = tWeatrNot;
    return;
  }
  if(printCom) {
    printTime();
    Serial.println("Getting weather forecast for City " +  cityID0 + "...");
  }
  if(ESPclient.connect(weatherHost0.c_str(), 80)) {
  } else {
    if(printCom) Serial.println("          Not connection server!!!");
    updateForecast++;
    if(updateForecast >= 360) weatherString = tWeatrNot;
    return;
  }

  HTTPClient http;
  String line="";
  String reqline="http://"+weatherHost0+"/v2.0/current/daily?city="+urlencode(cityID0)+"&lang="+weatherLang+"&key="+weatherKey0;
  if(printCom) {
    Serial.println("=======================================================");
    Serial.println(reqline);
    Serial.println("=======================================================");
  }  
  if (http.begin(ESPclient, reqline)) { // HTTP
   int httpCode = http.GET();
   if (httpCode > 0) {
     Serial.printf("[HTTP] GET... code: %d\n", httpCode);
     if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
      line = http.getString();
     }
   } else {
     Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
   }
   http.end();
  } else {
   Serial.printf("[HTTP} Unable to connect\n");
  }
  if(printCom) {
    Serial.print("line =");
    Serial.println(line);
  }
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(37) + 1128; //https://arduinojson.org/v6/assistant/
  DynamicJsonDocument doc(capacity);
  deserializeJson(doc, line);
  if(!doc.capacity()){
    if(printCom) Serial.println("          Parse weather forecast - FAILED!!!");
    updateForecast++;
    if(updateForecast >= 360) weatherString = tWeatrNot;
    return;
  }

  JsonObject data = doc["data"][0];
  location_rh = data["rh"]; // 69
  location_pres = data["pres"]; // 999.3
  location_pres /= 1.3332239;
  const char* data_timezone = data["timezone"]; // "Europe/Kiev"
  location_region = data_timezone;
  const char* data_ob_time = data["ob_time"]; // "2019-09-19 17:57"
  location_localtime = data_ob_time;
  const char* data_country_code = data["country_code"]; // "UA"
  location_country = data_country_code;
  location_clouds = data["clouds"]; // 4
  const char*   data_city_name = data["city_name"]; // "Kiev"
  location_name = data_city_name;
  if(location_name == "Frankfurt am Main") location_name = "Франкфурт на Майні"; 
  location_wind_spd = data["wind_spd"]; // 1
  const char* data_wind_cdir_full = data["wind_cdir_full"]; // "пі́вдень-пі́вдень-схід"
  location_wind_cdir_full = data_wind_cdir_full;
  location_vis = data["vis"]; // 5
  const char*   data_sunset = data["sunset"]; // "16:01"
  location_sunset = data_sunset;
  location_uv = data["uv"]; // 0
  int           data_wind_dir = data["wind_dir"]; // 166
  const char*   data_sunrise = data["sunrise"]; // "03:39"
  location_sunrise = data_sunrise;   //int         data_dni = data["dni"]; // 0
  JsonObject    data_weather = data["weather"];
  const char*   data_weather_description = data_weather["description"]; // "ясного неба"
  location_weather_description = data_weather_description;
  location_temp = data["temp"]; // 10.6
  location_app_temp = data["app_temp"]; // 10.6

  //const char* data_pod = data["pod"]; // "n"
  //float       data_lon = data["lon"]; // 30.5238
  //float       data_dewpt = data["dewpt"]; // 5.2
  //int         data_precip = data["precip"]; // 0
  //int         data_snow = data["snow"]; // 0
  //long        data_ts = data["ts"]; // 1568915820
  //int         data_solar_rad = data["solar_rad"]; // 0
  //const char* data_state_code = data["state_code"]; // "12"
  //const char* data_last_ob_time = data["last_ob_time"]; // "2019-09-19T17:57:00"
  //const char* data_wind_cdir = data["wind_cdir"]; // "ЮЮВ"
  //float       data_slp = data["slp"]; // 1017.9
  //int         data_h_angle = data["h_angle"]; // -90
  //int         data_ghi = data["ghi"]; // 0
  //int         data_dhi = data["dhi"]; // 0
  //int         data_aqi = data["aqi"]; // 25
  //float       data_lat = data["lat"]; // 50.45466
  //const char* data_weather_icon = data_weather["icon"]; // "c01n"
  //const char* data_weather_code = data_weather["code"]; // "800"
  //const char* data_datetime = data["datetime"]; // "2019-09-19:18"
  //const char* data_station = data["station"]; // "E0036"
  //float       data_elev_angle = data["elev_angle"]; // -18.88
  //int count = doc["count"]; // 1

  String windDegString;
  if(data_wind_dir >= 345 || data_wind_dir <= 22)  windDegString = "\211";    //"Північний";
  if(data_wind_dir >= 23  && data_wind_dir <= 68)  windDegString = "\234";    //"Північно-східний";
  if(data_wind_dir >= 69  && data_wind_dir <= 114) windDegString = "\230";    //"Східний";
  if(data_wind_dir >= 115 && data_wind_dir <= 160) windDegString = "\235";    //"Південно-східний";
  if(data_wind_dir >= 161 && data_wind_dir <= 206) windDegString = "\210";    //"Південний";
  if(data_wind_dir >= 207 && data_wind_dir <= 252) windDegString = "\232";    //"Південно-західний";
  if(data_wind_dir >= 253 && data_wind_dir <= 298) windDegString = "\231";    //"Західний";
  if(data_wind_dir >= 299 && data_wind_dir <= 344) windDegString = "\233";    //"Північно-західний";

  weatherString = "         " + String(location_name) + ", " + tNow + ":    \212 " + String(location_temp, 1) + ("\202") + "C";
  weatherString += "     \213 " + String(location_rh) + "%"; 
  weatherString += "     \215 " + String((location_pres), 0) + tPress;
  weatherString += "     \214 " + windDegString + String(location_wind_spd, 1) + tSpeed;
  weatherString += "     \216 " + String(location_clouds) + "%     " + data_weather_description + "                ";
  updateForecast = 0;
}
//===============================================================================================================================//
//                              БЕРЕМО ПОГОДУ З САЙТУ  openweathermap.org                                                     //
//===============================================================================================================================//
void getWeatherData1() {
  location_name = "";
  location_region = "";
  location_country = "";
  location_localtime = "";
  location_temp = 0;
  location_app_temp = 0;
  location_rh = 0;
  location_pres = 0;
  location_wind_spd = 0;
  location_wind_cdir_full = "";
  location_sunrise = "";
  location_sunset = "";
  location_clouds = 0;
  location_vis = 0;
  location_uv = 0;
  location_weather_description = "";
  if(!WIFI_connected) {
    updateForecast++;
    if(updateForecast >= 360) weatherString = tWeatrNot;
    return;
  }
  if(printCom) {
    printTime();
    Serial.println("Getting weather forecast for City " +  cityID1 + "...");
  }
  if(ESPclient.connect(weatherHost1.c_str(), 80)) {
  } else {
    if(printCom) Serial.println("          Not connection server!!!");
    updateForecast++;
    if(updateForecast >= 360) weatherString = tWeatrNot;
    return;
  }

  HTTPClient http;
  String line="";
  String reqline="http://"+weatherHost1+"/data/2.5/weather?id="+urlencode(cityID1)+"&lang="+weatherLang+"&units=metric&appid="+weatherKey1;
  if(printCom) {
    Serial.println("=======================================================");
    Serial.println(reqline);
    Serial.println("=======================================================");
  }  
  if (http.begin(ESPclient, reqline)) { // HTTP
  
   int httpCode = http.GET();
   if (httpCode > 0) {
     Serial.printf("[HTTP] GET... code: %d\n", httpCode);
     if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
      line = http.getString();
     }
   } else {
     Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
   }
   http.end();
  } else {
   Serial.printf("[HTTP} Unable to connect\n");
  }
  if(printCom) {
    Serial.print("line =");
    Serial.println(line);
  }
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + 2*JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(13) + 751; //https://arduinojson.org/v6/assistant/
  DynamicJsonDocument doc(capacity);
  deserializeJson(doc, line);
  if(!doc.capacity()){
    if(printCom) Serial.println("          Parse weather forecast - FAILED!!!");
    updateForecast++;
    if(updateForecast >= 360) weatherString = tWeatrNot;
    return;
  }
  JsonObject weather_0 = doc["weather"][0];
  const char*   data_weather_description = weather_0["description"]; // "fog"
  location_weather_description = data_weather_description;
  JsonObject main = doc["main"];
  location_temp = main["temp"]; // 10.34
  location_pres = main["pressure"]; // 1023
  location_pres /= 1.3332239;
  location_rh = main["humidity"]; // 100
  float location_temp_min = main["temp_min"]; // 7
  float location_temp_max = main["temp_max"]; // 12.22
  location_vis = doc["visibility"]; // 1000
  location_vis /= 1000;
  location_wind_spd = doc["wind"]["speed"]; // 1
  int data_wind_dir = doc["wind"]["deg"]; // 230
  location_clouds = doc["clouds"]["all"]; // 20
  JsonObject sys = doc["sys"];
  const char* data_country_code = sys["country"]; // "UA"
  location_country = data_country_code;
  const char*   data_city_name = doc["name"]; // "Kyiv"
  location_name = data_city_name;
  if(location_name == "Frankfurt am Main") location_name = "Франкфурт на Майні"; 
  String windDegString;
  if(data_wind_dir >= 345 || data_wind_dir <= 22)  windDegString = "\211";    //"Північний";
  if(data_wind_dir >= 23  && data_wind_dir <= 68)  windDegString = "\234";    //"Північно-східний";
  if(data_wind_dir >= 69  && data_wind_dir <= 114) windDegString = "\230";    //"Східний";
  if(data_wind_dir >= 115 && data_wind_dir <= 160) windDegString = "\235";    //"Південно-східний";
  if(data_wind_dir >= 161 && data_wind_dir <= 206) windDegString = "\210";    //"Південний";
  if(data_wind_dir >= 207 && data_wind_dir <= 252) windDegString = "\232";    //"Південно-західний";
  if(data_wind_dir >= 253 && data_wind_dir <= 298) windDegString = "\231";    //"Західний";
  if(data_wind_dir >= 299 && data_wind_dir <= 344) windDegString = "\233";    //"Північно-західний";

  weatherString = "         "+String(location_name)+", "+tNow+":    \212 "+String(location_temp, 1)+" ("+String(location_temp_min,1)+"..."+String(location_temp_max,1)+")"+("\202")+"C";
  weatherString += "     \213 " + String(location_rh) + "%";
  weatherString += "     \215 " + String((location_pres), 0) + tPress;
  weatherString += "     \214 " + windDegString + String(location_wind_spd, 1) + tSpeed;
  weatherString += "     \216 " + String(location_clouds) + "%     " + data_weather_description + "                ";
  updateForecast = 0;
}

// ============================================================================//
//               Беремо ПРОГНОЗ!!! погоди з сайту https://www.weatherbit.io     // 
// ============================================================================//
void getWeatherDataz0() {
  if(!WIFI_connected) {
    updateForecasttomorrow++;
    if(updateForecast >= 360) weatherStringZ = "";
    return;
  }
    //if(printCom) printTime();
  //if(printCom) Serial.println("Getting weather forecast for tomorrow...");
  HTTPClient http;
  String line="";
  String reqline="http://"+weatherHost0+"/v2.0/forecast/daily?city="+urlencode(cityID0)+"&lang="+weatherLang+"&days=2&key="+weatherKey0;
  if(printCom) {
    Serial.println("=======================================================");
    Serial.println(reqline);
    Serial.println("=======================================================");
  }  
  if (http.begin(ESPclient, reqline)) { // HTTP

   int httpCode = http.GET();
   if (httpCode > 0) {
     Serial.printf("[HTTP] GET... code: %d\n", httpCode);
     if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
      line = http.getString();
     }
   } else {
     Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
   }
   http.end();
  } else {
   Serial.printf("[HTTP} Unable to connect\n");
  }
  if(printCom) {
    Serial.print("line2=");
    Serial.println(line);
  }
  
  const size_t capacity = JSON_ARRAY_SIZE(2) + 2*JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(7) + 2*JSON_OBJECT_SIZE(37) + 2321;
  DynamicJsonDocument doc(capacity);
  deserializeJson(doc, line);
  if(!doc.capacity()){
    if(printCom) Serial.println("          Parse weather forecast for tomorrow - FAILED!!!");
    updateForecasttomorrow++;
    if(updateForecast >= 360) weatherStringZ = "";
    return;
  }
  JsonObject data_0 = doc["data"][0];
  JsonObject data_0_weather = data_0["weather"];
  const char* data_0_weather_description = data_0_weather["description"]; // "Помірний дощ"
  float data_0_max_temp = data_0["max_temp"]; // 13.4
  float data_0_min_temp = data_0["min_temp"]; // 10.9
  JsonObject data_1 = doc["data"][1];
  int data_1_rh = data_1["rh"]; // 75
  float data_1_pres = data_1["pres"]; // 1000.56
  int data_1_clouds = data_1["clouds"]; // 58
  float data_1_wind_spd = data_1["wind_spd"]; // 3.75302
  JsonObject data_1_weather = data_1["weather"];
  const char* data_1_weather_description = data_1_weather["description"]; // "Світло душ дощ"
  float data_1_max_temp = data_1["max_temp"]; // 16.3
  float data_1_min_temp = data_1["min_temp"]; // 10

  weatherStringZ = "";
  if(hour<18) weatherStringZ += tCurr + ":";
  if(hour<12) weatherStringZ += "   \212" + String(data_0_min_temp, 1) + "...." + String(data_0_max_temp, 1) + "\202" + "C  ";
  if(hour<18) weatherStringZ += "   " + String(data_0_weather_description) + "     ";
  weatherStringZ += tTom + ":   \212" + String(data_1_min_temp, 1) + "...." + String(data_1_max_temp, 1) + "\202" + "C";
  weatherStringZ += "     \213 " + String(data_1_rh) + "%";
  weatherStringZ += "     \214 " + String(data_1_wind_spd, 1) + tSpeed;
  weatherStringZ += "     " + String(data_1_weather_description);
  weatherStringZ += "                   ";
  if(printCom) Serial.println("          Getting weather forecast for tomorrow - is OK.");
  updateForecasttomorrow = 0;
}
// =======================================================================//
//               Беремо ПРОГНОЗ!!! погоди з сайту openweathermap.org      //
// =======================================================================//
void getWeatherDataz1(){
    if(!WIFI_connected) {
    updateForecasttomorrow++;
    if(updateForecast >= 360) weatherStringZ = "";
    return;
  }
    //if(printCom) printTime();
  //if(printCom) Serial.println("Getting weather forecast for tomorrow...");
  HTTPClient http;
  String line="";
  String reqline="http://"+weatherHost1+"/data/2.5/forecast/daily?id="+urlencode(cityID1)+"&units=metric&appid="+weatherKey1+"&lang="+weatherLang+"&cnt=2";
  if(printCom) {
    Serial.println("=======================================================");
    Serial.println(reqline);
    Serial.println("=======================================================");
  }  
  if (http.begin(ESPclient, reqline)) { // HTTP

   int httpCode = http.GET();
   if (httpCode > 0) {
     Serial.printf("[HTTP] GET... code: %d\n", httpCode);
     if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
      line = http.getString();
     }
   } else {
     Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
   }
   http.end();
  } else {
   Serial.printf("[HTTP} Unable to connect\n");
  }
  if(printCom) {
    Serial.print("line2=");
    Serial.println(line);
  }
  
  const size_t capacity = 2*JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(2) + 2*JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + 3*JSON_OBJECT_SIZE(6) + 2*JSON_OBJECT_SIZE(10) + 1281;
  DynamicJsonDocument doc(capacity);
  deserializeJson(doc, line);
  if(!doc.capacity()){
    if(printCom) Serial.println("          Parse weather forecast for tomorrow - FAILED!!!");
    updateForecasttomorrow++;
    if(updateForecast >= 360) weatherStringZ = "";
    return;
  }
  
  JsonObject city = doc["city"];
  JsonObject list_0 = doc["list"][0];
  JsonObject list_0_temp = list_0["temp"];
  float data_0_min_temp = list_0_temp["min"]; // 9.63
  float data_0_max_temp = list_0_temp["max"]; // 9.69
  JsonObject list_0_weather_0 = list_0["weather"][0];
  const char* data_0_weather_description = list_0_weather_0["description"]; // "облачно"
  JsonObject list_1 = doc["list"][1];
  JsonObject list_1_temp = list_1["temp"];
  float data_1_day_temp = list_1_temp["day"]; // 18.13
  float data_1_min_temp = list_1_temp["min"]; // 10.67
  float data_1_max_temp = list_1_temp["max"]; // 20.32
  int data_1_rh = list_1["humidity"]; // 56
  JsonObject list_1_weather_0 = list_1["weather"][0];
  const char* data_1_weather_description = list_1_weather_0["description"]; // "слегка облачно"
  float data_1_wind_spd = list_1["speed"]; // 0.7
  int data_1_clouds = list_1["clouds"]; // 38

  weatherStringZ = "";
  if(hour<18) weatherStringZ += tCurr + ":";
  if(hour<12) weatherStringZ += "   \212" + String(data_0_min_temp, 1) + "...." + String(data_0_max_temp, 1) + "\202" + "C  ";
  if(hour<18) weatherStringZ += "   " + String(data_0_weather_description) + "     ";
  weatherStringZ += tTom + ":   \212" + String(data_1_min_temp, 1) + "...." + String(data_1_day_temp, 1) + "...." + String(data_1_max_temp, 1) + "\202" + "C";
  weatherStringZ += "     \213 " + String(data_1_rh) + "%";
  weatherStringZ += "     \214 " + String(data_1_wind_spd, 1) + tSpeed;
  weatherStringZ += "     \216 " + String(data_1_clouds) + "%     "  + String(data_1_weather_description);
  weatherStringZ += "                   ";
  if(printCom) Serial.println("          Getting weather forecast for tomorrow - is OK.");
  updateForecasttomorrow = 0;
}
//=========================================================================================================
//                                  narodmon.ru
void getNarodmon(){
  if(!WIFI_connected)  return;
  if(printCom) {
    printTime();
    Serial.println("Connection to narodmon.ru");
  }
  if(ESPclient.connect("http://narodmon.ru", 80)) {
    if(printCom) Serial.println("connection failed");
    return;
  }
  if(!sensors_ID0) return;
  String line="";
  String reqline="http://narodmon.ru/api/sensorsValues?sensors=";
  if(sensors_ID0) reqline+=String(sensors_ID0);
  if(sensors_ID1) reqline+=","+String(sensors_ID1);
  if(sensors_ID2) reqline+=","+String(sensors_ID2);
  reqline+="&uuid="+uuid+"&api_key="+api_key;
  if(printCom) {
    Serial.println("=======================================================");
    Serial.println(reqline);
    Serial.println("=======================================================");
  }
  HTTPClient http;  
  if(http.begin(ESPclient, reqline)){ // HTTP
    int httpCode = http.GET();
    if(httpCode>0){
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY){
        line = http.getString();
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  } else {
    Serial.printf("[HTTP} Unable to connect\n");
  }
  if(printCom) {
    Serial.print("answer=");
    Serial.println(line);
  }
  const size_t capacity = JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(6) + 340; //https://arduinojson.org/v6/assistant/
  DynamicJsonDocument doc(capacity);
  deserializeJson(doc, line);
  if(!doc.capacity()){
    if(printCom) Serial.println("          Parse weather forecast - FAILED!!!");
    return;
  }
  JsonObject sensors_0 = doc["sensors"][0];
  float sensors_0_value = sensors_0["value"]; // 14.2
  long sensors_0_time = sensors_0["time"]; // 1571853360
  JsonObject sensors_1 = doc["sensors"][1];
  float sensors_1_value = sensors_1["value"]; // 14
  long sensors_1_time = sensors_1["time"]; // 1571853000
  JsonObject sensors_2 = doc["sensors"][2];
  float sensors_2_value = sensors_2["value"];
  long sensors_2_time = sensors_2["time"];

  long timestamp = epochNM + (millis()/1000);
  if(printCom){
    printTime();
    Serial.println("sensors_0 = "+String(sensors_0_value, 1)+"'C    sensors_1 = "+String(sensors_1_value, 1)+"'C    sensors_2 = "+String(sensors_2_value, 1)+"'C");
    Serial.println("time_0 = "+String(timestamp-sensors_0_time)+"      time_1 = "+String(timestamp-sensors_1_time)+"      time_2 = "+String(timestamp-sensors_2_time));
  }
  tempNM=0;
  if(sensors_ID0){
    if((timestamp-sensors_0_time)>3600){
      sensors_0_value=99;
    } else tempNM=sensors_0_value;
  }
  if(sensors_ID1){
    if((timestamp-sensors_1_time)>3600) {
      sensors_1_value=99;
    } else if(tempNM>sensors_1_value) tempNM=sensors_1_value;
  }
  if(sensors_ID2){
    if((timestamp-sensors_2_time)>3600){
      sensors_2_value=99;
    } else if(tempNM>sensors_2_value) tempNM=sensors_2_value;
  }
  if(!tempNM&&!updateForecast) tempNM=location_temp;
  Serial.println("tempNM = "+String(tempNM, 1)+"'C");
}
//=========================================================================================================
void wifiConnect(){
  if(printCom) {
    printTime();
    Serial.print("Connecting WiFi (ssid="+String(ssid.c_str())+"  pass="+String(password.c_str())+") ");
  }
  if(!firstStart) printStringWithShift("WiFi", 15);
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());
  for(int i=1; i<21; i++){
    if(WiFi.status()==WL_CONNECTED){
      WIFI_connected=true;
      if(printCom) Serial.print(" IP adress : ");
      if(printCom) Serial.println(WiFi.localIP());
      if(!firstStart){
        String aaa = WiFi.localIP().toString() + "                ";
        if(NUM_MAX>4){
          for(int j=0; j<NUM_MAX-4; j++) aaa+="  ";
        }
        clr();
        printStringWithShift(" IP: ", 15);
        printStringWithShift(aaa.c_str(), 25);
      }
      firstStart=1;
      timeUpdateNTP();
      amountNotStarts=0;
      return;
    }
    if(printCom) Serial.print(".");
    if(!firstStart){
      int j = 0;
      while(j < 500){
        if(j % 10 == 0) showAnimWifi(i);
        j++;
        delay(1);
      }
    }
    delay (800);
  }
  WiFi.disconnect();
  if(printCom) Serial.println(" Not connected!!!");
  amountNotStarts++;
  if(printCom) {
    Serial.print("Amount of the unsuccessful connecting = ");
    Serial.println(amountNotStarts);
  }
  if(amountNotStarts>21) {
    amountNotStarts=0;
    firstStart=0;
    ESP.reset();
  }
  if(!firstStart){
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(ssidAP.c_str(), passwordAP.c_str());
    if(printCom) {
      printTime();
      Serial.println("Start AP mode!!!");
      Serial.print("          Wifi AP IP : ");
      Serial.println(WiFi.softAPIP());
    }
    updateTime();
    printStringWithShift(tPoint.c_str(), 35);
    //firstStart=1;
  }
}
// ===========================КОНВЕРТАЦІЯ НАЗВ ДНІВ ТИЖНЯ НА УКРАЇНСЬКУ МОВУ============================================
void convertDw(){
  switch(dayOfWeek){
    case 1 : dw = tSunday;    break;
    case 2 : dw = tMonday;    break;
    case 3 : dw = tTuesday;   break;
    case 4 : dw = tWednesday; break;
    case 5 : dw = tThursday;  break;
    case 6 : dw = tFriday;    break;
    case 7 : dw = tSaturday;  break;
  }
}
// ===========================КОНВЕРТАЦІЯ НАЗВ МІСЯЦІВ НА УКРАЇНСЬКУ МОВУ============================================
void convertMonth(){
  switch(month){
    case 1 : _month = tJanuary;      break;
    case 2 : _month = tFebruary;     break;
    case 3 : _month = tMarch;        break;
    case 4 : _month = tApril;        break;
    case 5 : _month = tMay;          break;
    case 6 : _month = tJune;         break;
    case 7 : _month = tJuly;         break;
    case 8 : _month = tAugust;       break;
    case 9 : _month = tSeptember;    break;
    case 10 : _month = tOctober;     break;
    case 11 : _month = tNovember;    break;
    case 12 : _month = tDecember;    break;
  }
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void sensors() {
    sensorsDs18b20();
    sensorsSi7021();
    sensorsBmp();
    sensorsBme();
    sensorsDht();
    t0 = (sensorDom==0?0:sensorDom==1?tempDs18b20:sensorDom==2?celsiusSi7021:sensorDom==3?tempBmp:sensorDom==4?tempBme:sensorDom==5?tempDht:sensorDom==6?tMqtt5:0);
    t1 = (sensorDom==0?0:sensorDom==1?(int)tempDs18b20:sensorDom==2?(int)celsiusSi7021:sensorDom==3?(int)tempBmp:sensorDom==4?(int)tempBme:sensorDom==5?(int)tempDht:sensorDom==6?(int)tMqtt5:0);
    t2 = (sensorDom==0?0:sensorDom==1?((int)(tempDs18b20*(tempDs18b20<0?-10:10))%10):sensorDom==2?((int)(celsiusSi7021*(celsiusSi7021<0?-10:10))%10):sensorDom==3?((int)(tempBmp*(tempBmp<0?-10:10))%10):sensorDom==4?((int)(tempBme*(tempBme<0?-10:10))%10):sensorDom==5?((int)(tempDht*(tempDht<0?-10:10))%10):sensorDom==6?((int)(tMqtt5*(tMqtt5<0?-10:10))%10):0);
    t3 = (sensorUl==0?0:sensorUl==1?(int)tempDs18b20:sensorUl==2?(int)celsiusSi7021:sensorUl==3?(int)tempBmp:sensorUl==4?(int)tempBme:sensorUl==5?(int)tempDht:sensorUl==6?(int)tMqtt5:sensorUl==7?(int)tempNM:0);
    t4 = (sensorUl==0?0:sensorUl==1?((int)(tempDs18b20*(tempDs18b20<0?-10:10))%10):sensorUl==2?((int)(celsiusSi7021*(celsiusSi7021<0?-10:10))%10):sensorUl==3?((int)(tempBmp*(tempBmp<0?-10:10))%10):sensorUl==4?((int)(tempBme*(tempBme<0?-10:10))% 10):sensorUl==5?((int)(tempDht*(tempDht<0?-10:10)) % 10):sensorUl==6?((int)(tMqtt5*(tMqtt5<0?-10:10))%10):sensorUl==7?((int)(tempNM*(tempNM<0?-10:10))%10):0);
    t5 = (sensorUl==0?0:sensorUl==1?tempDs18b20:sensorUl==2?celsiusSi7021:sensorUl==3?tempBmp:sensorUl==4?tempBme:sensorUl==5?tempDht:sensorUl==6?tMqtt5:sensorUl==7?tempNM:0);
  if(sensorHumi == 0) {
    h1 = 0;
    h2 = 0;
    h3 = 0;
  }
  if(sensorHumi == 2){
    h1 = humSi7021 / 10;
    h2 = int(humSi7021) % 10;
    h3 = int(humSi7021 * 10) % 10;
  }
  if(sensorHumi == 4){
    h1 = humBme / 10;
    h2 = int(humBme) % 10;
    h3 = int(humBme * 10) % 10;
  }
  if(sensorHumi == 5){
    h1 = humiDht / 10;
    h2 = int(humiDht) % 10;
    h3 = int(humiDht * 10) % 10;
  }
}
//--------------------------------------------------------------------------
void sensorsDs18b20() {  //1
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  if(!ds.search(addr)) {                                // Стартуємо функцію пошук першого або наступного датчика в addr-возвращаем ответ датчика
    ds.reset_search();                                  // Якщо добігли кінця адресного простору, то скидуємо адрес на початок простору
    delay(250);                                         // Пауза
    return;                                             // Виходимо з підпрограми
  }
  if(OneWire::crc8(addr, 7) != addr[7]) return;           // перевіряємо 7 байт в addr - он содержит crc8
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);
  delay(750);
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);
  for(byte i = 0; i < 9; i++) {
    data[i] = ds.read();
  }
  int16_t raw = (data[1] << 8) | data[0];
  if(type_s) {
    raw = raw << 3;
    if(data[7] == 0x10) {
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    if(cfg == 0x00) raw = raw & ~7;
    else if(cfg == 0x20) raw = raw & ~3;
    else if (cfg == 0x40) raw = raw & ~1;
  }
  tempDs18b20 = (float)raw / 16.00 + (sensorDom == 1 ? corrTempD : corrTempU);
  if(printCom) {
    printTime();
    Serial.println("Temperature DS18B20: " + String(tempDs18b20) + " *C");
  }
}
//--------------------------------------------------------------------------
void sensorsSi7021() {  //2
  if(si7021 == false) return;
  humSi7021 = sensor.readHumidity()+ corrHumi;
  celsiusSi7021 = sensor.readTemperature()  + (sensorDom == 2 ? corrTempD : corrTempU);
  if(printCom) {
    printTime();
    Serial.println("Temperature Si7021: " + String(celsiusSi7021) + " *C,  Humidity: " + String(humSi7021) + " %");
  }
}
//--------------------------------------------------------------------------
void sensorsBmp() {  //3
  if(bmp280 == true) {
    tempBmp = bmp.readTemperature() + (sensorDom == 3 ? corrTempD : corrTempU);
    pressBmp = bmp.readPressure() * 0.00750063755419211 + corrPress;
    pressBmp = (int) pressBmp;
    altBmp = bmp.readAltitude(1013.25);
    if(printCom) {
      printTime();
      if(bmp280 == true) Serial.println("Temperature BMP280: " + String(tempBmp) + " *C,  Pressure: " + String(pressBmp) + " mmHg,  Approx altitude: " + String(altBmp) + " m");
    }
  }
  if(BMP180 == true) {
    tempBmp = bmp180.readTemperature() + (sensorDom == 3 ? corrTempD : corrTempU);
    pressBmp = bmp180.readPressure() * 0.00750063755419211 + corrPress;
    pressBmp = (int) pressBmp;
    altBmp = bmp180.readAltitude(101500);
    if(printCom) {
      printTime();
      if(BMP180 == true) Serial.println("Temperature BMP180: " + String(tempBmp) + " *C,  Pressure: " + String(pressBmp) + " mmHg,  Approx altitude: " + String(altBmp) + " m");
    }
  }
}
//--------------------------------------------------------------------------
void sensorsBme() {  //4
  if(bme280 == false) return;
  tempBme = bme.readTempC() + (sensorDom == 4 ? corrTempD : corrTempU);          //bme.readTempF()
  humBme = bme.readHumidity() + corrHumi;
  pressBme = bme.readPressure()/1.333223689017149 + corrPress;
  pressBme = (int) pressBme;
  altBme = bme.readAltitudeFeet();   //bme.readAltitudeMeter()  bme.readAltitudeFeet()
  if(printCom) {
    printTime();
    Serial.println("Temperature BME280: " + String(tempBme) + " *C,  Humidity: " + String(humBme) + " %,  Pressure: " + String(pressBme) + " mmHg,  Approx altitude: " + String(altBme) + " m");
  }
}
//--------------------------------------------------------------------------
void sensorsDht() {   //5
  int err = SimpleDHTErrSuccess;
  int err2 = SimpleDHTErrSuccess;
  byte temp11 = 0;
  byte humi11 = 0;
  if ((err2 = dht22.read2(pinDHT, &tempDht, &humiDht, NULL)) == SimpleDHTErrSuccess) {
    tempDht = tempDht + (sensorDom == 5 ? corrTempD : corrTempU);
    humiDht = (int) (humiDht + corrHumi);
    if(printCom) {
      printTime();
      Serial.println("Temperature DHT22: " + String(tempDht) + " *C,  Humidity: " + String(humiDht) + " %");
    }
  }
  if ((err = dht11.read(pinDHT, &temp11, &humi11, NULL)) == SimpleDHTErrSuccess) {
    tempDht = temp11 + (int) (sensorDom == 5 ? corrTempD : corrTempU);
    humiDht = humi11 + (int) (corrHumi);
    if(printCom) {
      printTime();
      Serial.println("Temperature DHT11: " + String(tempDht) + " *C,  Humidity: " + String(humiDht) + " %");
    }
  }
}
//--------------------------------------------------------------------------
void printTime() {
  if(printCom) Serial.print((hour < 10 ? "0" : "") + String(hour) + ":" + (minute < 10 ? "0" : "") + String(minute) + ":" + (second < 10 ? "0" : "") + String(second) + "  ");
}
//--------------------------------------------------------------------------
void bip(){
  if(!buzzerSet){
    tone(buzzerPin, 2000, 40);
    delay(250);
    noTone(buzzerPin);
  } else {
    digitalWrite(buzzerPin, HIGH);
    delay(120);
    digitalWrite(buzzerPin, LOW);
    delay(120);
  }
}
//--------------------------------------------------------------------------
byte alarms() {
  for(byte i = 0; i < 5; i++) {
    if(alarme[i][0]==hour&&alarme[i][1]==minute&&(alarme[i][2]==dayOfWeek||(alarme[i][2]==8&&(dayOfWeek>1&&dayOfWeek<7))||(alarme[i][2]==9&&dayOfWeek>1)||(alarme[i][2]==10&&(dayOfWeek==1||dayOfWeek==7))||alarme[i][2]>10)){
      alarm_numer=i;
      return 1;
    }
  }
  alarm_numer=255;
  return 0;
}
//------------ function urlencode for weather parameters --------------------
String urlencode(String str) {    // функция взята от http://forum.amperka.ru/members/benben.19545/
    String encodedString="";
    char c;
    char code0;
    char code1;
    for (int i =0; i < str.length(); i++){
      c=str.charAt(i);
      if (c == ' '){
        encodedString+= '+';
      } else if (isalnum(c)){
        encodedString+=c;
      } else{
        code1=(c & 0xf)+'0';
        if ((c & 0xf) >9){
            code1=(c & 0xf) - 10 + 'A';
        }
        c=(c>>4)&0xf;
        code0=c+'0';
        if (c > 9){
            code0=c - 10 + 'A';
        }
        encodedString+='%';
        encodedString+=code0;
        encodedString+=code1;
      }
      yield();
    }
    return encodedString;
}
//------------ function chr_to_str --------------------
String chr_to_str(String str) {
  String chr_to_str = "";
  for (int i =0; i < str.length(); i++){
    chr_to_str += str.charAt(i);
  }
  return chr_to_str;
}
