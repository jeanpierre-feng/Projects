    #include "window.hpp"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDebug>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QBrush>
#include <QTimer>
#include "vec2.hpp"

#include "grille.hpp"
#include "monrecitem.h"

window::window(QWidget *parent)
    :QMainWindow(parent),ui(new Ui::MainWindow),view(new QGraphicsView),m_grid(new Grille<MonRectItem>),item(new MonRectItem),elapsed_timer()

{
    //setup the graphical interface to the current widget
    ui->setupUi(this);


    //Attach the render_area window to the widget
    view -> setScene(m_grid);
    view -> setAlignment(Qt::AlignLeft | Qt::AlignTop);
    view -> centerOn(0,0);
    view -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view -> setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->setMouseTracking(true);
    ui -> layout_scene -> addWidget(view);





    //connect signals
    connect(ui -> QuitButton,SIGNAL(clicked()),this,SLOT(action_quit()));
    connect(ui -> ResetButton,SIGNAL(clicked()),this,SLOT(action_reset()));
    connect(ui -> PathWidthButton,SIGNAL(clicked()),this,SLOT(action_path_width()));
    connect(ui -> PathDeepButton,SIGNAL(clicked()),this,SLOT(action_path_deep()));
    connect(ui -> DijkstraButton,SIGNAL(clicked()),this,SLOT(action_dijkstra()));
    connect(ui -> AStarButton,SIGNAL(clicked()),this,SLOT(action_a_star()));
    connect(ui -> EraseButton,SIGNAL(clicked()),this,SLOT(action_erase()));



}


window::~window()
{

}

void window::action_quit()
{
    close();
}

void window::action_reset()
{
    m_grid -> reset();
    ui->PathWidthTimer->setText("****");
    ui->PathDeepTimer->setText("****");
    ui->DijkstraTimer->setText("****");
    ui->AStarTimer->setText("****");
}

void window::action_path_deep() // Pas l'option lorsque le point n'a pas de chemin/bloqué
{
    // Coordonnées
    int x_start_point = m_grid -> Get_start_end().at(0)-> x;//Récupère la coordonée x point d'arrivé
    int y_start_point = m_grid -> Get_start_end().at(0)-> y;//Récupère la coordonée y point d'arrivé
    int x_end_point = m_grid -> Get_start_end().at(1)-> x;//Récupère la coordonée x point d'arrivé
    int y_end_point = m_grid -> Get_start_end().at(1)-> y;//Récupère la coordonée y point d'arrivé
    int start = (x_start_point + y_start_point * 144)/5;
    int end = (x_end_point + y_end_point * 144)/5;

    if(m_grid->Get_start_end().size() != 2)
    {
        QMessageBox::critical(this," Attention ", " Please put a starting point and an ending point ");


    }
    else
    {
        elapsed_timer.restart();
        if(end > start)
        {
            for(int s = start; s < m_grid->Get_data().size(); s++)
            {
                if (m_grid->Get_end() == true)
                {
                    break;
                }

                //Vérifie si la case n'est pas marqué
                else if(m_grid->Get_data().at(s)->Get_marker_path_width() == false)
                {
                    explore(m_grid->Get_data().at(s));

                }
            }
        }

        else
        {
            qDebug()<<"TOP";

            for(int s = start -1; s > 0; s--)
            {
                if (m_grid->Get_end() == true)
                {
                    break;
                }

                //Vérifie si la case n'est pas marqué
                else if(m_grid->Get_data().at(s)->Get_marker_path_width() == false)
                {
                    explore(m_grid->Get_data().at(s));

                }
            }
        }
    }
}



