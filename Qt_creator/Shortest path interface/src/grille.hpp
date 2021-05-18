#pragma once

#ifndef GRILLE_HPP
#define GRILLE_HPP

#include <vector>
#include <iostream>
#include <QGraphicsScene>
#include <QObject>
#include <QWidget>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QDebug>
#include <QPen>
#include <QtMath>
#include <QMap>

#include "vec2.hpp"

template <typename T>
class Grille : public QGraphicsScene,QGraphicsRectItem
{
private :
    int Hx;
    int Hy;
    bool blocked;// variable pour savoir si on est bloqué
    bool end; // Variable pour savoir si on a fini utilisé dans l'algo parcours en profondeur


    QList<T*> data;
    QList<vec2*> start_end;

    //Variables utilisé pour l'algo de Dijkstra
    QList<int> distance;//Algo Dijkstra poids/distance des cases
    QList<T*> Q;//Algo Dijkstra
    QMap<T*,T*> P;//Algo Dijkstra <pointeur, prédecesseur> pendant la lecture on lit le sommet
    double mini ;//Distance minimal actuel
    T* sommet ; //Sommet sur lequel ce trouve la distance minimal

public:


    //Constructeur
    Grille()
        :Hx(71),Hy(146),blocked(false),end(false),data(),start_end(),distance(),Q(),P(),mini(pow(2,32)),sommet(new T())
    {
        //Grille
        for (int i =0;i < 71 ; i ++)
        {
            addLine(0,i*5,719,i*5);

        }
        for (int i =0;i < 145 ; i ++)
        {
            addLine(i*5,0,i*5,349);

        }


        //Carrés
        for (int j =0; j<70 ;j++ ) {
            for (int i=0; i<144; i++)
            {
                T* item = new T();
                item -> setPos(i*5,j*5);
                data.append(item);
                addItem(item);
            }
        }
    }

//Fonctions S
    void assert_coord(int x, int y) const
    {
        if(x<0 || x>=Hx || y<0 || y>=Hy)
        {
            std::cerr<<"Index "<<x<<","<<y<<" hors bornes."<<std::endl;
            exit(1);
        }
    }

    T const& operator()(int x,int y) const
    {
        assert_coord(x,y);
        return data[y+Hy*x];
    }

    T& operator()(int x,int y)
    {
        assert_coord(x,y);
        return data[y+Hy*x];
    }

    void resize(int Hx_arg, int Hy_arg)
    {
        Hx=Hx_arg;
        Hy=Hy_arg;
    }

//Accesseurs / Mutateurs
    int get_Hx() const
    {
        return Hx;
    }

    int get_Hy() const
    {
        return Hy;
    }

    QList<T*> Get_data() const
    {
        return data;
    }

    QList<vec2*> Get_start_end() const
    {
        return start_end;
    }

    QList<int> Get_distance() const
    {
        return distance;
    }

    void Set_distance(int value)
    {
        distance.append(value) ;
    }
    void Replace_distance(int ite,int value)
    {
        distance.replace(ite,value) ;
    }


    QList<T*> Get_Q() const
    {
        return Q;
    }
    void Set_Q(T* s)
    {
        Q.append(s);
    }
    void RemoveAt_Q(int pos)
    {
        Q.removeAt(pos);
    }

    QMap<T*,T*> Get_P() const
    {
        return P;
    }

    void Set_P(T* s1, T* s2)
    {
        P.insert(s1,s2);
    }

    bool Get_blocked() const
    {
        return blocked;
    }

    void Set_blocked(bool c)
    {
        blocked = c;
    }
    bool Get_end() const
    {
        return end;
    }

    void Set_end(bool e)
    {
        end = e;
    }
    double Get_mini() const
    {
        return mini;
    }
    void Set_mini(double value)
    {
        mini = value;
    }
    T* Get_sommet() const
    {
        return sommet;
    }
    void Set_sommet(T* s)
    {
        sommet = s;
    }
    //Varialbes globale
    int facts = 0;

    //Reset
    void reset()
    {
        // Delete data
        data.clear();
        start_end.clear();
        distance.clear();
        qDebug()<< "Data :"<<data;
        qDebug()<< "start_end :" <<start_end;


        // Reconstruit :
        facts =0;

        //Réinitialise les variables
        end = false;
        blocked = false;

        //Carrés
        for (int j =0; j<70 ;j++ ) {
            for (int i=0; i<144; i++)
            {
                T* item = new T();
                item -> setPos(i*5,j*5);
                data.append(item);
                addItem(item);
            }
        }


    }

    void erase()
    {
        //Réinitialise les variables
        end = false;
        blocked = false;
        distance.clear();

        //Carrés
        for(int j = 0; j<data.size(); j++)
        {
            if(Get_data().at(j)->Get_type() == 0 )
            {
                Get_data().at(j) -> setBrush(QBrush(Qt::black));
                Get_data().at(j) -> Set_marker_path_width(false);

            }
        }
    }

    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        int x = (cursor().pos().x()-184); //Coordonnées de 5 en 5
        int y = (cursor().pos().y()-128);
        int x_mouse = (x-x%5);
        int y_mouse = (y-y%5);

