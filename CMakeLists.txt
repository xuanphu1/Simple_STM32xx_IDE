cmake_minimum_required(VERSION 3.16)
project(STM32IDE LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tìm wxWidgets
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

file(GLOB_RECURSE SOURCES   Component/src/*.cpp 
                            Component/data/*.cpp 
                            main/*.cpp
)

include_directories(Component/include
                    main  # Nếu main.h nằm ở thư mục gốc
)
# Tạo executable
add_executable(STM32IDE ${SOURCES})

# Link wxWidgets
target_link_libraries(STM32IDE PRIVATE ${wxWidgets_LIBRARIES})

# Cài đặt (tùy chọn)
install(TARGETS STM32IDE DESTINATION bin)