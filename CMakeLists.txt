cmake_minimum_required(VERSION 2.6)


set (PROJECT gpp-gui-qt4-pomidorka)
project(${PROJECT})

# Для переменной доступны следующие варианты значений:
# DEBUG | RELEASE | RELWITHDEBINFO | MINSIZEREL
set( CMAKE_BUILD_TYPE DEBUG )

set (HEADERS_NOOBJECT
	./src/setting.h
)

set (HEADERS_OBJECT
	./src/staticview.h
	./src/timer.h
	./src/timerwindow.h
	./src/trayicon.h
)

set (HEADERS
		${HEADERS_OBJECT}
		${HEADERS_NOOBJECT}
)
set (SOURCES
	./src/main.cpp
	./src/staticview.cpp
	./src/timer.cpp
	./src/timerwindow.cpp
	./src/trayicon.cpp
	./src/setting.cpp
)

set (APP_RES
    ./resources/resources.qrc
)


# Возможно, понадобятся еще пакеты QtScript
find_package(Qt4 COMPONENTS QtCore QtGui QtSql REQUIRED)

include (${QT_USE_FILE})

# generate rules for building source files from the resources
QT4_ADD_RESOURCES(APP_RES_C ${APP_RES})

ADD_DEFINITIONS(${QT_DEFINITIONS})

#~ execute_process(COMMAND /bin/bash -c "echo -n `git describe --long`" OUTPUT_VARIABLE GIT_VERSION)
#~ execute_process(COMMAND /bin/bash -c "echo -n `date '+%d %m %G %T'`" OUTPUT_VARIABLE VAR_DATE)
#configure_file(./aut/config.h.in ${PROJECT_SOURCE_DIR}/src/config.h)

qt4_wrap_cpp (MOC_SOURCES ${HEADERS_OBJECT}) #создаем таблицу сигналов слотов
add_executable (${PROJECT} ${HEADERS} ${SOURCES} ${MOC_SOURCES} ${APP_RES_C} )
target_link_libraries (${PROJECT} ${QT_LIBRARIES})
