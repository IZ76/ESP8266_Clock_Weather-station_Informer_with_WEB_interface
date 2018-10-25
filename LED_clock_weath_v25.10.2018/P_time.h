const char P_time[] PROGMEM =  R"=====(
<html>
    <head>
        <!--meta name = "viewport" content = "width=device-width, initial-scale=1.0"-->
        <meta http-equiv = "Content-type" content = "text/html; charset=utf-8">
        <title>Led_clock_weath на ESP-12 ver:23.10.2018 (By IvanUA)</title>
        <link rel="shortcut icon" href="#" />
        <link rel = "stylesheet" type = "text/css" href = "/style.css">
        <script type = "text/javascript" src = "/function.js"></script>
        <script type = "text/javascript">
            function set_ntp(submit) {
                server = "/ntp?ntpServerName=" + val('ntpServerName') + "&timeZone=" + val('timeZone') + "&isDayLightSaving=" + val_sw('isDayLightSaving');
                server += "&al_0_0=" + val('al_0_0') + "&al_0_1=" + val('al_0_1') + "&al_0_2=" + val('al_0_2');
                server += "&al_1_0=" + val('al_1_0') + "&al_1_1=" + val('al_1_1') + "&al_1_2=" + val('al_1_2');
                server += "&al_2_0=" + val('al_2_0') + "&al_2_1=" + val('al_2_1') + "&al_2_2=" + val('al_2_2');
                server += "&al_3_0=" + val('al_3_0') + "&al_3_1=" + val('al_3_1') + "&al_3_2=" + val('al_3_2');
                server += "&al_4_0=" + val('al_4_0') + "&al_4_1=" + val('al_4_1') + "&al_4_2=" + val('al_4_2');
                server += "&md_0_0=" + val('md_0_0') + "&md_0_1=" + val('md_0_1') + "&md_0_2=" + val('md_0_2');
                server += "&md_1_0=" + val('md_1_0') + "&md_1_1=" + val('md_1_1') + "&md_1_2=" + val('md_1_2');
                server += "&md_2_0=" + val('md_2_0') + "&md_2_1=" + val('md_2_1') + "&md_2_2=" + val('md_2_2');
                server += "&md_3_0=" + val('md_3_0') + "&md_3_1=" + val('md_3_1') + "&md_3_2=" + val('md_3_2');
                server += "&md_4_0=" + val('md_4_0') + "&md_4_1=" + val('md_4_1') + "&md_4_2=" + val('md_4_2');
                server += "&md_5_0=" + val('md_5_0') + "&md_5_1=" + val('md_5_1') + "&md_5_2=" + val('md_5_2');
                server += "&md_6_0=" + val('md_6_0') + "&md_6_1=" + val('md_6_1') + "&md_6_2=" + val('md_6_2');
                server += "&md_7_0=" + val('md_7_0') + "&md_7_1=" + val('md_7_1') + "&md_7_2=" + val('md_7_2');
                server += "&md_8_0=" + val('md_8_0') + "&md_8_1=" + val('md_8_1') + "&md_8_2=" + val('md_8_2');
                server += "&md_start=" + val('md_start') + "&md_stop=" + val('md_stop');
                send_request(submit,server);
            }
            function set_ntp_auto(submit) {
                var set_date = new Date();
                var gmtHours = -set_date.getTimezoneOffset()/60 - (val_sw('isDayLightSaving'));
                document.getElementById('timeZone').value = gmtHours;
                server = "/ntp?ntpServerName=" + val('ntpServerName') + "&timeZone=" + gmtHours + "&isDayLightSaving=" + val_sw('isDayLightSaving');
                server += "&al_0_0=" + val('al_0_0') + "&al_0_1=" + val('al_0_1') + "&al_0_2=" + val('al_0_2');
                server += "&al_1_0=" + val('al_1_0') + "&al_1_1=" + val('al_1_1') + "&al_1_2=" + val('al_1_2');
                server += "&al_2_0=" + val('al_2_0') + "&al_2_1=" + val('al_2_1') + "&al_2_2=" + val('al_2_2');
                server += "&al_3_0=" + val('al_3_0') + "&al_3_1=" + val('al_3_1') + "&al_3_2=" + val('al_3_2');
                server += "&al_4_0=" + val('al_4_0') + "&al_4_1=" + val('al_4_1') + "&al_4_2=" + val('al_4_2');
                server += "&md_0_0=" + val('md_0_0') + "&md_0_1=" + val('md_0_1') + "&md_0_2=" + val('md_0_2');
                server += "&md_1_0=" + val('md_1_0') + "&md_1_1=" + val('md_1_1') + "&md_1_2=" + val('md_1_2');
                server += "&md_2_0=" + val('md_2_0') + "&md_2_1=" + val('md_2_1') + "&md_2_2=" + val('md_2_2');
                server += "&md_3_0=" + val('md_3_0') + "&md_3_1=" + val('md_3_1') + "&md_3_2=" + val('md_3_2');
                server += "&md_4_0=" + val('md_4_0') + "&md_4_1=" + val('md_4_1') + "&md_4_2=" + val('md_4_2');
                server += "&md_5_0=" + val('md_5_0') + "&md_5_1=" + val('md_5_1') + "&md_5_2=" + val('md_5_2');
                server += "&md_6_0=" + val('md_6_0') + "&md_6_1=" + val('md_6_1') + "&md_6_2=" + val('md_6_2');
                server += "&md_7_0=" + val('md_7_0') + "&md_7_1=" + val('md_7_1') + "&md_7_2=" + val('md_7_2');
                server += "&md_8_0=" + val('md_8_0') + "&md_8_1=" + val('md_8_1') + "&md_8_2=" + val('md_8_2');
                server += "&md_start=" + val('md_start') + "&md_stop=" + val('md_stop');
                send_request(submit,server);
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
            <titles>
                <div class="opt_cn">Time setting</div>
            </titles>
            <div id="main_unit">
                <paragraph><span class="opt_cn">The exact time server for example "time.nist.gov"</span></paragraph>
                <span class="opt_cn">Enter the server address</span>
                <input type="text" class="field" id="ntpServerName" value="{{ntpServerName}}" class="form-control" pattern="[0-9a-zA-Z. ]{1,20}"><br>
                <span class="opt_cn">Choose a time zone</span>
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
                <br>
                <label class="switch"><span class="opt_cn">Daylight Saving Time</span>
                    <input type="checkbox" id="isDayLightSaving">
                    <span class="switch-btn"></span>
                </label>
                <br>
                <br>
                <paragraph><span class="opt_cn">Alarm clock</span></paragraph>
                <center>
                    <table id="table__font">
                        <tr>
                            <td><span class="opt_cn">Number</span></td>
                            <td><span class="opt_cn">Hour</span></td>
                            <td><span class="opt_cn">Minute</span></td>
                            <td><span class="opt_cn">Settings</span></td>
                        </tr>
                        <tr>
                            <td><span>1</span></td>
                            <td>
                                <select id="al_0_0">
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
                                </select>
                            </td>
                            <td>
                                <select id="al_0_1">
                                    <option value = "0"> 00 </option>
                                    <option value = "1"> 01 </option>
                                    <option value = "2"> 02 </option>
                                    <option value = "3"> 03 </option>
                                    <option value = "4"> 04 </option>
                                    <option value = "5"> 05 </option>
                                    <option value = "6"> 06 </option>
                                    <option value = "7"> 07 </option>    
                                    <option value = "8"> 08 </option>
                                    <option value = "9"> 09 </option>
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
                                    <option value = "25"> 25 </option>
                                    <option value = "26"> 26 </option>
                                    <option value = "27"> 27 </option>    
                                    <option value = "28"> 28 </option>
                                    <option value = "29"> 29 </option>
                                    <option value = "30"> 30 </option>
                                    <option value = "31"> 31 </option>
                                    <option value = "32"> 32 </option>
                                    <option value = "33"> 33 </option>
                                    <option value = "34"> 34 </option>
                                    <option value = "35"> 35 </option>
                                    <option value = "36"> 36 </option>
                                    <option value = "37"> 37 </option>    
                                    <option value = "38"> 38 </option>
                                    <option value = "39"> 39 </option>
                                    <option value = "40"> 40 </option>
                                    <option value = "41"> 41 </option>
                                    <option value = "42"> 42 </option>
                                    <option value = "43"> 43 </option>
                                    <option value = "44"> 44 </option>
                                    <option value = "45"> 45 </option>
                                    <option value = "46"> 46 </option>
                                    <option value = "47"> 47 </option>    
                                    <option value = "48"> 48 </option>
                                    <option value = "49"> 49 </option>
                                    <option value = "50"> 50 </option>
                                    <option value = "51"> 51 </option>
                                    <option value = "52"> 52 </option>
                                    <option value = "53"> 53 </option>
                                    <option value = "54"> 54 </option>
                                    <option value = "55"> 55 </option>
                                    <option value = "56"> 56 </option>
                                    <option value = "57"> 57 </option>    
                                    <option value = "58"> 58 </option>
                                    <option value = "59"> 59 </option>
                                </select>
                            </td>
                            <td>
                                <select id="al_0_2">
                                    <option value="0">OFF</option>
                                    <option value="11">ONCE</option>
                                    <option value="8">MON-FRI (2-6)</option>
                                    <option value="9">MON-SAT (2-7)</option>
                                    <option value="10">SAT-SUN (6+1)</option>
                                    <option value="1">SUN (1)</option>
                                    <option value="2">MON (2)</option>
                                    <option value="3">TUE (3)</option>
                                    <option value="4">WED (4)</option>
                                    <option value="5">THU (5)</option>
                                    <option value="6">FRI (6)</option>
                                    <option value="7">SAT (7)</option>
                                    <option value="12">ALWAYS</option>
                                </select>
                            </td>
                        </tr>
                        <tr>
                            <td><span>2</span></td>
                            <td>
                                <select id="al_1_0">
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
                                </select>
                            </td>
                            <td>
                                <select id="al_1_1">
                                    <option value = "0"> 00 </option>
                                    <option value = "1"> 01 </option>
                                    <option value = "2"> 02 </option>
                                    <option value = "3"> 03 </option>
                                    <option value = "4"> 04 </option>
                                    <option value = "5"> 05 </option>
                                    <option value = "6"> 06 </option>
                                    <option value = "7"> 07 </option>    
                                    <option value = "8"> 08 </option>
                                    <option value = "9"> 09 </option>
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
                                    <option value = "25"> 25 </option>
                                    <option value = "26"> 26 </option>
                                    <option value = "27"> 27 </option>    
                                    <option value = "28"> 28 </option>
                                    <option value = "29"> 29 </option>
                                    <option value = "30"> 30 </option>
                                    <option value = "31"> 31 </option>
                                    <option value = "32"> 32 </option>
                                    <option value = "33"> 33 </option>
                                    <option value = "34"> 34 </option>
                                    <option value = "35"> 35 </option>
                                    <option value = "36"> 36 </option>
                                    <option value = "37"> 37 </option>    
                                    <option value = "38"> 38 </option>
                                    <option value = "39"> 39 </option>
                                    <option value = "40"> 40 </option>
                                    <option value = "41"> 41 </option>
                                    <option value = "42"> 42 </option>
                                    <option value = "43"> 43 </option>
                                    <option value = "44"> 44 </option>
                                    <option value = "45"> 45 </option>
                                    <option value = "46"> 46 </option>
                                    <option value = "47"> 47 </option>    
                                    <option value = "48"> 48 </option>
                                    <option value = "49"> 49 </option>
                                    <option value = "50"> 50 </option>
                                    <option value = "51"> 51 </option>
                                    <option value = "52"> 52 </option>
                                    <option value = "53"> 53 </option>
                                    <option value = "54"> 54 </option>
                                    <option value = "55"> 55 </option>
                                    <option value = "56"> 56 </option>
                                    <option value = "57"> 57 </option>    
                                    <option value = "58"> 58 </option>
                                    <option value = "59"> 59 </option>
                                </select>
                            </td>
                            <td>
                                <select id="al_1_2">
                                    <option value="0">OFF</option>
                                    <option value="11">ONCE</option>
                                    <option value="8">MON-FRI (2-6)</option>
                                    <option value="9">MON-SAT (2-7)</option>
                                    <option value="10">SAT-SUN (6+1)</option>
                                    <option value="1">SUN (1)</option>
                                    <option value="2">MON (2)</option>
                                    <option value="3">TUE (3)</option>
                                    <option value="4">WED (4)</option>
                                    <option value="5">THU (5)</option>
                                    <option value="6">FRI (6)</option>
                                    <option value="7">SAT (7)</option>
                                    <option value="12">ALWAYS</option>
                                </select>
                            </td>
                        </tr>
                        <tr>
                            <td><span>3</span></td>
                            <td>
                                <select id="al_2_0">
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
                                </select>
                            </td>
                            <td>
                                <select id="al_2_1">
                                    <option value = "0"> 00 </option>
                                    <option value = "1"> 01 </option>
                                    <option value = "2"> 02 </option>
                                    <option value = "3"> 03 </option>
                                    <option value = "4"> 04 </option>
                                    <option value = "5"> 05 </option>
                                    <option value = "6"> 06 </option>
                                    <option value = "7"> 07 </option>    
                                    <option value = "8"> 08 </option>
                                    <option value = "9"> 09 </option>
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
                                    <option value = "25"> 25 </option>
                                    <option value = "26"> 26 </option>
                                    <option value = "27"> 27 </option>    
                                    <option value = "28"> 28 </option>
                                    <option value = "29"> 29 </option>
                                    <option value = "30"> 30 </option>
                                    <option value = "31"> 31 </option>
                                    <option value = "32"> 32 </option>
                                    <option value = "33"> 33 </option>
                                    <option value = "34"> 34 </option>
                                    <option value = "35"> 35 </option>
                                    <option value = "36"> 36 </option>
                                    <option value = "37"> 37 </option>    
                                    <option value = "38"> 38 </option>
                                    <option value = "39"> 39 </option>
                                    <option value = "40"> 40 </option>
                                    <option value = "41"> 41 </option>
                                    <option value = "42"> 42 </option>
                                    <option value = "43"> 43 </option>
                                    <option value = "44"> 44 </option>
                                    <option value = "45"> 45 </option>
                                    <option value = "46"> 46 </option>
                                    <option value = "47"> 47 </option>    
                                    <option value = "48"> 48 </option>
                                    <option value = "49"> 49 </option>
                                    <option value = "50"> 50 </option>
                                    <option value = "51"> 51 </option>
                                    <option value = "52"> 52 </option>
                                    <option value = "53"> 53 </option>
                                    <option value = "54"> 54 </option>
                                    <option value = "55"> 55 </option>
                                    <option value = "56"> 56 </option>
                                    <option value = "57"> 57 </option>    
                                    <option value = "58"> 58 </option>
                                    <option value = "59"> 59 </option>
                                </select>
                            </td>
                           <td>
                                <select id="al_2_2">
                                    <option value="0">OFF</option>
                                    <option value="11">ONCE</option>
                                    <option value="8">MON-FRI (2-6)</option>
                                    <option value="9">MON-SAT (2-7)</option>
                                    <option value="10">SAT-SUN (6+1)</option>
                                    <option value="1">SUN (1)</option>
                                    <option value="2">MON (2)</option>
                                    <option value="3">TUE (3)</option>
                                    <option value="4">WED (4)</option>
                                    <option value="5">THU (5)</option>
                                    <option value="6">FRI (6)</option>
                                    <option value="7">SAT (7)</option>
                                    <option value="12">ALWAYS</option>
                                </select>
                            </td>
                        </tr>
                        <tr>
                            <td><span>4</span></td>
                            <td>
                                <select id="al_3_0">
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
                                </select>
                            </td>
                            <td>
                                <select id="al_3_1">
                                    <option value = "0"> 00 </option>
                                    <option value = "1"> 01 </option>
                                    <option value = "2"> 02 </option>
                                    <option value = "3"> 03 </option>
                                    <option value = "4"> 04 </option>
                                    <option value = "5"> 05 </option>
                                    <option value = "6"> 06 </option>
                                    <option value = "7"> 07 </option>    
                                    <option value = "8"> 08 </option>
                                    <option value = "9"> 09 </option>
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
                                    <option value = "25"> 25 </option>
                                    <option value = "26"> 26 </option>
                                    <option value = "27"> 27 </option>    
                                    <option value = "28"> 28 </option>
                                    <option value = "29"> 29 </option>
                                    <option value = "30"> 30 </option>
                                    <option value = "31"> 31 </option>
                                    <option value = "32"> 32 </option>
                                    <option value = "33"> 33 </option>
                                    <option value = "34"> 34 </option>
                                    <option value = "35"> 35 </option>
                                    <option value = "36"> 36 </option>
                                    <option value = "37"> 37 </option>    
                                    <option value = "38"> 38 </option>
                                    <option value = "39"> 39 </option>
                                    <option value = "40"> 40 </option>
                                    <option value = "41"> 41 </option>
                                    <option value = "42"> 42 </option>
                                    <option value = "43"> 43 </option>
                                    <option value = "44"> 44 </option>
                                    <option value = "45"> 45 </option>
                                    <option value = "46"> 46 </option>
                                    <option value = "47"> 47 </option>    
                                    <option value = "48"> 48 </option>
                                    <option value = "49"> 49 </option>
                                    <option value = "50"> 50 </option>
                                    <option value = "51"> 51 </option>
                                    <option value = "52"> 52 </option>
                                    <option value = "53"> 53 </option>
                                    <option value = "54"> 54 </option>
                                    <option value = "55"> 55 </option>
                                    <option value = "56"> 56 </option>
                                    <option value = "57"> 57 </option>    
                                    <option value = "58"> 58 </option>
                                    <option value = "59"> 59 </option>
                                </select>
                            </td>
                            <td>
                                <select id="al_3_2">
                                    <option value="0">OFF</option>
                                    <option value="11">ONCE</option>
                                    <option value="8">MON-FRI (2-6)</option>
                                    <option value="9">MON-SAT (2-7)</option>
                                    <option value="10">SAT-SUN (6+1)</option>
                                    <option value="1">SUN (1)</option>
                                    <option value="2">MON (2)</option>
                                    <option value="3">TUE (3)</option>
                                    <option value="4">WED (4)</option>
                                    <option value="5">THU (5)</option>
                                    <option value="6">FRI (6)</option>
                                    <option value="7">SAT (7)</option>
                                    <option value="12">ALWAYS</option>
                                </select>
                            </td>
                        </tr>
                        <tr>
                            <td><span>5</span></td>
                            <td>
                                <select id="al_4_0">
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
                                </select>
                            </td>
                            <td>
                                <select id="al_4_1">
                                    <option value = "0"> 00 </option>
                                    <option value = "1"> 01 </option>
                                    <option value = "2"> 02 </option>
                                    <option value = "3"> 03 </option>
                                    <option value = "4"> 04 </option>
                                    <option value = "5"> 05 </option>
                                    <option value = "6"> 06 </option>
                                    <option value = "7"> 07 </option>    
                                    <option value = "8"> 08 </option>
                                    <option value = "9"> 09 </option>
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
                                    <option value = "25"> 25 </option>
                                    <option value = "26"> 26 </option>
                                    <option value = "27"> 27 </option>    
                                    <option value = "28"> 28 </option>
                                    <option value = "29"> 29 </option>
                                    <option value = "30"> 30 </option>
                                    <option value = "31"> 31 </option>
                                    <option value = "32"> 32 </option>
                                    <option value = "33"> 33 </option>
                                    <option value = "34"> 34 </option>
                                    <option value = "35"> 35 </option>
                                    <option value = "36"> 36 </option>
                                    <option value = "37"> 37 </option>    
                                    <option value = "38"> 38 </option>
                                    <option value = "39"> 39 </option>
                                    <option value = "40"> 40 </option>
                                    <option value = "41"> 41 </option>
                                    <option value = "42"> 42 </option>
                                    <option value = "43"> 43 </option>
                                    <option value = "44"> 44 </option>
                                    <option value = "45"> 45 </option>
                                    <option value = "46"> 46 </option>
                                    <option value = "47"> 47 </option>    
                                    <option value = "48"> 48 </option>
                                    <option value = "49"> 49 </option>
                                    <option value = "50"> 50 </option>
                                    <option value = "51"> 51 </option>
                                    <option value = "52"> 52 </option>
                                    <option value = "53"> 53 </option>
                                    <option value = "54"> 54 </option>
                                    <option value = "55"> 55 </option>
                                    <option value = "56"> 56 </option>
                                    <option value = "57"> 57 </option>    
                                    <option value = "58"> 58 </option>
                                    <option value = "59"> 59 </option>
                                </select>
                            </td>
                            <td>
                                <select id="al_4_2">
                                    <option value="0">OFF</option>
                                    <option value="11">ONCE</option>
                                    <option value="8">MON-FRI (2-6)</option>
                                    <option value="9">MON-SAT (2-7)</option>
                                    <option value="10">SAT-SUN (6+1)</option>
                                    <option value="1">SUN (1)</option>
                                    <option value="2">MON (2)</option>
                                    <option value="3">TUE (3)</option>
                                    <option value="4">WED (4)</option>
                                    <option value="5">THU (5)</option>
                                    <option value="6">FRI (6)</option>
                                    <option value="7">SAT (7)</option>
                                    <option value="12">ALWAYS</option>
                                </select>
                            </td>
                        </tr>
                    </table>
                </center>
                <br>
                <paragraph><span class="opt_cn">Memorable dates</span></paragraph>
                <center>
                    <table id="table__font">
                        <tr>
                            <td><span class="opt_cn">Number</span></td>
                            <td><span class="opt_cn">Day</span></td>
                            <td><span class="opt_cn">Month</span></td>
                            <td><span class="opt_cn">Message</span></td>
                        </tr>
                        <tr>
                            <td><span>1</span></td>
                            <td>
                                <select id="md_0_0">
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
                                    <option value = "24"> 24 </option>
                                    <option value = "25"> 25 </option>
                                    <option value = "26"> 26 </option>
                                    <option value = "27"> 27 </option>    
                                    <option value = "28"> 28 </option>
                                    <option value = "29"> 29 </option>
                                    <option value = "30"> 30 </option>
                                    <option value = "31"> 31 </option>
                                </select>
                            </td>
                            <td>
                                <select id="md_0_1">
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
                                </select>
                            </td>
                            <td>
                                <input type="text" class="field form-control" id="md_0_2" value="{{md_0_2}}" pattern=".{1,25}">
                            </td>
                        </tr>
                        <tr>
                            <td><span>2</span></td>
                            <td>
                                <select id="md_1_0">
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
                                    <option value = "24"> 24 </option>
                                    <option value = "25"> 25 </option>
                                    <option value = "26"> 26 </option>
                                    <option value = "27"> 27 </option>    
                                    <option value = "28"> 28 </option>
                                    <option value = "29"> 29 </option>
                                    <option value = "30"> 30 </option>
                                    <option value = "31"> 31 </option>
                                </select>
                            </td>
                            <td>
                                <select id="md_1_1">
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
                                </select>
                            </td>
                            <td>
                                <input type="text" class="field form-control" id="md_1_2" value="{{md_1_2}}" pattern=".{1,25}">
                            </td>
                        </tr>
                        <tr>
                            <td><span>3</span></td>
                            <td>
                                <select id="md_2_0">
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
                                    <option value = "24"> 24 </option>
                                    <option value = "25"> 25 </option>
                                    <option value = "26"> 26 </option>
                                    <option value = "27"> 27 </option>    
                                    <option value = "28"> 28 </option>
                                    <option value = "29"> 29 </option>
                                    <option value = "30"> 30 </option>
                                    <option value = "31"> 31 </option>
                                </select>
                            </td>
                            <td>
                                <select id="md_2_1">
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
                                </select>
                            </td>
                            <td>
                                <input type="text" class="field form-control" id="md_2_2" value="{{md_2_2}}" pattern=".{1,25}">
                            </td>
                        </tr>
                        <tr>
                            <td><span>4</span></td>
                            <td>
                                <select id="md_3_0">
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
                                    <option value = "24"> 24 </option>
                                    <option value = "25"> 25 </option>
                                    <option value = "26"> 26 </option>
                                    <option value = "27"> 27 </option>    
                                    <option value = "28"> 28 </option>
                                    <option value = "29"> 29 </option>
                                    <option value = "30"> 30 </option>
                                    <option value = "31"> 31 </option>
                                </select>
                            </td>
                            <td>
                                <select id="md_3_1">
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
                                </select>
                            </td>
                            <td>
                                <input type="text" class="field form-control" id="md_3_2" value="{{md_3_2}}" pattern=".{1,25}">
                            </td>
                        </tr>
                        <tr>
                            <td><span>5</span></td>
                            <td>
                                <select id="md_4_0">
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
                                    <option value = "24"> 24 </option>
                                    <option value = "25"> 25 </option>
                                    <option value = "26"> 26 </option>
                                    <option value = "27"> 27 </option>    
                                    <option value = "28"> 28 </option>
                                    <option value = "29"> 29 </option>
                                    <option value = "30"> 30 </option>
                                    <option value = "31"> 31 </option>
                                </select>
                            </td>
                            <td>
                                <select id="md_4_1">
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
                                </select>
                            </td>
                            <td>
                                <input type="text" class="field form-control" id="md_4_2" value="{{md_4_2}}" pattern=".{1,25}">
                            </td>
                        </tr>
                        <tr>
                            <td><span>6</span></td>
                            <td>
                                <select id="md_5_0">
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
                                    <option value = "24"> 24 </option>
                                    <option value = "25"> 25 </option>
                                    <option value = "26"> 26 </option>
                                    <option value = "27"> 27 </option>    
                                    <option value = "28"> 28 </option>
                                    <option value = "29"> 29 </option>
                                    <option value = "30"> 30 </option>
                                    <option value = "31"> 31 </option>
                                </select>
                            </td>
                            <td>
                                <select id="md_5_1">
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
                                </select>
                            </td>
                            <td>
                                <input type="text" class="field form-control" id="md_5_2" value="{{md_5_2}}" pattern=".{1,25}">
                            </td>
                        </tr>
                        <tr>
                            <td><span>7</span></td>
                            <td>
                                <select id="md_6_0">
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
                                    <option value = "24"> 24 </option>
                                    <option value = "25"> 25 </option>
                                    <option value = "26"> 26 </option>
                                    <option value = "27"> 27 </option>    
                                    <option value = "28"> 28 </option>
                                    <option value = "29"> 29 </option>
                                    <option value = "30"> 30 </option>
                                    <option value = "31"> 31 </option>
                                </select>
                            </td>
                            <td>
                                <select id="md_6_1">
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
                                </select>
                            </td>
                            <td>
                                <input type="text" class="field form-control" id="md_6_2" value="{{md_6_2}}" pattern=".{1,25}">
                            </td>
                        </tr>
                        <tr>
                            <td><span>8</span></td>
                            <td>
                                <select id="md_7_0">
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
                                    <option value = "24"> 24 </option>
                                    <option value = "25"> 25 </option>
                                    <option value = "26"> 26 </option>
                                    <option value = "27"> 27 </option>    
                                    <option value = "28"> 28 </option>
                                    <option value = "29"> 29 </option>
                                    <option value = "30"> 30 </option>
                                    <option value = "31"> 31 </option>
                                </select>
                            </td>
                            <td>
                                <select id="md_7_1">
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
                                </select>
                            </td>
                            <td>
                                <input type="text" class="field form-control" id="md_7_2" value="{{md_7_2}}" pattern=".{1,25}">
                            </td>
                        </tr>
                        <tr>
                            <td><span>9</span></td>
                            <td>
                                <select id="md_8_0">
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
                                    <option value = "24"> 24 </option>
                                    <option value = "25"> 25 </option>
                                    <option value = "26"> 26 </option>
                                    <option value = "27"> 27 </option>    
                                    <option value = "28"> 28 </option>
                                    <option value = "29"> 29 </option>
                                    <option value = "30"> 30 </option>
                                    <option value = "31"> 31 </option>
                                </select>
                            </td>
                            <td>
                                <select id="md_8_1">
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
                                </select>
                            </td>
                            <td>
                                <input type="text" class="field form-control" id="md_8_2" value="{{md_8_2}}" pattern=".{1,25}">
                            </td>
                        </tr>
                    </table>
                </center>
                <br>
                <center>
                    <table id="table__font">
                        <tr>
                            <td><span class="opt_cn">Show anniversaries with:</span></td>
                            <td>
                                <select id="md_start">
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
                                </select>
                            </td>
                            <td><span class="opt_cn">to:</span></td>
                            <td>
                                <select id="md_stop">
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
                                </select>
                            </td>
                        </tr>
                    </table>
                </center>
                <br>
                <span class="save_booton" onclick="set_ntp(this);">Save</span>
                <br>
                <span class="save_booton" onclick="set_ntp_auto(this);">Belt out of PC and saving</span>
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
