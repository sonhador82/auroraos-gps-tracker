#include "mytrack.h"

#include <mlite5/MNotification>
#include <QtDBus/QDBusAbstractAdaptor>
#include <fstream>

#include <gpx/GPX.h>
#include <gpx/ReportCerr.h>
#include <gpx/Writer.h>

MyTrack::MyTrack(QString name)
{
    m_name = name;

    m_gpx_root = new gpx::GPX();
    m_gpx_root->add("xmlns", gpx::Node::ATTRIBUTE)
            ->setValue("http://www.topografix.com/GPX/1/1");
    m_gpx_root->version().add(&report)->setValue("1.1");
    m_gpx_root->creator().add(&report)->setValue("SonhadorGPSTracker");

    gpx::TRK *m_gpx_trk = dynamic_cast<gpx::TRK*>(m_gpx_root->trks().add(&report));
    m_gpx_trk->name().add(&report)->setValue(m_name.toStdString());
    m_gpx_trk->trksegs().add(&report);
    m_gpx_trkseg = dynamic_cast<gpx::TRKSeg*>(m_gpx_trk->trksegs().add(&report));
}

void MyTrack::addPoint(QString latitude, QString longitude)
{
    qDebug() << "Adding point: " << latitude << ", " << longitude;
    gpx::WPT *trkpt = dynamic_cast<gpx::WPT*>(m_gpx_trkseg->trkpts().add(&report));
    trkpt->lat().add(&report)->setValue(latitude.toStdString());
    trkpt->lon().add(&report)->setValue(longitude.toStdString());
}

void MyTrack::save(QString path)
{
    std::ofstream ofs(path.toStdString());
    gpx::Writer writer;
    writer.write(ofs, m_gpx_root, true);
    ofs.close();

    MNotification *notif = new MNotification();
    notif->setSummary(QString(m_name.append(" сохранён.")));
    //notif->setIsTransient(true);
    notif->publish();
}
