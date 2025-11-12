/*
 * yri-db-runtime-verif-PROCESS.cpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */


#include "yri-db-runtime-verif-PROCESS.hpp"


//############ USER'S RUNTIME MONITOR HEADER RELATED IMPORTS ############

#include "src/include/yri-db-runtime-verif-MONITOR.hpp"

//#######################################################################


#include "src/windows/yri-db-runtime-verif-windows.hpp"

#include "src/process/yri-db-runtime-verif-PROCESS-info.hpp"


#include <QtCore/QThread>

#include <QtWidgets/QMessageBox>



bool YRIDBRUNTIMEVERIF_Process::_yerith_YRI_DB_RUNTIME_VERIF_ProcessFilesSet(false);



QProcess *YRIDBRUNTIMEVERIF_Process::_yri_db_runtime_verif_PROCESS(new QProcess);

QProcess *YRIDBRUNTIMEVERIF_Process::_alertDeamonProcess(new QProcess);



void YRIDBRUNTIMEVERIF_Process::Deregister__ALL__RUNTIME__MONITORS()
{
    int rt_monitor_Vector_SIZE = YRI_DB_RUNTIME_VERIF_Config::user_defined_Runtime_Monitors.size();


    QString current_RT_Monitor_OBJECT_ID_for_query_RPC_Dbus;

    YRI_DB_RUNTIME_VERIF_Monitor *A_USER_DEFINED_RT_MONITOR = 0;


    for (uint k = 0; k < rt_monitor_Vector_SIZE; ++k)
    {
        A_USER_DEFINED_RT_MONITOR = YRI_DB_RUNTIME_VERIF_Config::user_defined_Runtime_Monitors.at(k);

        if (0 != A_USER_DEFINED_RT_MONITOR)
        {
            current_RT_Monitor_OBJECT_ID_for_query_RPC_Dbus =
                QString("/%1")
                 .arg(A_USER_DEFINED_RT_MONITOR->get_RUNTIME_MONITOR_NAME());

            YRI_DB_RUNTIME_VERIF_Config::qdbus_Application_Wide_connection
                .unregisterObject(current_RT_Monitor_OBJECT_ID_for_query_RPC_Dbus,
                                  QDBusConnection::UnregisterTree);

            QDEBUG_STRINGS_OUTPUT_1(QString("object %1 unregistered !")
                                        .arg(current_RT_Monitor_OBJECT_ID_for_query_RPC_Dbus));
        }
    }
}


bool YRIDBRUNTIMEVERIF_Process::STOP__Restart__GTK_gui_yri_db_runtime_verif()
{
	if (!_yerith_YRI_DB_RUNTIME_VERIF_ProcessFilesSet)
	{
		_yri_db_runtime_verif_PROCESS->setStandardErrorFile("/dev/null");

		_yri_db_runtime_verif_PROCESS->setStandardOutputFile("/dev/null");

		_yerith_YRI_DB_RUNTIME_VERIF_ProcessFilesSet = true;
	}

	QString msg;

	QStringList progArguments;

	progArguments << "/usr/bin/systemctl";

	progArguments << "force-reload";

	progArguments << "yri-db-runtime-verif";

	//We don't start this process with 'startDetached' so
	//the following call to function 'check_alert_daemon_process()'
	//works fine.

	YRIDBRUNTIMEVERIF_Process::startAndWaitForFinished(*_yri_db_runtime_verif_PROCESS,
                                                       "lxqt-sudo",
                                                       progArguments,
                                                       60000);

	return _yri_db_runtime_verif_PROCESS->waitForFinished(5000);
}


bool YRIDBRUNTIMEVERIF_Process::START_yri_db_runtime_verif_GUI()
{
    bool GUI_STARTED = false;

    QProcess *GUI_yri_db_runtime_verif_PROCESS = new QProcess;

    if (0 != GUI_yri_db_runtime_verif_PROCESS)
    {
        GUI_yri_db_runtime_verif_PROCESS->setStandardErrorFile("/dev/null", QIODevice::Append);

        GUI_yri_db_runtime_verif_PROCESS->setStandardOutputFile("/dev/null", QIODevice::Append);

        QStringList progArguments;

        GUI_STARTED =
            YRIDBRUNTIMEVERIF_Process::startDetached(*GUI_yri_db_runtime_verif_PROCESS,
                                                      YRI_DB_RUNTIME_VERIF_Config::GET_YRI_DB_RUNTIME_VERIF_EXECUTABLE_FULL_PATH(),
                                                      progArguments);
    }

    return GUI_STARTED;
}


