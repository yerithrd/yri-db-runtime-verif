/*
 * yri-db-runtime-verif-main-window.cpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */

#include "yri-db-runtime-verif-main-window.hpp"


//verification related.
#include "src/include/yri-db-runtime-verif-MONITOR.hpp"

#include "src/utils/yri-db-runtime-verif-CONFIG.hpp"

#include "src/windows/yri-db-runtime-verif-windows.hpp"

#include "src/utils/yri-db-runtime-verif-utils.hpp"

#include "src/process/yri-db-runtime-verif-PROCESS.hpp"


const QString YRIDBRUNTIMEVERIF_MainWindow::QMESSAGE_BOX_STYLE_SHEET =
		QString("QMessageBox {background-color: rgb(%1);}"
                "QMessageBox QLabel {color: rgb(%2);}")
			.arg("243,162,00",
				 "02,160,70");


YRIDBRUNTIMEVERIF_MainWindow::YRIDBRUNTIMEVERIF_MainWindow()
:_pushButton_lecteur_de_code_barres_Logging_JUST_CLICKED(false),
 _pushButton_lecteur_de_code_barres_JUST_CLICKED(false),
 _CURRENT_runtime_monitor_name_Filtered(false),
 _visible_Console_RAW_row_counter(0),
 _visible_ERROR_row_counter(0),
 _visible_row_counter(0),
 _Last_SelectedRow_Row_INDEX_Console_debugging(0),
 _Last_SelectedRow_Row_INDEX(0),
 _current_runtime_monitor_INSTANCE(0)
{
    setupUi(this);

    setFixedSize(width(), height());


    pushButton_STOP_LOGGING
        ->enable(this, SLOT(ON_STOP__logging__SUT_ACTIONS()));

    pushButton_START_LOGGING_from
        ->enable(this, SLOT(ON_START__logging__SUT_ACTIONS()));


    pushButton_lecteur_de_code_barres_Logging
        ->setVisible(false);

    pushButton_lecteur_de_code_barres
        ->setVisible(false);



    _qtabwidget_logging__To__LAST_SELECTED_row_INDEX
        .insert(tableWidget_Console_logging_Raw,
                0);

    _qtabwidget_logging__To__LAST_SELECTED_row_INDEX
        .insert(tableWidget_LOGGING,
                0);

    _qtabwidget_logging__To__LAST_SELECTED_row_INDEX
        .insert(tableWidget_LOGGING_ERROR_EVENT,
                0);



	toolBar_mainWindow_YRI_DB_RUNTIME_VERIF
		->setStyleSheet(QMESSAGE_BOX_STYLE_SHEET);


    actionSTOP_current_running_daemon_service_process_ON_THIS_DEVICE_computer
        ->setVisible(true);


    actionPRINT_AN_ANALYSIS_REPORT_for_currently_selected_Error_Event
        ->setVisible(false);

    actionVIEW_RUNTIME_monitor->setVisible(false);

    actionPRINT_event_log_excerpt_till_selected_SQL_event->setVisible(false);

    actionPRINT_event_log_FULL->setVisible(false);

    action_save_to_csv_format_sheet->setVisible(false);

    actionExport_as_CSV_till_selected_SQL_event->setVisible(false);

    actionSet_current_selected_SQL_event_as_filter_and_search->setVisible(false);



    lineEdit_last_RUNTIME_MONITOR_Logged_at_runtime
        ->setReadOnly(true);


    lineEdit_last_RUNTIME_MONITOR_Logged_at_runtime
        ->setText("LAST logged runtime monitor : none");



    comboBox_global_filtering->addItem("");
    comboBox_global_filtering->addItem("sql event log");
    comboBox_global_filtering->addItem("source");



    comboBox_SQL_event_filtering->addItem("");
    comboBox_SQL_event_filtering->addItem("DELETE");
    comboBox_SQL_event_filtering->addItem("UPDATE");
    comboBox_SQL_event_filtering->addItem("SELECT");
    comboBox_SQL_event_filtering->addItem("INSERT");


    set_runtime_monitor_name_ERROR_LOGGING_visible(false);


    checkBox_ALL_STATE_SAFETY_PROPERTIES->setVisible(false);

    checkBox_ALL_STATE_SAFETY_PROPERTIES_Logging->setVisible(false);


    comboBox_RUNTIME_MONITOR_NAME_Logging->setVisible(false);


    lineEdit_SQL_event_filtering
        ->setPlaceholderText(QString("Enter \"source\" or \"SQL event\" for filtering"));


    lineEdit_SQL_event_filtering->setAlignment(Qt::AlignHCenter);

    lineEdit_FILTERING_COUNT->setAlignment(Qt::AlignHCenter);


    tableWidget_LOGGING_2->setMaxSize(1);
    tableWidget_LOGGING_4->setMaxSize(1);
    tableWidget_LOGGING_PRECONDITIONS->setMaxSize(1);
    tableWidget_LOGGING_postconditions->setMaxSize(1);
    tableWidget_LOGGING_guarded_condition_expression->setMaxSize(1);
    tableWidget_LOGGING_SQL_recovery_executed_query->setMaxSize(1);


    tableWidget_LOGGING_4->setVisible(false);
    tableWidget_LOGGING_PRECONDITIONS->setVisible(false);
    tableWidget_LOGGING_postconditions->setVisible(false);
    tableWidget_LOGGING_guarded_condition_expression->setVisible(false);
    tableWidget_LOGGING_SQL_recovery_executed_query->setVisible(false);


    set_runtime_monitor_name_ERROR_LOGGING_visible(false);


    connect(checkBox_ALL_STATE_SAFETY_PROPERTIES,
            SIGNAL(stateChanged(int)),
            this,
            SLOT(handle_checkBox_ALL_STATE_SAFETY_PROPERTIES_State_CHANGED(int)));


    connect(comboBox_RUNTIME_MONITOR_NAMES,
            SIGNAL(currentTextChanged(const QString &)),
            this,
            SLOT(handle_combobox_CHANGE_RUNTIME_MONITOR_NAME(const QString &)));


    connect(tabWidget_SQL_ERROR_EVENT_LOGGING,
            SIGNAL(currentChanged(int)),
            this,
            SLOT(handle_current_tab_changed(int)));



    connect(actionSTOP_current_running_daemon_service_process_ON_THIS_DEVICE_computer,
            SIGNAL(triggered()),
            this,
            SLOT(STOP_YRI_DB_RUNTIME_VERIF_DAEMON_PROCESS()));



    connect(action_save_to_csv_format_sheet,
            SIGNAL(triggered()),
            this,
            SLOT(export_csv_file()));


    connect(actionExport_as_CSV_till_selected_SQL_event,
            SIGNAL(triggered()),
            this,
            SLOT(ON_action_export_as_CSV_till_selected_SQL_event()));


    connect(actionSet_current_selected_SQL_event_as_filter_and_search,
            SIGNAL(triggered()),
            this,
            SLOT(ON_action_set_current_selected_SQL_event_as_filter_and_search()));



    connect(pushButton_lecteur_de_code_barres_Logging,
    		SIGNAL(clicked()),
			this,
            SLOT(ON_QTABLEWIDGET_ITEM_pressed()));

    connect(pushButton_lecteur_de_code_barres,
    		SIGNAL(clicked()),
			this,
            SLOT(ON_QTABLEWIDGET_ERROR_ITEM_pressed()));



    connect(pushButton_reset_filtering,
    		SIGNAL(clicked()),
			this,
            SLOT(ON_BUTON_Reset_pressed()));

    connect(pushButton_filter,
    		SIGNAL(clicked()),
			this,
            SLOT(ON_BUTON_Filter_pressed()));


    connect(actionAbout, SIGNAL(triggered()), this, SLOT(about()));


    connect(actionSETUP_window,
    		SIGNAL(triggered()),
			this,
            SLOT(ON_Configfuration_panel_window_trigerred()));


    connect(actionVIEW_RUNTIME_monitor,
    		SIGNAL(triggered()),
			this,
            SLOT(YRI_on_progress_bar__VIEW_current_RUNTIME_MONITOR()));



    connect(actionPRINT_event_log_excerpt_till_selected_SQL_event,
    		SIGNAL(triggered()),
			this,
            SLOT(yri_PRINT_with_PROGRESS_BAR_ON__event_log_excerpt_till_selected_SQL_event()));


    connect(actionPRINT_event_log_FULL,
    		SIGNAL(triggered()),
			this,
            SLOT(yri_PRINT_with_PROGRESS_BAR_ON__event_log_excerpt()));



    // USEFUL TO UPDATE sql event information WHEN
    // actions from context menu are called from a cell.
    connect(tableWidget_LOGGING_ERROR_EVENT,
            SIGNAL(clicked(const QModelIndex &)),
            this,
            SLOT(setLast_SelectedRow_Row_ID(const QModelIndex &)));

    connect(tableWidget_LOGGING_ERROR_EVENT,
            SIGNAL(pressed(const QModelIndex &)),
            this,
            SLOT(setLast_SelectedRow_Row_ID(const QModelIndex &)));


    connect(tableWidget_Console_logging_Raw,
            SIGNAL(clicked(const QModelIndex &)),
            this,
            SLOT(setLast_SelectedRow_Row_ID(const QModelIndex &)));

    connect(tableWidget_Console_logging_Raw,
            SIGNAL(pressed(const QModelIndex &)),
            this,
            SLOT(setLast_SelectedRow_Row_ID(const QModelIndex &)));


    connect(tableWidget_LOGGING,
            SIGNAL(clicked(const QModelIndex &)),
            this,
            SLOT(setLast_SelectedRow_Row_ID(const QModelIndex &)));

    connect(tableWidget_LOGGING,
            SIGNAL(pressed(const QModelIndex &)),
            this,
            SLOT(setLast_SelectedRow_Row_ID(const QModelIndex &)));


    /*
     * USEFUL TO UPDATE sql event information WHEN
     * 'QtableWidget::selectRow' IS CALLED.
     */
    connect(tableWidget_LOGGING_ERROR_EVENT,
    		SIGNAL(itemChanged(QTableWidgetItem *)),
			this,
            SLOT(ON_QTABLEWIDGET_ERROR_ITEM_pressed(QTableWidgetItem *)));

    connect(tableWidget_LOGGING_ERROR_EVENT,
    		SIGNAL(itemClicked(QTableWidgetItem *)),
			this,
            SLOT(ON_QTABLEWIDGET_ERROR_ITEM_pressed(QTableWidgetItem *)));

    connect(tableWidget_LOGGING_ERROR_EVENT,
    		SIGNAL(itemPressed(QTableWidgetItem *)),
			this,
            SLOT(ON_QTABLEWIDGET_ERROR_ITEM_pressed(QTableWidgetItem *)));

    connect(tableWidget_LOGGING_ERROR_EVENT,
    		SIGNAL(itemSelectionChanged()),
			this,
            SLOT(ON_QTABLEWIDGET_ERROR_ITEM_pressed(QTableWidgetItem *)));



    connect(tableWidget_LOGGING,
    		SIGNAL(itemChanged(QTableWidgetItem *)),
			this,
            SLOT(ON_QTABLEWIDGET_ITEM_pressed(QTableWidgetItem *)));

    connect(tableWidget_LOGGING,
    		SIGNAL(itemClicked(QTableWidgetItem *)),
			this,
            SLOT(ON_QTABLEWIDGET_ITEM_pressed(QTableWidgetItem *)));

    connect(tableWidget_LOGGING,
    		SIGNAL(itemPressed(QTableWidgetItem *)),
			this,
            SLOT(ON_QTABLEWIDGET_ITEM_pressed(QTableWidgetItem *)));

    connect(tableWidget_LOGGING,
    		SIGNAL(itemSelectionChanged()),
			this,
            SLOT(ON_QTABLEWIDGET_ITEM_itemSelectionChanged()));



    connect(comboBox_global_filtering,
    		SIGNAL(currentTextChanged(const QString &)),
			this,
            SLOT(RESET_comboBox_SQL_event_filtering(const QString &)));

    connect(comboBox_SQL_event_filtering,
    		SIGNAL(currentTextChanged(const QString &)),
			this,
            SLOT(ON_QTABLEWIDGET_FILTER_ITEM_selected(const QString &)));



    connect(actionExit,
    		SIGNAL(triggered()),
			this,
            SLOT(ACTION_EXIT_method()));

    connect(actionUserGuide_PDF,
    		SIGNAL(triggered()),
			this,
            SLOT(__Progress_BAR__ACTION_USER_GUIDE_method()));


	setVisible(true);
}


