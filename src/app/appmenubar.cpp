// SPDX-License-Identifier: GPL-3.0-or-later

#include <QTemporaryFile>

#include "appmenubar.h"
#include "uicomponents/menubarmodel.h"
#include "uicomponents/menumodel.h"
#include "uicomponents/menuitemmodel.h"
#include "uicomponents/filedialog.h"

using namespace scratchcpp;
using namespace scratchcpp::uicomponents;

AppMenuBar::AppMenuBar(QObject *parent) :
    QObject(parent),
    m_model(new MenuBarModel(this)),
    m_openFileDialog(new FileDialog(this))
{
    m_openFileDialog->setShowAllFiles(false);
    m_openFileDialog->setNameFilters({ tr("Scratch 3 projects (%1)").arg("*.sb3") });

    // File menu
    m_fileMenu = new MenuModel(m_model);
    m_fileMenu->setTitle(tr("&File"));
    m_model->addMenu(m_fileMenu);

    // File -> Open
    m_openFileItem = new MenuItemModel(m_fileMenu);
    m_openFileItem->setText(tr("Open..."));
    m_fileMenu->addItem(m_openFileItem);

    connect(m_openFileItem, &MenuItemModel::clicked, this, &AppMenuBar::openFile);
#ifdef Q_OS_WASM
    connect(m_openFileDialog, &FileDialog::fileContentReady, this, &AppMenuBar::loadOpenedFile);
#endif

    // Edit menu
    m_editMenu = new MenuModel(m_model);
    m_editMenu->setTitle(tr("&Edit"));
    m_model->addMenu(m_editMenu);

    // Edit -> Turbo mode
    m_turboModeItem = new MenuItemModel(m_editMenu);
    m_turboModeItem->setText(tr("Turbo Mode"));
    m_turboModeItem->setCheckable(true);
    m_turboModeItem->setChecked(false);
    m_editMenu->addItem(m_turboModeItem);
    connect(m_turboModeItem, &MenuItemModel::checkedChanged, this, &AppMenuBar::turboModeChanged);

    // Edit -> 60 FPS mode
    m_fps60ModeItem = new MenuItemModel(m_editMenu);
    m_fps60ModeItem->setText(tr("60 FPS Mode"));
    m_fps60ModeItem->setCheckable(true);
    m_fps60ModeItem->setChecked(false);
    m_editMenu->addItem(m_fps60ModeItem);
    connect(m_fps60ModeItem, &MenuItemModel::checkedChanged, this, &AppMenuBar::fps60ModeChanged);

    // Edit -> Project settings
    m_projectSettingsItem = new MenuItemModel(m_editMenu);
    m_projectSettingsItem->setText(tr("Project settings..."));
    m_editMenu->addItem(m_projectSettingsItem);
    connect(m_projectSettingsItem, &MenuItemModel::clicked, this, &AppMenuBar::projectSettingsTriggered);

    // Help menu
    m_helpMenu = new MenuModel(m_model);
    m_helpMenu->setTitle(tr("&Help"));
    m_model->addMenu(m_helpMenu);

    // Help -> About program
    m_aboutAppItem = new MenuItemModel(m_fileMenu);
    m_aboutAppItem->setText(tr("About program..."));
    m_helpMenu->addItem(m_aboutAppItem);
    connect(m_aboutAppItem, &MenuItemModel::clicked, this, &AppMenuBar::aboutAppTriggered);
}

MenuBarModel *AppMenuBar::model() const
{
    return m_model;
}

void AppMenuBar::openFile()
{
#ifdef Q_OS_WASM
    m_openFileDialog->getOpenFileContent();
#else
    QString fileName = m_openFileDialog->getOpenFileName();

    if (!fileName.isEmpty())
        emit fileOpened(fileName);
#endif
}

#ifdef Q_OS_WASM
void AppMenuBar::loadOpenedFile(const QByteArray &content)
{
    if (m_tmpFile)
        m_tmpFile->deleteLater();

    m_tmpFile = new QTemporaryFile(this);

    if (m_tmpFile->open()) {
        m_tmpFile->write(content);
        m_tmpFile->close();
        emit fileOpened(m_tmpFile->fileName());
    } else
        qWarning("Failed to create temporary file.");
}
#endif

bool AppMenuBar::turboMode() const
{
    return m_turboModeItem->checked();
}

void AppMenuBar::setTurboMode(bool newTurboMode)
{
    if (m_turboModeItem->checked() == newTurboMode)
        return;

    m_turboModeItem->setChecked(newTurboMode);
}

bool AppMenuBar::fps60Mode() const
{
    return m_fps60ModeItem->checked();
}

void AppMenuBar::setFps60Mode(bool newFps60Mode)
{
    if (m_fps60ModeItem->checked() == newFps60Mode)
        return;

    m_fps60ModeItem->setChecked(newFps60Mode);
    emit fps60ModeChanged();
}
