cmake_minimum_required(VERSION 3.17)
project(Rest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_PREFIX_PATH C:/QT/5.15.2/msvc2015_64)
set(CMAKE_INSTALL_PREFIX C:/Rest2)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS Widgets Core Gui Sql LinguistTools REQUIRED)

set(QM qtbase_ru.qm)

file(GLOB_RECURSE CODE_FILES *.cpp)
file(GLOB_RECURSE HEADERS *.h)

qt5_add_resources (QRC_SOURCES resources.qrc)

add_executable(Rest WIN32
    ${CODE_FILES}
    ${HEADERS}
    ${QRC_SOURCES}
    ${QM}
    )

target_link_libraries(Rest PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Sql)

install(FILES ${QM} DESTINATION bin)

install(TARGETS Rest DESTINATION bin)

install(FILES ${PROJECT_SOURCE_DIR}/databasenew.db DESTINATION bin)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/documentation/ DESTINATION bin/docs/)

install(FILES $<TARGET_FILE:Qt5::Core> DESTINATION bin)
install(FILES $<TARGET_FILE:Qt5::Gui> DESTINATION bin)
install(FILES $<TARGET_FILE:Qt5::Widgets> DESTINATION bin)
install(FILES $<TARGET_FILE:Qt5::Sql> DESTINATION bin)


install(FILES $<TARGET_FILE:Qt5::QSQLiteDriverPlugin> DESTINATION bin/sqldrivers)

install(FILES $<TARGET_FILE:Qt5::QWindowsIntegrationPlugin> DESTINATION bin/platforms)
install(FILES $<TARGET_FILE:Qt5::QWindowsDirect2DIntegrationPlugin> DESTINATION bin/platforms)
