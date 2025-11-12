/*
 * yri-db-runtime-verif-sqltable-model.cpp
 *
  *      Author: Pr. Prof. Dr. Xavier Noundou
 */

#include "yri-db-runtime-verif-sqltable-model.hpp"

#include "src/utils/yri-db-runtime-verif-database-table-column.hpp"

#include "src/utils/yri-db-runtime-verif-utils.hpp"

#include <QtCore/QDebug>

#include <QtSql/QSqlRecord>

#include <QtSql/QSqlQuery>

#include <QtSql/QSqlError>

#include <QtWidgets/QMainWindow>

#include <QtWidgets/QMessageBox>

#include "yri-db-runtime-verif-logger.hpp"


YRI_DB_RUNTIME_VERIF_SqlTableModel::YRI_DB_RUNTIME_VERIF_SqlTableModel():_logger(0),
    _fromQSqlQuery
    (false)
{
    _logger = new YRI_DB_RUNTIME_VERIF_Logger("YerothSqlTableModel");

    setEditStrategy(QSqlTableModel::OnFieldChange);
}


YRI_DB_RUNTIME_VERIF_SqlTableModel::
YRI_DB_RUNTIME_VERIF_SqlTableModel(const QSqlQuery &aQSqlQuery):
    _logger(0),
    _fromQSqlQuery(true)
{
    _logger = new YRI_DB_RUNTIME_VERIF_Logger("YerothSqlTableModel");

    yerithSetQuery(aQSqlQuery);

    setEditStrategy(QSqlTableModel::OnFieldChange);
}


YRI_DB_RUNTIME_VERIF_SqlTableModel::
YRI_DB_RUNTIME_VERIF_SqlTableModel(const QString &sqlTableName,
                                  bool setTableName /* = true */)
    :
    _sqlTableName(sqlTableName),
    _logger(0),
    _fromQSqlQuery(false)
{
    _logger = new YRI_DB_RUNTIME_VERIF_Logger("YerothSqlTableModel");

    _logger->log("YerothSqlTableModel",
                 QString
                 ("table name: %1, edit strategy: QSqlTableModel::OnFieldChange").arg
                 (sqlTableName));

    if (setTableName)
    {
        setTable(sqlTableName);
    }

    setEditStrategy(QSqlTableModel::OnFieldChange);
}


YRI_DB_RUNTIME_VERIF_SqlTableModel::~YRI_DB_RUNTIME_VERIF_SqlTableModel()
{
    YERITH_DELETE_FREE_POINTER_NOW(_logger);
}


int
YRI_DB_RUNTIME_VERIF_SqlTableModel::
yerith_RESET_specify_filter_FROM_SELECT_STATEMENT(const QString &filter)
{
    QString curYerothSelectStatement(yerithSelectStatement());

    curYerothSelectStatement.remove(filter);

//      QDEBUG_STRING_OUTPUT_2("RESET filter", curYerothSelectStatement);

    int queryResultSize = yerithSetQueryRowCount(curYerothSelectStatement);

    return queryResultSize;
}


int
YRI_DB_RUNTIME_VERIF_SqlTableModel::
yerith_specify_filter_FROM_SELECT_STATEMENT(const QString &filter)
{
    QString curYerothSelectStatement(yerithSelectStatement());

    curYerothSelectStatement.append(QString(" %1").arg(filter));

//      QDEBUG_STRING_OUTPUT_2("filter", curYerothSelectStatement);

    int queryResultSize = yerithSetQueryRowCount(curYerothSelectStatement);

    return queryResultSize;
}


int YRI_DB_RUNTIME_VERIF_SqlTableModel::Is_SearchQSqlTable(QString tableColumn,
                                                          QString searchTerm)
{
    QString queryFilter(GENERATE_SQL_IS_STMT(tableColumn, searchTerm));

    yerithSetFilter_WITH_where_clause(queryFilter);

    int filterRowCount = rowCount();

    _logger->log("Is_SearchQSqlTable",
                 QString
                 ("(table: %1, column: %2) | queryFilter (%3) | row count: %4").arg
                 (_sqlTableName, tableColumn, queryFilter,
                  QString::number(filterRowCount)));
    resetFilter();

    return filterRowCount;
}


