#ifndef TOM_H
#define TOM_H

#include "chapter.h"

class TOM {
    private:
        QString path, name;
        QList <CHAPTER> chaptersList;

        int chaptersCount;

    public:
        TOM();

        void setPath(QString);
        void setName(QString);
        void append(CHAPTER);

        QString getPath();
        QString getName();
        CHAPTER at(int);
        int getChaptersCount();
        QStringList getChaptersNameList();

        void clear();
};

#endif // TOM_H
