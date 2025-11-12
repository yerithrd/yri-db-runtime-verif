/*
 * yri-db-runtime-verif-logging-table-widget.cpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */

#include "yri-db-runtime-verif-logging-table-widget.hpp"


#include "src/utils/yri-db-runtime-verif-utils.hpp"


const uint YRIDBRUNTIMEVERIF_TableWidget::MAX_TABLE_WIDGET_ROW_COUNT = 0;


const unsigned int YRIDBRUNTIMEVERIF_TableWidget::TIME_STAMP_COLUMN(0);

const unsigned int YRIDBRUNTIMEVERIF_TableWidget::SIGNAL_COLUMN(1);

const unsigned int YRIDBRUNTIMEVERIF_TableWidget::SOURCE_COLUMN(2);

const unsigned int YRIDBRUNTIMEVERIF_TableWidget::TARGET_COLUMN(3);

const unsigned int YRIDBRUNTIMEVERIF_TableWidget::changed_or_MODIFIED_database_QTY_COLUMN(4);



const unsigned int YRIDBRUNTIMEVERIF_TableWidget::qDebug_Console_Raw_Column(1);




YRIDBRUNTIMEVERIF_TableWidget::YRIDBRUNTIMEVERIF_TableWidget(QWidget *parent /* = 0 */)
:QTableWidget(parent),
 _IS_CURRENTLY_FILTERED(false),
 _qDebugConsoleRawItem(0),
 _TIMESTAMP_Item(0),
 _SIGNALItem(0),
 _SOURCEItem(0),
 _TARGETItem(0),
 _changed_OR_modified_database_qty_Item(0),
 _runtime_monitor_QSTRING_ID_Item(0)
{

    _curRow__Tab__Console_Logging_Raw = 0;

    _curRow = 0;


    _myQStandardItemFlags = Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;


    setQStandardItemFlags(_myQStandardItemFlags);


    setFrameShadow(QFrame::Plain);

    setSelectionBehavior(QAbstractItemView::SelectRows);

    setSelectionMode(QAbstractItemView::SingleSelection);

    setEditTriggers(QAbstractItemView::DoubleClicked);


    setMaxSize(MAX_TABLE_WIDGET_ROW_COUNT);


    resize_columns_AND_rows_to_contents();
}


void YRIDBRUNTIMEVERIF_TableWidget::setQStandardItemFlags(Qt::ItemFlags &flags)
{
    QTableWidgetItem *curItem = 0;

    for (int i = 0; i < rowCount(); ++i)
    {
        for (int j = 0; j < columnCount(); ++j)
        {
            curItem = item(i, j);

            if (0 != curItem)
            {
            	curItem->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
                curItem->setFlags(flags);
            }
        }
    }
}


void YRIDBRUNTIMEVERIF_TableWidget::setQStandardItemFlags(QTableWidgetItem &anItem,
						   	   	   	   	   	   	   	      Qt::ItemFlags    &flags)
{
	anItem.setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	anItem.setFlags(flags);
}


void YRIDBRUNTIMEVERIF_TableWidget::setMaxSize(uint MAX_SIZE)
{
	setRowCount(MAX_SIZE);

	//_mapListIdxToElement_db_ID.setMaxSize(MAX_SIZE);
}


void YRIDBRUNTIMEVERIF_TableWidget::resize_columns_AND_rows_to_contents()
{
    if (columnCount() > 1)
    {
        resizeColumnsToContents();
    }

    resizeRowsToContents();
}


/*
 * THIS METHOS IS meant to be only called by
 * class 'YRIDBRUNTIMEVERIF_MainWindow.tableWidget_LOGGING_4'.
 */
int YRIDBRUNTIMEVERIF_TableWidget::ADD_ITEM_3(QString Source_file__line_number)
{
	static bool first_time_call = true;

	if (first_time_call)
	{
		setMaxSize(1);

		first_time_call = false;
	}

	_curRow = 0;

    setRowCount(1);

    QList<QString> source_file__line_number_LIST = Source_file__line_number.split(':');

    QString A_PREVIOUS_STATE = source_file__line_number_LIST.at(0);

    QString AN_ACCEPTING_STATE = source_file__line_number_LIST.at(1);

    QString AN_ACCEPTING_STATE_is_error_state_VALUE = source_file__line_number_LIST.at(2);


    _TIMESTAMP_Item = new QTableWidgetItem(A_PREVIOUS_STATE);
    _SIGNALItem = new QTableWidgetItem(AN_ACCEPTING_STATE);
    _SOURCEItem = new QTableWidgetItem(AN_ACCEPTING_STATE_is_error_state_VALUE);

    _mapListIdxToElement_db_ID.yri_insert_item(_curRow, Source_file__line_number);

    unsigned idx = 0;

    //Each call to setItem triggers a call to YerothPointDeVenteWindow::handleQteChange
    setItem(_curRow, idx++, _TIMESTAMP_Item);
    setItem(_curRow, idx++, _SIGNALItem);
    setItem(_curRow, idx++, _SOURCEItem);

    setQStandardItemFlags(*_TIMESTAMP_Item, _myQStandardItemFlags);
    setQStandardItemFlags(*_SIGNALItem, _myQStandardItemFlags);
    setQStandardItemFlags(*_SOURCEItem, _myQStandardItemFlags);

    selectRow(_curRow);

    resize_columns_AND_rows_to_contents();

    return _curRow;
}


