____________________________________________COMPILATION_ET_EXECUTION______________________________________________________________


---> 	Dans un répertoire en amont de celui contenant le fichier main.cpp, tapez en ligne de commande
		qmake -project
	Observer la création d’un fichier du type [nom_repertoire].pro.

---> 	Rajouter à la fin du fichier .pro les composants Qt nécéssaires (indiqués QT += ... dans la doc), ici  	QT += widgets


---> 	Tapez ensuite en ligne de commande
		qmake
	Cette commande permet de générer un Makefile à partir du fichier de configuration .pro. 



---> 	De manière traditionnelle, la compilation puis l’exécution se réalisent à l’aide des commandes suivantes:
		make
		./[nom_repertoire]

--->  	Après compilation 'make', on observe les warning suivants (ces warnings n'affectent pas l'exécution de notre programme):

In file included from window.hpp:15,
                 from window.cpp:1:
grille.hpp: In instantiation of ‘void Grille<T>::mousePressEvent(QGraphicsSceneMouseEvent*) [with T = MonRectItem]’:
grille.hpp:247:10:   required from here
grille.hpp:247:52: warning: unused parameter ‘event’ [-Wunused-parameter]
  247 |     void mousePressEvent(QGraphicsSceneMouseEvent *event)
      |                          ~~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~
In file included from window.hpp:15,
                 from window.cpp:1:
grille.hpp: In instantiation of ‘void Grille<T>::mouseMoveEvent(QGraphicsSceneMouseEvent*) [with T = MonRectItem]’:
grille.hpp:313:10:   required from here
grille.hpp:313:51: warning: unused parameter ‘event’ [-Wunused-parameter]
  313 |     void mouseMoveEvent(QGraphicsSceneMouseEvent *event)
      |                         ~~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~
	



____________________________________________FONCTIONNEMENT_DE_L_INTERFACE_________________________________________________________


--->	Lancement
Lors du lancement sur Qt Creator, il y a l'affichage d'une fenêtre avec en première partie la grille et en deuxième partie les boutons et affichage des temps d'éxécution.


--->	Point départ/d'arrivé et obstacles
Cliquer sur une case de la grille pour faire apparaître la case de départ (en vert).
Cliquer sur une autre case de la grille pour faire apparaître la case d'arrivée (en rouge).
Cliquer et faire bouger la souris sur la grille pour dessiner les obstaccles (en blanc), recliquer pour arrêter de dessiner des obstacles. (!!! ATTENTION !!! ne pas faire sortir la souris de la grille lors du dessin)

--->	Boutons / Affichage
Tout à gauche, il y a 4 boutons pour exécuter les algorithmes de parcours :
	Path Width(4) 	: Algorithme de parcours en largeur en regardant seulement les 4 voisins à proximité
	Path Deep 	: Algorithme de parcours en profondeur 
	Dijkstra	: Algorithme de Dijkstra
	Path Width(8)	: Algorithme de parcours en largeur en regardant les 8 voisins à proximité

Au milieu se trouve l'affichage pour les temps d'exécution des 4 algorithmes

Tout à droite, il y a 3 boutons :
	Quit		: Bouton pour quitter la fenêtre
	Reset/Restart	: Bouton pour effacer les points de départ et d'arrivé avec les obstacles 
	Erase		: Bouton pour effacer seulement le chemin pour trouver relier les deux points après exécution d'un 			  algorithme. Garde les points de départ et d'arrivée avec les obstacles. Permet notamment de comparer les 			  temps d'exécution pour les différents algorithmes.