int YRIDBRUNTIMEVERIF_Process::start_PROCESS_AND_READ_PROCESS_output_INTO_FILE(const
                                                                      QString &
                                                                      program_executable_location_full_path,
                                                                      const
                                                                      QString &
                                                                      output_file_full_path,
                                                                      const
                                                                      QStringList
                                                                      &
                                                                      program_executable_args)
{
    QProcess A_YERITH_PROCESS;

    A_YERITH_PROCESS.start(program_executable_location_full_path,
                           program_executable_args);

    if (!A_YERITH_PROCESS.waitForFinished())
    {
        return -1;
    }

    QFile tmpFile(output_file_full_path);

    if (tmpFile.open(QFile::WriteOnly))
    {
        tmpFile.write(A_YERITH_PROCESS.readAllStandardOutput().trimmed());
    }
    else
    {
        return -1;
    }

    int output_file_size = tmpFile.size();

    tmpFile.close();

    return output_file_size;
}


QString YRIDBRUNTIMEVERIF_Process::compileLatex(QString prefixFileName)
{
    QStringList progArguments;

    progArguments << "-interaction";

    progArguments << "nonstopmode";

    progArguments << QString("%1tex").arg(prefixFileName);

    YRIDBRUNTIMEVERIF_Process::startAndWaitForFinished(YRI_DB_RUNTIME_VERIF_Config::
                                              pathToPdfLatex(), progArguments,
                                              -1);

    QThread::sleep(0.3);

    YRIDBRUNTIMEVERIF_Process::startAndWaitForFinished(YRI_DB_RUNTIME_VERIF_Config::
                                              pathToPdfLatex(), progArguments,
                                              -1);

    QThread::sleep(0.3);

    progArguments.clear();

    QString pdfResultFile = QString("%1pdf").arg(prefixFileName);

    return pdfResultFile;
}


QString YRIDBRUNTIMEVERIF_Process::compileWITH_LUATEX_Latex(QString prefixFileName)
{
    QStringList progArguments;

    progArguments << "-interaction";

    progArguments << "nonstopmode";

    progArguments << QString("%1tex").arg(prefixFileName);

    YRIDBRUNTIMEVERIF_Process::startAndWaitForFinished(YRI_DB_RUNTIME_VERIF_Config::
                                              pathToLualatex(), progArguments,
                                              -1);
    progArguments.clear();

    QString pdfResultFile = QString("%1pdf").arg(prefixFileName);

    return pdfResultFile;
}


QString YRIDBRUNTIMEVERIF_Process::startPdfViewerProcess(QString aPDFFileName)
{
    QStringList progArguments(aPDFFileName);

    QProcess::startDetached(YRI_DB_RUNTIME_VERIF_Config::pathToPdfReader,
                            progArguments, YRI_DB_RUNTIME_VERIF_Config::temporaryFilesDir);

    return aPDFFileName;
}


bool YRIDBRUNTIMEVERIF_Process::startDetached(QProcess &aProcess,
                                     QString programFileAbsolutePath,
                                     QStringList programArguments)
{
    aProcess.setWorkingDirectory(YRI_DB_RUNTIME_VERIF_Config::temporaryFilesDir);

//    QDEBUG_STRING_OUTPUT_2("startDetached; programFileAbsolutePath",
//    					   programFileAbsolutePath);
//
//    qDebug() << "startDetached; programArguments"
//    		 << programArguments;

    return aProcess.startDetached(programFileAbsolutePath, programArguments);
}


bool YRIDBRUNTIMEVERIF_Process::startAndWaitForFinished(QProcess &aProcess,
                                               QString programFileAbsolutePath,
                                               QStringList programArguments,
                                               int waitForFinished)
{
    aProcess.setWorkingDirectory(YRI_DB_RUNTIME_VERIF_Config::temporaryFilesDir);

//    QDEBUG_STRING_OUTPUT_2("startAndWaitForFinished; programFileAbsolutePath",
//    					   programFileAbsolutePath);
//
//    qDebug() << "startAndWaitForFinished; programArguments"
//    		 << programArguments;

    aProcess.start(programFileAbsolutePath, programArguments);

    return aProcess.waitForFinished(waitForFinished);
}


bool YRIDBRUNTIMEVERIF_Process::startAndWaitForFinished(QString programFileAbsolutePath,
                                               QStringList programArguments,
                                               int waitForFinished)
{
    QProcess aProcess;

    aProcess.setWorkingDirectory(YRI_DB_RUNTIME_VERIF_Config::temporaryFilesDir);

    aProcess.start(programFileAbsolutePath, programArguments);

    return aProcess.waitForFinished(waitForFinished);
}
