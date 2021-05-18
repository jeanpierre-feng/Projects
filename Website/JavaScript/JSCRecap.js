function recuperation(){
  document.getElementById('id03').style.display='block'
    var lien = window.location.search.substring(1);
    var elem = lien.split("&");
    var code =""
    while(code.length< 14){
      code += String(Math.floor(Math.random()*10));
      if (code.length == 4 || code.length == 9){
        code +="."
      }
    }
    document.getElementById("cc").innerHTML=code
    for (i=0;i< elem.length;i++) {
      let resultat = elem[i].split("=");
      document.getElementById(resultat[0]).innerHTML=resultat[1].toUpperCase();
      if(resultat[0]== "DEJ"){
        document.getElementById(resultat[0]).innerHTML= "Le petit déjeun est bien unclu"; 
      }
    }
}
