bool loadConfig() {                                                // Завантаження даних збереженних в файлі config.json
  File configFile = SPIFFS.open("/config.json", "r");              // Відкриваемо файл на читання
  if(!configFile) {                                                // якщо файл не знайдено ствоюємого його та записуємо в ньго данні з наших змінних
    if(printCom) Serial.println("Failed to open config file");
    saveConfig();                                                  // Створюємо файл
    configFile.close();
    return false;                                                  // Повернення з помилкою
  }
  size_t size = configFile.size();                                 // Перевіряємо ромір файлу, будемо використовувати файл довжиною в 1024 байта
  if(size > 1024) {
    if(printCom) Serial.println("Config file size is too large");
    configFile.close();
    return false;                                                  // Повернення з помилкою
  }
  jsonConfig = configFile.readString();                            // завантажуємо файл конфігурації в глобальну змінну
  DynamicJsonBuffer jsonBuffer;                                    // Резервуємо память для json обекту буфер може розти по мірі необхідності переважно для ESP8266 
  configFile.close();
  JsonObject& root = jsonBuffer.parseObject(jsonConfig);
  ssidAP = root["ssidAP"].as<String>();
  passwordAP = root["passwordAP"].as<String>();                     // Так отримуємо рядок
  ssid = root["ssid"].as<String>();
  password = root["password"].as<String>();
  ntpServerName = root["ntpServerName"].as<String>();
  timeZone = root["timeZone"];                                     // Так отримуємо число
  isDayLightSaving = root["isDayLightSaving"];
  kuOn = root["kuOn"];
  kuOff = root["kuOff"];
  weatherKey = root["weatherKey"].as<String>();
  weatherHost = root["weatherHost"].as<String>();
  cityID = root["cityID"].as<String>();
  outForecast = root["outForecast"];
  timeScrollStart = root["timeScrollStart"];
  timeScrollStop = root["timeScrollStop"];
  timeScrollSpeed = root["timeScrollSpeed"];
  ds18b20 = root["ds18b20"];
  ds18b20Out = root["ds18b20Out"];
  rotate = root["rotate"];
  updateOTA = root["updateOTA"];
  volBrightnessD = root["volBrightnessD"];
  volBrightnessN = root["volBrightnessN"];
  timeBrightnessD = root["timeBrightnessD"];
  timeBrightnessN = root["timeBrightnessN"];
  volBrightnessAuto = root["volBrightnessAuto"];
  mqttOn = root["mqttOn"];
  snprintf(mqtt_server, 24, "%s", (root["mqtt_server"].as<String>()).c_str());
  mqtt_port = root["mqtt_port"];
  snprintf(mqtt_user, 24, "%s", (root["mqtt_user"].as<String>()).c_str());
  snprintf(mqtt_pass, 24, "%s", (root["mqtt_pass"].as<String>()).c_str());
  snprintf(mqtt_name, 24, "%s", (root["mqtt_name"].as<String>()).c_str());
  snprintf(mqtt_pub_temp, 24, "%s", (root["mqtt_pub_temp"].as<String>()).c_str());
  snprintf(mqtt_pub_tempUl, 24, "%s", (root["mqtt_pub_tempUl"].as<String>()).c_str());
  snprintf(mqtt_pub_hum, 24, "%s", (root["mqtt_pub_hum"].as<String>()).c_str());
  snprintf(mqtt_pub_press, 24, "%s", (root["mqtt_pub_press"].as<String>()).c_str());
  snprintf(mqtt_pub_alt, 24, "%s", (root["mqtt_pub_alt"].as<String>()).c_str());
  snprintf(mqtt_sub, 24, "%s", (root["mqtt_sub"].as<String>()).c_str());
  snprintf(mqtt_sub_inform, 24, "%s", (root["mqtt_sub_inform"].as<String>()).c_str());
  printCom = root["printCom"];
  sensorDom = root["sensorDom"];
  sensorUl = root["sensorUl"];
  sensorHumi = root["sensorHumi"];
  sensorPrAl = root["sensorPrAl"];
  lang = root["lang"];
  if(printCom) {
    printTime();
    Serial.print("Load Config : ");
    Serial.println(jsonConfig);
  }
  return true;
}
//=================================================================
bool saveConfig() {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(jsonConfig);
  json["ssidAP"] = ssidAP;
  json["passwordAP"] = passwordAP;
  json["ssid"] = ssid;
  json["password"] = password;
  json["ntpServerName"] = ntpServerName;
  json["timeZone"] = timeZone;
  json["isDayLightSaving"] = isDayLightSaving;
  json["kuOn"] = kuOn;
  json["kuOff"] = kuOff;
  json["weatherKey"] = weatherKey;
  json["weatherHost"] = weatherHost;
  json["cityID"] = cityID;
  json["outForecast"] = outForecast;
  json["timeScrollStart"] = timeScrollStart;
  json["timeScrollStop"] = timeScrollStop;
  json["timeScrollSpeed"] = timeScrollSpeed;
  json["ds18b20"] = ds18b20;
  json["ds18b20Out"] = ds18b20Out;
  json["rotate"] = rotate;
  json["updateOTA"] = updateOTA;
  json["volBrightnessD"] = volBrightnessD;
  json["volBrightnessN"] = volBrightnessN;
  json["timeBrightnessD"] = timeBrightnessD;
  json["timeBrightnessN"] = timeBrightnessN;
  json["volBrightnessAuto"] = volBrightnessAuto;
  json["mqttOn"] = mqttOn;
  json["mqtt_server"] = mqtt_server;
  json["mqtt_port"] = mqtt_port;
  json["mqtt_user"] = mqtt_user;
  json["mqtt_pass"] = mqtt_pass;
  json["mqtt_name"] = mqtt_name;
  json["mqtt_pub_temp"] = mqtt_pub_temp;
  json["mqtt_pub_tempUl"] = mqtt_pub_tempUl;
  json["mqtt_pub_hum"] = mqtt_pub_hum;
  json["mqtt_pub_press"] = mqtt_pub_press;
  json["mqtt_pub_alt"] = mqtt_pub_alt;
  json["mqtt_sub"] = mqtt_sub;
  json["mqtt_sub_inform"] = mqtt_sub_inform;
  json["printCom"] = printCom;
  json["sensorDom"] = sensorDom;
  json["sensorUl"] = sensorUl;
  json["sensorHumi"] = sensorHumi;
  json["sensorPrAl"] = sensorPrAl;
  json["lang"] = lang;
  jsonConfig = "";
  json.printTo(jsonConfig);
  File configFile = SPIFFS.open("/config.json", "w");                // Відкриваємо файл для запису
  if(!configFile) {
    configFile.close();
    return false;
  }
  json.printTo(configFile);
  if(printCom) {
    printTime();
    Serial.print("Save Config : ");
    Serial.println(jsonConfig);
  }
  configFile.close();
  bip();
  return true;
}