void YRIDBRUNTIMEVERIF_MainWindow::SELECT_Logging_row(uint a_row_selected)
{
    tableWidget_LOGGING->selectRow(a_row_selected);

    _pushButton_lecteur_de_code_barres_Logging_JUST_CLICKED = true;

    pushButton_lecteur_de_code_barres_Logging->click();
}


void YRIDBRUNTIMEVERIF_MainWindow::SELECT_ERROR_LOGGING_row(uint a_row_selected)
{
    tableWidget_LOGGING_ERROR_EVENT->selectRow(a_row_selected);

    _pushButton_lecteur_de_code_barres_JUST_CLICKED = true;

    pushButton_lecteur_de_code_barres->click();
}


void YRIDBRUNTIMEVERIF_MainWindow::Update_RUNTIME_MONITOR_names()
{
    QMapIterator<QString, YRI_DB_RUNTIME_VERIF_Monitor *> j(user_defined_Runtime_Monitors_NAME__TO__RUNTIME_INSTANCES);

    QString a_runtime_monitor_name;

    uint registered_rt_monitors_really = 0;

    uint visible_user_FORMALIZED_nbr = 0;

    while (j.hasNext())
    {
        j.next();

        a_runtime_monitor_name = j.key();

        if (!a_runtime_monitor_name.isEmpty())
        {
            comboBox_RUNTIME_MONITOR_NAMES
                ->find_AND_SET_CURRENT_INDEX(a_runtime_monitor_name);


            ++registered_rt_monitors_really;


            visible_user_FORMALIZED_nbr =
                1 + comboBox_RUNTIME_MONITOR_NAMES->currentIndex();


            label_RUNTIME_verification_monitor_numbered
                ->setText(QObject::tr("# %1")
                            .arg(QString::number(visible_user_FORMALIZED_nbr)));


            label_RUNTIME_verification_monitors_NBR
                ->setText(QObject::tr("runtime monitor names (#: %1)")
                            .arg(QString::number(registered_rt_monitors_really)));
        }
    }
}


void YRIDBRUNTIMEVERIF_MainWindow::
        SET_CURRENT_RUNTIME_MONITOR_name_Logging(QString A_RUNTIME_MONITOR_name)
{
    if (!A_RUNTIME_MONITOR_name.isEmpty())
    {
        comboBox_RUNTIME_MONITOR_NAME_Logging
            ->find_AND_SET_CURRENT_INDEX(A_RUNTIME_MONITOR_name.trimmed());
    }
}


void YRIDBRUNTIMEVERIF_MainWindow::
        SET_CURRENT_RUNTIME_MONITOR_name_ERROR_Logging(QString A_RUNTIME_MONITOR_name)
{
    if (!A_RUNTIME_MONITOR_name.isEmpty())
    {
        comboBox_RUNTIME_MONITOR_NAME_Error_LOGGING
            ->find_AND_SET_CURRENT_INDEX(A_RUNTIME_MONITOR_name.trimmed());
    }
}


int YRIDBRUNTIMEVERIF_MainWindow::ADD_ITEM_Console_Raw(QString STRING_FOR_console_raw)
{
    ++_visible_Console_RAW_row_counter;

    if (_visible_Console_RAW_row_counter >= 2999)
    {
        _visible_Console_RAW_row_counter = 1;
    }

    int last_Raw_console_log_row_nr =
        tableWidget_Console_logging_Raw
            ->ADD_ITEM_Console_Raw_LOGGING(DBUS_CURRENT_TIME_WITH_MILLISECONDS,
                                           STRING_FOR_console_raw);

	return last_Raw_console_log_row_nr;
}


int YRIDBRUNTIMEVERIF_MainWindow::
				ADD_ERROR_ITEM(QString                        TIMESTAMPtem,
                               QString                        SIGNALItem,
                               QString                        SOURCEItem,
                               QString                        TARGETItem,
                               QString                        changed_OR_modified_database_qty_Item,
                               YRIDBRUNTIMEVERIF_Logging_Info  &a_logging_info)
{
    ++_visible_ERROR_row_counter;

    if (_visible_ERROR_row_counter >= 2999)
    {
        _visible_ERROR_row_counter = 1;
    }


	MAP___Assign_SutID__to__SutNAMEQString(a_logging_info.A_SUT_string_unique_ID,
                                           a_logging_info.A_RUNTIME_MONITOR_name);


    int last_ERROR_current_row_nr =
        tableWidget_LOGGING_ERROR_EVENT
            ->ADD_ITEM(TIMESTAMPtem,
                       SIGNALItem,
                       SOURCEItem,
                       TARGETItem,
                       changed_OR_modified_database_qty_Item,
                       a_logging_info.A_RUNTIME_MONITOR_QSTRING_ID,
                       true);


	QString logging_info = a_logging_info.toString();


    if (Is_SUT__to__LOG(a_logging_info.A_SUT_string_unique_ID))
    {
        //TODO: iumprove logging.
        //a_logging_info.WRITE_TO_FILE_IO(YRI_DB_RUNTIME_VERIF_Config::pathToLOGGING_EVENT_FILE);
    }


	_MAP_dbsqlERRORevent__TO__cppfileinfo.yri_insert_item(last_ERROR_current_row_nr,
                                                         logging_info);

    set_SQL_current_recovered_query_string
        (a_logging_info.RECOVERY_SQL_string__ON_ERROR__accepting_state,
         a_logging_info.timestamp);


    tableWidget_LOGGING_ERROR_SOURCE_LOCATION
        ->ADD_ITEM_2(QString("%1:%2")
                     .arg(a_logging_info.A_CPP_SOURCE_FILE_NAME,
                          a_logging_info.A_CPP_SOURCE_FILE_LINE_NUMBER));


	return last_ERROR_current_row_nr;
}


int YRIDBRUNTIMEVERIF_MainWindow::
				ADD_ITEM(QString                        TIMESTAMPtem,
						 QString                        SIGNALItem,
						 QString                        SOURCEItem,
						 QString                        TARGETItem,
						 QString                        changed_OR_modified_database_qty_Item,
						 YRIDBRUNTIMEVERIF_Logging_Info  &a_logging_info)
{
    handle_current_tab_changed(tabWidget_SQL_ERROR_EVENT_LOGGING->currentIndex());

    //We check if user has instructed to log this SUT SQL events
    bool LOGGING_INFO_VISIBLE =
        Is_SUT__to__LOG(a_logging_info.A_SUT_string_unique_ID);

    if (LOGGING_INFO_VISIBLE)
    {
        ++_visible_row_counter;
    }

    if (LOGGING_INFO_VISIBLE      &&
        _visible_row_counter >= 2999)
    {
        _visible_row_counter = 1;
    }


	MAP___Assign_SutID__to__SutNAMEQString(a_logging_info.A_SUT_string_unique_ID,
                                           a_logging_info.A_RUNTIME_MONITOR_name);


    SET__Sut__VISIBILITY_FOR_logging(a_logging_info.A_SUT_string_unique_ID);


    int last_current_row_nr =
        tableWidget_LOGGING->ADD_ITEM(TIMESTAMPtem,
                                      SIGNALItem,
                                      SOURCEItem,
                                      TARGETItem,
                                      changed_OR_modified_database_qty_Item,
                                      a_logging_info.A_RUNTIME_MONITOR_QSTRING_ID,
                                      LOGGING_INFO_VISIBLE);


	QString logging_info = a_logging_info.toString();


	_MAP_dbsqlevent__TO__cppfileinfo.yri_insert_item(last_current_row_nr,
												  	logging_info);


    tableWidget_LOGGING_2
        ->ADD_ITEM_2(QString("%1:%2")
                     .arg(a_logging_info.A_CPP_SOURCE_FILE_NAME,
                          a_logging_info.A_CPP_SOURCE_FILE_LINE_NUMBER));

	return last_current_row_nr;
}


void YRIDBRUNTIMEVERIF_MainWindow
		::SET__CURRENT__RUNTIME__MONITOR
			(YRI_DB_RUNTIME_VERIF_Monitor *a_current_runtime_monitor_INSTANCE)
{
	_current_runtime_monitor_INSTANCE = a_current_runtime_monitor_INSTANCE;

    if (0 != _current_runtime_monitor_INSTANCE)
    {
        QString current_runtime_monitor_NAME =
            _current_runtime_monitor_INSTANCE->get_RUNTIME_MONITOR_NAME();

    	actionVIEW_RUNTIME_monitor
			->setText(QString("view runtime monitor (%1)")
						.arg(current_runtime_monitor_NAME));
    }
}


void YRIDBRUNTIMEVERIF_MainWindow::
	Set_YRIDBRUNTIMEVERIF_Logging_Info(uint      row_number,
									  QString   logging_info)
{
	_MAP_dbsqlERRORevent__TO__cppfileinfo
        .yri_insert_item(row_number, logging_info);

	YRIDBRUNTIMEVERIF_Logging_Info a_logging_info(logging_info);

	if (a_logging_info.IS_ERROR_EVENT_LOGGING())
	{
	    {
            QString non_error_log_event_COMBOBOX_info =
                _MAP_dbsqlevent__TO__cppfileinfo.value(row_number);

            YRIDBRUNTIMEVERIF_Logging_Info a_logging_NON_ERROR_combobox_info
                (non_error_log_event_COMBOBOX_info);

            // WE PUT THIS EVENT ERROR INFORMATION to true so to
            //actualize it, AND WE REPLACE ITS OLD VALUE IN THE
            //MAP "_MAP_dbsqlevent__TO__cppfileinfo".
            a_logging_NON_ERROR_combobox_info.SET_IS_ERROR_EVENT(true);

            _MAP_dbsqlevent__TO__cppfileinfo
                .yri_insert_item(row_number,
                                a_logging_NON_ERROR_combobox_info.toString());


            if (SQL_EVENT_LOGGING == tabWidget_SQL_ERROR_EVENT_LOGGING->currentIndex())
            {
                comboBox_RUNTIME_MONITOR_NAME_Logging->setVisible(true);

                comboBox_RUNTIME_MONITOR_NAME_Logging
                    ->find_AND_SET_CURRENT_INDEX
                        (a_logging_NON_ERROR_combobox_info.A_RUNTIME_MONITOR_name);
            }
        }


        //Call ADD_ITEM here so to complement logging information
        //on an accepting error state.

        ADD_ERROR_ITEM(a_logging_info.timestamp,
                       a_logging_info.an_SQL_event_TOKEN,
                       a_logging_info.A_SUT_string_unique_ID,
                       "YRI-DB-RUNTIME-VERIF",
                       a_logging_info.changed_record_db_quantity,
                       a_logging_info);


        QTableWidgetItem *a_qtable_widget_item = tableWidget_LOGGING_4->item(0, 1);

		if (0 != a_qtable_widget_item)
		{
			a_qtable_widget_item->setForeground(Qt::red);
		}
	}


    tableWidget_LOGGING_4->setVisible(true);
    tableWidget_LOGGING_PRECONDITIONS->setVisible(true);
    tableWidget_LOGGING_postconditions->setVisible(true);
    tableWidget_LOGGING_guarded_condition_expression->setVisible(true);


    RUNTIME_MONITOR_name_TO_PRINT_DOT = a_logging_info.A_RUNTIME_MONITOR_name;


    // 3. Runtime monitor name is set on the main window
    // only for SQL events that lead to an accepting
    // error state.
    SET_CURRENT_RUNTIME_MONITOR_name_ERROR_Logging(a_logging_info.A_RUNTIME_MONITOR_name);


    if (!RUNTIME_MONITOR_name_TO_PRINT_DOT.isEmpty())
    {
        actionVIEW_RUNTIME_monitor
            ->setText(QString("view runtime monitor (%1)")
                       .arg(RUNTIME_MONITOR_name_TO_PRINT_DOT));

        actionVIEW_RUNTIME_monitor->setVisible(true);
    }
    else
    {
        actionVIEW_RUNTIME_monitor
            ->setText(QString("NO runtime monitor to visualize in PDF form"));

        actionVIEW_RUNTIME_monitor->setVisible(false);
    }


    set_runtime_monitor_name_ERROR_LOGGING_visible(true);


	tableWidget_LOGGING_4
		->ADD_ITEM_3(QString("%1:%2:%3")
					.arg(a_logging_info.A_PREVIOUS_STATE,
						 a_logging_info.AN_ACCEPTING_STATE,
						 a_logging_info.AN_ACCEPTING_STATE_is_error_state_VALUE));


    tableWidget_LOGGING_PRECONDITIONS
        ->ADD_ITEM_1(a_logging_info.A_TRANSITION_precondition);

    tableWidget_LOGGING_postconditions
        ->ADD_ITEM_1(a_logging_info.A_TRANSITION_postcondition);


	tableWidget_LOGGING_guarded_condition_expression
		->ADD_ITEM_2(QString("%1:%2")
						.arg(a_logging_info.A_SQL_EVENT_LOG_guarded_condition_expression,
							 a_logging_info.A_SQL_EVENT_LOG_guarded_condition_expression_VALUE));



    //############################ GRAPHICAL USER INTERFACE polishments CODE ###########################
    Set__TOOLTIP__for__CONDITIONS(a_logging_info);
    //##################################################################################################



	SET__Sut__VISIBILITY_FOR_logging(a_logging_info.A_SUT_string_unique_ID);


    //tableWidget_LOGGING_2 ONLY HAS A SINGLE ROW !
    YRIDBRUNTIMEVERIF_MainWindow::
        SET__foregroundcolor__ON__accepting_state(tableWidget_LOGGING_2->currentRow(),
                                                  tableWidget_LOGGING_2);


	YRIDBRUNTIMEVERIF_MainWindow::
		SET__foregroundcolor__ON__accepting_state(row_number,
												  tableWidget_LOGGING);
}


