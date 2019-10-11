cmake_minimum_required(VERSION 3.1)

project(imgview LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

add_executable(${PROJECT_NAME} "main.cpp"
    "qml.qrc"
    "tagprovider.cpp"
    "PlistCpp/src/pugixml.cpp" "PlistCpp/src/PList.cpp" "PlistCpp/src/PlistDate.cpp")
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "PlistCpp/include")
target_include_directories(${PROJECT_NAME} PRIVATE "PlistCpp/src")
