#ifndef SIDEBARWIDGET_H
#define SIDEBARWIDGET_H

#include <QWidget>

class QVBoxLayout;
class QButtonGroup;

class SideBarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SideBarWidget(QWidget* parent = nullptr);

    void addItem(const QString& display_text, const QString& action_id, const QIcon &decoration);

    bool isCompactMode() const { return m_is_compact_mode; }
    void setCompactMode(bool is_compact);

signals:
    void compactModeChanged(bool is_compact);
    void resizedToCompact();

protected:
    void resizeEvent(QResizeEvent* event) override;

protected:
    void toggleCompactMode();

private:
    QVBoxLayout* m_scroll_area_contents_layout = nullptr;
    QButtonGroup* m_button_group = nullptr;
    QTimer* m_auto_compact_mode_timer = nullptr;
    bool m_is_compact_mode = false;
    int m_last_noncompact_width = 0;
};

#endif // SIDEBARWIDGET_H
