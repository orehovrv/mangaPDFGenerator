#include "mainwindow.h"
#include "ui_mainwindow.h"

QString regExpChapter = "(\\d+\\.\\d+(?![\\d]))|(\\d+(?![\\.\\d]))";
QString regExpTom = "(\\d+\\.(?![\\d]))";

bool compareChapters(const QString & s1, const QString & s2) {
    bool f1 = false, f2 = false;
    double n1, n2;

    QRegExp re(regExpChapter);

    if(re.indexIn(s1) > -1) { f1 = true; n1 = re.cap(0).toDouble(); }
    if(re.indexIn(s2) > -1) { f2 = true; n2 = re.cap(0).toDouble(); }

    if(f1 && f2) return n1 < n2;
    else if(f2) return true;
    return false;
}

bool compareToms(QString s1, QString s2) {
    return s1.toDouble() > s2.toDouble();
}

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    centralWidget = new QWidget(this);
    mainVerticalLayout = new QVBoxLayout(centralWidget);

    horizontalLayout = new QHBoxLayout();
    seriesChaptersVerticalLayout = new QVBoxLayout();

    seriesListWidget = new QListWidget(centralWidget);
    seriesListWidget->setMinimumHeight(150);
    seriesListWidget->setMaximumHeight(150);

    settingsChaptersHorizontalLayout = new QHBoxLayout();
    settingsVerticalLayout = new QVBoxLayout();

    openDirPushButton = new QPushButton(centralWidget);
    openDirPushButton->setMaximumWidth(150);
    openDirPushButton->setText("Открыть каталог");

    coversCheckBox = new QCheckBox(centralWidget);
    coversCheckBox->setMaximumWidth(150);
    coversCheckBox->setText("Наличие обложек");

    contentsCheckBox = new QCheckBox(centralWidget);
    contentsCheckBox->setMaximumWidth(150);
    contentsCheckBox->setText("Добавить оглавление");

    chaptersCheckBox = new QCheckBox(centralWidget);
    chaptersCheckBox->setMaximumWidth(150);
    chaptersCheckBox->setText("Добавить номера глав");

    chaptersSortCheckBox = new QCheckBox(centralWidget);
    chaptersSortCheckBox->setMaximumWidth(150);
    chaptersSortCheckBox->setText("Сортировать главы");

    tomsCheckBox = new QCheckBox(centralWidget);
    tomsCheckBox->setMaximumWidth(150);
    tomsCheckBox->setText("Разбить на томики");

    tomsListWidget = new QListWidget(centralWidget);
    tomsListWidget->setMaximumWidth(150);
    tomsListWidget->setMinimumHeight(imageLabelWidgetMaxHeight - seriesListWidget->height() - 364);
    tomsListWidget->setMaximumHeight(imageLabelWidgetMaxHeight - seriesListWidget->height() - 364);

    openMangaPushButton = new QPushButton(centralWidget);
    openMangaPushButton->setMaximumWidth(150);
    openMangaPushButton->setText("Открыть мангу");

    scaleCheckBox = new QCheckBox(centralWidget);
    scaleCheckBox->setMaximumWidth(150);
    scaleCheckBox->setText("Сжать картинки");

    widthHorizontalLayout = new QHBoxLayout();
    widthLabel = new QLabel(centralWidget);
    widthLabel->setText("Ширина картинок");
    widthLabel->setMaximumWidth(94);

    widthLineEdit = new QLineEdit(centralWidget);
    widthLineEdit->setAlignment(Qt::AlignCenter);
    widthLineEdit->setMaximumWidth(50);
    widthLineEdit->setValidator(new QRegExpValidator(QRegExp("[1-9][0-9]{,3}"), widthLineEdit));
    //widthLineEdit->setDisabled(true);
    widthLineEdit->setText(QString::number(scaleWidthImage));

    widthHorizontalLayout->addWidget(widthLabel);
    widthHorizontalLayout->addWidget(widthLineEdit);

    oneTomPushButton = new QPushButton(centralWidget);
    oneTomPushButton->setMaximumWidth(150);
    oneTomPushButton->setText("Один томик");

    allTomsPushButton = new QPushButton(centralWidget);
    allTomsPushButton->setMaximumWidth(150);
    allTomsPushButton->setText("Все томики серии");

    allSeriesPushButton = new QPushButton(centralWidget);
    allSeriesPushButton->setMaximumWidth(150);
    allSeriesPushButton->setText("Все серии");

    ratioCheckBox = new QCheckBox(centralWidget);
    ratioCheckBox->setMaximumWidth(150);
    ratioCheckBox->setText("Изменить соотношение");

    ratioHorizontalLayout = new QHBoxLayout();

    ratioLabel = new QLabel(centralWidget);
    ratioLabel->setText("Высота / ширина:");
    ratioLabel->setMaximumWidth(94);

    ratioLineEdit = new QLineEdit(centralWidget);
    ratioLineEdit->setAlignment(Qt::AlignCenter);
    ratioLineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]*\\.{,1}[0-9]{,5}"), widthLineEdit));
    ratioLineEdit->setText(QString::number(ratio));
    ratioLineEdit->setDisabled(true);
    ratioLineEdit->setMaximumWidth(50);

    ratioHorizontalLayout->addWidget(ratioLabel);
    ratioHorizontalLayout->addWidget(ratioLineEdit);

    settingsVerticalLayout->addWidget(openDirPushButton);
    settingsVerticalLayout->addWidget(coversCheckBox);
    settingsVerticalLayout->addWidget(contentsCheckBox);
    settingsVerticalLayout->addWidget(chaptersCheckBox);
    settingsVerticalLayout->addWidget(chaptersSortCheckBox);
    settingsVerticalLayout->addWidget(tomsCheckBox);
    settingsVerticalLayout->addWidget(tomsListWidget);
    settingsVerticalLayout->addWidget(openMangaPushButton);
    settingsVerticalLayout->addWidget(scaleCheckBox);
    settingsVerticalLayout->addLayout(widthHorizontalLayout);
    settingsVerticalLayout->addWidget(oneTomPushButton);
    settingsVerticalLayout->addWidget(allTomsPushButton);
    settingsVerticalLayout->addWidget(allSeriesPushButton);
    settingsVerticalLayout->addWidget(ratioCheckBox);
    settingsVerticalLayout->addLayout(ratioHorizontalLayout);

    settingsChaptersHorizontalLayout->addLayout(settingsVerticalLayout);

    chaptersListWidget = new QListWidget(centralWidget);
    chaptersListWidget->setMinimumWidth(300);
    chaptersListWidget->setMaximumHeight(imageLabelWidgetMaxHeight - seriesListWidget->width() - 6);

    settingsChaptersHorizontalLayout->addWidget(chaptersListWidget);

    settingsChaptersHorizontalLayout->setStretch(0, 1);
    settingsChaptersHorizontalLayout->setStretch(1, 200);

    seriesChaptersVerticalLayout->addWidget(seriesListWidget);
    seriesChaptersVerticalLayout->addLayout(settingsChaptersHorizontalLayout);

    picturesListWidget = new QListWidget(centralWidget);
    picturesListWidget->setMinimumSize(QSize(100, imageLabelWidgetMaxHeight));
    picturesListWidget->setMaximumSize(QSize(100, imageLabelWidgetMaxHeight));

    imageLabelWidget = new QWidget(centralWidget);
    imageLabelWidget->setMinimumSize(QSize(imageLabelWidgetMaxWidth, imageLabelWidgetMaxHeight));
    imageLabelWidget->setMaximumSize(QSize(imageLabelWidgetMaxWidth, imageLabelWidgetMaxHeight));
    imageLabelWidget->setStyleSheet("QWidget { border: 1 solid #828790; background-color: white }");

    imageLabelVerticalLayout = new QVBoxLayout(imageLabelWidget);
    imageLabelVerticalLayout->setContentsMargins(0, 0, 0, 0);
    imageLabelHorizontalLayout = new QHBoxLayout();
    imageLabelHorizontalLayout->setContentsMargins(0, 0, 0, 0);

    lastPathToImage = "D:/_Programming/Qt/mangaPDFCreatorV5/image.jpg";
    image.load(lastPathToImage);

    imageLabel = new QLabel(centralWidget);
    imageLabel->setScaledContents(true);
    imageLabel->setStyleSheet("QWidget { border: 0; background-color: white }");

    loadImage(lastPathToImage);

    imageLabelHorizontalLayout->addWidget(imageLabel);
    imageLabelVerticalLayout->addLayout(imageLabelHorizontalLayout);

    horizontalLayout->addLayout(seriesChaptersVerticalLayout);
    horizontalLayout->addWidget(picturesListWidget);
    horizontalLayout->addWidget(imageLabelWidget);

    messagesListWidget = new QListWidget(centralWidget);
    messagesListWidget->setMinimumHeight(100);

    mainVerticalLayout->addLayout(horizontalLayout);
    mainVerticalLayout->addWidget(messagesListWidget);

    statusbar = new QStatusBar(this);

    int widthWindow = 10 + oneTomPushButton->maximumWidth() + 6 + chaptersListWidget->minimumWidth() + 6 + picturesListWidget->minimumWidth() + 6 + imageLabelWidgetMaxWidth + 10;
    int heightWindow = imageLabelWidgetMaxHeight + messagesListWidget->height() + 44;

    this->setCentralWidget(centralWidget);
    this->setStatusBar(statusbar);
    //this->setGeometry((1920 - widthWindow) / 2, (1080 - heightWindow) / 2, widthWindow, heightWindow);

    coversCheckBox->setChecked(true);
    contentsCheckBox->setChecked(true);
    chaptersCheckBox->setChecked(true);
    chaptersSortCheckBox->setChecked(true);
    tomsCheckBox->setChecked(true);
    scaleCheckBox->setChecked(true);

    coversFlag = true;
    contentsFlag = true;
    chaptersFlag = true;
    sortFlag = true;
    tomsFlag = true;
    scaleFlag = true;
    ratioFlag = false;

    oneTomPushButton->setDisabled(true);
    allTomsPushButton->setDisabled(true);
    allSeriesPushButton->setDisabled(true);

    connect(coversCheckBox, SIGNAL(clicked()), this, SLOT(coversCheckBox_clicked()));
    connect(contentsCheckBox, SIGNAL(clicked()), this, SLOT(contentsCheckBox_clicked()));
    connect(chaptersCheckBox, SIGNAL(clicked()), this, SLOT(chaptersCheckBox_clicked()));
    connect(chaptersSortCheckBox, SIGNAL(clicked()), this, SLOT(chaptersSortCheckBox_clicked()));
    connect(tomsCheckBox, SIGNAL(clicked()), this, SLOT(tomsCheckBox_clicked()));
    connect(scaleCheckBox, SIGNAL(clicked()), this, SLOT(scaleCheckBox_clicked()));
    connect(ratioCheckBox, SIGNAL(clicked()), this, SLOT(ratioCheckBox_clicked()));

    connect(widthLineEdit, SIGNAL(editingFinished()), this, SLOT(widthLineEdit_editingFinished()));
    connect(ratioLineEdit, SIGNAL(editingFinished()), this, SLOT(ratioLineEdit_editingFinished()));

    connect(seriesListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(seriesListWidget_itemClicked()));
    connect(tomsListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(tomsListWidget_itemClicked()));
    connect(chaptersListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(chapterListWidget_itemClicked()));
    connect(picturesListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(picturesListWidget_itemClicked()));

    connect(openDirPushButton, SIGNAL(clicked()), this, SLOT(openDirPushButton_clicked()));
    connect(openMangaPushButton, SIGNAL(clicked()), this, SLOT(openMangaPushButton_clicked()));
    connect(oneTomPushButton, SIGNAL(clicked()), this, SLOT(oneTomPushButton_clicked()));
    connect(allTomsPushButton, SIGNAL(clicked()), this, SLOT(allTomsPushButton_clicked()));
    connect(allSeriesPushButton, SIGNAL(clicked()), this, SLOT(allSeriesPushButton_clicked()));
}

