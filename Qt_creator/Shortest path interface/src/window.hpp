#pragma once

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QMainWindow>
#include <QtGui>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QElapsedTimer>
//forward declaration
#include "grille.hpp"
#include "monrecitem.h"
namespace Ui{
class MainWindow;
}
class render_area;

/** Window declaration */
class window: public QMainWindow
{
    Q_OBJECT

public:

    window(QWidget *parent=NULL);
    ~window();
    void explore(MonRectItem *c);
    void initialisation_Dijkstra();
    MonRectItem* Min_Dijkstra();
    void Maj_distance_Dijkstra(MonRectItem* s1,MonRectItem* s2);


private slots:

    void action_quit();
    void action_reset();
    void action_path_width();
    void action_path_deep();
    void action_dijkstra();
    void action_a_star();
    void action_erase();



private:

    Ui::MainWindow *ui;
    QGraphicsView* view;

    Grille<MonRectItem>* m_grid;
    MonRectItem* item;
    QElapsedTimer elapsed_timer;

};

#endif
