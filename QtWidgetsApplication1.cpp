#include "QtWidgetsApplication1.h"
#include <QTimerEvent>
#include <QApplication>
#include <QCloseEvent>
#include <QDebug>
#include "SettingsWindow.h"
#include <QRandomGenerator>



QtWidgetsApplication1::QtWidgetsApplication1(short portAddress, QWidget* parent)
    : QMainWindow(parent),
    PORT_ADDRESS(portAddress),
    m_flashInterval(500),
    m_flashDuration(300),
    m_maxFlashes(10),
    m_isVisible(true),
    m_currentFlashes(0),
    m_portController(new ParallelPortController(this)),
    m_currentIndex(0),
    m_label(nullptr),     // 初始化时置空
    m_timer(nullptr)      // 初始化时置空

{
    m_pixmap1.load("./res/1_output_135_degree.png");
    m_pixmap2.load("./res/1_red_output_135_degree.png");
}

QtWidgetsApplication1::~QtWidgetsApplication1()
{

    // 清理动态分配的资源
    if (m_label) delete m_label;
    if (m_timer) delete m_timer;
}

void QtWidgetsApplication1::startFlashing(int flashInterval, int flashDuration, int maxFlashes, short portAddress)
{   
    
    PORT_ADDRESS = portAddress;

    // 发送开始信号
    if (m_portController->isAvailable()) {
        m_portController->sendData(PORT_ADDRESS, START_DATA);
    }
    // 设置闪烁参数
    
    m_flashInterval = flashInterval;
    m_flashDuration = flashDuration;
    m_maxFlashes = maxFlashes;
    m_currentFlashes = 0;  // 重置计数器
    m_currentIndex = 0;

    // 设置窗口为全屏
    setWindowState(Qt::WindowFullScreen);
    setStyleSheet("background-color: black;");

    // 创建图片显示标签
    m_label = new QLabel(this);
    m_label->setAlignment(Qt::AlignCenter);
    m_label->setPixmap(m_pixmap1.scaled(800, 800, Qt::KeepAspectRatio));

    // 设置布局，保证标签居中
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(m_label);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);



    // 生成图片序列
    int image1_count = static_cast<int>(m_maxFlashes * 0.8);
    int image2_count = m_maxFlashes - image1_count;

    QList<int> sequence;
    // 初始化所有元素为图片一（0）
    for (int i = 0; i < m_maxFlashes; ++i) {
        sequence.append(0);
    }

    // 确保前两张为图片一，此处初始值已满足

    // 处理剩余位置以插入图片二（1），确保不连续
    QList<int> available_positions;
    for (int i = 2; i < m_maxFlashes; ++i) { // 从第三个位置开始
        available_positions.append(i);
    }

    QList<int> selected_positions;
    int needed = image2_count;

    while (needed > 0 && !available_positions.isEmpty()) {
        // 随机选择一个位置
        int randomIndex = QRandomGenerator::global()->bounded(available_positions.size());
        int pos = available_positions.takeAt(randomIndex);
        selected_positions.append(pos);

        // 移除相邻位置以避免连续
        int prev = pos - 1;
        int prevIndex = available_positions.indexOf(prev);
        if (prevIndex != -1) {
            available_positions.removeAt(prevIndex);
        }

        int next = pos + 1;
        int nextIndex = available_positions.indexOf(next);
        if (nextIndex != -1) {
            available_positions.removeAt(nextIndex);
        }

        needed--;
    }

    // 将选中的位置设置为图片二
    foreach(int pos, selected_positions) {
        if (pos < sequence.size()) {
            sequence[pos] = 1;
        }
    }

    m_imageSequence = sequence;
    m_currentIndex = 0; // 重置索引

    // 启动定时器进行闪烁控制
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &QtWidgetsApplication1::toggleTextVisibility);
    m_timer->start(m_flashInterval + m_flashDuration);
}

void QtWidgetsApplication1::toggleTextVisibility()
{   

    if (m_currentFlashes >= m_maxFlashes) {
        // 发送结束信号
        if (m_portController->isAvailable()) {
            m_portController->sendData(PORT_ADDRESS, END_DATA);
        }
        m_timer->stop();
        resetWindow();
        return;
    }


    // 根据概率选择图片
    int imageType = m_imageSequence.at(m_currentIndex);
    m_currentIndex++;
    if (imageType == 0) {
        m_label->setPixmap(m_pixmap1.scaled(800, 800, Qt::KeepAspectRatio));
        m_portController->sendData(PORT_ADDRESS, GRAY_DATA);
    }
    else {
        m_label->setPixmap(m_pixmap2.scaled(800, 800, Qt::KeepAspectRatio));
        m_portController->sendData(PORT_ADDRESS, COLOR_DATA);
    }

    m_currentFlashes++;
    m_label->show();

    QTimer::singleShot(m_flashDuration, [this]() {
        m_label->clear();
        });

    
}

void QtWidgetsApplication1::resetWindow()
{
    // 重置窗口状态
    m_currentFlashes = 0;
    m_currentIndex = 0;
    m_imageSequence.clear();
    if (m_label) {
        m_label->clear();
        m_label->deleteLater();
        m_label = nullptr;
    }
    if (m_timer) {
        m_timer->stop();
        m_timer->deleteLater();
        m_timer = nullptr;
    }
    hide(); // 隐藏窗口而非关闭
    deleteLater();
}
void QtWidgetsApplication1::closeEvent(QCloseEvent* event)
{
//    event->ignore(); // 阻止窗口关闭
//    hide();          // 隐藏窗口
}
