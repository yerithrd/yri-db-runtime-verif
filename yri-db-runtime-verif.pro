

CONFIG += debug
CONFIG += precompile_header
CONFIG += qt
CONFIG += moc

CONFIG -= import_plugins

QT += widgets
QT += sql
QT += dbus
QT += network

VERSION = 9.0

QMAKE_CXXFLAGS_RELEASE -= -O2
#QMAKE_CXXFLAGS_RELEASE += --coverage
#QMAKE_CXXFLAGS_RELEASE += -Wunused-parameter

QMAKE_CFLAGS_RELEASE -= -O2

DESTDIR = bin

MOC_DIR  = moc

OBJECTS_DIR = obj

PRECOMPILED_HEADER  = src/include/yri-db-runtime-verif-precompiled-header.hpp

DBUS_ADAPTORS += yri.db-runtime.verif.xml


FORMS = ui/yri-db-runtime-verif-setup-window.ui \
	ui/yri-db-runtime-verif-main-window.ui


HEADERS = src/windows/yri-db-runtime-verif-COMMONS-window.hpp \
			src/windows/yri-db-runtime-verif-setup-window.hpp \
			src/client_analysis/YERITH_QVGE_sample___CLIENT___TaintAnalysis.hpp \
			src/utils/yri-db-runtime-verif-LOGGING-INFO.hpp \
			src/widgets/yri-db-runtime-verif-combo-box.hpp \
			src/utils/yri-db-runtime-verif-qmap.hpp \
			src/widgets/yri-db-runtime-verif-progress-bar.hpp \
			src/widgets/yri-db-runtime-verif-push-button.hpp \
			src/widgets/yri-db-runtime-verif-logging-table-widget.hpp \
			src/windows/yri-db-runtime-verif-windows.hpp \
			src/windows/yri-db-runtime-verif-main-window.hpp \
			src/include/yri-db-runtime-verif-MONITOR__Analysis_CHECKING_Testing.hpp \
			src/include/yri-db-runtime-verif-MONITOR.hpp \
			src/include/yri-db-runtime-verif-definition-oo-class-operators.hpp \
			src/include/yri-db-runtime-verif-definition-format-date-time.hpp \
			src/include/yri-db-runtime-verif-software-text-configuration.hpp \
			src/process/yri-db-runtime-verif-PROCESS.hpp \
			src/process/yri-db-runtime-verif-PROCESS-info.hpp \
			src/DBUS/YRI_DBUS_COMMON.hpp \
			src/utils/yri-db-runtime-verif-logger.hpp \
			src/utils/yri-db-runtime-verif-sqltable-model.hpp \
		  src/utils/yri-db-runtime-verif-CONFIG.hpp \
		  src/utils/yri-db-runtime-verif-utils.hpp \
			src/utils/yri-db-runtime-verif-database-table-column.hpp \
		  src/utils/yri-db-runtime-verif-database.hpp 

SOURCES = src/windows/yri-db-runtime-verif-COMMONS-window.cpp \
			src/windows/yri-db-runtime-verif-setup-window.cpp \
			src/client_analysis/YERITH_QVGE_sample___CLIENT___TaintAnalysis.cpp \
			src/utils/yri-db-runtime-verif-LOGGING-INFO.cpp \
			src/widgets/yri-db-runtime-verif-combo-box.cpp \
			src/utils/yri-db-runtime-verif-qmap.cpp \
			src/widgets/yri-db-runtime-verif-progress-bar.cpp \
			src/widgets/yri-db-runtime-verif-push-button.cpp \
			src/widgets/yri-db-runtime-verif-logging-table-widget.cpp \
			src/windows/yri-db-runtime-verif-windows.cpp \
			src/windows/yri-db-runtime-verif-main-window.cpp \
			src/include/yri-db-runtime-verif-MONITOR__Analysis_CHECKING_Testing.cpp \
			src/include/yri-db-runtime-verif-MONITOR.cpp \
			src/yri-db-runtime-verif.cpp \
			src/process/yri-db-runtime-verif-PROCESS.cpp \
			src/process/yri-db-runtime-verif-PROCESS-info.cpp \
			src/DBUS/YRI_DBUS_COMMON.cpp \
			src/utils/yri-db-runtime-verif-logger.cpp \
			src/utils/yri-db-runtime-verif-sqltable-model.cpp \
			src/utils/yri-db-runtime-verif-CONFIG.cpp \
			src/utils/yri-db-runtime-verif-utils.cpp \
			src/utils/yri-db-runtime-verif-database-table-column.cpp \
			src/utils/yri-db-runtime-verif-database.cpp



#YRI-USER-CODE-INCLUDE



RESOURCES    = yri-db-runtime-verif.qrc


#link static libraries
LIBS += -L$$PWD/lib_SD -lyri_sd_runtime_verif


# install
target.path = yri-db-runtime-verif
sources.files = $$SOURCES $$HEADERS *.pro
sources.path = .
INSTALLS += target sources