int
YRI_DB_RUNTIME_VERIF_SqlTableModel::
_Is_SearchQSqlTable(enum YerothSqlQueryType, QString tableColumn,
                    QStringList &searchTermsList)
{
    QString queryTerm;

    const int size = searchTermsList.size();
    const int max = size - 1;

    for (int k = 0; k < size; ++k)
    {
        if (k < max)
        {
            queryTerm.append(GENERATE_SQL_IS_STMT
                             (tableColumn,
                              searchTermsList.at(k))).append(" AND ");
        }
        else
        {
            queryTerm.append(GENERATE_SQL_IS_STMT
                             (tableColumn, searchTermsList.at(k)));
        }
    }

    yerithSetFilter_WITH_where_clause(queryTerm);

    int filterRowCount = rowCount();

    resetFilter();

    return filterRowCount;
}

int YRI_DB_RUNTIME_VERIF_SqlTableModel::Like_SearchQSqlTable(QString tableColumn,
                                                            QString searchTerm)
{
    QString queryFilter(GENERATE_SQL_LIKE_STMT(tableColumn, searchTerm));

    yerithSetFilter_WITH_where_clause(queryFilter);

    int filterRowCount = rowCount();

    _logger->log("Like_SearchQSqlTable",
                 QString
                 ("(table: %1, column: %2) | queryFilter (%3) | row count: %4").arg
                 (_sqlTableName).arg(tableColumn).
                 arg(queryFilter).arg(filterRowCount));

    /*qDebug() <<
       QString("YerothSqlTableModel | Like_SearchQSqlTable (table: %1, column: %2) \n\t\t| queryFilter (%3) | row count: %4")
       .arg(_sqlTableName)
       .arg(tableColumn)
       .arg(queryFilter)
       .arg(filterRowCount); */

    resetFilter();

    return filterRowCount;
}

int
YRI_DB_RUNTIME_VERIF_SqlTableModel::
_Like_SearchQSqlTable(enum YerothSqlQueryType, QString tableColumn,
                      QStringList &searchTermsList)
{
    QString queryTerm;

    const int size = searchTermsList.size();
    const int max = size - 1;

    for (int k = 0; k < size; ++k)
    {
        if (k < max)
        {
            queryTerm.append(GENERATE_SQL_LIKE_STMT
                             (tableColumn,
                              searchTermsList.at(k))).append(" AND ");
        }
        else
        {
            queryTerm.append(GENERATE_SQL_LIKE_STMT
                             (tableColumn, searchTermsList.at(k)));
        }
    }

    yerithSetFilter_WITH_where_clause(queryTerm);

    int filterRowCount = rowCount();

    resetFilter();

    return filterRowCount;
}

bool YRI_DB_RUNTIME_VERIF_SqlTableModel::insertNewRecord(QSqlRecord &record,
                                                        QMainWindow *parent)
{
    _logger->log("insertNewRecord",
                 QString("Table name: %1").arg(sqlTableName()));

    resetFilter();

    YERITH_ERP_3_0_START_DATABASE_TRANSACTION;

    bool success = insertRecord(-1, record);

    YERITH_ERP_3_0_COMMIT_DATABASE_TRANSACTION;

    //qDebug() << QString("YerothSqlTableModel::insertNewRecord, success: %1")
    //                          .arg(BOOL_TO_STRING(success));

    if (!success)
    {
        QString retMsg(QObject::trUtf8
                       ("Une erreur (base de données) est survenue pendant l'insertion dans le tableau %1 !\n").arg
                       (sqlTableName()));

        retMsg.append(QObject::trUtf8
                      ("Contactez l'administrateur de Yeroth-pgi-3.0 !"));

        if (0 != parent)
        {
            QMessageBox::warning(parent,
                                 QObject::tr
                                 ("sqltablemodel - insertNewRecord"), retMsg);
        }

        qDebug() <<
                 QString("%1 - reason for failing: %2").arg(sqlTableName(),
                                                            lastError().text());

        _logger->log("insertNewRecord",
                     QString("reason for failing: %1").
                     arg(lastError().text()));
    }

    return success;
}