MainWindow::~MainWindow() {
    delete ui;
}

//=============================================================================================================

void MainWindow::coversCheckBox_clicked() {
    coversFlag = coversCheckBox->checkState();
    seriesListWidget_itemClicked();
}

void MainWindow::contentsCheckBox_clicked() {
    contentsFlag = contentsCheckBox->checkState();
}

void MainWindow::chaptersCheckBox_clicked() {
    chaptersFlag = chaptersCheckBox->checkState();
}

void MainWindow::chaptersSortCheckBox_clicked() {
    sortFlag = chaptersSortCheckBox->checkState();
    seriesListWidget_itemClicked();
}

void MainWindow::tomsCheckBox_clicked() {
    tomsFlag = tomsCheckBox->checkState();
    seriesListWidget_itemClicked();
}

void MainWindow::scaleCheckBox_clicked() {
    scaleFlag = scaleCheckBox->checkState();
    widthLineEdit->setDisabled(!scaleFlag);
}

void MainWindow::ratioCheckBox_clicked() {
    ratioFlag = ratioCheckBox->checkState();
    ratioLineEdit->setDisabled(!ratioFlag);
    if(!ratioFlag) {
        ratio = 1.32432;
        ratioLineEdit->setText(QString::number(ratio));
        ratioLineEdit_editingFinished();
    }
}

