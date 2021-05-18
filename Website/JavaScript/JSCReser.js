class Destination {
    constructor(ville, Prix,animaux) {
        this.ville = ville;
        this.Prix = Prix;
        this.animaux = animaux;
    }
  }
var marrakesh = new Destination('marrakesh', 40,false);
var dubai = new Destination('dubai', 350,false);
var boston = new Destination('boston', 50, true);
var vegas = new Destination('vegas', 100, true);
var Ville = [marrakesh, dubai, boston, vegas];

var voyage = new URLSearchParams(window.location.search).get("id");
function trouverdestination(voyage){
    for(dest of Ville){
        if(dest.ville==voyage){
            document.getElementById("DST").value= dest.ville;
            return dest.Prix
        }
    }
}

function calculprix(){
    let prixvoyage= trouverdestination(voyage)
    let nad = +document.getElementById('nad').value;
    let nenf= +document.getElementById('nenf').value;
    let dp=document.getElementById('datedepart').valueAsDate;
    let dr=document.getElementById("dateretour").valueAsDate;
    let nj=(dr-dp)/(1000*60*60*24);
    let dej=document.getElementById("dej"); 
    let frai=document.getElementById('frai');
    if (dej.checked == false){
        frai.style.display="none";
        document.getElementById("Prix").innerHTML= (prixvoyage*(nad + nenf*40/100)*nj)+'$'
        document.getElementById("PRIX").value=(prixvoyage*(nad + nenf*40/100)*nj);
    }
    else{
        frai.style.display="block";
        document.getElementById("Prix").innerHTML=(prixvoyage*(nad + nenf*40/100)*nj+ 12*(nenf+nad)*nj)+'$';
        document.getElementById("PRIX").value=(prixvoyage*(nad + nenf*40/100)*nj+ 12*(nenf+nad)*nj);
    }

}