/*
 * yri-db-runtime-verif-MONITOR__Analysis_CHECKING_Testing.cpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */

#include "yri-db-runtime-verif-MONITOR__Analysis_CHECKING_Testing.hpp"




const uint YRI_DB_RUNTIME_VERIF_analysis_Checking_TESTING::DB_SQL_analysis_table_column_MAX_length = 256;




QString YRI_DB_RUNTIME_VERIF_analysis_Checking_TESTING::
                        ___CREATE___Analysis___DB_SQL_table_creation_MariaDB_query()
{
    if (___sql_db_table_Columns.size() <= 0)
    {
        return YRI_DB_RUNTIME_VERIF_Utils::EMPTY_STRING;
    }


    QString str__create__table__tainted__analysis___query =
                QString("create table %1 (id int auto_increment primary key, ")
                  .arg(GET___sql_db_table_name());


    int max_db_sql_table_Column_SIZE_count = 9;



    QDEBUG_STRINGS_OUTPUT_2_N(QString("___CREATE___Analysis___DB_SQL_table_creation_MariaDB_query || %1 || column count || ")
                                .arg(GET___sql_db_table_name()),
                                     ___sql_db_table_Columns.size());



    if (___sql_db_table_Columns.size() < max_db_sql_table_Column_SIZE_count)
    {
        max_db_sql_table_Column_SIZE_count = ___sql_db_table_Columns.size();
    }



    for(uint k = 0; k < max_db_sql_table_Column_SIZE_count - 1; ++k)
    {
        str__create__table__tainted__analysis___query
            .append(QString("%1 varchar(50), ")
                      .arg(___sql_db_table_Columns.at(k)));
    }


    str__create__table__tainted__analysis___query
        .append(QString("%1 varchar(%2) ); ")
                  .arg(___sql_db_table_Columns.at(max_db_sql_table_Column_SIZE_count-1),
                       QString::number(DB_SQL_analysis_table_column_MAX_length)));



    QDEBUG_STRINGS_OUTPUT_2("Generated SQL mariadb create table query | ",
                             str__create__table__tainted__analysis___query);


    return str__create__table__tainted__analysis___query;
}


bool YRI_DB_RUNTIME_VERIF_analysis_Checking_TESTING::
            ___Fixture___CREATE_Tainted_Analysis_DB_SQL_table_ONCE___()
{
    QString query_STRING_for_sql_db_table_CreatiON =
                ___CREATE___Analysis___DB_SQL_table_creation_MariaDB_query();



    if (query_STRING_for_sql_db_table_CreatiON.isEmpty())
    {
        return false;
    }



    bool creation_of_db_sql_table = YRI_DB_RUNTIME_VERIF_Utils::execQuery(query_STRING_for_sql_db_table_CreatiON);


    if (! creation_of_db_sql_table)
    {
        QDEBUG_STRING_OUTPUT_2("COULDN'T CREATE analysis SQL database table named:--",
                                GET___sql_db_table_name());
    }
    else
    {
        QDEBUG_STRING_OUTPUT_2("COULD CREATE analysis SQL database table named:--",
                                GET___sql_db_table_name());
    }


    return creation_of_db_sql_table;
}


bool YRI_DB_RUNTIME_VERIF_analysis_Checking_TESTING::
            ___Fixture__Insert___INTO__DB__SQL__values___(QString a_Sql_Table_DATABASE_Column___Property,
                                                          QString an_Event_Related_value)
{
    QString db_Sql_TABLE_insertion_Query = QString("insert into %1 (%2) values ('%3')")
                                                .arg(___sql_db_table_name,
                                                     a_Sql_Table_DATABASE_Column___Property,
                                                     an_Event_Related_value);


    bool success_insertion = YRI_DB_RUNTIME_VERIF_Utils::execQuery(db_Sql_TABLE_insertion_Query);


    QDEBUG_STRING_OUTPUT_2_BOOL(QString("db_Sql_TABLE_insertion_Query | %1 ||| ")
                                  .arg(db_Sql_TABLE_insertion_Query),
                                success_insertion);


    return success_insertion;
}




