#LERICHE FENG 19/12/2019
#Space invaders sur tkinter
#Fonctions utiles


import random as rd


#class utiles

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

################################################################################
#Creation des entites

#Prend le position, taille et info de "structure" ainsi qu'ub liste
#Renvoi un liste remplie d'objets vaisseau, qui sont les vaisseaux ennemis. Affiche ces vaisseaux
def creationVaisseauxEnnemis(x,y,espace,largeurCanevas_jeu, Canevas_jeu, listeVaisseauxEnnemis, nbLignes, espaceCote, listeImages):
    taille = 20 #En brut pour l'instantn prendre car l'image est redimensionnee en brut
    listeVaisseauxEnnemis = [] #on vide la liste
    for i in range(nbLignes): #Pour chaque lignes
        ligneEnnemis = [] #une liste de vaisseaux vides
        x=espaceCote #Espacement de la bordure
        while x < largeurCanevas_jeu - espace: #Tant qu'on ne creer pas de vaisseau en dehors du cadre
            alea = rd.random() #Couleur aleatoire
            if alea > 0.9: score = 150 ; couleur = 3
            elif alea > 0.7 : score = 100 ; couleur = 2
            elif alea > 0.5 : score = 75 ; couleur = 1
            else : score = 50 ; couleur = 0
            enemy = Canevas_jeu.create_image(x,y, image = listeImages[couleur], anchor = "center") #Affichage du vaisseau ennemi
            vEnemy = vaisseau(1, [x,y], taille, enemy, score, "d") #Creation de l'entite
            ligneEnnemis.append(vEnemy) #Ajout du vaisseau a la ligne de vaisseau ennemis
            x += espace
        listeVaisseauxEnnemis.append(ligneEnnemis) #Ajout de la ligne de vaisseau a la liste des lignes de vaisseaux ennemis
        i += 1 #ligne suivante
        y += espace #position de la ligne suivante
    return listeVaisseauxEnnemis


#Prend une liste et la taille des rochers
#Renvoi la liste remplie des informations relatives aux rochers
def obstacle(listeRochers, Canevas_jeu, largeur):
    listeRochers=[] 
    listeCoord = [[120,430,1], [640, 380,0],[440, 450,1]] #les coordonnees des rochers a afficher, en brut pour l'instant
    for i in listeCoord: 
        x = i[0]
        y = i[1]
        typeRocher = i[2]
        #la structure de chaque type de rocher, en brut pour l'instant. O = vide, 1 = rocher
        liste = [[[0,0,0,1,1,0,0],[0,1,1,1,1,1,0],[1,1,1,1,1,1,1],[0,1,1,1,1,1,1],[0,0,1,1,1,1,0],[0,0,0,1,0,0,0]],\
            [[0,1,0,1,0,0,0],[1,1,1,1,1,0,0],[1,1,1,1,1,1,0],[0,1,1,1,1,1,1],[0,0,1,1,0,0,0],[0,0,0,1,1,0,1]]] 
        for i in range(len(liste[1])):
            for j in range(len(liste[1][0])):
                if liste[typeRocher][i][j] == 1: #Affichage d'un carre que s'il doit y en avoir un
                    X = x+j*2*largeur
                    Y = y+i*2*largeur
                    box = Canevas_jeu.create_rectangle([(X-largeur,Y-largeur), (X+largeur, Y+largeur)], fill="lightgrey") #Affichage du rocher
                    rocher = vaisseau(2, [X,Y], largeur, box, vie = 1) #Creation de l'entite
                    listeRochers.append(rocher) #Ajout du rocher a la liste des rochers
    return listeRochers


