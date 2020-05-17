include_directories(${EXTERNAL}/headers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(SimpleClient "SimpleClient.cpp")

file(COPY
    C:/Users/Benjamin/Source/Repos/SimpleNetworkExceptions/SimpleNetworkExceptions/SimpleNetworkExceptions.h
    DESTINATION ${EXTERNAL}/headers)

file(COPY
    C:/Users/Benjamin/Source/Repos/SimpleLogger/SimpleLogger/SimpleLogger.h
    DESTINATION ${EXTERNAL}/headers)