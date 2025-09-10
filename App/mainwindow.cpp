#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPluginLoader>
#include <QDir>
#include <QDebug>
#include "iplugin.h"
#include "appcontext.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 设置初始 xyz 值
    AppContext::instance().setValue("x", 1.23);
    AppContext::instance().setValue("y", 4.56);
    AppContext::instance().setValue("z", 7.89);

    // 监听变化（比如插件修改了数据，主程序就能更新 UI）
    connect(&AppContext::instance(), &AppContext::dataChanged,
            this, [this](const QString& key, const QVariant& value) {
        qDebug() << "主程序收到数据变化:" << key << "=" << value;
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked(){
    // 假设插件放在可执行文件同目录的 "plugins" 子目录
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins");
    QString pluginPath = pluginsDir.absoluteFilePath("myplugin.dll"); // Windows
    QPluginLoader loader(pluginPath);
    QObject* plugin = loader.instance();
    if (!plugin) {
        qDebug() << "加载插件失败:" << loader.errorString();
        return;
    }

    IPlugin* iPlugin = qobject_cast<IPlugin*>(plugin);
    if (iPlugin) {
        QWidget* w = iPlugin->createWidget(this);
        w->setAttribute(Qt::WA_DeleteOnClose);
        w->show();
    } else {
        qDebug() << "插件不是 IPlugin 类型";
    }
}
