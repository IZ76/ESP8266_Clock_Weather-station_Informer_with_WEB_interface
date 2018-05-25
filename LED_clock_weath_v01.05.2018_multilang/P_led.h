//
//  HTML PAGE
//
const char PAGE_LedSettings[] PROGMEM =  R"=====(
<html>
    <head>
        <!--meta name = "viewport" content = "width=device-width, initial-scale=1.0"-->
        <meta http-equiv = "Content-type" content = "text/html; charset=utf-8">
        <title>Led_clock_weath на ESP-12 ver:01.05.2018 (By IvanUA)</title>
        <link rel="shortcut icon" href="#" />
        <link rel = "stylesheet" type = "text/css" href = "/style.css">
        <script type = "text/javascript" src = "/function.js"></script>
        <script type = "text/javascript">
            function set_led(submit) {
                server = "/led?tbd=" + val('tbd') + "&vbd=" + val('vbd') + "&tbn=" + val('tbn') + "&vbn=" + val('vbn') + "&vba=" + val_sw('vba') + "&rotate=" + val('rotate');
                server += "&sensorDom=" + val('sensorDom') + "&sensorUl=" + val('sensorUl') + "&sensorHumi=" + val('sensorHumi') + "&sensorPrAl=" + val('sensorPrAl');
                send_request(submit,server);
            }
        </script>
    </head>
    <body onload = "load();">
        <header>
            ЧАСИ на ESP-12 ver: 01.05.2018 (by IvanZah)
        </header>       
        <central-unit>
            <titles>Налаштуваня екрану</titles>
            <div id="main_unit">
                <center>
                <table>
                  <tr>
                    <td align = "right">Денний режим працює з: </td>
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
                    <td align = "right"> до : </td>
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
                        <option value = "24"> 24 </option>
                    </select></td>
                </tr>
                <tr>
                    <td align = "right">Яскравість в день: </td>
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
                    <td align = "right">в ночі: </td>
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
                </table>
                </center>
                <label class="switch">Автоматичний рівень яскравості
                    <input type="checkbox" id="vba">
                    <span class="switch-btn"></span>
                </label>
                <div class="informer">
                    Рівень яскравості фоторезисторa (0-15): {{lba}}
                </div>
                <center>
                <table>
                  <tr>
                    <td align = "right">Датчик температури в кімнаті </td>
                    <td><select id = "sensorDom">
                        <option value = "NONE"> NONE </option>
                        <option value = "DS18B20"> DS18B20 </option>
                        <option value = "SI7021"> SI7021 </option>
                        <option value = "BMP280"> BMP280 </option>
                        <option value = "DHT22"> DHT22 </option>
                        <option value = "MQTT"> MQTT </option>
                    </select></td>
                  </tr>
                  <tr>
                    <td align = "right">Датчик температури на дворі </td>
                    <td><select id = "sensorUl">
                        <option value = "NONE"> NONE </option>
                        <option value = "DS18B20"> DS18B20 </option>
                        <option value = "SI7021"> SI7021 </option>
                        <option value = "BMP280"> BMP280 </option>
                        <option value = "DHT22"> DHT22 </option>
                        <option value = "MQTT"> MQTT </option>
                    </select></td>
                  </tr>
                  <tr>
                    <td align = "right">Датчик вологості в кімнаті </td>
                    <td><select id = "sensorHumi">
                        <option value = "NONE"> NONE </option>
                        <option value = "SI7021"> SI7021 </option>
                        <option value = "DHT22"> DHT22 </option>
                    </select></td>
                  </tr>
                  <tr>
                    <td align = "right">Датчик тиску та висоти </td>
                    <td><select id = "sensorPrAl">
                        <option value = "NONE"> NONE </option>
                        <option value = "BMP280"> BMP280 </option>
                    </select></td>
                  </tr>
                  <tr><td align = "right">______________________</td></tr>
                  <tr>
                    <td align = "right">Кут повороту екрану</td>
                    <td><select id = "rotate">
                        <option value = "0"> 0 </option>
                        <option value = "90"> 90 </option>
                        <option value = "270"> 270 </option>
                    </select></td>
                  </tr>
                </table>
                </center>
                <input type="submit" id="saves" onclick="set_led(this);" value="Зберегти">
            </div>
            <center>
                <div id="menu_unit">    
                    <a class="link" href="/" title="Тут можна налаштувати параметри точки доступу або параметри підключення до мережі WiFi">Налаштування wifi</a>
                    <a class="link" href="/time.html" title="Тут можна виконати налаштування сервера точного часу і годинної зони" img     scr="img/clock.png">Налаштування часу</a>
                    <a class="link" href="/mqtt.html" title="Тут можна виконати налаштуваня підключення до серверу MQTT">Налаштування mqtt</a>
                    <a class="link" href="/weather.html" title="Тут можна виконати налаштування сервера погоди, міста для прогнозу та інше">Налаштування погоди</a>
                    <a class="link" href="/led.html" title="Тут можна виконати налаштування параметрів екрану, яскравості та іншого.">Налаштування екрану</a>
                    <a class="link" href="/help.html" title="Якщо шось пішло не так...">Поміч</a>
                    <input type="submit" id="reset" onclick = "restart(this,'Ви дійсно бажаєте Перезавантажити пристрій?');" value="Перезавантажити пристрій">
                </div>
            </center>
        </central-unit>
        <footer>
            <a class="link" href="http://forum.amperka.ru/threads/%D0%A7%D0%B0%D1%81%D1%8B-%D0%BD%D0%B0-esp-01-nodemcu-max7219-web-%D0%B8%D0%BD%D1%82%D0%B5%D1%80%D1%84%D0%B5%D0%B9%D1%81.12767/"><span class="left">Амперка</span></a>
            <span class="center">Мова:</span>
            <select id = "mowa" onclick="set_lang(this);">
                <option value = "UA"> UA </option>
                <option value = "RU"> RU </option>
                <option value = "PL"> PL </option>
                <option value = "CZ"> CZ </option>
                <option value = "DE"> DE </option>
            </select>
            <a class="link" href=""><span class="right">YouTube</span></a>
        </footer>
    </body>
</html>
)=====";
