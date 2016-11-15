#include "metadatadialog.h"
#include "ui_metadatadialog.h"


bool MetadataDialog::staticVariablesInitialized = false;
std::map<QString, AgeGroup> MetadataDialog::ageGroupMap = std::map<QString, AgeGroup>();
std::map<QString, Sex> MetadataDialog::sexMap = std::map<QString, Sex>();
std::map<QString, DominantHand> MetadataDialog::dominantHandMap = std::map<QString, DominantHand>();

MetadataDialog::MetadataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MetadataDialog)
{
    ui->setupUi(this);

    if (!staticVariablesInitialized)
    {
        ageGroupMap["<12"] = AGE_GROUP_BELOW_12;
        ageGroupMap["12-17"] = AGE_GROUP_12_TO_17;
        ageGroupMap["18-25"] = AGE_GROUP_18_TO_25;
        ageGroupMap["26-40"] = AGE_GROUP_26_TO_40;
        ageGroupMap["41-60"] = AGE_GROUP_41_TO_60;
        ageGroupMap[">60"] = AGE_GROUP_OVER_60;
        ageGroupMap["N/A"] = AGE_GROUP_UNKNOWN;
        ageGroupMap[""] = AGE_GROUP_UNKNOWN;

        sexMap["M"] = SEX_MALE;
        sexMap["F"] = SEX_FEMALE;
        sexMap["Other"] = SEX_OTHER;
        sexMap["N/A"] = SEX_UNKNOWN;
        sexMap[""] = SEX_UNKNOWN;

        dominantHandMap["Left"] = DOMINANT_HAND_LEFT;
        dominantHandMap["Right"] = DOMINANT_HAND_RIGHT;
        dominantHandMap["Ambidextrous"] = DOMINANT_HAND_AMBIDEXTROUS;
        dominantHandMap["N/A"] = DOMINANT_HAND_UNKNOWN;
        dominantHandMap[""] = DOMINANT_HAND_UNKNOWN;

        staticVariablesInitialized = true;
    }


    QObject::connect(ui->ageGroupComboBox, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(setAgeGroup()));

    QObject::connect(ui->dominantHandComboBox, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(setDominantHand()));

    QObject::connect(ui->sexComboBox, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(setSex()));

    QObject::connect(ui->usedToVideoGamesAndInteractionSystemsCheckBox, SIGNAL(clicked()),
                     this, SLOT(setComputerLitterate()));

    QObject::connect(ui->notesTextEdit, SIGNAL(textChanged()),
                     this, SLOT(setNotes()));
}

MetadataDialog::~MetadataDialog()
{
    delete ui;
}

Entry* MetadataDialog::getEntry() const
{
    return entry;
}

void MetadataDialog::setEntry(Entry *entry)
{
    this->entry = entry;
}

void MetadataDialog::setAgeGroup()
{
    entry->setAgeGroup(ageGroupMap[ui->ageGroupComboBox->currentText()]);
}

void MetadataDialog::setSex()
{
    entry->setSex (sexMap[ui->sexComboBox->currentText()]);
}

void MetadataDialog::setDominantHand()
{
    entry->setDominantHand(dominantHandMap[ui->dominantHandComboBox->currentText()]);
}

void MetadataDialog::setComputerLitterate()
{
    entry->setComputerLitterate(ui->usedToVideoGamesAndInteractionSystemsCheckBox->isChecked());
}

void MetadataDialog::setNotes()
{
    entry->setNotes(ui->notesTextEdit->toPlainText());
}
