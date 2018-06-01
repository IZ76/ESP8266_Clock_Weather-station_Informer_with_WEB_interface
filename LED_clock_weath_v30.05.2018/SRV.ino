void server_init(void) {
  server.on("/configs.json", handle_ConfigJSON);    // формування configs.json сторінки для передачі данних в web інтерфейс
  server.on("/ssid", handle_Set_Ssid);
  server.on("/ntp", handle_ntp);         // Установка часової зони по запиту типа http://192.168.2.100/timeZone?timeZone=3
  server.on("/weatherUpdate", handle_weather_update);
  server.on("/weather", handle_weather);    // Установка сервера погоди по запиту типа http://192.168.2.100/weatherHost?weatherHost=api.openweathermap.org
  server.on("/mqttUst", handle_mqtt_ust);
  server.on("/mqttOn", handle_mqtt_on);
  server.on("/led", handle_led);
  server.on("/restart", handle_Restart);            // перезавантаження можуля по запиту типу http://192.168.1.11/restart?device=ok
  server.on("/resetConfig", handle_resetConfig);
  server.on("/printCom", handle_set_printCom);
  server.on("/lang", handle_set_lang);
  httpUpdater.setup(&server);
  server.begin();
}
//======================================================================================================
void handle_ConfigJSON() {
  String json = "{"; 
  json += "\"ssid\":\"";
  json += ssid;
  json += "\",\"password\":\"";
  json += password;
  json += "\",\"ssidAP\":\"";
  json += ssidAP;
  json += "\",\"passwordAP\":\"";
  json += passwordAP;
  json += "\",\"ip\":\"";
  json += WiFi.localIP().toString();
  json += "\",\"ntpServerName\":\"";
  json += ntpServerName;
  json += "\",\"timeZone\":\"";
  json += timeZone;
  json += "\",\"isDayLightSaving\":\"";
  json += (isDayLightSaving==1?"checked":"");
  json += "\",\"kuOn\":\"";
  json += kuOn;
  json += "\",\"kuOff\":\"";
  json += kuOff;
  json += "\",\"weatherKey\":\"";
  json += weatherKey;  
  json += "\",\"weatherHost\":\"";
  json += weatherHost;
  json += "\",\"cityID\":\"";
  json += cityID;
  json += "\",\"time\":\"";
  json += (String(hour) + ":" + (minute < 10 ? "0" : "") + String(minute) + ":" + (second < 10 ? "0" : "") + String(second));
  json += "\",\"tbd\":\"";
  json += timeBrightnessD;
  json += "\",\"vbd\":\"";
  json += volBrightnessD;
  json += "\",\"tbn\":\"";
  json += timeBrightnessN;
  json += "\",\"vbn\":\"";
  json += volBrightnessN;
  json += "\",\"vba\":\"";
  json += (volBrightnessAuto==1?"checked":"");
  json += "\",\"lba\":\"";
  json += levelBridhtness;
  json += "\",\"outForecast\":\"";
  json += (outForecast==1?"checked":"");
  json += "\",\"timeScrollStart\":\"";
  json += timeScrollStart;
  json += "\",\"timeScrollStop\":\"";
  json += timeScrollStop;
  json += "\",\"timeScrollSpeed\":\"";
  json += 100 - timeScrollSpeed;
  json += "\",\"ds18b20\":\"";
  json += (ds18b20==1?"checked":"");
  json += "\",\"ds18b20Out\":\"";
  json += (ds18b20Out==1?"checked":"");
  json += "\",\"rotate\":\"";
  json += rotate;
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
  json += "\",\"printCom\":\"";
  json += (printCom==1?"checked":"");
  json += "\",\"sensorDom\":\"";
  json += (sensorDom==0?"NONE":sensorDom==1?"DS18B20":sensorDom==2?"SI7021":sensorDom==3?"BMP280":sensorDom==4?"DHT22":sensorDom==5?"MQTT":"NONE");
  json += "\",\"sensorUl\":\"";
  json += (sensorUl==0?"NONE":sensorUl==1?"DS18B20":sensorUl==2?"SI7021":sensorUl==3?"BMP280":sensorUl==4?"DHT22":sensorUl==5?"MQTT":"NONE");
  json += "\",\"sensorHumi\":\"";
  json += (sensorHumi==0?"NONE":sensorHumi==2?"SI7021":sensorHumi==4?"DHT22":"NONE");
  json += "\",\"sensorPrAl\":\"";
  json += (sensorPrAl==0?"NONE":sensorPrAl==3?"BMP280":"NONE");
  json += "\",\"mowa\":\"";
  json += (lang==0?"UA":lang==1?"RU":lang==2?"PL":lang==3?"CZ":lang==4?"DE":"EN");
  json += "\",\"lang\":\"";
  json += (lang==0?"UA":lang==1?"RU":lang==2?"PL":lang==3?"CZ":lang==4?"DE":"EN");
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
  kuOn = server.arg("kuOn").toInt();
  kuOff = server.arg("kuOff").toInt();
  if(printCom) {
    printTime();
    Serial.println("Set NTP Server Name: " + ntpServerName + ",  NTP Time Zone: " + String(timeZone) + ",  kuOn: "+ String(kuOn) + ",  kuOff: " + String(kuOff) + ",  isDayLightSaving: " + String(isDayLightSaving));
  }
  saveConfig();
  timeUpdateNTP();
  server.send(200, "text/plain", "OK"); 
}
//======================================================================================================
void handle_weather_update() {
  if(server.arg("update") == "ok") {
    if(printCom) {
      printTime();
      Serial.println("Update weather!");
    }
    if(outForecast) getWeatherData();
    if(outForecast) getWeatherDataz();
    bip();
    server.send(200, "text/plain", "OK");
  }
}
//======================================================================================================
void handle_weather() {
  weatherHost = server.arg("weatherHost").c_str();
  weatherKey = server.arg("weatherKey").c_str();
  cityID = server.arg("cityID").c_str();
  outForecast = server.arg("outForecast").toInt();
  timeScrollStart = server.arg("timeScrollStart").toInt();
  timeScrollStop = server.arg("timeScrollStop").toInt();
  timeScrollSpeed = 100 - server.arg("timeScrollSpeed").toInt();
  if(printCom) {
    printTime();
    Serial.println("Set Weather Server: " + weatherHost + ",   Key: " + weatherKey + ",   City ID: " + cityID);
    Serial.println("outForecast: " + String(outForecast) + ", outtimeScrollStart: " + String(timeScrollStart) + ", timeScrollStop: " + String(timeScrollStop) + ", timeScrollSpeed: " + String(timeScrollSpeed));
  }
  saveConfig();
  if(outForecast) getWeatherData();
  if(outForecast) getWeatherDataz();
  server.send(200, "text/plain", "OK");
}
//======================================================================================================
void handle_led(){
  timeBrightnessD = server.arg("tbd").toInt();
  volBrightnessD = server.arg("vbd").toInt();
  timeBrightnessN = server.arg("tbn").toInt();
  volBrightnessN = server.arg("vbn").toInt();
  volBrightnessAuto = server.arg("vba").toInt();
  ds18b20 = server.arg("ds18b20").toInt();
  ds18b20Out = server.arg("ds18b20Out").toInt();
  rotate = server.arg("rotate").toInt();
  String sD = server.arg("sensorDom");
  String sU = server.arg("sensorUl");
  String sH = server.arg("sensorHumi");
  String sP = server.arg("sensorPrAl");
  if(sD=="NONE") sensorDom = 0;
  else if(sD=="DS18B20") sensorDom = 1;
  else if(sD=="SI7021") sensorDom = 2;
  else if(sD=="BMP280") sensorDom = 3;
  else if(sD=="DHT22") sensorDom = 4;
  else if(sD=="MQTT") sensorDom = 5;
  if(sU=="NONE") sensorUl = 0;
  else if(sU=="DS18B20") sensorUl = 1;
  else if(sU=="SI7021") sensorUl = 2;
  else if(sU=="BMP280") sensorUl = 3;
  else if(sU=="DHT22") sensorUl = 4;
  else if(sU=="MQTT") sensorUl = 5;
  if(sH=="NONE") sensorHumi = 0;
  else if(sH=="SI7021") sensorHumi = 2;
  else if(sH=="DHT22") sensorHumi = 4;
  if(sP=="NONE") sensorPrAl = 0;
  else if(sP=="BMP280") sensorPrAl = 3;
  if(printCom) {
    printTime();
    Serial.println("TBD: " + String(timeBrightnessD) + ", VBD: " + String(volBrightnessD) + ", TBN: " + String(timeBrightnessN) + ", VBN: " + String(volBrightnessN) + ",  ds18b20: " + String(ds18b20) + ", ds18b20Out: " + String(ds18b20Out) + ", rotate: " + String(rotate));
  }
  saveConfig(); 
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
    Serial.println("Set mqtt_server: "+String(mqtt_server)+",  mqtt_port: "+String(mqtt_port)+",  mqtt_user: "+String(mqtt_user)+",  mqtt_pass: "+String(mqtt_pass));
    Serial.println("Set mqtt_name: "+String(mqtt_name)+",  mqtt_sub: "+String(mqtt_sub)+",  mqtt_sub_inform: "+String(mqtt_sub_inform)+",  mqtt_pub_temp: "+String(mqtt_pub_temp)+",  mqtt_pub_tempUl: "+String(mqtt_pub_tempUl)+",  mqtt_pub_hum: "+String(mqtt_pub_hum)+",  mqtt_pub_press: "+String(mqtt_pub_press)+",  mqtt_pub_alt: "+String(mqtt_pub_alt));
  }
  reconnect();
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
  reconnect();
  saveConfig(); 
  server.send(200, "text/plain", "OK");
}
//======================================================================================================
void handle_resetConfig() {
  String restart = server.arg("device");
  if(restart == "ok"){
    SPIFFS.format();
    if(printCom) {
      printTime();
      Serial.println(ESP.eraseConfig());
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
void handle_set_lang() {
  if(server.arg("mowa") == "UA" && lang !=0) {
    lang = 0;
    ukrText();
  }
  else if(server.arg("mowa") == "RU" && lang !=1) {
    lang = 1;
    rusText();
  }
  else if(server.arg("mowa") == "PL" && lang !=2) {
    lang = 2;
    polText();
  }
  else if(server.arg("mowa") == "CZ" && lang !=3) {
    lang = 3;
    czText();
  }
  else if(server.arg("mowa") == "DE" && lang !=4) {
    lang = 4;
    deText();
  }
  else if(server.arg("mowa") == "EN" && lang !=5) {
    lang = 5;
    deText();
  }
  else {
    return;
  }
  if(printCom) {
    printTime();
    Serial.print("Set lang: ");
    Serial.println(server.arg("mowa").c_str());
  }
  saveConfig();
  server.send(200, "text/plain", "OK"); 
}
//======================================================================================================
void handle_Restart() {
  String restart = server.arg("device");
  if(restart == "ok"){
    server.send(200, "text/plain", "OK"); 
    ESP.restart();
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