int YRIDBRUNTIMEVERIF_TableWidget::ADD_ITEM_2(QString SQL_QUERY_STRING,
                                             QString TIMESTAMP)
{
	static bool first_time_call = true;

	if (first_time_call)
	{
		setMaxSize(1);

		first_time_call = false;
	}

	_curRow = 0;

    setRowCount(1);


    _TIMESTAMP_Item = new QTableWidgetItem(TIMESTAMP);
    _SIGNALItem = new QTableWidgetItem(SQL_QUERY_STRING);


    _mapListIdxToElement_db_ID.yri_insert_item(_curRow, SQL_QUERY_STRING);

    unsigned idx = 0;

    //Each call to setItem triggers a call to YerothPointDeVenteWindow::handleQteChange
    setItem(_curRow, idx++, _TIMESTAMP_Item);
    setItem(_curRow, idx++, _SIGNALItem);

    setQStandardItemFlags(*_TIMESTAMP_Item, _myQStandardItemFlags);
    setQStandardItemFlags(*_SIGNALItem, _myQStandardItemFlags);

    selectRow(_curRow);


    resize_columns_AND_rows_to_contents();


    return _curRow;
}


/*
 * THIS METHOS IS meant to be only called by
 * class 'YRIDBRUNTIMEVERIF_MainWindow.tableWidget_LOGGING_2'.
 */
int YRIDBRUNTIMEVERIF_TableWidget::ADD_ITEM_2(QString Source_file__line_number)
{
	static bool first_time_call = true;

	if (first_time_call)
	{
		setMaxSize(1);

		first_time_call = false;
	}

	_curRow = 0;

    setRowCount(1);

    QList<QString> source_file__line_number_LIST = Source_file__line_number.split(':');

    QString Source_file = source_file__line_number_LIST.at(0);

    QString line_number = source_file__line_number_LIST.at(1);


    _TIMESTAMP_Item = new QTableWidgetItem(Source_file);
    _SIGNALItem = new QTableWidgetItem(line_number);

    _mapListIdxToElement_db_ID.yri_insert_item(_curRow, Source_file__line_number);

    unsigned idx = 0;

    //Each call to setItem triggers a call to YerothPointDeVenteWindow::handleQteChange
    setItem(_curRow, idx++, _TIMESTAMP_Item);
    setItem(_curRow, idx++, _SIGNALItem);

    setQStandardItemFlags(*_TIMESTAMP_Item, _myQStandardItemFlags);
    setQStandardItemFlags(*_SIGNALItem, _myQStandardItemFlags);

    selectRow(_curRow);


    resize_columns_AND_rows_to_contents();


    return _curRow;
}


int YRIDBRUNTIMEVERIF_TableWidget::ADD_ITEM_1(QString Precondition__Or__POST_CONDITION)
{
    static bool first_time_call = true;

    if (first_time_call)
    {
        setMaxSize(1);

        first_time_call = false;
    }

    _curRow = 0;

    setRowCount(1);

    _TIMESTAMP_Item = new QTableWidgetItem(Precondition__Or__POST_CONDITION);

    _mapListIdxToElement_db_ID.yri_insert_item(_curRow, Precondition__Or__POST_CONDITION);

    unsigned idx = 0;

    //Each call to setItem triggers a call to YerothPointDeVenteWindow::handleQteChange
    setItem(_curRow, idx++, _TIMESTAMP_Item);

    setQStandardItemFlags(*_TIMESTAMP_Item, _myQStandardItemFlags);

    selectRow(_curRow);

    resize_columns_AND_rows_to_contents();

    return _curRow;
}


