//
//  HTML PAGE
//
const char PAGE_WertherSettings[] PROGMEM =  R"=====(
<html>
    <head>
        <!--meta name = "viewport" content = "width=device-width, initial-scale=1.0"-->
        <meta http-equiv = "Content-type" content = "text/html; charset=utf-8">
        <title>Led_clock_weath на ESP-12 ver:01.05.2018 (By IvanUA)</title>
        <link rel="shortcut icon" href="#" />
        <link rel = "stylesheet" type = "text/css" href = "/style.css">
        <script type = "text/javascript" src = "/function.js"></script>
        <script type = "text/javascript">
            var set_real_time;
            function set_weather(submit) {
                server = "/weather?weatherKey=" + val('weatherKey') + "&weatherHost=" + val('weatherHost') + "&cityID=" + val('cityID');
                server += "&outForecast=" + val_sw('outForecast') + "&outKurs=" + val_sw('outKurs') + "&timeScrollStart=" + val('timeScrollStart') + "&timeScrollStop=" + val('timeScrollStop') + "&timeScrollSpeed=" + val('timeScrollSpeed');
                send_request(submit, server);
            }
            function set_weather_up(submit, texts) {
                if (confirm(texts)) {
                    server = "/weatherUpdate?update=ok";
                    send_request(submit, server);
                    return true;
                } else {
                    return false;
                }
            }
            function set_kurs_up(submit,texts) {
                if (confirm(texts)) {
                    server = "/kursUpdate?kursUpdate=ok";
                    send_request(submit, server);
                    return true;
                } else {
                    return false;
                }
            }
        </script>
    </head>
    <body onload = "load();">
        <header>
            ЧАСИ на ESP-12 ver: 01.05.2018 (by IvanZah)
        </header>       
        <central-unit>
            <titles>Налаштуваня погоди</titles>
            <div class="informer">
                Для отримання прогнозу погоди, <a href = "http://openweathermap.org/api" align = "center" target = "_blank"> тут беремо API ключ</a>, 
                <a href = "http://openweathermap.org/help/city_list.txt" align = "center" target = "_blank">а тут знаходимо cityID свого міста</a>.
            </div>
            <div id="main_unit">
                <center>
                <table>
                    <tr>
                        <td align = "right">Сервер погоди</td>
                        <td><input type="text" class="field" id="weatherHost" value="{{weatherHost}}" class="form-control" pattern="[0-9a-zA-Z.]{1,32}" placeholder="Сервер погоди"></td>
                    </tr>
                    <tr>
                        <td align = "right">Ключ погоди API</td>
                        <td><input type="text" class="field" id="weatherKey" value="{{weatherKey}}" class="form-control" pattern="[0-9a-zA-Z.]{1,32}" placeholder="Ключ погоди"></td>
                    </tr>
                    <tr>
                        <td align = "right">ID Міста</span></td>
                        <td><input type="text" class="field" id="cityID" value="{{cityID}}" class="form-control" pattern="[0-9]{1,10}" placeholder="ID Міста"></td>
                    </tr>
                <table>
                <center>
                <label class="switch">Відображення прогнозу погоди
                    <input type="checkbox" id="outForecast">
                    <span class="switch-btn"></span>
                </label>
                <center>
                <table>
                  <tr>
                    <td align = "right">Відображення бігучого рядка з: </td>
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
                    <td align = "right"> до: </td>
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
                    <td align = "right">Швидкість біжучого рядка</td> 
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
                <label class="switch">Відображення курсу валют
                    <input type="checkbox" id="outKurs">
                    <span class="switch-btn"></span>
                </label>
                <input type="submit" id="saves" onclick="set_weather(this);" value="Зберегти">
                <hr>
                <div class="informer">
                    Погода та курс валют оновлюється в 15 та в 45 хвилин кожної години. Якщо ви бажаєте зараз оновити прогноз погоди, то натисніть:
                </div>
                <input type="submit" id="saves" onclick="set_weather_up(this,'Оновити погоду зараз?');" value="ОНОВИТИ ПРОГНОЗ ПОГОДИ">
                <hr>
                <div class="informer">
                    Якщо ви бажаєте зараз оновити курс валют, то натисніть:
                </div>
                <input type="submit" id="saves" onclick="set_kurs_up(this,'Оновити курс зараз?');" value="ОНОВИТИ КУРС PRIVAT 24">
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
