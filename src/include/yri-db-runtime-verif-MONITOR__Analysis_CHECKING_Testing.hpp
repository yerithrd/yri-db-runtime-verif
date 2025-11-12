/*
 * yri-db-runtime-verif-MONITOR__Analysis_CHECKING_Testing.hpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */

#ifndef _YRI_DB_RUNTIME_VERIF_MONITOR_analysis_checking_TESTing_HPP_
#define _YRI_DB_RUNTIME_VERIF_MONITOR_analysis_checking_TESTing_HPP_


#include "src/include/yri-db-runtime-verif-MONITOR.hpp"



class YRI_DB_RUNTIME_VERIF_analysis_Checking_TESTING : public YRI_DB_RUNTIME_VERIF_Monitor
{
	Q_OBJECT

public:

	inline YRI_DB_RUNTIME_VERIF_analysis_Checking_TESTING()
	:YRI_DB_RUNTIME_VERIF_Monitor()
	{
	}


    inline YRI_DB_RUNTIME_VERIF_analysis_Checking_TESTING(QString 	                    RUNTIME_MONITOR_NAME,
                                                           YRI_DB_RUNTIME_VERIF_Logger 	*aLogger)
    :YRI_DB_RUNTIME_VERIF_Monitor(RUNTIME_MONITOR_NAME,
                                  aLogger)
    {
    }


    inline YRI_DB_RUNTIME_VERIF_analysis_Checking_TESTING(YRI_DB_RUNTIME_VERIF_Logger *aLogger)
    :YRI_DB_RUNTIME_VERIF_Monitor(aLogger)
    {
    }


    virtual inline ~YRI_DB_RUNTIME_VERIF_analysis_Checking_TESTING()
    {
    }


protected:

    virtual QString ___CREATE___Analysis___DB_SQL_table_creation_MariaDB_query();


public slots:


    /**
     * SETUP code for a tainted analysis.
     */
    virtual bool ___Fixture___CREATE_Tainted_Analysis_DB_SQL_table_ONCE___();


    virtual bool ___Fixture__Insert___INTO__DB__SQL__values___(QString a_Sql_Table_DATABASE_Column___Property,
                                                               QString an_Event_Related_value);


public:

    virtual inline void SET___sql_db_table_name(QString _sql_db_table_name)
    {
        ___sql_db_table_name = _sql_db_table_name;
    }

    virtual inline QString GET___sql_db_table_name()
    {
        return ___sql_db_table_name;
    }


    static const uint DB_SQL_analysis_table_column_MAX_length;


protected:

    QString          ___sql_db_table_name;

    QList<QString>   ___sql_db_table_Columns;
};


#endif /* _YRI_DB_RUNTIME_VERIF_MONITOR_analysis_checking_TESTing_HPP_ */
