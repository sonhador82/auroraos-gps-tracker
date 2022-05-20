#ifndef NOTIF_H
#define NOTIF_H

#include <QtCore>

class Notif
{
public:
    static void notify_geo_missing();
    static void notify_track_saved(QString f_name);

};

#endif // NOTIF_H
