/* ============================================================
* qtwebkit-notifications DBus notification plugin
* Copyright (C) 2013  David Rosca <nowrep@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* ============================================================ */
#include "notificationpresenter.h"

#include <QDir>
#include <QDebug>
#include <QFile>
#include <QImage>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDBusInterface>

NotificationPresenter::NotificationPresenter()
    : QWebNotificationPresenter()
    , m_manager(0)
    , m_data(0)
    , m_uid(0)
{
}

void NotificationPresenter::showNotification(const QWebNotificationData* data)
{
    if (data->message().isEmpty()) {
        qDebug() << "NotificationPresenter: HTML notifications are not supported.";
        return;
    }

    m_data = data;

    if (!m_data->iconUrl().isEmpty()) {
        m_manager = new QNetworkAccessManager(this);
        m_manager->get(QNetworkRequest(m_data->iconUrl()));
        connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloaded(QNetworkReply*)));
    }

    sendNotification(QImage());
}

void NotificationPresenter::downloaded(QNetworkReply *reply)
{
    QByteArray response = reply->readAll();
    reply->deleteLater();

    QImage image;
    image.loadFromData(response);
    sendNotification(image);
}

void NotificationPresenter::sendNotification(const QImage &image)
{
    QString fileName = QDir::tempPath() + "/qtwebkit-notif.png";

    if (QFile(fileName).exists()) {
        QFile(fileName).remove();
    }

    if (image.isNull()) {
        QImage(":notifications/webkit.png").save(fileName, "PNG");
    }
    else {
        image.save(fileName, "PNG");
    }

    QDBusInterface dbus("org.freedesktop.Notifications", "/org/freedesktop/Notifications",
                        "org.freedesktop.Notifications", QDBusConnection::sessionBus());
    QVariantList args;
    args.append(QLatin1String("qtwebkitplugins"));
    args.append(m_uid);
    args.append(fileName);
    args.append(m_data->title());
    args.append(m_data->message());
    args.append(QStringList());
    args.append(QVariantMap());
    args.append(5000);

    QDBusMessage message = dbus.callWithArgumentList(QDBus::Block, "Notify", args);
    QVariantList list = message.arguments();
    if (list.count() > 0) {
        m_uid = list.at(0).toInt();
    }

    QDBusConnection::sessionBus().connect("org.freedesktop.Notifications",
                                          "/org/freedesktop/Notifications",
                                          "org.freedesktop.Notifications",
                                          "NotificationClosed", this,
                                          SLOT(notifClosed(quint32, quint32)));

    QDBusConnection::sessionBus().connect("org.freedesktop.Notifications",
                                          "/org/freedesktop/Notifications",
                                          "org.freedesktop.Notifications",
                                          "ActionInvoked", this,
                                          SLOT(notifClicked(quint32, const QString&)));
}

void NotificationPresenter::notifClosed(quint32 id, quint32 reason)
{
    Q_UNUSED(reason)

    if (m_uid == id) {
        emit notificationClosed();
    }
}

void NotificationPresenter::notifClicked(quint32 id, const QString &actionKey)
{
    Q_UNUSED(actionKey)

    if (m_uid == id) {
        emit notificationClicked();
    }
}

NotificationPresenter::~NotificationPresenter()
{
    delete m_manager;
}
