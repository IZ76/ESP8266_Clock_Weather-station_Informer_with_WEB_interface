bool loadConfig() {                                                // Завантаження даних збереженних в файлі config.json
  File configFile = SPIFFS.open("/config.json", "r");              // Відкриваемо файл на читання
  if(!configFile) {                                                // якщо файл не знайдено ствоюємого його та записуємо в ньго данні з наших змінних
    if(printCom) Serial.println("Failed to open config file");
    saveConfig();                                                  // Створюємо файл
    configFile.close();
    return false;                                                  // Повернення з помилкою
  }
  size_t size = configFile.size();                                 // Перевіряємо ромір файлу, будемо використовувати файл довжиною в 1024 байта
  if(size > 4496) {
    if(printCom) Serial.println("Config file size is too large");
    configFile.close();
    return false;                                                  // Повернення з помилкою
  }
  jsonConfig = configFile.readString();                            // завантажуємо файл конфігурації в глобальну змінну
  DynamicJsonDocument doc(4496);                                   // Резервуємо память для json обекту буфер може розти по мірі необхідності переважно для ESP8266 
  deserializeJson(doc, jsonConfig);
  configFile.close();
  ssidAP = doc["ssidAP"].as<String>();
  passwordAP = doc["passwordAP"].as<String>();                     // Так отримуємо рядок
  ssid = doc["ssid"].as<String>();
  password = doc["password"].as<String>();
  ntpServerName = doc["ntpServerName"].as<String>();
  timeZone = doc["timeZone"];                                      // Так отримуємо число
  isDayLightSaving = doc["isDayLightSaving"];
  kuOn = doc["kuOn"];
  kuOff = doc["kuOff"];
  weatherHost = doc["weatherHost"];
  weatherKey0 = doc["weatherKey0"].as<String>();
  weatherKey1 = doc["weatherKey1"].as<String>();
  cityID0 = doc["cityID0"].as<String>();
  cityID1 = doc["cityID1"].as<String>();
  snprintf(personalCityName, 51, "%s", (doc["personalCityName"].as<String>()).c_str());
  weatherLang = doc["weatherLang"].as<String>();
  displayForecast = doc["displayForecast"];
  displayCityName = doc["displayCityName"];
  displayForecastNow = doc["displayForecastNow"];
  displayForecastTomorrow = doc["displayForecastTomorrow"];
  timeScrollStart = doc["timeScrollStart"];
  timeScrollStop = doc["timeScrollStop"];
  timeScrollSpeed = doc["timeScrollSpeed"];
  rotate0 = doc["rotate0"];
  rotate1 = doc["rotate1"];
  updateOTA = doc["updateOTA"];
  volBrightnessD = doc["volBrightnessD"];
  volBrightnessN = doc["volBrightnessN"];
  timeDay = doc["timeDay"];
  timeNight = doc["timeNight"];
  volBrightnessAuto = doc["volBrightnessAuto"];
  bigCklock_x2 = doc["bigCklock_x2"];
  mqttOn = doc["mqttOn"];
  snprintf(mqtt_server, 24, "%s", (doc["mqtt_server"].as<String>()).c_str());
  mqtt_port = doc["mqtt_port"];
  snprintf(mqtt_user, 24, "%s", (doc["mqtt_user"].as<String>()).c_str());
  snprintf(mqtt_pass, 24, "%s", (doc["mqtt_pass"].as<String>()).c_str());
  snprintf(mqtt_name, 24, "%s", (doc["mqtt_name"].as<String>()).c_str());
  snprintf(mqtt_pub_temp, 24, "%s", (doc["mqtt_pub_temp"].as<String>()).c_str());
  snprintf(mqtt_pub_tempUl, 24, "%s", (doc["mqtt_pub_tempUl"].as<String>()).c_str());
  snprintf(mqtt_pub_hum, 24, "%s", (doc["mqtt_pub_hum"].as<String>()).c_str());
  snprintf(mqtt_pub_press, 24, "%s", (doc["mqtt_pub_press"].as<String>()).c_str());
  snprintf(mqtt_pub_alt, 24, "%s", (doc["mqtt_pub_alt"].as<String>()).c_str());
  snprintf(mqtt_sub1, 24, "%s", (doc["mqtt_sub1"].as<String>()).c_str());
  snprintf(mqtt_sub2, 24, "%s", (doc["mqtt_sub2"].as<String>()).c_str());
  snprintf(mqtt_sub3, 24, "%s", (doc["mqtt_sub3"].as<String>()).c_str());
  snprintf(mqtt_sub_inform, 24, "%s", (doc["mqtt_sub_inform"].as<String>()).c_str());
  printCom = doc["printCom"];
  sensorDom = doc["sensorDom"];
  sensorUl = doc["sensorUl"];
  sensorHome = doc["sensorHome"];
  sensorHumi = doc["sensorHumi"];
  sensorPrAl = doc["sensorPrAl"];
  pressSys = doc["pressSys"];
  alarme[0][0] = doc["al_0_0"];
  alarme[0][1] = doc["al_0_1"];
  alarme[0][2] = doc["al_0_2"];
  alarme[1][0] = doc["al_1_0"];
  alarme[1][1] = doc["al_1_1"];
  alarme[1][2] = doc["al_1_2"];
  alarme[2][0] = doc["al_2_0"];
  alarme[2][1] = doc["al_2_1"];
  alarme[2][2] = doc["al_2_2"];
  alarme[3][0] = doc["al_3_0"];
  alarme[3][1] = doc["al_3_1"];
  alarme[3][2] = doc["al_3_2"];
  alarme[4][0] = doc["al_4_0"];
  alarme[4][1] = doc["al_4_1"];
  alarme[4][2] = doc["al_4_2"];
  memory_date[0][0] = doc["md_0_0"];
  memory_date[0][1] = doc["md_0_1"];
  memory_date[1][0] = doc["md_1_0"];
  memory_date[1][1] = doc["md_1_1"];
  memory_date[2][0] = doc["md_2_0"];
  memory_date[2][1] = doc["md_2_1"];
  memory_date[3][0] = doc["md_3_0"];
  memory_date[3][1] = doc["md_3_1"];
  memory_date[4][0] = doc["md_4_0"];
  memory_date[4][1] = doc["md_4_1"];
  memory_date[5][0] = doc["md_5_0"];
  memory_date[5][1] = doc["md_5_1"];
  memory_date[6][0] = doc["md_6_0"];
  memory_date[6][1] = doc["md_6_1"];
  memory_date[7][0] = doc["md_7_0"];
  memory_date[7][1] = doc["md_7_1"];
  memory_date[8][0] = doc["md_8_0"];
  memory_date[8][1] = doc["md_8_1"];
  snprintf(memory_date_mes0, 51, "%s", (doc["md_0_2"].as<String>()).c_str());
  snprintf(memory_date_mes1, 51, "%s", (doc["md_1_2"].as<String>()).c_str());
  snprintf(memory_date_mes2, 51, "%s", (doc["md_2_2"].as<String>()).c_str());
  snprintf(memory_date_mes3, 51, "%s", (doc["md_3_2"].as<String>()).c_str());
  snprintf(memory_date_mes4, 51, "%s", (doc["md_4_2"].as<String>()).c_str());
  snprintf(memory_date_mes5, 51, "%s", (doc["md_5_2"].as<String>()).c_str());
  snprintf(memory_date_mes6, 51, "%s", (doc["md_6_2"].as<String>()).c_str());
  snprintf(memory_date_mes7, 51, "%s", (doc["md_7_2"].as<String>()).c_str());
  snprintf(memory_date_mes8, 51, "%s", (doc["md_8_2"].as<String>()).c_str());
  memory_hour_start = doc["memory_hour_start"];
  memory_hour_end = doc["memory_hour_end"];
  fontCLOCK = doc["fontCLOCK"];
  fontSizeCLOCK = doc["fontSizeCLOCK"];
  fontSizeData = doc["fontSizeData"];
  textDown = doc["textDown"];
  dataDown = doc["dataDown"];
  corrTempD = doc["corrTempD"];
  corrTempU = doc["corrTempU"];
  corrTempH = doc["corrTempH"];
  corrHumi  = doc["corrHumi"];
  corrPress = doc["corrPress"];
  NUM_MAX0 = doc["NUM_MAX0"];
  NUM_MAX1 = doc["NUM_MAX1"];
  rtcStat = doc["rtcStat"];
  uuid  = doc["uuid"].as<String>();
  api_key = doc["api_key"].as<String>();
  sensors_ID0 = doc["sensors_ID0"];
  sensors_ID1 = doc["sensors_ID1"];
  sensors_ID2 = doc["sensors_ID2"];
  butStat = doc["butStat"];
  if(printCom) {
    printTime();
    Serial.print("Load Config : ");
    Serial.println(jsonConfig);
  }
  return true;
}
//=================================================================
bool saveConfig() {
  DynamicJsonDocument doc(4496);
  deserializeJson(doc, jsonConfig);
  doc["ssidAP"] = ssidAP;
  doc["passwordAP"] = passwordAP;
  doc["ssid"] = ssid;
  doc["password"] = password;
  doc["ntpServerName"] = ntpServerName;
  doc["timeZone"] = timeZone;
  doc["isDayLightSaving"] = isDayLightSaving;
  doc["kuOn"] = kuOn;
  doc["kuOff"] = kuOff;
  doc["weatherHost"] = weatherHost;
  doc["weatherKey0"] = weatherKey0;
  doc["weatherKey1"] = weatherKey1;
  doc["cityID0"] = cityID0;
  doc["cityID1"] = cityID1;
  doc["personalCityName"] = personalCityName;
  doc["weatherLang"] = weatherLang;
  doc["displayForecast"] = displayForecast;
  doc["displayCityName"] = displayCityName;
  doc["displayForecastNow"] = displayForecastNow;
  doc["displayForecastTomorrow"] = displayForecastTomorrow;
  doc["timeScrollStart"] = timeScrollStart;
  doc["timeScrollStop"] = timeScrollStop;
  doc["timeScrollSpeed"] = timeScrollSpeed;
  doc["rotate0"] = rotate0;
  doc["rotate1"] = rotate1;
  doc["updateOTA"] = updateOTA;
  doc["volBrightnessD"] = volBrightnessD;
  doc["volBrightnessN"] = volBrightnessN;
  doc["timeDay"] = timeDay;
  doc["timeNight"] = timeNight;
  doc["volBrightnessAuto"] = volBrightnessAuto;
  doc["bigCklock_x2"] = bigCklock_x2;
  doc["buzzerSet"] = buzzerSet;
  doc["mqttOn"] = mqttOn;
  doc["mqtt_server"] = mqtt_server;
  doc["mqtt_port"] = mqtt_port;
  doc["mqtt_user"] = mqtt_user;
  doc["mqtt_pass"] = mqtt_pass;
  doc["mqtt_name"] = mqtt_name;
  doc["mqtt_pub_temp"] = mqtt_pub_temp;
  doc["mqtt_pub_tempUl"] = mqtt_pub_tempUl;
  doc["mqtt_pub_hum"] = mqtt_pub_hum;
  doc["mqtt_pub_press"] = mqtt_pub_press;
  doc["mqtt_pub_alt"] = mqtt_pub_alt;
  doc["mqtt_sub1"] = mqtt_sub1;
  doc["mqtt_sub2"] = mqtt_sub2;
  doc["mqtt_sub3"] = mqtt_sub3;
  doc["mqtt_sub_inform"] = mqtt_sub_inform;
  doc["printCom"] = printCom;
  doc["sensorDom"] = sensorDom;
  doc["sensorUl"] = sensorUl;
  doc["sensorHome"] = sensorHome;
  doc["sensorHumi"] = sensorHumi;
  doc["sensorPrAl"] = sensorPrAl;
  doc["pressSys"] = pressSys;
  doc["al_0_0"] = alarme[0][0];
  doc["al_0_1"] = alarme[0][1];
  doc["al_0_2"] = alarme[0][2];
  doc["al_1_0"] = alarme[1][0];
  doc["al_1_1"] = alarme[1][1];
  doc["al_1_2"] = alarme[1][2];
  doc["al_2_0"] = alarme[2][0];
  doc["al_2_1"] = alarme[2][1];
  doc["al_2_2"] = alarme[2][2];
  doc["al_3_0"] = alarme[3][0];
  doc["al_3_1"] = alarme[3][1];
  doc["al_3_2"] = alarme[3][2];
  doc["al_4_0"] = alarme[4][0];
  doc["al_4_1"] = alarme[4][1];
  doc["al_4_2"] = alarme[4][2];
  doc["md_0_0"] = memory_date[0][0];
  doc["md_0_1"] = memory_date[0][1];
  doc["md_1_0"] = memory_date[1][0];
  doc["md_1_1"] = memory_date[1][1];
  doc["md_2_0"] = memory_date[2][0];
  doc["md_2_1"] = memory_date[2][1];
  doc["md_3_0"] = memory_date[3][0];
  doc["md_3_1"] = memory_date[3][1];
  doc["md_4_0"] = memory_date[4][0];
  doc["md_4_1"] = memory_date[4][1];
  doc["md_5_0"] = memory_date[5][0];
  doc["md_5_1"] = memory_date[5][1];
  doc["md_6_0"] = memory_date[6][0];
  doc["md_6_1"] = memory_date[6][1];
  doc["md_7_0"] = memory_date[7][0];
  doc["md_7_1"] = memory_date[7][1];
  doc["md_8_0"] = memory_date[8][0];
  doc["md_8_1"] = memory_date[8][1];
  doc["md_0_2"] = memory_date_mes0;
  doc["md_1_2"] = memory_date_mes1;
  doc["md_2_2"] = memory_date_mes2;
  doc["md_3_2"] = memory_date_mes3;
  doc["md_4_2"] = memory_date_mes4;
  doc["md_5_2"] = memory_date_mes5;
  doc["md_6_2"] = memory_date_mes6;
  doc["md_7_2"] = memory_date_mes7;
  doc["md_8_2"] = memory_date_mes8;
  doc["memory_hour_start"] = memory_hour_start;
  doc["memory_hour_end"] = memory_hour_end;
  doc["fontCLOCK"] = fontCLOCK;
  doc["fontSizeCLOCK"] = fontSizeCLOCK;
  doc["fontSizeData"] = fontSizeData;
  doc["textDown"] = textDown;
  doc["dataDown"] = dataDown;
  doc["corrTempD"] = corrTempD;
  doc["corrTempU"] = corrTempU;
  doc["corrTempH"] = corrTempH;
  doc["corrHumi"] = corrHumi;
  doc["corrPress"] = corrPress;
  doc["NUM_MAX0"] = NUM_MAX0;
  doc["NUM_MAX1"] = NUM_MAX1;
  doc["rtcStat"] = rtcStat;
  doc["uuid"] = uuid;
  doc["api_key"] = api_key;
  doc["sensors_ID0"] = sensors_ID0;
  doc["sensors_ID1"] = sensors_ID1;
  doc["sensors_ID2"] = sensors_ID2;
  doc["butStat"] = butStat;
  jsonConfig = "";
  if(serializeJson(doc, jsonConfig)==0){
    Serial.println(F("Failed to write to jsonConfig"));
  }  
  File configFile = SPIFFS.open("/config.json", "w");                // Відкриваємо файл для запису
  if(!configFile) {
    configFile.close();
    return false;
  }
  if(serializeJson(doc, configFile)==0){
    Serial.println(F("Failed to write to file"));
  } 
  if(printCom) {
    printTime();
    Serial.print("Save Config : ");
    Serial.println(jsonConfig);
  }
  configFile.close();
  bip();
  return true;
}
//======================================================
bool loadTime() {
  File timeFile = SPIFFS.open("/time.json", "r");
  if(!timeFile) {
    if(printCom) Serial.println("Failed to open time file");
    saveTime();
    timeFile.close();
    return false;
  }
  size_t size = timeFile.size();
  if(size > 512) {
    if(printCom) Serial.println("Time file size is too large");
    timeFile.close();
    return false;
  }
  jsonTime = timeFile.readString();
  DynamicJsonDocument doc(512);
  deserializeJson(doc, jsonTime);
  timeFile.close();
  hour = doc["hour"];
  minute = doc["minute"];
  second = doc["second"]; 
  year = doc["year"];
  month = doc["month"];
  day = doc["day"]; 
  if(printCom) {
    printTime();
    Serial.print("Load Time : ");
    Serial.println(jsonTime);
  }
  return true;
}
//=================================================================
bool saveTime() {
  DynamicJsonDocument doc(512);
  deserializeJson(doc, jsonTime);
  doc["hour"] = hour;
  doc["minute"] = minute;
  doc["second"] = second;
  doc["year"] = year;
  doc["month"] = month;
  doc["day"] = day; 
  jsonTime = "";
  if(serializeJson(doc, jsonTime)==0){
    Serial.println(F("Failed to write to jsonTime"));
  }  
  File timeFile = SPIFFS.open("/time.json", "w");
  if(!timeFile) {
    timeFile.close();
    return false;
  }
  if(serializeJson(doc, timeFile)==0){
    Serial.println(F("Failed to write to timeFile "));
  } 
  if(printCom) {
    printTime();
    Serial.print("Save Time: ");
    Serial.println(jsonTime);
  }
  timeFile.close();
  return true;
}