void window::action_path_width()
{
    QTimer timer;

    // Tableaux
    QList<MonRectItem*> exploited;
    QList<vec2*> quatre_voisins;// juste pour les coordonnées

    //Vérifie si on a les deux points (départ/arrivé)
    if(m_grid->Get_start_end().size() != 2)
    {
        exploited.clear();
        quatre_voisins.clear();
        QMessageBox::critical(this," Attention ", " Please put a starting point and an ending point ");
    }
    else
    {
        // Coordonnées
        int x_start_point = m_grid -> Get_start_end().at(0)-> x;//Récupère la coordonée x point de départ
        int y_start_point = m_grid -> Get_start_end().at(0)-> y;//Récupère la coordonée y point de départ
        int x_end_point = m_grid -> Get_start_end().at(1)-> x;//Récupère la coordonée x point d'arrivé
        int y_end_point = m_grid -> Get_start_end().at(1)-> y;//Récupère la coordonée y point d'arrivé
        int x_pointer = x_start_point; // coordonnée x du point de parcours
        int y_pointer = y_start_point; // coordonnée y du point de parcours

        //Initialisation Exploited contient la case départ
        exploited.append(m_grid -> Get_data().at((x_start_point+y_start_point*144)/5));// ajoute notre point de départ à notre liste d'exploitation des cases

        // Si notre point de départ == (déja) notre point d'arrivé
        if(x_pointer == x_end_point && y_pointer == y_end_point)
        {
            exploited.clear();
            quatre_voisins.clear();
            QMessageBox::about(this," Trouvé ", " Chemin le plus court");

        }

        else
        {
            // Marque le point de départ pour indiquer qu'on l'a traité
            m_grid->Get_data().at((x_start_point+y_start_point*144)/5)->Set_marker_path_width(true);

            int x_voisin1 ;
            int y_voisin1 ;
            int x_voisin2 ;
            int y_voisin2 ;
            int x_voisin3 ;
            int y_voisin3 ;
            int x_voisin4 ;
            int y_voisin4 ;
            vec2* voisin1 = new vec2();
            vec2* voisin2 = new vec2();
            vec2* voisin3 = new vec2();
            vec2* voisin4 = new vec2();

//BOUCLE
            //Démarrage du timer
            elapsed_timer.restart();

            while(exploited.size() != 0)
            {
                //Coordonnées des 4 voisins de notre noeud source/pointeur

                x_voisin1 = (x_pointer +5);
                y_voisin1 = y_pointer;
                x_voisin2 = (x_pointer -5);
                y_voisin2 = y_pointer;
                x_voisin3 = x_pointer;
                y_voisin3 = (y_pointer + 5);
                x_voisin4 = x_pointer;
                y_voisin4 = (y_pointer - 5);

                //Ajoute les vecteurs coordonnées des 4 voisins dans une liste
                voisin1->Set_x_coord(x_voisin1);
                voisin1->Set_y_coord(y_voisin1);
                voisin2->Set_x_coord(x_voisin2);
                voisin2->Set_y_coord(y_voisin2);
                voisin3->Set_x_coord(x_voisin3);
                voisin3->Set_y_coord(y_voisin3);
                voisin4->Set_x_coord(x_voisin4);
                voisin4->Set_y_coord(y_voisin4);

                quatre_voisins.append(voisin1);
                quatre_voisins.append(voisin2);
                quatre_voisins.append(voisin3);
                quatre_voisins.append(voisin4);

                //Vérifie si il dépasse notre cadre
                for (int j =0; j<4; j++)
                {
                    if(quatre_voisins.at(j)->x <0 || quatre_voisins.at(j)->x >715 || quatre_voisins.at(j)->y >345 ||quatre_voisins.at(j)->y <0  )
                    {
                        quatre_voisins.at(j)->x = x_start_point;
                        quatre_voisins.at(j)->y = y_start_point;

                    }
                }

                //Vérifie si le voisin est la case d'arrivé
                if((x_voisin1 == x_end_point && y_voisin1 == y_end_point) || (x_voisin2 == x_end_point && y_voisin2 == y_end_point) || (x_voisin3 == x_end_point && y_voisin3 == y_end_point) || (x_voisin4 == x_end_point && y_voisin4 == y_end_point))
                {

                    exploited.clear();
                    quatre_voisins.clear();

                    QMessageBox::about(this," Trouvé ", " Chemin le plus court");

                    //Afficahge du temps pour effectuer l'algo parcours en largeur
                    QString t = QString::number(elapsed_timer.elapsed()) ;
                    ui->PathWidthTimer->setText(t + " " + "ms");//Affiche le temps

                }


                else
                {


                    for (int i = 0; i < 4; i++)
                    {
                        //Vérifie si il a été marqué
                        if (m_grid->Get_data().at((quatre_voisins.at(i)->x +(quatre_voisins.at(i)->y *144))/5)->Get_marker_path_width() == false)
                        {
                            exploited.append(m_grid -> Get_data().at((quatre_voisins.at(i)->x + (quatre_voisins.at(i)->y*144))/5));
                            //Marque le voisin
                            m_grid->Get_data().at((quatre_voisins.at(i)->x + (quatre_voisins.at(i)->y*144))/5)->Set_marker_path_width(true);
                            /*
                            connect(&timer, SIGNAL(timeout()), this, SLOT(Affichage_path_width()));
                            timer.start(500); //every 30ms
                            */

                            //Affichage des voisins en jaune
                            m_grid->Get_data().at((quatre_voisins.at(i)->x + (quatre_voisins.at(i)->y*144))/5)->setBrush(QBrush(Qt::yellow));
                        }
                    }

                    exploited.pop_front();//Supprime la première

                    // Bloqué de partout
                    if(exploited.size() == 0)
                    {
                        QMessageBox::critical(this," Attention ", " Starting point cannot find a path (blocked by obstacles)");
                        break;
                    }

                    quatre_voisins.clear();

                    //Change notre pointeur en prenant le premier élément de notre liste exploited
                    x_pointer = exploited.at(0) -> x();
                    y_pointer = exploited.at(0) -> y();
                    m_grid->Get_data().at((x_pointer + (y_pointer*144))/5)->setBrush(QBrush(Qt::yellow));
                }
            }
        }
    }
}


