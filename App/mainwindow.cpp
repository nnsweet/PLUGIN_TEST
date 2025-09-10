#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPluginLoader>
#include <QDir>
#include <QDebug>
#include "iplugin.h"
// #include "appcontext.h"
#include "QMessageBox"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins");
    QString pluginPath = pluginsDir.absoluteFilePath("myplugin.dll");
    qDebug() << "插件路径:" << pluginPath;
    QPluginLoader loader(pluginPath);
    QObject* plugin = loader.instance();
    if (!plugin) {
        qDebug() << "加载插件失败:" << loader.errorString();
        return;
    }

    IPlugin* iPlugin = qobject_cast<IPlugin*>(plugin);
    if (iPlugin) {

        QWidget* w = iPlugin->createWidget(this); // 不要指定 parent
        w->setAttribute(Qt::WA_DeleteOnClose);
        w->setWindowFlag(Qt::Dialog); // 让它是一个独立弹窗
        w->resize(300, 200);
        w->show();
    } else {
        qDebug() << "插件不是 IPlugin 类型";
    }
}
