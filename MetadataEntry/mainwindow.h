#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndexList>
#include <QStringListModel>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QListWidgetItem>

#include <iostream>

#include "metadatadialog.h"
#include "capturedialog.h"
#include "entry.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    // "To master your enemy, become your enemy !"
    //                  Some guy, probably
    // That's why you can appreciate some antipatterns in this project

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void saveEntries();
    void addEntry();
    void removeEntry();
    void editEntry();

private slots:
    void enableButtons();
    void dialogAccepted();
    void updateVisualizer(QListWidgetItem *newItem);
    void startCapture();

private:
    Ui::MainWindow *ui;
    QList<Entry*> entries;
    QModelIndexList indexes;
    MetadataDialog metadataDialog;
    CaptureDialog captureDialog;
    Entry* editedEntry;
    QStringList stringList;
    QStringListModel stringListModel;

    const QString metadataFolderPath;
};

#endif // MAINWINDOW_H