void window::action_dijkstra()
{
    //Coordonées
    int x_start_point = m_grid -> Get_start_end().at(0)-> x;//Récupère la coordonée x point de départ
    int y_start_point = m_grid -> Get_start_end().at(0)-> y;//Récupère la coordonée y point de départ
    int x_end_point = m_grid -> Get_start_end().at(1)-> x;//Récupère la coordonée x point d'arrivé
    int y_end_point = m_grid -> Get_start_end().at(1)-> y;//Récupère la coordonée y point d'arrivé

    //Variables
    MonRectItem* s1;
    QList<MonRectItem*> Stop_list;
    QList<MonRectItem*> Chemin_court;
    MonRectItem* s = m_grid->Get_data().at((x_end_point + y_end_point *144)/5);
    QList<int> pos_voisin = {-1,1,-144,144,145,-145,143,-143};

    //Initialisation de P avec le point de départ
    m_grid->Set_P(m_grid->Get_data().at((x_start_point + y_start_point *144)/5),m_grid->Get_data().at((x_start_point + y_start_point *144)/5));

    //Vérifie si il y a bien les deux points (départ et arrivés)
    if(m_grid->Get_start_end().size() != 2)
    {
        QMessageBox::critical(this," Attention ", " Please put a starting point and an ending point ");
    }
    else
    {
        //Démarrage du timer
        elapsed_timer.restart();

        initialisation_Dijkstra();
        //Construit Q : l'ensemble de tous les noeuds
        for(int s=0; s<m_grid->Get_data().size();s++)
        {
            m_grid->Set_Q(m_grid->Get_data().at(s));
            Stop_list.append(m_grid->Get_data().at(s));
        }



        //Algo de Dijkstra on obtient P et Q
        while(Stop_list.size() != 0)
        {
            s1 = Min_Dijkstra();
            //qDebug()<<"-----Mini---";
            //qDebug()<<s1;

            m_grid->Get_Q().at((s1->x() + s1->y()*144)/5) ->Set_prive(true); //Q privé de s1
            Stop_list.pop_front();
            for(int j=0; j<8; j++)
            {
                //Vérifie si les voisins sont dans le cadre
                if((pos_voisin.at(j) + s1->x() >0 && pos_voisin.at(j) + s1->x() < 715) && (pos_voisin.at(j) + s1->y() >0 && pos_voisin.at(j) + s1->y() < 345))
                {
                    Maj_distance_Dijkstra(s1, m_grid->Get_Q().at((pos_voisin.at(j) + s1->x() + pos_voisin.at(j) + s1->y() *144)/5));
                }

            }
        }

        //qDebug()<<"----Sort/list P----";
        //qDebug()<<m_grid->Get_P();




        while(s != m_grid->Get_data().at((x_start_point + y_start_point *144)/5))
        {
            Chemin_court.push_front(s);
            m_grid->Get_data().at((s->x() + (s->y()*144))/5)->setBrush(QBrush(Qt::yellow));
            s = m_grid->Get_P()[s];

        }
        m_grid->Get_data().at((x_end_point + (y_end_point*144))/5)->setBrush(QBrush(Qt::red));
        //qDebug()<<Chemin_court;

        //Afficahge du temps pour effectuer l'algo parcours en largeur
        QString t = QString::number(elapsed_timer.elapsed()) ;
        ui->DijkstraTimer->setText(t + " " + "ms");//Affiche le temps



    }
}

