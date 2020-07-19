#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include "editorclass.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonOpen_clicked();

    void on_buttonSave_clicked();

    void on_buttonNegative_clicked();

    void on_buttonBlur_clicked();

    void on_buttonSharpen_clicked();

private:
    Ui::MainWindow *ui;
    QImage image;
    QImage shImage;
    EditorClass engine;
};
#endif // MAINWINDOW_H
