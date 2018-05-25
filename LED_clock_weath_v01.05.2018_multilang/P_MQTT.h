//
//  HTML PAGE
//
const char PAGE_MQTTSettings[] PROGMEM =  R"=====(
<html>
    <head>
        <meta http-equiv = "Content-type" content = "text/html; charset=utf-8">
        <title>Led_clock_weath на ESP-12 ver:01.05.2018 (By IvanUA)</title>
        <link rel="shortcut icon" href="#" />
        <link rel = "stylesheet" type = "text/css" href = "/style.css">
        <script type = "text/javascript" src = "/function.js"></script>
        <script type = "text/javascript">
            function set_mqtt_ust(submit) {
                server = "/mqttUst?mqttOn=" + val('mqttOn') + "&mqtt_server=" + val('mqtt_server') + "&mqtt_port=" + (val('mqtt_port')) + "&mqtt_user=" + (val('mqtt_user')) + "&mqtt_pass=" + (val('mqtt_pass'));
                server += "&mqtt_name=" + val('mqtt_name') + "&mqtt_sub=" + val('mqtt_sub') + "&mqtt_sub_inform=" + val('mqtt_sub_inform') + "&mqtt_pub_temp=" + val('mqtt_pub_temp') + "&mqtt_pub_tempUl=" + val('mqtt_pub_tempUl') + "&mqtt_pub_hum=" + val('mqtt_pub_hum') + "&mqtt_pub_press=" + val('mqtt_pub_press') + "&mqtt_pub_alt=" + val('mqtt_pub_alt');
                send_request(submit,server);
            }
             function set_mqtt_on(submit) {
                mqttOn = document.getElementById('mqttOn');
                if (mqttOn.checked){
                  server = "/mqttOn?mqttOn=1";
                  send_request(submit, server);
                }
                if (!mqttOn.checked){
                  server = "/mqttOn?mqttOn=0";
                  send_request(submit, server);
                }
            }
        </script>
    </head>
    <body onload = "load();">
        <header>
            ЧАСИ на ESP-12 ver: 01.05.2018 (by IvanZah)
        </header>       
        <central-unit>
            <titles>Налаштуваня MQTT</titles>
            <div class="informer">
                Виконайте налаштування MQTT серверу.
                Ви можете використать завнішній сервер, наприклад: 
                <a href="https://www.cloudmqtt.com" align="center" target="_blank" title="Перйти за посиланням"> cloudmqtt.com</a>
            </div>            
            <div id="main_unit">
                <hr>
                <label class="switch">Використовувати MQTT сервер
                    <input type="checkbox" id="mqttOn" onclick="set_mqtt_on(this);">
                    <span class="switch-btn"></span>
                </label>
                <hr>
                <paragraph>Підключеня до MQTT серверу:</paragraph>
                <center>
                <table>
                    <tr>
                        <td align = "right">Адрес MQTT серверу</td>
                        <td><input type="text" class="field" id="mqtt_server" value="{{mqtt_server}}" class="form-control" pattern="[- 0-9a-zA-Z._/]{1,20}" placeholder="MQTT сервер"></td>
                    </tr>
                    <tr>
                        <td align = "right">Порт MQTT серверу</span></td>
                        <td><input type="text" class="field" id="mqtt_port" value="{{mqtt_port}}" class="form-control" pattern="[\d]{5}" placeholder="MQTT порт"><br>
                    </tr>
                    <tr>
                        <td align = "right">Логін користувача серверу</span></td>
                        <td><input type="text" class="field" id="mqtt_user" value="{{mqtt_user}}" class="form-control" pattern="[-\w\s#@/]{0,20}" placeholder="MQTT логін"></td>
                    </tr>
                    <tr>
                        <td align = "right">Пароль  користувача  серверу</span></td>
                        <td><input type="text" class="field" id="mqtt_pass" value="{{mqtt_pass}}" class="form-control" pattern="[-\w\s#@/]{0,20}" placeholder="MQTT пароль"></td>
                    </tr>
                </table>
                </center>  
                <paragraph>Налаштування ESP</paragraph>
                <center>
                <table>
                    <tr>
                        <td align = "right">Назва пристрою (ESP)</span></td>
                        <td><input type="text" class="field" id="mqtt_name" value="{{mqtt_name}}" class="form-control" pattern="[-\w\s#@/]{1,24}" placeholder="Назва пристрою"></td>
                    </tr>
                    <tr>
                        <td align = "right">Топік зовнішньої температури</span></td>
                        <td><input type="text" class="field" id="mqtt_sub" value="{{mqtt_sub}}" class="form-control" pattern="[-\w\s#@/]{1,24}" placeholder="Температура на вулиці"></td>
                    </tr>
                    <tr>
                        <td align = "right">Топік інформ повідомлень</span></td>
                        <td><input type="text" class="field" id="mqtt_sub_inform" value="{{mqtt_sub_inform}}" class="form-control" pattern="[-\w\s#@/]{1,24}" placeholder="Топік інформера"></td>
                    </tr>
                    <tr>
                        <td align = "right">Топік публікації температури</span></td>
                        <td><input type="text" class="field" id="mqtt_pub_temp" value="{{mqtt_pub_temp}}" class="form-control" pattern="[-\w\s#@/]{1,24}" placeholder="Публикація температури в будинку"></td>
                    </tr>
                    <tr>
                        <td align = "right">Топік публікації темп. вул.</span></td>
                        <td><input type="text" class="field" id="mqtt_pub_tempUl" value="{{mqtt_pub_tempUl}}" class="form-control" pattern="[-\w\s#@/]{1,24}" placeholder="Публикація температури на вулиці"></td>
                    </tr>
                    <tr>
                        <td align = "right">Топік публікації вологості</span></td>
                        <td><input type="text" class="field" id="mqtt_pub_hum" value="{{mqtt_pub_hum}}" class="form-control" pattern="[-\w\s#@/]{1,24}" placeholder="Публикація вологості"></td>
                    </tr>
                    <tr>
                        <td align = "right">Топік публікації тиску</span></td>
                        <td><input type="text" class="field" id="mqtt_pub_press" value="{{mqtt_pub_press}}" class="form-control" pattern="[-\w\s#@/]{1,24}" placeholder="Публикація тиску"></td>
                    </tr>
                    <tr>
                        <td align = "right">Топік публікації висоти</span></td>
                        <td><input type="text" class="field" id="mqtt_pub_alt" value="{{mqtt_pub_alt}}" class="form-control" pattern="[-\w\s#@/]{1,24}" placeholder="Публикація висоти"></td>
                    </tr>
                </table>
                </center>
                <input type="submit" id="saves" onclick="set_mqtt_ust(this);" value="Зберегти">
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
