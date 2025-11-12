#!/bin/bash
#@AUTEUR: Pr. Prof. Dr. Xavier Noundou

# SHOWS THIS Makefile FILE COMMAND STRING IN THE
# CONSOLE AS THEY ARE EXECUTED.
set -x

# -------------------------------------------------------------- #
YRI_DB_RUNTIME_VERIF_deb_folder=yri-db-runtime-verif
cp yri.db-runtime.verif.conf 		${YRI_DB_RUNTIME_VERIF_deb_folder}/etc/dbus-1/system.d/yri.db-runtime.verif.conf
cp yri-db-runtime-verif.service 	${YRI_DB_RUNTIME_VERIF_deb_folder}/lib/systemd/system/yri-db-runtime-verif.service
cp yri.db-runtime.verif.xml 			${YRI_DB_RUNTIME_VERIF_deb_folder}/usr/share/dbus-1/interfaces/yri.db-runtime.verif.xml
cp yri.db-runtime.verif.service 	${YRI_DB_RUNTIME_VERIF_deb_folder}/usr/share/dbus-1/system-services/yri.db-runtime.verif.service
# -------------------------------------------------------------- #


#qdbusxml2cpp -a src/YRIruntimeverification_adaptor yri.db-runtime.verif.xml 


YRI_ERRORS_LOG_FILE="yri_errors.log"


mkdir -p ${COMPILER_GENERATED_OUTPUT_FOLDER_FULL_PATH}


cp ${COMPILER_GENERATED_OUTPUT_FOLDER_FULL_PATH}/*.hpp src

cp ${COMPILER_GENERATED_OUTPUT_FOLDER_FULL_PATH}/*.cpp src


mkdir bin

clear && qmake -o Makefile yri-db-runtime-verif.pro

make clean

OUT_CMD_TIME=$(time make -j4 > /dev/null 2> "${YRI_ERRORS_LOG_FILE}")

val=$(cat "${YRI_ERRORS_LOG_FILE}" | grep -w "*** No rule to make target\|error\|ERROR\|Error" | wc -l)

if [ ${val} -eq 0 ]; then
	#rm -f "${YRI_ERRORS_LOG_FILE}" 
	echo "[success compilation]"
	
	rm -f verif_adaptor.h
	rm -f verif_adaptor.cpp

else
	echo "[compilation avec des erreurs (${val})]"
fi


echo ${OUT_CMD_TIME}

