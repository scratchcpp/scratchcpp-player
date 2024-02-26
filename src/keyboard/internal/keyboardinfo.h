// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QObject>

#include "ikeyboardinfo.h"

namespace scratchcpp::keyboard
{

class KeyboardInfo
    : public QObject
    , public IKeyboardInfo
{
        Q_OBJECT

    public:
        explicit KeyboardInfo(QObject *parent = nullptr);

        Q_INVOKABLE Qt::KeyboardModifiers keyboardModifiers() const override;
};

} // namespace scratchcpp::keyboard