YRIDBRUNTIMEVERIF_Logging_Info *YRIDBRUNTIMEVERIF_MainWindow::
	Get_YRIDBRUNTIMEVERIF_Logging_Info(uint row_number)
{
	YRIDBRUNTIMEVERIF_Logging_Info *a_logging_info_SAVED = 0;

	if (_MAP_dbsqlevent__TO__cppfileinfo.contains(row_number))
	{
		QString a_QSTRING_saved_logging_info = _MAP_dbsqlevent__TO__cppfileinfo.value(row_number);

		a_logging_info_SAVED = new YRIDBRUNTIMEVERIF_Logging_Info(a_QSTRING_saved_logging_info);
	}

	return a_logging_info_SAVED;
}


void YRIDBRUNTIMEVERIF_MainWindow::set_connection_DBUS_status(QString message_STATUS,
															  bool 	 error_not_connected /* = false*/)
{
	if (!error_not_connected)
	{
		label_display_yri_db_runtime_verifier_connection_STATUS
			->setStyleSheet(QString("color: rgb(%1);")
								.arg("243,162,0"));
	}
	else
	{
		label_display_yri_db_runtime_verifier_connection_STATUS
			->setStyleSheet(QString("color: rgb(%1);")
								.arg("178,34,34"));
	}

	label_display_yri_db_runtime_verifier_connection_STATUS
		->setText(message_STATUS);
}


void YRIDBRUNTIMEVERIF_MainWindow::
		ON_QTABLEWIDGET_ITEM_pressed(QTableWidgetItem *aQTable_widget_item)
{
	if (0 != aQTable_widget_item                                            &&
        SQL_EVENT_LOGGING == tabWidget_SQL_ERROR_EVENT_LOGGING->currentIndex())
	{
        if (_pushButton_lecteur_de_code_barres_Logging_JUST_CLICKED)
        {
            _pushButton_lecteur_de_code_barres_Logging_JUST_CLICKED = false;
        }

		QString LOGGING_INFO =
            _MAP_dbsqlevent__TO__cppfileinfo
                .value(GET_QTABLEWIDGET_CURRENT_ROW_TO_Select(SQL_EVENT_LOGGING));

		YRIDBRUNTIMEVERIF_Logging_Info a_logging_info(LOGGING_INFO);


        SET__Sut__VISIBILITY_FOR_logging(a_logging_info.A_SUT_string_unique_ID);


        tableWidget_LOGGING_2
            ->ADD_ITEM_2(QString("%1:%2")
                         .arg(a_logging_info.A_CPP_SOURCE_FILE_NAME,
                              a_logging_info.A_CPP_SOURCE_FILE_LINE_NUMBER));


        if (a_logging_info.IS_ERROR_EVENT_LOGGING())
        {
            RUNTIME_MONITOR_name_TO_PRINT_DOT =
                a_logging_info.A_RUNTIME_MONITOR_name;

            label_RUNTIME_MONITOR_VERIFIER_TESTER_Logging
                ->setVisible(true);


            CHANGE_visibility__Of__checkBox_ALL_STATE_SAFETY_PROPERTIES_Logging();


            actionVIEW_RUNTIME_monitor
                ->setText(QString("view runtime monitor (%1)")
                           .arg(a_logging_info.A_RUNTIME_MONITOR_name));

            actionVIEW_RUNTIME_monitor->setVisible(true);

            comboBox_RUNTIME_MONITOR_NAME_Logging->setVisible(true);
        }
        else
        {
            Disable_comboBox_RUNTIME_MONITOR_NAME_Logging();
        }


        SET_CURRENT_RUNTIME_MONITOR_name_Logging(a_logging_info.A_RUNTIME_MONITOR_name);
	}
	else
	{
        Disable_comboBox_RUNTIME_MONITOR_NAME_Logging();

        tableWidget_LOGGING_2->setVisible(false);

		tableWidget_LOGGING_2->ADD_ITEM_2(QString("no source file info:-1"));
	}
}


void YRIDBRUNTIMEVERIF_MainWindow::
		ON_QTABLEWIDGET_ERROR_ITEM_pressed(QTableWidgetItem *aQTable_widget_item /* = 0 */)
{
    if (0 != aQTable_widget_item)
    {
        QString LOGGING_INFO;

        if (_pushButton_lecteur_de_code_barres_JUST_CLICKED)
        {
            _pushButton_lecteur_de_code_barres_JUST_CLICKED = false;

            int current_row_BE_PRESSED_with_a_hidden_button =
                GET_QTABLEWIDGET_CURRENT_ROW_TO_Select(SQL_ERROR_EVENT_REPORTING_LOGGING);

            LOGGING_INFO =
                _MAP_dbsqlERRORevent__TO__cppfileinfo
                    .value(current_row_BE_PRESSED_with_a_hidden_button);

            YRIDBRUNTIMEVERIF_Logging_Info a_logging_info(LOGGING_INFO);

            set_SQL_current_recovered_query_string
                (a_logging_info.RECOVERY_SQL_string__ON_ERROR__accepting_state,
                 a_logging_info.timestamp);
        }
        else
        {
            set_SQL_current_recovered_query_string("", "");
        }


        if (SQL_ERROR_EVENT_REPORTING_LOGGING == tabWidget_SQL_ERROR_EVENT_LOGGING->currentIndex())
        {
            LOGGING_INFO = _MAP_dbsqlERRORevent__TO__cppfileinfo
                                .value(GET_QTABLEWIDGET_CURRENT_ROW_TO_Select(SQL_ERROR_EVENT_REPORTING_LOGGING));

            YRIDBRUNTIMEVERIF_Logging_Info a_logging_info(LOGGING_INFO);

            if (is_CURRENT_runtime_monitor_name_Filtered())
            {
                if (!YRI_DB_RUNTIME_VERIF_Utils::isEqualsCaseSensitive(a_logging_info.A_RUNTIME_MONITOR_name,
                                                                      GET_CURRENT_RUNTIME_MONITOR_name_Error_LOGGING()))
                {
                    return ;
                }
            }



            QString LOGGING_ERROR_SOURCE_LOCATION_string =
                        QString("%1:%2")
                             .arg(a_logging_info.A_CPP_SOURCE_FILE_NAME,
                                  a_logging_info.A_CPP_SOURCE_FILE_LINE_NUMBER);


            tableWidget_LOGGING_ERROR_SOURCE_LOCATION
                ->ADD_ITEM_2(LOGGING_ERROR_SOURCE_LOCATION_string);


            tableWidget_LOGGING_ERROR_SOURCE_LOCATION
                ->setToolTip(LOGGING_ERROR_SOURCE_LOCATION_string);



            set_SQL_current_recovered_query_string
                (a_logging_info.RECOVERY_SQL_string__ON_ERROR__accepting_state,
                 a_logging_info.timestamp);


            tableWidget_LOGGING_4->setVisible(true);
            tableWidget_LOGGING_PRECONDITIONS->setVisible(true);
            tableWidget_LOGGING_postconditions->setVisible(true);
            tableWidget_LOGGING_guarded_condition_expression->setVisible(true);


            set_runtime_monitor_name_ERROR_LOGGING_visible(true);


            YRIDBRUNTIMEVERIF_MainWindow::
                SET__foregroundcolor__ON__accepting_state
                    (aQTable_widget_item->row(),
                     tableWidget_LOGGING_ERROR_EVENT,
                     Qt::white);


            //tableWidget_LOGGING_ERROR_SOURCE_LOCATION ONLY HAS A SINGLE ROW !
            YRIDBRUNTIMEVERIF_MainWindow::
                SET__foregroundcolor__ON__accepting_state
                    (tableWidget_LOGGING_ERROR_SOURCE_LOCATION->currentRow(),
                     tableWidget_LOGGING_ERROR_SOURCE_LOCATION);


            RUNTIME_MONITOR_name_TO_PRINT_DOT = a_logging_info.A_RUNTIME_MONITOR_name;


            // 5. Runtime monitor name is set on the main window
            // only for SQL events that lead to an accepting
            // error state.
            SET_CURRENT_RUNTIME_MONITOR_name_ERROR_Logging(RUNTIME_MONITOR_name_TO_PRINT_DOT);


            if (!RUNTIME_MONITOR_name_TO_PRINT_DOT.isEmpty())
            {
                actionVIEW_RUNTIME_monitor
                    ->setText(QString("view runtime monitor (%1)")
                              .arg(RUNTIME_MONITOR_name_TO_PRINT_DOT));

                actionVIEW_RUNTIME_monitor->setVisible(true);
            }
            else
            {
                actionVIEW_RUNTIME_monitor
                    ->setText(QString("NO runtime monitor to visualize in PDF form"));

                actionVIEW_RUNTIME_monitor->setVisible(false);
            }


            tableWidget_LOGGING_4
                ->ADD_ITEM_3(QString("%1:%2:%3")
                             .arg(a_logging_info.A_PREVIOUS_STATE,
                                  a_logging_info.AN_ACCEPTING_STATE,
                                  a_logging_info.AN_ACCEPTING_STATE_is_error_state_VALUE));


            tableWidget_LOGGING_PRECONDITIONS
                ->ADD_ITEM_1(a_logging_info.A_TRANSITION_precondition);


            tableWidget_LOGGING_postconditions
                ->ADD_ITEM_1(a_logging_info.A_TRANSITION_postcondition);


            tableWidget_LOGGING_guarded_condition_expression
                ->ADD_ITEM_2(QString("%1:%2")
                             .arg(a_logging_info.A_SQL_EVENT_LOG_guarded_condition_expression,
                                  a_logging_info.A_SQL_EVENT_LOG_guarded_condition_expression_VALUE));


            //############################ GRAPHICAL USER INTERFACE polishments CODE ###########################
            Set__TOOLTIP__for__CONDITIONS(a_logging_info);
            //##################################################################################################

        }
        else
        {
            tableWidget_LOGGING_ERROR_SOURCE_LOCATION
                ->ADD_ITEM_2(QString("no source file info:-1"));
        }
    }

}


void YRIDBRUNTIMEVERIF_MainWindow::Disable_comboBox_RUNTIME_MONITOR_NAME_Logging()
{
    RUNTIME_MONITOR_name_TO_PRINT_DOT.clear();

    label_RUNTIME_MONITOR_VERIFIER_TESTER_Logging
        ->setVisible(false);

    checkBox_ALL_STATE_SAFETY_PROPERTIES_Logging
        ->setVisible(false);

    actionVIEW_RUNTIME_monitor
        ->setText(QString("NO runtime monitor to visualize in PDF form"));

    actionVIEW_RUNTIME_monitor->setVisible(false);

    comboBox_RUNTIME_MONITOR_NAME_Logging->setVisible(false);
}


bool YRIDBRUNTIMEVERIF_MainWindow::export_csv_file()
{
    YRIDBRUNTIMEVERIF_TableWidget *current_QTable_Widget_Item =
                                    Get_CURRENT_QTable_WIDGET();

    if (0 == current_QTable_Widget_Item)
    {
        return false;
    }


    return
        YRI_DB_RUNTIME_VERIF_Utils::SAVE_AS_csv_file(*this,
                                                    *current_QTable_Widget_Item,
                                                    "sql-event-log-listing-csv-format",
                                                    "SQL event log csv export");
}


