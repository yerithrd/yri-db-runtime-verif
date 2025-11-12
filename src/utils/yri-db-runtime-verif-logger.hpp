/*
 * yri-db-runtime-verif-logger.hpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */

#ifndef _SRC_YRI_DB_RUNTIME_VERIF_LOGGER_HPP_
#define _SRC_YRI_DB_RUNTIME_VERIF_LOGGER_HPP_

#include <QtCore/QString>



//##################### QMAINWINDOW RELATED IMPORTS #####################

#include "src/windows/yri-db-runtime-verif-windows.hpp"

//#######################################################################



class QDebug;
class QFile;


class YRI_DB_RUNTIME_VERIF_Logger
{
public:

    typedef enum _YERITH_LOG_LEVEL
    {
        YERITH_DEBUG = 0,
        YERITH_LOG,
        YERITH_WARN
    } YERITH_LOG_LEVEL;

    YRI_DB_RUNTIME_VERIF_Logger(QString cppClassName,
                                YERITH_LOG_LEVEL logLevel = YERITH_LOG);

    ~YRI_DB_RUNTIME_VERIF_Logger();

    void debug(const char *cppMethodName, const char *msg = "");

    void debug(const char *cppMethodName, QString msg);

    void log(const char *cppMethodName, const char *msg = "");

    void log(const char *cppMethodName, QString msg);

    YRI_DB_RUNTIME_VERIF_Logger &operator<< (const char *s);
    YRI_DB_RUNTIME_VERIF_Logger &operator<< (QString s);
    YRI_DB_RUNTIME_VERIF_Logger &operator<< (bool s);
    YRI_DB_RUNTIME_VERIF_Logger &operator<< (int s);
    YRI_DB_RUNTIME_VERIF_Logger &operator<< (char s);
    YRI_DB_RUNTIME_VERIF_Logger &operator<< (QByteArray s);

    inline void *operator   new[](size_t size)
    {
        return malloc(size);
    }

    inline void *operator   new (size_t size)
    {
        return malloc(size);
    }

    inline void operator   delete[](void *ptr)
    {
        free(ptr);
    }

    inline void operator   delete[](void *ptr, size_t)
    {
        free(ptr);
    }

    inline void operator   delete (void *ptr)
    {
        free(ptr);
    }

    inline void operator   delete (void *ptr, size_t)
    {
        free(ptr);
    }


    static inline void SET_ALL_WINDOWS_instance(YRIDBRUNTIMEVERIF_Windows *WINDOWS)
    {
    	_ALL_WINDOWS = WINDOWS;
    }


    static YRIDBRUNTIMEVERIF_Windows *_ALL_WINDOWS;


    static QStringList Console_Raw_STR_MSG_List;


private:

    YERITH_LOG_LEVEL _logLevel;

    QString _cppClassName;

    QDebug *_qDebug;
    QFile *_logFile;
};



#define QDEBUG_CONSOLE_RAW_OUTPUT_FOR_gtk_gui(STR)              \
     qDebug() << STR;                                           \
     if (0 != YRI_DB_RUNTIME_VERIF_Logger::_ALL_WINDOWS) {      \
        YRI_DB_RUNTIME_VERIF_Logger::_ALL_WINDOWS->_yrdbruntimeverif_main_Window->ADD_ITEM_Console_Raw(STR); \
     }




#endif //_SRC_YRI_DB_RUNTIME_VERIF_LOGGER_HPP_
