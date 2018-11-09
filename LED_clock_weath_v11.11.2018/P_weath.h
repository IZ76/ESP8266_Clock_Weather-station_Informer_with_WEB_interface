const char P_weath[] PROGMEM =  R"=====(
<html>
    <head>
        <!--meta name = "viewport" content = "width=device-width, initial-scale=1.0"-->
        <meta http-equiv = "Content-type" content = "text/html; charset=utf-8">
        <title>Led_clock_weath на ESP-12 ver:11.11.2018 (By IvanUA)</title>
        <link rel="shortcut icon" href="#" />
        <link rel = "stylesheet" type = "text/css" href = "/style.css">
        <script type = "text/javascript" src = "/function.js"></script>
        <script type = "text/javascript">
            var set_real_time;
            function set_weather(submit) {
                server = "/weather?weatherKey=" + val('weatherKey') + "&weatherHost=" + val('weatherHost') + "&cityID=" + val('cityID');
                server += "&outForecast=" + val_sw('outForecast') + "&timeScrollStart=" + val('timeScrollStart') + "&timeScrollStop=" + val('timeScrollStop') + "&timeScrollSpeed=" + val('timeScrollSpeed');
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
            <span class="opt_cn">CLOCK on ESP-12 ver: 11/11/2018 (by IvanZah)</span><br>
            <span class="opt_cn">Time on ESP:</span>
            <span id="time">{{time}}</span>
        </header>       
        <central-unit>
            <div class="menu_unit">
                <a class="link__img" href="/index.html"><span class="ico__text">Wifi</span></a>
                <a class="link__img" href="/time.html"><span class="ico__text">Time</span></a>
                <a class="link__img" href="/mqtt.html"><span class="ico__text">Mqtt</span></a>
                <a class="link__img" href="/weather.html"><span class="ico__text">Weather</span></a>
                <a class="link__img" href="/led.html"><span class="ico__text">Setup</span></a>
                <a class="link__img" href="/help.html"><span class="ico__text">Help</span></a>
                <a class="link__img" href="#"><span class="ico__text" onclick="restart(this,'ResetESP?');">Restart</span></a>
            </div>
            <titles>
                <span class="opt_cn">Setting the weather</span>
            </titles>
            <div class="informer">
                <span class="opt_cn">To obtain the weather forecast,</span>
                <a href = "https://www.apixu.com/" align = "center" target = "_blank">here we take the API key,</a> 
            </div>
            <div id="main_unit">
                <center>
                    <table>
                        <tr>
                            <td align = "right"><span class="opt_cn">Weather Server</span></td>
                            <td><input type="text" class="field" id="weatherHost" value="{{weatherHost}}" class="form-control" pattern="[0-9a-zA-Z.]{1,32}"></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">API weather key</span></td>
                            <td><input type="text" class="field" id="weatherKey" value="{{weatherKey}}" class="form-control" pattern="[0-9a-zA-Z.]{1,32}"></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">City (name or coord)</span></td>
                            <td><input type="text" class="field" id="cityID" value="{{cityID}}" class="form-control" pattern="[ 0-9a-zA-Z._]{1,32}"></td>
                        </tr>
                    </table>
                </center>
                <center>
                    <label class="switch"><span class="opt_cn">Display of weather forecast</span>
                        <input type="checkbox" id="outForecast">
                        <span class="switch-btn"></span>
                    </label>
                </center>
                <center>
                    <table>
                      <tr>
                        <td align = "right"><span class="opt_cn">Display a running line, with:</span></td>
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
                        <td align = "right"><span class="opt_cn">to:</span></td>
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
                            <option value = "24"> 24 </option>
                        </select></td>
                      </tr>
                    </table>
                </center>
                <center>
                    <table>
                      <tr>
                        <td align = "right"><span class="opt_cn">Treadmill speed</span></td> 
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
                <span class="center"><b>LOCATION</b></span>
                <center>
                    <table>    
                        <tr>
                            <td align = "right"><span class="opt_cn">City name :</span></td>
                            <td><span class="opt_cn">{{location_name}}</span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Region :</span></td>
                            <td><span class="opt_cn">{{location_region}}</span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Country :</span></td>
                            <td><span class="opt_cn">{{location_country}}</span></td>
                        </tr>
                        <tr>
                            <td align = "right"><span class="opt_cn">Time update :</span></td>
                            <td><span class="opt_cn">{{location_localtime}}</span></td>
                        </tr>
                    </table>
                </center>
                <span class="save_booton" onclick="set_weather(this);", "load_weath();">Save</span>
                <br>
                <span class="save_booton" onclick="set_weather_up(this);">Update weather forecast</span>
            </div>
            <div class="menu_unit" id="langs">
                <a><span class="ico__text" onclick="set_lang_f(this, 'EN');">EN</span></a>
                <a><span class="ico__text" onclick="set_lang_f(this, 'UA');">UA</span></a>
                <a><span class="ico__text" onclick="set_lang_f(this, 'RU');">RU</span></a>
                <a><span class="ico__text" onclick="set_lang_f(this, 'PL');">PL</span></a>
                <a><span class="ico__text" onclick="set_lang_f(this, 'CZ');">CZ</span></a>
                <a><span class="ico__text" onclick="set_lang_f(this, 'DE');">DE</span></a>
            </div>
            <div>
                <a href="http://forum.amperka.ru/threads/%D0%A7%D0%B0%D1%81%D1%8B-%D0%BD%D0%B0-esp-01-nodemcu-max7219-web-%D0%B8%D0%BD%D1%82%D0%B5%D1%80%D1%84%D0%B5%D0%B9%D1%81.12767/">Forum</a>
                <a href="https://github.com/IZ76/ESP8266_Clock_Weather-station_Informer_with_WEB_interface" class = "right">GitHub</a>
            </div>
        </central-unit>
    </body>
</html>
)=====";
