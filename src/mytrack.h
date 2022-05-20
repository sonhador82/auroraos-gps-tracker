#ifndef MYTRACK_H
#define MYTRACK_H

#include <QtCore>
#include <gpx/GPX.h>
#include <gpx/ReportCerr.h>

class MyTrack
{

public:
    void addPoint(QString latitude, QString longitude);
    void save(QString path);
    MyTrack(QString name);
    QString m_name;

private:
    gpx::GPX *m_gpx_root;
    gpx::TRKSeg *m_gpx_trkseg;
    gpx::ReportCerr report;
};

//gpx::GPX *m_gpx_root;
//gpx::TRK *m_gpx_trk;
//gpx::TRKSeg *m_gpx_trkseg;
//

#endif // MYTRACK_H
