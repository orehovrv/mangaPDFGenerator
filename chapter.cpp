#include "chapter.h"

CHAPTER::CHAPTER() {
    path = "";
    name = "";

    picturesList.clear();

    picturesCount = 0;
}

void CHAPTER::setPath(QString input) {
    path = input;
}

void CHAPTER::setName(QString input) {
    name = input;
}

void CHAPTER::setPicturesList(QStringList input) {
    picturesList = input;
    picturesCount = input.count();
}

QString CHAPTER::getPath() {
    return path;
}

QString CHAPTER::getName() {
    return name;
}

QStringList CHAPTER::getPicturesList() {
    return picturesList;
}

int CHAPTER::getPicturesCount() {
    return picturesCount;
}

void CHAPTER::clear() {
    path = "";
    name = "";

    picturesList.clear();

    picturesCount = 0;
}
