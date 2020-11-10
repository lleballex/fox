#ifndef VERBMODEL_H
#define VERBMODEL_H


class VerbModel
{
public:
    VerbModel();

private:
    struct INDEXES {
        static const int id = 0;
        static const int v1 = 1;
        static const int v2 = 2;
        static const int v3 = 3;
        static const int translate = 4;
    };

protected:
    struct Verb {
        int id;
        char v1[30];
        char v2[30];
        char v3[30];
        char translate[30];
    };

    int getVerbsCount(int level = 0);
    int getStartVerbId(int level);
    Verb *getVerbs(int level = 0);
    Verb getVerb(int id);
};


#endif // VERBMODEL_H