bool YRIDBRUNTIMEVERIF_MainWindow::
        set_SQL_current_recovered_query_string(QString SQL_QUERY_STRING,
                                               QString TIMESTAMP /* = "" */)
{
    bool result = !SQL_QUERY_STRING.isEmpty();


    tableWidget_LOGGING_SQL_recovery_executed_query
        ->setToolTip(QString("``%1``")
                        .arg(SQL_QUERY_STRING));


    tableWidget_LOGGING_SQL_recovery_executed_query
        ->setVisible(result);

    tableWidget_LOGGING_SQL_recovery_executed_query
		->ADD_ITEM_2(SQL_QUERY_STRING,
                     TIMESTAMP);

    return result;
}


void YRIDBRUNTIMEVERIF_MainWindow::
        set_A_Runtime_Monitor_Name_FOR_VIEWING_As_Dot_Graph(QString RUNTIME_MONITOR_name_TO_PRINT_DOT,
                                                            bool Clear__ON__Empty_NAME /* = false */)
{
    if (! RUNTIME_MONITOR_name_TO_PRINT_DOT.isEmpty())
    {
        actionVIEW_RUNTIME_monitor
            ->setText(QString("view runtime monitor (%1)")
                        .arg(RUNTIME_MONITOR_name_TO_PRINT_DOT));

        actionVIEW_RUNTIME_monitor->setVisible(true);
    }
    else if (Clear__ON__Empty_NAME)
    {
        actionVIEW_RUNTIME_monitor
            ->setText(QString("NO runtime monitor to visualize in PDF form"));

        actionVIEW_RUNTIME_monitor->setVisible(false);
    }
}


void YRIDBRUNTIMEVERIF_MainWindow::set_UPPER_widgets_elements_visibility()
{
    switch(tabWidget_SQL_ERROR_EVENT_LOGGING->currentIndex())
    {
        case CONSOLE_LOGGING_RAW:
        case RUNTIME_VERIFICATION_MONITORS:

            comboBox_SQL_event_filtering->setVisible(false);
            comboBox_global_filtering->setVisible(false);

            lineEdit_SQL_event_filtering->setVisible(false);
            lineEdit_FILTERING_COUNT->setVisible(false);

            pushButton_reset_filtering->setVisible(false);
            pushButton_filter->setVisible(false);

            break;


        case SQL_ERROR_EVENT_REPORTING_LOGGING:
        case SQL_EVENT_LOGGING:

        default:

            comboBox_SQL_event_filtering->setVisible(true);
            comboBox_global_filtering->setVisible(true);

            lineEdit_SQL_event_filtering->setVisible(true);
            lineEdit_FILTERING_COUNT->setVisible(true);

            pushButton_reset_filtering->setVisible(true);
            pushButton_filter->setVisible(true);

            break;
    }
}


void YRIDBRUNTIMEVERIF_MainWindow::set_CURRENT_TABWIDGET_ACTION_visible(bool a_value)
{
    QString LOGGING_INFO;


    actionPRINT_AN_ANALYSIS_REPORT_for_currently_selected_Error_Event
        ->setVisible(false);


    if (SQL_ERROR_EVENT_REPORTING_LOGGING == tabWidget_SQL_ERROR_EVENT_LOGGING->currentIndex())
    {
        if (_visible_ERROR_row_counter > 0)
        {
            actionPRINT_AN_ANALYSIS_REPORT_for_currently_selected_Error_Event
                ->setVisible(true);
        }
        else
        {
            actionPRINT_AN_ANALYSIS_REPORT_for_currently_selected_Error_Event
                ->setVisible(false);
        }


        LOGGING_INFO =
            _MAP_dbsqlERRORevent__TO__cppfileinfo
                .value(GET_QTABLEWIDGET_CURRENT_ROW_TO_Select(SQL_ERROR_EVENT_REPORTING_LOGGING));


        checkBox_ALL_STATE_SAFETY_PROPERTIES->setVisible(a_value);


        tableWidget_LOGGING_ERROR_EVENT->resize_columns_AND_rows_to_contents();

        tableWidget_LOGGING_ERROR_SOURCE_LOCATION->resize_columns_AND_rows_to_contents();

        tableWidget_LOGGING_PRECONDITIONS->resize_columns_AND_rows_to_contents();

        tableWidget_LOGGING_postconditions->resize_columns_AND_rows_to_contents();

        tableWidget_LOGGING_guarded_condition_expression->resize_columns_AND_rows_to_contents();

        tableWidget_LOGGING_SQL_recovery_executed_query->resize_columns_AND_rows_to_contents();

        tableWidget_LOGGING_4->resize_columns_AND_rows_to_contents();
    }
    else if (SQL_EVENT_LOGGING == tabWidget_SQL_ERROR_EVENT_LOGGING->currentIndex())
    {
        if (_visible_row_counter > 0)
        {
            actionPRINT_AN_ANALYSIS_REPORT_for_currently_selected_Error_Event
                ->setVisible(true);
        }
        else
        {
            actionPRINT_AN_ANALYSIS_REPORT_for_currently_selected_Error_Event
                ->setVisible(false);
        }


        LOGGING_INFO =
            _MAP_dbsqlevent__TO__cppfileinfo
                .value(GET_QTABLEWIDGET_CURRENT_ROW_TO_Select(SQL_EVENT_LOGGING));

        tableWidget_LOGGING->resize_columns_AND_rows_to_contents();

        tableWidget_LOGGING_2->resize_columns_AND_rows_to_contents();
    }
    else if (CONSOLE_LOGGING_RAW == tabWidget_SQL_ERROR_EVENT_LOGGING->currentIndex())
    {
        tableWidget_Console_logging_Raw->resize_columns_AND_rows_to_contents();
    }


    YRIDBRUNTIMEVERIF_Logging_Info a_logging_info(LOGGING_INFO);


    if (SQL_EVENT_LOGGING == tabWidget_SQL_ERROR_EVENT_LOGGING->currentIndex())
    {
        CHANGE_visibility__Of__checkBox_ALL_STATE_SAFETY_PROPERTIES_Logging();

        if (a_logging_info.IS_ERROR_EVENT_LOGGING())
        {
            label_RUNTIME_MONITOR_VERIFIER_TESTER_Logging
                ->setVisible(true);
        }
        else
        {
            label_RUNTIME_MONITOR_VERIFIER_TESTER_Logging
                ->setVisible(false);

            checkBox_ALL_STATE_SAFETY_PROPERTIES_Logging
                ->setVisible(false);
        }
    }


    if (a_logging_info.IS_ERROR_EVENT_LOGGING())
    {
        RUNTIME_MONITOR_name_TO_PRINT_DOT =
            a_logging_info.A_RUNTIME_MONITOR_name;

        set_A_Runtime_Monitor_Name_FOR_VIEWING_As_Dot_Graph(RUNTIME_MONITOR_name_TO_PRINT_DOT);
    }
    else
    {
        RUNTIME_MONITOR_name_TO_PRINT_DOT.clear();

        set_A_Runtime_Monitor_Name_FOR_VIEWING_As_Dot_Graph(RUNTIME_MONITOR_name_TO_PRINT_DOT,
                                                            true);
    }


    actionPRINT_event_log_excerpt_till_selected_SQL_event->setVisible(a_value);

    actionPRINT_event_log_FULL->setVisible(a_value);

    action_save_to_csv_format_sheet->setVisible(a_value);

    actionExport_as_CSV_till_selected_SQL_event->setVisible(a_value);


    uint visible_user_FORMALIZED_nbr = 0;


    if (CONSOLE_LOGGING_RAW == tabWidget_SQL_ERROR_EVENT_LOGGING->currentIndex())
    {
        RUNTIME_MONITOR_name_TO_PRINT_DOT.clear();

        set_A_Runtime_Monitor_Name_FOR_VIEWING_As_Dot_Graph();


        actionPRINT_event_log_excerpt_till_selected_SQL_event->setVisible(true);

        actionPRINT_event_log_FULL->setVisible(true);

        action_save_to_csv_format_sheet->setVisible(true);

        actionExport_as_CSV_till_selected_SQL_event->setVisible(true);


        a_value = false;
    }
    else if (RUNTIME_VERIFICATION_MONITORS == tabWidget_SQL_ERROR_EVENT_LOGGING->currentIndex())
    {
        RUNTIME_MONITOR_name_TO_PRINT_DOT =
            comboBox_RUNTIME_MONITOR_NAMES->currentText();


        set_A_Runtime_Monitor_Name_FOR_VIEWING_As_Dot_Graph(RUNTIME_MONITOR_name_TO_PRINT_DOT);


        visible_user_FORMALIZED_nbr =
            1 + comboBox_RUNTIME_MONITOR_NAMES->currentIndex();


        label_RUNTIME_verification_monitor_numbered
            ->setText(QObject::tr("# %1)")
                        .arg(QString::number(visible_user_FORMALIZED_nbr)));


        actionVIEW_RUNTIME_monitor->setVisible(true);

        a_value = false;
    }


    actionSet_current_selected_SQL_event_as_filter_and_search->setVisible(a_value);
}


void YRIDBRUNTIMEVERIF_MainWindow::filter_All_RUNTIME_monitor__ERROR__SQL__EVENTS()
{
    ON_BUTON_Reset_pressed();


    uint Filtered_Cell_Count = 0;


    QString A_Current_RUNTIME_monitor_Name = GET_CURRENT_RUNTIME_MONITOR_name_Error_LOGGING();


    QString a_CURRENT_LOGGING_INFO;


    uint TIMESTAMP_column_number = 0;


    QTableWidgetItem *a_qwidget_item = 0;


    for (int row_number = 0;
         row_number < tableWidget_LOGGING_ERROR_EVENT->rowCount();
         ++row_number)
    {
        a_qwidget_item =
            tableWidget_LOGGING_ERROR_EVENT->item(row_number,
                                                  TIMESTAMP_column_number);

        if (0 != a_qwidget_item)
        {
            a_CURRENT_LOGGING_INFO = _MAP_dbsqlERRORevent__TO__cppfileinfo
                                                .value(a_qwidget_item->row());

            YRIDBRUNTIMEVERIF_Logging_Info a_CURRENT_logging_info(a_CURRENT_LOGGING_INFO);

            if (YRI_DB_RUNTIME_VERIF_Utils::isEqualsCaseSensitive(a_CURRENT_logging_info.A_RUNTIME_MONITOR_name,
                                                                 A_Current_RUNTIME_monitor_Name))
            {
                ++Filtered_Cell_Count;

                a_qwidget_item->setBackground(Qt::darkMagenta);
            }
        }
    }

    if (Filtered_Cell_Count > 0)
    {
        set_CURRENT_runtime_monitor_name_Filtered(true);

        tableWidget_LOGGING_ERROR_EVENT->Set_CURRENTLY_filtered(true);
    }
}


void YRIDBRUNTIMEVERIF_MainWindow::UN__filter_All_RUNTIME_monitor__ERROR__SQL__EVENTS()
{
    QString A_Current_RUNTIME_monitor_Name = GET_CURRENT_RUNTIME_MONITOR_name_Error_LOGGING();


    QString a_CURRENT_LOGGING_INFO;


    uint TIMESTAMP_column_number = 0;


    QTableWidgetItem *a_qwidget_item = 0;


    for (int row_number = 0;
         row_number < tableWidget_LOGGING_ERROR_EVENT->rowCount();
         ++row_number)
    {
        a_qwidget_item =
            tableWidget_LOGGING_ERROR_EVENT->item(row_number,
                                                  TIMESTAMP_column_number);

        if (0 != a_qwidget_item)
        {
            a_CURRENT_LOGGING_INFO = _MAP_dbsqlERRORevent__TO__cppfileinfo
                                                .value(a_qwidget_item->row());

            YRIDBRUNTIMEVERIF_Logging_Info a_CURRENT_logging_info(a_CURRENT_LOGGING_INFO);

            if (YRI_DB_RUNTIME_VERIF_Utils::isEqualsCaseSensitive(a_CURRENT_logging_info.A_RUNTIME_MONITOR_name,
                                                                 A_Current_RUNTIME_monitor_Name))
            {
                a_qwidget_item->setBackground(Qt::black);
            }
        }
    }


    set_CURRENT_runtime_monitor_name_Filtered(false);
}


void YRIDBRUNTIMEVERIF_MainWindow::
        handle_checkBox_ALL_STATE_SAFETY_PROPERTIES_State_CHANGED(int a_state)
{
    if (Qt::Checked == a_state)
    {
        filter_All_RUNTIME_monitor__ERROR__SQL__EVENTS();
    }
    else
    {
        UN__filter_All_RUNTIME_monitor__ERROR__SQL__EVENTS();
    }
}


