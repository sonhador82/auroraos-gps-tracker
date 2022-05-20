/*******************************************************************************
**
** Copyright (C) 2022 Open Mobile Platform LLC.
** Contact: https://community.omprussia.ru/open-source
**
** This file is part of the Aurora OS Application Template project.
**
** Redistribution and use in source and binary forms,
** with or without modification, are permitted provided
** that the following conditions are met:
**
** * Redistributions of source code must retain the above copyright notice,
**   this list of conditions and the following disclaimer.
** * Redistributions in binary form must reproduce the above copyright notice,
**   this list of conditions and the following disclaimer
**   in the documentation and/or other materials provided with the distribution.
** * Neither the name of the copyright holder nor the names of its contributors
**   may be used to endorse or promote products derived from this software
**   without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
** THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
** FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
** OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS;
** OR BUSINESS INTERRUPTION)
** HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
** EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
*******************************************************************************/

#include <QScopedPointer>
#include <QGuiApplication>
#include <QQuickView>
#include <QtPositioning/QGeoPositionInfoSource>
#include <QDebug>
#include <QObject>
#include <QQuickItem>

#include <sailfishapp.h>

#include "statecontroller.h"

#include "mytrack.h"
#include "notif.h"


StateController *initController()
{
    QGeoPositionInfoSource *source = QGeoPositionInfoSource::createDefaultSource(nullptr);
    if(source == 0){
        Notif::notify_geo_missing();
        qDebug() << "GEO Source not found";
    }
    StateController *controller = new StateController(source);
    // source->setUpdateInterval(3000);
    return controller;
}


void bind_signals(StateController *controller, QQuickView *view)
{
    QQuickItem *item = view->rootObject();
    QObject *btns = item->findChild<QObject *>("controlButtons");

    QObject::connect(
                btns,
                SIGNAL(startClick()),
                controller,
                SLOT(startRecording())
                );
    QObject::connect(
                btns,
                SIGNAL(stopClick()),
                controller,
                SLOT(stopRecording())
                );
    QObject::connect(
                controller->getSource(),
                SIGNAL(positionUpdated(QGeoPositionInfo)),
                controller,
                SLOT(positionUpdated(QGeoPositionInfo))
                );

}

int main(int argc, char *argv[])
{

    QScopedPointer<QGuiApplication> application(SailfishApp::application(argc, argv));
    application->setOrganizationName(QStringLiteral("ru.sonhador"));
    application->setApplicationName(QStringLiteral("gpstracker1"));


    QScopedPointer<QQuickView> view(SailfishApp::createView());
    view->setSource(SailfishApp::pathTo(QStringLiteral("qml/gpstracker1.qml")));
    view->show();

    StateController *controller = initController();
    bind_signals(controller, view.take());

    return application->exec();
}
