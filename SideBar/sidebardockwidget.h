#ifndef SIDEBARDOCKWIDGET_H
#define SIDEBARDOCKWIDGET_H

#include <QDockWidget>

class SideBarWidget;

class SideBarDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    SideBarDockWidget(QWidget* parent = nullptr);

//protected:
//    void mousePressEvent(QMouseEvent* event) override;
//    void mouseReleaseEvent(QMouseEvent* event) override;
//    bool event(QEvent* event) override;

protected:
    void resizeEvent(QResizeEvent* event) override;
    bool eventFilter(QObject *obj, QEvent *ev) override;

private:
    SideBarWidget* m_side_bar = nullptr;
    QMainWindow* m_main_window = nullptr;

    bool m_is_dragging = false;
    bool m_resized_to_compact = false;

    int m_last_width = 0;
};

#endif // SIDEBARDOCKWIDGET_H
