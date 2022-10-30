#ifndef CHAPTER_H
#define CHAPTER_H

#include <QStringList>

class CHAPTER {
    private:
        QString path, name;
        QStringList picturesList;

        int picturesCount;

    public:
        CHAPTER();

        void setPath(QString);
        void setName(QString);
        void setPicturesList(QStringList);

        QString getPath();
        QString getName();
        QStringList getPicturesList();
        int getPicturesCount();

        void clear();
};

#endif // CHAPTER_H
