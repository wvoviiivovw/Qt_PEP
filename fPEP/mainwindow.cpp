#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFileDialog>
#include <thread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_buttonOpen_clicked()    //открытие изображения
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Choose"),"",tr("Images(*.png *.jpg *.jpeg)"));
    if (QString::compare(filename,QString())!=0)
        {

            bool valid = image.load(filename);
            shImage = image;
            if(valid)
            {
                image = image.scaledToWidth(ui->label_img->width(),Qt::SmoothTransformation);
                ui->label_img->setPixmap(QPixmap::fromImage(image));
            }
        }
}

void MainWindow::on_buttonSave_clicked()   //сохранение изображения
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save Image File"), QString(),tr("Images (*.png *.jpeg *.jpg"));
        if (!fileName.isEmpty())
        {
            shImage.save(fileName);
        }
}

void MainWindow::on_buttonNegative_clicked() //передаем в класс обработки изображение, инвертирую цвет и возвращаем обратно
{
    engine.negative(shImage);
    shImage = engine.getImage();
    image = shImage;
    image = image.scaledToWidth(ui->label_img->width(),Qt::SmoothTransformation);
    ui->label_img->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_buttonBlur_clicked() //передаем в класс обработки изображение, размываем и возвращаем
{
    engine.blur(shImage);
    shImage = engine.getImage();
    image = shImage;
    image = image.scaledToWidth(ui->label_img->width(),Qt::SmoothTransformation);
    ui->label_img->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_buttonSharpen_clicked() //передаем в класс обработки изображение, увеличиваем резкость и возвращаем
{
    engine.sharpen(shImage);
    shImage = engine.getImage();
    image = shImage;
    image = image.scaledToWidth(ui->label_img->width(),Qt::SmoothTransformation);
    ui->label_img->setPixmap(QPixmap::fromImage(image));
}