int YRIDBRUNTIMEVERIF_MainWindow::
        GET_QTABLEWIDGET_CURRENT_ROW_TO_Select(int current_index)
{
    int current_row_TO_SELECT = 0;

    const QModelIndex *a_Last_SelectedRow_Row_INDEX = 0;

    switch (current_index)
    {
    case SQL_ERROR_EVENT_REPORTING_LOGGING:

        a_Last_SelectedRow_Row_INDEX =
            _qtabwidget_logging__To__LAST_SELECTED_row_INDEX
                .value(tableWidget_LOGGING_ERROR_EVENT);

        if (0 != a_Last_SelectedRow_Row_INDEX)
        {
            current_row_TO_SELECT = a_Last_SelectedRow_Row_INDEX->row();
        }

        break;


    case SQL_EVENT_LOGGING:

        a_Last_SelectedRow_Row_INDEX =
            _qtabwidget_logging__To__LAST_SELECTED_row_INDEX
                .value(tableWidget_LOGGING);

        if (0 != a_Last_SelectedRow_Row_INDEX)
        {
            current_row_TO_SELECT = a_Last_SelectedRow_Row_INDEX->row();
        }
        break;


    case CONSOLE_LOGGING_RAW:

        if (0 != _Last_SelectedRow_Row_INDEX_Console_debugging)
        {
            current_row_TO_SELECT = _Last_SelectedRow_Row_INDEX_Console_debugging->row();
        }
        break;


    default:
        break;
    }

    return current_row_TO_SELECT;
}


void YRIDBRUNTIMEVERIF_MainWindow::handle_current_tab_changed(int current_index)
{
    bool debugging_console_log = false;


    int current_row_TO_SELECT =
        GET_QTABLEWIDGET_CURRENT_ROW_TO_Select(current_index);


    SWICTH_EVENT__LOG__to___console__log__EVENT_action(debugging_console_log);


//    QWidget *cur_widget_to_QPALETTE_style = 0;



    switch (current_index)
    {
    case SQL_ERROR_EVENT_REPORTING_LOGGING:

//        cur_widget_to_QPALETTE_style =
//            tabWidget_SQL_ERROR_EVENT_LOGGING->currentWidget();
//
//
//        if (0 != cur_widget_to_QPALETTE_style)
//        {
//            QPalette a_current_widget_palette = QPalette(cur_widget_to_QPALETTE_style->palette());
//
//
//            QColor a_window_text_Color = QColor(2, 160, 70);
//
//            QBrush a_brush = QBrush(a_window_text_Color);
//
//
//            a_current_widget_palette
//                .setColor(QPalette::Active,
//                          QPalette::WindowText,
//                          a_window_text_Color);
//
//            a_current_widget_palette
//                .setBrush(QPalette::Active,
//                          QPalette::WindowText,
//                          a_brush);
//
//            cur_widget_to_QPALETTE_style->setPalette(a_current_widget_palette);
//
//            QDEBUG_STRINGS_OUTPUT_1("*** QPALETTE ***");
//
//            cur_widget_to_QPALETTE_style->update();
//        }

        //also clears qtablewidget filtering
        ON_BUTON_Reset_pressed();

        if (_visible_ERROR_row_counter > 0)
        {
            SELECT_ERROR_LOGGING_row(current_row_TO_SELECT);

            set_CURRENT_TABWIDGET_ACTION_visible(true);
        }
        else
        {
            set_CURRENT_TABWIDGET_ACTION_visible(false);
        }
        break;


    case SQL_EVENT_LOGGING:

        //also clears qtablewidget filtering
        ON_BUTON_Reset_pressed();

        if (_visible_row_counter > 0)
        {
            SELECT_Logging_row(current_row_TO_SELECT);

            set_CURRENT_TABWIDGET_ACTION_visible(true);
        }
        else
        {
            set_CURRENT_TABWIDGET_ACTION_visible(false);
        }
        break;


    case CONSOLE_LOGGING_RAW:

        debugging_console_log = true;

        SWICTH_EVENT__LOG__to___console__log__EVENT_action(debugging_console_log);

        set_CURRENT_TABWIDGET_ACTION_visible(false);

        break;


    case RUNTIME_VERIFICATION_MONITORS:
        set_CURRENT_TABWIDGET_ACTION_visible(false);
        break;


    default:
        break;
    }


    set_UPPER_widgets_elements_visibility();
}


void YRIDBRUNTIMEVERIF_MainWindow::
		SET__foregroundcolor__ON__accepting_state(uint 			row_number,
												  QTableWidget 	*a_table_widget,
												  QColor        a_color_to_SET /* = Qt::green */)
{
	if (0 != a_table_widget)
	{
		QTableWidgetItem *a_qwidget_item = 0;

		for (int k = 0; k < a_table_widget->columnCount(); ++k)
		{
			a_qwidget_item = a_table_widget->item(row_number, k);

			if (0 != a_qwidget_item)
			{
				a_qwidget_item->setForeground(a_color_to_SET);
			}
		}
	}
}


void *YRIDBRUNTIMEVERIF_MainWindow::VIEW_current_RUNTIME_MONITOR()
{
    YRI_DB_RUNTIME_VERIF_Monitor *a_to_print_DOT_FORMAT_runtime_monitor =
        user_defined_Runtime_Monitors_NAME__TO__RUNTIME_INSTANCES
            .value(RUNTIME_MONITOR_name_TO_PRINT_DOT);

    emit SIGNAL_INCREMENT_PROGRESS_BAR(30);

	if (0 != a_to_print_DOT_FORMAT_runtime_monitor)
	{
		QString DOT_FORMAT =
				a_to_print_DOT_FORMAT_runtime_monitor
                    ->print_TO_dot_FILE(YRI_DB_RUNTIME_VERIF_Config::temporaryFilesDir,
                                        RUNTIME_MONITOR_name_TO_PRINT_DOT,
                                        true,
                                        true,
                                        true);

        emit SIGNAL_INCREMENT_PROGRESS_BAR(90);
	}
}


void YRIDBRUNTIMEVERIF_MainWindow::
        setLast_SelectedRow_Row_ID(const QModelIndex &a_model_CELL_index)
{
    _Last_SelectedRow_Row_INDEX = &a_model_CELL_index;

    switch(tabWidget_SQL_ERROR_EVENT_LOGGING->currentIndex())
    {
        case SQL_ERROR_EVENT_REPORTING_LOGGING:

            _qtabwidget_logging__To__LAST_SELECTED_row_INDEX
                .insert(tableWidget_LOGGING_ERROR_EVENT,
                        &a_model_CELL_index);
            break;


        case SQL_EVENT_LOGGING:
            _qtabwidget_logging__To__LAST_SELECTED_row_INDEX
                .insert(tableWidget_LOGGING,
                        &a_model_CELL_index);
            break;


        case CONSOLE_LOGGING_RAW:
            _Last_SelectedRow_Row_INDEX_Console_debugging = &a_model_CELL_index;
            break;
    }
}


void YRIDBRUNTIMEVERIF_MainWindow::
        get_console_Debugging_LOG_Raw_PRINT_OUT_TexTableString(QTableWidget  &current_QTable_Widget_Item,
                                                               QString       &texTable_IN_OUT,
                                                               int            row_MAX_TO_GO_export /* = -1 */)
{
	int rowCount = current_QTable_Widget_Item.rowCount();

    int columnCount = current_QTable_Widget_Item.columnCount();


    texTable_IN_OUT.append(YRI_DB_RUNTIME_VERIF_Utils::Console_RAW___LOG___Header_FIRST_print_pdf_file);

    texTable_IN_OUT.append(YRI_DB_RUNTIME_VERIF_Utils::Console_RAW___LOG___Header_Second__print_pdf_file);


    int MAX_TABLE_MODDEL_ROW_COUNT__to_export = rowCount;

	if (row_MAX_TO_GO_export > -1)
	{
        MAX_TABLE_MODDEL_ROW_COUNT__to_export = row_MAX_TO_GO_export;
	}



	bool color_this_row_grey = true;


	int LINE_COUNT_PER_PDF_PAGE = 41;


	QString cell_text;


    int TABLE_COUNT = qFloor(rowCount / LINE_COUNT_PER_PDF_PAGE);

    int current_table_count = 0;

	int current_pdf_page_line_count = 0;

	uint Visual_ID_counter = 0;

	//Tex table body
	for (int i = 0;
         i < MAX_TABLE_MODDEL_ROW_COUNT__to_export && current_pdf_page_line_count <= LINE_COUNT_PER_PDF_PAGE;
         ++i)
	{
        color_this_row_grey = (0 == i%2);

        if (color_this_row_grey)
        {
            texTable_IN_OUT.append(QString("\\rowcolor{yerithColorGray}"));
        }
        else
        {
            texTable_IN_OUT.append(QString("\\rowcolor{white}"));
        }


        //We add a cell for row numbering wioth an ID number.
        {
            ++Visual_ID_counter;

            QTableWidgetItem *an_item_ID = new QTableWidgetItem(QString::number(Visual_ID_counter));

            if (0 != an_item_ID)
            {
                YRI_DB_RUNTIME_VERIF_Utils::handleTexTableItemText(columnCount,
                                                                  texTable_IN_OUT,
                                                                  0,
                                                                  an_item_ID->text());
            }
        }


        for (int j = 0; j < columnCount; ++j)
        {
            QTableWidgetItem *an_item = 0;

            an_item = current_QTable_Widget_Item.item(i, j);

            if (0 != an_item)
            {
                if (j != 4)
                {
                    cell_text = an_item->text();
                }
                else
                {
                    cell_text = GET_NUM_STRING(an_item->text().toDouble());

                }
            }

            YRI_DB_RUNTIME_VERIF_Utils::handleTexTableItemText(columnCount,
                                                              texTable_IN_OUT,
                                                              j,
                                                              cell_text,
                                                              an_item);
        }

        if (i < rowCount - 1)
        {
            texTable_IN_OUT.append("\\hline\n");
        }


        ++current_pdf_page_line_count;


        if (LINE_COUNT_PER_PDF_PAGE - 1 == current_pdf_page_line_count)
        {
            current_pdf_page_line_count = 0;

            if (current_table_count < TABLE_COUNT)
            {
                texTable_IN_OUT.append(YRI_DB_RUNTIME_VERIF_Utils::Console_RAW___LOG___Footer_print_pdf_file);

                texTable_IN_OUT.append("\\newpage\n");

                texTable_IN_OUT.append(YRI_DB_RUNTIME_VERIF_Utils::Console_RAW___LOG___Header_FIRST_print_pdf_file);

                texTable_IN_OUT.append(YRI_DB_RUNTIME_VERIF_Utils::Console_RAW___LOG___Header_Second__print_pdf_file);
            }

            ++current_table_count;

            if (current_table_count > 0)
            {
                LINE_COUNT_PER_PDF_PAGE = 57;
            }
        }

    } //for-i


    texTable_IN_OUT.append(YRI_DB_RUNTIME_VERIF_Utils::Console_RAW___LOG___Footer_print_pdf_file);

}


