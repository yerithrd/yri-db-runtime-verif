/*
 * yri-db-runtime-verif-setup-window.hpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */

#ifndef _YRI_DB_RUNTIME_VERIF_SETUP_WINDOW_HPP_
#define _YRI_DB_RUNTIME_VERIF_SETUP_WINDOW_HPP_

#include "../../ui_yri-db-runtime-verif-setup-window.h"


#include "src/windows/yri-db-runtime-verif-COMMONS-window.hpp"


#include <QtWidgets/QMainWindow>

#include <QtCore/QObject>


class YRIDBRUNTIMEVERIF_SetupWindow : public YRIDBRUNTIMEVERIF_CommonsWindow,
									 public Ui_YRIDBRUNTIMEVERIF_SetupWindow
{
	Q_OBJECT

public:

	YRIDBRUNTIMEVERIF_SetupWindow();

    inline virtual ~YRIDBRUNTIMEVERIF_SetupWindow()
    {
    }


    virtual void yri_show();


    inline virtual QToolBar &get_tool_bar()
    {
    	return *toolBar_SetupWindow_YRI_DB_RUNTIME_VERIF;
    }


public slots:

	virtual void set_connection_DBUS_status(QString	message_STATUS,
											bool 	error_not_connected = false);


protected slots:

    virtual void ON_choose_path_pdfReader();


    virtual void ON_actionRETURN_TO_console_trigerred();


    virtual void ON_pushButton_Reset_parameters_PRESSED();


	virtual void ON_pushButton_SAVE_parameters_PRESSED();
};

#endif /* _YRI_DB_RUNTIME_VERIF_SETUP_WINDOW_HPP_ */
