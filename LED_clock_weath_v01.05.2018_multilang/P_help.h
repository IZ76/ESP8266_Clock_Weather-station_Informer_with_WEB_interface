//
//  HTML PAGE
//
const char PAGE_Help[] PROGMEM =  R"=====(
<html>
    <head>
        <!--meta name = "viewport" content = "width=device-width, initial-scale=1.0"-->
        <meta http-equiv = "Content-type" content = "text/html; charset=utf-8">
        <title>Led_clock_weath на ESP-12 ver:01.05.2018 (By IvanUA)</title>
        <link rel="shortcut icon" href="#" />
        <link rel = "stylesheet" type = "text/css" href = "/style.css">
        <script type = "text/javascript" src = "/function.js"></script>
        <script type = "text/javascript">
            function set_printCom(submit) {
                server = "/printCom?printCom=" + val_sw('printCom');
                send_request(submit, server);
            }
            function resetConfig(submit,texts) {
                if(confirm(texts)) {
                    server = "/resetConfig?device=ok";
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
            <titles>Якщо щось пішло не так...</titles>
            <div class="informer"> УВАГА!!! Деякі зміни можуть бути незворотніми!!!
            </div>            
            <div id="main_unit">
                <div class="informer">
                    Якщо ви щось не вірно ввели і не можете цьoго змінити, то поверніть пристрій до заводських налаштувань. Файл конфігурації буде видалено. Пристрій перезавантажено
                </div>  
                <a class = "btn btn-block btn-default" href = "/configs.json">Відкрити файл конфігурації</a>
                <hr>
                <label class="switch">Відображати інформацію в СОМ порт
                    <input type="checkbox" id="printCom" name="switch-btn" class="checkbox">
                    <span class="switch-btn"></span>
                </label>
                <input type="submit" id="saves" onclick="set_printCom(this);" value="Зберегти">
            </div>
            <center>
            <div>
                <b>Оновлення: виберіть та завантажте прошивку (bin)</b>
                <form method="POST" action="/update" enctype="multipart/form-data">
                    <div>
                        <input type="file"  name="update" style="height: 33px;">
                        <input type="submit" value="завантажити" onclick="this.value='Зачекайте...';">
                    </div>
                </form>
            </div>
            <div id="menu_unit">    
                <a class="link" href="/" title="Тут можна налаштувати параметри точки доступу або параметри підключення до мережі WiFi">Налаштування wifi</a>
                <a class="link" href="/time.html" title="Тут можна виконати налаштування сервера точного часу і годинної зони" img     scr="img/clock.png">Налаштування часу</a>
                <a class="link" href="/mqtt.html" title="Тут можна виконати налаштуваня підключення до серверу MQTT">Налаштування mqtt</a>
                <a class="link" href="/weather.html" title="Тут можна виконати налаштування сервера погоди, міста для прогнозу та інше">Налаштування погоди</a>
                <a class="link" href="/led.html" title="Тут можна виконати налаштування параметрів екрану, яскравості та іншого.">Налаштування екрану</a>
                <a class="link" href="/help.html" title="Якщо шось пішло не так...">Поміч</a>
                <input type="submit" id="reset" onclick = "resetConfig(this,'Ви дійсно бажаєте повернутися до заводських налаштувань?');" value="Повернутися до заводських налаштувань">
            </div>
            </center>
        </central-unit>
        <footer>
            <a class="link" href="http://forum.amperka.ru/threads/%D0%A7%D0%B0%D1%81%D1%8B-%D0%BD%D0%B0-esp-01-nodemcu-max7219-web-%D0%B8%D0%BD%D1%82%D0%B5%D1%80%D1%84%D0%B5%D0%B9%D1%81.12767/"><span class="left">Амперка</span></a>
            <span class="center">Мова:</span>
            <select id = "mowa" name = "mowa" onclick="set_lang(this);">
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
