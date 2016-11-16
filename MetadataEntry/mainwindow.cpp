#include <ctime>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "metadatadialog.h"
#include "entrylabel.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dialog(this),
    stringListModel(this),
    metadataFolderPath("metadata")
{
    ui->setupUi(this);

    QFile file("metadata");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    in >> entries;
    file.close();

    QObject::connect(this->ui->saveButton, SIGNAL(clicked()),
                     this, SLOT(saveEntries()));
    QObject::connect(this->ui->addEntryButton, SIGNAL(clicked()),
                     this, SLOT(addEntry()));
    QObject::connect(this->ui->editEntryButton, SIGNAL(clicked()),
                     this, SLOT(editEntry()));
    QObject::connect(this->ui->removeEntryButton, SIGNAL(clicked()),
                     this, SLOT(removeEntry()));

    QObject::connect(&dialog, SIGNAL(accepted()),
                     this, SLOT(dialogAccepted()));

    QObject::connect(this->ui->entryListWidget, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
                     this, SLOT(enableButtons()));

    QObject::connect(this->ui->entryListWidget, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
                     this, SLOT(updateVisualizer(QListWidgetItem*)));


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
            QFile file(dir.path() + "/" + GetRandomString()); // WARNING: Not checking duplicates
            file.open(QIODevice::WriteOnly);
            QDataStream out(&file);

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
    dialog.setEntry(entry);
    dialog.show();
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
}

void MainWindow::dialogAccepted()
{
    EntryLabel* entryLabel = new EntryLabel(dialog.getEntry(), ui->entryListWidget);
    ui->entryListWidget->addItem(entryLabel);
    ui->entryListWidget->update();
}


void MainWindow::updateVisualizer(QListWidgetItem* newItem)
{
    /*auto selectedItems = ui->entryListWidget->selectedItems();
    if (selectedItems.length() != 0)
    {
        auto selectedItem = selectedItems.first();
        ui->dataVisualizer->document()->setPlainText(selectedItem->text());
    }*/

    auto entryLabelNewItem = static_cast<EntryLabel*>(newItem);
    ui->dataVisualizer->document()->setPlainText(entryLabelNewItem->getEntry()->toQString());
}


QString MainWindow::GetRandomString(int randomStringLength)
{
   const QString possibleCharacters("abcdefghijklmnopqrstuvwxyz0123456789");

   QString randomString;
   for(int i=0; i<randomStringLength; ++i)
   {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }
   return randomString;
}
