#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    // 新增：处理数据变化的槽函数
    void onDataChanged(const QString& key, const QVariant& value);


    
private:
    Ui::MainWindow *ui;
    double m_value_x = 0;
    double m_value_y = 0;
    double m_value_z = 0;

};

#endif // MAINWINDOW_H
