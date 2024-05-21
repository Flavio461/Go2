cmake_minimum_required(VERSION 3.5.0)
project(Go2 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(HEADER_FILES src/utils/user.hpp src/utils/car.hpp src/utils/driver.hpp src/utils/route.hpp src/utils/routeHandler.hpp src/utils/routePath.hpp)
add_executable(Go2 src/main.cpp src/utils/user.cpp src/utils/car.cpp src/utils/driver.cpp src/utils/route.cpp src/utils/routeHandler.cpp src/utils/routePath.cpp ${HEADER_FILES})
target_include_directories(Go2 PRIVATE src/utils)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
