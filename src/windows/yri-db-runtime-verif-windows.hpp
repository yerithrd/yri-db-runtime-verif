/*
 * yri-db-runtime-verif-windows.hpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */

#ifndef _YRI_DB_RUNTIME_VERIF_WINDOWS_HPP_
#define _YRI_DB_RUNTIME_VERIF_WINDOWS_HPP_

#include <QtCore/QObject>


#include "src/windows/yri-db-runtime-verif-setup-window.hpp"
#include "src/windows/yri-db-runtime-verif-main-window.hpp"


class QString;
class QDesktopWidget;


class YRIDBRUNTIMEVERIF_Windows : public QObject
{
	Q_OBJECT

public:

	inline YRIDBRUNTIMEVERIF_Windows(QDesktopWidget *desktopWidget)
	:_yrdbruntimeverif_setup_Window(0),
	 _yrdbruntimeverif_main_Window(0),
	 _desktopWidget(desktopWidget)
	{
	}

	virtual ~YRIDBRUNTIMEVERIF_Windows();

	virtual void createAll_YRIDBRUNTIMEVERIF_Windows();

	virtual void CLOSE_allWindows();


    YRIDBRUNTIMEVERIF_SetupWindow *_yrdbruntimeverif_setup_Window;

    YRIDBRUNTIMEVERIF_MainWindow *_yrdbruntimeverif_main_Window;

private:

	inline YRIDBRUNTIMEVERIF_Windows()
	:_yrdbruntimeverif_setup_Window(0),
	 _yrdbruntimeverif_main_Window(0),
	 _desktopWidget(0)
	{
	}


    //QPoint *_currentPosition;

    QDesktopWidget *_desktopWidget;
};

#endif /* _YRI_DB_RUNTIME_VERIF_WINDOWS_HPP_ */
