#include "QtWidgetsApplication1.h"
#include "SettingsWindow.h"
#include <QtWidgets/QApplication>
#include <QPointer> 
#include <QDebug>
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    SettingsWindow settingsWindow;
    settingsWindow.show();

    // ʹ������ָ�������������������
    QPointer<QtWidgetsApplication1> flashWindow;

    // ���� settingsConfirmed �ź�
    QObject::connect(&settingsWindow, &SettingsWindow::settingsConfirmed,
        [&settingsWindow, &flashWindow](int interval, int duration, int flashes, short port) {
            QPointer<QtWidgetsApplication1> oldFlashWindow = flashWindow;
            if (oldFlashWindow) {
                oldFlashWindow->deleteLater();
            }
            flashWindow = new QtWidgetsApplication1(port, &settingsWindow);
            QObject::connect(flashWindow, &QtWidgetsApplication1::destroyed,
                [&flashWindow]() {
                    qDebug() << "Flash window destroyed";
                    flashWindow.clear();
                });

            flashWindow->startFlashing(interval, duration, flashes, port);
            flashWindow->show();
        });


    return a.exec();
}
