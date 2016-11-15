#ifndef ENTRY_H
#define ENTRY_H

#include <string>

#include <QDataStream>

typedef enum _ageGroup {
    AGE_GROUP_UNKNOWN,
    AGE_GROUP_BELOW_12,
    AGE_GROUP_12_TO_17,
    AGE_GROUP_18_TO_25,
    AGE_GROUP_26_TO_40,
    AGE_GROUP_41_TO_60,
    AGE_GROUP_OVER_60

} AgeGroup;



typedef enum _sex {
    SEX_UNKNOWN,
    SEX_MALE,
    SEX_FEMALE,
    SEX_OTHER
} Sex;

typedef enum _dominantHand {
    DOMINANT_HAND_UNKNOWN,
    DOMINANT_HAND_LEFT,
    DOMINANT_HAND_RIGHT,
    DOMINANT_HAND_AMBIDEXTROUS
} DominantHand;

class Entry
{
public:
    Entry();
    Entry(AgeGroup ageGroup,Sex sex,DominantHand dominantHand, bool computerLitterate, QString notes);
    Entry(const Entry& entry);
    void operator=(const Entry& entry);
    virtual ~Entry();


    AgeGroup getAgeGroup();
    Sex getSex();
    DominantHand getDominantHand();
    bool getComputerLitterate();
    QString getNotes();

    void setAgeGroup(AgeGroup);
    void setSex(Sex);
    void setDominantHand(DominantHand);
    void setComputerLitterate(bool);
    void setNotes(QString);

    QString toQString() const;

    friend bool operator==(const Entry& entry1, const Entry& entry2);
    friend QDataStream &operator<<(QDataStream& dataStream, const Entry* entry);
    friend QDataStream &operator>>(QDataStream& dataStream, Entry* entry);


private:
    AgeGroup ageGroup;
    Sex sex;
    DominantHand dominantHand;
    bool computerLitterate;
    QString notes;
};

bool operator==(const Entry& entry1, const Entry& entry2);

QDataStream &operator<<(QDataStream& dataStream, const Entry* entry);
QDataStream &operator>>(QDataStream& dataStream, Entry* entry);


#endif // ENTRY_H
