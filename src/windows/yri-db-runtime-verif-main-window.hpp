/*
 * yri-db-runtime-verif-main-window.hpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */

#ifndef _YRI_DB_RUNTIME_VERIF_MAIN_WINDOW_HPP_
#define _YRI_DB_RUNTIME_VERIF_MAIN_WINDOW_HPP_

#include "../../ui_yri-db-runtime-verif-main-window.h"


#include "src/process/yri-db-runtime-verif-PROCESS.hpp"

#include "src/widgets/yri-db-runtime-verif-progress-bar.hpp"

#include "src/windows/yri-db-runtime-verif-COMMONS-window.hpp"

#include "src/utils/yri-db-runtime-verif-qmap.hpp"


#include <QtGui/QContextMenuEvent>

#include <QtWidgets/QMainWindow>

#include <QtCore/QObject>


class YRI_DB_RUNTIME_VERIF_Monitor;


class YRIDBRUNTIMEVERIF_MainWindow : public YRIDBRUNTIMEVERIF_CommonsWindow,
									public Ui_YRIDBRUNTIMEVERIF_MainWindow
{
	Q_OBJECT


public:

	YRIDBRUNTIMEVERIF_MainWindow();


    virtual inline ~YRIDBRUNTIMEVERIF_MainWindow()
    {
    }


    virtual inline QToolBar &get_tool_bar()
    {
    	return *toolBar_mainWindow_YRI_DB_RUNTIME_VERIF;
    }


    virtual void SELECT_Logging_row(uint a_row_selected);


    virtual void SELECT_ERROR_LOGGING_row(uint a_row_selected);


    virtual void Update_RUNTIME_MONITOR_names();


    virtual void SET_CURRENT_RUNTIME_MONITOR_name_Logging(QString A_RUNTIME_MONITOR_name);


    virtual void SET_CURRENT_RUNTIME_MONITOR_name_ERROR_Logging(QString A_RUNTIME_MONITOR_name);


    virtual inline QString GET_CURRENT_RUNTIME_MONITOR_name_Error_LOGGING()
    {
        return comboBox_RUNTIME_MONITOR_NAME_Error_LOGGING->currentText();
    }


    virtual inline int ADD_ITEM_Console_Raw(QStringList &Console_Raw_STR_MSG_List)
    {
       return ADD_ITEM_Console_Raw(Console_Raw_STR_MSG_List.join(YRI_DB_RUNTIME_VERIF_Utils::EMPTY_STRING).trimmed());
    }


    virtual int ADD_ITEM_Console_Raw(QString STRING_FOR_console_raw);


	virtual int ADD_ERROR_ITEM(QString                        TIMESTAMPtem,
                               QString                        SIGNALItem,
                               QString                        SOURCEItem,
                               QString                        TARGETItem,
                               QString                        changed_OR_modified_database_qty_Item,
                               YRIDBRUNTIMEVERIF_Logging_Info  &a_logging_info);


	virtual int ADD_ITEM(QString                        TIMESTAMPtem,
						 QString                        SIGNALItem,
						 QString                        SOURCEItem,
						 QString                        TARGETItem,
						 QString                        changed_OR_modified_database_qty_Item,
						 YRIDBRUNTIMEVERIF_Logging_Info  &a_logging_info);


	virtual void SET__CURRENT__RUNTIME__MONITOR
		(YRI_DB_RUNTIME_VERIF_Monitor *a_current_runtime_monitor_INSTANCE);


	virtual inline YRI_DB_RUNTIME_VERIF_Monitor *GET__CURRENT__RUNTIME__MONITOR()
	{
		return _current_runtime_monitor_INSTANCE;
	}


public slots:

    virtual void ON_STOP__logging__SUT_ACTIONS();


    virtual void ON_START__logging__SUT_ACTIONS();


    virtual void Set_A_SUT_comboBox_SUT_identification(QString &a_sut_identification);


    virtual inline void Set___SUT__Logging(QString A_SUT_ID,
                                           bool a_boolean_value)
    {
        _MAP_SutID__TO__SutLogging.insert(A_SUT_ID,
                                          a_boolean_value);
    }


    virtual inline bool Is_SUT__to__LOG(QString A_SUT_ID)
    {
        return _MAP_SutID__TO__SutLogging.value(A_SUT_ID);
    }


    virtual bool MAP___Assign_SutID__to__SutNAMEQString(QString A_SUT_ID,
                                                        QString SutNAMEQString);


	virtual void Set_YRIDBRUNTIMEVERIF_Logging_Info(uint     row_number,
												   QString  logging_info);


	virtual YRIDBRUNTIMEVERIF_Logging_Info *Get_YRIDBRUNTIMEVERIF_Logging_Info(uint row_number);


	virtual void set_connection_DBUS_status(QString	message_STATUS,
											bool 	error_not_connected = false);


    virtual inline void ON_QTABLEWIDGET_ITEM_itemSelectionChanged()
    {
        pushButton_lecteur_de_code_barres_Logging->click();
    }


	virtual void ON_QTABLEWIDGET_ITEM_pressed(QTableWidgetItem *aQTable_widget_item);


	/*
	 * aQTable_widget_item is set to zero ('0') when the
	 * hidden button "pushButton_lecteur_de_code_barres"
	 * for showing SQL recovered query string
	 * is only shown by now.
     */
	virtual void ON_QTABLEWIDGET_ERROR_ITEM_pressed(QTableWidgetItem *aQTable_widget_item = 0);


protected slots:


    virtual void Disable_comboBox_RUNTIME_MONITOR_NAME_Logging();


    virtual inline void STOP_YRI_DB_RUNTIME_VERIF_DAEMON_PROCESS()
    {
        YRIDBRUNTIMEVERIF_Process::STOP__Restart__GTK_gui_yri_db_runtime_verif();
    }


    virtual inline bool export_Console_DEBUGGING_csv_file()
    {
        return
            YRI_DB_RUNTIME_VERIF_Utils::
                SAVE_AS_csv_file(*this,
                                 *tableWidget_Console_logging_Raw,
                                 "console-debugging-log-listing-csv-format",
                                 "CONSOLE DEBUGGING log csv export");
    }


    bool export_csv_file();


    virtual bool set_SQL_current_recovered_query_string(QString SQL_QUERY_STRING,
                                                        QString TIMESTAMP = "");


    virtual inline void set_A_Runtime_Monitor_Name_FOR_VIEWING_As_Dot_Graph()
    {
        set_A_Runtime_Monitor_Name_FOR_VIEWING_As_Dot_Graph(YRI_DB_RUNTIME_VERIF_Utils::EMPTY_STRING,
                                                            true);
    }


    virtual void set_A_Runtime_Monitor_Name_FOR_VIEWING_As_Dot_Graph(QString    RUNTIME_MONITOR_name_TO_PRINT_DOT,
                                                                     bool       Clear__ON__Empty_NAME = false);


    void set_UPPER_widgets_elements_visibility();


    void set_CURRENT_TABWIDGET_ACTION_visible(bool a_value);


    virtual void filter_All_RUNTIME_monitor__ERROR__SQL__EVENTS();


    virtual void UN__filter_All_RUNTIME_monitor__ERROR__SQL__EVENTS();


    void handle_checkBox_ALL_STATE_SAFETY_PROPERTIES_State_CHANGED(int aState);


    int GET_QTABLEWIDGET_CURRENT_ROW_TO_Select(int current_index);


    virtual inline void handle_combobox_CHANGE_RUNTIME_MONITOR_NAME(const QString &)
    {
        set_CURRENT_TABWIDGET_ACTION_visible(false);
    }


    void handle_current_tab_changed(int current_index);


	static void SET__foregroundcolor__ON__accepting_state(uint 			row_number,
														  QTableWidget 	*a_table_widget,
														  QColor        a_color_to_SET = Qt::green);


    virtual inline void YRI_on_progress_bar__VIEW_current_RUNTIME_MONITOR()
    {
        YRI_DB_RUNTIME_VERIF_ProgressBar(this)(this,
                                              &YRIDBRUNTIMEVERIF_MainWindow::VIEW_current_RUNTIME_MONITOR);
    }


	virtual void *VIEW_current_RUNTIME_MONITOR();


    virtual void setLast_SelectedRow_Row_ID(const QModelIndex &a_model_CELL_index);


	virtual void get_console_Debugging_LOG_Raw_PRINT_OUT_TexTableString(QTableWidget  &current_QTable_Widget_Item,
                                                                        QString       &texTable_IN_OUT,
                                                                        int           row_MAX_TO_GO_export = -1);


	virtual void get_PRINT_OUT_TexTableString(QTableWidget  &current_QTable_Widget_Item,
                                              QString       &texTable_IN_OUT,
                                              int           row_MAX_TO_GO_export = -1);



    virtual inline void yri_PRINT_console_debugging_Log_excerpt_till_selected_LOGGING_string_ID()
    {
        YRI_DB_RUNTIME_VERIF_ProgressBar(this)(this,
                                              &YRIDBRUNTIMEVERIF_MainWindow::PRINT_console_debugging_Log_excerpt_till_selected_LOGGING_string_ID);
    }


    virtual inline void yri_PRINT_with_PROGRESS_BAR_ON__event_log_excerpt_till_selected_SQL_event()
    {
        YRI_DB_RUNTIME_VERIF_ProgressBar(this)(this,
                                              &YRIDBRUNTIMEVERIF_MainWindow::PRINT_event_log_excerpt_till_selected_SQL_event);
    }


    virtual bool PRINT_console_debugging_Log_excerpt_till_selected_LOGGING_string_ID();

    virtual bool PRINT_event_log_excerpt_till_selected_SQL_event();


    virtual void yri_PRINT_with_PROGRESS_BAR_ON__console_debugging_Log_excerpt(int a_row_FOR_pdf_printing_max = -1);

    virtual void yri_PRINT_with_PROGRESS_BAR_ON__event_log_excerpt(int a_row_FOR_pdf_printing_max = -1);


    virtual inline void *PRINT_console_debugging_Log_excerpt__POINTER_PARAMETER(int *a_row_FOR_pdf_printing_max)
    {
        (0 != a_row_FOR_pdf_printing_max) ?
                PRINT_console_debugging_Log_excerpt(*a_row_FOR_pdf_printing_max) :
                PRINT_console_debugging_Log_excerpt();
    }

    virtual inline void *PRINT_event_log_excerpt__POINTER_PARAMETER(int *a_row_FOR_pdf_printing_max)
    {
        (0 != a_row_FOR_pdf_printing_max) ?
                PRINT_event_log_excerpt(*a_row_FOR_pdf_printing_max) :
                PRINT_event_log_excerpt();
    }


    virtual bool PRINT_console_debugging_Log_excerpt(int a_row_FOR_pdf_printing_max = -1);

    virtual bool PRINT_event_log_excerpt(int a_row_FOR_pdf_printing_max = -1);



	virtual void ON_Configfuration_panel_window_trigerred();


	virtual bool ON_action_export_as_CSV_till_selected_console_debugging_LINE();


    virtual bool ON_action_export_as_CSV_till_selected_SQL_event();


	virtual void ON_action_set_current_selected_SQL_event_as_filter_and_search();


	virtual void SOFT_Reset_selected();


	virtual void ON_BUTON_Reset_pressed(bool soft = false);


    virtual void ON_BUTON_Filter_pressed();


    //for combobox "comboBox_global_filtering"
    virtual void RESET_comboBox_SQL_event_filtering();


    virtual void RESET_comboBox_SQL_event_filtering(const QString &a_SQL_event_item);


    //for combobox "comboBox_global_filtering"
    virtual inline void RESET_comboBox_global_filtering()
    {
        comboBox_global_filtering->setCurrentIndex(0);
    }


    virtual inline void RESET_comboBox_global_filtering(const QString &a_SQL_event_item)
    {
        RESET_comboBox_global_filtering();
    }


    //for combobox "comboBox_SQL_event_filtering"
	virtual void ON_QTABLEWIDGET_FILTER_ITEM_selected(const QString &a_SQL_event_item);


    //for QLinedEdit "lineEdit_SQL_event_filtering"
    virtual void ON_QTABLEWIDGET_FILTER_ITEM_Exact_GIVEN(const QString &a_SourceSUT__OR__SQLEvent__Text);


    virtual inline void __Progress_BAR__ACTION_USER_GUIDE_method()
    {
        YRI_DB_RUNTIME_VERIF_ProgressBar(this)(this,
                                              &YRIDBRUNTIMEVERIF_MainWindow::ACTION_USER_GUIDE_method);
    }


	virtual void *ACTION_USER_GUIDE_method();


    virtual inline void about()
    {
    	QMessageBox::information(toolBar_mainWindow_YRI_DB_RUNTIME_VERIF,
    							 "ABOUT THIS SOFTWARE (YRI-DB-RUNTIME-VERIF)",
    							 QObject::tr("DEVELOPED by D.ENG. PR. PROF. Xavier Noundou."));
    }


protected:

    virtual void SET__Sut__VISIBILITY_FOR_logging(QString A_SUT_ID);


    virtual YRIDBRUNTIMEVERIF_TableWidget *Get_CURRENT_QTable_WIDGET();


    virtual void set_runtime_monitor_name_ERROR_LOGGING_visible(bool aVisibleValue);


    virtual inline void set_CURRENT_runtime_monitor_name_Filtered(bool a_bool_value)
    {
        _CURRENT_runtime_monitor_name_Filtered = a_bool_value;
    }


    virtual inline bool is_CURRENT_runtime_monitor_name_Filtered()
    {
        return _CURRENT_runtime_monitor_name_Filtered;
    }


    virtual void SWICTH_EVENT__LOG__to___console__log__EVENT_action(bool console_debugging_log = true);


    virtual void contextMenuEvent(QContextMenuEvent *event);



private:

    void Set__TOOLTIP__for__CONDITIONS(YRIDBRUNTIMEVERIF_Logging_Info &a_logging_info);

    /*
     * Checkbox 'checkBox_ALL_STATE_SAFETY_PROPERTIES_Logging' is visible only
     * when the observed and manipulated runtimme monitor STATE DIAGRAM MEALY
     * MACHINE has more than 2 states.
     *
     * @return: return set visibility of Checkbox 'checkBox_ALL_STATE_SAFETY_PROPERTIES_Logging'.
     */
    bool CHANGE_visibility__Of__checkBox_ALL_STATE_SAFETY_PROPERTIES_Logging();



public:

    static const QString QMESSAGE_BOX_STYLE_SHEET;

    QMap<QString, YRI_DB_RUNTIME_VERIF_Monitor *> user_defined_Runtime_Monitors_NAME__TO__RUNTIME_INSTANCES;


private:


    enum YridbruntimeVerifMainWindowTabPositionsTypes
    {
        SQL_ERROR_EVENT_REPORTING_LOGGING = 0,
        SQL_EVENT_LOGGING = 1,
        CONSOLE_LOGGING_RAW = 2,
        RUNTIME_VERIFICATION_MONITORS = 3
    };


    bool                        _pushButton_lecteur_de_code_barres_Logging_JUST_CLICKED;

    bool                        _pushButton_lecteur_de_code_barres_JUST_CLICKED;

    bool                        _CURRENT_runtime_monitor_name_Filtered;


    uint                        _visible_Console_RAW_row_counter;

    uint                        _visible_ERROR_row_counter;

    uint                        _visible_row_counter;


    QString                     RUNTIME_MONITOR_name_TO_PRINT_DOT;


    const QModelIndex           *_Last_SelectedRow_Row_INDEX_Console_debugging;

    const QModelIndex           *_Last_SelectedRow_Row_INDEX;

    YRI_DB_RUNTIME_VERIF_Monitor	*_current_runtime_monitor_INSTANCE;

    QMap<QString, bool> 		_MAP_SutID__TO__SutLogging;

    QMap<QString, QString> 		_MAP_SutID__TO__SutNAMEQString;

    /**
     * This is used to keep selected row across
     * "tabWidget_SQL_ERROR_EVENT_LOGGING" QTABLEWIDGET.
     */
    QMap<YRIDBRUNTIMEVERIF_TableWidget *, const QModelIndex *>
        _qtabwidget_logging__To__LAST_SELECTED_row_INDEX;

    YRIDBRUNTIMEVERIF_QMap 		_MAP_dbsqlevent__TO__cppfileinfo;

    YRIDBRUNTIMEVERIF_QMap 		_MAP_dbsqlERRORevent__TO__cppfileinfo;
};

#endif /* _YRI_DB_RUNTIME_VERIF_MAIN_WINDOW_HPP_ */
