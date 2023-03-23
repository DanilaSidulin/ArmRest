#include "login.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    QString path = "C:/Users/User/Documents/untitled/qtbase_ru.qm";
    if (translator.load(path)) {
        a.installTranslator(&translator);
    }
    else
        {
            qDebug() << "Ошибка загрузки языка!";
        }

    qApp->setStyle(QStyleFactory::create("Fusion"));

    Login w;
    w.show();
    w.setWindowTitle("АРМ Вход");
    return a.exec();
}
