/*
 * yri-db-runtime-verif-PROCESS.hpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */

#ifndef _YRI_DB_RUNTIME_VERIF_ERP_PROCESS_HPP_
#define _YRI_DB_RUNTIME_VERIF_ERP_PROCESS_HPP_


#include <QtCore/QProcess>


#include <QtCore/QStringList>

#include "src/utils/yri-db-runtime-verif-CONFIG.hpp"

#include "src/utils/yri-db-runtime-verif-utils.hpp"


class YRIDBRUNTIMEVERIF_Process : public QProcess
{

public:

    inline YRIDBRUNTIMEVERIF_Process()
    {
        setWorkingDirectory(YRI_DB_RUNTIME_VERIF_Config::temporaryFilesDir);
    }


    inline ~YRIDBRUNTIMEVERIF_Process()
    {
    }


    static void Deregister__ALL__RUNTIME__MONITORS();


    static bool STOP__Restart__GTK_gui_yri_db_runtime_verif();

    static bool START_yri_db_runtime_verif_GUI();

    static bool stopYerothERPAlertProcess();

    static bool startYerothERPAlertProcess();

    /**
     * Returns the size of the output file created
     * by execution of the program 'program' !
     */
    inline static int start_PROCESS_AND_READ_PROCESS_output_INTO_FILE(const QString     &program_executable_location_full_path,
                                                                      const QString     &program_working_directory_full_path,
                                                                      const QString     &output_file_name,
                                                                      const QStringList &program_executable_args)
    {
        return
                        YRIDBRUNTIMEVERIF_Process::start_PROCESS_AND_READ_PROCESS_output_INTO_FILE
                                (program_executable_location_full_path,
                                 QString("%1/%2")
                                    .arg(program_working_directory_full_path,
                                         output_file_name),
                                 program_executable_args);
    }


    /**
     * Returns the size of the output file created
     * by execution of the program 'program' !
     */
    static int start_PROCESS_AND_READ_PROCESS_output_INTO_FILE(const QString     &program_executable_location_full_path,
                                                               const QString     &output_file_full_path,
                                                               const QStringList &program_executable_args);


    /**
     * @return: the full file path name of the
     *          opened PDF file with prefix: prefixFileName
     *          ("prefixFileName.pdf").
     */
    static QString compileLatex(QString prefixFileName);

    static QString compileWITH_LUATEX_Latex(QString prefixFileName);

    static QString startPdfViewerProcess(QString aPDFFileName);

    static bool startDetached(QProcess      &aProcess,
                              QString       programFileAbsolutePath,
                              QStringList   programArguments);

    static bool startAndWaitForFinished(QProcess    &aProcess,
                                        QString     programFileAbsolutePath,
                                        QStringList programArguments,
                                        int         waitForFinished);

    static bool startAndWaitForFinished(QString     programFileAbsolutePath,
                                        QStringList programArguments,
                                        int         waitForFinished);


private:

    static bool _yerith_YRI_DB_RUNTIME_VERIF_ProcessFilesSet;


    static QProcess *_yri_db_runtime_verif_PROCESS;

    static QProcess *_alertDeamonProcess;
};


#endif /* _YRI_DB_RUNTIME_VERIF_ERP_PROCESS_HPP_ */
