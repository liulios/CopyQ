/*
    Copyright (c) 2015, Lukas Holecek <hluk@email.cz>

    This file is part of CopyQ.

    CopyQ is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    CopyQ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with CopyQ.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TRAYMENU_H
#define TRAYMENU_H

#include <QMenu>
#include <QPointer>
#include <QTimer>

class QModelIndex;

class TrayMenu : public QMenu
{
    Q_OBJECT
public:
    explicit TrayMenu(QWidget *parent = NULL);

    /** Show/hide menu. */
    void toggle();

    /**
     * Add clipboard item action with number key hint.
     *
     * Triggering this action emits clipboardItemActionTriggered() signal.
     */
    void addClipboardItemAction(const QModelIndex &index, bool showImages, bool isCurrent);

    /** Add custom action. */
    void addCustomAction(QAction *action);

    /** Clear clipboard item actions and curstom actions. */
    void clearAllActions();

    /** Select first enabled menu item. */
    void setActiveFirstEnabledAction();

signals:
    /** Emitted if numbered action triggered. */
    void clipboardItemActionTriggered(uint clipboardItemHash, bool omitPaste);

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void onClipboardItemActionTriggered();
    void onActionHovered(QAction *action);
    void updateTooltip();

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    void resetSeparators();

    QPointer<QAction> m_clipboardItemActionsSeparator;
    QPointer<QAction> m_customActionsSeparator;
    int m_clipboardItemActionCount;

    QTimer m_timerShowTooltip;

    bool m_omitPaste;
};

#endif // TRAYMENU_H