void window::action_a_star()
{
    QTimer timer;

    // Tableaux
    QList<MonRectItem*> exploited;
    QList<vec2*> quatre_voisins;// juste pour les coordonnées

    //Vérifie si on a les deux points (départ/arrivé)
    if(m_grid->Get_start_end().size() != 2)
    {
        exploited.clear();
        quatre_voisins.clear();
        QMessageBox::critical(this," Attention ", " Please put a starting point and an ending point ");
    }
    else
    {
        // Coordonnées
        int x_start_point = m_grid -> Get_start_end().at(0)-> x;//Récupère la coordonée x point de départ
        int y_start_point = m_grid -> Get_start_end().at(0)-> y;//Récupère la coordonée y point de départ
        int x_end_point = m_grid -> Get_start_end().at(1)-> x;//Récupère la coordonée x point d'arrivé
        int y_end_point = m_grid -> Get_start_end().at(1)-> y;//Récupère la coordonée y point d'arrivé
        int x_pointer = x_start_point; // coordonnée x du point de parcours
        int y_pointer = y_start_point; // coordonnée y du point de parcours

        //Initialisation Exploited contient la case départ
        exploited.append(m_grid -> Get_data().at((x_start_point+y_start_point*144)/5));// ajoute notre point de départ à notre liste d'exploitation des cases

        // Si notre point de départ == (déja) notre point d'arrivé
        if(x_pointer == x_end_point && y_pointer == y_end_point)
        {
            exploited.clear();
            quatre_voisins.clear();
            QMessageBox::about(this," Trouvé ", " Chemin le plus court");

        }

        else
        {
            // Marque le point de départ pour indiquer qu'on l'a traité
            m_grid->Get_data().at((x_start_point+y_start_point*144)/5)->Set_marker_path_width(true);

            int x_voisin1 ;
            int y_voisin1 ;
            int x_voisin2 ;
            int y_voisin2 ;
            int x_voisin3 ;
            int y_voisin3 ;
            int x_voisin4 ;
            int y_voisin4 ;
            int x_voisin5 ;
            int y_voisin5 ;
            int x_voisin6 ;
            int y_voisin6 ;
            int x_voisin7 ;
            int y_voisin7 ;
            int x_voisin8 ;
            int y_voisin8 ;
            vec2* voisin1 = new vec2();
            vec2* voisin2 = new vec2();
            vec2* voisin3 = new vec2();
            vec2* voisin4 = new vec2();
            vec2* voisin5 = new vec2();
            vec2* voisin6 = new vec2();
            vec2* voisin7 = new vec2();
            vec2* voisin8 = new vec2();


//BOUCLE
            //Démarrage du timer
            elapsed_timer.restart();

            while(exploited.size() != 0)
            {
                //Coordonnées des 4 voisins de notre noeud source/pointeur

                x_voisin1 = (x_pointer +5);
                y_voisin1 = y_pointer;
                x_voisin2 = (x_pointer -5);
                y_voisin2 = y_pointer;
                x_voisin3 = x_pointer;
                y_voisin3 = (y_pointer + 5);
                x_voisin4 = x_pointer;
                y_voisin4 = (y_pointer - 5);
                x_voisin5 = x_pointer + 5;
                y_voisin5 = y_pointer - 5;
                x_voisin6 = x_pointer - 5;
                y_voisin6 = y_pointer - 5;
                x_voisin7 = x_pointer - 5;
                y_voisin7 = y_pointer + 5;
                x_voisin8 = x_pointer + 5;
                y_voisin8 = y_pointer + 5;

                //Ajoute les vecteurs coordonnées des 4 voisins dans une liste
                voisin1->Set_x_coord(x_voisin1);
                voisin1->Set_y_coord(y_voisin1);
                voisin2->Set_x_coord(x_voisin2);
                voisin2->Set_y_coord(y_voisin2);
                voisin3->Set_x_coord(x_voisin3);
                voisin3->Set_y_coord(y_voisin3);
                voisin4->Set_x_coord(x_voisin4);
                voisin4->Set_y_coord(y_voisin4);
                voisin5->Set_x_coord(x_voisin5);
                voisin5->Set_y_coord(y_voisin5);
                voisin6->Set_x_coord(x_voisin6);
                voisin6->Set_y_coord(y_voisin6);
                voisin7->Set_x_coord(x_voisin7);
                voisin7->Set_y_coord(y_voisin7);
                voisin8->Set_x_coord(x_voisin8);
                voisin8->Set_y_coord(y_voisin8);

                quatre_voisins.append(voisin1);
                quatre_voisins.append(voisin5);
                quatre_voisins.append(voisin4);
                quatre_voisins.append(voisin6);
                quatre_voisins.append(voisin2);
                quatre_voisins.append(voisin7);
                quatre_voisins.append(voisin3);
                quatre_voisins.append(voisin8);


                //Vérifie si il dépasse notre cadre
                for (int j =0; j<8; j++)
                {
                    if(quatre_voisins.at(j)->x <0 || quatre_voisins.at(j)->x >715 || quatre_voisins.at(j)->y >345 ||quatre_voisins.at(j)->y <0  )
                    {
                        quatre_voisins.at(j)->x = x_start_point;
                        quatre_voisins.at(j)->y = y_start_point;

                    }
                }

                //Vérifie si le voisin est la case d'arrivé
                if((x_voisin1 == x_end_point && y_voisin1 == y_end_point) || (x_voisin2 == x_end_point && y_voisin2 == y_end_point) || (x_voisin3 == x_end_point && y_voisin3 == y_end_point) || (x_voisin4 == x_end_point && y_voisin4 == y_end_point) || (x_voisin5 == x_end_point && y_voisin5 == y_end_point) || (x_voisin6 == x_end_point && y_voisin6 == y_end_point) || (x_voisin7 == x_end_point && y_voisin7 == y_end_point) || (x_voisin8 == x_end_point && y_voisin8 == y_end_point))
                {

                    exploited.clear();
                    quatre_voisins.clear();

                    QMessageBox::about(this," Trouvé ", " Chemin le plus court");

                    //Afficahge du temps pour effectuer l'algo parcours en largeur
                    QString t = QString::number(elapsed_timer.elapsed()) ;
                    ui->AStarTimer->setText(t + " " + "ms");//Affiche le temps

                }


                else
                {


                    for (int i = 0; i < 8; i++)
                    {
                        //Vérifie si il a été marqué
                        if (m_grid->Get_data().at((quatre_voisins.at(i)->x +(quatre_voisins.at(i)->y *144))/5)->Get_marker_path_width() == false)
                        {
                            exploited.append(m_grid -> Get_data().at((quatre_voisins.at(i)->x + (quatre_voisins.at(i)->y*144))/5));
                            //Marque le voisin
                            m_grid->Get_data().at((quatre_voisins.at(i)->x + (quatre_voisins.at(i)->y*144))/5)->Set_marker_path_width(true);
                            /*
                            connect(&timer, SIGNAL(timeout()), this, SLOT(Affichage_path_width()));
                            timer.start(500); //every 30ms
                            */

                            //Affichage des voisins en jaune
                            m_grid->Get_data().at((quatre_voisins.at(i)->x + (quatre_voisins.at(i)->y*144))/5)->setBrush(QBrush(Qt::darkCyan));
                        }
                    }

                    exploited.pop_front();//Supprime la première

                    // Bloqué de partout
                    if(exploited.size() == 0)
                    {
                        QMessageBox::critical(this," Attention ", " Starting point cannot find a path (blocked by obstacles)");
                        break;
                    }

                    quatre_voisins.clear();

                    //Change notre pointeur en prenant le premier élément de notre liste exploited
                    x_pointer = exploited.at(0) -> x();
                    y_pointer = exploited.at(0) -> y();
                    m_grid->Get_data().at((x_pointer + (y_pointer*144))/5)->setBrush(QBrush(Qt::darkCyan));
                }
            }
        }
    }
}
void window::action_erase()
{
    m_grid -> erase();
}

