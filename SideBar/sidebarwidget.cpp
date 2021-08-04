#include "sidebarwidget.h"

#include <QButtonGroup>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QToolButton>
#include <QTreeView>
#include <QTimer>
#include <QLabel>

struct SideBarItem {
    QString display_text;
    QString action_id;
};

SideBarWidget::SideBarWidget(QWidget *parent) : QWidget(parent), m_button_group(new QButtonGroup(this))
{
    m_auto_compact_mode_timer = new QTimer(this);
    m_auto_compact_mode_timer->setSingleShot(true);
    m_auto_compact_mode_timer->setInterval(10000);
    connect(m_auto_compact_mode_timer, &QTimer::timeout, this, &SideBarWidget::resizedToCompact);

    auto main_layout = new QVBoxLayout();
    auto scroll_area = new QScrollArea();
    auto scroll_area_contents = new QWidget();
    m_scroll_area_contents_layout = new QVBoxLayout();
    scroll_area_contents->setLayout(m_scroll_area_contents_layout);
    scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll_area->setWidgetResizable(true);
    scroll_area->setWidget(scroll_area_contents);
/*
    auto btn = new QToolButton(scroll_area_contents);
    btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    btn->setText("Category`1");
    btn->setIconSize(QSize(24, 24));
    btn->setAutoRaise(true);
    btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
*/
    for (int i =0 ; i < 10; i++) {
        addItem(QString("Category%1").arg(i), "", QIcon(QPixmap(32,32)));
    }
    //m_scroll_area_contents_layout->addWidget(btn);
    //scroll_area_contents_layout->addWidget(new QLabel("contrents", scroll_area_contents));
    //m_scroll_area_contents_layout->addWidget(new QTreeView());
    m_scroll_area_contents_layout->addStretch(1);

    auto mode_button = new QToolButton(this);
    mode_button->setText(">>");
    main_layout->addWidget(scroll_area);
    main_layout->addWidget(mode_button);
    connect(mode_button, &QToolButton::clicked, this, &SideBarWidget::toggleCompactMode);

    scroll_area_contents->show();

    setLayout(main_layout);
}

void SideBarWidget::addItem(const QString& display_text, const QString& action_id, const QIcon& decoration) {
    auto btn = new QToolButton();
    btn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    btn->setText("    " + display_text);
    btn->setIconSize(QSize(32, 32));
    btn->setIcon(decoration);
    btn->setAutoRaise(true);
    btn->setCheckable(true);
    btn->setAutoExclusive(true); // or use QButtonGroup
    btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    btn->setToolTip(display_text);
    //btn->setStyleSheet("text-align:left;");

    m_scroll_area_contents_layout->addWidget(btn);
    m_button_group->addButton(btn, -1); // TODO : add ID
}

void SideBarWidget::toggleCompactMode() {
    setCompactMode(!m_is_compact_mode);
}

void SideBarWidget::setCompactMode(bool is_compact) {
    m_is_compact_mode = is_compact;

    const auto buttons = m_button_group->buttons();
    for (const auto& btn : qAsConst(buttons)) {
        auto tool_btn = qobject_cast<QToolButton*>(btn);
        if (tool_btn) {
//            tool_btn->setToolButtonStyle(m_is_compact_mode ? Qt::ToolButtonIconOnly
//                                                           : Qt::ToolButtonTextBesideIcon);
            tool_btn->setText(m_is_compact_mode ? QString{} : QString("    ") + "Return text");
        }
    }

    if (m_is_compact_mode) {
        m_last_noncompact_width = width();
        //setGeometry(m_is_compact_mode ? 32 : sizeHint().width());
    //resize(m_is_compact_mode ? 32 : sizeHint().width(), height());
    //updateGeometry();
    }

    compactModeChanged(m_is_compact_mode);
}

void SideBarWidget::resizeEvent(QResizeEvent* event) {
    if (!m_is_compact_mode && width() < 150) {
        setCompactMode(true);
 //       m_auto_compact_mode_timer->start();
    }
    if (m_is_compact_mode && width() > 150) {
       setCompactMode(false);
    }
    QWidget::resizeEvent(event);
}
