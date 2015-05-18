#ifndef GIRODATARECIEVER_H
#define GIRODATARECIEVER_H

#include <QtSerialPort/QtSerialPort>

class GiroDataReciever : public QSerialPort
{
public:
    GiroDataReciever();
    ~GiroDataReciever();
};

#endif // GIRODATARECIEVER_H