int YRIDBRUNTIMEVERIF_TableWidget::ADD_ITEM_Console_Raw_LOGGING(QString TIMESTAMP,
                                                                QString STRING_FOR_console_raw)
{
//    QDEBUG_STRINGS_OUTPUT_2("YRIDBRUNTIMEVERIF_TableWidget::ADD_ITEM_Console_Raw_LOGGING",
//                             QString("%1:%2:%3")
//                                .arg(QString::number(getMaxSize()),
//                                     TIMESTAMP,
//                                     STRING_FOR_console_raw));

    setRowCount(_curRow__Tab__Console_Logging_Raw + 1);


    _TIMESTAMP_Item = new QTableWidgetItem(TIMESTAMP);
    _TIMESTAMP_Item->setTextAlignment(Qt::AlignLeft);

    _qDebugConsoleRawItem = new QTableWidgetItem(STRING_FOR_console_raw);
    _qDebugConsoleRawItem->setTextAlignment(Qt::AlignLeft);


    _CONSOLE_RAW_mapListIdxToElement_db_ID.yri_insert_item(_curRow__Tab__Console_Logging_Raw, STRING_FOR_console_raw);


    unsigned idx = 0;


    setItem(_curRow__Tab__Console_Logging_Raw, idx++, _TIMESTAMP_Item);
    setItem(_curRow__Tab__Console_Logging_Raw, idx++, _qDebugConsoleRawItem);


    selectRow(_curRow__Tab__Console_Logging_Raw);


    resize_columns_AND_rows_to_contents();

    int lastCurRow = _curRow__Tab__Console_Logging_Raw;


    if (_curRow__Tab__Console_Logging_Raw <= getMaxSize())
    {
        ++_curRow__Tab__Console_Logging_Raw;
    }
    else
    {
        _curRow__Tab__Console_Logging_Raw = 0;
    }

    return lastCurRow;
}


int YRIDBRUNTIMEVERIF_TableWidget::ADD_ITEM(QString TIMESTAMPtem,
										   QString SIGNALItem,
		   	   	   	   	   	   	   	   	   QString SOURCEItem,
										   QString TARGETItem,
										   QString changed_OR_modified_database_qty_Item,
										   QString runtime_monitor_QSTRING_ID_Item,
										   bool    LOGGING_INFO_VISIBLE)
{
    if (LOGGING_INFO_VISIBLE)
    {
        setRowCount(_curRow + 1);
    }


    TIMESTAMPtem.truncate(50);
    SIGNALItem.truncate(50);
    SOURCEItem.truncate(50);
    TARGETItem.truncate(50);
    changed_OR_modified_database_qty_Item.truncate(50);
    runtime_monitor_QSTRING_ID_Item.truncate(7);


    if (LOGGING_INFO_VISIBLE)
    {
        _TIMESTAMP_Item = new QTableWidgetItem(TIMESTAMPtem);
        _SIGNALItem = new QTableWidgetItem(SIGNALItem);
        _SOURCEItem = new QTableWidgetItem(SOURCEItem);
        _TARGETItem = new QTableWidgetItem(TARGETItem);

        _changed_OR_modified_database_qty_Item =
            new QTableWidgetItem(changed_OR_modified_database_qty_Item);

        _runtime_monitor_QSTRING_ID_Item =
            new QTableWidgetItem(runtime_monitor_QSTRING_ID_Item);
    }


    _mapListIdxToElement_db_ID.yri_insert_item(_curRow, SIGNALItem);


    if (LOGGING_INFO_VISIBLE)
    {
        unsigned idx = 0;


        setItem(_curRow, idx++, _TIMESTAMP_Item);
        setItem(_curRow, idx++, _SIGNALItem);
        setItem(_curRow, idx++, _SOURCEItem);
        setItem(_curRow, idx++, _TARGETItem);
        setItem(_curRow, idx++, _changed_OR_modified_database_qty_Item);
        setItem(_curRow, idx++, _runtime_monitor_QSTRING_ID_Item);


        setQStandardItemFlags(*_TIMESTAMP_Item, _myQStandardItemFlags);
        setQStandardItemFlags(*_SIGNALItem, _myQStandardItemFlags);
        setQStandardItemFlags(*_SOURCEItem, _myQStandardItemFlags);
        setQStandardItemFlags(*_TARGETItem, _myQStandardItemFlags);
        setQStandardItemFlags(*_changed_OR_modified_database_qty_Item, _myQStandardItemFlags);
        setQStandardItemFlags(*_runtime_monitor_QSTRING_ID_Item, _myQStandardItemFlags);


        selectRow(_curRow);

        resize_columns_AND_rows_to_contents();


        int lastCurRow = _curRow;

        if (_curRow <= getMaxSize())
        {
            ++_curRow;
        }
        else
        {
            _curRow = 0;
        }

        return lastCurRow;
    }

    return -1;
}


