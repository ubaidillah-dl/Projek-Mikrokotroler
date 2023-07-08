String message, XML;

char setwaktu[] PROGMEM = R"=====(

<!DOCTYPE HTML>
<html>
  <meta name='viewport' content='width=device-width, initial-scale=1'>
    <head>
      <title>Jam Digital</title>
      <style> body { width: 97% ; text-align: center; } input, select, button, textarea { max-width: 100% ; margin: 5px; padding: 5px; border-radius: 7px; } meter, progress, output { max-width: 100% ; } h1 { color: grey; } .note { color: #555; font-size:1em;} .info { background-color: #eee; border-radius: 3px; padding-top: 17px; margin: 5px;} .tombol { background-color: #ccc; margin: 20px; padding: 10px; border-radius: 10px; text-decoration: none;}</style>
    </head>
    <body onload='process()'>
      <h1>Jam Digital</h1>
      <div class='info'>
        <span id='day'></span>/<span id='month'></span>/<span id='year'></span><span> </span>
        <span id='hour'></span>:<span id='minute'></span>:<span id='second'></span><span> </span>
        <span id='temp'></span><span>C</span><br><br>
      </div>
      <table width='100%'>
        <tr>
          <td>
            <form >
              <h4>Tanggal</h4>  
                <input type='date' name='date' min='2017-03-20'><br><br>
                <input type='submit' value='Ubah'> 
            </form>  
          </td>
          <td>
            <form >  
              <h4>Jam</h4>
              <input type='TIME' name='time'><br><br>
              <input type='submit' value='Ubah'> 
            </form>
          </td>
        </tr>
      </table>
      <br><br>
      <form id='data_form' name='frmText'>
        <label>Redup<input id="cerah" type='range' name='Cerah' min='18' max='255'>Cerah
        <br>
      </form>
      <br>
      <button onClick="setDisp()"> Simpan </button><span> </span>
      <br><br>
      </body>

      <script>
        function setDisp() {
        console.log("tombol telah ditekan!");
  
        var cerah = document.getElementById("cerah").value;
        var datadisp = {cerah:cerah};

        var xhr = new XMLHttpRequest();
        var url = "/settingdisp";

        xhr.onreadystatechange = function() {
          if(this.onreadyState == 4  && this.status == 200) {
          console.log(xhr.responseText);
          }
        };
        
        xhr.open("POST", url, true);
        xhr.send(JSON.stringify(datadisp));
        }

        var xmlHttp=createXmlHttpObject();

        function createXmlHttpObject(){
          if(window.XMLHttpRequest){
            xmlHttp=new XMLHttpRequest();
          }else{
            xmlHttp=new ActiveXObject('Microsoft.XMLHTTP');
          }
          return xmlHttp;
        }

        function process(){
          if(xmlHttp.readyState==0 || xmlHttp.readyState==4){
          xmlHttp.open('PUT','xml',true);
          xmlHttp.onreadystatechange=handleServerResponse;
          xmlHttp.send(null);
          }
        }

        function handleServerResponse(){
         if(xmlHttp.readyState==4 && xmlHttp.status==200){
           xmlResponse=xmlHttp.responseXML;
        
           xmldoc = xmlResponse.getElementsByTagName('rCerah');
           message = xmldoc[0].firstChild.nodeValue;
           document.getElementById('cerah').value=message;
         }
        }

        var xmlHttp=createXmlHttpObject();
        
        function createXmlHttpObject(){
         if(window.XMLHttpRequest){
            xmlHttp=new XMLHttpRequest();
         }else{
            xmlHttp=new ActiveXObject('Microsoft.XMLHTTP');// code for IE6, IE5
         }
         return xmlHttp;
        }

        function process(){
         if(xmlHttp.readyState==0 || xmlHttp.readyState==4){
           xmlHttp.open('PUT','xml',true);
           xmlHttp.onreadystatechange=handleServerResponse;
           xmlHttp.send(null);
         }
         setTimeout('process()',1000);
        }

        function handleServerResponse(){
         if(xmlHttp.readyState==4 && xmlHttp.status==200){
           xmlResponse=xmlHttp.responseXML;
        
           xmldoc = xmlResponse.getElementsByTagName('rYear');
           message = xmldoc[0].firstChild.nodeValue;
           document.getElementById('year').innerHTML=message;
        
           xmldoc = xmlResponse.getElementsByTagName('rMonth');
           message = xmldoc[0].firstChild.nodeValue;
           document.getElementById('month').innerHTML=message;
        
           xmldoc = xmlResponse.getElementsByTagName('rDay');
           message = xmldoc[0].firstChild.nodeValue;
           document.getElementById('day').innerHTML=message;
        
           xmldoc = xmlResponse.getElementsByTagName('rHour');
           message = xmldoc[0].firstChild.nodeValue;
           document.getElementById('hour').innerHTML=message;
        
           xmldoc = xmlResponse.getElementsByTagName('rMinute');
           message = xmldoc[0].firstChild.nodeValue;
           document.getElementById('minute').innerHTML=message;
        
           xmldoc = xmlResponse.getElementsByTagName('rSecond');
           message = xmldoc[0].firstChild.nodeValue;
           document.getElementById('second').innerHTML=message;
        
           xmldoc = xmlResponse.getElementsByTagName('rTemp');
           message = xmldoc[0].firstChild.nodeValue;
           document.getElementById('temp').innerHTML=message;
         }
        }
      </script>
</html>
)=====";
