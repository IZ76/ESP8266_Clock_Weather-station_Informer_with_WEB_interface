//
//  HTML PAGE
//
const char PAGE_TimeSettings[] PROGMEM =  R"=====(
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
          function handleServerResponse(){
            clearTimeout(set_real_time);
            var res = jsonResponse.time.split(":");
            real_time(hours=res[0],min=res[1],sec=res[2]);
            document.body.style.backgroundColor="rgb("+jsonResponse.rgb+")";
          }
          function real_time(hours,min,sec){
            sec=Number(sec)+1;
            if (sec>=60){min=Number(min)+1;sec=0;}
            if (min>=60){hours=Number(hours)+1;min=0;}
            if (hours>=24){hours=0};
            document.getElementById("time").innerHTML = "Час на ESP "+hours+":"+(min<10?"0":"")+min+":"+(sec<10?"0":"")+sec;
            set_real_time = setTimeout("real_time("+hours+","+min+","+sec+");", 1000);
          }
          function load_time(submit){
            server = "/Time";
            send_request(submit,server);
            load();
          }
          function set_ntp(submit) {
            server = "/ntp?ntpServerName=" + val('ntpServerName') + "&timeZone=" + val('timeZone') + "&kuOn=" + val('kuOn') + "&kuOff=" + val('kuOff') + "&isDayLightSaving=" + val_sw('isDayLightSaving');
            send_request(submit,server);
          }
          function set_ntp_auto(submit) {
            var set_date = new Date();
            var gmtHours = -set_date.getTimezoneOffset()/60 - (val_sw('isDayLightSaving'));
            document.getElementById('timeZone').value = gmtHours;
            server = "/ntp?ntpServerName=" + val('ntpServerName') + "&timeZone=" + gmtHours + "&kuOn=" + val('kuOn') + "&kuOff=" + val('kuOff') + "&isDayLightSaving=" + val_sw('isDayLightSaving');
            send_request(submit,server);
          }
        </script>
    </head>
    <body onload = "load();">
        <header>
            ЧАСИ на ESP-12 ver: 01.05.2018 (by IvanZah)
        </header>       
        <central-unit>
            <titles>Налаштуваня часу</titles>
            <div class="informer" id="time"> {{time}} </div>

            <div id="main_unit">
                <paragraph>Сервер точного часу типу "time.nist.gov"</paragraph>
                <span>Введіть адрес серверу</span>
                <input type="text" class="field" id="ntpServerName" value="{{ntpServerName}}" class="form-control" pattern="[0-9a-zA-Z. ]{1,20}" placeholder="Сервер часу"><br>
                <span>Вкажіть часову зону</span>
                <select id = "timeZone">
                    <option value="-12.00"> (GMT) -12:00 </option>
                    <option value="-11.00"> (GMT) -11:00 </option>
                    <option value="-10.00"> (GMT) -10:00 </option>
                    <option value="-9.00" > (GMT) -09:00 </option>
                    <option value="-8.00" > (GMT) -08:00 </option>
                    <option value="-7.00" > (GMT) -07:00 </option>
                    <option value="-6.00" > (GMT) -06:00 </option>
                    <option value="-5.00" > (GMT) -05:00 </option>
                    <option value="-4.00" > (GMT) -04:00 </option>
                    <option value="-3.50" > (GMT) -03:30 </option>
                    <option value="-3.00" > (GMT) -03:00 </option>
                    <option value="-2.00" > (GMT) -02:00 </option>
                    <option value="-1.00" > (GMT) -01:00 </option>
                    <option value="0.00"  > (GMT) +00:00 </option>
                    <option value="1.00"  > (GMT) +01:00 </option>
                    <option value="2.00"  > (GMT) +02:00 </option>
                    <option value="3.00"  > (GMT) +03:00 </option>
                    <option value="3.50"  > (GMT) +03:30 </option>
                    <option value="4.00"  > (GMT) +04:00 </option>
                    <option value="4.50"  > (GMT) +04:30 </option>
                    <option value="5.00"  > (GMT) +05:00 </option>
                    <option value="5.50"  > (GMT) +05:30 </option>
                    <option value="5.75"  > (GMT) +05:45 </option>
                    <option value="6.00"  > (GMT) +06:00 </option>
                    <option value="6.50"  > (GMT) +06:30 </option>
                    <option value="7.00"  > (GMT) +07:00 </option>
                    <option value="8.00"  > (GMT) +08:00 </option>
                    <option value="8.50"  > (GMT) +08:30 </option>
                    <option value="8.75"  > (GMT) +08:45 </option>
                    <option value="9.00"  > (GMT) +09:00 </option>
                    <option value="9.50"  > (GMT) +09:30 </option>
                    <option value="10.00" > (GMT) +10:00 </option>
                    <option value="10.50" > (GMT) +10:30 </option>
                    <option value="11.00" > (GMT) +11:00 </option>
                    <option value="12.00" > (GMT) +12:00 </option>
                    <option value="12.75" > (GMT) +12:45 </option>
                    <option value="13.00" > (GMT) +13:00 </option>
                    <option value="14.00" > (GMT) +14:00 </option>
                </select>
                <label class="switch">Перехід на літній час
                    <input type="checkbox" id="isDayLightSaving">
                    <span class="switch-btn"></span>
                </label>
                <paragraph>Щогодинний сигнал</paragraph>
                <tr>
                    <td align = "right">"Кукушка" працює з: </td>
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
                    <td align = "right"> до: </td>
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
                        <option value = "24"> 24 </option>
                    </select></td>
                </tr>
                <input type="submit" id="saves" onclick="set_ntp(this);" value="Зберегти">
                <input type="submit" id="saves" onclick="set_ntp_auto(this);" value="Визначеня зони з ПК та збереження">
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
