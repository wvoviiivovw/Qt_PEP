#include "editorclass.h"
#include <QtDebug>
#include "picturethread.h"
#include <thread>

EditorClass::EditorClass()
{

}

EditorClass::EditorClass(QImage value)
{
    editPhoto = value;
}

void EditorClass::setImage(QImage img)
{
    editPhoto = img;
}

void EditorClass::negative(QImage value)
{
    widthHeight(value);
    int numThreads = 4;                //кол-во потоков
    PictureThread pic(value);
    int sector = (width+1)/numThreads;
    std::thread one([&]()
    {
        pic.negativeThread(0,0,sector,height+1);
    });

    std::thread two([&]()
    {
        pic.negativeThread(sector,0,sector*2,height+1);
    });

    std::thread three([&]()
    {
        pic.negativeThread(sector*2,0,sector*3,height+1);
    });
    std::thread four([&]()
    {
        pic.negativeThread(sector*3,0,width+1,height+1);
    });

    one.join();
    two.join();
    three.join();
    four.join();
    editPhoto = pic.getImage();

    /*    for (int  i= 0; i <= numThreads-1; ++i )                  thread[0]-dont work!
    {
        if (i+1 != numThreads)
        {
                th[i]=std::thread([&]()
                {
                    pic.negativeThread(sector*i,0,sector*(i+1),height+1);
                });
        }
        else
        {
            th[i]=std::thread([&]()
            {
               pic.negativeThread(sector*i,0,width+1,height+1);
            });
        }
    }
    for (int  i= 0; i <= numThreads-1; ++i )
    {
        th[i].join();
    }
*/
}

void EditorClass::blur(QImage value)
{
    widthHeight(value);
    int numThreads = 4;                //кол-во потоков
    PictureThread pic(value);
    int sector = (width+1)/numThreads;
    std::thread one([&]()
    {
        pic.blurThread(1,1,sector,height);
    });

    std::thread two([&]()
    {
        pic.blurThread(sector,1,sector*2,height);
    });

    std::thread three([&]()
    {
        pic.blurThread(sector*2,1,sector*3,height);
    });
    std::thread four([&]()
    {
        pic.blurThread(sector*3,1,width,height);
    });

    one.join();
    two.join();
    three.join();
    four.join();

    editPhoto = pic.getImage();
}

void EditorClass::sharpen(QImage value)
{
    widthHeight(value);
    PictureThread pic(value);
    std::thread one([&]()
    {
        pic.sharpenThread(1,1,width,height);
    });
    one.join();
    editPhoto = pic.getImage();
}

void EditorClass::widthHeight(QImage & setXY)
{
    width = setXY.width()-1;
    height = setXY.height()-1;
}

