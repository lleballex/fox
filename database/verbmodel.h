#ifndef VERBMODEL_H
#define VERBMODEL_H


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
        static const int image = 5;
    };

protected:
    struct Verb {
        char v1[30];
        char v2[30];
        char v3[30];
        char translate[30];
        int level;
        char image[30];
    };

    int getVerbsCount(int level = 0);
    Verb *getVerbs(int level = 0);
};


#endif // VERBMODEL_H
