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
#ifndef NOTIFICATIONPRESENTER_H
#define NOTIFICATIONPRESENTER_H

#include "qwebkitplatformplugin.h"

#include <QString>

class QImage;
class QNetworkAccessManager;
class QNetworkReply;

class NotificationPresenter : public QWebNotificationPresenter
{
    Q_OBJECT
public:
    explicit NotificationPresenter();
    ~NotificationPresenter();

    void showNotification(const QWebNotificationData* data);

signals:
    void notificationClosed();
    void notificationClicked();

private slots:
    void downloaded(QNetworkReply* reply);
    void notifClosed(quint32 id, quint32 reason);
    void notifClicked(quint32 id, const QString &actionKey);

private:
    void sendNotification(const QImage &image);

    QNetworkAccessManager* m_manager;
    const QWebNotificationData* m_data;
    quint32 m_uid;
};

#endif // NOTIFICATIONPRESENTER_H
