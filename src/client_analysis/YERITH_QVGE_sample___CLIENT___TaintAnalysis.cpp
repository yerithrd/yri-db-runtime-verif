/*
* YERITH_QVGE_sample_TaintAnalysis.cpp
*
*/

#include "YERITH_QVGE_sample___CLIENT___TaintAnalysis.hpp"


#include <QtSql/QSqlRecord>

#include <QtSql/QSqlQuery>

#include <QtSql/QSqlError>


#include "src/utils/yri-db-runtime-verif-logger.hpp"

#include "src/yri_sd_runtime_verif/YRI_CPP_MONITOR.hpp"
#include "src/yri_sd_runtime_verif/YRI_CPP_MONITOR_STATE.hpp"
#include "src/yri_sd_runtime_verif/YRI_CPP_MONITOR_EDGE.hpp"


void YERITH_QVGE_sample_CLIENT_TaintAnalysis::YRI_CALL_BACK_final_state(YRI_CPP_MONITOR 			*a_runtime_monitor,
        YRI_CPP_MONITOR_EDGE 	*an_EDGE_leading_TO_error_FINAL_state)
{
    if (0 != a_runtime_monitor)
    {
        ( (YRI_DB_RUNTIME_VERIF_Monitor *) a_runtime_monitor)
        ->YRI_DB_RUNTIME_VERIF_Monitor_notify_SUCCESS_VERIFICATION(an_EDGE_leading_TO_error_FINAL_state);
    }
}



YERITH_QVGE_sample_CLIENT_TaintAnalysis::YERITH_QVGE_sample_CLIENT_TaintAnalysis()
    :YRI_DB_RUNTIME_VERIF_analysis_Checking_TESTING()
{
    ___Fixture___CREATE_Tainted_Analysis_DB_SQL_table_ONCE___();

    set_RUNTIME_MONITOR_NAME("YERITH_QVGE_sample_CLIENT_TaintAnalysis");

    // ## PUT OUTPUT OF CALLING . ./YRI-create-executable-for-user-SDMM.sh -d projet-de-tests-yri-nissi
    // ## here.

//    YRI_CPP_MONITOR_EDGE *a_last_edge_1 = create_yri_monitor_edge ("T0", "TF");
//    a_last_edge_1->get_SOURCE_STATE()->set_START_STATE(*this, true);
//    a_last_edge_1->get_TARGET_STATE()->set_ERROR_STATE(true);
//    a_last_edge_1->get_SOURCE_STATE()->set_PRE_CONDITION_notIN("in", "yri_tainted_analysis.sanitizers_methods");
//    a_last_edge_1->get_TARGET_STATE()->set_POST_CONDITION_IN("i0", "yri_tainted_analysis.tainted_values");
//
//
//    YRI_CPP_notinset_inset_TRACE_expression *a_last_edge_1_GUARDED_CONDITION
//        = new YRI_CPP_notinset_inset_TRACE_expression(false,
//                "'SELECT.i0#sanitize'",
//                "T0");
//
//    a_last_edge_1->set_GUARDED_CONDITION(a_last_edge_1_GUARDED_CONDITION);
//
//
//    YRI_CPP_MONITOR_EVENT *a_last_edge_event_1 = a_last_edge_1->set_EDGE_EVENT("'INSERT.i0#in'");
//
//    //print_TO_dot_FILE();
//
    YRI_register_set_final_state_CALLBACK_FUNCTION(&YRI_CALL_BACK_final_state);
}


