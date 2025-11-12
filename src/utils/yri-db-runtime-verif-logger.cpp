/*
 * yri-db-runtime-verif-logger.cpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */

#include "yri-db-runtime-verif-logger.hpp"


#include "src/utils/yri-db-runtime-verif-utils.hpp"

#include <QtCore/QDebug>
#include <QtCore/QFile>

//#define YERITH_DEBUG_LOG



QStringList YRI_DB_RUNTIME_VERIF_Logger::Console_Raw_STR_MSG_List;


YRIDBRUNTIMEVERIF_Windows *YRI_DB_RUNTIME_VERIF_Logger::_ALL_WINDOWS = 0;




YRI_DB_RUNTIME_VERIF_Logger::YRI_DB_RUNTIME_VERIF_Logger(QString            cppClassName,
                                                         YERITH_LOG_LEVEL   logLevel)
:_logLevel(logLevel),
 _cppClassName(cppClassName),
 _qDebug(0),
 _logFile(0)
{
    _logFile = new QFile(YRI_DB_RUNTIME_VERIF_Utils::getLogFileName());

    _qDebug = new QDebug(_logFile);

    if (!_logFile->open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug() << "[YerenLogger][YerenLogger] "
                 << "Could not create file " << YRI_DB_RUNTIME_VERIF_Utils::
                 getLogFileName();
    }
}

YRI_DB_RUNTIME_VERIF_Logger::~YRI_DB_RUNTIME_VERIF_Logger()
{
    delete _logFile;
    delete _qDebug;
}

void YRI_DB_RUNTIME_VERIF_Logger::debug(const char *cppMethodName, const char *msg)
{
    *_qDebug <<
             QString("DEBUG | %1 %2 | %3 | %4 |").arg(GET_CURRENT_STRING_DATE,
                                                      CURRENT_TIME, _cppClassName,
                                                      cppMethodName).toStdString().
             c_str() << msg << "\n";

#ifdef YERITH_DEBUG_LOG
    qDebug() <<
             QString("DEBUG | %1 %2 | %3 | %4 |").arg(GET_CURRENT_STRING_DATE,
                                                      CURRENT_TIME, _cppClassName,
                                                      cppMethodName).toStdString().
             c_str() << msg;
#endif
}

void YRI_DB_RUNTIME_VERIF_Logger::debug(const char *cppMethodName, QString msg)
{
    *_qDebug <<
             QString("DEBUG | %1 %2 | %3 | %4 |").arg(GET_CURRENT_STRING_DATE,
                                                      CURRENT_TIME, _cppClassName,
                                                      cppMethodName).toStdString().
             c_str() << msg << "\n";

#ifdef YERITH_DEBUG_LOG
    qDebug() <<
             QString("DEBUG | %1 %2 | %3 | %4 |").arg(GET_CURRENT_STRING_DATE,
                                                      CURRENT_TIME, _cppClassName,
                                                      cppMethodName).toStdString().
             c_str() << msg;
#endif
}

void YRI_DB_RUNTIME_VERIF_Logger::log(const char *cppMethodName, const char *msg)
{
    *_qDebug <<
             QString("LOG | %1 %2 | %3 | %4 |").arg(GET_CURRENT_STRING_DATE,
                                                    CURRENT_TIME, _cppClassName,
                                                    cppMethodName).toStdString().
             c_str() << msg << "\n";

#ifdef YERITH_DEBUG_LOG
    qDebug() <<
             QString("LOG | %1 %2 | %3 | %4 |").arg(GET_CURRENT_STRING_DATE,
                                                    CURRENT_TIME, _cppClassName,
                                                    cppMethodName).toStdString().
             c_str() << msg;
#endif
}

void YRI_DB_RUNTIME_VERIF_Logger::log(const char *cppMethodName, const QString msg)
{
    *_qDebug <<
             QString("LOG | %1 %2 | %3 | %4 |").arg(GET_CURRENT_STRING_DATE,
                                                    CURRENT_TIME, _cppClassName,
                                                    cppMethodName).toStdString().
             c_str() << msg << "\n";

#ifdef YERITH_DEBUG_LOG
    qDebug() <<
             QString("LOG | %1 %2 | %3 | %4 |").arg(GET_CURRENT_STRING_DATE,
                                                    CURRENT_TIME, _cppClassName,
                                                    cppMethodName).toStdString().
             c_str() << msg;
#endif
}

YRI_DB_RUNTIME_VERIF_Logger &YRI_DB_RUNTIME_VERIF_Logger::operator<< (const
                                                                    char *s)
{
    *_qDebug << s;
    return *this;
}

YRI_DB_RUNTIME_VERIF_Logger &YRI_DB_RUNTIME_VERIF_Logger::operator<< (QString
                                                                    s)
{
    *_qDebug << s;
    return *this;
}

YRI_DB_RUNTIME_VERIF_Logger &YRI_DB_RUNTIME_VERIF_Logger::operator<< (bool s)
{
    *_qDebug << s;
    return *this;
}

YRI_DB_RUNTIME_VERIF_Logger &YRI_DB_RUNTIME_VERIF_Logger::operator<< (int s)
{
    *_qDebug << s;
    return *this;
}

YRI_DB_RUNTIME_VERIF_Logger &YRI_DB_RUNTIME_VERIF_Logger::operator<< (char s)
{
    *_qDebug << s;
    return *this;
}

YRI_DB_RUNTIME_VERIF_Logger &YRI_DB_RUNTIME_VERIF_Logger::operator<< (QByteArray s)
{
    *_qDebug << s;
    return *this;
}
