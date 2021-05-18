//var inscrits=[{
//  mail:"test1@gamil.com",
//   psw :"123456",
//   nom:"boot1",
//   prenom : "xx"
//  },{
//   mail :"test2@gamil.com",
//   psw  :"1234567",
//     nom :"boot2",
//     prenom: 'yy'
//  }];
 // var datainscrits = JSON.stringify(inscrits);
 // localStorage.setItem("lesinscrits",datainscrits);
 // Pour verifier l'inscription il suffit de décommenter ce qui est en haut sinon vous pouver vous inscrire déconnecter et reconnecter 
 function getinfo1(){
   let mailconex=document.getElementById("mailconex").value;
   let pswconex=document.getElementById("pswconex").value;
   let datajson = localStorage.getItem('lesinscrits');
   let data= JSON.parse(datajson);
   let etat = true;
   for(x of data ){
     if(mailconex==x.mail && pswconex==x.psw){
       etat= false;
       localStorage.setItem("etatconex",'true');
       let name = x.prenom +' '+ x.nom
       localStorage.setItem("utilisateur",name);
       document.getElementById("id01").style.display="none";
       document.getElementById("utilisateur").innerHTML= "Hello!"+ localStorage.getItem("utilisateur") ;
       document.getElementById("iden").style.display="none";
       document.getElementById("insc").style.display="none";
       document.getElementById("deco").style.display="block";
     }
   }
   if (etat){
     window.alert("Email ou mdp incorrecte veillez reessayez svp");
   }
 }
 function getinfo2(){
    let mailinsc=document.getElementById("mailinsc").value;
    let psw=document.getElementById("pswinsc").value;
    let pswrepeat=document.getElementById("pswrepeat").value;
    let nom=document.getElementById("nominsc").value;
    let prenom=document.getElementById("prenominsc").value;
    if(psw != pswrepeat){
        window.alert("Vos mots de passes ne matches pas !! ");
    }
    else{
         var datainscjson = localStorage.getItem("lesinscrits");
        var datainsc = JSON.parse(datainscjson);
        var nouveau = true
        for(y of datainsc ){
            if (mailinsc == y.mail ){
                window.alert("Ce mail est déjà utilisé");
                nouveau = false;
            }
        }
        if(nouveau){
            var newutil = {
                mail: mailinsc,
                psw : psw ,
                nom: nom,
                prenom : prenom
            };
            datainsc.push(newutil);
            var newdata = JSON.stringify(datainsc);
            localStorage.setItem("lesinscrits",newdata);
            let name = prenom +' '+ nom;
            localStorage.setItem("etatconex",'true');
            localStorage.setItem("utilisateur",name);
            document.getElementById("id02").style.display="none";
            document.getElementById("utilisateur").innerHTML= "Hello!"+ localStorage.getItem("utilisateur") ;
            document.getElementById("iden").style.display="none";
            document.getElementById("insc").style.display="none";
            document.getElementById("deco").style.display="block";
            window.alert("Votre inscription a réussi!!  Soyez les bien venue");

        }
    }
   

}


 function conexdisco(){
     var etatcon = localStorage.getItem("etatconex");
     if(etatcon == "true"){
        document.getElementById("utilisateur").innerHTML= "Hello!"+ localStorage.getItem("utilisateur");
        document.getElementById("iden").style.display="none";
        document.getElementById("insc").style.display="none";
        document.getElementById("deco").style.display="block";

     }


 
 }
 function deconnex(){
    localStorage.setItem("etatconex","");
    localStorage.setItem('utilisateur','')
    document.getElementById("utilisateur").innerHTML= "Inscription/Identification" ;
    document.getElementById("iden").style.display="block";
    document.getElementById("insc").style.display="block";
    document.getElementById("deco").style.display="none";

 }