YERITH_QVGE_sample_CLIENT_TaintAnalysis::YERITH_QVGE_sample_CLIENT_TaintAnalysis(YRI_DB_RUNTIME_VERIF_Logger *logger)
    :YRI_DB_RUNTIME_VERIF_analysis_Checking_TESTING(logger)
{
    ___Fixture___CREATE_Tainted_Analysis_DB_SQL_table_ONCE___();

    set_RUNTIME_MONITOR_NAME("YERITH_QVGE_sample_CLIENT_TaintAnalysis");


    // ## PUT OUTPUT OF CALLING . ./YRI-create-executable-for-user-SDMM.sh -d projet-de-tests-yri-nissi
    // ## here.

//    YRI_CPP_MONITOR_EDGE *a_last_edge_1 = create_yri_monitor_edge ("T0", "TF");
//    a_last_edge_1->get_SOURCE_STATE()->set_START_STATE(*this, true);
//    a_last_edge_1->get_TARGET_STATE()->set_ERROR_STATE(true);
//    a_last_edge_1->get_SOURCE_STATE()->set_PRE_CONDITION_notIN("in", "yri_tainted_analysis.sanitizers_methods");
//    a_last_edge_1->get_TARGET_STATE()->set_POST_CONDITION_IN("i0", "yri_tainted_analysis.tainted_values");
//
//
//    YRI_CPP_notinset_inset_TRACE_expression *a_last_edge_1_GUARDED_CONDITION
//        = new YRI_CPP_notinset_inset_TRACE_expression(false,
//                "'SELECT.i0#sanitize'",
//                "T0");
//
//    a_last_edge_1->set_GUARDED_CONDITION(a_last_edge_1_GUARDED_CONDITION);
//
//
//    YRI_CPP_MONITOR_EVENT *a_last_edge_event_1 = a_last_edge_1->set_EDGE_EVENT("'INSERT.i0#in'");
//
//    //print_TO_dot_FILE();
//
    YRI_register_set_final_state_CALLBACK_FUNCTION(&YRI_CALL_BACK_final_state);
}


bool YERITH_QVGE_sample_CLIENT_TaintAnalysis::___Fixture___CREATE_Tainted_Analysis_DB_SQL_table_ONCE___()
{
    SET___sql_db_table_name("yri_tainted_analysis");


    ___sql_db_table_Column_sanitizers_methods = "sanitizers_methods";

    ___sql_db_table_Column_taint_methods = "taint_methods";

    ___sql_db_table_Column_tainted_values = "tainted_values";


    ___sql_db_table_Columns.append(___sql_db_table_Column_sanitizers_methods);

    ___sql_db_table_Columns.append(___sql_db_table_Column_taint_methods);

    ___sql_db_table_Columns.append(___sql_db_table_Column_tainted_values);



    return YRI_DB_RUNTIME_VERIF_analysis_Checking_TESTING::
                ___Fixture___CREATE_Tainted_Analysis_DB_SQL_table_ONCE___();
}


