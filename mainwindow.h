#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>

#include <QMainWindow>
#include <QDebug>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QListWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QStatusBar>

#include <QList>
#include <QPixmap>

#include <QStringLiteral>
#include <QFileDialog>
#include <QDir>

#include <QPrinter>
#include <QPdfWriter>
#include <QPainter>

#include "chapter.h"
#include "tom.h"

bool compareChapters(const QString &, const QString &);
bool compareToms(QString, QString);

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
        Q_OBJECT

        QWidget * centralWidget;
        QWidget * imageLabelWidget;

        QStatusBar * statusbar;

        QVBoxLayout * mainVerticalLayout;
        QVBoxLayout * seriesChaptersVerticalLayout;
        QVBoxLayout * settingsVerticalLayout;
        QVBoxLayout * imageLabelVerticalLayout;

        QHBoxLayout * horizontalLayout;
        QHBoxLayout * settingsChaptersHorizontalLayout;
        QHBoxLayout * widthHorizontalLayout;
        QHBoxLayout * ratioHorizontalLayout;
        QHBoxLayout * imageLabelHorizontalLayout;

        QListWidget * seriesListWidget;
        QListWidget * tomsListWidget;
        QListWidget * chaptersListWidget;
        QListWidget * picturesListWidget;
        QListWidget * messagesListWidget;

        QPushButton * openDirPushButton;
        QPushButton * openMangaPushButton;
        QPushButton * oneTomPushButton;
        QPushButton * allTomsPushButton;
        QPushButton * allSeriesPushButton;

        QCheckBox * coversCheckBox;
        QCheckBox * contentsCheckBox;
        QCheckBox * chaptersCheckBox;
        QCheckBox * chaptersSortCheckBox;
        QCheckBox * tomsCheckBox;
        QCheckBox * scaleCheckBox;
        QCheckBox * ratioCheckBox;

        QLabel * imageLabel;
        QLabel * widthLabel;
        QLabel * ratioLabel;

        QLineEdit * widthLineEdit;
        QLineEdit * ratioLineEdit;

    private:
        Ui::MainWindow * ui;

        QPixmap image, imageTemp;
        int scaleWidthImage = 1264;

        QStringList seriesNameList, tomsNameList, chaptersNameList, picturesNameList;
        QString sPath, mPath, mName, lastPathToImage;
        QDir mDir, sDir, tDir;

        QList <TOM> tomsList;
        int picturesCount, maxNumberTom;

        TOM tomTemp;
        CHAPTER chapterTemp;

        bool coversFlag;
        bool sortFlag;
        bool tomsFlag;
        bool contentsFlag;
        bool chaptersFlag;
        bool scaleFlag;
        bool ratioFlag;

        const double tolerance = 0.3;
        double ratio = 1.30063;

        const int pageWidth = 148;
        int pageHeigth = ceil(pageWidth * ratio);

        const int imageLabelWidgetMaxHeight = 650;
        int imageLabelWidgetMaxWidth = ceil(imageLabelWidgetMaxHeight / ratio);


        void disableAllWidget();
        void enableAllWidget();

        int lengNumber(int);

        void loadImage(QString);

        void loadSeries();
        int createOneTom(int);

    private slots:
        void coversCheckBox_clicked();
        void contentsCheckBox_clicked();
        void chaptersCheckBox_clicked();
        void chaptersSortCheckBox_clicked();
        void tomsCheckBox_clicked();
        void scaleCheckBox_clicked();
        void ratioCheckBox_clicked();

        void widthLineEdit_editingFinished();
        void ratioLineEdit_editingFinished();

        void seriesListWidget_itemClicked();
        void tomsListWidget_itemClicked();
        void chapterListWidget_itemClicked();
        void picturesListWidget_itemClicked();

        void openDirPushButton_clicked();
        void openMangaPushButton_clicked();
        void oneTomPushButton_clicked();
        void allTomsPushButton_clicked();
        void allSeriesPushButton_clicked();

    public:
        MainWindow(QWidget * parent = nullptr);
        ~MainWindow();
};
#endif // MAINWINDOW_H
