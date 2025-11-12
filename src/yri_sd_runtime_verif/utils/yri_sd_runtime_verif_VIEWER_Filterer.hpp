/*
 * yri_sd_runtime_verif_VIEWER_Filterer.hpp
 *
 */

#ifndef ___YRI_DB_Runtime_Verif_Viewer_FILTERER___
#define ___YRI_DB_Runtime_Verif_Viewer_FILTERER___


#include "YRI_CPP_UTILS.hpp"


#include <QtCore/QDebug>


class YRI_DB_Runtime_Verif_Viewer_FILTERER
{

public:

    inline YRI_DB_Runtime_Verif_Viewer_FILTERER()
    :_FILTER_view_All_STMTS___(true),
     _FILTER__View___INsert_STMTS___(false),
     _FILTER__View___SElect_STMTS___(false),
     _FILTER__View___UPdate_STMTS___(false),
     _FILTER__View___DElete_STMTS___(false)
    {
    }

    inline virtual ~YRI_DB_Runtime_Verif_Viewer_FILTERER()
    {
    }


    /**
     * View this only if now printed upfront
     * in ALL statements view 'qDebug()'.
     */
    void FILTER___view__only____INSERT___CMDs(YRI_CPP_UTILS::SQL_CONSTANT_IDENTIFIER    yri_cur_SQL_command,
                                              QString                                   yri_sql_table_name,
                                              uint                                      yri_sql_record_qty_MODIFIED,
                                              QString                                   yri_CPP_FILE_NAME,
                                              QString                                   yri_cpp_line_number);


    /**
     * View this only if now printed upfront
     * in ALL statements view 'qDebug()'.
     */
    void FILTER___view__only____SELECT___CMDs(YRI_CPP_UTILS::SQL_CONSTANT_IDENTIFIER    yri_cur_SQL_command,
                                              QString                                   yri_sql_table_name,
                                              uint                                      yri_sql_record_qty_MODIFIED,
                                              QString                                   yri_CPP_FILE_NAME,
                                              QString                                   yri_cpp_line_number);


    /**
     * View this only if now printed upfront
     * in ALL statements view 'qDebug()'.
     */
    void FILTER___view__only____UPDATE___CMDs(YRI_CPP_UTILS::SQL_CONSTANT_IDENTIFIER    yri_cur_SQL_command,
                                              QString                                   yri_sql_table_name,
                                              uint                                      yri_sql_record_qty_MODIFIED,
                                              QString                                   yri_CPP_FILE_NAME,
                                              QString                                   yri_cpp_line_number);


    /**
     * View this only if now printed upfront
     * in ALL statements view 'qDebug()'.
     */
    void FILTER___view__only____DELETE___CMDs(YRI_CPP_UTILS::SQL_CONSTANT_IDENTIFIER    yri_cur_SQL_command,
                                              QString                                   yri_sql_table_name,
                                              uint                                      yri_sql_record_qty_MODIFIED,
                                              QString                                   yri_CPP_FILE_NAME,
                                              QString                                   yri_cpp_line_number);



    virtual void VIEW_only_STATEMENT(enum YRI_CPP_UTILS::SQL_CONSTANT_IDENTIFIER A_SQL_Event_Stmt);


    virtual void filter_View_All_stmts();


    virtual inline void filter_View___INSERT_stmts(bool __yes_or_NO___)
    {
        _FILTER__View___INsert_STMTS___ = __yes_or_NO___;
    }

    virtual inline void filter_View___SELECT_stmts(bool __yes_or_NO___)
    {
        _FILTER__View___SElect_STMTS___ = __yes_or_NO___;
    }

    virtual inline void filter_View___UPDATE_stmts(bool __yes_or_NO___)
    {
        _FILTER__View___UPdate_STMTS___ = __yes_or_NO___;
    }

    virtual inline void filter_View___DELETE_stmts(bool __yes_or_NO___)
    {
        _FILTER__View___DElete_STMTS___ = __yes_or_NO___;
    }


    bool _FILTER_view_All_STMTS___;

    bool _FILTER__View___INsert_STMTS___;

    bool _FILTER__View___SElect_STMTS___;

    bool _FILTER__View___UPdate_STMTS___;

    bool _FILTER__View___DElete_STMTS___;

};



#endif /* ___YRI_DB_Runtime_Verif_Viewer_FILTERER___ */
