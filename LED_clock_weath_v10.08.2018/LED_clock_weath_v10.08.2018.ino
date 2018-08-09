/*_______By IvanUA___________
 Піни LED------NodeMCU  1.0  |
  DataIn_____D7/GPIO 13      |
  LOAD/CS____D8/GPIO 15      |
  CLK________D5/GPIO 14      |
                             |
 Бaзер_______D6/GPIO 12      |
 DS18B20_____D3/GPIO 0       |
 Si7021 DA___D2/GPIO 4       | 
 Si7021 CL___D1/GPIO 5       |
 GND - FotoRezistor - A0     |
 +3,3 - rezistor 2-100k - A0 |
                             |
 BMP280 DA___D2/GPIO 4       |
 BMP280 CL___D1/GPIO 5       |
                             |
 DHT22_______D4/GPIO 2       |
_____________________________|
*/
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
#include "BlueDot_BME280.h"
#include <SimpleDHT.h>
ESP8266HTTPUpdateServer httpUpdater;
WiFiClient ESPclient;
PubSubClient MQTTclient(ESPclient);
ESP8266WebServer server(80);                                                            // Веб сервер
File fsUploadFile;
IPAddress apIP(192, 168, 4, 1);

// =====================================================================================
String ssid = "IvanUA";                                                                 // Назва локального WiFi
String password = "";                                                                   // Пароль локального WiFi
String ssidAP      = "WiFi-Clock";                                                      // Назва точки доступу
String passwordAP  = "" ;                                                               // Пароль точки доступу
String weatherKey  = "********************************";                                // Ключ для отримання прогнозу погоди
String weatherLang = "en";                                                              // Мова отримання прогнозу погоди
String cityID      = "703845";
// ----------змінні для роботи з mqtt сервером
char mqtt_server[21] = "m11.cloudmqtt.com";                                             // Имя сервера MQTT
int  mqtt_port = 11011;                                                                 // Порт для подключения к серверу MQTT
char mqtt_user[25] = "********";                                                        // Логи от сервер
char mqtt_pass[25] = "************";                                                    // Пароль от сервера MQTT
char mqtt_name[25] = "ESP-12_Czasy";
char mqtt_sub_inform[25] = "Inform/mess";
char mqtt_sub[25] = "Ulica/temp";
char mqtt_pub_temp[25] = "Clock_ESP-12/temp";
char mqtt_pub_tempUl[25] = "Clock_ESP-12/tempUl";
char mqtt_pub_hum[25] = "Clock_ESP-12/hum";
char mqtt_pub_press[25] = "Clock_ESP-12/press";
char mqtt_pub_alt[25] = "Clock_ESP-12/alt";
bool mqttOn = true;
// =====================================================================================
bool printCom = true;
#define MAX_DIGITS 16
#define NUM_MAX 4
byte volBrightnessD  = 8;
byte volBrightnessN  = 2;
bool volBrightnessAuto = 0;
byte levelBridhtness = 0;
byte timeDay = 7;
byte timeNight = 23;
int rotate = 90;
byte timeScrollStart = 6;
byte timeScrollStop = 23;
byte timeScrollSpeed = 20;
byte lang = 0;             // 0-ukr, 1-rus, 2-pol,  3-czech, 4-de, 5-en
// ---------- для ESP-01
//#define DIN_PIN   2                                                                   // D4
//#define CS_PIN    0                                                                   // D3
//#define CLK_PIN   3                                                                   // RX
//#define buzzerPin 1                                                                   // TX 
// ---------- для NodeMCU 1.0
#define DIN_PIN   13                                                                    //GPIO 13 / D7
#define CS_PIN    15                                                                    //GPIO 15 / D8
#define CLK_PIN   14                                                                    //GPIO 14 / D5
#define buzzerPin 12                                                                    //GPIO 12 / D6
bool buzzerSet = 1;
#define brightPin A0
OneWire  ds(0);                                                                         // DS18B20 подключен к 10 пину (резистор на 4.7к обязателен)
int pinDHT22 = 2;
SimpleDHT22 dht22;
#define BUT_PIN   16
// ----------
#include "max7219.h"
#include "fonts.h"
boolean WIFI_connected = false;
// ---------- Настройка оновлення часу
IPAddress timeServerIP;
String ntpServerName = "ntp.time.in.ua";
const int NTP_PACKET_SIZE = 48;
byte packetBuffer[NTP_PACKET_SIZE];
WiFiUDP udp;
unsigned int localPort = 2390;
static const uint8_t monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};        // Кількість днів у місяцях
#define LEAP_YEAR(Y) (((1970+Y)>0) && !((1970+Y)%4) && (((1970+Y)%100)||!((1970+Y)%400)))   // Високосні літа
String weatherHost = "api.openweathermap.org";
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
// ---------- Змінні для роботи локального годинника
float timeZone = 2.0;                                                                       //  часовий пояс
bool isDayLightSaving = true;
long localEpoc = 0;
long localMillisAtUpdate = 0;
int hour=22, minute=41, second=0, month=4, day=6, dayOfWeek=6, year=2018;
int g_hour, g_minute, g_second, g_month=1, g_day, g_dayOfWeek, g_year;
bool statusUpdateNtpTime = 0;                                                               // якщо не "0" - то останнє оновленя часу було вдалим
String y, mon, wd, d, h, m, s, mes;
uint8_t hourTest[3], minuteTest[3];
int secFr, lastSecond;
String date;
byte kuOn = 7;
byte kuOff = 23;
bool clockNight=0;
// ----------
String cityName;
int cityId;
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
bool ds18b20 = true;
bool ds18b20Out = false;
bool outForecast = true;
int updateForecast = 0;
int updateForecasttomorrow = 0;
byte t1 = 85;
byte t2 = 0;
byte t3 = 85;
byte t4 = 0;
byte h1 = 0;
byte h2 = 0;
byte h3 = 0;
byte tMqtt3 = 0;
byte tMqtt4 = 0;
byte tMqtt5 = 0;
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
float tempBmp = 0;
float pressBmp = 0;
float altBmp = 0;
bool bmp280 = false;
bool bme280 = false;
float tempDht22 = 0;
float humiDht22 = 0;
int err = SimpleDHTErrSuccess;
Adafruit_Si7021 sensor = Adafruit_Si7021();
float hum = 0;
float humSi7021 = 0;
float celsiusSi7021 = 0;
bool si7021 = false;
byte sensorDom = 1;          //NONE = 0, DS18B20 = 1, Si7021 = 2, BMP280 = 3, BME280 = 4, DHT22 = 5, MQTT = 6;
byte sensorUl = 6;           //NONE = 0, DS18B20 = 1, Si7021 = 2, BMP280 = 3, BME280 = 4, DHT22 = 5, MQTT = 6;
byte sensorHumi = 0;         //NONE = 0, NONE    = 1, Si7021 = 2, NONE   = 3, BME280 = 4, DHT22 = 5, NONE = 6;
byte sensorPrAl = 0;         //NONE = 0, NONE    = 1, NONE   = 2, BMP280 = 3, BME280 = 4, NONE  = 5, NONE = 6;
String tMes, tNow, tPress, tSpeed, tMin, tTom, tKurs, tSale, tYour, tPoint;
String tWarsaw, tKrivoy, tKyiv, tOdessa, tDnepr, tCherkassy, tLviv, tKherson, tNikolaev, tZaporozhye, tKharkiv, tDonetsk, tLugansk, tPoltava, tSumy, tChernigov, tZhytomyr;
String tRivne, tKropivnitsky, tUman, tVinnitsa, tKhmelnitsky, tTernopil, tLutsk, tKovel, tChernivtsi, tIvano, tStry, tMukachevo, tUzhgorod, tCzenstochowa, tKrakow, tLublinec;
String tJanuary, tFebruary, tMarch, tApril, tMay, tJune, tJuly, tAugust, tSeptember, tOctober, tNovember, tDecember;
String tMonday, tTuesday, tWednesday, tThursday, tFriday, tSaturday, tSunday;
String tClearSky, tSkyIsClear, tFewClouds, tScatteredClouds, tBrokenClouds, tOvercastClouds, tLightRain, tModerateRain, tLightIntensityShowerRain, tShowerRain, tHeavyIntensityRain, tVeryHeavyRain, tThunderstorm, tHaze, tFog, tMist, tShowerSleet, tLightSnow, tLightShowerSnow, tSnow, tWeatrNot, tWeatrTN;
bool alarm_stat=0;
bool alarm_hold=0;
byte alarm_numer=255;
byte alarme[5][3]{{12, 30, 11},{7, 15, 9},{22, 55, 12},{0, 30, 0},{0, 0, 0}}; //1-часы, 2-минуты, 3-откл(0)/1раз(11)/пон-пят(8)/пон-сб(9)/сб-вс(10)/вс(1)/пон(2)/вто(3)/сре(4)/чет(5)/пят(6)/сб(7)/всегда(12)
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
//======================================================================================
void setup() {
  Serial.begin(115200);
  Serial.println("");
  pinMode(BUT_PIN, INPUT);
  initMAX7219();
  sendCmdAll(CMD_SHUTDOWN, 1);
  sendCmdAll(CMD_INTENSITY, 1);
  SPIFFS.begin();
  // ------------------
  if(bmp.begin()) {
    if(printCom) Serial.println("YES!!! find BMP280 sensor!");
    bmp280 = true;
    sensorsBmp();
  } else {
    if(printCom) Serial.println("Did not find BMP280 sensor!");
  }
  bme.parameter.communication = 0;
  bme.parameter.I2CAddress = 0x76;
  bme.parameter.sensorMode = 0b11;
  bme.parameter.IIRfilter = 0b100;
  bme.parameter.humidOversampling = 0b101;
  bme.parameter.tempOversampling = 0b101;
  bme.parameter.pressOversampling = 0b101;
  bme.parameter.pressureSeaLevel = 1013.25;
  bme.parameter.tempOutsideCelsius = 15;
  bme.parameter.tempOutsideFahrenheit = 59;
  if(bme.init() == 0x60) {
    if(printCom) Serial.println("YES!!! find BME280 sensor!");
    bme280 = true;
    sensorsBme();
  } else {
    if(printCom) Serial.println("Did not find BME280 sensor!");
  }
  if (sensor.begin()) {
    if(printCom) Serial.println("YES!!! find Si7021 sensor!");
    si7021 = true;
    sensorsSi7021();
  } else {
    if(printCom) Serial.println("Did not find Si7021 sensor!");
  }
// ---------- HTTP сторінки для налаштуваня ESP
  SPIFFS.begin();{
    Dir dir=SPIFFS.openDir("/");
    while (dir.next()){
      String fileName=dir.fileName();
      size_t fileSize=dir.fileSize();
    }
  }
  server.serveStatic("/", SPIFFS, "/index.html");
  server.onNotFound([]() {
    if(!handleFileRead(server.uri()))
    server.send(404, "text/plain", "FileNotFound");
    });
  server_init();
// ----------
  loadConfig();
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

// ---------- Підключення до WiFi
  wifiConnect();
// ***********  OTA SETUP
  if(updateOTA) {
    ArduinoOTA.setPort(8266);
    ArduinoOTA.setHostname("ESP-Clock"); 
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
    if(outForecast) getWeatherData();
    if(outForecast) getWeatherDataz();
  }
// ---------- MQTT client
  MQTTclient.setServer(mqtt_server, mqtt_port);
  MQTTclient.setCallback(callback);
  MQTTclient.connect(mqtt_name);
  MQTTclient.subscribe(mqtt_sub_inform);
  MQTTclient.subscribe(mqtt_sub);
}
//======================================================================================
void callback(char* topic, byte* payload, unsigned int length) {
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
  }
  if(String(topic) == mqtt_sub) {
    tMqtt3 = 0;
    tMqtt4 = 0;
    if((payload[0] >= 48 && payload[0] < 58) || payload[0] == 45) { // в payload[0] - хранится первый полученный символ. 48, 58 и 45 - это коды знаков можете их посмотреть в fontUA_RU_PL_DE[]
      if(payload[0] == 45) {                                        // если первый символ = "-" (равен минусу) то tMqtt5 = -1 
        tMqtt5 = -1;
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
      } else {                                                      // здесь таже самая процедура но уже с положительными числами))))) tMqtt5 = 1 - это признак того что число положителньное или отрицательное....
        tMqtt5 = 1;
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
      }
    }
    tMqtt3 = tMqtt3 * tMqtt5;                                        // через tMqtt5 - определяем число будет положительным или отрицательным.....
  }
}
//======================================================================================
void reconnect() {
  if(!mqttOn) return;
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
  //if(printCom) Serial.print("secFr=");
  //if(printCom) Serial.println(secFr);
    secFr = 0;
  } else secFr++;                                                                       // якщо секунда ще не скінчилась то нарощуємо лічильник циклів secFr
  if(minute == 0 && second == 0 && secFr == 0 && (hour >= kuOn && hour < kuOff)) {      // сигнал кожду годину 
    bip();
    bip();
  }
  //----------- РОБОТА З БУДИЛЬНИКОМ------------------------------------------------------
  if(secFr==0){
    if(second>0 && alarms()){
      if(!alarm_stat && alarm_numer!=255 && !alarm_hold) alarm_stat=1;
    } else if(alarm_stat) {
      alarm_stat=0;
      if(alarme[alarm_numer][2]==11) alarme[alarm_numer][2]=0;
    } else if(alarm_hold!=0);
  }
  //------------- РОБОТА ЗІ СВЯТКОВИМИ ДАТАМИ ---------------------------------------------
  if(secFr==0) {
    if(minute==0) {
      if(hour>=memory_hour_start && hour<=memory_hour_end && second<15 && second>2){
        for(byte i = 0; i < 9; i++) {
          if(memory_date[i][0]==day && memory_date[i][1]==month){
            m_date=i;
            bip();
            bip();
            bip();
            printStringWithShift(("         "), timeScrollSpeed);
            printStringWithShift((m_date==0?memory_date_mes0:m_date==1?memory_date_mes1:m_date==2?memory_date_mes2:m_date==3?memory_date_mes3:m_date==4?memory_date_mes4:m_date==5?memory_date_mes5:m_date==6?memory_date_mes6:m_date==7?memory_date_mes7:memory_date_mes8), timeScrollSpeed);
            break;
          }
        }
      } 
    } else m_date=0;
  }
  //------------- РОБОТА З КНОПКОЮ --------------------------------------------------------
  if(digitalRead(BUT_PIN)==LOW){
    if(alarm_stat) {
      alarm_stat=0;
      alarm_hold=1;
      if(alarme[alarm_numer][2]==11) alarme[alarm_numer][2]=0;
    } else {
      showSimpleTemp();
      return;
    }
  }
  //------------- НАШ ЧАС ----------------------------------------------------------------
  if(hour == 22 && minute == 55) {                                                      // якщо наш час - то іде повідомлення для коханої
    bip();
    bip();
    bip();
    printStringWithShift(("       22:55 \200\200\200 " + tMes + " \200\200\200").c_str(), timeScrollSpeed);
    return;
  }
  // ---------- ВИВІД НА ЕКРАН ГОДИННИКА АБО ТЕМПЕРАТУРИ ЧИ ВОЛОГОСТІ------------------------
  if(!alarm_stat && millis() % 50 == 0){
    if((clockNight && hour>=timeDay && hour<timeNight) || !clockNight){
      if(second>=40 && second < 43 && sensorDom){
        showSimpleTemp();
      } else if(second>=43 && second<46 && sensorUl) {
        showSimpleTempU();
      } else if(second>=46 && second<49 && (sensorHumi==2 || sensorHumi==4 || sensorHumi==5)) {
        showSimpleHum();
      } else if(second>=49 && second<52 && (sensorPrAl==3 || sensorPrAl==4)) {
        showSimplePre();
      } else if((hour<timeScrollStart || hour>=timeScrollStop) && second>=10 && second<15) {
        showSimpleDate();
      } else showAnimClock();
    } else showAnimClock();
  } else if(alarm_stat) {
    if(millis() % 50==0) showAnimClock();
    if(secFr==0 && second>1 && second<=59){
      clr();
      refreshAll();
      bip();
      bip();
    }
  }
  // --------------------------------------------------------------------------------------------------------
  if(secFr == 0) {
    // ---------- 10 секунда - виводимо дату/погоду----------------------------------------------------------
    if(second == 10 && !alarm_stat) {
      sensors();
      if(hour >= timeScrollStart && hour < timeScrollStop) {        // працує тілки в дозволений час
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
      }// else showSimpleDate();
    }
    // ---------- 41 перевірка доступності WiFi мережі ---// повторне підк. до WiFi кожну 1, 6, 11, 16...56 хв.
    if(second == 41 && WiFi.status() != WL_CONNECTED && !alarm_stat) {
      WIFI_connected = false;
      WiFi.disconnect();
      if(minute % 10 == 1 || minute % 10 == 6) {
        wifiConnect();
        if(WiFi.status() == WL_CONNECTED) WIFI_connected = true;
      }
    }
    // ---------- 43 секунда оновленя мережевого часу кожну хвилину або в 5 хвилину кожного часу
    if(((statusUpdateNtpTime==0 && second==43) || (minute==02 && second==43)) && !alarm_stat) timeUpdateNTP();
    // ---------- 46 cек. оновлюємо прогноз погоди ------------------------------------- 
    if(second == 46 && hour >= timeScrollStart && hour <= timeScrollStop && !alarm_stat) {
      if(minute == 15 || minute == 45 || updateForecast || updateForecasttomorrow) {
        if(minute == 15 || minute == 45) {
          if(outForecast) getWeatherData();
          if(outForecast) getWeatherDataz();
        } else {
          if(updateForecast && outForecast) getWeatherData();
          if(updateForecasttomorrow && outForecast) getWeatherDataz();
        }    
        if(!MQTTclient.connected() && mqttOn) reconnect();
      }
    }
    // ---------- 50 сек. перевірка доступності MQTT та публікація температури ---------
    if(second == 50 && mqttOn && !alarm_stat) {
      if(!MQTTclient.connected()) {
        reconnect();
      }
      if(MQTTclient.connected()) {
        if(sensorDom && t1 != 85) MQTTclient.publish(mqtt_pub_temp, (String(t1) + "." + String(t2)).c_str());
        if(sensorUl !=0 && sensorUl != 6 && t3 != 85) MQTTclient.publish(mqtt_pub_tempUl, (String(t3) + "." + String(t4)).c_str());
        if(sensorHumi == 2 && humSi7021 != 0) MQTTclient.publish(mqtt_pub_hum, (String(humSi7021)).c_str());
        if(sensorHumi == 4 && humBme != 0) MQTTclient.publish(mqtt_pub_hum, (String(humBme)).c_str());
        if(sensorHumi == 5 && humiDht22 != 0) MQTTclient.publish(mqtt_pub_hum, (String(humiDht22)).c_str());
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
          if(sensorUl !=0 && sensorUl != 6 && t3 != 85) Serial.print("Na ulice: " + String(t3) + "." + String(t4) + "*C,   ");
          if(sensorHumi == 2 && humSi7021 != 0) Serial.print("Humidity: " + String(humSi7021) + " %,  ");
          if(sensorHumi == 4 && humBme != 0) Serial.print("Humidity: " + String(humBme) + " %,  ");
          if(sensorHumi == 5 && humiDht22 != 0) Serial.print("Humidity: " + String(humiDht22) + " %,  ");
          if(sensorPrAl == 3 && pressBmp != 0) Serial.print("  Pressure: " + String(pressBmp) + " mmHg,  Altitude: " + String(altBmp) + " m.");
          if(sensorPrAl == 4 && pressBme != 0) Serial.print("  Pressure: " + String(pressBme) + " mmHg,  Altitude: " + String(altBme) + " m.");
          Serial.println("");
        }
      }
    }
  }
  // ---------- якщо мережа WiFi доступна то виконуємо наступні функції ----------------------------
  if(WIFI_connected){
    if(mqttOn) MQTTclient.loop();                                                                  // перевіряємо чи намає вхідних повідомлень, як є, то колбек функція
  // 
  }
}
//======================================================================================
//==========ВИВІД НА ЕКРАН ТЕМПЕРАТУРИ В БУДИНКУ========================================
void showSimpleTemp() {
  dx = dy = 0;
  clr();
  showDigit((t1 < 0 ? 14 : 13), 0, dig5x8rn); // друкуємо D+ альбо D-
  if(t1 <= -10.0 || t1 >= 10) showDigit((t1 < 0 ? (t1 * -1) / 10 : t1 / 10), 4, dig5x8rn);
  showDigit((t1 < 0 ? (t1 * -1) % 10 : t1 % 10), 10, dig5x8rn);
  showDigit(12, 16, dig5x8rn);
  showDigit(t2, 18, dig5x8rn);
  showDigit(10, 24, dig5x8rn);
  showDigit(11, 27, dig5x8rn);
  refreshAll();
}
//==========ВИВІД НА ЕКРАН ТЕМПЕРАТУРИ НА ВУЛИЦІ========================================
void showSimpleTempU() {
  if(WiFi.status() == WL_CONNECTED) {
    dx = dy = 0;
    clr();
    showDigit((t3 < 0 ? 16 : 15), 0, dig5x8rn); //друкуємо U+ альбо U-
    if(t3 <= -10.0 || t3 >= 10) showDigit((t3 < 0 ? (t3 * -1) / 10 : t3 / 10), 4, dig5x8rn);
    showDigit((t3 < 0 ? (t3 * -1) % 10 : t3 % 10), 10, dig5x8rn);
    showDigit(12, 16, dig5x8rn);
    showDigit(t4, 18, dig5x8rn);
    showDigit(10, 24, dig5x8rn);
    showDigit(11, 27, dig5x8rn);
    refreshAll();
  }
}
//==========ВИВІД НА ЕКРАН ВОЛОГОСТІ В БУДИНКУ========================================
void showSimpleHum() {
  if(WiFi.status() == WL_CONNECTED) {
    dx = dy = 0;
    clr();
  showDigit(17, 0, dig5x8rn);     // друкуємо знак вологості
  if(h1 >= 0) showDigit(h1, 6, dig5x8rn);
  showDigit(h2, 12, dig5x8rn);
  showDigit(12, 18, dig5x8rn);
  showDigit(h3, 20, dig5x8rn);
  showDigit(18, 26, dig5x8rn);
  refreshAll();
  }
}
//==========ВИВІД НА ЕКРАН ТИСКУ В БУДИНКУ========================================
void showSimplePre() {
  if(WiFi.status() == WL_CONNECTED) {
    dx = dy = 0;
    clr();
  showDigit(19, 0, dig5x8rn);     // друкуємо знак тиску
  showDigit(int(sensorPrAl==3?pressBmp:pressBme / 100), 6, dig5x8rn);
  showDigit((int(sensorPrAl==3?pressBmp:pressBme /10) - int(sensorPrAl==3?pressBmp:pressBme /100) * 10) , 12, dig5x8rn);
  showDigit((sensorPrAl==3?pressBmp:pressBme - int(sensorPrAl==3?pressBmp:pressBme / 10) *10) , 18, dig5x8rn);
  showDigit(20, 24, dig5x8rn);
  showDigit(21, 29, dig5x8rn);
  refreshAll();
  }
}
//==========ВИВІД НА ЕКРАН ДАТИ=========================================================
void showSimpleDate() { 
  dx = dy = 0;
  clr();
  showDigit(day / 10,  0, dig4x8);
  showDigit(day % 10,  5, dig4x8);
  showDigit(month / 10, 12, dig4x8);
  showDigit(month % 10, 17, dig4x8);
  showDigit((year - 2000) / 10, 23, dig4x8);
  showDigit((year - 2000) % 10, 28, dig4x8);
  setCol(10, 0xC0);
  setCol(22, 0xC0);
  refreshAll();
}
//==========ВИВІД НА ЕКРАН АНІМАЦІЙНОГО ГОДИННИКА=======================================
void showAnimClock() {
  byte digPos[6] = {1, 8, 18, 25, 15, 16};//2, 8, 19, 25, 15, 16,
  if(hour < 10) {
    digPos[1] = 5;
    digPos[2] = 15;
    digPos[3] = 22;
    digPos[4] = 12;
    digPos[5] = 13;
  }
  int digHt = 16;
  int num = 4;
  int i;
  if(del == 0) {
    del = digHt;
    for(i = 0; i < num; i++) digold[i] = dig[i];
    dig[0] = hour / 10 ? hour / 10 : 10;
    dig[1] = hour % 10;
    dig[2] = minute / 10;
    dig[3] = minute % 10;
    for(i = 0; i < num; i++)  digtrans[i] = (dig[i] == digold[i]) ? 0 : digHt;
  } else del--;
  clr();
  for(i = 0; i < num; i++) {
    if(digtrans[i] == 0) {
      dy = 0;
      showDigit(dig[i], digPos[i], dig6x8);
    } else {
      dy = digHt - digtrans[i];
      showDigit(digold[i], digPos[i], dig6x8);
      dy =- digtrans[i];
      showDigit(dig[i], digPos[i], dig6x8);
      digtrans[i]--;
    }
  }
  dy = 0;
  int flash = millis() % 1000;
  if(!alarm_stat){
    if((flash >= 180 && flash < 360) || flash >= 540) {                       // мерегтіння двокрапок в годиннику підвязуємо до личильника циклів
      setCol(digPos[4], WIFI_connected ? 0x66 : 0x60);
      setCol(digPos[5], WIFI_connected ? 0x66 : 0x60);
    }
    if(statusUpdateNtpTime) {                                                 // якщо останнє оновленя часу було вдалим, то двокрапки в годиннику будуть анімовані
      if(flash >= 0 && flash < 180) {
        setCol(digPos[4], WIFI_connected ? 0x24 : 0x20);
        setCol(digPos[5], WIFI_connected ? 0x42 : 0x40);
      }
      if(flash >= 360 && flash < 540) {
        setCol(digPos[4], WIFI_connected ? 0x42 : 0x40);
        setCol(digPos[5], WIFI_connected ? 0x24 : 0x20);
      }
    }
    if(updateForecast) setCol(00, flash < 500 ? 0x80 : 0x00);
    if(updateForecasttomorrow) setCol(31, flash < 500 ? 0x80 : 0x00);
  } else {
    setCol(digPos[4], 0x66);
    setCol(digPos[5], 0x66);
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
//======================================================================================
int showChar(char ch, const uint8_t *data) {
  int len = pgm_read_byte(data);
  int i,w = pgm_read_byte(data + 1 + ch * len);
  for(i = 0; i < w; i++)
    scr[NUM_MAX * 8 + i] = pgm_read_byte(data + 1 + ch * len + 1 + i);
    scr[NUM_MAX * 8 + i] = 0;
  return w;
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
//==========ДРУКУВАННЯ БІГУЧОЇ СТРОКИ *s - текст, shiftDelay - швидкість==========================================
void printStringWithShift(const char* s, int shiftDelay) {
  while(*s) {                                                   // коли працює ця функція, основний цикл зупиняється
    printCharWithShift(*s, shiftDelay);
    s++;
    server.handleClient();                                      // зберігаемо можливість відповіді на HTML запити під час бігучої стоки
    if(mqttOn) MQTTclient.loop();                                          // зберігаемо можливість слухати MQTT топік під час бігучої стоки
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
  long epoch = round(curEpoch + 86400L) % 86400L;
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
    minuteTest[timeTest] = g_minute;
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
  localMillisAtUpdate = millis();
  localEpoc = (hour * 60 * 60 + minute * 60 + second);
  convertDw();
  convertMonth();
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
//                              БЕРЕМО ПОГОДУ З САЙТУ api.openweathermap.org                                                     //
//===============================================================================================================================//
void getWeatherData() {
  if(!WIFI_connected) {
    updateForecast++;
    if(updateForecast >= 360) weatherString = tWeatrNot;
    return;
  }
  if(printCom) {
    printTime();
    Serial.println("Getting weather forecast for City " + cityID + "...");
  }
  if(ESPclient.connect(weatherHost.c_str(), 80)) {
    ESPclient.println(String("GET /data/2.5/weather?id=") + cityID + "&units=metric&appid=" + weatherKey + "&lang="+ weatherLang + "\r\n" +
                "Host: " + weatherHost + "\r\nUser-Agent: ArduinoWiFi/1.1\r\n" +
                "Connection: close\r\n\r\n");
  } else {
    if(printCom) Serial.println("          Not connection server!!!");
    updateForecast++;
    if(updateForecast >= 360) weatherString = tWeatrNot;
    return;
  }
  //---------------Якщо було підключення та запрос було відправлено, перевіряємо чи маємо відповідь (чекаємо 0,5с * 10 разів)------
  int repeatCounter = 0;
  while(!ESPclient.available() && repeatCounter < 10) {
    delay(500);
    if(printCom) Serial.println("          w.");
    repeatCounter++;
  }
  //---------------Якщо було підключення то була получена відповідь, то в змінну line записуємо отримані символи окрім ( [ та ] )--
  String line;
  while(ESPclient.connected() && ESPclient.available()) {
    char c = ESPclient.read(); 
    if(c == '[' || c == ']') c = ' ';
    line += c;
  }
  //---------------Зупеняемо роботу WiFi клієнта------------------------------------------------------------------------------
  ESPclient.stop();
  //---------------Зтворюємо json буфер, та парсимо в ньго дані зі змінної line--------------------------------------------------
  DynamicJsonBuffer jsonBuf;
  JsonObject &root=jsonBuf.parseObject(line);
  if(!root.success()){
    if(printCom) Serial.println("          Parse weather forecast - failed!!!");
    updateForecast++;
    if(updateForecast >= 360) weatherString = tWeatrNot;
    return;
  }
  //weatherMain = root["weather"]["main"].as<String>();
  weatherDescription = root["weather"]["description"].as<String>();
  weatherDescription.toLowerCase();
  if(lang!=5) convertWeatherDes();
  //country = root["sys"]["country"].as<String>();
  cityName = root ["name"] .as<String>();
  cityId = root ["id"]; convertCity();
  temp = root["main"]["temp"];
  humidity = root["main"]["humidity"];
  pressure = root["main"]["pressure"];
  pressure = (pressure/1.3332239) - 0;
  windDeg = root["wind"]["deg"];
  windSpeed = root["wind"]["speed"];
  clouds = root["clouds"]["all"];
  String windDegString;
  if(windDeg >= 345 || windDeg <= 22)  windDegString = "\211";    //"Північний";
  if(windDeg >= 23  && windDeg <= 68)  windDegString = "\234";    //"Північно-східний";
  if(windDeg >= 69  && windDeg <= 114) windDegString = "\230";    //"Східний";
  if(windDeg >= 115 && windDeg <= 160) windDegString = "\235";    //"Південно-східний";
  if(windDeg >= 161 && windDeg <= 206) windDegString = "\210";    //"Південний";
  if(windDeg >= 207 && windDeg <= 252) windDegString = "\232";    //"Південно-західний";
  if(windDeg >= 253 && windDeg <= 298) windDegString = "\231";    //"Західний";
  if(windDeg >= 299 && windDeg <= 344) windDegString = "\233";    //"Північно-західний";
  weatherString = "         " + cityName + ", " + tNow + ":    \212 " + String(temp, 0) + ("\202") + "C";
  weatherString += "     \213 " + String(humidity) + "%";
  weatherString += "     \215 " + String(pressure, 0) + tPress;
  weatherString += "     \214 " + windDegString + String(windSpeed, 1) + tSpeed;
  weatherString += "     \216 " + String(clouds) + "%     " + weatherDescription + "          ";
  if(printCom) Serial.println("          Getting weather forecast - is OK.");
  updateForecast = 0;
}
// =======================================================================//
//               Беремо ПРОГНОЗ!!! погоди з сайту openweathermap.org      //
// =======================================================================//
void getWeatherDataz() {
  if(!WIFI_connected) {
    updateForecasttomorrow++;
    if(updateForecast >= 360) weatherStringZ = "";
    return;
  }
  if(printCom) printTime();
  if(printCom) Serial.println("Getting weather forecast for tomorrow...");
  if(ESPclient.connect(weatherHost.c_str(), 80)) {
    ESPclient.println(String("GET /data/2.5/forecast/daily?id=") + cityID + "&units=metric&appid=" + weatherKey + "&lang=" + weatherLang + "&cnt=2" + "\r\n" +
                "Host: " + weatherHost + "\r\nUser-Agent: ArduinoWiFi/1.1\r\n" +
                "Connection: close\r\n\r\n");
  } else {
    if(printCom) Serial.println("          No connection server (for tomorrow)!!!");
    updateForecasttomorrow++;
    if(updateForecast >= 360) weatherStringZ = "";
    return;
  }
  String line;
  int  repeatCounter = 0;
  while(!ESPclient.available() && repeatCounter < 10) {
    delay(500);
    repeatCounter++;
  }
  while(ESPclient.connected() && ESPclient.available()) {
    char c = ESPclient.read(); 
    if(c == '[' || c == ']') c = ' ';
    line += c;
  }
  tvoday (line);
  ESPclient.stop();
  DynamicJsonBuffer jsonBuf;
  JsonObject &root = jsonBuf.parseObject(tempz);
  if(!root.success()){
    if(printCom) Serial.println("          Parse weather forecast for tomorrow - failed!!!");
    updateForecasttomorrow++;
    if(updateForecast >= 360) weatherStringZ = "";
    return;
  }
  //lon = root ["coord"]["lon"];
  //lat = root ["coord"]["lat"];
  float tempMin=root ["temp"]["min"];
  float tempMax=root ["temp"]["max"];  
  float wSpeed=root ["speed"];
  int wDeg=root ["deg"];
  weatherDescription=root ["weather"]["description"].as<String>();
  weatherDescription.toLowerCase();
  if(lang!=5) convertWeatherDes();
  String wDegString;
  if(wDeg >= 345 || wDeg <= 22)  wDegString = "\211";    //"Північний";
  if(wDeg >= 23  && wDeg <= 68)  wDegString = "\234";    //"Північно-східний";
  if(wDeg >= 69  && wDeg <= 114) wDegString = "\230";    //"Східний";
  if(wDeg >= 115 && wDeg <= 160) wDegString = "\235";    //"Південно-східний";
  if(wDeg >= 161 && wDeg <= 206) wDegString = "\210";    //"Південний";
  if(wDeg >= 207 && wDeg <= 252) wDegString = "\232";    //"Південно-західний";
  if(wDeg >= 253 && wDeg <= 298) wDegString = "\231";    //"Західний";
  if(wDeg >= 299 && wDeg <= 344) wDegString = "\233";    //"Північно-західний";
  weatherStringZ = tTom + ":   \212" + String(tempMin, 1) + "...." + String(tempMax, 1) + "\202" + "C";
  weatherStringZ += "     \214 " + wDegString + String(wSpeed, 1) + tSpeed + "     " + weatherDescription + "             ";
  if(printCom) Serial.println("          Getting weather forecast for tomorrow - is OK.");
  updateForecasttomorrow = 0;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void wifiConnect(){
  if(printCom) {
    printTime();
    Serial.print("Connecting WiFi (ssid="+String(ssid.c_str())+"  pass="+String(password.c_str())+") ");
  }
  printStringWithShift("WiFi", 15);
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  for(int i = 1; i < 6; i++){
    WiFi.begin(ssid.c_str(), password.c_str());
    delay (5000);
    if(WiFi.status() == WL_CONNECTED){
      WIFI_connected = true;
      if(printCom) Serial.print(" IP adress : ");
      if(printCom) Serial.println(WiFi.localIP());
      String aaa = WiFi.localIP().toString();
      clr();
      printStringWithShift((tYour + " IP: ").c_str(), 15);
      printStringWithShift(aaa.c_str(), 25);
      timeUpdateNTP();
      return;
    }
    if(printCom) Serial.print(".");
    int j = 0;
    while(j < 500){
      if(j % 10 == 0) showAnimWifi(i);
      j++;
      delay(1);
    }
    //clr();
    //refreshAll();
  }
  if(printCom) Serial.println(" Not connected!!!");
  WiFi.disconnect();
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
}

// =======================================================================
void tvoday(String line){
  String s;
  int strt = line.indexOf('}');
  for(int i = 1; i <= 4; i++){
    strt=line.indexOf('}', strt + 1);
  }
  s = line.substring(2 + strt, line.length());
  tempz = s;
}

// ===========================КОНВЕРТАЦІЯ НАЗВ МІСТ НА УКРАЇНСЬКУ МОВУ============================================
void convertCity(){
  switch(cityId){
    case 756135 : cityName = tWarsaw;        break;
    case 703845 : cityName = tKrivoy;        break;
    case 703448 : cityName = tKyiv;          break;
    case 698740 : cityName = tOdessa;        break;
    case 709930 : cityName = tDnepr;         break;
    case 710791 : cityName = tCherkassy;     break;
    case 702550 : cityName = tLviv;          break;
    case 706448 : cityName = tKherson;       break;
    case 700569 : cityName = tNikolaev;      break;
    case 687700 : cityName = tZaporozhye;    break;
    case 706483 : cityName = tKharkiv;       break;
    case 709717 : cityName = tDonetsk;       break;
    case 702658 : cityName = tLugansk;       break;
    case 696643 : cityName = tPoltava;       break;
    case 692194 : cityName = tSumy;          break;
    case 710735 : cityName = tChernigov;     break;
    case 686967 : cityName = tZhytomyr;      break;
    case 695594 : cityName = tRivne;         break;
    case 705812 : cityName = tKropivnitsky;  break;
    case 690688 : cityName = tUman;          break;
    case 689558 : cityName = tVinnitsa;      break;
    case 706369 : cityName = tKhmelnitsky;   break;
    case 691650 : cityName = tTernopil;      break;
    case 702569 : cityName = tLutsk;         break;
    case 704617 : cityName = tKovel;         break;
    case 710719 : cityName = tChernivtsi;    break;
    case 707471 : cityName = tIvano;         break;
    case 692372 : cityName = tStry;          break;
    case 700646 : cityName = tMukachevo;     break;
    case 690548 : cityName = tUzhgorod;      break;
    case 3100946 : cityName = tCzenstochowa; break;
    case 3094802 : cityName = tKrakow;       break;
    case 3092906 : cityName = tLublinec;     break;
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

// ===========================КОНВЕРТАЦІЯ ХМАРНОСТІ НА УКРАЇНСЬКУ МОВУ============================================
void convertWeatherDes(){
  if(weatherDescription == "clear sky") weatherDescription = tClearSky;
  else if(weatherDescription == "sky is clear") weatherDescription = tSkyIsClear;
  else if(weatherDescription == "few clouds") weatherDescription = tFewClouds;
  else if(weatherDescription == "scattered clouds") weatherDescription = tScatteredClouds;
  else if(weatherDescription == "broken clouds") weatherDescription = tBrokenClouds;
  else if(weatherDescription == "overcast clouds") weatherDescription = tOvercastClouds;
  else if(weatherDescription == "light rain") weatherDescription = tLightRain;  
  else if(weatherDescription == "moderate rain") weatherDescription = tModerateRain;
  else if(weatherDescription == "light intensity shower rain") weatherDescription = tLightIntensityShowerRain;
  else if(weatherDescription == "shower rain") weatherDescription = tShowerRain;
  else if(weatherDescription == "heavy intensity rain") weatherDescription = tHeavyIntensityRain;
  else if(weatherDescription == "very heavy rain") weatherDescription = tVeryHeavyRain;
  else if(weatherDescription == "thunderstorm") weatherDescription = tThunderstorm;
  else if(weatherDescription == "haze") weatherDescription = tHaze;
  else if(weatherDescription == "fog") weatherDescription = tFog;
  else if(weatherDescription == "mist") weatherDescription = tMist;
  else if(weatherDescription == "shower sleet") weatherDescription = tShowerSleet;
  else if(weatherDescription == "light snow") weatherDescription = tLightSnow;
  else if(weatherDescription == "light shower snow") weatherDescription = tLightShowerSnow; 
  else if(weatherDescription == "snow") weatherDescription = tSnow; 
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void sensors() {
    sensorsDs18b20();
    sensorsSi7021();
    sensorsBmp();
    sensorsBme();
    sensorsDht();
    t1 = (sensorDom==0?0:sensorDom==1?(int)tempDs18b20:sensorDom==2?(int)celsiusSi7021:sensorDom==3?(int)tempBmp:sensorDom==4?(int)tempBme:sensorDom==5?(int)tempDht22:sensorDom==6?tMqtt3:0);
    t2 = (sensorDom==0?0:sensorDom==1?((int)(tempDs18b20*(tempDs18b20<0?-10:10))%10):sensorDom==2?((int)(celsiusSi7021*(celsiusSi7021<0?-10:10))%10):sensorDom==3?((int)(tempBmp*(tempBmp<0?-10:10))%10):sensorDom==4?((int)(tempBme*(tempBme<0?-10:10))%10):sensorDom==5?((int)(tempDht22*(tempDht22<0?-10:10))%10):sensorDom==6?tMqtt4:0);
    t3 = (sensorUl==0?0:sensorUl==1?(int)tempDs18b20:sensorUl==2?(int)celsiusSi7021:sensorUl==3?(int)tempBmp:sensorUl==4?(int)tempBme:sensorUl==5?(int)tempDht22:sensorUl==6?tMqtt3:0);
    t4 = (sensorUl==0?0:sensorUl==1?((int)(tempDs18b20*(tempDs18b20<0?-10:10))%10):sensorUl==2?((int)(celsiusSi7021*(celsiusSi7021<0?-10:10))%10):sensorUl==3?((int)(tempBmp*(tempBmp<0?-10:10))%10):sensorUl==4?((int)(tempBme*(tempBme<0?-10:10))%10):sensorUl==5?((int)(tempDht22*(tempDht22<0?-10:10))%10):sensorUl==6?tMqtt4:0);
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
    h1 = humiDht22 / 10;
    h2 = int(humiDht22) % 10;
    h3 = int(humiDht22 * 10) % 10;
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
  tempDs18b20 = (float)raw / 16.00;
  tempDs18b20 = tempDs18b20 - 1.5;
  if(printCom) {
    printTime();
    Serial.println("Temperature DS18B20: " + String(tempDs18b20) + " *C");
  }
}
//--------------------------------------------------------------------------
void sensorsSi7021() {  //2
  if(si7021 == false) return;
  humSi7021 = sensor.readHumidity();
  celsiusSi7021 = sensor.readTemperature() - 4.7;
  if(printCom) {
    printTime();
    Serial.println("Temperature Si7021: " + String(celsiusSi7021) + " *C,  Humidity: " + String(humSi7021) + " %");
  }
}
//--------------------------------------------------------------------------
void sensorsBmp() {  //3
  if(bmp280 == false) return;
  tempBmp = bmp.readTemperature();
  pressBmp = bmp.readPressure()*0.00750063755419211 + 21;
  pressBmp = (int) pressBmp;
  altBmp = bmp.readAltitude(1013.25);
  if(printCom) {
    printTime();
    Serial.println("Temperature BMP280: " + String(tempBmp) + " *C,  Pressure: " + String(pressBmp) + " mmHg,  Approx altitude: " + String(altBmp) + " m");
  }
}
//--------------------------------------------------------------------------
void sensorsBme() {  //4
  if(bme280 == false) return;
  tempBme = bme.readTempC();          //bme.readTempF()
  humBme = bme.readHumidity();
  pressBme = bme.readPressure()/1.333223689017149;
  pressBme = (int) pressBme;
  altBme = bme.readAltitudeFeet();   //bme.readAltitudeMeter()  bme.readAltitudeFeet()
  if(printCom) {
    printTime();
    Serial.println("Temperature BME280: " + String(tempBme) + " *C,  Humidity: " + String(humBme) + " %,  Pressure: " + String(pressBme) + " mmHg,  Approx altitude: " + String(altBme) + " m");
  }
}
//--------------------------------------------------------------------------
void sensorsDht() {   //5
  if ((err = dht22.read2(pinDHT22, &tempDht22, &humiDht22, NULL)) != SimpleDHTErrSuccess) {
    return;
    Serial.print("Read DHT22 failed, err=");
    Serial.println(err);
  } else if(printCom) {
    humiDht22 = (int) humiDht22;
    printTime();
    Serial.println("Temperature DHT22: " + String(tempDht22) + " *C,  Humidity: " + String(humiDht22) + " %");
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

