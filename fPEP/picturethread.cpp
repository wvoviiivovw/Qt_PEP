#include "picturethread.h"

PictureThread::PictureThread()
{

}

PictureThread::PictureThread(QImage value)
{
    editing = value;
}

void PictureThread::negativeThread(int z, int f, int x,int y)
{
    mtx.lock();
        for(int i = z /*0*/; i < x; ++i)    //по ширине позиция
        {
            for(int j = f/*0*/; j < y; ++j) //по высоте позиция
            {
                QRgb old_color = editing.pixel(i, j);
                old_color = qRgb(0xFF - qRed(old_color), 0xFF - qGreen(old_color), 0xFF - qBlue(old_color));
                editing.setPixel(i, j, old_color);
            }
        }
    mtx.unlock();
}

void PictureThread::blurThread(int z, int f, int x,int y)
{
    mtx.lock();
            for(int i = z/*1*/; i < x; ++i) //по ширине позиция
            {
                for(int j = f/*1*/; j < y; ++j)  //по высоте позиция
                {
                    QRgb old_color = editing.pixel(i, j);
                    int red = qRed(old_color);
                    int blue = qBlue(old_color);
                    int green = qGreen(old_color);
                    red = (red * 4 + qRed(editing.pixel(i-1,j)) * 2 + qRed(editing.pixel(i+1,j)) * 2
                          + qRed(editing.pixel(i,j-1)) * 2 + qRed(editing.pixel(i,j+1)) * 2
                          + qRed(editing.pixel(i-1,j-1)) + qRed(editing.pixel(i+1,j+1))
                          + qRed(editing.pixel(i-1,j+1)) + qRed(editing.pixel(i+1, j-1)))/16;
                    blue = (blue * 4 + qBlue(editing.pixel(i-1,j)) * 2 + qBlue(editing.pixel(i+1,j)) * 2
                          + qBlue(editing.pixel(i,j-1)) * 2 + qBlue(editing.pixel(i,j+1)) * 2
                          + qBlue(editing.pixel(i-1,j-1)) + qBlue(editing.pixel(i+1,j+1))
                          + qBlue(editing.pixel(i-1,j+1)) + qBlue(editing.pixel(i+1, j-1)))/16;
                    green = (green * 4 + qGreen(editing.pixel(i-1,j)) * 2 + qGreen(editing.pixel(i+1,j)) * 2
                          + qGreen(editing.pixel(i,j-1)) * 2 + qGreen(editing.pixel(i,j+1)) * 2
                          + qGreen(editing.pixel(i-1,j-1)) + qGreen(editing.pixel(i+1,j+1))
                          + qGreen(editing.pixel(i-1,j+1)) + qGreen(editing.pixel(i+1, j-1)))/16;
                    if(red > 0xFF) red = 0xEF;
                    if(red < 0) red = 0;
                    if(green > 0xFF) green = 0xEF;
                    if(green < 0) green = 0;
                    if(blue > 0xFF) blue = 0xEF;
                    if(blue < 0 ) blue = 0;
                    old_color = qRgb(red, green, blue);
                    editing.setPixel(i, j, old_color);
                }
            }
    mtx.unlock();
}

void PictureThread::sharpenThread(int z, int f, int x,int y)
{
    QImage img = editing;
    QImage out_img = img;
        for(int i = z; i < x; ++i)      //по ширине позиция
        {
            for(int j = f; j < y; ++j)      //по высоте позиция
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
  editing = out_img;
}

