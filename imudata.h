#ifndef IMUDATA_H
#define IMUDATA_H

#include <QQuaternion>
#include <QVector3D>

namespace LsdSlamIMU
{

class IMUData
{
public:
    IMUData();
    ~IMUData();

    // Возвращает ореинтацию
    QQuaternion Orientation() const;
    // Возвращает положение
    QVector3D   Position() const;

private:
    // Инициализация
    bool        m_bInit;

    // Ориентация
    QQuaternion m_qOrientation;
    // Ускорение
    QVector3D   m_vAcceleration;
    // Скорость
    QVector3D   m_vVelocity;
    // Положение
    QVector3D   m_vPosition;

private:
    // Прием данных
    void updateData(QByteArray &buff);

    // Отрисовка себя ???
};

}

#endif // IMUDATA_H
