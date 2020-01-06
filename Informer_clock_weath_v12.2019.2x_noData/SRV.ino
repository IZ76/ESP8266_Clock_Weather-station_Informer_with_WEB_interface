void serverInit(void) {
  server.on("/", [](){server.send_P(200, "text/html", P_index);});
  server.on("/index.html", [](){server.send_P(200, "text/html", P_index);});
  server.on("/time.html", [](){server.send_P(200, "text/html", P_time);}); 
  server.on("/weather.html", [](){server.send_P(200, "text/html", P_weath);});
  server.on("/mqtt.html", [](){server.send_P(200, "text/html", P_mqtt);});
  server.on("/setup.html", [](){server.send_P(200, "text/html", P_setup);});
  server.on("/help.html", [](){server.send_P(200, "text/html", P_help);});
  server.on("/style.css", [](){server.send_P ( 200, "text/css", P_css);});
  server.on("/function.js", [](){server.send_P ( 200, "text/plain", P_js);});
  server.on("/favicon.ico", [](){server.send(200, "text/html", "");});
  server.onNotFound([]() {(404, "text/plain", "FileNotFound");});
  server.on("/configs.json", handle_ConfigJSON);    // формування configs.json сторінки для передачі данних в web інтерфейс
  server.on("/configs_wifi.json", handle_ConfigWifiJson);
  server.on("/configs_time.json", handle_ConfigTimeJson);
  server.on("/configs_mqtt.json", handle_ConfigMqttJson);
  server.on("/configs_weath.json", handle_ConfigWeathJson);
  server.on("/configs_setup.json", handle_ConfigSetupJson);
  server.on("/ssid", handle_Set_Ssid);
  server.on("/ntp", handle_ntp);         // Установка часової зони по запиту типа http://192.168.2.100/timeZone?timeZone=3
  server.on("/timepc", handle_timepc);
  server.on("/weatherUpdate", handle_weather_update);
  server.on("/weather", handle_weather);    // Установка сервера погоди по запиту типа http://192.168.2.100/weatherHost?weatherHost=api.openweathermap.org
  server.on("/mqttUst", handle_mqtt_ust);
  server.on("/mqttOn", handle_mqtt_on);
  server.on("/setup", handle_setup);
  server.on("/restart", handle_Restart);            // перезавантаження можуля по запиту типу http://192.168.1.11/restart?device=ok
  server.on("/resetConfig", handle_resetConfig);
  server.on("/printCom", handle_set_printCom);
  httpUpdater.setup(&server);
  server.begin();
}
//======================================================================================================
void handle_ConfigJSON() {
  String json = "{";
  json += "\"time\":\"";
  json += (String(hour) + ":" + (minute < 10 ? "0" : "") + String(minute) + ":" + (second < 10 ? "0" : "") + String(second));
  json += "\",\"ip\":\"";
  json += WiFi.localIP().toString();
  json += "\",\"printCom\":\"";
  json += (printCom==1?"checked":"");
  json += "\"}";
  server.send(200, "text/json", json);
}
//======================================================================================================
void handle_ConfigWifiJson() {
  String json = "{";
  json += "\"time\":\"";
  json += (String(hour) + ":" + (minute < 10 ? "0" : "") + String(minute) + ":" + (second < 10 ? "0" : "") + String(second));
  json += "\",\"ssid\":\"";
  json += ssid;
  json += "\",\"password\":\"";
  json += password;
  json += "\",\"ssidAP\":\"";
  json += ssidAP;
  json += "\",\"passwordAP\":\"";
  json += passwordAP;
  json += "\"}";
  server.send(200, "text/json", json);
}
//======================================================================================================
void handle_ConfigTimeJson() {
  String json = "{";
  json += "\"time\":\"";
  json += (String(hour) + ":" + (minute < 10 ? "0" : "") + String(minute) + ":" + (second < 10 ? "0" : "") + String(second));
  json += "\",\"ntpServerName\":\"";
  json += ntpServerName;
  json += "\",\"timeZone\":\"";
  json += timeZone;
  json += "\",\"isDayLightSaving\":\"";
  json += (isDayLightSaving==1?"checked":"");
  json += "\",\"rtcStat\":\"";
  json += (rtcStat==1?"checked":"");
  json += "\",\"al_0_0\":\"";
  json += alarme[0][0];
  json += "\",\"al_0_1\":\"";
  json += alarme[0][1];
  json += "\",\"al_0_2\":\"";
  json += alarme[0][2];
  json += "\",\"al_1_0\":\"";
  json += alarme[1][0];
  json += "\",\"al_1_1\":\"";
  json += alarme[1][1];
  json += "\",\"al_1_2\":\"";
  json += alarme[1][2];
  json += "\",\"al_2_0\":\"";
  json += alarme[2][0];
  json += "\",\"al_2_1\":\"";
  json += alarme[2][1];
  json += "\",\"al_2_2\":\"";
  json += alarme[2][2];
  json += "\",\"al_3_0\":\"";
  json += alarme[3][0];
  json += "\",\"al_3_1\":\"";
  json += alarme[3][1];
  json += "\",\"al_3_2\":\"";
  json += alarme[3][2];
  json += "\",\"al_4_0\":\"";
  json += alarme[4][0];
  json += "\",\"al_4_1\":\"";
  json += alarme[4][1];
  json += "\",\"al_4_2\":\"";
  json += alarme[4][2];
  json += "\",\"md_0_0\":\"";
  json += memory_date[0][0];
  json += "\",\"md_0_1\":\"";
  json += memory_date[0][1];
  json += "\",\"md_0_2\":\"";
  json += memory_date_mes0;
  json += "\",\"md_1_0\":\"";
  json += memory_date[1][0];
  json += "\",\"md_1_1\":\"";
  json += memory_date[1][1];
  json += "\",\"md_1_2\":\"";
  json += memory_date_mes1;
  json += "\",\"md_2_0\":\"";
  json += memory_date[2][0];
  json += "\",\"md_2_1\":\"";
  json += memory_date[2][1];
  json += "\",\"md_2_2\":\"";
  json += memory_date_mes2;
  json += "\",\"md_3_0\":\"";
  json += memory_date[3][0];
  json += "\",\"md_3_1\":\"";
  json += memory_date[3][1];
  json += "\",\"md_3_2\":\"";
  json += memory_date_mes3;
  json += "\",\"md_4_0\":\"";
  json += memory_date[4][0];
  json += "\",\"md_4_1\":\"";
  json += memory_date[4][1];
  json += "\",\"md_4_2\":\"";
  json += memory_date_mes4;
  json += "\",\"md_5_0\":\"";
  json += memory_date[5][0];
  json += "\",\"md_5_1\":\"";
  json += memory_date[5][1];
  json += "\",\"md_5_2\":\"";
  json += memory_date_mes5;
  json += "\",\"md_6_0\":\"";
  json += memory_date[6][0];
  json += "\",\"md_6_1\":\"";
  json += memory_date[6][1];
  json += "\",\"md_6_2\":\"";
  json += memory_date_mes6;
  json += "\",\"md_7_0\":\"";
  json += memory_date[7][0];
  json += "\",\"md_7_1\":\"";
  json += memory_date[7][1];
  json += "\",\"md_7_2\":\"";
  json += memory_date_mes7;
  json += "\",\"md_8_0\":\"";
  json += memory_date[8][0];
  json += "\",\"md_8_1\":\"";
  json += memory_date[8][1];
  json += "\",\"md_8_2\":\"";
  json += memory_date_mes8;
  json += "\",\"md_start\":\"";
  json += memory_hour_start;
  json += "\",\"md_stop\":\"";
  json += memory_hour_end;
  json += "\"}";
  server.send(200, "text/json", json);
}
//======================================================================================================
void handle_ConfigMqttJson() {
  String json = "{";
  json += "\"time\":\"";
  json += (String(hour) + ":" + (minute < 10 ? "0" : "") + String(minute) + ":" + (second < 10 ? "0" : "") + String(second));
  json += "\",\"mqttOn\":\"";
  json += (mqttOn==1?"checked":"");
  json += "\",\"mqtt_server\":\"";
  json += mqtt_server;
  json += "\",\"mqtt_port\":\"";
  json += mqtt_port;
  json += "\",\"mqtt_user\":\"";
  json += mqtt_user;
  json += "\",\"mqtt_pass\":\"";
  json += mqtt_pass;
  json += "\",\"mqtt_name\":\"";
  json += mqtt_name;
  json += "\",\"mqtt_sub\":\"";
  json += mqtt_sub;
  json += "\",\"mqtt_sub_inform\":\"";
  json += mqtt_sub_inform;
  json += "\",\"mqtt_pub_temp\":\"";
  json += mqtt_pub_temp;
  json += "\",\"mqtt_pub_tempUl\":\"";
  json += mqtt_pub_tempUl;
  json += "\",\"mqtt_pub_hum\":\"";
  json += mqtt_pub_hum;
  json += "\",\"mqtt_pub_press\":\"";
  json += mqtt_pub_press;
  json += "\",\"mqtt_pub_alt\":\"";
  json += mqtt_pub_alt;
  json += "\"}";
  server.send(200, "text/json", json);
}
//======================================================================================================  
void handle_ConfigWeathJson() {
  int sr = location_sunrise.substring(0, 2).toInt() + (int)hourCorr;
  if(sr>23) sr -= 24;
  if(sr<0) sr += 24;
  String sunrise = String(sr) + location_sunrise.substring(2, 5);
  int ss = location_sunset.substring(0, 2).toInt() + (int)hourCorr;
  if(ss>23) ss -= 24;
  if(ss<0) ss += 24;
  String sunset = String(ss) + location_sunset.substring(2, 5);
  int st = location_localtime.substring(11, 13).toInt() + (int)hourCorr;
  int ly = location_localtime.substring(0, 4).toInt();
  byte lm = location_localtime.substring(5, 7).toInt();
  byte ld = location_localtime.substring(8, 10).toInt(); 
  if(st>23) {
    st -= 24;
    ld++;
    if(ld==32 || (ld==31 && (lm==4 || lm==6 || lm==9 || lm==11)) || (lm==2 && ((ld==29 && ly%4!=0) || (ld==30 && ly%4==0)))) {
      ld=1;
      lm++;
      if(lm>12){
        lm=1;
        ly++;
      }
    }
  }
  if(st<0) {
    st += 24;
    ld--;
    if(ld<1) {
      ld = 0 + ((lm==5 || lm==7 || lm==10 || lm==12 || (lm==3 && ly%4==0))?30:(lm==3 && ly%4!=0)?29:31);
      lm--;
      if(lm<1){
        lm=12;
        ly--;
      }
    }
  }
  String lt = String(ly) + "-" + (lm<10?"0":"") + String(lm) + "-" + (ld<10?"0":"") + String(ld) + " " + (st<10?"0":"") + String(st) + location_localtime.substring(13, 16);
  String json = "{";
  json += "\"time\":\"";
  json += (String(hour) + ":" + (minute < 10 ? "0" : "") + String(minute) + ":" + (second < 10 ? "0" : "") + String(second));
  json += "\",\"weatherKey0\":\"";
  json += weatherKey0;
  json += "\",\"weatherKey1\":\"";
  json += weatherKey1;
  json += "\",\"weatherHost\":\"";
  json += weatherHost;
  json += "\",\"cityID0\":\"";
  json += cityID0;
  json += "\",\"cityID1\":\"";
  json += cityID1;
  json += "\",\"weatherLang\":\"";
  json += weatherLang;
  json += "\",\"displayForecast\":\"";
  json += (displayForecast==1?"checked":"");
  json += "\",\"displayCityName\":\"";
  json += (displayCityName==1?"checked":"");
  json += "\",\"displayForecastNow\":\"";
  json += (displayForecastNow==1?"checked":"");
  json += "\",\"displayForecastTomorrow\":\"";
  json += (displayForecastTomorrow==1?"checked":"");
  json += "\",\"timeScrollStart\":\"";
  json += timeScrollStart;
  json += "\",\"timeScrollStop\":\"";
  json += timeScrollStop;
  json += "\",\"timeScrollSpeed\":\"";
  json += 100 - timeScrollSpeed;
  json += "\",\"location_name\":\"";
  json += location_name;
  json += "\",\"location_region\":\"";
  json += location_region;
  json += "\",\"location_country\":\"";
  json += location_country;
  json += "\",\"location_localtime\":\"";
  json += lt;
  json += "\",\"location_temp\":\"";
  json += location_temp;
  json += "\",\"location_app_temp\":\"";
  json += location_app_temp;
  json += "\",\"location_rh\":\"";
  json += location_rh;
  json += "\",\"location_pres\":\"";
  json += location_pres;
  json += "\",\"location_wind_spd\":\"";
  json += location_wind_spd;
  json += "\",\"location_wind_cdir_full\":\"";
  json += location_wind_cdir_full;
  json += "\",\"location_sunrise\":\"";
  json += sunrise;
  json += "\",\"location_sunset\":\"";
  json += sunset;
  json += "\",\"location_clouds\":\"";
  json += location_clouds;
  json += "\",\"location_vis\":\"";
  json += location_vis;
  json += "\",\"location_uv\":\"";
  json += location_uv;
  json += "\",\"location_weather_description\":\"";
  json += location_weather_description;
  json += "\",\"uuid\":\"";
  json += uuid;
  json += "\",\"api_key\":\"";
  json += api_key;
  json += "\",\"sensors_ID0\":\"";
  json += sensors_ID0;
  json += "\",\"sensors_ID1\":\"";
  json += sensors_ID1;
  json += "\",\"sensors_ID2\":\"";
  json += sensors_ID2;
  json += "\",\"personalCityName\":\"";
  json += personalCityName;
  json += "\"}";
  server.send(200, "text/json", json);
}
//======================================================================================================
void handle_ConfigSetupJson() {
  String json = "{";
  json += "\"time\":\"";
  json += (String(hour) + ":" + (minute < 10 ? "0" : "") + String(minute) + ":" + (second < 10 ? "0" : "") + String(second));
  json += "\",\"kuOn\":\"";
  json += kuOn;
  json += "\",\"kuOff\":\"";
  json += kuOff;
  json += "\",\"tbd\":\"";
  json += timeDay;
  json += "\",\"tbn\":\"";
  json += timeNight;
  json += "\",\"vbd\":\"";
  json += volBrightnessD;
  json += "\",\"vbn\":\"";
  json += volBrightnessN;
  json += "\",\"bigCklock_x2\":\"";
  json += bigCklock_x2;
  json += "\",\"vba\":\"";
  json += (volBrightnessAuto==1?"checked":"");
  json += "\",\"lba\":\"";
  json += levelBridhtness;
  json += "\",\"buzzerSet\":\"";
  json += (buzzerSet==1?"checked":"");
  json += "\",\"sensorDom\":\"";
  json += (sensorDom==0?"NONE":sensorDom==1?"DS18B20":sensorDom==2?"SI7021":sensorDom==3?"BMP280":sensorDom==4?"BME280":sensorDom==5?"DHT":sensorDom==6?"MQTT":"NONE");
  json += "\",\"corrTempD\":\"";
  json += corrTempD;
  json += "\",\"Td\":\"";
  json += t0;
  json += "\",\"sensorUl\":\"";
  json += (sensorUl==0?"NONE":sensorUl==1?"DS18B20":sensorUl==2?"SI7021":sensorUl==3?"BMP280":sensorUl==4?"BME280":sensorUl==5?"DHT":sensorUl==6?"MQTT":sensorUl==7?"NMon":"NONE");
  json += "\",\"corrTempU\":\"";
  json += corrTempU;
  json += "\",\"Tu\":\"";
  json += t3;
  json += "\",\"sensorHome\":\"";
  json += (sensorHome==0?"NONE":sensorHome==1?"DS18B20":sensorHome==2?"SI7021":sensorHome==3?"BMP280":sensorHome==4?"BME280":sensorHome==5?"DHT":sensorHome==6?"MQTT":sensorHome==7?"NMon":"NONE");
  json += "\",\"corrTempH\":\"";
  json += corrTempH;
  json += "\",\"Th\":\"";
  json += t6;
  json += "\",\"sensorHumi\":\"";
  json += (sensorHumi==0?"NONE":sensorHumi==2?"SI7021":sensorHumi==4?"BME280":sensorHumi==5?"DHT":"NONE");
  json += "\",\"corrHumi\":\"";
  json += corrHumi;
  json += "\",\"Hd\":\"";
  json += h0;
  json += "\",\"sensorPrAl\":\"";
  json += (sensorPrAl==0?"NONE":sensorPrAl==3?"BMP280":sensorPrAl==4?"BME280":"NONE");
  json += "\",\"corrPress\":\"";
  json += corrPress;
  json += "\",\"Pu\":\"";
  json += p0;
  json += "\",\"pressSys\":\"";
  json += pressSys;
  json += "\",\"rotate0\":\"";
  json += rotate0;
  json += "\",\"rotate1\":\"";
  json += rotate1;
  json += "\",\"NUM_MAX0\":\"";
  json += NUM_MAX0;
  json += "\",\"NUM_MAX1\":\"";
  json += NUM_MAX1;
  json += "\",\"fontCLOCK\":\"";
  json += fontCLOCK;
  json += "\",\"fontSizeCLOCK\":\"";
  json += fontSizeCLOCK;
  json += "\",\"fontSizeData\":\"";
  json += fontSizeData;
  json += "\",\"dataDown\":\"";
  json += dataDown;
  json += "\",\"textDown\":\"";
  json += textDown;
  json += "\",\"butStat\":\"";
  json += butStat;
  json += "\"}";
  server.send(200, "text/json", json);
}
//======================================================================================================
void handle_Set_Ssid() {
  ssid = server.arg("ssid").c_str();
  password = server.arg("password").c_str();
  ssidAP = server.arg("ssidAP").c_str();
  passwordAP = server.arg("passwordAP").c_str();
  if(printCom) {
    printTime();
    Serial.println("Set SSID: " + ssid + ",  Set password: " + password + ",  Set SSID AP: " + ssidAP + ",  Set AP password: " + passwordAP);
  } 
  saveConfig();
  server.send(200, "text/plain", "OK");
  ESP.reset();
}
//======================================================================================================
void handle_ntp() {
  ntpServerName = server.arg("ntpServerName").c_str();
  timeZone = server.arg("timeZone").toFloat();
  isDayLightSaving = server.arg("isDayLightSaving").toInt();
  rtcStat = server.arg("rtcStat").toInt();
  alarme[0][0]=server.arg("al_0_0").toInt();
  alarme[0][1]=server.arg("al_0_1").toInt();
  alarme[0][2]=server.arg("al_0_2").toInt();
  alarme[1][0]=server.arg("al_1_0").toInt();
  alarme[1][1]=server.arg("al_1_1").toInt();
  alarme[1][2]=server.arg("al_1_2").toInt();
  alarme[2][0]=server.arg("al_2_0").toInt();
  alarme[2][1]=server.arg("al_2_1").toInt();
  alarme[2][2]=server.arg("al_2_2").toInt();
  alarme[3][0]=server.arg("al_3_0").toInt();
  alarme[3][1]=server.arg("al_3_1").toInt();
  alarme[3][2]=server.arg("al_3_2").toInt();
  alarme[4][0]=server.arg("al_4_0").toInt();
  alarme[4][1]=server.arg("al_4_1").toInt();
  alarme[4][2]=server.arg("al_4_2").toInt();
  memory_date[0][0]=server.arg("md_0_0").toInt();
  memory_date[0][1]=server.arg("md_0_1").toInt();
  memory_date[1][0]=server.arg("md_1_0").toInt();
  memory_date[1][1]=server.arg("md_1_1").toInt();
  memory_date[2][0]=server.arg("md_2_0").toInt();
  memory_date[2][1]=server.arg("md_2_1").toInt();
  memory_date[3][0]=server.arg("md_3_0").toInt();
  memory_date[3][1]=server.arg("md_3_1").toInt();
  memory_date[4][0]=server.arg("md_4_0").toInt();
  memory_date[4][1]=server.arg("md_4_1").toInt();
  memory_date[5][0]=server.arg("md_5_0").toInt();
  memory_date[5][1]=server.arg("md_5_1").toInt();
  memory_date[6][0]=server.arg("md_6_0").toInt();
  memory_date[6][1]=server.arg("md_6_1").toInt();
  memory_date[7][0]=server.arg("md_7_0").toInt();
  memory_date[7][1]=server.arg("md_7_1").toInt();
  memory_date[8][0]=server.arg("md_8_0").toInt();
  memory_date[8][1]=server.arg("md_8_1").toInt();
  snprintf(memory_date_mes0, 51, "%s", server.arg("md_0_2").c_str());
  snprintf(memory_date_mes1, 51, "%s", server.arg("md_1_2").c_str());
  snprintf(memory_date_mes2, 51, "%s", server.arg("md_2_2").c_str());
  snprintf(memory_date_mes3, 51, "%s", server.arg("md_3_2").c_str());
  snprintf(memory_date_mes4, 51, "%s", server.arg("md_4_2").c_str());
  snprintf(memory_date_mes5, 51, "%s", server.arg("md_5_2").c_str());
  snprintf(memory_date_mes6, 51, "%s", server.arg("md_6_2").c_str());
  snprintf(memory_date_mes7, 51, "%s", server.arg("md_7_2").c_str());
  snprintf(memory_date_mes8, 51, "%s", server.arg("md_8_2").c_str());
  memory_hour_start = server.arg("md_start").toInt();
  memory_hour_end = server.arg("md_stop").toInt();
  if(printCom) {
    printTime();
    Serial.println("Set NTP Server Name: " + ntpServerName + ",  NTP Time Zone: " + String(timeZone) + ",  isDayLightSaving: " + String(isDayLightSaving));
  }
  alarm_hold=0;
  saveConfig();
  timeUpdateNTP();
  server.send(200, "text/plain", "OK"); 
}
//======================================================================================================
void handle_timepc() {
  hour = server.arg("hours").toInt();
  minute = server.arg("minute").toInt();
  second = server.arg("sec").toInt();
  timeZone = server.arg("tz").toFloat();
  day = server.arg("day").toInt();
  month = server.arg("month").toInt();
  year = server.arg("year").toInt();
  if(printCom) {
    printTime();
    Serial.println("Set Date/Time from PC - "+String(day)+"."+String(month)+"."+String(year)+"     "+String(hour)+":"+String(minute)+":"+String(second)+"    timeZone="+String(timeZone));
  }
  localMillisAtUpdate = millis();
  localEpoc = (hour * 60 * 60 + minute * 60 + second);
  saveConfig();
  server.send(200, "text/plain", "OK"); 
}
//======================================================================================================
void handle_weather_update() {
  if(server.arg("update") == "ok") {
    if(printCom) {
      printTime();
      Serial.println("Update weather!");
    }
    if(displayForecast) {
      if(!weatherHost){
        getWeatherData0();
        getWeatherDataz0();
      } else {
        getWeatherData1();
        getWeatherDataz1();
      }
    }
    if(sensorUl==7)getNarodmon();
    bip();
    server.send(200, "text/plain", "OK");
  }
}
//======================================================================================================
void handle_weather() {
  weatherHost = server.arg("weatherHost").toInt();
  weatherKey0 = server.arg("weatherKey0").c_str();
  weatherKey1 = server.arg("weatherKey1").c_str();
  cityID0 = server.arg("cityID0").c_str();
  cityID1 = server.arg("cityID1").c_str();
  weatherLang = server.arg("weatherLang").c_str();
  displayForecast = server.arg("displayForecast").toInt();
  displayCityName = server.arg("displayCityName").toInt();
  displayForecastNow = server.arg("displayForecastNow").toInt();
  displayForecastTomorrow = server.arg("displayForecastTomorrow").toInt();
  timeScrollStart = server.arg("timeScrollStart").toInt();
  timeScrollStop = server.arg("timeScrollStop").toInt();
  timeScrollSpeed = 100 - server.arg("timeScrollSpeed").toInt();
  uuid = server.arg("uuid").c_str();
  api_key = server.arg("api_key").c_str();
  sensors_ID0 = server.arg("sensors_ID0").toInt();
  sensors_ID1 = server.arg("sensors_ID1").toInt();
  sensors_ID2 = server.arg("sensors_ID2").toInt();
  snprintf(personalCityName, 51, "%s", server.arg("personalCityName").c_str());
  if(printCom) {
    printTime();
    Serial.print("Set Weather Server: ");
    if(!weatherHost) Serial.print(weatherHost0);
    else Serial.print(weatherHost1);
    Serial.println(", Key0: " + weatherKey0 + ", Key1: " + weatherKey1 + ", City ID0: " + cityID0 + ", City ID1: " + cityID1 + ", weatherLang: " + weatherLang);
    Serial.println("displayForecast: " + String(displayForecast) + ", displayCityName: " + String(displayCityName) + ", displayForecastNow: " + String(displayForecastNow) + ", displayForecastTomorrow: " + String(displayForecastTomorrow));
    Serial.println("outtimeScrollStart: " + String(timeScrollStart) + ", timeScrollStop: " + String(timeScrollStop) + ", timeScrollSpeed: " + String(timeScrollSpeed) + ", uuid: " + String(uuid) + ", api_key: " + String(api_key) + ", sensors_ID0: " + String(sensors_ID0) + ", sensors_ID1: " + String(sensors_ID1) + ", sensors_ID2: " + String(sensors_ID2));
  }
  saveConfig();
  lang();
  if(displayForecast && WiFi.status() == WL_CONNECTED){ 
    if(!weatherHost){
      getWeatherData0();
      getWeatherDataz0();
    } else {
      getWeatherData1();
      getWeatherDataz1();
    }
    if(printCom) {
      printTime();
      Serial.println("Update weather!");
    }
  }
  if(sensorUl==7) getNarodmon();
  server.send(200, "text/plain", "OK");
}
//======================================================================================================
void handle_setup(){
  timeDay = server.arg("tbd").toInt();
  volBrightnessD = server.arg("vbd").toInt();
  timeNight = server.arg("tbn").toInt();
  volBrightnessN = server.arg("vbn").toInt();
  volBrightnessAuto = server.arg("vba").toInt();
  bigCklock_x2 = server.arg("bigCklock_x2").toInt();
  buzzerSet = server.arg("buzzerSet").toInt();
  rotate0 = server.arg("rotate0").toInt();
  rotate1 = server.arg("rotate1").toInt();
  NUM_MAX0 = server.arg("NUM_MAX0").toInt();
  NUM_MAX1 = server.arg("NUM_MAX1").toInt();
  kuOn = server.arg("kuOn").toInt();
  kuOff = server.arg("kuOff").toInt();
  String sD = server.arg("sensorDom");
  String sU = server.arg("sensorUl");
  String sHo = server.arg("sensorHome");
  String sH = server.arg("sensorHumi");
  String sP = server.arg("sensorPrAl");
  if(sD=="NONE") sensorDom = 0;
  else if(sD=="DS18B20") sensorDom = 1;
  else if(sD=="SI7021") sensorDom = 2;
  else if(sD=="BMP280") sensorDom = 3;
  else if(sD=="BME280") sensorDom = 4;
  else if(sD=="DHT") sensorDom = 5;
  else if(sD=="MQTT") sensorDom = 6;
  if(sU=="NONE") sensorUl = 0;
  else if(sU=="DS18B20") sensorUl = 1;
  else if(sU=="SI7021") sensorUl = 2;
  else if(sU=="BMP280") sensorUl = 3;
  else if(sU=="BME280") sensorUl = 4;
  else if(sU=="DHT") sensorUl = 5;
  else if(sU=="MQTT") sensorUl = 6;
  else if(sU=="NMon") sensorUl = 7;
  if(sHo=="NONE") sensorHome = 0;
  else if(sHo=="DS18B20") sensorHome = 1;
  else if(sHo=="SI7021") sensorHome = 2;
  else if(sHo=="BMP280") sensorHome = 3;
  else if(sHo=="BME280") sensorHome = 4;
  else if(sHo=="DHT") sensorHome = 5;
  else if(sHo=="MQTT") sensorHome = 6;
  else if(sHo=="NMon") sensorHome = 7;
  if(sH=="NONE") sensorHumi = 0;
  else if(sH=="SI7021") sensorHumi = 2;
  else if(sH=="BME280") sensorHumi = 4;
  else if(sH=="DHT") sensorHumi = 5;
  if(sP=="NONE") sensorPrAl = 0;
  else if(sP=="BMP280") sensorPrAl = 3;
  else if(sP=="BME280") sensorPrAl = 4;
  pressSys = server.arg("pressSys").toInt();
  fontCLOCK = server.arg("fontCLOCK").toInt();
  fontSizeCLOCK = server.arg("fontSizeCLOCK").toInt();
  fontSizeData = server.arg("fontSizeData").toInt();
  dataDown = server.arg("dataDown").toInt();
  textDown = server.arg("textDown").toInt();
  corrTempD = server.arg("corrTempD").toFloat();
  corrTempU = server.arg("corrTempU").toFloat();
  corrTempH = server.arg("corrTempH").toFloat();
  corrHumi = server.arg("corrHumi").toFloat();
  corrPress = server.arg("corrPress").toInt();
  butStat = server.arg("butStat").toInt();
  if(printCom) {
    printTime();
    Serial.println("TBD: "+String(timeDay)+", VBD: "+String(volBrightnessD)+", TBN: "+String(timeNight)+", VBN: "+String(volBrightnessN)+",  kuOn: "+String(kuOn)+",  kuOff: "+String(kuOff)+",  rotate0: "+String(rotate0)+", rotate1: "+String(rotate1)+", bigCklock_x2: "+String(bigCklock_x2)+", buzzerSet: "+String(buzzerSet));
  }
  saveConfig();
  sensors();
  server.send(200, "text/plain", "OK");
}
//======================================================================================================
void handle_mqtt_ust() {
  snprintf(mqtt_server, 24, "%s", server.arg("mqtt_server").c_str());
  mqtt_port = server.arg("mqtt_port").toInt();
  snprintf(mqtt_user, 24, "%s", server.arg("mqtt_user").c_str());
  snprintf(mqtt_pass, 24, "%s", server.arg("mqtt_pass").c_str());
  snprintf(mqtt_name, 24, "%s", server.arg("mqtt_name").c_str());
  snprintf(mqtt_sub, 24, "%s", server.arg("mqtt_sub").c_str());
  snprintf(mqtt_sub_inform, 24, "%s", server.arg("mqtt_sub_inform").c_str());
  snprintf(mqtt_pub_temp, 24, "%s", server.arg("mqtt_pub_temp").c_str());
  snprintf(mqtt_pub_tempUl, 24, "%s", server.arg("mqtt_pub_tempUl").c_str());
  snprintf(mqtt_pub_hum, 24, "%s", server.arg("mqtt_pub_hum").c_str());
  snprintf(mqtt_pub_press, 24, "%s", server.arg("mqtt_pub_press").c_str());
  snprintf(mqtt_pub_alt, 24, "%s", server.arg("mqtt_pub_alt").c_str());
  if(printCom) {
    printTime();
    Serial.println("Set mqtt_server: " + String(mqtt_server) + ",  mqtt_port: " + String(mqtt_port) + ",  mqtt_user: " + String(mqtt_user) + ",  mqtt_pass: " + String(mqtt_pass));
    Serial.println("Set mqtt_name: " + String(mqtt_name) + ",  mqtt_sub: " + String(mqtt_sub) + ",  mqtt_sub_inform: " + String(mqtt_sub_inform) + ",  mqtt_pub_temp: " + String(mqtt_pub_temp) + ",  mqtt_pub_tempUl: " + String(mqtt_pub_tempUl) + ",  mqtt_pub_hum: " + String(mqtt_pub_hum));
  }
  if(mqttOn) reconnect();
  saveConfig(); 
  server.send(200, "text/plain", "OK");
}
//======================================================================================================
void handle_mqtt_on() {
  mqttOn = server.arg("mqttOn").toInt(); 
  if(printCom) {
    printTime();
    Serial.println(server.arg("mqttOn"));
  }
  if(mqttOn) reconnect();
  saveConfig(); 
  server.send(200, "text/plain", "OK");
}
//======================================================================================================
void handle_resetConfig() {
  String restart = server.arg("device");
  if(restart == "ok"){
    //SPIFFS.format();
    SPIFFS.remove("/config.json");
    if(printCom) {
      printTime();
      Serial.println("ESP erase Config file");
    }
    delay(3000);
    server.send(200, "text/plain", "OK");
    delay(3000);
    bip();
    ESP.reset();
  }
}
//======================================================================================================
void handle_set_printCom() {
  printCom = server.arg("printCom").toInt();

  if(printCom) {
    printTime();
    Serial.println("Set printCom: " + String(printCom));
  }
  saveConfig();
  server.send(200, "text/plain", "OK"); 
}
//======================================================================================================
void handle_Restart() {
  String restart = server.arg("device");
  if(restart == "ok"){
    server.send(200, "text/plain", "OK"); 
    ESP.reset();
  }
}
//====================================== Тут функції для роботи з файловою системою
String getContentType(String filename){
  if (server.hasArg("download")) return "application/octet-stream";
  else if (filename.endsWith(".htm")) return "text/html";
  else if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".json")) return "application/json";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".gif")) return "image/gif";
  else if (filename.endsWith(".jpg")) return "image/jpeg";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".xml")) return "text/xml";
  else if (filename.endsWith(".pdf")) return "application/x-pdf";
  else if (filename.endsWith(".zip")) return "application/x-zip";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}
