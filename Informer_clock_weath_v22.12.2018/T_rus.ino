void rusText(){
  tMes = "Моей любимой Зающке!!!";
  tNow = "сейчас";
  tPress = "ммРс";
  tSpeed = "м/с";
  tMin = "мин.";
  tCurr = "Сегодня";
  tTom = "Завтра";
  tYour = "Ваш";
  tPoint = "Подключитесь к точке доступа ESP-Info и введите в браузере адрес: 192.168.4.1         ";
  tJanuary = "января";
  tFebruary = "февраля";
  tMarch = "марта";
  tApril = "апреля";
  tMay = "мая";
  tJune = "июня";
  tJuly = "июля";
  tAugust = "августа";
  tSeptember = "сентября";
  tOctober = "октября";
  tNovember = "ноября";
  tDecember = "декабря";
  tMonday = "Понедельник";
  tTuesday = "Вторник";
  tWednesday = "Среда";
  tThursday = "Четверг";
  tFriday = "Пятница";
  tSaturday = "Суббота";
  tSunday = "Воскресенье";

  tWeatrNot = "   Нет обновления погоды более 6 часов!!!   ";
  tWeatrTN = "нет обновления погоды - ";
  if(printCom) {
    printTime();
    Serial.println("Text RUS.");
  }
  weatherLang = "ru";
}

