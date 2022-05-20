#include <QtPositioning/QGeoPositionInfoSource>
#include <QtDebug>
#include <QStandardPaths>
#include <QDir>
#include <QQuickItem>
#include <QFile>


#include <iostream>
#include <fstream>

#include <gpx/Writer.h>

#include "statecontroller.h"
#include "notif.h"

StateController::StateController(QGeoPositionInfoSource *source, QObject *parent) : QObject(parent)
{
    if(source != NULL){
        m_source = source;
        m_is_gps_avail = true;
    }
    m_datapath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QDir *dir = new QDir();
    dir->mkpath(m_datapath);
}

void StateController::startRecording()
{
    qDebug() << "Start recording from C++";
    // создать новый список
    if (m_source == NULL){
        Notif::notify_geo_missing();
    }
    if (m_source){
       qDebug() << "Sources: " <<  m_source->availableSources();
    }


    if(!m_is_recording){
        qDebug() << "Start new track";
        m_trk = new MyTrack(QDateTime::currentDateTime().toString("yyyyMMdd-HHmmss"));

        // start updates
        m_is_recording = true;
        if (m_is_gps_avail){
            m_source->startUpdates();
        }
    }
}

void StateController::stopRecording()
{
    qDebug() << "Stop updates";
    m_is_recording = false;
    if (m_is_gps_avail){
        m_source->stopUpdates();
    }

    QString f_name = QString(m_datapath);
    f_name.append("/").append(m_trk->m_name).append(".gpx");
    qDebug() << "Save to: " << m_datapath << f_name;
    m_trk->save(f_name);
}

void StateController::positionUpdated(const QGeoPositionInfo &update)
{
    qDebug() << "Position Updated: " << update;
    m_trk->addPoint(QString::number(update.coordinate().latitude()),
                QString::number(update.coordinate().longitude()));
}

QGeoPositionInfoSource *StateController::getSource()
{
    return m_source;
}
