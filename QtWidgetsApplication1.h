// QtWidgetsApplication1.h
#pragma once

#include <QtWidgets/QMainWindow>
#include <QPixmap>
#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>
#include "parallelportcontroller.h"
#include <algorithm>
#include <QImageReader>
class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(short portAddress,QWidget* parent = nullptr);
    ~QtWidgetsApplication1();

    void resetWindow();
signals:
    void endFlashsing();
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
    static constexpr short START_DATA = 0x00;  // �̶���ʼ�ź�
    static constexpr short END_DATA = 0xff;    // �̶������ź�
    static constexpr short GRAY_DATA = 0x01;  // �̶���ɫ�ź�
    static constexpr short COLOR_DATA = 0x02;    // �̶���ɫ�ź�

    QList<int> m_imageSequence;     //��ʾ����
    QPixmap m_pixmap1;
    QPixmap m_pixmap2;
protected:
    void closeEvent(QCloseEvent* event) override;
};
