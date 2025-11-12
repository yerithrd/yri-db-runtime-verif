/*
* YERITH_QVGE_sample_TaintAnalysis.hpp
*
*/

#ifndef _YRI_DB_VERIF_RUNTIME_MONITOR_YERITH_QVGE_sample_TaintAnalysis_HPP_
#define _YRI_DB_VERIF_RUNTIME_MONITOR_YERITH_QVGE_sample_TaintAnalysis_HPP_

#include "src/include/yri-db-runtime-verif-MONITOR__Analysis_CHECKING_Testing.hpp"

#include "src/yri_sd_runtime_verif/utils/YRI_CPP_UTILS.hpp"

#include "src/yri_sd_runtime_verif/YRI_CPP_MONITOR_object.hpp"


#include <QtCore/QDebug>


class YRI_CPP_MONITOR_EDGE;
class YRI_CPP_MONITOR;


class YERITH_QVGE_sample_CLIENT_TaintAnalysis : public YRI_DB_RUNTIME_VERIF_analysis_Checking_TESTING
{
    Q_OBJECT

public:

    static void YRI_CALL_BACK_final_state(YRI_CPP_MONITOR 		*a_runtime_monitor,
                                          YRI_CPP_MONITOR_EDGE 	*an_EDGE_leading_TO_error_FINAL_state);

    YERITH_QVGE_sample_CLIENT_TaintAnalysis();

    YERITH_QVGE_sample_CLIENT_TaintAnalysis(YRI_DB_RUNTIME_VERIF_Logger *logger);

    virtual inline ~YERITH_QVGE_sample_CLIENT_TaintAnalysis()
    {
    }

public slots:


    virtual bool ___Fixture___CREATE_Tainted_Analysis_DB_SQL_table_ONCE___();


    /**
    * THIS METHOD PERFORMS EFFECTIVE TEMPORAL LINEAR
    * LOGIC CHECK AFTER A STATE EVENT (or system event)
    * could be achieved by the runtime monitor system !
    *
    * A SERIOUS VERIFICATION CLIENT MUST OVERRIDE THIS
    * METHOD !
    */
    virtual bool DO_VERIFY_AND_or_CHECK_ltl_PROPERTY(
        QString sql_table_ADDED_with_file_AND_line_number,
        uint	sql_record_qty_MODIFIED,
        YRI_CPP_UTILS::SQL_CONSTANT_IDENTIFIER cur_SQL_command =
            YRI_CPP_UTILS::SQL_CONSTANT_IDENTIFIER::UNDEFINED_SQL_COMMAND);


protected:


    QMap<QString, QString>  ___taint_analysis___Event___TO___Input_Value;


    QString ___sql_db_table_Column_sanitizers_methods;

    QString ___sql_db_table_Column_taint_methods;

    QString ___sql_db_table_Column_tainted_values;

};


#endif /* _YRI_DB_VERIF_RUNTIME_MONITOR_YERITH_QVGE_sample_TaintAnalysis_HPP_ */

