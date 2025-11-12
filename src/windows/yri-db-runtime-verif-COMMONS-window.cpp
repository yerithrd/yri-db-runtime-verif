/*
 * yri-db-runtime-verif-COMMONS-window.cpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */


#include "yri-db-runtime-verif-COMMONS-window.hpp"


#include "src/utils/yri-db-runtime-verif-CONFIG.hpp"

#include "src/windows/yri-db-runtime-verif-windows.hpp"



void YRIDBRUNTIMEVERIF_CommonsWindow::ACTION_EXIT_method()
{


    YRIDBRUNTIMEVERIF_Windows *ALL_WINDOWS_INSTANCE =
        YRI_DB_RUNTIME_VERIF_Config::GET_ALL_WINDOWS_instance();

    if (0 != ALL_WINDOWS_INSTANCE)
    {
    	ALL_WINDOWS_INSTANCE->CLOSE_allWindows();
    }

	close();
}
