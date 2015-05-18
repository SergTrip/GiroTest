#ifndef GIROTESTWIDGET_H
#define GIROTESTWIDGET_H

#include <QWidget>
#include <QGLViewer/qglviewer.h>
#include <QGLViewer/manipulatedFrame.h>
#include <QGLViewer/quaternion.h>

#include "girodatareciever.h"

namespace Ui {
class GiroTestWidget;
}

class GiroTestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GiroTestWidget(QWidget *parent = 0);
    ~GiroTestWidget();

public slots:
    // Слот перерисовки виджета
    void draw();
    // Слот обновления положения
    void    newGiroDataSlot( qint16 x, qint16 y, qint16 z);

private:
    Ui::GiroTestWidget *ui;

    // Класс связи с устройством
    GiroDataReciever m_oGiroData;
};

#endif // GIROTESTWIDGET_H
