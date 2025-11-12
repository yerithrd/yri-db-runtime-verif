/*
 * yri-db-runtime-verif-COMMONS-window.hpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */

#ifndef _YRI_DB_RUNTIME_VERIF_COMMONS_WINDOW_HPP_
#define _YRI_DB_RUNTIME_VERIF_COMMONS_WINDOW_HPP_


#include "src/utils/yri-db-runtime-verif-LOGGING-INFO.hpp"


#include <QtWidgets/QMainWindow>

#include <QtCore/QObject>


class YRIDBRUNTIMEVERIF_CommonsWindow : public QMainWindow
{
	Q_OBJECT

public:

	inline YRIDBRUNTIMEVERIF_CommonsWindow()
	{
	}

    inline virtual ~YRIDBRUNTIMEVERIF_CommonsWindow()
    {
    }

    virtual QToolBar &get_tool_bar() = 0;


signals:

    void SIGNAL_INCREMENT_PROGRESS_BAR(int countSuccess);


public slots:

	inline virtual void yri_show()
	{
		setVisible(true);
	}

	inline virtual void yri_close()
	{
		close();
	}


protected slots:

	virtual void ACTION_EXIT_method();

    inline virtual void help()
    {
    }
};

#endif /* _YRI_DB_RUNTIME_VERIF_COMMONS_WINDOW_HPP_ */