//=============================================================================================================

void MainWindow::widthLineEdit_editingFinished() {
    scaleWidthImage = widthLineEdit->text().toInt();
    loadImage(lastPathToImage);
}

void MainWindow::ratioLineEdit_editingFinished() {
    ratio = ratioLineEdit->text().toDouble();

    pageHeigth = ceil(pageWidth * ratio);

    imageLabelWidgetMaxWidth = ceil(imageLabelWidgetMaxHeight / ratio);

    imageLabelWidget->setMinimumWidth(imageLabelWidgetMaxWidth);
    imageLabelWidget->setMaximumWidth(imageLabelWidgetMaxWidth);

    loadImage(lastPathToImage);
}

//=============================================================================================================

void MainWindow::seriesListWidget_itemClicked() {
    if(!seriesNameList.count() || seriesListWidget->currentRow() < 0) return;

    mName = seriesNameList.at(seriesListWidget->currentRow());
    mPath = sPath + "/" + mName;
    mDir.setPath(mPath);

    if(!mDir.exists()) {
        mName = "";
        mPath = "";
        mDir.setPath("");
    }

    tomsNameList.clear();
    tomsListWidget->clear();

    chaptersNameList = mDir.entryList(QDir::Dirs, QDir::NoSort);
    chaptersNameList.removeAt(chaptersNameList.indexOf("."));
    chaptersNameList.removeAt(chaptersNameList.indexOf(".."));
    chaptersListWidget->clear();

    picturesNameList.clear();
    picturesListWidget->clear();

    loadSeries();

    if(!tomsList.count()) return;

    tomsListWidget->addItems(tomsNameList);
    tomsListWidget->setCurrentRow(0);
    tomsListWidget_itemClicked();
}

