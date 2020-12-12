#ifndef VERBMODEL_H
#define VERBMODEL_H

#include <QString>


class VerbModel
{
public:
    VerbModel();

private:
    struct INDEXES {
        static const int v1 = 0;
        static const int v2 = 1;
        static const int v3 = 2;
        static const int translate = 3;
        static const int level = 4;
    };

protected:
    struct Verb {
        char v1[30];
        char v2[70];
        char v3[70];
        char translate[70];
        int level;
    };

    int getVerbsCount(int level = 0, QString text = "");
    Verb *getVerbs(int level = 0);
    Verb *searchVerbs(QString text);
};


#endif // VERBMODEL_H
