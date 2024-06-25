cmake_minimum_required(VERSION 3.5.0)
project(Go2 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(SRC_FILES src/utils/user.cpp src/utils/models/car.cpp src/utils/models/driver.cpp src/utils/route.cpp src/utils/routeHandler.cpp src/utils/routePath.cpp src/utils/models/routeTemplates.cpp src/routes/session.cpp src/utils/data_base/SHA256.cpp)
add_executable(Go2 src/main.cpp ${SRC_FILES})
target_include_directories(Go2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)