#include "girodatareciever.h"

namespace LsdSlamIMU
{

IMUDataReciever::IMUDataReciever() :
    m_eRecieverState    ( Disconnected  ),
    m_bDataStreamSync   ( false         )
{
    // Сбросить  структур
    // m_structLastPackedge;

    quint16 size = sizeof( dataPackageStruct );

    // Подключить таймер к слоту
    connect( &m_oStateTimer, SIGNAL(timeout()), this, SLOT(stateTimeOutSlot()));

    // Подключить сигнал приема данных
    connect(  this,   SIGNAL    (   readyRead()         ),
              this,   SLOT      (   recieveDataSlot()   )   );

    // Запускаем таймер
    m_oStateTimer.start( GIRO_DATA_STATE_TIME );
}

IMUDataReciever::~IMUDataReciever()
{
    // Отключиться
    this->close();
}

void IMUDataReciever::stateTimeOutSlot()
{
    // Проверить состояние
    switch( m_eRecieverState )
    {
    // Если устройство отсоеденино
    case Disconnected:
        // Обновить список портов
        m_oPortList.clear();
        m_oPortList = QSerialPortInfo::availablePorts();

        // Поемнять состояние
        m_eRecieverState = CheckPorts;
        break;

    // Если идет проверка портов
    case CheckPorts:
        do
        {
            // Если список пустой
            if( m_oPortList.isEmpty() )
            {
                // Поемнять состояние
                m_eRecieverState = Disconnected;
                // Прервать цикл
                break;
            }

            // Подключить следующий порт
            this->setPortName( m_oPortList.first().portName() );
            // Вывести имя
            qDebug() << "Подключем порт: " << m_oPortList.first().portName() ;

            // Удалить его из списка
            m_oPortList.removeFirst();

            // Сбросить счетчик пакетов
            m_nPackageCounter = 0;

        }
        while( !open(QIODevice::ReadWrite) );
        break;

    // Если подсоединились
    case Connected:
        // Проверить соединение ???
        qDebug() << " Синхронизировано";

        if( !this->open(QIODevice::ReadWrite))
        {
            // Поемнять состояние
            m_eRecieverState = Disconnected;

            m_bDataStreamSync   = false;
            m_nPackageCounter   = 0;
        }
        break;

    default:
        // Что то не так - сообщить
        qDebug() << " GiroDataReciever::stateTimeOutSlot() Default Case ";
        break;
    }
}

void IMUDataReciever::recieveDataSlot()
{
    // Вычитать буфер
    QByteArray tempBuffer = readAll();
    qDebug() << "Сервер: Приняты байты...";

    // Добавляем полученные данные
    m_oRecieveBuffer.append( tempBuffer );

    // Пока длинна буфера больше 2
    while( m_oRecieveBuffer.size() >= sizeof(m_structLastPackedge) )
    {
        // Формируем полученную структуру
        m_structLastPackedge = *(dataPackageStruct*)m_oRecieveBuffer.data();

//        x = m_structLastPackedge.x/16384.0;
//        y = m_structLastPackedge.y/16384.0;
//        z = m_structLastPackedge.z/16384.0;
//        w = m_structLastPackedge.w/16384.0;

//        AccelX = m_structLastPackedge.accelX;
//        AccelY = m_structLastPackedge.accelY;
//        AccelZ = m_structLastPackedge.accelZ;

        //m_oIMUdata.

        qDebug() << "Marker = " << QString::number( m_structLastPackedge.marker, 16 );
        qDebug() <<   " Quaternion X = "   << m_structLastPackedge.qua.x   << ";" << "/n" \
                      " Quaternion Y = "   << m_structLastPackedge.qua.y   << ";" << "/n" \
                      " Quaternion Z = "   << m_structLastPackedge.qua.z   << ";" << "/n" \
                      " Quaternion W = "   << m_structLastPackedge.qua.w   << ";" << "/n" ;

        qDebug() << " Position X = "   << m_structLastPackedge.pos.x   << "mm;" << "/n" \
                    " Position Y = "   << m_structLastPackedge.pos.y   << "mm;" << "/n" \
                    " Position Z = "   << m_structLastPackedge.pos.z   << "mm;" << "/n" ;

        // Если они не равны маркеру
        if( (m_structLastPackedge.marker == 0x00AA) && !m_bDataStreamSync )
        {
            // Если уже 5 пакетов без ошибок
            m_nPackageCounter++;
            if( m_nPackageCounter > 5 )
            {
                // Отметить синхронизауию
                m_bDataStreamSync = true;
                // Сменить состояние
                m_eRecieverState = Connected;
            }
        }
        // Удалить обработанные элементы
        m_oRecieveBuffer.remove( 0, sizeof(m_structLastPackedge) );
    }

    // Опубликовать последние данные
    emit imuDataUpdatedSignal ( );
}

}

