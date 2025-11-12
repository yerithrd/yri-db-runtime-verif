/*
 * yri-db-runtime-verif-logging-table-widget.hpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */

#ifndef _YRI_DB_RUNTIME_VERIF_LOGGING_TABLE_WIDGET_HPP_
#define _YRI_DB_RUNTIME_VERIF_LOGGING_TABLE_WIDGET_HPP_


#include "src/utils/yri-db-runtime-verif-qmap.hpp"

#include <QtWidgets/QTableWidget>


class YRIDBRUNTIMEVERIF_TableWidget : public QTableWidget
{
	Q_OBJECT

public:

	YRIDBRUNTIMEVERIF_TableWidget(QWidget *parent = 0);

	inline virtual ~YRIDBRUNTIMEVERIF_TableWidget()
	{
	}

	void setQStandardItemFlags(Qt::ItemFlags &flags);

	void setQStandardItemFlags(QTableWidgetItem &anItem,
							   Qt::ItemFlags 	&flags);

	inline uint getMaxSize()
	{
		return _mapListIdxToElement_db_ID.getMaxSize();
	}

	void setMaxSize(uint MAX_SIZE);

	virtual void resize_columns_AND_rows_to_contents();


	int ADD_ITEM_3(QString Source_file__line_number);

    int ADD_ITEM_2(QString SQL_QUERY_STRING,
                   QString TIMESTAMP);

	int ADD_ITEM_2(QString Source_file__line_number);

	int ADD_ITEM_1(QString Precondition__Or__POST_CONDITION);


    int ADD_ITEM_Console_Raw_LOGGING(QString TIMESTAMP,
                                     QString STRING_FOR_console_raw);

	int ADD_ITEM(QString TIMESTAMPtem,
				 QString SIGNALItem,
				 QString SOURCEItem,
				 QString TARGETItem,
				 QString changed_OR_modified_database_qty_Item,
				 QString runtime_monitor_QSTRING_ID_Item,
				 bool    LOGGING_INFO_VISIBLE);


public slots:

    virtual inline void Set_CURRENTLY_filtered(bool is_currently_filtered)
    {
        _IS_CURRENTLY_FILTERED = is_currently_filtered;
    }


    virtual inline bool  IS_CURRENTLY_filtered()
    {
        return _IS_CURRENTLY_FILTERED;
    }


    virtual void CLEAR_FILTERING();


    virtual uint FILTER_ITEM(const QString &SIGNALItem_TEXT,
                             bool exact_sql_event_query);


    virtual uint FILTER__SUT_SOURCE__ITEM(const QString &SUT_SOURCEItem_TEXT);


    virtual inline uint FILTER_ITEM(const QString &SIGNALItem_TEXT)
    {
        return FILTER_ITEM(SIGNALItem_TEXT, false);
    }

signals:

    void yerith_signal_QTABLEWidget_CLEAR_FILTERING();


public:

	static const unsigned int TIME_STAMP_COLUMN;

	static const unsigned int SIGNAL_COLUMN;

	static const unsigned int SOURCE_COLUMN;

	static const unsigned int TARGET_COLUMN;

	static const unsigned int changed_or_MODIFIED_database_QTY_COLUMN;


	static const unsigned int qDebug_Console_Raw_Column;

private:

	static const uint MAX_TABLE_WIDGET_ROW_COUNT;


	bool    _IS_CURRENTLY_FILTERED;



	/*
	 * Console Logging Raw Tab elements (Tab number 3).
	 */
	int _curRow__Tab__Console_Logging_Raw;

	QTableWidgetItem *_qDebugConsoleRawItem;

    YRIDBRUNTIMEVERIF_QMap _CONSOLE_RAW_mapListIdxToElement_db_ID;



    int _curRow;

    Qt::ItemFlags _myQStandardItemFlags;

    YRIDBRUNTIMEVERIF_QMap _mapListIdxToElement_db_ID;



	QTableWidgetItem *_TIMESTAMP_Item;

	QTableWidgetItem *_SIGNALItem;

	QTableWidgetItem *_SOURCEItem;

	QTableWidgetItem *_TARGETItem;

	QTableWidgetItem *_changed_OR_modified_database_qty_Item;

	QTableWidgetItem *_runtime_monitor_QSTRING_ID_Item;
};

#endif //_YRI_DB_RUNTIME_VERIF_LOGGING_TABLE_WIDGET_HPP_
