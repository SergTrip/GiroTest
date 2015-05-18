#ifndef GIROTESTWIDGET_H
#define GIROTESTWIDGET_H

#include <QWidget>

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
  void draw();

private:
    Ui::GiroTestWidget *ui;

    // Класс связи с устройством
    GiroDataReciever m_oGiroData;
};

#endif // GIROTESTWIDGET_H
