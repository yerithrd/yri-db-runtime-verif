/*
 * yri-db-runtime-verif-MONITOR.cpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */


#include "yri-db-runtime-verif-MONITOR.hpp"

#include "src/utils/yri-db-runtime-verif-database-table-column.hpp"

#include "src/utils/yri-db-runtime-verif-database.hpp"

#include "src/utils/yri-db-runtime-verif-logger.hpp"



YRI_DB_RUNTIME_VERIF_Monitor::YRI_DB_RUNTIME_VERIF_Monitor()
:YRI_CPP_MONITOR(),
 _logger(0),
 _dbus_client(0)
{
    static bool FIRST_TIME_CALL = true;

    if (FIRST_TIME_CALL)
    {
        YRI_CPP_UTILS();

        FIRST_TIME_CALL = false;
    }

    _dbus_client = new YRI_DBUS_COMMON(this);
}


YRI_DB_RUNTIME_VERIF_Monitor::YRI_DB_RUNTIME_VERIF_Monitor(QString RUNTIME_MONITOR_NAME,
														 YRI_DB_RUNTIME_VERIF_Logger *aLogger)
:YRI_CPP_MONITOR(RUNTIME_MONITOR_NAME),
 _logger(aLogger),
 _dbus_client(0)
{
    static bool FIRST_TIME_CALL = true;

    if (FIRST_TIME_CALL)
    {
        YRI_CPP_UTILS();

        FIRST_TIME_CALL = false;
    }

    _dbus_client = new YRI_DBUS_COMMON(this);
}


YRI_DB_RUNTIME_VERIF_Monitor::YRI_DB_RUNTIME_VERIF_Monitor(YRI_DB_RUNTIME_VERIF_Logger *aLogger):YRI_CPP_MONITOR(),
    _logger(aLogger),
    _dbus_client(0)
{
    static bool
    FIRST_TIME_CALL = true;

    if (FIRST_TIME_CALL)
    {
        YRI_CPP_UTILS();

        FIRST_TIME_CALL = false;
    }

    _dbus_client = new YRI_DBUS_COMMON(this);
}


YRI_DB_RUNTIME_VERIF_Monitor::~YRI_DB_RUNTIME_VERIF_Monitor()
{
    if (0 != _dbus_client)
    {
        delete _dbus_client;
    }
}


bool YRI_DB_RUNTIME_VERIF_Monitor::
		YRI_DB_RUNTIME_VERIF_Monitor_notify_SUCCESS_VERIFICATION
			(YRI_CPP_MONITOR_EDGE *an_EDGE_leading_TO_error_FINAL_state /* = 0 */)
{
	bool ret_value = false;

    qDebug() << "//** YRI_DB_RUNTIME_VERIF_Monitor::YRI_DB_RUNTIME_VERIF_Monitor_notify_SUCCESS_VERIFICATION **//";

    if (0 != an_EDGE_leading_TO_error_FINAL_state)
    {
    	TRACE_SUT_LOG_EVENT_complement_info_ON_ACCEPTING_STATE(*an_EDGE_leading_TO_error_FINAL_state);
    }

    ret_value = RESET_RUNTIME_MONITOR();

    return ret_value;
}


//TODO: write a description for each runtime monitor
//error accepted state.
//This information might come from runtime monitor
//class itself, as written by developer.
void YRI_DB_RUNTIME_VERIF_Monitor::
        WRITE_failed_error_accepted_Runtime_Monitor___SUT()
{
    QString QUERY_TO_SET_A_RUNTIME_MONITOR_FAILURE =
        QString("INSERT into %1 (`%2`, `%3`, `%4`) values ('%5', '%6', '%7');")
         .arg(YRI_DB_RUNTIME_VERIF_Database::YRI_DB_RUNTIME_VERIF,
              YRI_DB_RUNTIME_VERIF_DatabaseTableColumn::ERROR_ACCEPTED_RUNTIME_MONITOR_NAME,
              YRI_DB_RUNTIME_VERIF_DatabaseTableColumn::ERROR_ACCEPTED_RUNTIME_MONITOR_NAME_ID,
              YRI_DB_RUNTIME_VERIF_DatabaseTableColumn::ERROR_ACCEPTED_RUNTIME_MONITOR_NAME_DESCRIPTION,
              get_RUNTIME_MONITOR_NAME(),
              GET_QSTRING_ID(),
              "");

    //QDEBUG_STRINGS_OUTPUT_2("QUERY_TO_SET_A_RUNTIME_MONITOR_FAILURE",
    //                         QUERY_TO_SET_A_RUNTIME_MONITOR_FAILURE);

    YRI_DB_RUNTIME_VERIF_Utils::execQuery(QUERY_TO_SET_A_RUNTIME_MONITOR_FAILURE);
}


