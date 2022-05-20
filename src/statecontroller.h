#ifndef STATECONTROLLER_H
#define STATECONTROLLER_H

#include <QtPositioning/QGeoPositionInfoSource>
#include <QFile>
#include <QDebug>
#include <QObject>
#include <QGeoPositionInfo>
#include <QQuickItem>
#include <QQuickView>
#include <QQmlContext>

#include "mytrack.h"

class StateController : public QObject
{
    Q_OBJECT
public:
    explicit StateController(QGeoPositionInfoSource *source, QObject *parent = nullptr);

signals:

public slots:
    void startRecording();
    void stopRecording();
    void positionUpdated(const QGeoPositionInfo &update);
    void positionUpdated(){};
    QGeoPositionInfoSource *getSource();

private:
    bool m_is_recording = false;
    bool m_is_gps_avail = false;
    QGeoPositionInfoSource *m_source;
    QString m_datapath;
    QList<QGeoPositionInfo> *m_list;
    MyTrack *m_trk;

    ~StateController(){}
};

#endif // STATECONTROLLER_H