//Fonctions pour l'algo Dijkstra

void window::explore(MonRectItem *c)
{
    QTimer timer;
    QList<int> pos_voisin = {1,-1,144,-144};

    // Coordonnées
    int x_start_point = m_grid -> Get_start_end().at(1)-> x;//Récupère la coordonée x point d'arrivé
    int y_start_point = m_grid -> Get_start_end().at(1)-> y;//Récupère la coordonée y point d'arrivé


    c -> setBrush(QBrush(Qt::blue));
    c -> Set_marker_path_width(true); //Met l'obstacle comme étant marqué pour l'algo parcours en largeur

    //Vérifie si il dépasse notre cadre
    for (int j =0; j<4; j++)
    {
        if(pos_voisin.at(j) + (c->pos().x() + c->pos().y() * 144)/5 == (x_start_point + y_start_point * 144)/5)
        {
            QMessageBox::about(this," Trouvé ", " Chemin le plus court");

            //Afficahge du temps pour effectuer l'algo parcours en profondeur
            QString t = QString::number(elapsed_timer.elapsed()) ;
            ui->PathDeepTimer->setText(t + " " + "ms");//Affiche le temps
            m_grid ->Set_end(true);
            break;
        }

        else if(((pos_voisin.at(j) + (c->pos().x() + c->pos().y() * 144)/5 >0) || (pos_voisin.at(j) + (c->pos().x() + c->pos().y() * 144)/5 < 10080)) && m_grid->Get_data().at(pos_voisin.at(j) + (c->pos().x() + c->pos().y() * 144)/5)->Get_marker_path_width() == false )
        {
            explore(m_grid->Get_data().at(pos_voisin.at(j) + (c->pos().x() + c->pos().y() * 144)/5));
            break;
        }


    }
}



