// SPDX-License-Identifier: GPL-3.0-or-later

#include <QQmlEngine>

#include "modularity/ioc.h"
#include "keyboardmodule.h"
#include "internal/keyboardinfo.h"

using namespace scratchcpp::keyboard;

std::string KeyboardModule::moduleName() const
{
    return "keyboard";
}

void KeyboardModule::registerExports()
{
    m_keyboardInfo = std::make_shared<KeyboardInfo>();

    QQmlEngine::setObjectOwnership(m_keyboardInfo.get(), QQmlEngine::CppOwnership);
    qmlRegisterSingletonInstance<KeyboardInfo>("ScratchCPP.Keyboard", 1, 0, "KeyboardInfo", m_keyboardInfo.get());
    modularity::ioc()->registerExport<IKeyboardInfo>(m_keyboardInfo);
}
