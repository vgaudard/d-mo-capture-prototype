#ifndef UTILS_H
#define UTILS_H

#include <QString>


class Utils
{
public:
    static QString GetRandomString(int randomStringLength = 6);

private:
    Utils();
};

#endif // UTILS_H
