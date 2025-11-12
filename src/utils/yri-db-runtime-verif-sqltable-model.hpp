/*
 * yri-db-runtime-verif-sqltable-model.hpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */

#ifndef _YRI_DB_RUNTIME_VERIF_SQLTABLE_MODEL_HPP_
#define _YRI_DB_RUNTIME_VERIF_SQLTABLE_MODEL_HPP_

#include <QtCore/QStringList>

#include <QtSql/QSqlRelationalTableModel>


class QMainWindow;
class YRI_DB_RUNTIME_VERIF_Logger;


enum YerothSqlQueryType
{
    OR = 0,
    AND = 1
};


class YRI_DB_RUNTIME_VERIF_SqlTableModel:public QSqlTableModel
{
public:

    YRI_DB_RUNTIME_VERIF_SqlTableModel();

    YRI_DB_RUNTIME_VERIF_SqlTableModel(const QSqlQuery &aQSqlQuery);

    YRI_DB_RUNTIME_VERIF_SqlTableModel(const QString &sqlTableName,
                                      bool setTableName = true);

    ~YRI_DB_RUNTIME_VERIF_SqlTableModel();

    inline bool isFromQSqlQuery()
    {
        return _fromQSqlQuery;
    }

    virtual int yerith_RESET_specify_filter_FROM_SELECT_STATEMENT(const QString
                                                                  & filter);

    virtual int yerith_specify_filter_FROM_SELECT_STATEMENT(const QString &
                                                            filter);

    inline virtual void yerithSetFilter_WITH_where_clause(const QString &
                                                          filter)
    {
        QSqlTableModel::setFilter(filter.trimmed());
    }

    inline void changeEditStrategy(QSqlTableModel::EditStrategy strategy)
    {
        setEditStrategy(strategy);
    }

    int Is_SearchQSqlTable(QString tableColumn, QString searchTerm);

    int _Is_SearchQSqlTable(enum YerothSqlQueryType,
                            QString tableColumn,
                            QStringList &searchTermsList);

    inline int OR_Is_SearchQSqlTable(QString tableColumn,
                                     QStringList &searchTermsList)
    {
        return _Is_SearchQSqlTable(OR, tableColumn, searchTermsList);
    }

    inline int AND_Is_SearchQSqlTable(QString tableColumn,
                                      QStringList &searchTermsList)
    {
        return _Is_SearchQSqlTable(AND, tableColumn, searchTermsList);
    }

    int Like_SearchQSqlTable(QString tableColumn, QString searchTerm);

    int _Like_SearchQSqlTable(enum YerothSqlQueryType,
                              QString tableColumn,
                              QStringList &searchTermsList);

    inline int OR_Like_SearchQSqlTable(QString tableColumn,
                                       QStringList &searchTermsList)
    {
        return _Like_SearchQSqlTable(OR, tableColumn, searchTermsList);
    }

    inline int AND_Like_SearchQSqlTable(QString tableColumn,
                                        QStringList &searchTermsList)
    {
        return _Like_SearchQSqlTable(AND, tableColumn, searchTermsList);
    }

    bool insertNewRecord(QSqlRecord &record, QMainWindow *parent = 0);

//      bool updateRecord(QSqlRecord &record);

    bool updateRecord(unsigned row, QSqlRecord &record);

    /*inline bool removeRow(int row)
       {
       return  removeRow(row);
       } */

    void resetFilter();

    inline QString sqlTableName()
    {
        return _sqlTableName;
    }

    inline void yerithSetQuery(const QSqlQuery &query)
    {
        QSqlTableModel::setQuery(query);
    }

    int easySelect();

    bool yerithSetSort(int column, Qt::SortOrder order);

    int yerithSetQueryRowCount(const QString &STRING_aSqlQuery);

    bool yerithSetQuery(const QString &aSqlQuery);

    inline QString yerithSelectStatement()
    {
        return QSqlTableModel::selectStatement();
    }

private:

    const QString _sqlTableName;

    YRI_DB_RUNTIME_VERIF_Logger *_logger;

    bool _fromQSqlQuery;
};

#endif /* _YRI_DB_RUNTIME_VERIF_SQLTABLE_MODEL_HPP_ */
