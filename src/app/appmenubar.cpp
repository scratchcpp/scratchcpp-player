// SPDX-License-Identifier: GPL-3.0-or-later

#include "appmenubar.h"
#include "uicomponents/menubarmodel.h"
#include "uicomponents/menumodel.h"
#include "uicomponents/menuitemmodel.h"

using namespace scratchcpp;
using namespace scratchcpp::uicomponents;

AppMenuBar::AppMenuBar(QObject *parent) :
    QObject(parent),
    m_model(new MenuBarModel(this))
{
}

MenuBarModel *AppMenuBar::model() const
{
    return m_model;
}
