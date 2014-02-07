// checksum 0xa193 version 0x30001
/*
  This file was generated by the Mobile Qt Application wizard of Qt Creator.
  MainWindow is a convenience class containing mobile device specific code
  such as screen orientation handling.
  It is recommended not to modify this file, since newer versions of Qt Creator
  may offer an updated version of it.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore/QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    iBg = new QWidget(this);
    iBg->setGeometry(0,0,360, 640);


    iTitleBar = new QLabel(iBg);
    iTitleBar->setFixedSize(360, 60);
    iTitleBar->setAlignment(Qt::AlignCenter);
    iTitleBar->setStyleSheet("background-image: url(:/images/gamename.png)");

    iStackedWidget = new QStackedWidget(iBg);
    iStackedWidget->setFixedSize(360, 580);


    QVBoxLayout* v_layout = new QVBoxLayout(iBg);
    v_layout->setMargin(0);
    v_layout->setContentsMargins(0,0,0,0);
    v_layout->setSpacing(0);
    v_layout->addWidget(iTitleBar);
    v_layout->addWidget(iStackedWidget);



    iHomeView = new HomeView(iStackedWidget); //0
    iImageView = new ImageView(iStackedWidget); //1
    iGamePad = new GamePad(iStackedWidget); //2
    iAboutView = new AboutView(iStackedWidget); //3
    iLevelView= new LevelView(iStackedWidget); //4
    iInstructionView = new InstructionView(iStackedWidget);//5

    iStackedWidget->addWidget(iHomeView);
    iStackedWidget->addWidget(iImageView);
    iStackedWidget->addWidget(iGamePad);
    iStackedWidget->addWidget(iAboutView);
    iStackedWidget->addWidget(iLevelView);
    iStackedWidget->addWidget(iInstructionView);


    iStackedWidget->setCurrentIndex(0);

    connect(iHomeView, SIGNAL(showImageView()), this, SLOT(activateImageView()));
    connect(iHomeView, SIGNAL(showAboutView()), this,SLOT(activateAboutView()));
    connect(iImageView,SIGNAL(showLevelView(QString)), this, SLOT(activateLevelView(QString)));
    connect(iGamePad, SIGNAL(showImageView()), this,SLOT(activateImageView()));
    connect(iImageView,SIGNAL(showHomeView()),this,SLOT(activateHomeView()));
    connect(iAboutView,SIGNAL(showHomeView()),this,SLOT(activateHomeView()));
    connect(iInstructionView,SIGNAL(showHomeView()),this,SLOT(activateHomeView()));
    connect(iLevelView,SIGNAL(showGamePad(int)),this,SLOT(activateGamePad(int)));
    connect(iLevelView,SIGNAL(showImageView()),this,SLOT(activateImageView()));
    connect(iHomeView,SIGNAL(showInstructionView()),this,SLOT(activateInstructionView()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setOrientation(ScreenOrientation orientation)
{
#if defined(Q_OS_SYMBIAN)
    // If the version of Qt on the device is < 4.7.2, that attribute won't work
    if (orientation != ScreenOrientationAuto) {
        const QStringList v = QString::fromAscii(qVersion()).split(QLatin1Char('.'));
        if (v.count() == 3 && (v.at(0).toInt() << 16 | v.at(1).toInt() << 8 | v.at(2).toInt()) < 0x040702) {
            qWarning("Screen orientation locking only supported with Qt 4.7.2 and above");
            return;
        }
    }
#endif // Q_OS_SYMBIAN

    Qt::WidgetAttribute attribute;
    switch (orientation) {
#if QT_VERSION < 0x040702
    // Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
    case ScreenOrientationLockPortrait:
        attribute = static_cast<Qt::WidgetAttribute>(128);
        break;
    case ScreenOrientationLockLandscape:
        attribute = static_cast<Qt::WidgetAttribute>(129);
        break;
    default:
    case ScreenOrientationAuto:
        attribute = static_cast<Qt::WidgetAttribute>(130);
        break;
#else // QT_VERSION < 0x040702
    case ScreenOrientationLockPortrait:
        attribute = Qt::WA_LockPortraitOrientation;
        break;
    case ScreenOrientationLockLandscape:
        attribute = Qt::WA_LockLandscapeOrientation;
        break;
    default:
    case ScreenOrientationAuto:
        attribute = Qt::WA_AutoOrientation;
        break;
#endif // QT_VERSION < 0x040702
    };
    setAttribute(attribute, true);
}

void MainWindow::showExpanded()
{
#ifdef Q_OS_SYMBIAN
    showFullScreen();
#elif defined(Q_WS_MAEMO_5) || defined(Q_WS_MAEMO_6)
    showMaximized();
#else
    show();
#endif
}

void MainWindow::activateImageView()
{
    iTitleBar->setStyleSheet("background-image: url(:/images/selectimage.png)");
    iStackedWidget->setCurrentIndex(1);

    QPropertyAnimation *animation = new QPropertyAnimation(iImageView, "pos", this);

    QRect pixRect = QRect(QPoint(0,0), iImageView->size());
    pixRect.moveCenter( QPoint(width()/2,0));

    animation->setDuration(200);
    animation->setStartValue(QPoint(iImageView->x(), -(iImageView->height())));
    animation->setEndValue(QPoint(pixRect.x(), iImageView->y()));
    animation->setEasingCurve(QEasingCurve::InQuad);
    animation->start();
}


void MainWindow::activateAboutView()
{
    iTitleBar->setStyleSheet("background-image: url(:/images/about.png)");
    iStackedWidget->setCurrentIndex(3);

    QPropertyAnimation *animation = new QPropertyAnimation(iAboutView, "pos", this);

    QRect pixRect = QRect(QPoint(0,0), iAboutView->size());
    pixRect.moveCenter( QPoint(width()/2,0));

    animation->setDuration(200);
    animation->setStartValue(QPoint(iAboutView->x(), -(iAboutView->height())));
    animation->setEndValue(QPoint(pixRect.x(), iAboutView->y()));
    animation->setEasingCurve(QEasingCurve::InQuad);
    animation->start();
}


void MainWindow::activateInstructionView()
{
    iTitleBar->setStyleSheet("background-image: url(:/images/instructions.png)");
    iStackedWidget->setCurrentIndex(5);

    QPropertyAnimation *animation = new QPropertyAnimation(iInstructionView, "pos", this);

    QRect pixRect = QRect(QPoint(0,0), iInstructionView->size());
    pixRect.moveCenter( QPoint(width()/2,0));

    animation->setDuration(200);
    animation->setStartValue(QPoint(iInstructionView->x(), -(iInstructionView->height())));
    animation->setEndValue(QPoint(pixRect.x(), iInstructionView->y()));
    animation->setEasingCurve(QEasingCurve::InQuad);
    animation->start();
}


void MainWindow::activateLevelView(QString aFilename)
{
    iTitleBar->setStyleSheet("background-image: url(:/images/selectlevel.png)");
    iStackedWidget->setCurrentIndex(4);
    iFilename=aFilename;

    QPropertyAnimation *animation = new QPropertyAnimation(iLevelView, "pos", this);

    QRect pixRect = QRect(QPoint(0,0), iLevelView->size());
    pixRect.moveCenter( QPoint(width()/2,0));

    animation->setDuration(200);
    animation->setStartValue(QPoint(iLevelView->x(), -(iLevelView->height())));
    animation->setEndValue(QPoint(pixRect.x(), iLevelView->y()));
    animation->setEasingCurve(QEasingCurve::InQuad);
    animation->start();

}

void MainWindow::activateHomeView()
{
    iTitleBar->setStyleSheet("background-image: url(:/images/gamename.png)");
    iStackedWidget->setCurrentIndex(0);

    QPropertyAnimation *animation = new QPropertyAnimation(iHomeView, "pos", this);

    QRect pixRect = QRect(QPoint(0,0), iHomeView->size());
    pixRect.moveCenter( QPoint(width()/2,0));

    animation->setDuration(200);
    animation->setStartValue(QPoint(iHomeView->x(), -(iHomeView->height())));
    animation->setEndValue(QPoint(pixRect.x(), iHomeView->y()));
    animation->setEasingCurve(QEasingCurve::InQuad);
    animation->start();
}

void MainWindow::activateGamePad(int aLevel)
{
    iTitleBar->setStyleSheet("background-image: url(:/images/gamename.png)");
    iStackedWidget->setCurrentIndex(2);
    iGamePad->setGame(iFilename, aLevel);

    QPropertyAnimation *animation = new QPropertyAnimation(iGamePad, "pos", this);

    QRect pixRect = QRect(QPoint(0,0), iGamePad->size());
    pixRect.moveCenter( QPoint(width()/2,0));

    animation->setDuration(200);
    animation->setStartValue(QPoint(iGamePad->rect().x(), -(iGamePad->height())));
    animation->setEndValue(QPoint(pixRect.x(), iGamePad->rect().y()));
    animation->setEasingCurve(QEasingCurve::InQuad);
    animation->start();
}