void YRIDBRUNTIMEVERIF_MainWindow::get_PRINT_OUT_TexTableString(QTableWidget  &current_QTable_Widget_Item,
                                                               QString       &texTable_IN_OUT,
                                                               int           row_MAX_TO_GO_export /* = -1 */)
{
	int rowCount = current_QTable_Widget_Item.rowCount();

    int columnCount = current_QTable_Widget_Item.columnCount();


    texTable_IN_OUT.append(YRI_DB_RUNTIME_VERIF_Utils::Sql__EVENT___LOG___Header_FIRST_print_pdf_file);

    texTable_IN_OUT.append(YRI_DB_RUNTIME_VERIF_Utils::Sql__EVENT___LOG___Header_Second__print_pdf_file);


    int MAX_TABLE_MODDEL_ROW_COUNT__to_export = rowCount;

	if (row_MAX_TO_GO_export > -1)
	{
        MAX_TABLE_MODDEL_ROW_COUNT__to_export = row_MAX_TO_GO_export;
	}



	bool color_this_row_grey = true;


	int LINE_COUNT_PER_PDF_PAGE = 41;


	QString cell_text;


    int TABLE_COUNT = qFloor(rowCount / LINE_COUNT_PER_PDF_PAGE);

    int current_table_count = 0;

	int current_pdf_page_line_count = 0;

	uint Visual_ID_counter = 0;

	//Tex table body
	for (int i = 0;
         i < MAX_TABLE_MODDEL_ROW_COUNT__to_export && current_pdf_page_line_count <= LINE_COUNT_PER_PDF_PAGE;
         ++i)
	{
        color_this_row_grey = (0 == i%2);

        if (color_this_row_grey)
        {
            texTable_IN_OUT.append(QString("\\rowcolor{yerithColorGray}"));
        }
        else
        {
            texTable_IN_OUT.append(QString("\\rowcolor{white}"));
        }


        //We add a cell for row numbering wioth an ID number.
        {
            ++Visual_ID_counter;

            QTableWidgetItem *an_item_ID = new QTableWidgetItem(QString::number(Visual_ID_counter));

            if (0 != an_item_ID)
            {
                YRI_DB_RUNTIME_VERIF_Utils::handleTexTableItemText(columnCount,
                                                                  texTable_IN_OUT,
                                                                  0,
                                                                  an_item_ID->text());
            }
        }


        for (int j = 0; j < columnCount; ++j)
        {
            QTableWidgetItem *an_item = 0;

            an_item = current_QTable_Widget_Item.item(i, j);

            if (0 != an_item)
            {
                if (j != 4)
                {
                    cell_text = an_item->text();
                }
                else
                {
                    cell_text = GET_NUM_STRING(an_item->text().toDouble());

                }
            }

            YRI_DB_RUNTIME_VERIF_Utils::handleTexTableItemText(columnCount,
                                                              texTable_IN_OUT,
                                                              j,
                                                              cell_text,
                                                              an_item);
        }

        if (i < rowCount - 1)
        {
            texTable_IN_OUT.append("\\hline\n");
        }


        ++current_pdf_page_line_count;


        if (LINE_COUNT_PER_PDF_PAGE - 1 == current_pdf_page_line_count)
        {
            current_pdf_page_line_count = 0;

            if (current_table_count < TABLE_COUNT)
            {
                texTable_IN_OUT.append(YRI_DB_RUNTIME_VERIF_Utils::Sql__EVENT___LOG___Footer_print_pdf_file);

                texTable_IN_OUT.append("\\newpage\n");

                texTable_IN_OUT.append(YRI_DB_RUNTIME_VERIF_Utils::Sql__EVENT___LOG___Header_FIRST_print_pdf_file);

                texTable_IN_OUT.append(YRI_DB_RUNTIME_VERIF_Utils::Sql__EVENT___LOG___Header_Second__print_pdf_file);
            }

            ++current_table_count;

            if (current_table_count > 0)
            {
                LINE_COUNT_PER_PDF_PAGE = 57;
            }
        }

    } //for-i


    texTable_IN_OUT.append(YRI_DB_RUNTIME_VERIF_Utils::Sql__EVENT___LOG___Footer_print_pdf_file);

}


void YRIDBRUNTIMEVERIF_MainWindow::yri_PRINT_with_PROGRESS_BAR_ON__console_debugging_Log_excerpt(int a_row_FOR_pdf_printing_max /* = -1*/)
{
    int p = a_row_FOR_pdf_printing_max;

    YRI_DB_RUNTIME_VERIF_ProgressBar(this)(this,
                                          &p,
                                          &YRIDBRUNTIMEVERIF_MainWindow::PRINT_console_debugging_Log_excerpt__POINTER_PARAMETER);
}


void YRIDBRUNTIMEVERIF_MainWindow::yri_PRINT_with_PROGRESS_BAR_ON__event_log_excerpt(int a_row_FOR_pdf_printing_max /* = -1*/)
{
    int p = a_row_FOR_pdf_printing_max;

    YRI_DB_RUNTIME_VERIF_ProgressBar(this)(this,
                                          &p,
                                          &YRIDBRUNTIMEVERIF_MainWindow::PRINT_event_log_excerpt__POINTER_PARAMETER);
}


bool YRIDBRUNTIMEVERIF_MainWindow::PRINT_console_debugging_Log_excerpt_till_selected_LOGGING_string_ID()
{
    int a_row_FOR_pdf_printing_max = -1;

    if (0 != _Last_SelectedRow_Row_INDEX_Console_debugging)
    {
        a_row_FOR_pdf_printing_max = _Last_SelectedRow_Row_INDEX_Console_debugging->row() + 1;
    }
    else
    {
        a_row_FOR_pdf_printing_max = -1;
    }

    return PRINT_console_debugging_Log_excerpt(a_row_FOR_pdf_printing_max);
}


bool YRIDBRUNTIMEVERIF_MainWindow::PRINT_event_log_excerpt_till_selected_SQL_event()
{
    int a_row_FOR_pdf_printing_max = -1;

    if (0 != _Last_SelectedRow_Row_INDEX)
    {
        a_row_FOR_pdf_printing_max = _Last_SelectedRow_Row_INDEX->row() + 1;
    }
    else
    {
        a_row_FOR_pdf_printing_max = -1;
    }

    return PRINT_event_log_excerpt(a_row_FOR_pdf_printing_max);
}


bool YRIDBRUNTIMEVERIF_MainWindow::PRINT_console_debugging_Log_excerpt(int a_row_FOR_pdf_printing_max /* = -1 */)
{
    YRIDBRUNTIMEVERIF_TableWidget *current_QTable_Widget_Item =
                                    Get_CURRENT_QTable_WIDGET();


    if (0 == current_QTable_Widget_Item)
    {
        QMessageBox::information(toolBar_mainWindow_YRI_DB_RUNTIME_VERIF,
                                 QObject::tr("NO QTABLEWIDGET existing now"),
                                 QObject::tr("No event log data to print out !"));

        return false;
    }


	if (current_QTable_Widget_Item->rowCount() <= 0)
	{
		QMessageBox::information(toolBar_mainWindow_YRI_DB_RUNTIME_VERIF,
				QObject::tr("Event log printing"),
				QObject::tr("No event log data to print out !"));

		return false;
	}


	QString EN_template_CONSOLE_RAW_LOG__tex_table;


	QString EN_template_CONSOLE_RAW_LOG__TexDocument =
        YRI_DB_RUNTIME_VERIF_Utils::EN_template_CONSOLE_RAW_LOG_TEX_document;


	get_console_Debugging_LOG_Raw_PRINT_OUT_TexTableString(*current_QTable_Widget_Item,
                                                            EN_template_CONSOLE_RAW_LOG__tex_table,
                                                            a_row_FOR_pdf_printing_max);


	//qDebug() << EN_template_EVENT_LOG__tex_table;


	emit SIGNAL_INCREMENT_PROGRESS_BAR(18);


    EN_template_CONSOLE_RAW_LOG__TexDocument.append(EN_template_CONSOLE_RAW_LOG__tex_table)
                                            .append("\n")
                                            .append("\\end{document}");


	emit SIGNAL_INCREMENT_PROGRESS_BAR(50);


    if (a_row_FOR_pdf_printing_max > 0)
    {
        EN_template_CONSOLE_RAW_LOG__TexDocument
            .replace("YRIDBRUNTIMEVERIFSUBJECT",
                     "CONSOLE DEBUGGING LOG EXCERPT");
    }
    else
    {
        EN_template_CONSOLE_RAW_LOG__TexDocument
            .replace("YRIDBRUNTIMEVERIFSUBJECT",
                     "CONSOLE DEBUGGING LOG Full file");
    }


    QString current_date;


    YRI_DB_RUNTIME_VERIF_Utils::getCurrentSimplifiedDateWITHmilliseconds(current_date);


    EN_template_CONSOLE_RAW_LOG__TexDocument.replace("YRIDBRUNTIMEVERIFPAPERSPEC", "a4paper");
    EN_template_CONSOLE_RAW_LOG__TexDocument.replace("YRIDBRUNTIMEVERIFDATE", current_date);
    EN_template_CONSOLE_RAW_LOG__TexDocument.replace("YRIDBRUNTIMEVERIFPRINTTIME", CURRENT_TIME_WITH_MILLISECONDS);



	emit SIGNAL_INCREMENT_PROGRESS_BAR(70);


    QString prefixFileName;

    prefixFileName.append(YRI_DB_RUNTIME_VERIF_Utils::getUniquePrefixFileInTemporaryFilesDir("yri-db-runtime-verif-CONSOLE-DEBUGGING-RAW-LOG-"));
	//qDebug() << "++\n" << EN_template_EVENT_LOG__TexDocument;

	QFile tmpLatexFile(prefixFileName + "tex");

	if (tmpLatexFile.open(QFile::WriteOnly))
	{
		tmpLatexFile.write(EN_template_CONSOLE_RAW_LOG__TexDocument.toUtf8());
	}

	tmpLatexFile.close();

	QString pdfReceiptFileName = YRIDBRUNTIMEVERIF_Process::compileLatex(prefixFileName);

	if (!pdfReceiptFileName.isEmpty())
	{
		YRIDBRUNTIMEVERIF_Process::startPdfViewerProcess(pdfReceiptFileName);
	}

	emit SIGNAL_INCREMENT_PROGRESS_BAR(98);

	return true;
}


bool YRIDBRUNTIMEVERIF_MainWindow::PRINT_event_log_excerpt(int a_row_FOR_pdf_printing_max /* = -1 */)
{
    YRIDBRUNTIMEVERIF_TableWidget *current_QTable_Widget_Item =
                                    Get_CURRENT_QTable_WIDGET();


    if (0 == current_QTable_Widget_Item)
    {
        QMessageBox::information(toolBar_mainWindow_YRI_DB_RUNTIME_VERIF,
                                 QObject::tr("NO QTABLEWIDGET existing now"),
                                 QObject::tr("No event log data to print out !"));

        return false;
    }


	if (current_QTable_Widget_Item->rowCount() <= 0)
	{
		QMessageBox::information(toolBar_mainWindow_YRI_DB_RUNTIME_VERIF,
				QObject::tr("Event log printing"),
				QObject::tr("No event log data to print out !"));

		return false;
	}


	QString EN_template_EVENT_LOG__tex_table;


	QString EN_template_EVENT_LOG__TexDocument =
        YRI_DB_RUNTIME_VERIF_Utils::EN_template_EVENT_LOG_TEX_document;

	//QString factureDate(infoEntreprise.getVille_LATEX());

	//YRI_DB_RUNTIME_VERIF_Utils::getCurrentSimplifiedDate(factureDate);


	get_PRINT_OUT_TexTableString(*current_QTable_Widget_Item,
                                 EN_template_EVENT_LOG__tex_table,
                                 a_row_FOR_pdf_printing_max);


	//qDebug() << EN_template_EVENT_LOG__tex_table;


	emit SIGNAL_INCREMENT_PROGRESS_BAR(18);


    EN_template_EVENT_LOG__TexDocument.append(EN_template_EVENT_LOG__tex_table)
                                      .append("\n")
                                      .append("\\end{document}");


	emit SIGNAL_INCREMENT_PROGRESS_BAR(50);


    EN_template_EVENT_LOG__TexDocument
        .replace("YRIDBRUNTIMEVERIFSUBJECT",
                 "SQL Event log Excerpt");



    QString current_date;


    YRI_DB_RUNTIME_VERIF_Utils::getCurrentSimplifiedDateWITHmilliseconds(current_date);


    EN_template_EVENT_LOG__TexDocument.replace("YRIDBRUNTIMEVERIFPAPERSPEC", "a4paper");
    EN_template_EVENT_LOG__TexDocument.replace("YRIDBRUNTIMEVERIFDATE", current_date);
    EN_template_EVENT_LOG__TexDocument.replace("YRIDBRUNTIMEVERIFPRINTTIME", CURRENT_TIME_WITH_MILLISECONDS);



	emit SIGNAL_INCREMENT_PROGRESS_BAR(70);


    QString prefixFileName;

    prefixFileName.append(YRI_DB_RUNTIME_VERIF_Utils::getUniquePrefixFileInTemporaryFilesDir("yri-db-runtime-verif-EVENT-LOG-"));
	//qDebug() << "++\n" << EN_template_EVENT_LOG__TexDocument;

	QFile tmpLatexFile(prefixFileName + "tex");

	if (tmpLatexFile.open(QFile::WriteOnly))
	{
		tmpLatexFile.write(EN_template_EVENT_LOG__TexDocument.toUtf8());
	}

	tmpLatexFile.close();

	QString pdfReceiptFileName = YRIDBRUNTIMEVERIF_Process::compileLatex(prefixFileName);

	if (!pdfReceiptFileName.isEmpty())
	{
		YRIDBRUNTIMEVERIF_Process::startPdfViewerProcess(pdfReceiptFileName);
	}

	emit SIGNAL_INCREMENT_PROGRESS_BAR(98);

	return true;
}


