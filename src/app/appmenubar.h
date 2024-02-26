// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QQmlEngine>

Q_MOC_INCLUDE("uicomponents/menubarmodel.h")

class QTemporaryFile;

namespace scratchcpp
{

namespace uicomponents
{

class MenuBarModel;
class MenuModel;
class MenuItemModel;
class FileDialog;

} // namespace uicomponents

class AppMenuBar : public QObject
{
        Q_OBJECT
        QML_ELEMENT
        QML_SINGLETON
        Q_PROPERTY(uicomponents::MenuBarModel *model READ model NOTIFY modelChanged)
        Q_PROPERTY(bool turboMode READ turboMode WRITE setTurboMode NOTIFY turboModeChanged)

    public:
        explicit AppMenuBar(QObject *parent = nullptr);

        uicomponents::MenuBarModel *model() const;

        bool turboMode() const;
        void setTurboMode(bool newTurboMode);

    signals:
        void modelChanged();
        void fileOpened(const QString &fileName);
        void turboModeChanged();

    private:
        void openFile();
#ifdef Q_OS_WASM
        void loadOpenedFile(const QByteArray &content);
#endif

        uicomponents::MenuBarModel *m_model = nullptr;

        uicomponents::MenuModel *m_fileMenu = nullptr;
        uicomponents::MenuItemModel *m_openFileItem = nullptr;
        uicomponents::FileDialog *m_openFileDialog = nullptr;
        QTemporaryFile *m_tmpFile = nullptr;

        uicomponents::MenuModel *m_editMenu = nullptr;
        uicomponents::MenuItemModel *m_turboModeItem = nullptr;
        bool m_turboMode = false;
};

} // namespace scratchcpp
