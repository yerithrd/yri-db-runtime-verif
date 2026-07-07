#!/bin/bash
# @author: Pr. Prof. Dr. Xavier Noundou
# 

YRI_DB_RUNTIME_VERIF_Xsessionrc___file="${HOME}/my.yri-db-runtime-verif_xsessionrc"

if [ -f ${YRI_DB_RUNTIME_VERIF_Xsessionrc___file} ]; then
	sh ${YRI_DB_RUNTIME_VERIF_Xsessionrc___file}
fi

export QT_SCALE_FACTOR=${EXP_QT_SCALE_FACTOR}

/opt/yri-db-runtime-verif/bin/yri-db-runtime-verif 2> /tmp/YRI_DB_RUNTIME_VERIF.log

export QT_SCALE_FACTOR=
