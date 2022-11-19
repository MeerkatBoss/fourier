add_library(fourier fourier.cpp)

target_include_directories(fourier PUBLIC
                    ${CMAKE_CURRENT_LIST_DIR}/include)