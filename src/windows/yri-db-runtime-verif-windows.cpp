/*
 * yri-db-runtime-verif-windows.cpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */


#include "src/windows/yri-db-runtime-verif-windows.hpp"


YRIDBRUNTIMEVERIF_Windows::~YRIDBRUNTIMEVERIF_Windows()
{
	delete _yrdbruntimeverif_setup_Window;
	delete _yrdbruntimeverif_main_Window;
}


void YRIDBRUNTIMEVERIF_Windows::createAll_YRIDBRUNTIMEVERIF_Windows()
{
	_yrdbruntimeverif_setup_Window = new YRIDBRUNTIMEVERIF_SetupWindow;

	_yrdbruntimeverif_main_Window = new YRIDBRUNTIMEVERIF_MainWindow;

	_yrdbruntimeverif_main_Window->show();
}


void YRIDBRUNTIMEVERIF_Windows::CLOSE_allWindows()
{
	_yrdbruntimeverif_setup_Window->yri_close();
	_yrdbruntimeverif_main_Window->yri_close();
}


