const char P_weath[] PROGMEM =  R"=====(
<html>
    <head>
        <!--meta name = "viewport" content = "width=device-width, initial-scale=1.0"-->
        <meta http-equiv = "Content-type" content = "text/html; charset=utf-8">
        <title>Informer_clock_weath на ESP8266 ver:12.2019.2x (By IvanUA)</title>
        <link rel="shortcut icon" href="#" />
        <link rel = "stylesheet" type = "text/css" href = "/style.css">
        <script type = "text/javascript" src = "/function.js"></script>
        <script type = "text/javascript">
            var set_real_time;
            function set_weather(submit) {
                server = "/weather?weatherKey0=" + val('weatherKey0') + "&weatherKey1=" + val('weatherKey1') +"&weatherHost=" + val('weatherHost') + "&cityID0=" + val('cityID0') + "&cityID1=" + val('cityID1') + "&weatherLang=" + val('weatherLang');
                server += "&displayForecast=" + val_sw('displayForecast') + "&displayCityName=" + val_sw('displayCityName') + "&displayForecastNow=" + val_sw('displayForecastNow') + "&displayForecastTomorrow=" + val_sw('displayForecastTomorrow') + "&timeScrollStart=" + val('timeScrollStart') + "&timeScrollStop=" + val('timeScrollStop') + "&timeScrollSpeed=" + val('timeScrollSpeed');
                server += "&uuid=" + val('uuid') + "&api_key=" + val('api_key') + "&sensors_ID0=" + val('sensors_ID0') + "&sensors_ID1=" + val('sensors_ID1') + "&sensors_ID2=" + val('sensors_ID2') + "&personalCityName=" + val('personalCityName');
                send_request(submit, server);
            }
            function set_weather_up(submit) {
                server = "/weatherUpdate?update=ok";
                send_request(submit, server);
            }
        </script>
    </head>
    <body onload = "load_weath();">
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
                <span class="opt_cn">Настройки погоды</span>
            </titles>
            <div class="informer">
                <span class="opt_cn">Чтобы получить прогноз погоды,</span>
                <a href = "https://www.weatherbit.io/" align = "center" target = "_blank">weatherbit.io </a> 
                <a href = "https://openweathermap.org/" align = "center" target = "_blank">openweathermap.org </a> 
                <span class="opt_cn">здесь мы берем ключи API.</span>
            </div>
            <div id="main_unit">
                    <table class = "table">
                        <tr>
                            <td align = "right"><span class="opt_cn">Погодный сервер</span></td>
                            <td><select id = "weatherHost">
                                <option value = "0"> weatherbit.io </option>
                                <option value = "1"> openweathermap.org </option>
                            </select></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">API weatherbit ключ</span></td>
                            <td><input type="text" class="field" id="weatherKey0" value="{{weatherKey0}}" class="form-control" pattern="[0-9a-zA-Z.]{1,32}"></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Название города</span></td>
                            <td><input type="text" class="field" id="cityID0" value="{{cityID0}}" class="form-control" pattern="[ 0-9a-zA-Zа-яА-Я._]{1,32}"></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">API openweathermap ключ</span></td>
                            <td><input type="text" class="field" id="weatherKey1" value="{{weatherKey1}}" class="form-control" pattern="[0-9a-zA-Z.]{1,32}"></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Название или код города</span></td>
                            <td><input type="text" class="field" id="cityID1" value="{{cityID1}}" class="form-control" pattern="[ 0-9a-zA-Zа-яА-Я._]{1,32}"></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Отображаемое название города</span></td>
                            <td><input type="text" class="field form-control" id="personalCityName" value="{{personalCityName}}" pattern=".{1,25}"></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Язык прогноза</span></td>
                            <td><select id = "weatherLang">
                                <option value = "en"> English </option>
                                <option value = "uk"> Український </option>
                                <option value = "ru"> Русский </option>
                                <option value = "de"> Deutsch </option>
                                <option value = "pl"> Polski </option>
                            </select></td>
                        </tr>
                    </table>
                    <label class="switch"><span class="opt_cn">Отображать погоду на экране</span>
                        <input type="checkbox" id="displayForecast">
                        <span class="switch-btn"></span>
                    </label>
                    <br>
                    <label class="switch"><span class="opt_cn">Отображать название города</span>
                        <input type="checkbox" id="displayCityName">
                        <span class="switch-btn"></span>
                    </label>
                    <br>
                    <label class="switch"><span class="opt_cn">Отображать прогноз на сейчас</span>
                        <input type="checkbox" id="displayForecastNow">
                        <span class="switch-btn"></span>
                    </label>
                    <br>
                    <label class="switch"><span class="opt_cn">Отображать прогноз на завтра</span>
                        <input type="checkbox" id="displayForecastTomorrow">
                        <span class="switch-btn"></span>
                    </label>
                    <br>
                  <center>
                    <table>
                      <tr>
                        <td align = "right"><span class="opt_cn">Показывать погоду с:</span></td>
                        <td><select id = "timeScrollStart">
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
                        <td><select id = "timeScrollStop">
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
                    </table>
                    <table>
                      <tr>
                        <td align = "right"><span class="opt_cn">Скорость бегущей строки</span></td> 
                        <td><select id = "timeScrollSpeed">
                            <option value = "1"> 1 </option>
                            <option value = "5"> 5 </option>
                            <option value = "10"> 10 </option>
                            <option value = "15"> 15 </option>
                            <option value = "20"> 20 </option>
                            <option value = "25"> 25 </option>
                            <option value = "30"> 30 </option>
                            <option value = "35"> 35 </option>
                            <option value = "40"> 40 </option>
                            <option value = "45"> 45 </option>
                            <option value = "50"> 50 </option>
                            <option value = "55"> 55 </option>
                            <option value = "60"> 60 </option>
                            <option value = "65"> 65 </option>
                            <option value = "70"> 70 </option>
                            <option value = "75"> 75 </option>
                            <option value = "80"> 80 </option>
                            <option value = "85"> 85 </option>
                            <option value = "90"> 90 </option>
                            <option value = "95"> 95 </option>
                            <option value = "99"> 99 </option>
                        </select></td>
                      </tr>
                    </table>
                  </center>
                  <br>
                <span class="center"><b>Данные сервера</b></span>
                  <center>
                    <table class = "table">    
                        <tr>
                            <td align = "right"><span class="opt_cn">Название города :</span></td>
                            <td><span class="opt_cn">{{location_name}}</span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Регион :</span></td>
                            <td><span class="opt_cn">{{location_region}}</span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Страна :</span></td>
                            <td><span class="opt_cn">{{location_country}}</span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Время обновления :</span></td>
                            <td><span class="opt_cn">{{location_localtime}}</span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Рассвет :</span></td>
                            <td><span class="opt_cn">{{location_sunrise}}</span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Закат :</span></td>
                            <td><span class="opt_cn">{{location_sunset}}</span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Температура :</span></td>
                            <td><span class="opt_cn">{{location_temp}}</span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Ощущается как :</span></td>
                            <td><span class="opt_cn">{{location_app_temp}}</span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Влажность (%) :</span></td>
                            <td><span class="opt_cn">{{location_rh}}</span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Давление (mb) :</span></td>
                            <td><span class="opt_cn">{{location_pres}}</span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Скорость ветра (m/s) :</span></td>
                            <td><span class="opt_cn">{{location_wind_spd}}</span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Направление ветра :</span></td>
                            <td><span class="opt_cn">{{location_wind_cdir_full}}</span></td>
                        </tr>
                        
                        <tr>
                            <td align = "right"><span class="opt_cn">Облачность (%) :</span></td>
                            <td><span class="opt_cn">{{location_clouds}}</span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Видимость (km) :</span></td>
                            <td><span class="opt_cn">{{location_vis}}</span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Индекс UV (0-11+) :</span></td>
                            <td><span class="opt_cn">{{location_uv}}</span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Описание погоды :</span></td>
                            <td><span class="opt_cn">{{location_weather_description}}</span></td>
                        </tr>
                    </table>
                  </center>
                  <br>
                <span class="center"><b>Установки NarodMon</b></span>
                  <center>
                  <table class = "table">
                    <tr>
                        <td align = "right"><span class="opt_cn">uuid (любое валидное)</span></td>
                        <td><input type="text" class="field" id="uuid" value="{{uuid}}" class="form-control" pattern="[0-9a-zA-Z.]{1,32}"></td>
                    </tr>
                    <tr>
                        <td align = "right"><span class="opt_cn">API ключ</span></td>
                        <td><input type="text" class="field" id="api_key" value="{{api_key}}" class="form-control" pattern="[ 0-9a-zA-Z]{1,32}"></td>
                    </tr>
                    <tr>
                        <td align = "right"><span class="opt_cn">Датчик 1</span></td>
                        <td><input type="text" class="field" id="sensors_ID0" value="{{sensors_ID0}}" class="form-control" pattern="[0-9]{1,6}"></td>
                    </tr>
                    <tr>
                        <td align = "right"><span class="opt_cn">Датчик 2</span></td>
                        <td><input type="text" class="field" id="sensors_ID1" value="{{sensors_ID1}}" class="form-control" pattern="[0-9]{1,6}"></td>
                    </tr>
                    <tr>
                        <td align = "right"><span class="opt_cn">Датчик 3</span></td>
                        <td><input type="text" class="field" id="sensors_ID2" value="{{sensors_ID2}}" class="form-control" pattern="[0-9]{1,6}"></td>
                    </tr>
                  </table>
                  </center>
                <br>
                <span class="save_booton" onclick="set_weather(this);", "load_weath();">Сохранить настройки и обновить погоду</span>
                <br>
                <span class="save_booton" onclick="set_weather_up(this);">Обновить прогноз погоды</span>
            </div>
            <div>
                <a href="http://forum.amperka.ru/threads/%D0%A7%D0%B0%D1%81%D1%8B-%D0%BD%D0%B0-esp-01-nodemcu-max7219-web-%D0%B8%D0%BD%D1%82%D0%B5%D1%80%D1%84%D0%B5%D0%B9%D1%81.12767/">Forum</a>
                <a href="https://github.com/IZ76/ESP8266_Clock_Weather-station_Informer_with_WEB_interface" class = "right">GitHub</a>
            </div>
        </central-unit>
    </body>
</html>
)=====";
