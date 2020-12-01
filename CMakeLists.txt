cmake_minimum_required(VERSION 3.5)

project(DcsResourcesViewer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(LIBS ${CMAKE_CURRENT_SOURCE_DIR}/libs)
include_directories(${LIBS})



find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(ZLIB REQUIRED)
find_package(libzip REQUIRED)


#----------LUA-----------------
include_directories(${LIBS}/Lua)
file(GLOB LUA_SOURCE
     ${LIBS}/Lua/*.h
    ${LIBS}/Lua/*.hpp
)
source_group("Lua" FILES ${LUA_SOURCE})

#----------LUA BRIDGE------------
include_directories(${LIBS}/LuaBridge)
set (LUABRIDGE_HEADERS
  ${LIBS}/LuaBridge/List.h
  ${LIBS}/LuaBridge/LuaBridge.h
  ${LIBS}/LuaBridge/Map.h
  ${LIBS}/LuaBridge/RefCountedObject.h
  ${LIBS}/LuaBridge/RefCountedPtr.h
  ${LIBS}/LuaBridge/UnorderedMap.h
  ${LIBS}/LuaBridge/Vector.h
  ${LIBS}/LuaBridge/Array.h
)
source_group ("Lua\\LuaBridge" FILES ${LUABRIDGE_HEADERS})

include_directories(${LIBS}/LuaBridge/detail)
set (LUABRIDGE_DETAIL_HEADERS
  ${LIBS}/LuaBridge/detail/CFunctions.h
  ${LIBS}/LuaBridge/detail/ClassInfo.h
  ${LIBS}/LuaBridge/detail/Config.h
  ${LIBS}/LuaBridge/detail/Constructor.h
  ${LIBS}/LuaBridge/detail/dump.h
  ${LIBS}/LuaBridge/detail/FuncTraits.h
  ${LIBS}/LuaBridge/detail/Iterator.h
  ${LIBS}/LuaBridge/detail/LuaException.h
  ${LIBS}/LuaBridge/detail/LuaHelpers.h
  ${LIBS}/LuaBridge/detail/LuaRef.h
  ${LIBS}/LuaBridge/detail/Namespace.h
  ${LIBS}/LuaBridge/detail/Stack.h
  ${LIBS}/LuaBridge/detail/TypeList.h
  ${LIBS}/LuaBridge/detail/TypeTraits.h
  ${LIBS}/LuaBridge/detail/Userdata.h
)
source_group ("Lua\\LuaBridge\\detail" FILES ${LUABRIDGE_DETAIL_HEADERS})
link_directories(${LIBS}/lua)

include_directories(${CMAKE_CURRENT_LIST_DIR}/src)
set(WAREHOUSE_FILES
    src/warehouses/warehouseparser.h
    src/warehouses/warehouseparser.cpp
    src/warehouses/airfieldparser.h
    src/warehouses/airfieldparser.cpp
    src/warehouses/jsondbparser.h
    src/warehouses/jsondbparser.cpp

    )
source_group ("data\\parsers\\warehouses" FILES ${WAREHOUSE_FILES})

set(MISSION_FILES
    src/mission/missionparser.h
    src/mission/missionparser.cpp

    )
source_group ("data\\parsers\\mission" FILES ${MISSION_FILES})

set(DATA_FILES
    src/mizinterface.h
    src/mizinterface.cpp
    src/datamanager.h
    src/datamanager.cpp
    src/LuaConstants.h
    src/airfield.h
    src/airfield.cpp
    src/mission.h
    src/mission.cpp
    src/inventory.h
    src/inventory.cpp
    )
source_group ("data" FILES ${DATA_FILES})

set(UI_FILES
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui
    src/selectionvisitor.h
    src/selectionvisitor.cpp
    )
source_group("ui" FILES ${UI_FILES})

set(UI_MODEL
    src/airfieldtreemodel.h
    src/airfieldtreemodel.cpp
    src/treeitembase.h
    src/treeitembase.cpp
    src/treeitemairfield.h
    src/treeitemairfield.cpp
    src/treeitemfuel.h
    src/treeitemfuel.cpp
    src/treeitemairframe.h
    src/treeitemairframe.cpp
    src/treeitemvisitor.h
    src/inventorymodel.h
    src/inventorymodel.cpp
    src/treeitemequipment.h
    src/treeitemequipment.cpp
    )
source_group("models" FILES ${UI_MODEL})


add_executable(DcsResourcesViewer
    ${UI_FILES}
    ${DATA_FILES}
    ${WAREHOUSE_FILES}
    ${LUA_SOURCE}
    ${LUABRIDGE_HEADERS}
    ${MISSION_FILES}
    ${UI_MODEL}
    resources.qrc
 )

#target_include_directories(DcsResourcesViewer PUBLIC  ${CMAKE_CURRENT_LIST_DIR}/src)
#target_link_directories(DcsResourcesViewer PUBLIC   ${LIBS})
target_link_libraries(DcsResourcesViewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    lua5.3.5-static
    libzip::zip
    ZLIB::ZLIB
     )
