/*
 * yri-db-runtime-verif-qmap.hpp
 *
 *      Author: Pr. Prof. Dr. Xavier Noundou
 */

#ifndef _YRI_DB_RUNTIME_VERIF_QMAP_HPP_
#define _YRI_DB_RUNTIME_VERIF_QMAP_HPP_


#include <cstdlib>

#include <QtCore/QObject>
#include <QtCore/QMap>


class YRIDBRUNTIMEVERIF_QMap : public QMap<uint, QString>
{
public:

	inline YRIDBRUNTIMEVERIF_QMap()
	:QMap<uint, QString>(),
	 _current_IDX(0),
	 _max_elements_SIZE(70000)
	{
	}

	inline virtual ~YRIDBRUNTIMEVERIF_QMap()
	{
	}

	inline virtual uint getMaxSize()
	{
		return _max_elements_SIZE;
	}

	virtual void setMaxSize(uint MAX_SIZE);

	virtual void yri_insert_item(uint 	a_yri_key,
								QString a_yri_value);

private:

	uint _current_IDX = 0;

	uint _max_elements_SIZE;
};

#endif //_YRI_DB_RUNTIME_VERIF_QMAP_HPP_