/**
* THIS METHOD PERFORMS EFFECTIVE TEMPORAL LINEAR
* LOGIC CHECK AFTER A STATE EVENT (or system event)
* could be achieved by the runtime monitor system !
*
* A SERIOUS VERIFICATION CLIENT MUST OVERRIDE THIS
* METHOD !
*/
bool YERITH_QVGE_sample_CLIENT_TaintAnalysis::DO_VERIFY_AND_or_CHECK_ltl_PROPERTY(
    QString sql_table_ADDED_with_file_AND_line_number,
    uint	sql_record_qty_MODIFIED,
    YRI_CPP_UTILS::SQL_CONSTANT_IDENTIFIER cur_SQL_command
    /* = YRI_CPP_UTILS::SQL_CONSTANT_IDENTIFIER::UNDEFINED_SQL_COMMAND */)
{
    QStringList sql_table_ADDED_with_file_AND_line_number_LIST =
        sql_table_ADDED_with_file_AND_line_number.split(";", Qt::KeepEmptyParts);

    QString sql_table_name = sql_table_ADDED_with_file_AND_line_number_LIST.at(0);

    QString CPP_FILE_NAME = sql_table_ADDED_with_file_AND_line_number_LIST.at(1);

    QString cpp_line_number = sql_table_ADDED_with_file_AND_line_number_LIST.at(2);

    QString cur_Sql_Event_TOKEN = YRI_CPP_UTILS::_DB_STMT_verification_ToUserViewString.value(cur_SQL_command);


    qDebug() << "\t "
             << QString("[C++_STMT (%1.%2)[%3,%4] at %5:%6]").
             arg(cur_Sql_Event_TOKEN,
                 sql_table_name,
                 QString::number(cur_SQL_command),
                 QString::number(sql_record_qty_MODIFIED), CPP_FILE_NAME,
                 cpp_line_number);



    YRI_CPP_MONITOR_EDGE *a_current_TO_state_OUTGOINg_Edge = 0;

    QString real_error_trigger_Event;

    QString first_OPERATION;

    QString an_external_INPUT_value = "ERROR_VOID";

    if (sql_table_name.contains("#"))
    {
        QList<QString> sql_table_name_OPERATIONS_value_list = sql_table_name.split("#");

        int counter = sql_table_name_OPERATIONS_value_list.size();

        an_external_INPUT_value = sql_table_name_OPERATIONS_value_list.at(0);

        if (2 == counter)
        {
            if (! YRI_DB_RUNTIME_VERIF_Utils::isEqualsCaseInsensitive("ERROR_VOID",
                                                                       an_external_INPUT_value))
            {
                 first_OPERATION = sql_table_name_OPERATIONS_value_list.at(1);

                 YRI_CPP_MONITOR_STATE *a_current_TO_state = get_current_MONITOR_STATE();

                 if (0 != a_current_TO_state)
                 {
                    a_current_TO_state_OUTGOINg_Edge = a_current_TO_state->get_AN_outgoing_edge();

                    if (0 != a_current_TO_state_OUTGOINg_Edge)
                    {
                        QDEBUG_STRING_OUTPUT_2(QString("an_external_INPUT_value modified ||| a_current_TO_state_OUTGOINg_Edge->toString() || %1 ||| ")
                                                    .arg(a_current_TO_state_OUTGOINg_Edge->toString()),
                                               an_external_INPUT_value);

                        if (YRI_DB_RUNTIME_VERIF_Utils::isEqualsCaseInsensitive(YRI_CPP_UTILS::STRING_insert,
                                                                                cur_Sql_Event_TOKEN))
                        {
                            real_error_trigger_Event =
                                    QString("%1.%2#%3")
                                        .arg(YRI_CPP_UTILS::_DB_STMT_verification_ToUserViewString.value(cur_SQL_command),
                                             an_external_INPUT_value,
                                             "in");

                            ___taint_analysis___Event___TO___Input_Value
                                .insert(real_error_trigger_Event,
                                        an_external_INPUT_value);
                        }
                    }
                 }
                 else
                 {
                    QDEBUG_STRING_OUTPUT_1("0 == a_current_TO_state");
                 }

            }
        }
    }


    switch(cur_SQL_command)
    {
    case YRI_CPP_UTILS::INSERT:

        QDEBUG_STRING_OUTPUT_2("an_external_INPUT_value",
                                an_external_INPUT_value);

        if (! an_external_INPUT_value.isEmpty() &&
            ! YRI_DB_RUNTIME_VERIF_Utils::isEqualsCaseInsensitive("ERROR_VOID",
                                                                   an_external_INPUT_value))
        {

            if (0 != a_current_TO_state_OUTGOINg_Edge)
            {
                QDEBUG_STRING_OUTPUT_2("a_current_TO_state_OUTGOINg_Edge->toString()",
                                        a_current_TO_state_OUTGOINg_Edge->toString());
            }


            bool success_insertion = false;


            if (0 != a_current_TO_state_OUTGOINg_Edge)
            {
                a_current_TO_state_OUTGOINg_Edge
                ->set_EDGE_EVENT(QString("'%1'").arg(real_error_trigger_Event));


                a_current_TO_state_OUTGOINg_Edge
                ->get_TARGET_STATE()
                ->set_POST_CONDITION_IN(an_external_INPUT_value,
                                        "yri_tainted_analysis.tainted_values");

                QDEBUG_STRING_OUTPUT_2(QString("an_external_INPUT_value modified--AFTER I0. ||| a_current_TO_state_OUTGOINg_Edge->toString() || %1 ||| ")
                                       .arg(a_current_TO_state_OUTGOINg_Edge->toString()),
                                       an_external_INPUT_value);

//                bool succeeded_TRIggering_of_Event =
//                    YRI_SQL_INSERT_i0___op___Event(QString("'%1'")
//                                                   .arg(real_error_trigger_Event),
//                                                   true);
//
//                QDEBUG_STRING_OUTPUT_2_BOOL("succeeded_TRIggering_of_Event",
//                                            succeeded_TRIggering_of_Event);
//
//                QString monitor_print = generate_in_DOT_format(true);
//
//                QDEBUG_STRING_OUTPUT_2("monitor_print",
//                                        monitor_print);
//
//                if (succeeded_TRIggering_of_Event)
//                {
//                    success_insertion =
//                    ___Fixture__Insert___INTO__DB__SQL__values___(___sql_db_table_Column_tainted_values,
//                                                                  an_external_INPUT_value);
//                }

            }


            if (! success_insertion)
            {
                QDEBUG_STRING_OUTPUT_2("COULDN'T MARK-insert tainted value:--",
                                       an_external_INPUT_value);
            }

        }

        break;

    case YRI_CPP_UTILS::SELECT:
        break;

    case YRI_CPP_UTILS::UPDATE:
        break;

    case YRI_CPP_UTILS::DELETE:
        break;

    default:

        break;
    }

    return false;
}




