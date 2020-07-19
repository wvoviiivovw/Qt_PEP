#ifndef PICTURETHREAD_H
#define PICTURETHREAD_H
#include <QImage>
#include <mutex>

class PictureThread
{
public:
    PictureThread();
    PictureThread(QImage value);

    void negativeThread(int z, int f, int x,int y); //int w, int h, int ii,int jj
    void blurThread(int z, int f, int x,int y);
    void sharpenThread(int z, int f, int x,int y);
    QImage getImage(){return editing;}

private:
    QImage editing;
    std::mutex mtx;
};

#endif // PICTURETHREAD_H
