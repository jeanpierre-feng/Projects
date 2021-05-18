#ifndef MONRECITEM_H
#define MONRECITEM_H
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsRectItem>
class MonRectItem : public QGraphicsRectItem
{
public:
    MonRectItem();
    int Get_type() const;
    void Set_type(int a);
    bool Get_marker_path_width() const;
    void Set_marker_path_width(bool b);
    bool Get_prive() const;
    void Set_prive(bool p);


public:
    int type;   // Etat de la case :
                // VIDE : 0 infini
                // Point de départ : 1 0
                // Point d'arrivé : 2 infini
                // Ressource/Obstacle : 3 0
    bool marker_path_width; // Marqueur pour l'algo de parcours en largeur
    bool prive;
};

#endif // MONRECITEM_H
