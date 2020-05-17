include_directories (${CMAKE_SOURCE_DIR}/src)
include_directories (${EXTERNAL}/headers)

add_executable(ConsoleClient "consoleclient.cpp")
target_link_libraries (ConsoleClient SimpleClient)