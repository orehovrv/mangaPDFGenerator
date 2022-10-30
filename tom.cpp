#include "tom.h"

TOM::TOM() {
    path = "";
    name = "";

    chaptersList.clear();

    chaptersCount = 0;
}

void TOM::setPath(QString input) {
    path = input;
}

void TOM::setName(QString input) {
    name = input;
}

void TOM::append(CHAPTER input) {
    chaptersList.append(input);
    chaptersCount = chaptersList.count();
}

QString TOM::getPath() {
    return path;
}

QString TOM::getName() {
    return name;
}

CHAPTER TOM::at(int index) {
    return chaptersList.at(index);
}

int TOM::getChaptersCount() {
    return chaptersCount;
}

QStringList TOM::getChaptersNameList() {
    QStringList temp;
    for(int i = 0; i < chaptersList.count(); i++)
        temp.append(chaptersList[i].getName());
    return temp;
}

void TOM::clear() {
    path = "";
    name = "";

    for(int i = 0; i < chaptersList.count(); i++)
        chaptersList[i].clear();

    chaptersList.clear();

    chaptersCount = 0;
}
