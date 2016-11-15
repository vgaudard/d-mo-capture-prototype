#ifndef METADATADIALOG_H
#define METADATADIALOG_H

#include <QDialog>

#include <map>
#include <list>

#include "entry.h"

namespace Ui {
class MetadataDialog;
}

class MetadataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MetadataDialog(QWidget *parent = 0);
    ~MetadataDialog();
    void setEntry(Entry *entry);
    Entry* getEntry() const;

private slots:
    void setAgeGroup();
    void setSex();
    void setDominantHand();
    void setComputerLitterate();
    void setNotes();

private:
    Ui::MetadataDialog *ui;
    Entry* entry;

    static bool staticVariablesInitialized;
    static std::map<QString, AgeGroup> ageGroupMap;
    static std::map<QString, Sex> sexMap;
    static std::map<QString, DominantHand> dominantHandMap;
};

#endif // METADATADIALOG_H
