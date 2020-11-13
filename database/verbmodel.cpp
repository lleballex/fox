#include "verbmodel.h"

#include <QVariant>
#include <QSqlQuery>


VerbModel::VerbModel() {}


int VerbModel::getVerbsCount(int level)
{
    QString q = "SELECT COUNT(*) FROM verbs";
    if(level > 0) q = QString("SELECT COUNT(*) FROM verbs WHERE level = %1").arg(level);

    QSqlQuery query(q);
    query.next();
    return query.value(0).toInt();
}


int VerbModel::getStartVerbId(int level)
{
    QSqlQuery query(QString("SELECT id FROM verbs WHERE level = %1").arg(level));
    query.next();
    return query.value(0).toInt();
}


VerbModel::Verb *VerbModel::getVerbs(int level)
{
    int verbsCount = getVerbsCount(level);
    QString q = "SELECT * FROM verbs";
    if(level > 0) q = QString("SELECT * FROM verbs WHERE level = %1").arg(level);

    VerbModel::Verb *verbs = new VerbModel::Verb[verbsCount];
    QSqlQuery query(q);

    for(int i = 0; i < verbsCount; i++) {
        query.next();
        VerbModel::Verb verb;
        verb.id = query.value(VerbModel::INDEXES::id).toInt();
        strcpy(verb.v1, query.value(VerbModel::INDEXES::v1).toString().toUtf8());
        strcpy(verb.v2, query.value(VerbModel::INDEXES::v2).toString().toUtf8());
        strcpy(verb.v3, query.value(VerbModel::INDEXES::v3).toString().toUtf8());
        strcpy(verb.translate, query.value(VerbModel::INDEXES::translate).toString().toUtf8());
        verb.level = query.value(VerbModel::INDEXES::level).toInt();
        strcpy(verb.image, query.value(VerbModel::INDEXES::image).toString().toUtf8());
        verbs[i] = verb;
    }

    return verbs;
}


VerbModel::Verb VerbModel::getVerb(int id)
{
    QSqlQuery query(QString("SELECT * FROM verbs WHERE id = %1").arg(id));
    query.next();

    VerbModel::Verb verb;
    verb.id = query.value(VerbModel::INDEXES::id).toInt();
    strcpy(verb.v1, query.value(VerbModel::INDEXES::v1).toString().toUtf8());
    strcpy(verb.v2, query.value(VerbModel::INDEXES::v2).toString().toUtf8());
    strcpy(verb.v3, query.value(VerbModel::INDEXES::v3).toString().toUtf8());
    strcpy(verb.translate, query.value(VerbModel::INDEXES::translate).toString().toUtf8());
    verb.level = query.value(VerbModel::INDEXES::level).toInt();
    strcpy(verb.image, query.value(VerbModel::INDEXES::image).toString().toUtf8());

    return verb;
}