void MainWindow::tomsListWidget_itemClicked() {
    int index = tomsListWidget->currentRow();
    if(tomsNameList.count() < index) return;

    tomTemp = tomsList.at(index);

    chaptersNameList = tomTemp.getChaptersNameList();

    if(!chaptersNameList.count()) return;

    chaptersListWidget->clear();
    chaptersListWidget->addItems(chaptersNameList);
    chaptersListWidget->setCurrentRow(0);
    chapterListWidget_itemClicked();

    QDir nDir;
    if(coversFlag) {
        nDir.setPath(mPath + "/_Covers/");
        QRegExp re("\\d+");
        if(re.indexIn(tomTemp.getName()) > -1) {
            QStringList covers = nDir.entryList(QStringList() << "* " + QString::number((int)(re.cap(0)).toDouble()) + ".*", QDir::Files, QDir::NoSort);
            if(covers.count())
                loadImage(mPath + "/_Covers/" + covers.at(0));
        }
    }
}

void MainWindow::chapterListWidget_itemClicked() {
    int index = chaptersListWidget->currentRow();
    if(chaptersNameList.count() < index) return;

    chapterTemp = tomTemp.at(index);

    picturesNameList = chapterTemp.getPicturesList();

    if(!picturesNameList.count()) return;

    picturesListWidget->clear();
    picturesListWidget->addItems(picturesNameList);
    picturesListWidget->setCurrentRow(0);
    picturesListWidget_itemClicked();
}

void MainWindow::picturesListWidget_itemClicked() {
    int index = picturesListWidget->currentRow();
    if(picturesNameList.count() < index) return;

    loadImage(chapterTemp.getPath() + "/" + picturesNameList.at(index));
}

//=============================================================================================================

