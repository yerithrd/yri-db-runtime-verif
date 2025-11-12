/*
 * yri-db-runtime-verif-database.cpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */

#include "yri-db-runtime-verif-database.hpp"


#include "src/utils/yri-db-runtime-verif-utils.hpp"



QString YRI_DB_RUNTIME_VERIF_Database::_db_type("");

QString YRI_DB_RUNTIME_VERIF_Database::_db_name("");

QString YRI_DB_RUNTIME_VERIF_Database::_db_ip_address("");

QString YRI_DB_RUNTIME_VERIF_Database::_db_user_name("");

QString YRI_DB_RUNTIME_VERIF_Database::_db_user_pwd("");

QString YRI_DB_RUNTIME_VERIF_Database::_db_connection_options("");



const QString YRI_DB_RUNTIME_VERIF_Database::YRI_DB_RUNTIME_VERIF("yri_db_runtime_verif");

const QString YRI_DB_RUNTIME_VERIF_Database::MYSQL("MySQL");



YRI_DB_RUNTIME_VERIF_Database::YRI_DB_RUNTIME_VERIF_Database(QString dbType)
{
    if (YRI_DB_RUNTIME_VERIF_Utils::isEqualsCaseInsensitive
            (dbType, YRI_DB_RUNTIME_VERIF_Database::MYSQL))
    {
        qDebug() <<
                 "yri-db-runtime-verif | YRI_DB_RUNTIME_VERIF_Database::YRI_DB_RUNTIME_VERIF_Database | database type: QMYSQL \n";
        _database = QSqlDatabase::addDatabase("QMYSQL");
    }

    this->set_db_type(dbType);
    this->set_db_name(YRI_DB_RUNTIME_VERIF_Config::_db_name);
    this->set_db_ip_address(YRI_DB_RUNTIME_VERIF_Config::_db_ip_address);
    this->set_db_user_name(YRI_DB_RUNTIME_VERIF_Config::_db_user_name);
    this->set_db_user_pwd(YRI_DB_RUNTIME_VERIF_Config::_db_user_pwd);
    this->set_db_connection_options(YRI_DB_RUNTIME_VERIF_Config::_db_connection_options);
}

void YRI_DB_RUNTIME_VERIF_Database::set_db_name(QString db_name)
{
    _db_name = db_name;
    _database.setDatabaseName(_db_name);
}

void YRI_DB_RUNTIME_VERIF_Database::set_db_ip_address(QString db_ip_address)
{
    _db_ip_address = db_ip_address;
    _database.setHostName(_db_ip_address);
}

void YRI_DB_RUNTIME_VERIF_Database::set_db_user_name(QString db_user_name)
{
    _db_user_name = db_user_name;
    _database.setUserName(_db_user_name);
}

void YRI_DB_RUNTIME_VERIF_Database::set_db_user_pwd(QString db_user_pwd)
{
    _db_user_pwd = db_user_pwd;
    _database.setPassword(_db_user_pwd);
}

void YRI_DB_RUNTIME_VERIF_Database::set_db_connection_options(QString db_connection_options)
{
    _db_connection_options = db_connection_options;
    _database.setConnectOptions(_db_connection_options);

}

QString YRI_DB_RUNTIME_VERIF_Database::toString() const
{
    QString ret;

    if (_database.isValid())
    {
        ret.append(QString("db_type: %1\n"
                           "db_name: %2\n"
                           "db_ip_address: %3\n"
                           "db_connection_options: %4").arg(_db_type,
                                                            _database.databaseName
                                                            (),
                                                            _database.hostName
                                                            (),
                                                            _database.connectOptions
                                                            ()));
    }
    else
    {
        ret.append(QString("db_type: %1\n"
                           "db_name: %2\n"
                           "db_ip_address: %3\n"
                           "db_connection_options: %4").arg(_db_type,
                                                            YRI_DB_RUNTIME_VERIF_Database::_db_name,
                                                            YRI_DB_RUNTIME_VERIF_Database::_db_ip_address,
                                                            YRI_DB_RUNTIME_VERIF_Database::_db_connection_options));
    }

    return ret;
}
