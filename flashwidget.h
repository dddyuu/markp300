#ifndef FLASHWIDGET_H
#define FLASHWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>
#include "parallelportcontroller.h"
#include <algorithm>

namespace Ui {
class FlashWidget;
}

class FlashWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FlashWidget(QWidget *parent = nullptr);
    ~FlashWidget();
    void resetWindow();

public slots:
    void startFlashing(int flashInterval, int flashDuration, int maxFlashes, short portAddress);

private slots:
    void toggleTextVisibility();

private:
    QLabel* m_label;
    QPixmap m_pixmap;
    QTimer* m_timer;
    bool m_isVisible;
    int m_flashInterval;
    int m_flashDuration;
    int m_maxFlashes;
    int m_currentFlashes;
    int m_currentIndex;
    int PORT_ADDRESS;
    ParallelPortController* m_portController;
    static constexpr short START_DATA = 0xAA;  // 固定开始信号
    static constexpr short END_DATA = 0x55;    // 固定结束信号
    static constexpr short GRAY_DATA = 0x99;  // 固定灰色信号
    static constexpr short COLOR_DATA = 0x22;    // 固定颜色信号

    QList<int> m_imageSequence;     //显示序列
    QPixmap m_pixmap1;
    QPixmap m_pixmap2;
protected:
    void closeEvent(QCloseEvent* event) override;
private:
    Ui::FlashWidget *ui;
};

#endif // FLASHWIDGET_H
