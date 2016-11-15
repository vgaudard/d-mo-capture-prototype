#include "entry.h"

AgeGroup ageGroup;
Sex sex;
DominantHand dominantHand;
bool computerLitterate;
std::string notes;

static const char* ageGroupString[] = {
    "AGE_GROUP_UNKNOWN",
    "AGE_GROUP_BELOW_12",
    "AGE_GROUP_12_TO_17",
    "AGE_GROUP_18_TO_25",
    "AGE_GROUP_26_TO_40",
    "AGE_GROUP_41_TO_60",
    "AGE_GROUP_OVER_60"
};



static const char* sexString[] {
    "SEX_UNKNOWN",
    "SEX_MALE",
    "SEX_FEMALE",
    "SEX_OTHER"
};

static const char* dominantHandString[] {
    "DOMINANT_HAND_UNKNOWN",
    "DOMINANT_HAND_LEFT",
    "DOMINANT_HAND_RIGHT",
    "DOMINANT_HAND_AMBIDEXTROUS"
};


Entry::Entry() :
    ageGroup(AGE_GROUP_UNKNOWN),
    sex(SEX_UNKNOWN),
    dominantHand(DOMINANT_HAND_UNKNOWN),
    computerLitterate(false),
    notes("")
{
}

Entry::Entry(AgeGroup ageGroup,Sex sex,DominantHand dominantHand, bool computerLitterate, QString notes) :
    ageGroup(ageGroup),
    sex(sex),
    dominantHand(dominantHand),
    computerLitterate(computerLitterate),
    notes(notes)
{
}

Entry::Entry(const Entry& entry)
{
    ageGroup = entry.ageGroup;
    sex = entry.sex;
    dominantHand = entry.dominantHand;
    computerLitterate = entry.computerLitterate;
    notes = entry.notes;
}

void Entry::operator=(const Entry& entry)
{
    ageGroup = entry.ageGroup;
    sex = entry.sex;
    dominantHand = entry.dominantHand;
    computerLitterate = entry.computerLitterate;
    notes = entry.notes;
}

Entry::~Entry()
{
}


AgeGroup Entry::getAgeGroup()
{
    return ageGroup;
}

Sex Entry::getSex()
{
    return sex;
}

DominantHand Entry::getDominantHand()
{
    return dominantHand;
}

bool Entry::getComputerLitterate()
{
    return computerLitterate;
}

QString Entry::getNotes()
{
    return notes;
}


void Entry::setAgeGroup(AgeGroup ageGroup)
{
    this->ageGroup = ageGroup;
}

void Entry::setSex(Sex sex)
{
    this->sex = sex;
}

void Entry::setDominantHand(DominantHand dominantHand)
{
    this->dominantHand = dominantHand;
}

void Entry::setComputerLitterate(bool computerLitterate)
{
    this->computerLitterate = computerLitterate;
}

void Entry::setNotes(QString notes)
{
    this->notes = notes;
}

QString Entry::toQString() const
{
    return QString("{%1,%2,%3,%4,%5}")
            .arg(ageGroupString[ageGroup])
            .arg(sexString[sex])
            .arg(dominantHandString[dominantHand])
            .arg(computerLitterate)
            .arg(notes);
}


bool operator==(const Entry& entry1, const Entry& entry2)
{
    return entry1.ageGroup == entry2.ageGroup &&
            entry1.computerLitterate == entry2.computerLitterate &&
            entry1.dominantHand == entry2.dominantHand &&
            entry1.notes == entry2.notes &&
            entry1.sex == entry2.sex;
}

QDataStream &operator<<(QDataStream& dataStream, const Entry* entry)
{
    // TODO
    return dataStream << entry->toQString();
}

QDataStream &operator>>(QDataStream& dataStream, Entry* entry)
{
    // TODO
    return dataStream;
}
