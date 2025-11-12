/*
 * yri-db-runtime-verif-MONITOR.hpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */

#ifndef _YRI_DB_RUNTIME_VERIF_ABSTRACT_ENTITY_HPP_
#define _YRI_DB_RUNTIME_VERIF_ABSTRACT_ENTITY_HPP_


#include "src/include/yri-db-runtime-verif-definition-oo-class-operators.hpp"

#include "src/utils/yri-db-runtime-verif-utils.hpp"

#include "src/DBUS/YRI_DBUS_COMMON.hpp"


#include "src/yri_sd_runtime_verif/utils/YRI_CPP_UTILS.hpp"


#include "src/yri_sd_runtime_verif/YRI_CPP_MONITOR.hpp"


#include <QtCore/QTimer>

#include <QtSql/QSqlRecord>

#include <QtSql/QSqlQuery>

#include <QtSql/QSqlError>

#include <QtCore/QObject>

#include <QtCore/QString>


class QTimer;

class YRI_CPP_MONITOR;

class YRI_DB_RUNTIME_VERIF_Logger;


/**
 * THIS CLASS MUST ALSO INHERITS FROM 'YRI_CPP_MONITOR'
 * SO method 'bool DO_VERIFY_AND_or_CHECK_ltl_PROPERTY()'
 * COULD PERFORM effective runtime check !
 */
class YRI_DB_RUNTIME_VERIF_Monitor : public YRI_CPP_MONITOR
{
	Q_OBJECT

public:

	YRI_DB_RUNTIME_VERIF_Monitor();


    YRI_DB_RUNTIME_VERIF_Monitor(QString 					RUNTIME_MONITOR_NAME,
    							YRI_DB_RUNTIME_VERIF_Logger 	*aLogger);


    YRI_DB_RUNTIME_VERIF_Monitor(YRI_DB_RUNTIME_VERIF_Logger *aLogger);


    virtual ~YRI_DB_RUNTIME_VERIF_Monitor();


    virtual bool YRI_DB_RUNTIME_VERIF_Monitor_notify_SUCCESS_VERIFICATION
					(YRI_CPP_MONITOR_EDGE *an_EDGE_leading_TO_error_FINAL_state = 0);


protected:

    virtual void WRITE_failed_error_accepted_Runtime_Monitor___SUT();


public:

	virtual void TRACE_SUT_LOG_EVENT_complement_info_ON_ACCEPTING_STATE
					(YRI_CPP_MONITOR_EDGE &an_EDGE_leading_TO_error_FINAL_state);


	virtual void TRACE_SUT_LOG_EVENT(YRI_DB_RUNTIME_VERIF_Monitor &a_runtime_monitor,
							 	 	 uint 						 cur_command,
									 QString 					 &in0,
									 QString 					 CHANGED_RECORD_DB_QTY);


    inline virtual void YRI_TRIGGERED_EVENT_LOGGING(const QString A_METHOD_CALLED,
                                                   const QString AN_EVENT,
                                                   bool 		 A_RETURNED_VALUE)
    {
        qDebug() << QString("%1; triggered event: ")
        				.arg(A_METHOD_CALLED)
                 << AN_EVENT
				 << " ["
				 << DB_BOOL_TO_STRING(A_RETURNED_VALUE)
				 << "]";
    }


    inline virtual YRI_DB_RUNTIME_VERIF_Logger *get_logger()
    {
        return _logger;
    }


public Q_SLOTS:

    virtual bool YRI_slot_refresh_INSERT_DB_MYSQL(QString in0, uint in1);


    virtual bool YRI_slot_refresh_SELECT_DB_MYSQL(QString in0, uint in1);


    virtual bool YRI_slot_refresh_UPDATE_DB_MYSQL(QString in0, uint in1);


    virtual bool YRI_slot_refresh_DELETE_DB_MYSQL(QString in0, uint in1);


    /**
     * THIS METHOD PERFORMS EFFECTIVE TEMPORAL LINEAR
     * LOGIC CHECK AFTER A STATE EVENT (or system event)
     * could be achieved by the runtime monitor system !
     *
     * A SERIOUS VERIFICATION CLIENT MUST OVERRIDE THIS
     * METHOD !
     */
    virtual bool DO_VERIFY_AND_or_CHECK_ltl_PROPERTY(QString 	sql_table_ADDED_with_file_AND_line_number,
                                                     uint 		sql_record_qty_MODIFIED,
                                                     YRI_CPP_UTILS::SQL_CONSTANT_IDENTIFIER
                                                     	 cur_SQL_command = YRI_CPP_UTILS::SQL_CONSTANT_IDENTIFIER::UNDEFINED_SQL_COMMAND);


protected:

    YRI_DB_RUNTIME_VERIF_Logger 	*_logger;

    YRI_DBUS_COMMON 				*_dbus_client;
};


#endif /* _YRI_DB_RUNTIME_VERIF_ABSTRACT_ENTITY_HPP_ */
