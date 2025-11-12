/*
 * yri-db-runtime-verif-PROCESS-info.cpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */

#include "yri-db-runtime-verif-PROCESS-info.hpp"

#include "src/utils/yri-db-runtime-verif-logger.hpp"

#include "src/utils/yri-db-runtime-verif-CONFIG.hpp"

#include <QtCore/QByteArray>

#include <QtCore/QDebug>

#include <QtCore/QFile>

#include <QtCore/QProcess>




bool YRIDBRUNTIMEVERIF_ProcessInfo::CHECK_WHETHER_DAEMON_PROCESS_IS_RUNNING(QString a_daemon_process_ID_STR,
																QString executable_full_path,
																YRI_DB_RUNTIME_VERIF_Logger *logger /* = 0 */)
{
	if (logger)
	{
		logger->log
		("yerith-erp-9-0 | YRIDBRUNTIMEVERIF_ProcessInfo::CHECK_WHETHER_DAEMON_PROCESS_IS_RUNNING");
	}

	QStringList progArguments;

	progArguments << "-a"
				  << a_daemon_process_ID_STR;

	QString PGREP_Program("/usr/bin/pgrep");

	QString yerithpsoutput_file(QString("%1/%2_psoutput")
									.arg(YRI_DB_RUNTIME_VERIF_Config::temporaryFilesDir,
										 QString(".%1")
										 	 .arg(a_daemon_process_ID_STR)));

//	QDEBUG_STRING_OUTPUT_2(QString("%1: temporary psoutput file: ")
//								.arg(a_daemon_process_ID_STR),
//						   yerithpsoutput_file);

	int output_file_size =
			YRIDBRUNTIMEVERIF_Process::start_PROCESS_AND_READ_PROCESS_output_INTO_FILE
								(PGREP_Program,
								 yerithpsoutput_file,
								 progArguments);

	if (output_file_size > 0)
	{
//		QDEBUG_STRING_OUTPUT_2_N(QString("%1; output_file_size: ")
//									.arg(a_daemon_process_ID_STR),
//								  output_file_size);

		return YRI_DB_RUNTIME_VERIF_Utils::GREP_YERITH_FILE_CONTENT(yerithpsoutput_file,
													 executable_full_path,
													 a_daemon_process_ID_STR);
	}

	return false;
}

