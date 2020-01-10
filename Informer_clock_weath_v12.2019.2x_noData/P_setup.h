const char P_setup[] PROGMEM =  R"=====(
<html>
    <head>
        <!--meta name = "viewport" content = "width=device-width, initial-scale=1.0"-->
        <meta http-equiv = "Content-type" content = "text/html; charset=utf-8">
        <title>Informer_clock_weath на ESP8266 ver:12.2019.2x (By IvanUA)</title>
        <link rel="shortcut icon" href="#" />
        <link rel = "stylesheet" type = "text/css" href = "/style.css">
        <script type = "text/javascript" src = "/function.js"></script>
        <script type = "text/javascript">
            function set_setup(submit) {
                server = "/setup?tbd=" + val('tbd') + "&vbd=" + val('vbd') + "&tbn=" + val('tbn') + "&vbn=" + val('vbn') + "&vba=" + val_sw('vba') + "&rotate0=" + val('rotate0') + "&rotate1=" + val('rotate1') + "&kuOn=" + val('kuOn') + "&kuOff=" + val('kuOff');
                server += "&sensorDom=" + val('sensorDom') + "&sensorUl=" + val('sensorUl') + "&sensorHome=" + val('sensorHome') + "&sensorHumi=" + val('sensorHumi') + "&sensorPrAl=" + val('sensorPrAl') + "&pressSys=" + val('pressSys') + "&bigCklock_x2=" + val('bigCklock_x2') + "&buzzerSet=" + val_sw('buzzerSet');
                server += "&fontCLOCK=" + val('fontCLOCK') + "&fontSizeCLOCK=" + val('fontSizeCLOCK') + "&fontSizeData=" + val('fontSizeData') + "&dataDown=" + val('dataDown') + "&textDown=" + val('textDown');
                server += "&corrTempD=" + val('corrTempD') + "&corrTempU=" + val('corrTempU') + "&corrTempH=" + val('corrTempH') + "&corrHumi=" + val('corrHumi') + "&corrPress=" + val('corrPress') + "&NUM_MAX0=" + val('NUM_MAX0') + "&NUM_MAX1=" + val('NUM_MAX1') + "&butStat=" + val('butStat');
                send_request(submit,server);
            }
        </script>
    </head>
    <body onload = "load_setup();">
        <header>
            <span class="opt_cn">Часы информер на ESP8266 ver:12.2019.2X (by IvanZah)</span><br>
            <span class="opt_cn">Время на ESP:</span>
            <span id="time">{{time}}</span> 
        </header>       
        <central-unit>
            <div class="menu_unit">
                <a class="link__img" href="/index.html"><span class="ico__text">Wifi</span></a>
                <a class="link__img" href="/time.html"><span class="ico__text">Время</span></a>
                <a class="link__img" href="/mqtt.html"><span class="ico__text">Mqtt</span></a>
                <a class="link__img" href="/weather.html"><span class="ico__text">Погода</span></a>
                <a class="link__img" href="/setup.html"><span class="ico__text">Настройки</span></a>
                <a class="link__img" href="/help.html"><span class="ico__text">Помощь</span></a>
            </div>
            <titles>
                <span class="opt_cn">Настройки Часов</span>
            </titles>
            <div class="informer">
                <span class="opt_cn">Здесь можно настроить параметры экрана, отображение данных на экране, параметры и отображение датчиков.</a>
            </div> 
            <div id="main_unit">
                <center>
                    <paragraph><span class="opt_cn">Настройки экрана</span></paragraph>
                    <table>
                        <tr>
                            <td align = "right"><span class="opt_cn">Дневной режим экрана с:</span></td>
                            <td><select id = "tbd">
                                <option value = "0"> 0 </option>
                                <option value = "1"> 1 </option>
                                <option value = "2"> 2 </option>
                                <option value = "3"> 3 </option>
                                <option value = "4"> 4 </option>
                                <option value = "5"> 5 </option>
                                <option value = "6"> 6 </option>
                                <option value = "7"> 7 </option>
                                <option value = "8"> 8 </option>
                                <option value = "9"> 9 </option>
                                <option value = "10"> 10 </option>
                                <option value = "11"> 11 </option>
                                <option value = "12"> 12 </option>
                                <option value = "13"> 13 </option>
                                <option value = "14"> 14 </option>
                                <option value = "15"> 15 </option>
                                <option value = "16"> 16 </option>
                                <option value = "17"> 17 </option>
                                <option value = "18"> 18 </option>
                                <option value = "19"> 19 </option>
                                <option value = "20"> 20 </option>
                                <option value = "21"> 21 </option>
                                <option value = "22"> 22 </option>
                                <option value = "23"> 23 </option>
                            </select></td>
                            <td align = "right"><span class="opt_cn">до:</span></td>
                            <td><select id = "tbn">
                                <option value = "1"> 1 </option>
                                <option value = "2"> 2 </option>
                                <option value = "3"> 3 </option>
                                <option value = "4"> 4 </option>
                                <option value = "5"> 5 </option>
                                <option value = "6"> 6 </option>
                                <option value = "7"> 7 </option>
                                <option value = "8"> 8 </option>
                                <option value = "9"> 9 </option>
                                <option value = "10"> 10 </option>
                                <option value = "11"> 11 </option>
                                <option value = "12"> 12 </option>
                                <option value = "13"> 13 </option>
                                <option value = "14"> 14 </option>
                                <option value = "15"> 15 </option>
                                <option value = "16"> 16 </option>
                                <option value = "17"> 17 </option>
                                <option value = "18"> 18 </option>
                                <option value = "19"> 19 </option>
                                <option value = "20"> 20 </option>
                                <option value = "21"> 21 </option>
                                <option value = "22"> 22 </option>
                                <option value = "23"> 23 </option>
                                <option value = "24"> полуночи </option>
                            </select></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Уровень яркости днем:</span></td>
                            <td><select id = "vbd">
                                <option value = "0"> 0 </option>
                                <option value = "1"> 1 </option>
                                <option value = "2"> 2 </option>
                                <option value = "3"> 3 </option>
                                <option value = "4"> 4 </option>
                                <option value = "5"> 5 </option>
                                <option value = "6"> 6 </option>
                                <option value = "7"> 7 </option>
                                <option value = "8"> 8 </option>
                                <option value = "9"> 9 </option>
                                <option value = "10"> 10 </option>
                                <option value = "11"> 11 </option>
                                <option value = "12"> 12 </option>
                                <option value = "13"> 13 </option>
                                <option value = "14"> 14 </option>
                                <option value = "15"> 15 </option>
                            </select></td>
                            <td align = "right"><span class="opt_cn">ночью:</span></td>
                            <td><select id = "vbn">
                                <option value = "0"> 0 </option>
                                <option value = "1"> 1 </option>
                                <option value = "2"> 2 </option>
                                <option value = "3"> 3 </option>
                                <option value = "4"> 4 </option>
                                <option value = "5"> 5 </option>
                                <option value = "6"> 6 </option>
                                <option value = "7"> 7 </option>
                                <option value = "8"> 8 </option>
                                <option value = "9"> 9 </option>
                                <option value = "10"> 10 </option>
                                <option value = "11"> 11 </option>
                                <option value = "12"> 12 </option>
                                <option value = "13"> 13 </option>
                                <option value = "14"> 14 </option>
                                <option value = "15"> 15 </option>
                            </select></td>
                        </tr>
                        <tr>
                    </table>
                    <label class="switch"><span class="opt_cn">Автояркость (при наличии модуля с фоторезистором)</span>
                        <input type="checkbox" id="vba">
                        <span class="switch-btn"></span>
                    </label>
                    <br>
                    <table id="table__font" class = "table">
                        <tr>
                            <td></td>
                            <td><span class="opt_cn"><b> 1-я строка </b></span></td>
                            <td><span class="opt_cn"><b> 2-я строка </b></span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Кол-во модулей</span></td>
                            <td><select id = "NUM_MAX0">
                                <option value = "3"> 3 </option>
                                <option value = "4"> 4 </option>
                                <option value = "5"> 5 </option>
                                <option value = "6"> 6 </option>
                                <option value = "7"> 7 </option>
                                <option value = "8"> 8 </option>
                            </select></td>
                            <td><select id = "NUM_MAX1">
                                <option value = "3"> 3 </option>
                                <option value = "4"> 4 </option>
                                <option value = "5"> 5 </option>
                                <option value = "6"> 6 </option>
                                <option value = "7"> 7 </option>
                                <option value = "8"> 8 </option>
                            </select></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Вращение</span></td>
                            <td><select id = "rotate0">
                                <option value = "0"> 0 </option>
                                <option value = "90"> 90 </option>
                                <option value = "270"> 270 </option>
                            </select></td>
                            <td><select id = "rotate1">
                                <option value = "0"> 0 </option>
                                <option value = "90"> 90 </option>
                                <option value = "270"> 270 </option>
                            </select></td>
                        </tr>
                    </table>
                    <table>
                        <tr>
                            <td align = "right"><span class="opt_cn">Шрифт часов</span></td>
                            <td><select id = "fontCLOCK">
                                <option value = "0"> Широкий </option>
                                <option value = "1"> Широкий цифровой </option>
                                <option value = "2"> Жирный </option>
                                <option value = "3"> Жирный цифровой</option>
                                <option value = "4"> Нормальный </option>
                                <option value = "5"> Нормальный цифровой</option>
                                <option value = "6"> Узкий </option>
                                <option value = "7"> Узкий цифровой</option>
                            </select></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Высота часов</span></td>
                            <td><select id = "fontSizeCLOCK">
                                <option value = "0"> 8 линий </option>
                                <option value = "1"> 7 линий </option>
                            </select></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Высота данных</span></td>
                            <td><select id = "fontSizeData">
                                <option value = "0"> 8 линий </option>
                                <option value = "1"> 7 линий </option>
                            </select></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Смещение данных</span></td>
                            <td><select id = "dataDown">
                                <option value = "0"> без смещения </option>
                                <option value = "1"> смещение вниз </option>
                            </select></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Смещение текста</span></td>
                            <td><select id = "textDown">
                                <option value = "0"> без смещения </option>
                                <option value = "1"> смещение вниз </option>
                            </select></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Часы в две строки</span></td>
                            <td><select id = "bigCklock_x2">
                                <option value = "0"> никогда </option>
                                <option value = "1"> только ночью </option>
                                <option value = "2"> всегда </option>
                            </select></td>
                        </tr>
                    </table>
                    <br>
                    <paragraph><span class="opt_cn">Настройки датчиков</span></paragraph>
                    <div class="informer">
                        <span class="opt_cn">Урояень ярскости фоторезистора (0-15): </span>{{lba}}
                    </div>
                    <label class="switch"><span class="opt_cn">Использовать активный базер</span>
                        <input type="checkbox" id="buzzerSet">
                        <span class="switch-btn"></span>
                    </label>
                    <br>
                    <table>
                        <tr>
                            <td align = "right"><span class="opt_cn">Сигнал в начале каждого часа с:</span></td>
                            <td><select id = "kuOn">
                                <option value = "0"> 0 </option>
                                <option value = "1"> 1 </option>
                                <option value = "2"> 2 </option>
                                <option value = "3"> 3 </option>
                                <option value = "4"> 4 </option>
                                <option value = "5"> 5 </option>
                                <option value = "6"> 6 </option>
                                <option value = "7"> 7 </option>    
                                <option value = "8"> 8 </option>
                                <option value = "9"> 9 </option>
                                <option value = "10"> 10 </option>
                                <option value = "11"> 11 </option>
                                <option value = "12"> 12 </option>
                                <option value = "13"> 13 </option>
                                <option value = "14"> 14 </option>
                                <option value = "15"> 15 </option>
                                <option value = "16"> 16 </option>
                                <option value = "17"> 17 </option>
                                <option value = "18"> 18 </option>
                                <option value = "19"> 19 </option>
                                <option value = "20"> 20 </option>
                                <option value = "21"> 21 </option>
                                <option value = "22"> 22 </option>
                                <option value = "23"> 23 </option>
                            </select></td>
                            <td align = "right"><span class="opt_cn">до:</span></td>
                            <td><select id = "kuOff">
                                <option value = "1"> 1 </option>
                                <option value = "2"> 2 </option>
                                <option value = "3"> 3 </option>
                                <option value = "4"> 4 </option>
                                <option value = "5"> 5 </option>
                                <option value = "6"> 6 </option>
                                <option value = "7"> 7 </option>
                                <option value = "8"> 8 </option>
                                <option value = "9"> 9 </option>
                                <option value = "10"> 10 </option>
                                <option value = "11"> 11 </option>
                                <option value = "12"> 12 </option>
                                <option value = "13"> 13 </option>
                                <option value = "14"> 14 </option>
                                <option value = "15"> 15 </option>
                                <option value = "16"> 16 </option>
                                <option value = "17"> 17 </option>
                                <option value = "18"> 18 </option>
                                <option value = "19"> 19 </option>
                                <option value = "20"> 20 </option>
                                <option value = "21"> 21 </option>
                                <option value = "22"> 22 </option>
                                <option value = "23"> 23 </option>
                                <option value = "24"> полуночи </option>
                            </select></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Кнопка подключена к GPIO16 и к:</span></td>
                            <td><select id = "butStat">
                                <option value = "0"> - 5V </option>
                                <option value = "1"> + 5V </option>
                            </select></td>
                        </tr>
                    </table>
                    <div class="informer">
                        <span class="opt_cn">Подтягивающий резистор подключен соответственно к GPIO16 и к противоположному полюсу питания</span>
                    </div>
                    <table id="table__font" class = "table">
                        <tr>
                            <td></td>
                            <td><span class="opt_cn"><b> Датчик </b></span></td>
                            <td><span class="opt_cn"><b> Корр. </b></span></td>
                            <td><span class="opt_cn"><b> Данные </b></span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">tD</span></td>
                            <td><select id = "sensorDom">
                              <option value = "NONE"> НЕТ </option>
                              <option value = "DS18B20"> DS18B20 </option>
                              <option value = "SI7021"> SI7021 </option>
                              <option value = "BMP280"> BMP180/280 </option>
                              <option value = "BME280"> BME280 </option>
                              <option value = "DHT"> DHT11/22 </option>
                              <option value = "MQTT1"> MQTT1 </option>
                              <option value = "MQTT2"> MQTT2 </option>
                              <option value = "MQTT3"> MQTT3 </option>
                            </select></td>
                            <td><input type="text" class="field form-control" id="corrTempD" value="{{corrTempD}}" pattern="\- \d+(\.\d{2})?"></td>
                            <td><span class="opt_cn"> {{Td}} </span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">tU</span></td>
                            <td><select id = "sensorUl">
                              <option value = "NONE"> НЕТ </option>
                              <option value = "DS18B20"> DS18B20 </option>
                              <option value = "SI7021"> SI7021 </option>
                              <option value = "BMP280"> BMP180/280 </option>
                              <option value = "BME280"> BME280 </option>
                              <option value = "DHT"> DHT11/22 </option>
                              <option value = "MQTT1"> MQTT1 </option>
                              <option value = "MQTT2"> MQTT2 </option>
                              <option value = "MQTT3"> MQTT3 </option>
                              <option value = "NMon"> NMon </option>
                            </select></td>
                            <td><input type="text" class="field form-control" id="corrTempU" value="{{corrTempU}}" pattern="\- \d+(\.\d{2})?"></td>
                            <td><span class="opt_cn"> {{Tu}} </span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">tH</span></td>
                            <td><select id = "sensorHome">
                              <option value = "NONE"> НЕТ </option>
                              <option value = "DS18B20"> DS18B20 </option>
                              <option value = "SI7021"> SI7021 </option>
                              <option value = "BMP280"> BMP180/280 </option>
                              <option value = "BME280"> BME280 </option>
                              <option value = "DHT"> DHT11/22 </option>
                              <option value = "MQTT1"> MQTT1 </option>
                              <option value = "MQTT2"> MQTT2 </option>
                              <option value = "MQTT3"> MQTT3 </option>
                              <option value = "NMon"> NMon </option>
                            </select></td>
                            <td><input type="text" class="field form-control" id="corrTempH" value="{{corrTempH}}" pattern="\- \d+(\.\d{2})?"></td>
                            <td><span class="opt_cn"> {{Th}} </span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">hD</span></td>
                            <td><select id = "sensorHumi">
                              <option value = "NONE"> НЕТ </option>
                              <option value = "SI7021"> SI7021 </option>
                              <option value = "BME280"> BME280 </option>
                              <option value = "DHT"> DHT11/22.... </option>
                            </select></td>
                            <td><input type="text" class="field form-control" id="corrHumi" value="{{corrHumi}}" pattern="\- \d+(\.\d{2})?"></td>
                            <td><span class="opt_cn"> {{Hd}} </span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">P</span></td>
                            <td><select id = "sensorPrAl">
                              <option value = "NONE"> НЕТ </option>
                              <option value = "BMP280"> BMP180/280 </option>
                              <option value = "BME280"> BME280 </option>
                            </select></td>
                            <td><input type="text" class="field form-control" id="corrPress" value="{{corrPress}}" pattern="\- [0-9]{0,3}"></td>
                            <td><span class="opt_cn"> {{Pu}} </span></td>
                        </tr>
                        <tr>
                            <td></td>
                            <td><select id = "pressSys">
                              <option value = "0"> hPa </option>
                              <option value = "1"> mmHg </option>
                            </select></td>
                            <td></td>
                            <td></td>
                        </tr>
                    </table>
                    <br>
                    <span class="save_booton" onclick="set_setup(this);">Сохранить настройки</span>
                </center>
            </div>
            <div>
                <a href="http://forum.amperka.ru/threads/%D0%A7%D0%B0%D1%81%D1%8B-%D0%BD%D0%B0-esp-01-nodemcu-max7219-web-%D0%B8%D0%BD%D1%82%D0%B5%D1%80%D1%84%D0%B5%D0%B9%D1%81.12767/">Forum</a>
                <a href="https://github.com/IZ76/ESP8266_Clock_Weather-station_Informer_with_WEB_interface" class = "right">GitHub</a>
            </div>
        </central-unit>
    </body>
</html>
)=====";
