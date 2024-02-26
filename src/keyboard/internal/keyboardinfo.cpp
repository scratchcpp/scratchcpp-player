// SPDX-License-Identifier: GPL-3.0-or-later

#include <QGuiApplication>

#include "keyboardinfo.h"

using namespace scratchcpp::keyboard;

KeyboardInfo::KeyboardInfo(QObject *parent) :
    QObject(parent)
{
}

Qt::KeyboardModifiers KeyboardInfo::keyboardModifiers() const
{
    return QGuiApplication::keyboardModifiers();
}
