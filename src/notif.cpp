#include <mlite5/MNotification>

#include "notif.h"

void Notif::notify_geo_missing()
{

    MNotification *notif = new MNotification();
    notif->setSummary(QString("Нет gps моудуля."));
    notif->publish();
    delete notif;
}

void Notif::notify_track_saved(QString f_name)
{
    MNotification *notif = new MNotification();
    notif->setSummary(f_name.append(" файл сохранен."));
    notif->publish();
    delete notif;
}