//======================================= Читання файлу
bool handleFileRead(String path){
  if (path.endsWith("/")) path += "index.htm";
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) {
    if (SPIFFS.exists(pathWithGz))
      path += ".gz";
    File file = SPIFFS.open(path, "r");
    size_t sent = server.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}
//======================================== Завантаження файлу
void handleFileUpload(){
  if (server.uri() != "/edit") return;
  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    String filename = upload.filename;
    if (!filename.startsWith("/")) filename = "/" + filename;
    fsUploadFile = SPIFFS.open(filename, "w");
    filename = String();
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    if (fsUploadFile)
      fsUploadFile.write(upload.buf, upload.currentSize);
  } else if (upload.status == UPLOAD_FILE_END) {
    if (fsUploadFile)
      fsUploadFile.close();
  }
}
//======================================== Видалення файлу
void handleFileDelete(){
  if (server.args() == 0) return server.send(500, "text/plain", "BAD ARGS");
  String path = server.arg(0);
  if (path == "/")
    return server.send(500, "text/plain", "BAD PATH");
  if (!SPIFFS.exists(path))
    return server.send(404, "text/plain", "FileNotFound");
  SPIFFS.remove(path);
  server.send(200, "text/plain", "");
  path = String();
}
//========================================= Створення файлу
void handleFileCreate(){
  if (server.args() == 0)
    return server.send(500, "text/plain", "BAD ARGS");
  String path = server.arg(0);
  if (path == "/")
    return server.send(500, "text/plain", "BAD PATH");
  if (SPIFFS.exists(path))
    return server.send(500, "text/plain", "FILE EXISTS");
  File file = SPIFFS.open(path, "w");
  if (file)
    file.close();
  else
    return server.send(500, "text/plain", "CREATE FAILED");
  server.send(200, "text/plain", "");
  path = String();
}
//========================================== Список файлів 
void handleFileList(){
  if (!server.hasArg("dir")){
    server.send(500, "text/plain", "BAD ARGS");
    return;
  }
  String path = server.arg("dir");
  Dir dir = SPIFFS.openDir(path);
  path = String();
  String output = "[";
  while (dir.next()) {
    File entry = dir.openFile("r");
    if (output != "[") output += ',';
    bool isDir = false;
    output += "{\"type\":\"";
    output += (isDir) ? "dir" : "file";
    output += "\",\"name\":\"";
    output += String(entry.name()).substring(1);
    output += "\"}";
    entry.close();
  }
  output += "]";
  server.send(200, "text/json", output);
}
