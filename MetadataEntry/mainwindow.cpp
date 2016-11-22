#include <ctime>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "metadatadialog.h"
#include "entrylabel.h"
#include "utils.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    metadataDialog(this),
    captureDialog(this),
    stringListModel(this),
    metadataFolderPath("metadata")
{
    ui->setupUi(this);

    /*QFile file("metadata");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    in >> entries;
    file.close();*/

    // Clicking the different buttons shows the corresponding windows
    QObject::connect(ui->saveButton, SIGNAL(clicked()),
                     this, SLOT(saveEntries()));
    QObject::connect(ui->addEntryButton, SIGNAL(clicked()),
                     this, SLOT(addEntry()));
    QObject::connect(ui->editEntryButton, SIGNAL(clicked()),
                     this, SLOT(editEntry()));
    QObject::connect(ui->removeEntryButton, SIGNAL(clicked()),
                     this, SLOT(removeEntry()));

    QObject::connect(&metadataDialog, SIGNAL(accepted()),
                     this, SLOT(dialogAccepted()));

    QObject::connect(this->ui->entryListWidget, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
                     this, SLOT(enableButtons()));

    QObject::connect(this->ui->entryListWidget, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
                     this, SLOT(updateVisualizer(QListWidgetItem*)));

    QObject::connect(ui->captureButton, SIGNAL(clicked()),
                     this, SLOT(startCapture()));


    stringListModel.setStringList(stringList);

    qsrand(time(NULL));

}

MainWindow::~MainWindow()
{
    delete ui;

    for (auto it = entries.begin(); it != entries.end(); it++)
    {
        delete *it;
    }
}


void MainWindow::saveEntries()
{
    QDir dir(".");
    if (dir.mkpath(metadataFolderPath) && dir.cd(metadataFolderPath))
    {
        for (auto it = entries.begin(); it < entries.end(); it++)
        {
            QFile file(dir.path() + "/" + (*it)->getId()); // WARNING: Not checking duplicates
            file.open(QIODevice::WriteOnly);
            //QDataStream out(&file);

            //out << *it;
            file.write((*it)->toQString().toUtf8());

            file.close();
        }
    }
    else
    {
        QMessageBox::critical(this, "Error", "Could not create metadata directory");
    }
}

void MainWindow::addEntry()
{
    Entry* entry = new Entry();
    entries.append(entry);
    editedEntry = entry;
    metadataDialog.setEntry(entry);
    metadataDialog.show();
}

void MainWindow::removeEntry()
{
    //entries.removeAll(static_cast<Entry*>(indexes.first().internalPointer()));
}

void MainWindow::editEntry()
{

}

void MainWindow::enableButtons()
{
    // TODO Uncomment these two lines
    //this->ui->editEntryButton->setEnabled(true);
    //this->ui->removeEntryButton->setEnabled(true);
    this->ui->captureButton->setEnabled(true);
}

void MainWindow::dialogAccepted()
{
    EntryLabel* entryLabel = new EntryLabel(metadataDialog.getEntry(), ui->entryListWidget);
    ui->entryListWidget->addItem(entryLabel);
    ui->entryListWidget->update();
}


void MainWindow::updateVisualizer(QListWidgetItem* newItem)
{
    auto entryLabelNewItem = static_cast<EntryLabel*>(newItem);
    ui->dataVisualizer->document()->setPlainText(entryLabelNewItem->getEntry()->toQString());
}

void MainWindow::startCapture()
{
    captureDialog.setId(static_cast<EntryLabel*>(ui->entryListWidget->selectedItems().first())->getEntry()->getId());
    captureDialog.show();
}


