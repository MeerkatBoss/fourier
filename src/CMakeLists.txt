add_library(fourier fourier.cpp)

target_link_directories(fourier PUBLIC
                    ${CMAKE_CURRENT_LIST_DIR})