#Prend une liste vide ou non des tirs ennemis sur l'ecran et la liste des vaisseaux ennemis en vie
#Renvoi une liste remplie des tirs ennemis present a l'ecran, tirs generes aleatoirement
def tirEnnemi(jeuEnMarche, listeVaisseauxEnnemis, listeProjectilesEnnemis, Canevas_jeu, conditionAleatoire, nbTirMax):
    for i in listeVaisseauxEnnemis: #Pour chaque ligne de vaisseaux ennemis
        for k in i: #Pour chaque vaisseau ennemi
            if len(listeProjectilesEnnemis) < nbTirMax: #condition pour ne pas avoir trop de tirs a l'ecran
                alea = rd.random()
                if alea < conditionAleatoire: #Condition pour ne pas tirer systematiquemet
                    x = k.position[0]
                    y = k.position[1]
                    newproj = projectile(0, [x,y-k.taille], k.taille//10) #creation de l'entite
                    #Affichage du projectile
                    newproj.hitbox = Canevas_jeu.create_rectangle([(newproj.position[0]-newproj.taille, newproj.position[1]-newproj.taille),\
                        (newproj.position[0]+newproj.taille, newproj.position[1]+newproj.taille)], fill="pink")
                    listeProjectilesEnnemis.append(newproj) #Ajout du projectile a la liste des projectiles ennemis
    return listeProjectilesEnnemis



#Prend la liste des vaisseaux allies, les dimensions de l'ecran
#Renvoi la la liste avec le vaisseau ajoute dedans
def creationVaisseauJoueur(listeVaisseaux, largeurCanevas_jeu, hauteurCanevas_jeu, Canevas_jeu, imageVaisseauAllie):
    vaisseauJoueur = vaisseau(0, [largeurCanevas_jeu//2, hauteurCanevas_jeu - 1.5*30], 30) #Creation de l'entite
    #Affichage du vaisseau
    x = vaisseauJoueur.position[0]
    y = vaisseauJoueur.position[1]
    vaisseauJoueur.hitbox = Canevas_jeu.create_image(x,y, image = imageVaisseauAllie, anchor = "center")
    listeVaisseaux.append(vaisseauJoueur) #Ajout du vaisseau
    return vaisseauJoueur

################################################################################
#Deplacements

#Prend la liste des projectiles allies
#Ne renvoi rien, la liste est mise a jour dans la fonction 
def deplacementProjectile(jeuEnMarche, listeProjectiles, Canevas_jeu, deplacement):
    for i in listeProjectiles: #Pour tous les projectiles a l'ecran
        Canevas_jeu.move(i.hitbox, 0, -deplacement) #on deplace le projectile (visuel)
        i.position[1] -= deplacement #On actualise son information de position
        if i.position[1] < -i.taille+20: #Si en dehors du la fenetre : on le retire
            Canevas_jeu.delete(i.hitbox)

#Prend la liste des vaisseaux ennemis 
#Ne renvoi rien, la liste est mise a jour dans la fonction 
def deplacerVaisseauEnnemis(listeVaisseauxEnnemis, Canevas_jeu, deplacement, abaissement,largeurCanevas_jeu):
    l1 = [] #des listes utiles
    l2 = []
    l3 = []
    for i in listeVaisseauxEnnemis: #On parcourt les lignes de vaisseaux ennemis
        if len(i)!=0: #s'il reste des vaisseaux sur cette ligne
            vaisseauFin = i[-1] #le vaisseau le plus a droite
            x = vaisseauFin.position[0]
            y = vaisseauFin.position[1]
            vaisseauDebut = i[0] #le vaisseau le plus a gauche
            xdeb = vaisseauDebut.position[0]
            #On conserve l'abscisse des vaisseaux dans des listes distinctes
            l1.append(x) 
            l2.append(xdeb)
    x = max(l1) #On prend l'abscisse du vaisseau le plus a droite, toutes lignes confondues
    xdeb = min(l2) #Idem a gauche
    #Permet de recuperer l'ordonnee de tous les vaisseaux ennemis
    for i in listeVaisseauxEnnemis:
        for j in i:
            l3.append(j.position[1])
    y = max(l3) #ordonnees du vaisseau le plus bas de l'ecran
    for i in listeVaisseauxEnnemis:
        for j in i:
            if j.direction == "d" : #Si le vaisseau doit aller a droite
                if x < largeurCanevas_jeu -  5 - vaisseauFin.taille : #S'il ne va pas sortir de l'ecran
                    j.position[0] = j.position[0] + deplacement #Deplacementde l'information de position
                    Canevas_jeu.move(j.hitbox, deplacement, 0) #Deplacement visuel
                else : #Si le vaisseau ne peut plus aller a droite, il doit descendre et aller vers la gauche
                    if y < 350: #Si pas trop bas on descend
                        j.position[1] = j.position[1] + abaissement #Deplacementde l'information de position
                        Canevas_jeu.move(j.hitbox, 0, abaissement)  #Deplacement visuel
                    j.direction = "g" #Changment de l'information de direction, le vaisseau va maintenant aller a gauche
            elif j.direction == "g":
                if xdeb > 5 + vaisseauDebut.taille:
                    j.position[0] = j.position[0] - deplacement
                    Canevas_jeu.move(j.hitbox, -deplacement, 0)
                else :
                    if y < 350: #Si pas trop bas on descend
                        j.position[1] = j.position[1] + abaissement
                        Canevas_jeu.move(j.hitbox, 0, abaissement)
                    j.direction = "d"


#Prend la liste des projectiles ennemis et les deplace
#Ne renvoi rien ,les changements sont fait dans la fonction
def deplacementProjectileEnnemis(jeuEnMarche, listeProjectilesEnnemis, Canevas_jeu, deplacement, hauteurCanevas_jeu, vie_int, vaisseauJoueur ):
    for i in listeProjectilesEnnemis: 
        Canevas_jeu.move(i.hitbox, 0, deplacement) #on deplace le projectile (visuel)
        i.position[1] += deplacement #On met a jour sa position (information)
        if i.position[1] > hauteurCanevas_jeu-i.taille-20: #Si en dehors du la fenetre : on le retire
            Canevas_jeu.delete(i.hitbox) #Retrait visuel
            listeProjectilesEnnemis.remove(i) #Retrait de l'entite
        elif collision(i, vaisseauJoueur) == True: #Si collision avec le vaisseau allie, il disparait et on perd une vie
            vie = vie_int.get()
            vie_int.set(vie-1)
            Canevas_jeu.delete(i.hitbox)
            listeProjectilesEnnemis.remove(i)


################################################################################
#Collisions

#Prend deux elements de la classe vaisseau
#Renvoi True si les elements se superposent, False sinon
def collision(i,j):
    larg = j.taille
    l = i.taille
    if i.position[0] - l < j.position[0]+larg and i.position[0] - l > j.position[0]-larg and\
         i.position[1] - l < j.position[1]+larg and i.position[1] - l > j.position[1]-larg:
        return True
    elif i.position[0] - l < j.position[0]+larg and i.position[0] - l > j.position[0]-larg and\
         i.position[1] + l < j.position[1]+larg and i.position[1] + l > j.position[1]-larg:
        return True
    elif i.position[0] + l < j.position[0]+larg and i.position[0] + l > j.position[0]-larg and\
         i.position[1] + l < j.position[1]+larg and i.position[1] + l > j.position[1]-larg:
        return True
    elif i.position[0] + l < j.position[0]+larg and i.position[0] + l > j.position[0]-larg and\
         i.position[1] - l < j.position[1]+larg and i.position[1] - l > j.position[1]-larg:
        return True


#Prend les listes des rochers et des projectiles (ennemis et allies)
#Ne renvoi rien, met a jour la liste dans la fonction s'il y a collision
def collisionRocher(listeProjectilesEnnemis, listeRochers, listeProjectiles, Canevas_jeu):
    for i in listeProjectilesEnnemis:
        for j in listeRochers:
            if collision(i,j) == True:
                j.vie = j.vie - 1 
                Canevas_jeu.delete(i.hitbox)
                listeProjectilesEnnemis.remove(i)
                if j.vie <= 0: #Si plus de vie pour le rocher on le detruit
                    Canevas_jeu.delete(j.hitbox)
                    listeRochers.remove(j)
    for i in listeProjectiles:
        for j in listeRochers:
            if collision(i,j) == True: #Si collision avec le tir allie, on retire le projectile seulement
                Canevas_jeu.delete(i.hitbox)
                listeProjectiles.remove(i)

#Prend la liste des projectiles allies et la liste des vaisseaux ennemis
#Ne renvoi rien, listes mises a jour dans le fonction
def destructionEnnemis(listeProjectiles, listeVaisseauxEnnemis, Canevas_jeu, score_int):
    for i in listeProjectiles:
        for k in listeVaisseauxEnnemis:
            if len(k) != 0: #On s'assure de ne pas parcourir une ligne d'ennemi vide
                for j in k:
                    if collision(i,j) == True:
                        Canevas_jeu.delete(j.hitbox)
                        Canevas_jeu.delete(i.hitbox)
                        k.remove(j)
                        listeProjectiles.remove(i)
                        score = score_int.get()
                        score_int.set(score+j.score)  #Ajoute du score en fonction de l'ennemi tue
            else :
                listeVaisseauxEnnemis.remove(k)


################################################################################
#Pour plus tard


def connexion(listeJoueurs, Saisie_mdp, Saisie_identifiant, Frame_score):
    for i in listeJoueurs:
        if Saisie_identifiant == i.id and Saisie_mdp == i.motDePasse:
            Frame_score.delete('all')
            Label_score_affiche.grid(row=1, column=1)
            Label_vie.grid(row = 1, column = 5)
            Label_vieNb.grid(row = 1, column = 6)
            Bouton_deconnexion.grid(row=1, column = 4)
            Label_connecte.grid(row=0, column=2)

def deconnexion(Frame_score): 
    Frame_score.delete('all')
    Frame_score.grid(row = 0, column = 0)
    Label_score.grid(row=1, column=0)
    Label_score_affiche.grid(row=1, column=1)
    Label_identifiant.grid(row=0, column=2)
    Label_mdp.grid(row=1, column=2)
    Saisie_identifiant.grid(row=0, column=3)
    Saisie_mdp.grid(row=1, column=3)
    Bouton_connexion.grid(row=0, column = 4)
    Label_vie.grid(row = 1, column = 5)
    Label_vieNb.grid(row = 1, column = 6)


################################################################################

#Fonctions pratiques pour simplifier

def remplacerBouton(bouton1, bouton2):
    dico = bouton1.grid_info()
    c = dico['column']
    r = dico['row']
    bouton1.grid_forget()
    bouton2.grid(row=r, column = c)

################################################################################

#Fonctions de reinitialisation

#Prend les listes a vider (suppression de l'entite et de l'affichage)
#Ne renvoi rien
def wipeVaisseaux(listeVaisseaux, listeVaisseauxEnnemis, listeRochers, Canevas_jeu): #On peut tout regrouper mais il faut bien que les elements soit des objets de la calsse vaisseau
    for i in listeVaisseaux:
        Canevas_jeu.delete(i.hitbox)
        listeVaisseaux.remove(i)
    for j in listeVaisseauxEnnemis:
        Canevas_jeu.delete(j.hitbox)
        listeVaisseauxEnnemis.remove(j)
    for k in listeRochers:
        Canevas_jeu.delete(k.hitbox)
        listeRochers.remove(k)

#Prend les listes a vider (suppression de l'entite et de l'affichage)
#Ne renvoi rien
def wipeProjectiles(listeProjectilesEnnemis, listeProjectiles, Canevas_jeu):
    for i in listeProjectilesEnnemis:
        Canevas_jeu.delete(i.hitbox)
        listeProjectilesEnnemis.remove(i)
    for j in listeProjectiles:
        Canevas_jeu.delete(j.hitbox)
        listeProjectiles.remove(j)

