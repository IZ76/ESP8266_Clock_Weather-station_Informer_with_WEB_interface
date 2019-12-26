const char P_css[] PROGMEM = R"=====(
  @charset "utf-8";
  * {
      margin: 0;
      padding: 0;
      outline: none;
  }
  html {
      height: 100%;
      width: 100%;
  }
  body {
      color: #343434;
      background: #f7f7f7;
      height: 100%;
      width: 100%;
      font-size: 1em;
      font-family: PT Serif, sans-serif;
  }
  central-unit {
      background-color: #e4fdfd;
      box-shadow: 0 12px 15px rgba(0, 0, 0, 0.4);
      padding: 10px;
      margin-left: auto;
      margin-right: auto;
      width: 460px;
      max-width: 100%;
      display: block;
  }
  .informer {
      background-color: #eaeaea;
      margin: 5px;
      padding: 1%;
      border: 1px solid #909090;
      border-radius: 2px;
      border-color: #3e3b3b;
      font-style: italic;
      text-align: justify;
      text-indent: 30px;
      display: block;
  }
  #main_unit {text-align: center;}
  .menu_unit {
      width: 97%;
      height: 21px;
      padding: 5px;
      margin-bottom: 10px;
      text-transform: uppercase;
      display: flex;
      justify-content: space-between;
      background: rgba(0, 137, 255, 0.27);
      border-radius: 4px;
      border: 2px solid #383838;
      font-size: 1.2em;
      font-weight: bold;
  }
  .table > * > tr > td  {
    border: 1px solid #a2a9b1;
    padding: 0.2em 0.4em;
  }
  input[type=text].field, input[type=password].field {
      padding: 3px;
      margin: 1px;
      border: 1px solid #575757;
      border-radius: 2px;
  }
  input:focus[type=text].field{border: 1px solid #03d703}
  input:invalid[type=text] {
      border:1px solid red !important;
  }
  .save_booton {
      background-color: rgba(0, 137, 255, 0.27);
      padding: 5px;
      margin: 5px;
      border-radius: 2px;
      border: 2px solid #909090;
      font-size: 1em;
      font-weight: bold;
      text-transform: uppercase;
      display:inline-table;
      line-height: 100%;
      cursor:pointer;
      box-shadow: inset 0 0 10px 2px rgba(0,0,0,0.3);
      z-index: 1005;
  }
  .save_booton:hover {
      box-shadow: 0 0 10px 2px rgba(0,0,0,0.3);
  }
  .ico__text {
      margin: -0 0 -8px 0;
      font-size: .8em;
      color: #434343;
      display: block;
      cursor:pointer; 
  }
  .ico__text:hover {
      padding: 3px;
      margin: -3px;
      border-radius: 2px;
      box-shadow: 0 0 10px 2px rgba(0,0,0,0.3);
  }
  .link__img{
      text-decoration: none;
  }
  .left {float: left}
  .right {float: right}
  .center {float: center}
  .clear {clear: both}
  #table__font{text-align: center;}
  titles {
      color: darkblue;
      padding-bottom: 10px;
      font-size: 1.2em;
      font-weight: bold;
      text-align: center;
      text-transform: uppercase;
      display: block;
  }
  paragraph {
      color: #000019;
      padding-top: 5px;
      font-size: 1.2em;
      font-weight: bold;
      text-align: center;
      display: block;
      line-height: 140%;
  }
  ::selection {background: green; color: #fff}
  ::-moz-selection {background: green; color: #fff}
  select {  
      height: 22px;
      padding: 0px 5px 0px;
      margin-bottom: 2px;
      margin-top: 0;
      margin-left: 5px;
      margin-right: 5px;
      border-radius: 2px;
      border: 1px solid #909090;
  }
  header, footer {
      padding: 5px;
      margin-left: auto;
      margin-right: auto;
      width: 470px;
      max-width: 100%;
      display: block;
  }
  header {
      color: #00008B;
      font-size: 1em;
      font-weight: bold;
      text-align: center;
      line-height: 115%;
  }
)=====";
