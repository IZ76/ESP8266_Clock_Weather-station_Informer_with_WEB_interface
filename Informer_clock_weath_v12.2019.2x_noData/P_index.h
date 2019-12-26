const char P_index[] PROGMEM =  R"=====(
<html>
    <head>
        <!--meta name = "viewport" content = "width=device-width, initial-scale=1.0"-->
        <meta http-equiv = "Content-type" content = "text/html; charset=utf-8">
        <title>Informer_clock_weath ESP8266 ver:12.2019.2x (By IvanUA)</title>
        <link rel="shortcut icon" href="#" />
        <link rel = "stylesheet" type = "text/css" href = "/style.css">
        <script type = "text/javascript" src = "/function.js"></script>
        <script type = "text/javascript">
            function set_ssid(submit) {
                server = "/ssid?ssid=" + val('ssid') + "&password=" + encodeURIComponent(val('password'))+"&ssidAP=" + val('ssidap') + "&passwordAP=" + encodeURIComponent(val('passwordAp'));
                send_request(submit,server);
                alert("Изменения вступят в силу после перезагрузки.");
            }
        </script>
    </head>
    <body onload = "load_wifi();">
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
            <div class="body__center">
                <titles>
                    <span class="opt_cn">Настройки WIFI</span>
                </titles>
                <div class="informer">
                    <span class="opt_cn">Введите натройки интернет соединения для обновления времени, получения данных о погоде, отправки и получения данных с погодных датчиков.</span>
                </div>
                <div id="main_unit">
                    <paragraph>
                        <span class="opt_cn">Подключение к локальной WiFi сети</span>
                    </paragraph>
                    <center>
                        <table>
                            <tr>
                                <td align = "right"><span class="opt_cn">Введите название WiFi сети</span></td>
                                <td><input type="text" class="field form-control" id="ssid" value="{{ssid}}" pattern="[-\w\s#@/]{1,15}" placeholder="name WiFi network"></td>
                            </tr>
                            <tr>  
                                <td align = "right"><span class="opt_cn">Пароль для доступа к этой сети</span></td>
                                <td><input class="field form-control" id="password" value="{{password}}" pattern=".{8,15}" onfocus="this.type='text'" type="password"></td>
                            </tr>
                        </table>
                    </center>
                    <paragraph>
                        <span class="opt_cn">Точка доступа часов (IP_192.168.4.1)</span>
                    </paragraph>
                    <center>
                        <table>
                            <tr>
                                <td align = "right"><span class="opt_cn">Введите имя точки доступа часов</span></td>
                                <td><input type="text" class="field" id="ssidap" value="{{ssidAP}}" class="form-control" pattern="[-\w\s#@/]{1,15}" placeholder="access point name"></td>
                            </tr>
                            <tr>
                                <td align = "right"><span class="opt_cn">Пароль к точке доступа</span></td>  
                                <td><input class="field" id="passwordAp" value="{{passwordAP}}" class="form-control" pattern=".{0,15}" onfocus="this.type='text'" type="password" class="form-control"></td>
                            <tr>
                        </table>
                    </center>
                    <span class="save_booton" onclick="set_ssid(this);">Сохранить настройки</span>
                </div>
            </div>
            <div>
                <a href="http://forum.amperka.ru/threads/%D0%A7%D0%B0%D1%81%D1%8B-%D0%BD%D0%B0-esp-01-nodemcu-max7219-web-%D0%B8%D0%BD%D1%82%D0%B5%D1%80%D1%84%D0%B5%D0%B9%D1%81.12767/">Forum</a>
                <a href="https://github.com/IZ76/ESP8266_Clock_Weather-station_Informer_with_WEB_interface" class = "right">GitHub</a>
            </div>
        </central-unit>
    </body>
</html>
)=====";
