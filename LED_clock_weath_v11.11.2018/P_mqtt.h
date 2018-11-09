const char P_mqtt[] PROGMEM =  R"=====(
<html>
    <head>
        <meta http-equiv = "Content-type" content = "text/html; charset=utf-8">
        <title>Led_clock_weath на ESP-12 ver:11.11.2018 (By IvanUA)</title>
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
                server = "/mqttOn?mqttOn=" + val_sw("mqttOn");
                send_request(submit, server);
            }
        </script>
    </head>
    <body onload = "load();">
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
                <span class="opt_cn">Configure MQTT</span>
            </titles>
            <div class="informer">
                <span class="opt_cn">Configure the MQTT server. You can use an external server, for example:</span>
                <a href="https://www.cloudmqtt.com" align="center" target="_blank"> cloudmqtt.com</a>
            </div>            
            <div id="main_unit">
                <hr>
                <label class="switch">
                    <span class="opt_cn">Use MQTT server</span>
                    <input type="checkbox" class="checkbox" id="mqttOn" name="switch-btn" onclick="set_mqtt_on(this);">
                    <span class="switch-btn"></span>
                </label>
                <hr>
                <paragraph><span class="opt_cn">Connection to MQTT server:</span></paragraph>
                <center>
                <table>
                    <tr>
                        <td align = "right"><span class="opt_cn">MQTT server address</span></td>
                        <td><input type="text" class="field form-control" id="mqtt_server" value="{{mqtt_server}}" pattern="[- 0-9a-zA-Z._/]{1,20}"></td>
                    </tr>
                    <tr>
                        <td align = "right"><span class="opt_cn">MQTT Server Port</span></td>
                        <td><input type="text" class="field form-control" id="mqtt_port" value="{{mqtt_port}}" pattern="[\d]{5}"><br>
                    </tr>
                    <tr>
                        <td align = "right"><span class="opt_cn">Server user login</span></td>
                        <td><input class="field form-control" id="mqtt_user" value="{{mqtt_user}}" pattern="[-\w\s#@/]{0,20}" onfocus="this.type='text'" type="password"></td>
                    </tr>
                    <tr>
                        <td align = "right"><span class="opt_cn">Server User Password</span></td>
                        <td><input class="field form-control" id="mqtt_pass" value="{{mqtt_pass}}" pattern="[-\w\s#@/]{0,20}" onfocus="this.type='text'" type="password"></td>
                    </tr>
                </table>
                </center>  
                <paragraph><span class="opt_cn">Configuring ESP</span></paragraph>
                <center>
                <table>
                    <tr>
                        <td align = "right"><span class="opt_cn">Device name (ESP)</span></td>
                        <td><input type="text" class="field form-control" id="mqtt_name" value="{{mqtt_name}}" pattern="[-\w\s#@/]{1,24}"></td>
                    </tr>
                    <tr>
                        <td align = "right"><span class="opt_cn">Topic of external temperature</span></td>
                        <td><input type="text" class="field form-control" id="mqtt_sub" value="{{mqtt_sub}}" pattern="[-\w\s#@/]{1,24}"></td>
                    </tr>
                    <tr>
                        <td align = "right"><span class="opt_cn">Topic of inform message</span></td>
                        <td><input type="text" class="field form-control" id="mqtt_sub_inform" value="{{mqtt_sub_inform}}" pattern="[-\w\s#@/]{1,24}"></td>
                    </tr>
                    <tr>
                        <td align = "right"><span class="opt_cn">Topic of publication of temperature</span></td>
                        <td><input type="text" class="field form-control" id="mqtt_pub_temp" value="{{mqtt_pub_temp}}" pattern="[-\w\s#@/]{1,24}"></td>
                    </tr>
                    <tr>
                        <td align = "right"><span class="opt_cn">Topic of publication temp. streets</span></td>
                        <td><input type="text" class="field form-control" id="mqtt_pub_tempUl" value="{{mqtt_pub_tempUl}}" pattern="[-\w\s#@/]{1,24}"></td>
                    </tr>
                    <tr>
                        <td align = "right"><span class="opt_cn">Topic of humidity publication</span></td>
                        <td><input type="text" class="field form-control" id="mqtt_pub_hum" value="{{mqtt_pub_hum}}" pattern="[-\w\s#@/]{1,24}"></td>
                    </tr>
                    <tr>
                        <td align = "right"><span class="opt_cn">Press Release Topic</span></td>
                        <td><input type="text" class="field form-control" id="mqtt_pub_press" value="{{mqtt_pub_press}}" pattern="[-\w\s#@/]{1,24}"></td>
                    </tr>
                    <tr>
                        <td align = "right"><span class="opt_cn">Topic of publication of height</span></td>
                        <td><input type="text" class="field form-control" id="mqtt_pub_alt" value="{{mqtt_pub_alt}}" pattern="[-\w\s#@/]{1,24}"></td>
                    </tr>
                </table>
                </center>
                <span class="save_booton" onclick="set_mqtt_ust(this);">Save</span>
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
