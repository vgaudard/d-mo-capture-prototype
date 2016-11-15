#ifndef ENTRYLABEL_H
#define ENTRYLABEL_H

#include <QWidget>
#include <QListWidgetItem>

#include "entry.h"

class EntryLabel : public QListWidgetItem
{
public:
    explicit EntryLabel(Entry* entry, QListWidget *parent = 0);
    ~EntryLabel();
    Entry* getEntry();

private:
    Entry* _entry;
};

#endif // ENTRYLABEL_H
