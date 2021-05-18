#include "monrecitem.h"
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QDebug>
#include <QApplication>
#include <QMouseEvent>
#include <QTimer>
#include <QObject>
#include "qobject.h"


MonRectItem::MonRectItem()
    :type(0),marker_path_width(false),prive(false)
{

    setRect(0,0,5,5);
    setPen(QPen(Qt::white));
    setBrush(QBrush(Qt::black));


}

// Getters et Setters
int MonRectItem:: Get_type() const
{
    return type;
}

void MonRectItem:: Set_type(int a)
{
    type = a;
}

bool MonRectItem::Get_marker_path_width() const
{
    return marker_path_width;
}
void MonRectItem::Set_marker_path_width(bool b)
{
    marker_path_width = b;
}

bool MonRectItem::Get_prive() const
{
    return prive;
}

void MonRectItem::Set_prive(bool p)
{
    prive = p;
}