        if (facts == 0 )
        {
            //Point de départ
            facts++;
            qDebug()<<start_end;
            vec2* point_start = new vec2(x_mouse,y_mouse);
            qDebug()<<start_end.size();//Récupère la coordonée
            start_end.append(point_start);
            qDebug()<<start_end.at(0)->x;//Récupère la coordonée

            data.at((x_mouse+y_mouse*144)/5)->setBrush(QBrush(Qt::green));
            qDebug()<<x_mouse<<";"<<y_mouse;
            qDebug()<<Get_data().at((x_mouse+y_mouse*144)/5)->Get_type();
            Get_data().at((x_mouse+y_mouse*144)/5)->Set_type(1); //Change le type de la case en 1 : point de départ
            Get_data().at((x_mouse+y_mouse*144)/5)->Set_marker_path_width(true); //Met le point de départ comme étant marqué pour l'algo parcours en largeur

            qDebug()<<Get_data().at((x_mouse+y_mouse*144)/5)->Get_type();



        }
        else if (facts == 1 )
        {
            facts++;
            //Point d'arrivé
            vec2* point_end = new vec2(x_mouse,y_mouse);
            start_end.append(point_end);
            qDebug()<<start_end.size();//Taille de la table = 4

            data.at((x_mouse+y_mouse*144)/5)->setBrush(QBrush(Qt::red));
            qDebug()<<x_mouse<<";"<<y_mouse;
            qDebug()<<Get_data().at((x_mouse+y_mouse*144)/5)->Get_type();
            Get_data().at((x_mouse+y_mouse*144)/5)->Set_type(2); //Change le type de la case en 1 : point de départ
            Get_data().at((x_mouse+y_mouse*144)/5)->Set_marker_path_width(true); //Met le point de départ comme étant marqué pour l'algo parcours en largeur
            qDebug()<<Get_data().at((x_mouse+y_mouse*144)/5)->Get_type();


        }

        else if (facts == 2 && data.at((x_mouse+y_mouse*144)/5)->Get_type() == 0)
        {
            //Obstacles

            data.at((x_mouse+y_mouse*144)/5)->setBrush(QBrush(Qt::white));
            qDebug()<<x_mouse<<";"<<y_mouse;
            qDebug()<<Get_data().at((x_mouse+y_mouse*144)/5)->Get_type();
            Get_data().at((x_mouse+y_mouse*144)/5)->Set_type(3); //Change le type de la case en 1 : point de départ
            Get_data().at((x_mouse+y_mouse*144)/5)->Set_marker_path_width(true); //Met l'obstacle comme étant marqué pour l'algo parcours en largeur

            qDebug()<<Get_data().at((x_mouse+y_mouse*144)/5)->Get_type();
            facts++;

        }

        else if (facts == 3)
        {
            facts =2;
        }
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)
    {
        int x = (cursor().pos().x()-184); //Coordonnées de 5 en 5
        int y = (cursor().pos().y()-128);
        int x_current = (x-x%5);
        int y_current = (y-y%5);

        if(facts == 3 && data.at((x_current+y_current*144)/5)->Get_type()==0 && data.at((x_current+y_current*144)/5+1)->Get_type()==0 && data.at((x_current+y_current*144)/5+145)->Get_type()==0 && data.at((x_current+y_current*144)/5+144)->Get_type()==0)
        {

            data.at((x_current+y_current*144)/5)->setBrush(QBrush(Qt::white));
            data.at((x_current+y_current*144)/5+1)->setBrush(QBrush(Qt::white));
            data.at((x_current+y_current*144)/5+144)->setBrush(QBrush(Qt::white));
            data.at((x_current+y_current*144)/5+145)->setBrush(QBrush(Qt::white));

            Get_data().at((x_current+y_current*144)/5)->Set_type(3); //Change le type de la case en 1 : point de départ
            Get_data().at((x_current+y_current*144)/5+1)->Set_type(3); //Change le type de la case en 1 : point de départ
            Get_data().at((x_current+y_current*144)/5+144)->Set_type(3); //Change le type de la case en 1 : point de départ
            Get_data().at((x_current+y_current*144)/5+145)->Set_type(3); //Change le type de la case en 1 : point de départ

            Get_data().at((x_current+y_current*144)/5)->Set_marker_path_width(true); //Met l'obstacle comme étant marqué pour l'algo parcours en largeur
            Get_data().at((x_current+y_current*144)/5+1)->Set_marker_path_width(true);
            Get_data().at((x_current+y_current*144)/5+144)->Set_marker_path_width(true);
            Get_data().at((x_current+y_current*144)/5+145)->Set_marker_path_width(true);

        }
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& stream,const Grille<T> g)
{
    for(int cpt_x=0; cpt_x<g.get_Hx(); cpt_x++)
    {
        for(int cpt_y=0; cpt_y<g.get_Hy(); cpt_y++)
        {
            stream<<g(cpt_x,cpt_y)<<" ";
            
        }
        stream<<std::endl;
    }
    return stream;
}
#endif
