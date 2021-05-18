#LERICHE FENG 19/12/2019
#Space invaders sur tkinter
#Fichier a exectuer pour jouer
#Python3.6.4

#A ajouter :
    #Connexion/deconnexion
    #Plusieurs niveaux
    #Plusieurs vaisseaux
    #d'autres rochers
    #Des fonctionnalite aurtes dans les barres de menu deroulant (triche, a propos...)
from Tkinter import *
import func as f
import random as rd

#Classes utilisees

class vaisseau:
    def __init__(self, joueur, position, taille, hitbox=None, score=0, direction="", vie=int):
        self.joueur = joueur
        self.position = position
        self.taille = taille
        self.hitbox = hitbox
        self.score = score
        self.direction = direction
        self.vie = vie

class projectile:
    def __init__(self, joueur, position, taille, hitbox=None):
        self.joueur = joueur
        self.position = position
        self.taille = taille
        self.hitbox = hitbox


#Variables utilisees

refresh = 50
listeVaisseaux = []
listeVaisseauxEnnemis = []
listeRochers = []
vaisseauJoueur = vaisseau(1, [0,0], 1)
listeProjectiles = []
listeProjectilesEnnemis = []

#########################################################################################################

#Pas de possibilite de connexion pour l'instant

# def delete_frame(frame):
#     for i in frame.winfo_children():
#         i.grid_forget()

# def connexion():
#     for i in listeJoueurs:
#         if Saisie_identifiant.get() == i.id and Saisie_mdp.get() == i.motDePasse:
#             delete_frame(Frame_score)
#             Label_score_affiche.grid(row=1, column=1)
#             Label_vie.grid(row = 1, column = 5)
#             Label_vieNb.grid(row = 1, column = 6)
#             Bouton_deconnexion.grid(row=1, column = 4)
#             player_co.set(i.id)
#             Label_connecte.grid(row=1, column=2)

# def deconnexion(): 
#     delete_frame(Frame_score)
#     Frame_score.grid(row = 0, column = 0)
#     Label_score.grid(row=1, column=0)
#     Label_score_affiche.grid(row=1, column=1)
#     Label_identifiant.grid(row=0, column=2)
#     Label_mdp.grid(row=1, column=2)
#     Saisie_identifiant.grid(row=0, column=3)
#     Saisie_mdp.grid(row=1, column=3)
#     Bouton_connexion.grid(row=0, column = 4)
#     Label_vie.grid(row = 1, column = 5)
#     Label_vieNb.grid(row = 1, column = 6)

#########################################################################################################

#Evenements claviers
#Lors que l'appuie sur gauche ou droite, le vaisseau se deplace a gauche ou a droite
def deplacerVaisseau(event):
    touche = event.keysym
    if touche == 'Left' and vaisseauJoueur.position[0] > 2*vaisseauJoueur.taille:
        depl = -10
        vaisseauJoueur.position[0] = vaisseauJoueur.position[0] + depl #Changement de l'information de position
    elif touche == 'Right' and vaisseauJoueur.position[0] < largeurCanevas_jeu - 2*vaisseauJoueur.taille:
        depl = 10
        vaisseauJoueur.position[0] = vaisseauJoueur.position[0] + depl #Changement de l'information de position
    Canevas_jeu.move(vaisseauJoueur.hitbox, depl, 0) #Deplacement visuel


