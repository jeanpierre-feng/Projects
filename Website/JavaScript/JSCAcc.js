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
var Ville = [boston,dubai,marrakesh,vegas];
var mdouna = document.getElementsByClassName("dest");

function filtre() {
  let prixmin = document.getElementById("min").value;
  let prixmax = document.getElementById("max").value;
  let domestique = document.getElementById("animaux");
  for(i=0;i<mdouna.length;i++){
    mdouna[i].style.display="block";
  }
  for (i=0;i<Ville.length;i++){
    if( Ville[i].Prix > prixmax & prixmax!=''){
      mdouna[i].style.display='none';
    }
    if( Ville[i].Prix < prixmin ){
      mdouna[i].style.display='none';
    }
  }
  if(domestique.checked){
    mdouna[1].style.display='none';
    mdouna[2].style.display='none';

  }
}
window.onclick = function(event) {
  if (event.target == modal) {
    modal.style.display = "none";
  }
}






