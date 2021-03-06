/* ============================================================
* qtwebkit-plugins Plugins for QtWebKit
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
#include "plugin.h"
#include "spellcheck/spellcheck.h"
#include "notifications/notificationpresenter.h"

QtWebKitPlugin::QtWebKitPlugin()
{
}

bool QtWebKitPlugin::supportsExtension(Extension ext) const
{
    return (ext == SpellChecker || ext == Notifications);
}

QObject* QtWebKitPlugin::createExtension(Extension ext) const
{
    switch (ext) {
    case SpellChecker:
        return new SpellCheck();

    case Notifications:
        return new NotificationPresenter();

    default:
        return 0;
    }
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qtwebkitplugins, QtWebKitPlugin);
#endif
