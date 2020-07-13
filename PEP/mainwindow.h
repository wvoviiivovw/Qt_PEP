#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QStack>
#include <QTextStream>
#include <QInputDialog>
#include <QImage>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QImage image;

private slots:
    void on_buttonOpen_clicked(); //открытие изображения

    void on_buttonNegative_clicked(); //

    void on_buttonSharpen_clicked();

    void on_buttonBlur_clicked();
};
#endif // MAINWINDOW_H
