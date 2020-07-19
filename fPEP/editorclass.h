#ifndef EDITORCLASS_H
#define EDITORCLASS_H
#include <QImage>
#include "picturethread.h"

class EditorClass
{
public:
    EditorClass();
    EditorClass (QImage value);

    void setImage(QImage img);
    QImage getImage(){return editPhoto;}

    void negative(QImage value);
    void blur(QImage value);
    void sharpen(QImage value);
    int Widtg(){return editPhoto.width();}
    int Height(){return editPhoto.height();}

private:
    QImage editPhoto;

    int width;
    int height;

    void widthHeight(QImage & setXY);
};

#endif // EDITORCLASS_H
