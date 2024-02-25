// SPDX-License-Identifier: GPL-3.0-or-later

#include <QFileInfo>
#include <QFileDialog>

#include "filedialog.h"

using namespace scratchcpp::uicomponents;

FileDialog::FileDialog(QObject *parent) :
    QObject(parent)
{
}

const QStringList &FileDialog::nameFilters(void) const
{
    return m_nameFilters;
}

void FileDialog::setNameFilters(const QStringList &filters)
{
    m_nameFilters = filters;
    emit nameFiltersChanged();
}

bool FileDialog::showAllFiles(void) const
{
    return m_showAllFiles;
}

void FileDialog::setShowAllFiles(bool value)
{
    m_showAllFiles = value;
    emit showAllFilesChanged();
}

const QString &FileDialog::fileName(void) const
{
    return m_fileName;
}

QString FileDialog::shortFileName(void) const
{
    QFileInfo fileInfo(m_fileName);
    return fileInfo.fileName();
}

const QString &FileDialog::defaultSuffix() const
{
    return m_defaultSuffix;
}

void FileDialog::setDefaultSuffix(const QString &newDefaultSuffix)
{
    if (m_defaultSuffix == newDefaultSuffix)
        return;

    m_defaultSuffix = newDefaultSuffix;
    emit defaultSuffixChanged();
}

void FileDialog::getOpenFileContent(void)
{
    auto fileContentReadyLambda = [this](const QString &fileName, const QByteArray &fileContent) {
        if (!fileName.isEmpty()) {
            m_fileName = fileName;
            emit fileNameChanged();
            emit shortFileNameChanged();
            emit fileContentReady(fileContent);
        }
    };

#ifdef Q_OS_WASM
    QFileDialog::getOpenFileContent(QString(), fileContentReadyLambda);
#else
    QString fileName = QFileDialog::getOpenFileName(nullptr, QString(), QString(), getFilters());

    if (fileName != "") {
        QFile file(fileName);

        if (file.open(QIODevice::ReadOnly))
            fileContentReadyLambda(fileName, file.readAll());
    }
#endif
}

QString FileDialog::getOpenFileName() const
{
    QFileDialog dialog(nullptr, QString(), QString(), getFilters());
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setDefaultSuffix(m_defaultSuffix);

    if (dialog.exec() == QDialog::Accepted)
        return dialog.selectedFiles().at(0);
    else
        return "";
}

QString FileDialog::getSaveFileName() const
{
    QFileDialog dialog(nullptr, QString(), QString(), getFilters());
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setDefaultSuffix(m_defaultSuffix);

    if (dialog.exec() == QDialog::Accepted)
        return dialog.selectedFiles().at(0);
    else
        return "";
}

QString FileDialog::getFilters() const
{
    QString filtersStr = m_nameFilters.join(";;");

    if (m_showAllFiles)
        filtersStr += ";;" + tr("All files") + " (*)";

    return filtersStr;
}
