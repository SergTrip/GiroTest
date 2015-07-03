#ifndef GIRODATARECIEVER_H
#define GIRODATARECIEVER_H

#include <QtSerialPort/QtSerialPort>
#include <QTimer>
#include <QDebug>

#include "imudata.h"

namespace LsdSlamIMU
{

// Время для таймера контроля состояния
#define GIRO_DATA_STATE_TIME 500
// Длинна пакета
#define GIRO_DATA_PACET_SIZE 8

class IMUDataReciever : public QSerialPort
{
    Q_OBJECT
public:
    // Конструктор
    IMUDataReciever();
    ~IMUDataReciever();

private:
    // Состояния системы
    enum
    {
        Disconnected,       // Устройство не подключено
        CheckPorts,         // Идет опрос доступных портов
        Connected           // Устройство подключено
    } m_eRecieverState;

    // Таймер для тактирования протокола
    QTimer m_oStateTimer;

    // Содержит список портов
    // QSerialPortInfo m_oConnectionList;

    // Содержит список портов
    QList<QSerialPortInfo>  m_oPortList;

    // Флаг синхронизации данных
    bool        m_bDataStreamSync;
    // Счетчик данных
    qint8       m_nPackageCounter;

    // Буфер полученных данных
    QByteArray  m_oRecieveBuffer;

    // Структура пакета
    typedef struct
    {
        quint16 marker; // маркер пакета

        struct
        {
            qint16  w;
            qint16  x;
            qint16  y;
            qint16  z;
        }qua;
        struct
        {
            double  x;
            double  y;
            double  z;
        }acc;
        struct
        {
            double  x;
            double  y;
            double  z;
        }vel;
        struct
        {
            double  x;
            double  y;
            double  z;
        }pos;

    }dataPackageStruct;

    // Экземпляр структуры
    dataPackageStruct m_structLastPackedge;

    IMUData m_oIMUdata;

protected slots:
    // Слот для контроля состояния модуля
    void stateTimeOutSlot();

    // Слот приема данных
    void recieveDataSlot();

signals:
    // Сообщение о формировании новых данных
    void    imuDataUpdatedSignal();

};

}

#endif // GIRODATARECIEVER_H
