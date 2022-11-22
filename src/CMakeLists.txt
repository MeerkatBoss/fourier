add_library(fourier fourier.cpp big_int.cpp)

target_include_directories(fourier PUBLIC
                    ${CMAKE_CURRENT_LIST_DIR}/include)