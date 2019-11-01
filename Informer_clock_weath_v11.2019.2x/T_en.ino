void enText(){
  tMes = "To my beloved Zayushke !!!";
  tNow = "now";
  tPress = "mmHg";
  tSpeed = "m/s";
  tMin = "min.";
  tCurr = "Today";
  tTom = "Tomorrow";
  tYour = "Your";
  tPoint = "Connect to the ESP-Info access point and enter in the browser the address: 192.168.4.1         ";
  tJanuary = "January";
  tFebruary = "February";
  tMarch = "Martha";
  tApril = "April";
  tMay = "May";
  tJune = "June";
  tJuly = "July";
  tAugust = "August";
  tSeptember = "September";
  tOctober = "October";
  tNovember = "November";
  tDecember = "December";

  tMonday = "Monday";
  tTuesday = "Tuesday";
  tWednesday = "Wednesday";
  tThursday = "Thursday";
  tFriday = "Friday";
  tSaturday = "Saturday";
  tSunday = "Sunday";
  tWeatrNot = "   There is no weather update for more than 6 hours !!!   ";
  tWeatrTN = "no weather updates - ";
  if(printCom) {
    printTime();
    Serial.println("Text EN.");
  }
  weatherLang = "en";
}
