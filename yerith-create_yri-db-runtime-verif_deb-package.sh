#!/bin/bash
#email: YERITH.xavier@gmail.com
#author: Pr. Prof. Dr. Xavier Noundou (YERITH R&D)!


rm -f yri-db-runtime-verif.deb


cp YRI-DB-RUNTIME-VERIF-GUI-ELEMENTS-SETUP/40yri-db-runtime-verif_xsessionrc \
	yri-db-runtime-verif/etc/X11/Xsession.d


cp YRI-DB-RUNTIME-VERIF-GUI-ELEMENTS-SETUP/yri-db-runtime-verif.desktop \
	yri-db-runtime-verif/usr/share/applications


cp YRI-DB-RUNTIME-VERIF-GUI-ELEMENTS-SETUP/LOGO-icon.png \
	yri-db-runtime-verif/usr/share/pixmaps


cp YRI-DB-RUNTIME-VERIF-GUI-ELEMENTS-SETUP/yri-db-runtime-verif-database-connection.properties \
	yri-db-runtime-verif/opt/yri-db-runtime-verif


cp YRI-DB-RUNTIME-VERIF-GUI-ELEMENTS-SETUP/yri-db-runtime-verif-BIN.SH \
	yri-db-runtime-verif/opt/yri-db-runtime-verif/bin


cp YRI-DB-RUNTIME-VERIF-GUI-ELEMENTS-SETUP/yri-sd-db-runtime-verif.pdf \
	yri-db-runtime-verif/usr/share/doc/yri-db-runtime-verif


cp YRI-DB-RUNTIME-VERIF-GUI-ELEMENTS-SETUP/YERITH_QVGE.pdf \
	yri-db-runtime-verif/usr/share/doc/yri-db-runtime-verif


mkdir -p yri-db-runtime-verif/opt/yri-db-runtime-verif/bin

cp bin/yri-db-runtime-verif yri-db-runtime-verif/opt/yri-db-runtime-verif/bin

touch yri-db-runtime-verif/opt/yri-db-runtime-verif/yri-db-runtime-verif.log

chmod go+rw yri-db-runtime-verif/opt/yri-db-runtime-verif/yri-db-runtime-verif.log

chmod 755 yri-db-runtime-verif/DEBIAN/postinst

dpkg-deb --build yri-db-runtime-verif


cp yri.db-runtime.verif.xml ${YERITH_ERP_3_0_HOME_FOLDER}/src/dbus/
