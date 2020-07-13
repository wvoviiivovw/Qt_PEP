#include "mainwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::on_buttonOpen_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Choose"),"",tr("Images(*.png *.jpg *.jpeg)"));
    if (QString::compare(filename,QString())!=0)
    {

        bool valid = image.load(filename);
        if(valid)
        {
            image = image.scaledToWidth(ui->label_img->width(),Qt::SmoothTransformation);
            ui->label_img->setPixmap(QPixmap::fromImage(image));
        }
    }
}

void MainWindow::on_buttonNegative_clicked()
{
    QImage img = image;
    for(int i = 0; i < img.width(); ++i)
    {
        for(int j = 0; j < img.height(); ++j)
        {
            QRgb old_color = img.pixel(i, j);
            old_color = qRgb(0xFF - qRed(old_color), 0xFF - qGreen(old_color), 0xFF - qBlue(old_color));
            img.setPixel(i, j, old_color);
        }
    }
    image = img;
    ui->label_img->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_buttonSharpen_clicked()
{
    QImage img = image;
    QImage out_img = img;
    for(int i = 1; i < img.width() - 1; ++i)
    {
        for(int j = 1; j < img.height() - 1; ++j)
        {
            QRgb old_color = img.pixel(i, j);
            int red = qRed(old_color);
            int blue = qBlue(old_color);
            int green = qGreen(old_color);
            red = 5 * red - qRed(img.pixel(i-1,j)) -qRed(img.pixel(i+1,j)) -qRed(img.pixel(i,j-1)) -qRed(img.pixel(i,j+1));
            blue = 5 * blue - qBlue(img.pixel(i-1,j)) -qBlue(img.pixel(i+1,j)) -qBlue(img.pixel(i,j-1)) -qBlue(img.pixel(i,j+1));
            green = 5 * green - qGreen(img.pixel(i-1,j)) -qGreen(img.pixel(i+1,j)) -qGreen(img.pixel(i,j-1)) -qGreen(img.pixel(i,j+1));
            if(red > 0xFF) red = 0xEF;
            if(red < 0) red = 0;
            if(green > 0xFF) green = 0xEF;
            if(green < 0) green = 0;
            if(blue > 0xFF) blue = 0xEF;
            if(blue < 0 ) blue = 0;
            old_color = qRgb(red, green, blue);
            out_img.setPixel(i, j, old_color);
        }
    }
    image = out_img;
    ui->label_img->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_buttonBlur_clicked()
{
    QImage img = image;
    QImage out_img = img;
    for(int i = 1; i < img.width() - 1; ++i)
    {
        for(int j = 1; j < img.height() - 1; ++j)
        {
            QRgb old_color = img.pixel(i, j);
            int red = qRed(old_color);
            int blue = qBlue(old_color);
            int green = qGreen(old_color);
            red = (red * 4 + qRed(img.pixel(i-1,j)) * 2 + qRed(img.pixel(i+1,j)) * 2
                  + qRed(img.pixel(i,j-1)) * 2 + qRed(img.pixel(i,j+1)) * 2
                  + qRed(img.pixel(i-1,j-1)) + qRed(img.pixel(i+1,j+1))
                  + qRed(img.pixel(i-1,j+1)) + qRed(img.pixel(i+1, j-1)) )/16;
            blue = (blue * 4 + qBlue(img.pixel(i-1,j)) * 2 + qBlue(img.pixel(i+1,j)) * 2
                  + qBlue(img.pixel(i,j-1)) * 2 + qBlue(img.pixel(i,j+1)) * 2
                  + qBlue(img.pixel(i-1,j-1)) + qBlue(img.pixel(i+1,j+1))
                  + qBlue(img.pixel(i-1,j+1)) + qBlue(img.pixel(i+1, j-1)) )/16;
            green = (green * 4 + qGreen(img.pixel(i-1,j)) * 2 + qGreen(img.pixel(i+1,j)) * 2
                  + qGreen(img.pixel(i,j-1)) * 2 + qGreen(img.pixel(i,j+1)) * 2
                  + qGreen(img.pixel(i-1,j-1)) + qGreen(img.pixel(i+1,j+1))
                  + qGreen(img.pixel(i-1,j+1)) + qGreen(img.pixel(i+1, j-1)) )/16;
            if(red > 0xFF) red = 0xEF;
            if(red < 0) red = 0;
            if(green > 0xFF) green = 0xEF;
            if(green < 0) green = 0;
            if(blue > 0xFF) blue = 0xEF;
            if(blue < 0 ) blue = 0;
            old_color = qRgb(red, green, blue);
            out_img.setPixel(i, j, old_color);
        }
    }
    image = out_img;
    ui->label_img->setPixmap(QPixmap::fromImage(image));
}

