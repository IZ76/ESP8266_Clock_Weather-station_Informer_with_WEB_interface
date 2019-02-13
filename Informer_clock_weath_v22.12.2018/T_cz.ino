void czText(){
  tMes = "Моїй коханій Зайченяткі";
  tNow = "teď";
  tPress = "mmHg";
  tSpeed = "m/s";
  tMin = "min.";
  tCurr = "Dnes";
  tTom = "Zítra";
  tYour = "Vaše";
  tPoint = "Připojte se k přístupovému bodu ESP-Info a zadejte adresu v prohlížeči: 192.168.4.1         ";
  tJanuary = "Leden";
  tFebruary = "Únor";
  tMarch = "Březen";
  tApril = "Duben";
  tMay = "Květen";
  tJune = "Červen";
  tJuly = "Červenec";
  tAugust = "Srpen";
  tSeptember = "Září";
  tOctober = "Říjen";
  tNovember = "Listopad";
  tDecember = "Prosinec";
  tMonday = "Pondělí";
  tTuesday = "Úterý";
  tWednesday = "Středa";
  tThursday = "Čtvrtek";
  tFriday = "Pátek";
  tSaturday = "Sobota";
  tSunday = "Neděle";

  tWeatrNot = "   Bez aktualizací počasí po dobu delší než 6 hodin!!!   ";
  tWeatrTN = "bez aktualizací počasí - ";
  if(printCom) {
    printTime();
    Serial.println("Text CZ.");
  }
  weatherLang = "cs";
}
