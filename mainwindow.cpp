#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // setup main window
    this->centralWidget = new QWidget(this);
    this->image = new QLabel("", this);
    this->layout.addWidget(this->image);
    this->centralWidget->setLayout(&this->layout);
    this->setCentralWidget(this->centralWidget);
    this->imageData = NULL;

    // setup navigation
    QAction *actOpen = new QAction(tr("&Öffnen"), this);
    QObject::connect(actOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    QAction *actSave = new QAction(tr("&Speichern"), this);
    QObject::connect(actSave, SIGNAL(triggered()), this, SLOT(saveFile()));
    QMenu *fileMenu = new QMenu(tr("&Datei"), this);
    fileMenu->addAction(actOpen);
    fileMenu->addAction(actSave);
    this->menuBar()->addMenu(fileMenu);

    QAction *actGreyScale = new QAction(tr("&Graustufen"), this);
    QObject::connect(actGreyScale, SIGNAL(triggered()), this, SLOT(greyScale()));
    QAction *actLighten = new QAction(tr("&Aufhellen"), this);
    QObject::connect(actLighten, SIGNAL(triggered()), this, SLOT(lighten()));
    QAction *actDarken = new QAction(tr("&Abdunkeln"), this);
    QObject::connect(actDarken, SIGNAL(triggered()), this, SLOT(darken()));
    QMenu *filterMenu = new QMenu(tr("&Filter"), this);
    filterMenu->addAction(actGreyScale);
    filterMenu->addAction(actLighten);
    filterMenu->addAction(actDarken);
    this->menuBar()->addMenu(filterMenu);
}

MainWindow::~MainWindow()
{
    delete this->centralWidget;
    delete this->image;
    delete this->imageData;
}

void MainWindow::openFile(void)
{
    QString file = QFileDialog::getOpenFileName(this,
                                                tr("Datei öffnen"),
                                                QDir::homePath(),
                                                "Bilddateien (*.jpg *.png *.bmp);;" "Alle Dateien (*.*)");
    if(!file.isNull())
    {
        if(this->imageData != NULL)
        {
            delete this->imageData;
        }
        this->imageData = new QImage(file);
        this->image->setPixmap(QPixmap::fromImage(*this->imageData));
        this->image->setScaledContents(true);
    }
}

void MainWindow::saveFile(void)
{
    if(this->imageData != NULL)
    {
        QString file = QFileDialog::getSaveFileName(this,"Datei speichern",QDir::homePath(),
                                                     "Bilddateien (*.jpg *.png *.bmp);;" "Alle Dateien (*.*)");
        if(!file.isNull())
        {
            this->imageData->save(file);
        }
    }
}

void MainWindow::greyScale(void)
{
    if(this->imageData != NULL)
    {
        *this->imageData = ImageFilter::greyScale(*this->imageData);
        this->image->setPixmap(QPixmap::fromImage(*this->imageData));
    }
}

void MainWindow::lighten(void)
{
    if(this->imageData != NULL)
    {
        int value = QInputDialog::getInt(this, tr("Aufhellen"), tr("Wert für Aufhellung:"), 0, 0, 255);
        *this->imageData = ImageFilter::lighten(*this->imageData, value);
        this->image->setPixmap(QPixmap::fromImage(*this->imageData));
    }
}

void MainWindow::darken(void)
{
    if(this->imageData != NULL)
    {
        int value = QInputDialog::getInt(this, tr("Aufhellen"), tr("Wert für Aufhellung:"), 0, 0, 255);
        *this->imageData = ImageFilter::darken(*this->imageData, value);
        this->image->setPixmap(QPixmap::fromImage(*this->imageData));
    }
}
