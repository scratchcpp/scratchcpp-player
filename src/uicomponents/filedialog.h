// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QQmlEngine>

namespace scratchcpp::uicomponents
{

class FileDialog : public QObject
{
        Q_OBJECT
        QML_ELEMENT
        Q_PROPERTY(QStringList nameFilters READ nameFilters WRITE setNameFilters NOTIFY nameFiltersChanged)
        Q_PROPERTY(bool showAllFiles READ showAllFiles WRITE setShowAllFiles NOTIFY showAllFilesChanged)
        Q_PROPERTY(QString fileName READ fileName NOTIFY fileNameChanged)
        Q_PROPERTY(QString shortFileName READ shortFileName NOTIFY shortFileNameChanged)
        Q_PROPERTY(QString defaultSuffix READ defaultSuffix WRITE setDefaultSuffix NOTIFY defaultSuffixChanged)

    public:
        explicit FileDialog(QObject *parent = nullptr);

        const QStringList &nameFilters(void) const;
        void setNameFilters(const QStringList &filters);

        bool showAllFiles(void) const;
        void setShowAllFiles(bool value);

        const QString &fileName(void) const;
        QString shortFileName(void) const;

        const QString &defaultSuffix() const;
        void setDefaultSuffix(const QString &newDefaultSuffix);

        Q_INVOKABLE void getOpenFileContent(void);
        Q_INVOKABLE QString getOpenFileName(void) const;
        Q_INVOKABLE QString getSaveFileName() const;

    private:
        QString getFilters() const;

        QStringList m_nameFilters;
        bool m_showAllFiles = true;
        QString m_fileName;
        QString m_defaultSuffix;

    signals:
        void nameFiltersChanged();
        void showAllFilesChanged();
        void fileNameChanged();
        void shortFileNameChanged();
        void defaultSuffixChanged();
        void fileContentReady(const QByteArray &content);
};

} // namespace scratchcpp::uicomponents
