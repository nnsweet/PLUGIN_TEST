#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPluginLoader>
#include <QDir>
#include <QDebug>
#include "iplugin.h"
#include "appcontext.h"
#include "QMessageBox"
#include "QTimer"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 连接AppContext的数据变化信号到槽函数
    connect(&AppContext::instance(), &AppContext::dataChanged,this, [this](const QString& key, const QVariant& value){
        if (key == "X") {
            m_value_x = value.toDouble();
            ui->doubleSpinBox->setValue(m_value_x);
        } else if (key == "Y") {
            m_value_y = value.toDouble();
            ui->doubleSpinBox_2->setValue(m_value_y);
        } else if (key == "Z") {
            m_value_z = value.toDouble();
            ui->doubleSpinBox_3->setValue(m_value_z);
        }
    });
    // 主程序spinbox修改同步到AppContext（修复后）
    connect(ui->doubleSpinBox, &QAbstractSpinBox::editingFinished,
            [=]() {
        // 通过控件自身获取当前值
        AppContext::instance().setValue("X", ui->doubleSpinBox->value());
    });
    connect(ui->doubleSpinBox_2, &QAbstractSpinBox::editingFinished,
            [=]() {
        AppContext::instance().setValue("Y", ui->doubleSpinBox_2->value());
    });
    connect(ui->doubleSpinBox_3, &QAbstractSpinBox::editingFinished,
            [=]() {
        AppContext::instance().setValue("Z", ui->doubleSpinBox_3->value());
    });

    // 主程序MainWindow构造函数中
    qDebug() << "主程序AppContext地址:" << &AppContext::instance();

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

