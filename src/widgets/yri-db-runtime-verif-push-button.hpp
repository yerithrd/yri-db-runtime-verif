/*
 * yri-db-runtime-verif-push-button.hpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */

#ifndef _YRI_DB_RUNTIME_VERIF_PUSH_BUTTON_HPP_
#define _YRI_DB_RUNTIME_VERIF_PUSH_BUTTON_HPP_


#include <QtWidgets/QPushButton>


class YRIDBRUNTIMEVERIF_QPushButton : public QPushButton
{
    Q_OBJECT

public:

    inline YRIDBRUNTIMEVERIF_QPushButton(QWidget *w)
    :QPushButton(w)
    {
    }

    virtual inline ~YRIDBRUNTIMEVERIF_QPushButton()
    {
    }

    inline void enable(const QObject *receiver, const char *f)
    {
        QObject::connect(this,
                         SIGNAL(clicked()),
                         receiver,
                         f,
                         Qt::UniqueConnection);
    }

    inline void disable(const QObject *receiver)
    {
        QObject::disconnect(this,
                            SIGNAL(clicked()),
                            receiver,
                            0);
    }
};


#endif /* _YRI_DB_RUNTIME_VERIF_PUSH_BUTTON_HPP_ */