void YRI_DB_RUNTIME_VERIF_Monitor::
		TRACE_SUT_LOG_EVENT_complement_info_ON_ACCEPTING_STATE
				(YRI_CPP_MONITOR_EDGE &an_EDGE_leading_TO_error_FINAL_state)
{
	if (0 != _dbus_client)
	{
        /*
         * Write this error accepted state runtime monitor name
         * into USER APPLICATION (system under test) corresponding
         * database table columns.
         */
        WRITE_failed_error_accepted_Runtime_Monitor___SUT();

		_dbus_client
			->TRACE_SUT_LOG_EVENT_complement_info_ON_ACCEPTING_STATE
				(an_EDGE_leading_TO_error_FINAL_state);
	}
}


void YRI_DB_RUNTIME_VERIF_Monitor::
		TRACE_SUT_LOG_EVENT(YRI_DB_RUNTIME_VERIF_Monitor &a_runtime_monitor,
						 	uint 						cur_command,
							QString 					&in0,
							QString 					CHANGED_RECORD_DB_QTY)
{
	if (0 != _dbus_client)
	{
		_dbus_client
			->TRACE_SUT_LOG_EVENT(a_runtime_monitor,
								  cur_command,
								  in0,
								  CHANGED_RECORD_DB_QTY);
	}
}


bool YRI_DB_RUNTIME_VERIF_Monitor::YRI_slot_refresh_INSERT_DB_MYSQL(QString in0,
                                                                  uint in1)
{
    if (0 != _dbus_client)
    {
        return _dbus_client->YRI_slot_refresh_INSERT_DB_MYSQL(in0, in1);
    }

    return false;
}


bool YRI_DB_RUNTIME_VERIF_Monitor::YRI_slot_refresh_SELECT_DB_MYSQL(QString in0,
                                                                  uint in1)
{
    if (0 != _dbus_client)
    {
        return _dbus_client->YRI_slot_refresh_SELECT_DB_MYSQL(in0, in1);
    }

    return false;
}


bool YRI_DB_RUNTIME_VERIF_Monitor::YRI_slot_refresh_UPDATE_DB_MYSQL(QString in0,
                                                                  uint in1)
{
    if (0 != _dbus_client)
    {
        return _dbus_client->YRI_slot_refresh_UPDATE_DB_MYSQL(in0, in1);
    }

    return false;
}


bool YRI_DB_RUNTIME_VERIF_Monitor::YRI_slot_refresh_DELETE_DB_MYSQL(QString in0,
                                                                  uint in1)
{
    if (0 != _dbus_client)
    {
        return _dbus_client->YRI_slot_refresh_DELETE_DB_MYSQL(in0, in1);
    }

    return false;
}


/**
 * THIS METHOD PERFORMS EFFECTIVE TEMPORAL LINEAR
 * LOGIC CHECK AFTER A STATE EVENT (or system event)
 * could be achieved by the runtime monitor system !
 *
 * A SERIOUS VERIFICATION CLIENT MUST OVERRIDE THIS
 * METHOD !
 */
bool YRI_DB_RUNTIME_VERIF_Monitor::
	DO_VERIFY_AND_or_CHECK_ltl_PROPERTY(QString sql_table_ADDED_with_file_AND_line_number,
                                        uint sql_record_qty_MODIFIED,
										YRI_CPP_UTILS::SQL_CONSTANT_IDENTIFIER cur_SQL_command
											/* = YRI_CPP_UTILS::SQL_CONSTANT_IDENTIFIER::SQL_COMMAND_UNDEFINED */)
{
    if (0 != _logger)
    {
        _logger->log("YRI_DB_RUNTIME_VERIF_Monitor::DO_VERIFY_AND_or_CHECK_ltl_PROPERTY");
    }

    QStringList sql_table_ADDED_with_file_AND_line_number_LIST =
                    sql_table_ADDED_with_file_AND_line_number.split(";",
                                                                    Qt::KeepEmptyParts);

    QString sql_table_name =
                    sql_table_ADDED_with_file_AND_line_number_LIST.at(0);
    QString CPP_FILE_NAME =
                    sql_table_ADDED_with_file_AND_line_number_LIST.at(1);
    QString cpp_line_number =
                    sql_table_ADDED_with_file_AND_line_number_LIST.at(2);


    YRI_DB_RUNTIME_VERIF_Logger::Console_Raw_STR_MSG_List.clear();

    YRI_DB_RUNTIME_VERIF_Logger::Console_Raw_STR_MSG_List
             << "[C++_STMT "
             << QString("(%1.%2)[%3,%4] at %5:%6]")
                 .arg(YRI_CPP_UTILS::_DB_STMT_verification_ToUserViewString.value(cur_SQL_command),
                      sql_table_name,
                      QString::number(cur_SQL_command),
                      QString::number(sql_record_qty_MODIFIED), CPP_FILE_NAME,
                      cpp_line_number);

    QDEBUG_CONSOLE_RAW_OUTPUT_FOR_gtk_gui(YRI_DB_RUNTIME_VERIF_Logger::Console_Raw_STR_MSG_List);


    /*
     * SKELETON THAT COULD BE A starting
     * code FOR A VERIFYING method OVERIDING
     * THIS method !
     *
     switch(cur_SQL_command)
     {
     case YRI_CPP_UTILS::INSERT:
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
     */

    return false;
}
