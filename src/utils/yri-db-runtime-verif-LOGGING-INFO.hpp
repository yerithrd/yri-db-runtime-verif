/*
 * yri-db-runtime-verif-LOGGING-INFO.hpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */

#ifndef _YRI_DB_RUNTIME_VERIF_LOGGING_INFO_HPP_
#define _YRI_DB_RUNTIME_VERIF_LOGGING_INFO_HPP_


#include "src/utils/yri-db-runtime-verif-utils.hpp"


#include <cstdlib>

#include <QtCore/QStringList>
#include <QtCore/QString>


class YRIDBRUNTIMEVERIF_Logging_Info
{
public:

	inline YRIDBRUNTIMEVERIF_Logging_Info()
	{
	}

	YRIDBRUNTIMEVERIF_Logging_Info(QString LOGGING_INFO);

	virtual inline ~YRIDBRUNTIMEVERIF_Logging_Info()
	{
	}

	virtual inline QString SET_IS_ERROR_EVENT(bool a_boolean_value)
	{
        return
            a_boolean_value ? AN_ACCEPTING_STATE_is_error_state_VALUE = "True"
                            : AN_ACCEPTING_STATE_is_error_state_VALUE = "False";
	}

	virtual inline bool IS_ERROR_EVENT_LOGGING()
	{
		return (YRI_DB_RUNTIME_VERIF_Utils::isEqualsCaseInsensitive
                    ("True", AN_ACCEPTING_STATE_is_error_state_VALUE));
	}


    virtual QString toString();


    virtual inline void WRITE_TO_FILE_IO(QFile &an_output_file)
    {
        YRI_DB_RUNTIME_VERIF_Utils::
            writeStringToQFilewithUTF8Encoding_IO(an_output_file,
                                                  toString());
    }


	virtual void WRITE_TO_FILE_IO(QString a_file_output_name);



	QString A_RUNTIME_MONITOR_name;

	QString A_SUT_string_unique_ID;

	QString A_CPP_SOURCE_FILE_NAME;

	QString A_CPP_SOURCE_FILE_LINE_NUMBER;

	QString A_SQL_EVENT_LOG_guarded_condition_expression;

	QString A_SQL_EVENT_LOG_guarded_condition_expression_VALUE;

	QString A_TRANSITION_precondition;

	QString A_TRANSITION_postcondition;

	QString A_PREVIOUS_STATE;

	QString AN_ACCEPTING_STATE;

	QString AN_ACCEPTING_STATE_is_error_state_VALUE;

	QString an_SQL_event_TOKEN;

	QString changed_record_db_quantity;

    QString timestamp;

    QString RECOVERY_SQL_string__ON_ERROR__accepting_state;

    QString A_RUNTIME_MONITOR_QSTRING_ID;
};



#endif /* _YRI_DB_RUNTIME_VERIF_LOGGING_INFO_HPP_ */