void YRIDBRUNTIMEVERIF_MainWindow::ON_Configfuration_panel_window_trigerred()
{
    YRIDBRUNTIMEVERIF_Windows *ALL_WINDOWS_INSTANCE =
    		YRI_DB_RUNTIME_VERIF_Config::GET_ALL_WINDOWS_instance();

    if (0 != ALL_WINDOWS_INSTANCE)
    {
    	ALL_WINDOWS_INSTANCE->_yrdbruntimeverif_setup_Window->yri_show();
    }

    yri_close();
}


bool YRIDBRUNTIMEVERIF_MainWindow::ON_action_export_as_CSV_till_selected_console_debugging_LINE()
{
    int a_row = -1;

    if (0 != _Last_SelectedRow_Row_INDEX_Console_debugging)
    {
        a_row = _Last_SelectedRow_Row_INDEX_Console_debugging->row() + 1;
    }
    else
    {
        a_row = -1;
    }

    return
        YRI_DB_RUNTIME_VERIF_Utils::SAVE_AS_csv_file(*this,
                                                    *tableWidget_Console_logging_Raw,
                                                    "Console-debugging-log-Partial-csv-format",
                                                    "Console Debugging LOGGING (partial) csv export",
                                                    a_row);
}


bool YRIDBRUNTIMEVERIF_MainWindow::ON_action_export_as_CSV_till_selected_SQL_event()
{
    int a_row = -1;

    if (0 != _Last_SelectedRow_Row_INDEX)
    {
        a_row = _Last_SelectedRow_Row_INDEX->row() + 1;
    }
    else
    {
        a_row = -1;
    }

    return
        YRI_DB_RUNTIME_VERIF_Utils::SAVE_AS_csv_file(*this,
                                                    *tableWidget_LOGGING,
                                                    "sql-event-log-listing-csv-format",
                                                    "SQL event log csv export",
                                                    a_row);
}


void YRIDBRUNTIMEVERIF_MainWindow::
        ON_action_set_current_selected_SQL_event_as_filter_and_search()
{
    //THE USER MUST MANUALLY UNCHECKED "checkBox_ALL_STATE_SAFETY_PROPERTIES"
    //before any other search filtering could occur here.
    if (SQL_ERROR_EVENT_REPORTING_LOGGING == tabWidget_SQL_ERROR_EVENT_LOGGING->currentIndex() &&
        checkBox_ALL_STATE_SAFETY_PROPERTIES->isChecked())
    {
        QMessageBox::warning(toolBar_mainWindow_YRI_DB_RUNTIME_VERIF,
                             QObject::tr("(1) A RUNTIME MONITOR is selected"),
                             QObject::tr("FIRST UNCHECKED checkbox near combobox \"runtime monitor name\" !"));

        ON_BUTON_Reset_pressed(true);

        return ;
    }


    YRIDBRUNTIMEVERIF_TableWidget *current_QTable_Widget_Item =
                                    Get_CURRENT_QTable_WIDGET();


    if (0 == current_QTable_Widget_Item)
    {
        return;
    }


    if (current_QTable_Widget_Item->rowCount() <= 0)
    {
        return ;
    }


    int current_row = current_QTable_Widget_Item->currentRow();


    static const uint SIGNALItem_COLUMN = 1;


    QString current_selected_SQL_event_text;


    QTableWidgetItem *an_item =
        current_QTable_Widget_Item->item(current_row,
                                         SIGNALItem_COLUMN);

    if (0 != an_item)
    {
        current_selected_SQL_event_text = an_item->text();

        comboBox_global_filtering->find_AND_SET_CURRENT_INDEX(QString("sql event log"));

        lineEdit_SQL_event_filtering->setText(current_selected_SQL_event_text);

        ON_QTABLEWIDGET_FILTER_ITEM_Exact_GIVEN(current_selected_SQL_event_text);
    }
}


void YRIDBRUNTIMEVERIF_MainWindow::SOFT_Reset_selected()
{
    lineEdit_SQL_event_filtering->clear();

    lineEdit_FILTERING_COUNT->clear();


    YRIDBRUNTIMEVERIF_TableWidget *current_QTable_Widget_Item = Get_CURRENT_QTable_WIDGET();

    if (0 != current_QTable_Widget_Item)
    {
        current_QTable_Widget_Item->CLEAR_FILTERING();
    }
}


void YRIDBRUNTIMEVERIF_MainWindow::ON_BUTON_Reset_pressed(bool soft /* = false */)
{
    YRIDBRUNTIMEVERIF_TableWidget *current_QTable_Widget_Item =
                                        Get_CURRENT_QTable_WIDGET();

    comboBox_global_filtering->setCurrentIndex(0);

    comboBox_SQL_event_filtering->setCurrentIndex(0);

    lineEdit_SQL_event_filtering->clear();

    lineEdit_FILTERING_COUNT->clear();

    if (!soft)
    {
        if (0 != current_QTable_Widget_Item)
        {
            current_QTable_Widget_Item->CLEAR_FILTERING();
        }
    }
}


void YRIDBRUNTIMEVERIF_MainWindow::ON_BUTON_Filter_pressed()
{
    //THE USER MUST MANUALLY UNCHECK "checkBox_ALL_STATE_SAFETY_PROPERTIES"
    //before any other search filtering could occur here.
    if (SQL_ERROR_EVENT_REPORTING_LOGGING == tabWidget_SQL_ERROR_EVENT_LOGGING->currentIndex() &&
        checkBox_ALL_STATE_SAFETY_PROPERTIES->isChecked())
    {
        QMessageBox::warning(toolBar_mainWindow_YRI_DB_RUNTIME_VERIF,
                             QObject::tr("(2) A RUNTIME MONITOR is selected"),
                             QObject::tr("FIRST UNCHECK checkbox near combobox \"runtime monitor name\" !"));

        ON_BUTON_Reset_pressed(true);

        return ;
    }


    ON_QTABLEWIDGET_FILTER_ITEM_Exact_GIVEN(lineEdit_SQL_event_filtering->text().trimmed());
}


//for combobox "comboBox_global_filtering"
void YRIDBRUNTIMEVERIF_MainWindow::RESET_comboBox_SQL_event_filtering()
{
    comboBox_SQL_event_filtering->setCurrentIndex(0);

    QString lineEdit_SQL_event_filtering__CURRENT_text =
                lineEdit_SQL_event_filtering->text();

    SOFT_Reset_selected();

    //THE PREVIOUS COMMAND CLEARS content of "lineEdit_SQL_event_filtering"
    lineEdit_SQL_event_filtering->setText(lineEdit_SQL_event_filtering__CURRENT_text);
}


void YRIDBRUNTIMEVERIF_MainWindow::
        RESET_comboBox_SQL_event_filtering(const QString &a_SQL_event_item)
{
    comboBox_SQL_event_filtering->setCurrentIndex(0);

    QString lineEdit_SQL_event_filtering__CURRENT_text =
                lineEdit_SQL_event_filtering->text();

    SOFT_Reset_selected();

    //THE PREVIOUS COMMAND CLEARS content of "lineEdit_SQL_event_filtering"
    lineEdit_SQL_event_filtering->setText(lineEdit_SQL_event_filtering__CURRENT_text);
}


void YRIDBRUNTIMEVERIF_MainWindow::
        ON_QTABLEWIDGET_FILTER_ITEM_selected(const QString &a_SQL_event_item)
{
    //THE USER MUST MANUALLY UNCHECKED "checkBox_ALL_STATE_SAFETY_PROPERTIES"
    //before any other search filtering could occur here.
    if (SQL_ERROR_EVENT_REPORTING_LOGGING == tabWidget_SQL_ERROR_EVENT_LOGGING->currentIndex() &&
        checkBox_ALL_STATE_SAFETY_PROPERTIES->isChecked())
    {
        QMessageBox::warning(toolBar_mainWindow_YRI_DB_RUNTIME_VERIF,
                             QObject::tr("A RUNTIME MONITOR is selected"),
                             QObject::tr("FIRST UNCHECKED checkbox near combobox \"runtime monitor name\" !"));

        ON_BUTON_Reset_pressed(true);

        return ;
    }


    lineEdit_SQL_event_filtering->clear();

    if (a_SQL_event_item.isEmpty())
    {
        SOFT_Reset_selected();

        return ;
    }


    YRIDBRUNTIMEVERIF_TableWidget *current_QTable_Widget_Item = Get_CURRENT_QTable_WIDGET();

    if (0 == current_QTable_Widget_Item)
    {
        return;
    }


    RESET_comboBox_global_filtering();


    //PREVIOUS COMMAND CLEARS resets of "comboBox_SQL_event_filtering"
    comboBox_SQL_event_filtering->find_AND_SET_CURRENT_INDEX(a_SQL_event_item);


    uint MATCHED_search = current_QTable_Widget_Item->FILTER_ITEM(a_SQL_event_item);


    lineEdit_FILTERING_COUNT->setText(QString::number(MATCHED_search));
}


void YRIDBRUNTIMEVERIF_MainWindow::
        ON_QTABLEWIDGET_FILTER_ITEM_Exact_GIVEN(const QString &a_SourceSUT__OR__SQLEvent__Text)
{
    if (a_SourceSUT__OR__SQLEvent__Text.isEmpty())
    {
        return ;
    }


    YRIDBRUNTIMEVERIF_TableWidget *current_QTable_Widget_Item =
                                        Get_CURRENT_QTable_WIDGET();

    if (0 == current_QTable_Widget_Item)
    {
        return;
    }


    current_QTable_Widget_Item->CLEAR_FILTERING();


    RESET_comboBox_SQL_event_filtering();


    //THE PREVIOUS COMMAND CLEARS content of "lineEdit_SQL_event_filtering"
    lineEdit_SQL_event_filtering->setText(a_SourceSUT__OR__SQLEvent__Text);


    uint MATCHED_search = 0;

    if (YRI_DB_RUNTIME_VERIF_Utils::isEqualsCaseInsensitive(comboBox_global_filtering->currentText(),
                                                            QString("source")))
    {
        MATCHED_search = current_QTable_Widget_Item->FILTER__SUT_SOURCE__ITEM(a_SourceSUT__OR__SQLEvent__Text);
    }
    else if (YRI_DB_RUNTIME_VERIF_Utils::isEqualsCaseInsensitive(comboBox_global_filtering->currentText(),
                                                                 QString("sql event log")))
    {
        MATCHED_search = current_QTable_Widget_Item->FILTER_ITEM(a_SourceSUT__OR__SQLEvent__Text,
                                                                 true);
    }
    else
    {
        QMessageBox::warning(toolBar_mainWindow_YRI_DB_RUNTIME_VERIF,
                             QObject::tr("'source' OR 'ql event log' to look for ?"),
                             QObject::tr("Please select in 2 (second) combobox either 'source' OR 'sql event log' "
                                         "as a type of \"sql event\" or a \"SUT (PUA)\" to look for !"));
    }


    lineEdit_FILTERING_COUNT->setText(QString::number(MATCHED_search));
}


void *YRIDBRUNTIMEVERIF_MainWindow::ACTION_USER_GUIDE_method()
{
	QStringList progArguments;

	emit SIGNAL_INCREMENT_PROGRESS_BAR(12);

	QProcess aProcess;

	progArguments << "/usr/share/doc/yri-db-runtime-verif/YERITH_QVGE.pdf";

	emit SIGNAL_INCREMENT_PROGRESS_BAR(30);

    YRIDBRUNTIMEVERIF_Process::startDetached
            (aProcess,
             YRI_DB_RUNTIME_VERIF_Config::pathToPdfReader,
             progArguments);

    emit SIGNAL_INCREMENT_PROGRESS_BAR(98);
}


void YRIDBRUNTIMEVERIF_MainWindow::SET__Sut__VISIBILITY_FOR_logging(QString a_SUT_ID)
{
    //We check if user has instructed to log this SUT SQL events
    bool render_logging_SUT_visible = Is_SUT__to__LOG(a_SUT_ID);

    if (!render_logging_SUT_visible)
    {
        Disable_comboBox_RUNTIME_MONITOR_NAME_Logging();
    }
    else
    {
        comboBox_RUNTIME_MONITOR_NAME_Logging->setVisible(render_logging_SUT_visible);
    }

    tableWidget_LOGGING_2->setVisible(render_logging_SUT_visible);
}