void MainWindow::openDirPushButton_clicked() {
    sPath = QFileDialog::getExistingDirectory(this, tr("Открыть каталог с мангой"), "D:/Books/Manga", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    sDir.setPath(sPath);

    seriesListWidget->clear();

    tomsNameList.clear();
    tomsListWidget->clear();
    chaptersNameList.clear();
    chaptersListWidget->clear();
    picturesNameList.clear();
    picturesListWidget->clear();

    imageLabel->clear();
    lastPathToImage = "";

    if(!sDir.exists() || sPath == "") {
        sPath = "";
        return;
    }
    this->setWindowTitle(sPath);

    mName = "";
    mPath = "";
    mDir.setPath("");

    seriesNameList = sDir.entryList(QDir::Dirs, QDir::NoSort);
    seriesNameList.removeAt(seriesNameList.indexOf("."));
    seriesNameList.removeAt(seriesNameList.indexOf(".."));
    int t = seriesNameList.indexOf("_PDFs");

    if(t > -1) seriesNameList.removeAt(t);

    seriesListWidget->addItems(seriesNameList);

    oneTomPushButton->setDisabled(false);
    allTomsPushButton->setDisabled(false);
    allSeriesPushButton->setDisabled(false);
}

void MainWindow::openMangaPushButton_clicked() {
    mPath = QFileDialog::getExistingDirectory(this, tr("Открыть папку с главами манги"), "D:/Books/Manga", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    mDir.setPath(mPath);

    seriesNameList.clear();

    seriesListWidget->clear();

    tomsNameList.clear();
    tomsListWidget->clear();
    chaptersNameList.clear();
    chaptersListWidget->clear();
    picturesNameList.clear();
    picturesListWidget->clear();

    imageLabel->clear();
    lastPathToImage = "";

    if(!mDir.exists() || mPath == "") {
        mPath = "";
        return;
    }
    this->setWindowTitle(mPath);

    mName = mDir.dirName();

    mDir.cdUp();
    sPath = mDir.path();

    mDir.setPath(mPath);

    seriesNameList.append(mName);

    seriesListWidget->addItems(seriesNameList);
    seriesListWidget->setCurrentRow(0);

    seriesListWidget_itemClicked();

    oneTomPushButton->setDisabled(false);
    allTomsPushButton->setDisabled(false);
    if(seriesNameList.count() > 1) allSeriesPushButton->setDisabled(false);
    else allSeriesPushButton->setDisabled(true);
}

void MainWindow::oneTomPushButton_clicked() {
    if(seriesListWidget->currentRow() < 0) return;
    disableAllWidget();

    createOneTom(tomsListWidget->currentRow());

    //messagesListWidget->addItem("Начало создания pdf файла");
    //messagesListWidget->setCurrentRow(messagesListWidget->count() - 1);
    //messagesListWidget->addItem("Все готово, всего изображений: " + QString::number(createOneTom(tomsListWidget->currentRow())));
    //messagesListWidget->setCurrentRow(messagesListWidget->count() - 1);

    enableAllWidget();
    oneTomPushButton->setDisabled(false);
    allTomsPushButton->setDisabled(false);
    if(seriesNameList.count() > 1) allSeriesPushButton->setDisabled(false);
    else allSeriesPushButton->setDisabled(true);
}

void MainWindow::allTomsPushButton_clicked() {
    if(seriesListWidget->currentRow() < 0) return;
    disableAllWidget();

    //messagesListWidget->addItem("Начало создания pdf файлов серии");
    //messagesListWidget->setCurrentRow(messagesListWidget->count() - 1);
    int countPictures = 0;
    if(tomsFlag)
        for(int i = 0; i < tomsList.count(); i++)
            countPictures += createOneTom(i);
    else countPictures += createOneTom(0);
    //messagesListWidget->addItem("Все готово, всего изображений: " + QString::number(countPictures));
    //messagesListWidget->setCurrentRow(messagesListWidget->count() - 1);

    enableAllWidget();
    oneTomPushButton->setDisabled(false);
    allTomsPushButton->setDisabled(false);
    if(seriesNameList.count() > 1) allSeriesPushButton->setDisabled(false);
    else allSeriesPushButton->setDisabled(true);
}

void MainWindow::allSeriesPushButton_clicked() {
    disableAllWidget();

    //messagesListWidget->addItem("Начало создания pdf всех файлов");
    for(int i = 0; i < seriesNameList.count(); i++) {
        messagesListWidget->addItem("Начало создания pdf файлов серии");
        seriesListWidget->setCurrentRow(i);
        seriesListWidget_itemClicked();

        int countPictures = 0;
        if(tomsFlag)
            for(int i = 0; i < tomsList.count(); i++)
                countPictures += createOneTom(i);
        else countPictures += createOneTom(0);
        //messagesListWidget->addItem("Серия закончена, всего изображений: " + QString::number(countPictures));
        //messagesListWidget->setCurrentRow(messagesListWidget->count() - 1);

        qApp->processEvents();

    }

    //messagesListWidget->addItem("Все готов");
    //messagesListWidget->setCurrentRow(messagesListWidget->count() - 1);

    enableAllWidget();
}

//=============================================================================================================

int MainWindow::lengNumber(int n) {
    int digits = 1;
    while (n /= 10) digits++;
    return digits;
}

void MainWindow::disableAllWidget() {
    coversCheckBox->setDisabled(true);
    contentsCheckBox->setDisabled(true);
    chaptersCheckBox->setDisabled(true);
    chaptersSortCheckBox->setDisabled(true);
    tomsCheckBox->setDisabled(true);
    scaleCheckBox->setDisabled(true);
    ratioCheckBox->setDisabled(true);

    openDirPushButton->setDisabled(true);
    openMangaPushButton->setDisabled(true);
    oneTomPushButton->setDisabled(true);
    allTomsPushButton->setDisabled(true);
    allSeriesPushButton->setDisabled(true);

    widthLabel->setDisabled(true);
    ratioLabel->setDisabled(true);
    widthLineEdit->setDisabled(true);
    ratioLineEdit->setDisabled(true);

    seriesListWidget->setDisabled(true);
    tomsListWidget->setDisabled(true);
    chaptersListWidget->setDisabled(true);
    picturesListWidget->setDisabled(true);
    messagesListWidget->setDisabled(true);

    qApp->processEvents();
}

void MainWindow::enableAllWidget() {
    coversCheckBox->setDisabled(false);
    contentsCheckBox->setDisabled(false);
    chaptersCheckBox->setDisabled(false);
    chaptersSortCheckBox->setDisabled(false);
    tomsCheckBox->setDisabled(false);
    scaleCheckBox->setDisabled(false);
    ratioCheckBox->setDisabled(false);

    openDirPushButton->setDisabled(false);
    openMangaPushButton->setDisabled(false);
    oneTomPushButton->setDisabled(false);
    allTomsPushButton->setDisabled(false);
    allSeriesPushButton->setDisabled(false);

    widthLabel->setDisabled(false);
    ratioLabel->setDisabled(false);
    widthLineEdit->setDisabled(!scaleFlag);
    ratioLineEdit->setDisabled(!ratioFlag);

    seriesListWidget->setDisabled(false);
    tomsListWidget->setDisabled(false);
    chaptersListWidget->setDisabled(false);
    picturesListWidget->setDisabled(false);
    messagesListWidget->setDisabled(false);

    qApp->processEvents();
}

void MainWindow::loadImage(QString path) {
    imageTemp.load(path);
    lastPathToImage = path;

    double imageTempRatio = (double)imageTemp.height() / imageTemp.width();
    int tempWidth = scaleWidthImage;

    if(!scaleFlag || scaleWidthImage > imageTemp.width())
        tempWidth = imageTemp.width();

    if(ratio < imageTempRatio + tolerance && imageTempRatio - tolerance < ratio)
        image = imageTemp.scaled(tempWidth, ceil(tempWidth * ratio), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    else if(ratio < imageTempRatio)
        image = imageTemp.scaled(ceil(ceil(tempWidth * ratio) / imageTempRatio), ceil(tempWidth * ratio), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    else image = imageTemp.scaled(tempWidth, ceil(tempWidth * imageTempRatio), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    imageLabel->setPixmap(image);

    double scale = std::min((double)imageLabelWidgetMaxHeight / image.height(), (double)imageLabelWidgetMaxWidth / image.width());

    int height = ceil(image.height() * scale);
    int width = ceil(image.width() * scale);

    if(imageLabelWidgetMaxWidth < width) width = imageLabelWidgetMaxWidth;
    if(imageLabelWidgetMaxHeight < height) height = imageLabelWidgetMaxHeight;

    imageLabel->setMinimumSize(QSize(width - 2, height - 2));
    imageLabel->setMaximumSize(QSize(width - 2, height - 2));
}

void MainWindow::loadSeries() {
    if(!chaptersNameList.count() || !mDir.exists() || mPath == "" || mName == "") return;

    tomsList.clear();
    tomTemp.clear();
    tomsNameList.clear();

    picturesCount = 0;

    int i, j;

    if(tomsFlag) {
        QList <QStringList> chaptersNameListTemp;
        QStringList chaptersIndexList, otherNameList, tempStringList;
        QString strTemp, strIndex;

        if(coversFlag) {
            int indexCovers = chaptersNameList.indexOf("_Covers");
            if(indexCovers > -1) chaptersNameList.removeAt(indexCovers);
        }

        QRegExp re(regExpTom);
        for(i = 0; i < chaptersNameList.count(); i++) {
            strTemp = chaptersNameList.at(i);
            if(re.indexIn(strTemp) > -1) {
                strIndex = re.cap(0);
                if((j = chaptersIndexList.indexOf(strIndex)) > -1) {
                    tempStringList = chaptersNameListTemp.at(j);
                    chaptersNameListTemp[j].append(strTemp);
                } else {
                    tempStringList.clear();
                    chaptersIndexList.append(strIndex);
                    tempStringList.append(strTemp);
                    chaptersNameListTemp.append(tempStringList);
                }
            } else otherNameList.append(strTemp);
        }

        if(chaptersIndexList.count() > 1) {
            int l = 0, r = chaptersIndexList.count();
            bool b = true;
            while (b) {
                b = false;
                for(i = l, j = 0; i + 1 < r; i++, j++)
                    if (compareToms(chaptersIndexList.at(i), chaptersIndexList.at(i + 1))) {
                        chaptersIndexList.swapItemsAt(i, i + 1);
                        chaptersNameListTemp.swapItemsAt(j, j + 1);
                        b = true;
                    }
                r--;
            }
        }
        maxNumberTom = (int)chaptersIndexList.at(chaptersIndexList.count() - 1).toDouble();

        for(i = 0; i < chaptersNameListTemp.count(); i++) {
            tempStringList = chaptersNameListTemp.at(i);
			if(sortFlag && tempStringList.count() > 1) qSort(tempStringList.begin(), tempStringList.end(), compareChapters);

            tomTemp.clear();
            tomTemp.setName(mName + ". Tom " + QStringLiteral("%1").arg((int)chaptersIndexList[i].toDouble(), lengNumber(maxNumberTom), 10, QLatin1Char('0')));
            tomTemp.setPath(mPath);

            tomsNameList.append("Том " + QString::number(chaptersIndexList[i].toDouble()));

            for(j = 0; j < tempStringList.count(); j++) {
                chapterTemp.clear();
                chapterTemp.setName(tempStringList.at(j));
                chapterTemp.setPath(mPath + "/" + tempStringList.at(j));

                tDir.setPath(chapterTemp.getPath());
                if(tDir.exists()) {
                    chapterTemp.setPicturesList(tDir.entryList(QStringList() << "*.png" << "*.jpg" << "*.jpeg" << "*.webp" << "*.gif", QDir::Files));
                    picturesCount += chapterTemp.getPicturesCount();
                    tomTemp.append(chapterTemp);
                }
            }
            tomsList.append(tomTemp);
        }

        if(otherNameList.count()) {
            tomTemp.clear();
            tomTemp.setName(mName + ". Other");
            tomTemp.setPath(mPath);

            tomsNameList.append("Other");

            for(j = 0; j < otherNameList.count(); j++) {
                chapterTemp.clear();
                chapterTemp.setName(otherNameList.at(j));
                chapterTemp.setPath(mPath + "/" + otherNameList.at(j));

                tDir.setPath(chapterTemp.getPath());
                if(tDir.exists()) {
                    chapterTemp.setPicturesList(tDir.entryList(QStringList() << "*.png" << "*.jpg" << "*.jpeg" << "*.webp" << "*.gif", QDir::Files));
                    picturesCount += chapterTemp.getPicturesCount();
                    tomTemp.append(chapterTemp);
                }
            }
            tomsList.append(tomTemp);
        }
    } else {
		if(sortFlag  && chaptersNameList.count() > 1) qSort(chaptersNameList.begin(), chaptersNameList.end(), compareChapters);
        if(coversFlag) {
            int indexCovers = chaptersNameList.indexOf("_Covers");
            if(indexCovers > -1) chaptersNameList.removeAt(indexCovers);
        }

        tomTemp.setName(mName);
        tomTemp.setPath(mPath);

        tomsNameList.append("All");

        for(i = 0; i < chaptersNameList.count(); i++) {
            chapterTemp.clear();
            chapterTemp.setName(chaptersNameList.at(i));
            chapterTemp.setPath(mPath + "/" + chaptersNameList.at(i));

            tDir.setPath(chapterTemp.getPath());
            if(tDir.exists()) {
                chapterTemp.setPicturesList(tDir.entryList(QStringList() << "*.png" << "*.jpg" << "*.jpeg" << "*.webp" << "*.gif", QDir::Files));
                picturesCount += chapterTemp.getPicturesCount();
                tomTemp.append(chapterTemp);
            }
        }
        tomsList.append(tomTemp);
    }
}

int MainWindow::createOneTom(int index) {
    tomsListWidget->setCurrentRow(index);
    tomsListWidget_itemClicked();

    QString scaledText, nameFile;

    QDir nDir(sPath + "/_PDFs");
    if(!nDir.exists()) {
        nDir.setPath(sPath);
        nDir.mkdir("_PDFs");
    }

    if(tomsFlag) {
        nDir.setPath(sPath + "/_PDFs/" + mName);
        if(!nDir.exists()) {
            nDir.setPath(sPath + "/_PDFs");
            nDir.mkdir(mName);
        }
    }

    if(scaleFlag) scaledText = " (scaled from " + QString::number(scaleWidthImage) + " x " + QString::number(ceil(scaleWidthImage * ratio)) + ")";
    else scaledText = " (not scaled)";

    if(tomsFlag) nameFile = sPath + "/_PDFs/" + mName + "/" + tomsList[index].getName() + scaledText + ".pdf";
    else nameFile = sPath + "/_PDFs/" + mName + scaledText + ".pdf";

    /*if(tomsFlag) {
        nDir.setPath("F:/_PDFs/" + mName);
        if(!nDir.exists()) {
            nDir.setPath("F:/_PDFs");
            nDir.mkdir(mName);
        }
    }

    if(tomsFlag) nameFile = "F:/_PDFs/" + mName + "/" + tomsList[index].getName() + scaledText + ".pdf";
    else nameFile = "F:/_PDFs/" + mName + scaledText + ".pdf";*/

    //nameFile = "C:/file.pdf";

    QPdfWriter writer(nameFile);
    writer.setPageSizeMM(QSizeF(pageWidth, pageHeigth));
    writer.setPageMargins(QMargins(0, 0, 0, 0));

    QPainter painter(&writer);
    painter.setFont(QFont("Consolas", 8));
    painter.setPen(QPen(Qt::black, 12, Qt::DotLine, Qt::RoundCap));

    QRect r = painter.viewport();

    int i, j;
    int x, y, height, width;
    int page = 1, countPictures = 0;
    double scale, scaleFromWidth, scaleFromHeight, imageRatio;

    tomTemp = tomsList.at(index);

    if(coversFlag) {
        nDir.setPath(mPath + "/_Covers/");
        QRegExp re("\\d+");
        if(re.indexIn(tomTemp.getName()) > -1) {
            QStringList covers = nDir.entryList(QStringList() << "* " + QString::number((int)(re.cap(0)).toDouble()) + ".*", QDir::Files, QDir::NoSort);
            if(covers.count()) {
                loadImage(mPath + "/_Covers/" + covers.at(0));

                scaleFromWidth = (double)writer.width() / image.width();
                scaleFromHeight = (double)writer.height() / image.height();
                imageRatio = (double)image.height() / image.width();

                if(ratio < imageRatio + 0.01 && imageRatio - 0.01 < ratio) {
                    x = 0;
                    y = 0;

                    height = writer.height();
                    width = writer.width();
                } else if(ratio < imageRatio) {
                    x = (writer.width() - ceil(image.width() * scaleFromHeight)) / 2;
                    y = 0;

                    height = writer.height();
                    width = ceil(image.width() * scaleFromHeight);
                } else {
                    x = 0;
                    y = (writer.height() - ceil(image.height() * scaleFromWidth)) / 2;

                    height = ceil(image.height() * scaleFromWidth);
                    width = writer.width();
                }

                painter.drawPixmap(x, y, width, height, image);
                writer.newPage();

                page++;
                countPictures++;
            }
        }
    }

    QRegExp re(regExpChapter);
    QStringList picturesList, parts, chaptersList = tomsList[index].getChaptersNameList(), textList;

    if(contentsFlag && chaptersList.count() > 1) {
        int countParagraph = (writer.height() - 800) / 200;
        page += ceil((double)chaptersList.count() / countParagraph);

        int offsetY = chaptersList.count() > countParagraph ? (writer.height() - 200 * countParagraph) / 2 : ((countParagraph - tomsList[index].getChaptersNameList().count()) * 200) / 2 + (writer.height() - 200 * countParagraph) / 2, k;
        QString text, number;

        for(i = 0; i < chaptersList.count(); i++) {
            chapterTemp = tomsList[index].at(i);

            text = chaptersList[i];
            if(tomsFlag && re.indexIn(chaptersList[i]) > -1) {
                textList = chaptersList[i].split(" ", QString::SkipEmptyParts);
                text = "Глава " + re.cap(0);
                if((k = textList.indexOf("-")) != -1) {
                    text += " - ";
                    int p = textList.count() - k - 1;
                    for(j = 0; j < p; j++) {
                        text += textList[j + k + 1];
                        if(j < p - 1) text += " ";
                    }
                }
            }

            picturesList = chapterTemp.getPicturesList();
            number = QString::number(page);

            if(i && !(i % countParagraph)) writer.newPage();

            QRect boundingRect, rectangle;
            rectangle.setRect(430, 22 + offsetY + (i % countParagraph) * 200, writer.width() - 800, 200);
            painter.drawText(rectangle, 0, text, &boundingRect);
            painter.drawLine(460 + boundingRect.width(), 143 + offsetY + (i % countParagraph) * 200, writer.width() - number.count() * 73 - 470, 143 + offsetY + (i % countParagraph) * 200);
            painter.drawText(writer.width() - number.count() * 73 - 440, 143 + offsetY + (i % countParagraph) * 200, number);
            //painter.drawRect(400, offsetY + (i % countParagraph) * 200, writer.width() - 800, 200);

            page += picturesList.count();
        }
        writer.newPage();
    }

    for(i = 0; i < chaptersList.count(); i++) {
        chapterTemp = tomsList[index].at(i);
        picturesList = chapterTemp.getPicturesList();

        chaptersListWidget->setCurrentRow(i);
        picturesListWidget->clear();
        picturesListWidget->addItems(picturesList);

        for(j = 0; j < picturesList.count(); j++) {
            picturesListWidget->setCurrentRow(j);
            loadImage(chapterTemp.getPath() + "/" + picturesList[j]);

            scaleFromWidth = (double)writer.width() / image.width();
            scaleFromHeight = (double)writer.height() / image.height();
            imageRatio = (double)image.height() / image.width();

            if(ratio < imageRatio + 0.01 && imageRatio - 0.01 < ratio) {
                x = 0;
                y = 0;

                height = writer.height();
                width = writer.width();
            } else if(ratio < imageRatio) {
                x = (writer.width() - ceil(image.width() * scaleFromHeight)) / 2;
                y = 0;

                height = writer.height();
                width = ceil(image.width() * scaleFromHeight);
            } else {
                x = 0;
                y = (writer.height() - ceil(image.height() * scaleFromWidth)) / 2;

                height = ceil(image.height() * scaleFromWidth);
                width = writer.width();
            }

            painter.drawPixmap(x, y, width, height, image);
            if(chaptersFlag && chaptersList.count() > 1 && re.indexIn(chaptersList[i]) > -1) painter.drawText(r, Qt::AlignBottom | Qt::AlignRight, re.cap(0));

            countPictures++;

            if(i == chaptersList.count() - 1 && j == picturesList.count() - 1) break;
            writer.newPage();

            qApp->processEvents();
        }
    }

    messagesListWidget->addItem(nameFile + " создан, количество картинок в файле: " + QString::number(countPictures));
    messagesListWidget->setCurrentRow(messagesListWidget->count() - 1);
    qDebug() << nameFile + " создан, количество картинок в файле: " + QString::number(countPictures);

    painter.end();

    return countPictures;
}
