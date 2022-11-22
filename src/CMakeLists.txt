add_library(fourier fourier.c big_int.c)

target_include_directories(fourier PUBLIC
                    ${CMAKE_CURRENT_LIST_DIR}/include)