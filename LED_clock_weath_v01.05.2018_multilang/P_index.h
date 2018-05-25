//
//  HTML PAGE
//
const char PAGE_WiFiSettings[] PROGMEM =  R"=====(
<html>
    <head>
        <!--meta name = "viewport" content = "width=device-width, initial-scale=1.0"-->
        <meta http-equiv = "Content-type" content = "text/html; charset=utf-8">
        <title>Led_clock_weath на ESP-12 ver:01.05.2018 (By IvanUA)</title>
        <link rel="shortcut icon" href="#" />
        <link rel = "stylesheet" type = "text/css" href = "/style.css">
        <script type = "text/javascript" src = "/function.js"></script>
        <script type = "text/javascript">
            function set_ssid(submit) {
                server = "/ssid?ssid=" + val('ssid') + "&password=" + encodeURIComponent(val('password'))+"&ssidAP=" + val('ssidap') + "&passwordAP=" + encodeURIComponent(val('passwordAp'));
                send_request(submit,server);
                alert("Зміни вступлять в силу після перезагрузки. Будьласка перезагрузіть пристрій.");
            }
        </script>
    </head>
    <body onload = "load();">
        <header>
            ЧАСИ на ESP-12 ver: 01.05.2018 (by IvanZah)
        </header>       
        <central-unit>
            <titles>Налаштування WiFi</titles>
            <div class="informer">
                Підключення до мережі internet дозволить синхронізувати час та отримувати прогноз погоди.
            </div>
            <div id="main_unit">
                <paragraph>Підключеня до WiFi роутера</paragraph>
                <center>
                <table>
                  <tr>
                    <td align = "right">Введіть ім'я WiFi мережі</td>
                    <td><input type="text" class="field" id="ssid" value="{{ssid}}" class="form-control" pattern="[-\w\s#@/]{1,15}" placeholder="Ім'я WiFi мережі"></td>
                  </tr>
                  <tr>  
                    <td align = "right">Введіть пароль WiFi мережі</td>
                    <td><input class="field" id="password" value="{{password}}" class="form-control" pattern=".{8,15}" onfocus="this.type='text'" type="password" placeholder="Не встановлено"></td>
                  </tr>
                </table>
                </center>
                <paragraph>Параметри точки доступу (IP_192.168.4.1)</paragraph>
                <center>
                <table>
                  <tr>
                    <td align = "right">Введіть ім'я точки доступу</td>
                    <td><input type="text" class="field" id="ssidap" value="{{ssidAP}}" class="form-control" pattern="[-\w\s#@/]{1,15}" placeholder="Ім'я WiFi мережі"></td>
                  </tr>
                  <tr>
                    <td align = "right">Введіть пароль точки доступу</td>  
                    <td><input class="field" id="passwordAp" value="{{passwordAP}}" class="form-control" pattern=".{0,15}" onfocus="this.type='text'" type="password" class="form-control" placeholder="Не встановлено"></td>
                  <tr>
                </table>
                </center>
                <input type="submit" id="saves" onclick="set_ssid(this)" value="Зберегти">
            </div>
            <center>
                <div id="menu_unit">    
                    <a class="link" href="/" title="Тут можна налаштувати параметри точки доступу або параметри підключення до мережі wifi">Налаштування wifi</a>
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
