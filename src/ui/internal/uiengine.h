// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QObject>

#include "ui/iuiengine.h"

Q_MOC_INCLUDE(<QQuickItem>)

class QQuickItem;

namespace scratchcpp::ui
{

class UiEngine
    : public QObject
    , public IUiEngine
{
        Q_OBJECT
        Q_PROPERTY(QQuickItem *activeFocusItem READ activeFocusItem WRITE setActiveFocusItem NOTIFY activeFocusItemChanged)
        Q_PROPERTY(bool useNativeMenuBar READ useNativeMenuBar NOTIFY useNativeMenuBarChanged FINAL)

    public:
        explicit UiEngine(QObject *parent = nullptr);
        ~UiEngine();

        static std::shared_ptr<UiEngine> instance();

        QQmlEngine *qmlEngine() const override;
        void setQmlEngine(QQmlEngine *engine);

        Q_INVOKABLE QString standardButtonText(QDialogButtonBox::StandardButton button) const override;

        QQuickItem *activeFocusItem() const;
        void setActiveFocusItem(QQuickItem *newActiveFocusItem);

        bool useNativeMenuBar() const;

    signals:
        void activeFocusItemChanged();
        void useNativeMenuBarChanged();

    private:
        static std::shared_ptr<UiEngine> m_instance;
        QQmlEngine *m_qmlEngine = nullptr;
        QQuickItem *m_activeFocusItem = nullptr;
        mutable QDialogButtonBox *m_dialogButtonBox = nullptr;
};

} // namespace scratchcpp::ui
