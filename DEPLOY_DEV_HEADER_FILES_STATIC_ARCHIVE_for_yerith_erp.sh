#!/bin/bash
# @AUTHOR: Pr. Prof. Dr. Xavier Noundou
# @EMAIL: YERITH.xavier@gmail.com


#yri_compile_LIB_FOR_YERITH_ERP_3_0_j4.sh

#cp lib/libyri-db-runtime-verif_FOR_YERITH_ERP.a "${YERITH_ERP_3_0_HOME_FOLDER}/lib"
#echo "cp lib/libyri-db-runtime-verif_FOR_YERITH_ERP.a '${YERITH_ERP_3_0_HOME_FOLDER}/lib'"


MYFILE=YRI_DB_RUNTIME_VERIF_HEADERS_FOR_yerith_erp.TXT

echo "processing files within '${MYFILE}'"

echo "cp yri.db-runtime.verif.xml ${HOME}/yerith-erp-9-0/src/dbus"
cp yri.db-runtime.verif.xml ${HOME}/yerith-erp-9-0/src/dbus 

n=1
while read LINE; do
	CUR_YRI_DEV_FILE=`find src -name "${LINE}"`

	FILE_TO_REPLACE="${YERITH_ERP_3_0_HOME_FOLDER}/src/${LINE}"

	echo "cp "${CUR_YRI_DEV_FILE}" "${FILE_TO_REPLACE}""

	cp "${CUR_YRI_DEV_FILE}" "${FILE_TO_REPLACE}"

	n=$((n+1))
done < "$MYFILE"