//bool YerothSqlTableModel::updateRecord(QSqlRecord &record)
//{
//    _logger->log("updateRecord",
//                 QString("Table name: %1").arg(sqlTableName()));
//
//    bool success = false;
//
//    QString aCurFieldValue;
//
//    QString dbFieldIDValue;
//
//    QString aCurFieldName;
//
//    QString SQL_UPDATE_STRING_COMMAND = QString("UPDATE %1 SET ")
//                                                                              .arg(_sqlTableName);
//
//    for (int k = 0; k < record.count(); ++k)
//    {
//      aCurFieldName.clear();
//
//      aCurFieldName.append(record.fieldName(k));
//
//      if (!YRI_DB_RUNTIME_VERIF_Utils::isEqualCaseInsensitive(YerothDatabaseTableColumn::ID, aCurFieldName))
//      {
//              if (!aCurFieldName.contains("date_"))
//              {
//                      aCurFieldValue = YRI_DB_RUNTIME_VERIF_Utils::get_text(record.value(aCurFieldName));
//
//              SQL_UPDATE_STRING_COMMAND.append(QString("%1='%2', ")
//                                                                                      .arg(aCurFieldName,
//                                                                                               aCurFieldValue));
//              }
//              else
//              {
//                      aCurFieldValue = DATE_TO_DB_FORMAT_STRING(record.value(aCurFieldName).toDate());
//
////                            QDEBUG_STRING_OUTPUT_2("aCurFieldValue (DATE_TO_DB_FORMAT_STRING)", aCurFieldValue);
//
//                      if (!aCurFieldValue.isEmpty())
//                      {
//                              SQL_UPDATE_STRING_COMMAND.append(QString("%1='%2', ")
//                                                                                                      .arg(aCurFieldName,
//                                                                                                               aCurFieldValue));
//                      }
//              }
//      }
//      else
//      {
//              dbFieldIDValue = YRI_DB_RUNTIME_VERIF_Utils::get_text(record.value(aCurFieldName));
//      }
//    }
//
//    int len = SQL_UPDATE_STRING_COMMAND.length();
//
//    SQL_UPDATE_STRING_COMMAND.remove(len - 2, 2);
//
//      SQL_UPDATE_STRING_COMMAND.append(QString(" WHERE %1 = '%2';")
//                                                                              .arg(YerothDatabaseTableColumn::ID,
//                                                                                       dbFieldIDValue));
//
////    QDEBUG_STRING_OUTPUT_2("SQL_UPDATE_STRING_COMMAND", SQL_UPDATE_STRING_COMMAND);
//
//    success = YRI_DB_RUNTIME_VERIF_Utils::execQuery(SQL_UPDATE_STRING_COMMAND);
//
//    return success;
//}


bool YRI_DB_RUNTIME_VERIF_SqlTableModel::updateRecord(unsigned row,
                                                     QSqlRecord &record)
{
    _logger->log("updateRecord",
                 QString("Table name: %1").arg(sqlTableName()));

    YERITH_ERP_3_0_START_DATABASE_TRANSACTION;

    bool success = setRecord(row, record);

    YERITH_ERP_3_0_COMMIT_DATABASE_TRANSACTION;

    if (!success)
    {
        _logger->log("updateRecord",
                     QString("updating row %1. reason for failing: %2").arg
                     (QString::number(row), lastError().text()));
    }
    else
    {
        _logger->log("updateRecord",
                     QString("updated row %1 with success").arg(row));
    }

    return success;
}


void YRI_DB_RUNTIME_VERIF_SqlTableModel::resetFilter()
{
    yerithSetFilter_WITH_where_clause(YRI_DB_RUNTIME_VERIF_Utils::EMPTY_STRING);
    select();
}


int YRI_DB_RUNTIME_VERIF_SqlTableModel::easySelect()
{
    bool success = select();

    if (!success)
    {
        return -1;
    }

    return rowCount();
}


bool YRI_DB_RUNTIME_VERIF_SqlTableModel::yerithSetSort(int column,
                                                      Qt::SortOrder order)
{
    setSort(column, order);
    return select();
}

int
YRI_DB_RUNTIME_VERIF_SqlTableModel::
yerithSetQueryRowCount(const QString &STRING_aSqlQuery)
{
    QSqlQueryModel::setQuery(STRING_aSqlQuery);

    if (lastError().isValid())
    {
        qDebug() << "++ YerothSqlTableModel::yerithSetQuery(QString): \n\t"
                 << STRING_aSqlQuery << "\n" << lastError();

        return -1;
    }

    int queryResultRowCount = QSqlQueryModel::rowCount();

    return queryResultRowCount;
}


bool YRI_DB_RUNTIME_VERIF_SqlTableModel::yerithSetQuery(const QString &aSqlQuery)
{
    QSqlQueryModel::setQuery(aSqlQuery);

    if (lastError().isValid())
    {
        qDebug() << "++ YerothSqlTableModel::yerithSetQuery(QString): \n\t"
                 << aSqlQuery << "\n" << lastError();

        return false;
    }

    return true;
}
