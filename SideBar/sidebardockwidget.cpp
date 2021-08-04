#include "sidebardockwidget.h"
#include "sidebarwidget.h"

#include <QMainWindow>
#include <QEvent>
#include <QDebug>

namespace {
const int CompactModeAutoToggleWidth = 150; // TODO : calc on minsize or compactsize
} // namespace

SideBarDockWidget::SideBarDockWidget(QWidget* parent) : QDockWidget(parent), m_side_bar(new SideBarWidget(this))
{
    m_main_window = qobject_cast<QMainWindow*>(this->parent());
    if (m_main_window) {
        m_main_window->installEventFilter(this);
    }

    setFloating(false);
    setFeatures(QDockWidget::NoDockWidgetFeatures);
    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    setTitleBarWidget(new QWidget(this));
    setWidget(m_side_bar);

    connect(m_side_bar, &SideBarWidget::resizedToCompact, this, [this]() {
        bool is_compact = true;
        auto main_window = qobject_cast<QMainWindow*>(this->parent());
        if (main_window) {
            main_window->resizeDocks({this}, QList<int>{} <<(is_compact ? 32 : m_last_width), Qt::Horizontal );
        }
    });


    connect(m_side_bar, &SideBarWidget::compactModeChanged, this, [this](bool is_compact) {
        //ui->dockWidget->resize(is_compact ? 32 : 150, ui->dockWidget->height());
        //if (is_compact) {
            //m_last_noncompact_width = width(); // TODO in Dock
            if (m_is_dragging) {
                m_resized_to_compact = is_compact;
            }
//        }
//        else {

//        }
        auto main_window = qobject_cast<QMainWindow*>(this->parent());
        if (main_window) {
            main_window->resizeDocks({this}, QList<int>{} <<(is_compact ? 32 : m_last_width), Qt::Horizontal );
        }
    });
}

//void SideBarDockWidget::mousePressEvent(QMouseEvent* event) {
//    qDebug() << "SideBarDockWidget::mousePressEvent()";
//}

//void SideBarDockWidget::mouseReleaseEvent(QMouseEvent* event) {
//    qDebug() << "SideBarDockWidget::mouseReleaseEvent()";
//}

//bool SideBarDockWidget::event(QEvent* e) {
//    if (e->type() == QEvent::MouseButtonRelease) {
//        qDebug() << "SideBarDockWidget::EVENT RELEASE";
//    }
//    return QWidget::event(e);
//}

bool SideBarDockWidget::eventFilter(QObject* obj, QEvent *event) {
    if (obj == m_main_window) {
        if (event->type() == QEvent::MouseButtonPress) {
            //QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            //qDebug() << "Ate key press" << keyEvent->key();
        //    return true;
            m_is_dragging = true;
        }
        else if (event->type() == QEvent::MouseButtonRelease) {
            //QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            //qDebug() << "Ate key press" << keyEvent->key();
        //    return true;
            if (m_is_dragging) {

            m_is_dragging = false;
            if (m_resized_to_compact) {
                m_resized_to_compact = false;
                bool is_compact = true;
                auto main_window = qobject_cast<QMainWindow*>(this->parent());
                if (main_window) {
                    main_window->resizeDocks({this}, QList<int>{} <<(is_compact ? 32 : m_last_width), Qt::Horizontal );
                }
            }
            else {
                m_last_width = width();
            }
            }
        }

       //     return false;
    }

    // pass the event on to the parent class
    return QDockWidget::eventFilter(obj, event);
}

void SideBarDockWidget::resizeEvent(QResizeEvent* event) {
    //m_last_width = width();

    if (!m_side_bar->isCompactMode() && width() < CompactModeAutoToggleWidth) {
        m_side_bar->setCompactMode(true);
 //       m_auto_compact_mode_timer->start();
    }
    if (m_side_bar->isCompactMode() && width() > CompactModeAutoToggleWidth) {
       m_side_bar->setCompactMode(false);
    }
    QWidget::resizeEvent(event);
}
