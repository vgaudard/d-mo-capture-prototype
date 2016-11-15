
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "metadatadialog.h"
#include "entrylabel.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dialog(this),
    stringListModel(this)
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
                     this, SLOT(updateVisualizer(QListWidgetItem*, QListWidgetItem*)));


    stringListModel.setStringList(stringList);

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
    QFile file("metadata");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);

    out << entries;
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


void MainWindow::updateVisualizer(QListWidgetItem* newItem, QListWidgetItem* oldItem)
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
