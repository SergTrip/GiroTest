#ifndef GIROTESTWIDGET_H
#define GIROTESTWIDGET_H

#include <QWidget>
#include <QGLViewer/qglviewer.h>
#include <QGLViewer/manipulatedFrame.h>
#include <QGLViewer/quaternion.h>
#include <QVector3D>
#include <QQuaternion>

#include "girodatareciever.h"

#include "facerecognizer.h"

namespace Ui {
class GiroTestWidget;
}

using namespace LsdSlamIMU;

class GiroTestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GiroTestWidget(QWidget *parent = 0);
    ~GiroTestWidget();

public slots:
    // Слот инициализации виджета
    void glViewerWidgetInitSlot();
    // Слот перерисовки виджета
    void draw();

    // Слот обновления положения
    void    newGiroDataSlot     ( qreal x, qreal y, qreal z, qreal w);

    void    newAccelDataSignal  ( qint16 x, qint16 y, qint16 z );

private:
    Ui::GiroTestWidget *ui;

    // Класс связи с устройством
    IMUDataReciever m_oGiroData;

    // Текущие значения гироскопа
    // QQuaternion m_vGiroData;
    QVector4D m_vGiroData;

    QVector3D m_vAccelData;

    // Угол квантерниона
    //double      m_nAngle;

    // Рисует тестовую спираль
    void drawSpiral();

    // Рисуем камеру
    void drawCamera();

    // Рисуем текстуру
    void drawTexture();

    // Описатель текстуры
    GLuint  m_uTexture;

    // Ширина основания
    GLfloat m_nCameraWidth;
    // Высота основания
    GLfloat m_nCameraHigth;
    // Расстояние до плоскости
    GLfloat m_CameraDistance;

private:
    // Создать экземпляр класса захвата камеры
    FaceRecognizer  m_oFaceDetector;
};

#endif // GIROTESTWIDGET_H
