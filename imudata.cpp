#include "imudata.h"

namespace LsdSlamIMU
{

IMUData::IMUData()
{

}

IMUData::~IMUData()
{

}
QQuaternion IMUData::Orientation() const
{
    return m_qOrientation;
}

QVector3D IMUData::Position() const
{
    return m_vPosition;
}

}

