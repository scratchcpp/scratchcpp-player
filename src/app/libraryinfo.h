// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QQmlEngine>

namespace scratchcpp
{

class LibraryInfo : public QObject
{
        Q_OBJECT
        QML_ELEMENT
        QML_SINGLETON
    public:
        explicit LibraryInfo(QObject *parent = nullptr);

        Q_INVOKABLE QString libscratchcppVersion() const;
        Q_INVOKABLE QString scratchcppRenderVersion() const;
};

} // namespace scratchcpp