void YRIDBRUNTIMEVERIF_TableWidget::CLEAR_FILTERING()
{
    int row_size = rowCount();


    static const uint SIGNALItem_COLUMN = 1;

    static const uint SUT_SOURCEItem_COLUMN = 2;


    QTableWidgetItem *current_signal_item = 0;

    QTableWidgetItem *current_signal_item_two = 0;


    for (int row = 0; row < row_size; ++row)
    {
        current_signal_item = item(row, SIGNALItem_COLUMN);

        current_signal_item_two = item(row, SUT_SOURCEItem_COLUMN);

        if (0 != current_signal_item)
        {
            current_signal_item->setBackground(Qt::black);
        }

        if (0 != current_signal_item_two)
        {
            current_signal_item_two->setBackground(Qt::black);
        }
    }


    Set_CURRENTLY_filtered(false);


    emit yerith_signal_QTABLEWidget_CLEAR_FILTERING();


    resize_columns_AND_rows_to_contents();
}


uint YRIDBRUNTIMEVERIF_TableWidget::FILTER_ITEM(const QString &SIGNALItem_TEXT,
                                               bool exact_sql_event_query)
{
    if (SIGNALItem_TEXT.isEmpty())
    {
        return 0;
    }


    CLEAR_FILTERING();


    uint MATCHED_search = 0;

    QString searched_SIGNALItem_TEXT = SIGNALItem_TEXT;

    if (!exact_sql_event_query)
    {
        searched_SIGNALItem_TEXT =
            QString("'%1")
                .arg(SIGNALItem_TEXT);
    }


    int row_size = rowCount();


    static const uint SIGNALItem_COLUMN = 1;


    QTableWidgetItem *current_signal_item = 0;

    QString current_signal_item_TEXT;


    for (uint row = 0; row < row_size; ++row)
    {
        current_signal_item = item(row, SIGNALItem_COLUMN);

        if (0 != current_signal_item)
        {
            current_signal_item_TEXT = current_signal_item->text();


            if (!exact_sql_event_query)
            {
                if (!current_signal_item_TEXT.startsWith(searched_SIGNALItem_TEXT))
                {
                    current_signal_item->setBackground(Qt::black);
                }
                else
                {
                    ++MATCHED_search;

                    current_signal_item->setBackground(Qt::darkMagenta);
                }
            }
            else
            {
                if (!YRI_DB_RUNTIME_VERIF_Utils::isEqualsCaseInsensitive(current_signal_item_TEXT,
                                                                        searched_SIGNALItem_TEXT))
                {
                    current_signal_item->setBackground(Qt::black);
                }
                else
                {
                    ++MATCHED_search;

                    current_signal_item->setBackground(Qt::darkMagenta);
                }
            }
        }

    }//for


    resize_columns_AND_rows_to_contents();


    if (MATCHED_search > 0)
    {
        Set_CURRENTLY_filtered(true);
    }
    else
    {
        Set_CURRENTLY_filtered(false);
    }


    return MATCHED_search;
}


uint YRIDBRUNTIMEVERIF_TableWidget::
        FILTER__SUT_SOURCE__ITEM(const QString &SUT_SOURCEItem_TEXT)
{
    if (SUT_SOURCEItem_TEXT.isEmpty())
    {
        return 0;
    }


    CLEAR_FILTERING();


    uint MATCHED_search = 0;

    QString searched_SUT_SOURCEItem_TEXT = SUT_SOURCEItem_TEXT;


    int row_size = rowCount();


    static const uint SUT_SOURCEItem_COLUMN = 2;


    QTableWidgetItem *current_SUT_source_item = 0;

    QString current_SUT_source_item_TEXT;


    for (int row = 0; row < row_size; ++row)
    {
        current_SUT_source_item = item(row, SUT_SOURCEItem_COLUMN);

        if (0 != current_SUT_source_item)
        {
            current_SUT_source_item_TEXT = current_SUT_source_item->text();

            if (!YRI_DB_RUNTIME_VERIF_Utils::isEqualsCaseInsensitive(current_SUT_source_item_TEXT,
                                                                    searched_SUT_SOURCEItem_TEXT))
            {
                current_SUT_source_item->setBackground(Qt::black);
            }
            else
            {
                ++MATCHED_search;

                current_SUT_source_item->setBackground(Qt::darkMagenta);
            }
        }

    }//for


    resize_columns_AND_rows_to_contents();


    if (MATCHED_search > 0)
    {
        Set_CURRENTLY_filtered(true);
    }
    else
    {
        Set_CURRENTLY_filtered(false);
    }


    return MATCHED_search;
}