void window::initialisation_Dijkstra()
{
    double infini = pow(2,32);
    QList<int> pos_voisin = {-1,-145,-143,-144};

    for(int s=0; s<m_grid->Get_data().size(); s++)
    {
        if(m_grid->Get_data().at(s)->Get_type() == 0 || m_grid->Get_data().at(s)->Get_type() == 2)
        {
            m_grid->Set_distance(infini);
        }
        else
        {
            m_grid->Set_distance(0);
        }
    }
}


MonRectItem* window::Min_Dijkstra()
{
    double mini = pow(2,32);
    for(int s=0; s<m_grid->Get_Q().size(); s++)
    {
        if((m_grid->Get_distance().at((m_grid->Get_Q().at(s)->x() + (m_grid->Get_Q().at(s)->y() *144))/5) < mini) && (m_grid->Get_Q().at(s)->Get_prive() == false))
        {
            mini = m_grid->Get_distance().at((m_grid->Get_Q().at(s)->x() + (m_grid->Get_Q().at(s)->y() *144))/5);
            m_grid->Set_sommet(m_grid->Get_Q().at(s));

        }
    }

    return m_grid->Get_sommet();
}

void window::Maj_distance_Dijkstra(MonRectItem* s1,MonRectItem* s2)
{
    if(m_grid->Get_distance().at((s2->x() + (s2->y()*144))/5) > m_grid->Get_distance().at((s1->x() + (s1->y()*144))/5) + 1 && (m_grid->Get_Q().at((s2->x() + (s2->y()*144))/5)->Get_prive() == false) ) // +1 :poids
    {
        m_grid->Replace_distance((s2->x() + (s2->y()*144))/5, 1 + m_grid->Get_distance().at((s1->x() + (s1->y()*144))/5));
        m_grid->Set_P(s2,s1); // prédécesseur[s2] := s1
    }
}