YRIDBRUNTIMEVERIF_TableWidget* YRIDBRUNTIMEVERIF_MainWindow::Get_CURRENT_QTable_WIDGET()
{
    YRIDBRUNTIMEVERIF_TableWidget *current_QTable_Widget_Item = 0;

    switch(tabWidget_SQL_ERROR_EVENT_LOGGING->currentIndex())
    {
    case SQL_ERROR_EVENT_REPORTING_LOGGING:
        current_QTable_Widget_Item = tableWidget_LOGGING_ERROR_EVENT;
        break;

    case SQL_EVENT_LOGGING:
        current_QTable_Widget_Item = tableWidget_LOGGING;
        break;

    case CONSOLE_LOGGING_RAW:
        current_QTable_Widget_Item = tableWidget_Console_logging_Raw;
        break;

    default:
        break;

    }

    return current_QTable_Widget_Item;
}


void YRIDBRUNTIMEVERIF_MainWindow::set_runtime_monitor_name_ERROR_LOGGING_visible(bool aVisibleValue)
{
    tableWidget_LOGGING_ERROR_SOURCE_LOCATION->setVisible(aVisibleValue);

    label_RUNTIME_MONITOR_VERIFIER_TESTER->setVisible(aVisibleValue);

    comboBox_RUNTIME_MONITOR_NAME_Error_LOGGING->setVisible(aVisibleValue);
}


void YRIDBRUNTIMEVERIF_MainWindow::SWICTH_EVENT__LOG__to___console__log__EVENT_action(bool console_debugging_log /* = true */)
{
    QObject::disconnect(actionExport_as_CSV_till_selected_SQL_event, 0, 0, 0);

    QObject::disconnect(action_save_to_csv_format_sheet, 0, 0, 0);


    QObject::disconnect(actionPRINT_event_log_excerpt_till_selected_SQL_event, 0, 0, 0);

    QObject::disconnect(actionPRINT_event_log_FULL, 0, 0, 0);



    if (console_debugging_log)
    {
        SET_AN_ACTION_TEXT_AND_Tooltip_Text(*actionExport_as_CSV_till_selected_SQL_event,
                                            QObject::tr("Export CONSOLE Debugging Log as CSV till selected LINE"));

        SET_AN_ACTION_TEXT_AND_Tooltip_Text(*action_save_to_csv_format_sheet,
                                            QObject::tr("Save CONSOLE Debugging Log to CSV format sheet"));

        connect(actionExport_as_CSV_till_selected_SQL_event,
                SIGNAL(triggered()),
                this,
                SLOT(ON_action_export_as_CSV_till_selected_console_debugging_LINE()));

        connect(action_save_to_csv_format_sheet,
                SIGNAL(triggered()),
                this,
                SLOT(export_Console_DEBUGGING_csv_file()));



        SET_AN_ACTION_TEXT_AND_Tooltip_Text(*actionPRINT_event_log_excerpt_till_selected_SQL_event,
                                            QObject::tr("Print console debugging raw excerpt till selected LINE"));

        SET_AN_ACTION_TEXT_AND_Tooltip_Text(*actionPRINT_event_log_FULL,
                                            QObject::tr("Print console debugging raw log (full)"));

        connect(actionPRINT_event_log_excerpt_till_selected_SQL_event,
                SIGNAL(triggered()),
                this,
                SLOT(yri_PRINT_console_debugging_Log_excerpt_till_selected_LOGGING_string_ID()));

        connect(actionPRINT_event_log_FULL,
                SIGNAL(triggered()),
                this,
                SLOT(yri_PRINT_with_PROGRESS_BAR_ON__console_debugging_Log_excerpt()));
    }
    else
    {
        SET_AN_ACTION_TEXT_AND_Tooltip_Text(*actionExport_as_CSV_till_selected_SQL_event,
                                            QObject::tr("Export as CSV till selected SQL event"));

        SET_AN_ACTION_TEXT_AND_Tooltip_Text(*action_save_to_csv_format_sheet,
                                            QObject::tr("Save to CSV format sheet"));

        connect(actionExport_as_CSV_till_selected_SQL_event,
                SIGNAL(triggered()),
                this,
                SLOT(ON_action_export_as_CSV_till_selected_SQL_event()));

        connect(action_save_to_csv_format_sheet,
                SIGNAL(triggered()),
                this,
                SLOT(export_csv_file()));


        SET_AN_ACTION_TEXT_AND_Tooltip_Text(*actionPRINT_event_log_excerpt_till_selected_SQL_event,
                                            QObject::tr("Print event log excerpt till selected SQL event"));

        SET_AN_ACTION_TEXT_AND_Tooltip_Text(*actionPRINT_event_log_FULL,
                                            QObject::tr("Print event log (full)"));

        connect(actionPRINT_event_log_excerpt_till_selected_SQL_event,
                SIGNAL(triggered()),
                this,
                SLOT(yri_PRINT_with_PROGRESS_BAR_ON__event_log_excerpt_till_selected_SQL_event()));

        connect(actionPRINT_event_log_FULL,
                SIGNAL(triggered()),
                this,
                SLOT(yri_PRINT_with_PROGRESS_BAR_ON__event_log_excerpt()));
    }
}


void YRIDBRUNTIMEVERIF_MainWindow::
        contextMenuEvent(QContextMenuEvent *event)
{
    bool ANALYSIS_report_AVAILABLE = false;

    bool Console_Debugging_log = false;

    bool Enable___actionSet_current_selected_SQL_event_as_filter_and_search = true;


    uint VISIBLE_unique_row_count = 0;


    SWICTH_EVENT__LOG__to___console__log__EVENT_action(Console_Debugging_log);


    switch(tabWidget_SQL_ERROR_EVENT_LOGGING->currentIndex())
    {
    case SQL_ERROR_EVENT_REPORTING_LOGGING:

        if (_visible_ERROR_row_counter > 0)
        {
            ANALYSIS_report_AVAILABLE = true;
        }
        else
        {
            ANALYSIS_report_AVAILABLE = false;
        }

        VISIBLE_unique_row_count = _visible_ERROR_row_counter;
        break;


    case SQL_EVENT_LOGGING:

        if (_visible_row_counter > 0)
        {
            ANALYSIS_report_AVAILABLE = true;
        }
        else
        {
            ANALYSIS_report_AVAILABLE = false;
        }

        VISIBLE_unique_row_count = _visible_row_counter;
        break;


    case CONSOLE_LOGGING_RAW:

        Console_Debugging_log = true;

        //1 is set only to enable context menu here.
        VISIBLE_unique_row_count = 1;

        SWICTH_EVENT__LOG__to___console__log__EVENT_action(Console_Debugging_log);

        break;


    default:
        VISIBLE_unique_row_count = 0;
        break;

    }

    if (VISIBLE_unique_row_count > 0)
    {
        QMenu menu(this);

        menu.addAction(actionExport_as_CSV_till_selected_SQL_event);
        menu.addAction(actionPRINT_event_log_FULL);
        menu.addAction(actionPRINT_event_log_excerpt_till_selected_SQL_event);
        menu.addAction(action_save_to_csv_format_sheet);


        if (ANALYSIS_report_AVAILABLE)
        {
            menu.addAction(actionPRINT_AN_ANALYSIS_REPORT_for_currently_selected_Error_Event);
        }
        else
        {
            menu.removeAction(actionPRINT_AN_ANALYSIS_REPORT_for_currently_selected_Error_Event);
        }

        if (Enable___actionSet_current_selected_SQL_event_as_filter_and_search)
        {
            menu.addAction(actionSet_current_selected_SQL_event_as_filter_and_search);
        }
        else
        {
            menu.removeAction(actionSet_current_selected_SQL_event_as_filter_and_search);
        }

        menu.exec(event->globalPos());
    }
}


void YRIDBRUNTIMEVERIF_MainWindow::
        Set__TOOLTIP__for__CONDITIONS(YRIDBRUNTIMEVERIF_Logging_Info &a_logging_info)
{
	tableWidget_LOGGING_4
		->setToolTip(QString("PREVIOUS state: '%1'.\n\n"
                             "ACCEPTING state: ':%2'. \n\n"
                             "Accepting state (%2) is error state: '%3'.")
                        .arg(a_logging_info.A_PREVIOUS_STATE,
                             a_logging_info.AN_ACCEPTING_STATE,
                             a_logging_info.AN_ACCEPTING_STATE_is_error_state_VALUE));

    tableWidget_LOGGING_PRECONDITIONS
        ->setToolTip(a_logging_info.A_TRANSITION_precondition);

    tableWidget_LOGGING_postconditions
        ->setToolTip(a_logging_info.A_TRANSITION_postcondition);

    tableWidget_LOGGING_guarded_condition_expression
        ->setToolTip(QString("Predicate \"%1\" value is \"%2\" ")
                     .arg(a_logging_info.A_SQL_EVENT_LOG_guarded_condition_expression,
                          a_logging_info.A_SQL_EVENT_LOG_guarded_condition_expression_VALUE));
}


bool YRIDBRUNTIMEVERIF_MainWindow::
        CHANGE_visibility__Of__checkBox_ALL_STATE_SAFETY_PROPERTIES_Logging()
{
    bool Set_visibility = false;

    if (0 != _current_runtime_monitor_INSTANCE                            &&
        _current_runtime_monitor_INSTANCE->YRI_CPP_monitor_state_count() > 2)
    {
        checkBox_ALL_STATE_SAFETY_PROPERTIES_Logging
            ->setVisible(true);

        Set_visibility = true;
    }
    else
    {
        checkBox_ALL_STATE_SAFETY_PROPERTIES_Logging
            ->setVisible(false);

        Set_visibility = false;
    }

    return Set_visibility;
}


void YRIDBRUNTIMEVERIF_MainWindow::ON_STOP__logging__SUT_ACTIONS()
{
    YRIDBRUNTIMEVERIF_Windows *ALL_WINDOWS_INSTANCE =
    		YRI_DB_RUNTIME_VERIF_Config::GET_ALL_WINDOWS_instance();

    if (0 != ALL_WINDOWS_INSTANCE)
    {
        if (0 != ALL_WINDOWS_INSTANCE->_yrdbruntimeverif_main_Window)
        {
            QString SUT_string_ID = comboBox_SUT_identification->currentText();

            if (!SUT_string_ID.isEmpty())
            {
                ALL_WINDOWS_INSTANCE
                    ->_yrdbruntimeverif_main_Window
                        ->Set___SUT__Logging(SUT_string_ID,
                                             false);
            }
        }
    }
}


void YRIDBRUNTIMEVERIF_MainWindow::ON_START__logging__SUT_ACTIONS()
{
    YRIDBRUNTIMEVERIF_Windows *ALL_WINDOWS_INSTANCE =
    		YRI_DB_RUNTIME_VERIF_Config::GET_ALL_WINDOWS_instance();

    if (0 != ALL_WINDOWS_INSTANCE)
    {
        if (0 != ALL_WINDOWS_INSTANCE->_yrdbruntimeverif_main_Window)
        {
            QString SUT_string_ID = comboBox_SUT_identification->currentText();

            if (!SUT_string_ID.isEmpty())
            {
                qDebug() << "|> start logging of SYSTEM UDER TEST: "
                         << SUT_string_ID;

                ALL_WINDOWS_INSTANCE
                    ->_yrdbruntimeverif_main_Window
                        ->Set___SUT__Logging(SUT_string_ID,
                                             true);
            }
        }
    }
}


void YRIDBRUNTIMEVERIF_MainWindow::Set_A_SUT_comboBox_SUT_identification(QString &a_sut_identification)
{
    lineEdit_last_RUNTIME_MONITOR_Logged_at_runtime
        ->setText(QString("LAST logged runtime monitor : --- %1 ---")
                    .arg(a_sut_identification));

    comboBox_SUT_identification
        ->find_AND_SET_CURRENT_INDEX(a_sut_identification.trimmed());
}


bool YRIDBRUNTIMEVERIF_MainWindow::
        MAP___Assign_SutID__to__SutNAMEQString(QString A_SUT_ID,
                                               QString SutNAMEQString)
{
    bool assigned = false;

    if (!_MAP_SutID__TO__SutNAMEQString.contains(A_SUT_ID))
    {
        _MAP_SutID__TO__SutNAMEQString.insert(A_SUT_ID,
                                              SutNAMEQString);

        _MAP_SutID__TO__SutLogging.insert(A_SUT_ID,
                                          false);

        assigned = true;
    }
    else
    {
        /*QDEBUG_STRINGS_OUTPUT_1(QString("ATTEMP TO map assign %1 -> %2 (Already %3)")
                                    .arg(A_SUT_ID,
                                         SutNAMEQString,
                                         _MAP_SutID__TO__SutNAMEQString
                                            .value(A_SUT_ID)));*/

        assigned = false;
    }

    return assigned;
}

