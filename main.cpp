#include "installer.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
#if defined(Q_OS_LINUX)
    // Check if this program is executed as root
    QProcess lsblk;
    lsblk.start(QString("whoami"), QIODevice::ReadOnly);
    lsblk.waitForStarted();
    lsblk.waitForFinished();
    QString output = lsblk.readLine();
    if (!output.contains("root")) {
        qDebug () << "Not executed as root! Closing...";
        QMessageBox::StandardButton nonRoot = QMessageBox::warning(NULL,"Insufficient privileges", "Please execute as root!",QMessageBox::Ok);
        if (nonRoot == QMessageBox::Ok) {
            return 0;
        }
    }
#endif

    Installer w;
    w.setWindowTitle("XBian installer (version 1.0)");
    w.show();
    return a.exec();
}