#Lors de l'appuie sur espace, un projectile est envoye 
def tirer(event): 
    global jeuEnMarche
    touche = event.keysym
    if jeuEnMarche and touche == "space": #Si appuie sur espace
        x = vaisseauJoueur.position[0]
        y = vaisseauJoueur.position[1]
        #Creation d'un projectile devant le vaisseau
        newproj = projectile(0, [x,y-vaisseauJoueur.taille], vaisseauJoueur.taille//10)
        newproj.hitbox = Canevas_jeu.create_image(x,y-vaisseauJoueur.taille, image = imageMissile, anchor="center")
        #Ajout du projectile a la liste des projectiles
        listeProjectiles.append(newproj)




#Lance le jeu et la fonction principale jeuEnFonctionnement
def start():
    global jeuEnMarche
    jeuEnMarche = True
    f.remplacerBouton(Bouton_start, Bouton_resume)
    jeuEnFonctionnement()

#Autre fonction juste pour avoir un nom clair
def restart():
    initilisation()

def jeuEnFonctionnement():
    global jeuEnMarche
    if jeuEnMarche:
        #Rappel de la fonction apres ...ms
        Canevas_jeu.after(refresh, jeuEnFonctionnement)
        #deplacements
        f.deplacementProjectile(jeuEnMarche, listeProjectiles, Canevas_jeu, 15)
        f.deplacementProjectileEnnemis(jeuEnMarche, listeProjectilesEnnemis, Canevas_jeu, 5, hauteurCanevas_jeu, vie_int, vaisseauJoueur)
        f.deplacerVaisseauEnnemis(listeVaisseauxEnnemis, Canevas_jeu, 3, 10, largeurCanevas_jeu)
        #collisions
        f.destructionEnnemis(listeProjectiles, listeVaisseauxEnnemis, Canevas_jeu, score_int)
        f.collisionRocher(listeProjectilesEnnemis,listeRochers,listeProjectiles,Canevas_jeu)
        f.tirEnnemi(jeuEnMarche, listeVaisseauxEnnemis, listeProjectilesEnnemis, Canevas_jeu, 0.08, 15)
        #Verification de victoire ou defaite a chaque instant
        defaite()
        victoire()
        #Affichage
        f.remplacerBouton(Bouton_resume, Bouton_pause)

#Fonctions des boutons


#Lorsque les conditions de defaite sont remplies, affichage de l'ecran de defaite, jeu en pause
#et possibilite de recommencer
def defaite():
    global jeuEnMarche
    vie = vie_int.get()
    if vie <= 0 and jeuEnMarche: #Si le joueur n'a plus de vie
        jeuEnMarche = False #Jeu pause
        Canevas_jeu.delete('all') #Ecran vide 
        gameOver = Canevas_jeu.create_image(400,300, image = game_Over, anchor = "center") #Affiche l'image de defaite
        f.remplacerBouton(Bouton_pause, Bouton_choixNiveau)
        f.wipeProjectiles(listeProjectilesEnnemis, listeProjectiles, Canevas_jeu) 
        f.wipeVaisseaux(listeVaisseaux, listeVaisseauxEnnemis, listeRochers, Canevas_jeu)


#Lorsque les conditions de victoires sont remplies, affichage de l'ecran de victoire, jeu en pause
#et possibilite de recommencer
def victoire():
    global jeuEnMarche
    if listeVaisseauxEnnemis == []:
        jeuEnMarche = False #Jeu en pause
        Canevas_jeu.delete('all') #Ecran vide
        victoireScreen = Canevas_jeu.create_image(400, 300, image =victoire_screen, anchor = CENTER)#Affiche l'image de victoire
        f.remplacerBouton(Bouton_pause, Bouton_choixNiveau)
        f.wipeProjectiles(listeProjectilesEnnemis, listeProjectiles, Canevas_jeu) 
        f.wipeVaisseaux(listeVaisseaux, listeVaisseauxEnnemis, listeRochers, Canevas_jeu)

#mise en pause du jeu
def pause():
    global jeuEnMarche
    if jeuEnMarche:
        jeuEnMarche = False #Stop la fonction principale jeuEnFonctionnement()
        f.remplacerBouton(Bouton_pause, Bouton_resume)

#le jeu reprend son cours
def resume():
    global jeuEnMarche
    jeuEnMarche = True
    jeuEnFonctionnement() #relance la fonction principale


def initilisation():
    global listeVaisseauxEnnemis
    global listeRochers
    global vaisseauJoueur
    global listeProjectiles
    global listeProjectilesEnnemis
    listeVaisseaux = []
    listeVaisseauxEnnemis = []
    listeRochers = []
    vaisseauJoueur = vaisseau(1, [0,0], 1)
    listeProjectiles = []
    listeProjectilesEnnemis = []
#Reinitialisation des parametres
    vie_int.set(3)
    score_int.set(0)
#(re)initialise toutes les listes (affichage + existence)
    f.wipeProjectiles(listeProjectilesEnnemis, listeProjectiles, Canevas_jeu) 
    f.wipeVaisseaux(listeVaisseaux, listeVaisseauxEnnemis, listeRochers, Canevas_jeu)
    Canevas_jeu.delete('all')
#Creation des entites du jeu
    listeVaisseauxEnnemis = f.creationVaisseauxEnnemis(80,40,60,largeurCanevas_jeu, Canevas_jeu, listeVaisseauxEnnemis, 4, 70, listeImagesVaisseauxEnnemis)
    listeRochers = f.obstacle(listeRochers, Canevas_jeu, largeur=7)
    vaisseauJoueur = f.creationVaisseauJoueur(listeVaisseaux, largeurCanevas_jeu, hauteurCanevas_jeu, Canevas_jeu,imageVaisseauAllie)
#Remplacement des bouton du menu
    f.remplacerBouton(Bouton_choixNiveau, Bouton_start)



#########################################################################################################

Fenetre = Tk()

#Images
imageVaisseauAllie = PhotoImage(file='VaisseauAllie.gif')
imageMissile = PhotoImage (file = 'missile.gif')

imageVaisseauEnnemi0 = PhotoImage(file='VaisseauEnnemi0.gif')
imageVaisseauEnnemi1 = PhotoImage(file='VaisseauEnnemi1.gif')
imageVaisseauEnnemi2 = PhotoImage(file='VaisseauEnnemi2.gif')
imageVaisseauEnnemi3 = PhotoImage(file='VaisseauEnnemi3.gif')
listeImagesVaisseauxEnnemis = [imageVaisseauEnnemi0, imageVaisseauEnnemi1, imageVaisseauEnnemi2, imageVaisseauEnnemi3]

game_Over = PhotoImage(file='Game_Over.gif')
victoire_screen = PhotoImage(file='VictoireScreen.gif')

#Informations fenetre
Fenetre.title("Space Invaders")
Fenetre["bg"]="grey"
Fenetre.geometry('800x800')



#Haut de la fenetre(score)

Frame_score =  Frame(Fenetre, borderwidth = 4)
Frame_score.grid(row = 0, column = 0)


Label_score = Label(Frame_score, text = "SCORE : ")
Label_score.grid(row=1, column=0)

score_int = IntVar()
score_int.set(0)
Label_score_affiche =  Label(Frame_score, textvariable=score_int)
Label_score_affiche.grid(row=1, column=1)


# Label_identifiant =  Label(Frame_score, text="Identifiant", bg="lightgrey")
# Label_identifiant.grid(row=0, column=2)

# player_co = StringVar()
# Label_connecte = Label(Frame_score, textvariable=player_co, bg="lightgrey")

# Label_mdp =  Label(Frame_score, text="Mot de passe", bg="lightgrey")
# Label_mdp.grid(row=1, column=2)

# Saisie_identifiant =  Entry(Frame_score, width = 30)
# Saisie_identifiant.grid(row=0, column=3)

# Saisie_mdp =  Entry(Frame_score, width = 30, show="*")
# Saisie_mdp.grid(row=1, column=3)

# Bouton_connexion =  Button(Frame_score, text="Connexion", command=connexion)
# Bouton_connexion.grid(row=0, column = 4)

# Bouton_deconnexion =  Button(Frame_score, text="Deconnexion", bd = 0, command=deconnexion)


Label_vie = Label(Frame_score, text = "VIE(S) : ")
Label_vie.grid(row = 1, column = 5)

vie_int = IntVar()
Label_vieNb = Label(Frame_score, textvariable = vie_int)
Label_vieNb.grid(row = 1, column = 6)

###################################


#Ecran de jeu
hauteurCanevas_jeu = 650
largeurCanevas_jeu = 800
Canevas_jeu =  Canvas(Fenetre, width = largeurCanevas_jeu, height = hauteurCanevas_jeu, bg = "black")
Canevas_jeu.focus_set()
Canevas_jeu.bind('<Right>', deplacerVaisseau)
Canevas_jeu.bind('<Left>', deplacerVaisseau)
Canevas_jeu.bind('<space>', tirer)
Canevas_jeu.grid(padx = 5, pady = 5, row = 1, column = 0)




###################################


#Bas de la fenetre (connexion)
Frame_joueur = Frame(Fenetre, borderwidth = 4, bg="lightgrey")
Frame_joueur.grid(row=2, column=0, columnspan=7)

#Les boutons utiles
Bouton_recommencer = Button(Frame_joueur, text="Recommencer", command=restart)

Bouton_choixNiveau = Button(Frame_joueur, text="Choisir un niveau", command=initilisation)
Bouton_choixNiveau.grid(row=0, column=1)

Bouton_start = Button(Frame_joueur, text="Commencer", command=start)

Bouton_pause = Button(Frame_joueur, text="Pause", command=pause)

Bouton_resume = Button(Frame_joueur, text="Reprendre", command=resume)

Bouton_quitter =  Button(Frame_joueur, text="Quitter", command=Fenetre.destroy)
Bouton_quitter.grid(row=0, column = 2, padx=100, pady=20)

###################################


#Pas utilise
# Barre de menu 
menubar = Menu(Fenetre)
menufichier = Menu(menubar,tearoff = 0)
menufichier.add_command(label = "Quitter", command = Fenetre.destroy)

menubar.add_cascade(label="Menu", menu = menufichier)

menuaide = Menu(menubar,tearoff = 0)
menuaide.add_command(label = "A propos" , command = Fenetre.destroy)
menuaide.add_command(label = "Cheat", command = Fenetre.destroy)

menubar.add_cascade(label="Aide", menu = menuaide)

Fenetre.config(menu = menubar)
###################################

Fenetre.mainloop()
###################################




