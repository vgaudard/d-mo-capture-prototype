#include "entrylabel.h"

EntryLabel::EntryLabel(Entry* entry, QListWidget *parent) :
    QListWidgetItem(QString(entry->getNotes()),  parent),
    _entry(entry)
{
}

EntryLabel::~EntryLabel()
{
}

Entry* EntryLabel::getEntry()
{
    return _entry;
}
