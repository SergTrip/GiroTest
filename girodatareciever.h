#ifndef GIRODATARECIEVER_H
#define GIRODATARECIEVER_H

#include <QtSerialPort/QtSerialPort>
#include <QTimer>
#include <QDebug>

// Время для таймера контроля состояния
#define GIRO_DATA_STATE_TIME 500
// Длинна пакета
#define GIRO_DATA_PACET_SIZE 8

class GiroDataReciever : public QSerialPort
{
    Q_OBJECT
public:
    // Конструктор
    GiroDataReciever();
    ~GiroDataReciever();

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
    bool        m_bDataDtreamSync;
    // Счетчик данных
    qint8       m_nPackageCounter;

    // Буфер полученных данных
    QByteArray  m_oRecieveBuffer;

    // Структура пакета
    typedef struct
    {
        quint16 marker; // маркерпакета
        qint16  x;
        qint16  y;
        qint16  z;

    }dataPackageStruct;

    // Экземпляр структуры
    dataPackageStruct m_structLastPackedge;

protected slots:
    // Слот для контроля состояния модуля
    void stateTimeOutSlot();

    // Слот приема данных
    void recieveDataSlot();

};

#endif // GIRODATARECIEVER_H
