const char P_index[] PROGMEM =  R"=====(
<html>
    <head>
        <!--meta name = "viewport" content = "width=device-width, initial-scale=1.0"-->
        <meta http-equiv = "Content-type" content = "text/html; charset=utf-8">
        <title>Led_clock_weath на ESP-12 ver:23.10.2018 (By IvanUA)</title>
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
            <span class="opt_cn">CLOCK on ESP-12 ver: 23/10/2018 (by IvanZah)</span><br>
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
            <div class="body__center">
                <titles>
                    <span class="opt_cn">WIFI setup</span>
                </titles>
                <div class="informer">
                    <span class="opt_cn">Connecting to the internet network will allow you to synchronize the time and receive a weather forecast.</span>
                </div>
                <div id="main_unit">
                    <paragraph>
                        <span class="opt_cn">Connecting to WiFi router</span>
                    </paragraph>
                    <center>
                        <table>
                            <tr>
                                <td align = "right"><span class="opt_cn">Enter the name of the WiFi network</span></td>
                                <td><input type="text" class="field form-control" id="ssid" value="{{ssid}}" pattern="[-\w\s#@/]{1,15}" placeholder="name WiFi network"></td>
                            </tr>
                            <tr>  
                                <td align = "right"><span class="opt_cn">Enter the WiFi network password</span></td>
                                <td><input class="field form-control" id="password" value="{{password}}" pattern=".{8,15}" onfocus="this.type='text'" type="password"></td>
                            </tr>
                        </table>
                    </center>
                    <paragraph>
                        <span class="opt_cn">Access Point Parameters (IP_192.168.4.1)</span>
                    </paragraph>
                    <center>
                        <table>
                            <tr>
                                <td align = "right"><span class="opt_cn">Enter the name of the access point</span></td>
                                <td><input type="text" class="field" id="ssidap" value="{{ssidAP}}" class="form-control" pattern="[-\w\s#@/]{1,15}" placeholder="access point name"></td>
                            </tr>
                            <tr>
                                <td align = "right"><span class="opt_cn">Enter the access point password</span></td>  
                                <td><input class="field" id="passwordAp" value="{{passwordAP}}" class="form-control" pattern=".{0,15}" onfocus="this.type='text'" type="password" class="form-control"></td>
                            <tr>
                        </table>
                    </center>
                    <span class="save_booton" onclick="set_ssid(this);">Save</span>
                </div>
            </div>
            <div class="menu_unit" id="langs">
                <a><span class="ico__text" onclick="set_lang_f(this, 'EN');">EN</span></a>
                <a><span class="ico__text" onclick="set_lang_f(this, 'UA');">UA</span></a>
                <a><span class="ico__text" onclick="set_lang_f(this, 'RU');">RU</span></a>
                <a><span class="ico__text" onclick="set_lang_f(this, 'PL');">PL</span></a>
                <a><span class="ico__text" onclick="set_lang_f(this, 'CZ');">CZ</span></a>
                <a><span class="ico__text" onclick="set_lang_f(this, 'DE');">DE</span></a>
            </div>
        </central-unit>
    </body>
</html>
)=====";
