#include "verbmodel.h"

#include <QVariant>
#include <QSqlQuery>


VerbModel::VerbModel() {}


int VerbModel::getVerbsCount(int level, QString text)
{
    QString q = "SELECT COUNT(*) FROM verbs";
    if(!text.isEmpty()) q = QString("SELECT COUNT(*) FROM verbs WHERE v_1 LIKE '%%1%' OR v_2 LIKE '%%1%' OR v_3 LIKE '%%1%' OR translate LIKE '%%1%'").arg(text);
    else if(level > 0) q = QString("SELECT COUNT(*) FROM verbs WHERE level = %1").arg(level);

    QSqlQuery query(q);
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
        strcpy(verb.v1, query.value(VerbModel::INDEXES::v1).toString().toUtf8());
        strcpy(verb.v2, query.value(VerbModel::INDEXES::v2).toString().toUtf8());
        strcpy(verb.v3, query.value(VerbModel::INDEXES::v3).toString().toUtf8());
        strcpy(verb.translate, query.value(VerbModel::INDEXES::translate).toString().toUtf8());
        verb.level = query.value(VerbModel::INDEXES::level).toInt();
        verbs[i] = verb;
    }

    return verbs;
}

VerbModel::Verb *VerbModel::searchVerbs(QString text)
{
    int verbsCount = getVerbsCount(0, text);

    QString q = QString("SELECT * FROM verbs WHERE v_1 LIKE '%%1%' OR v_2 LIKE '%%1%' OR v_3 LIKE '%%1%' OR translate LIKE '%%1%'").arg(text);
    VerbModel::Verb *verbs = new VerbModel::Verb[verbsCount];
    QSqlQuery query(q);

    for(int i = 0; i < verbsCount; i++) {
        query.next();
        VerbModel::Verb verb;
        strcpy(verb.v1, query.value(VerbModel::INDEXES::v1).toString().toUtf8());
        strcpy(verb.v2, query.value(VerbModel::INDEXES::v2).toString().toUtf8());
        strcpy(verb.v3, query.value(VerbModel::INDEXES::v3).toString().toUtf8());
        strcpy(verb.translate, query.value(VerbModel::INDEXES::translate).toString().toUtf8());
        verb.level = query.value(VerbModel::INDEXES::level).toInt();
        verbs[i] = verb;
    }

    return verbs;
}
