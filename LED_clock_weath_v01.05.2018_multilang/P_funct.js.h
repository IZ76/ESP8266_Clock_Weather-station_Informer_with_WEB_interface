const char PAGE_function_js[] PROGMEM = R"=====(
var xmlHttp=createXmlHttpObject();
function createXmlHttpObject(){
  if(window.XMLHttpRequest){
    xmlHttp=new XMLHttpRequest();
  }else{
    xmlHttp=new ActiveXObject('Microsoft.XMLHTTP');
  }
  return xmlHttp;
}
function load(){
  if(xmlHttp.readyState==0 || xmlHttp.readyState==4){
    xmlHttp.open('PUT','/configs.json',true);
    xmlHttp.send(null);
    xmlHttp.onload = function(e) {
      jsonResponse=JSON.parse(xmlHttp.responseText);
      loadBlock();
    }
  }
}
function loadBlock() {
  var data2 = JSON.parse(xmlHttp.responseText);
  data = document.getElementsByTagName('body')[0].innerHTML;
  var new_string;
  for (var key in data2) {
    new_string = data.replace(new RegExp('{{'+key+'}}', 'g'), data2[key]);
    data = new_string;
  }
  document.getElementsByTagName('body')[0].innerHTML = new_string;
  var inputs = document.getElementsByTagName("input");
  var selects = document.getElementsByTagName("select");
  for (var key in data2) {
    if(data2[key] == 'checked'){
       //alert(key);                            // выводим название найденной переменной
       for (var i = 0; i < inputs.length; i++) {
         if (inputs[i].id === key) {
           inputs[i].checked = "true";
         }
       }
    }
    for (var i = 0; i < selects.length; i++) {
      if (selects[i].id === key) {
        //alert(key +  " : " + data2[key]);
        document.getElementById(key).value = data2[key];
      }
    }
  }
  handleServerResponse();
}
function val(id){
  var v = document.getElementById(id).value;
  return v;
}
function val_sw(nameSwitch) {
  switchOn = document.getElementById(nameSwitch);
  if (switchOn.checked){
    return 1;
  }
  return 0;
}
function send_request(submit,server){
  request = new XMLHttpRequest();
  request.open("GET", server, true);
  request.send();
  save_status(submit,request);
}
function save_status(submit,request){
  old_submit = submit.value;
  request.onreadystatechange = function() {
    if (request.readyState != 4) return;
    submit.value = request.responseText;
    setTimeout(function(){
      submit.value=old_submit;
      submit_disabled(false);
    }, 1000);
  }
  submit.value = 'Зачекайте...';
  submit_disabled(true);
}
function submit_disabled(request){
  var inputs = document.getElementsByTagName("input");
  for (var i = 0; i < inputs.length; i++) {
    if (inputs[i].type === 'submit') {inputs[i].disabled = request;}
  }
}
function toggle(target) {
  var curVal = document.getElementById(target).className;
  document.getElementById(target).className = (curVal === 'hidden') ? 'show' : 'hidden';
}
function set_lang(submit) {
  server = "/lang?mowa=" + val('mowa');
  send_request(submit, server);
}
function restart(submit, texts) {
  if (confirm(texts)) {
    server = "/restart?device=ok";
    send_request(submit, server);
    return true;
  } else {
    return false;
  }
}
)=====";
