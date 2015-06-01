#include "girodatareciever.h"

GiroDataReciever::GiroDataReciever() :
    m_eRecieverState    ( Disconnected  ),
    m_bDataDtreamSync   ( false         )
{
    // Сбросить  структур
    // m_structLastPackedge;

    // Подключить таймер к слоту
    connect( &m_oStateTimer, SIGNAL(timeout()), this, SLOT(stateTimeOutSlot()));

    // Подключить сигнал приема данных
    connect(  this,   SIGNAL    (   readyRead()         ),
              this,   SLOT      (   recieveDataSlot()   )   );

    // Запускаем таймер
    m_oStateTimer.start( GIRO_DATA_STATE_TIME );
}

GiroDataReciever::~GiroDataReciever()
{
    // Отключиться
    this->close();
}

void GiroDataReciever::stateTimeOutSlot()
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

            m_bDataDtreamSync   = false;
            m_nPackageCounter   = 0;
        }
        break;

    default:
        // Что то не так - сообщить
        qDebug() << " GiroDataReciever::stateTimeOutSlot() Default Case ";
        break;
    }
}

void GiroDataReciever::recieveDataSlot()
{
    qreal x,y,z,w;

    qint16 AccelX, AccelY, AccelZ;

    // Вычитать буфер
    QByteArray tempBuffer = readAll();
    qDebug() << "Сервер: Приняты байты...";

    // Добавляем полученные данные
    m_oRecieveBuffer.append( tempBuffer );

    // Пока длинна буфера больше 2
    while( m_oRecieveBuffer.size() >= (8*2) )
    {
        // Формируем полученную структуру
        m_structLastPackedge = *(dataPackageStruct*)m_oRecieveBuffer.data();

        x = m_structLastPackedge.x/16384.0;
        y = m_structLastPackedge.y/16384.0;
        z = m_structLastPackedge.z/16384.0;
        w = m_structLastPackedge.w/16384.0;

        AccelX = m_structLastPackedge.accelX;
        AccelY = m_structLastPackedge.accelY;
        AccelZ = m_structLastPackedge.accelZ;

        qDebug() << "Marker = " << QString::number( m_structLastPackedge.marker, 16 );
        qDebug() << "X = "      << x   <<  \
                    "; Y = "    << y   <<  \
                    "; Z = "    << z   <<  \
                    "; W = "    << w   ;

        qDebug() << " Accel X = "     << AccelX   <<  \
                    "; Accel Y = "    << AccelY   <<  \
                    "; Accel Z = "    << AccelZ   ;
        // Если они не равны маркеру
        if( (m_structLastPackedge.marker == 0x00AA) && !m_bDataDtreamSync )
        {
            // Если уже 5 пакетов без ошибок
            m_nPackageCounter++;
            if( m_nPackageCounter > 5 )
            {
                // Отметить синхронизауию
                m_bDataDtreamSync = true;
                // Сменить состояние
                m_eRecieverState = Connected;
            }
        }
        // Удалить обработанные элементы
        m_oRecieveBuffer.remove( 0, (8*2) );
    }

    // Опубликовать последние данные
    emit newGiroDataSignal ( x, y, z, w );

    emit newAccelDataSignal( AccelX, AccelY, AccelZ );

    // m_oRecieveBuffer.clear();
}

