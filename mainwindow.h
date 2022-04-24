#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>                                      //->Hauptfenster bietet viel Möglichkeiten
#include <QWidget>
#include <QLabel>                                           //->Zur Beschriftung verwenden
#include <QImage>                                           //->Arbeiten mit Bildern
#include <QVBoxLayout>                                      // Anordnung der Elemente im Fenster
#include <QMenu>
#include <QMenuBar>
#include <QIcon>
#include <QKeySequence>
#include <QAction>
#include <QString>
#include <QFileDialog>
#include <QDir>
#include <QPixmap>
#include <QRgb>
#include <QToolBar>
#include <QInputDialog>

#include "./imagefilter.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QWidget *centralWidget;
    QLabel *image;
    QImage *imageData;
    QVBoxLayout layout;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void openFile(void);
    void saveFile(void);
    void greyScale(void);
    void lighten(void);
    void darken(void);
    void filterMedian(void);
};
#endif // MAINWINDOW_H
