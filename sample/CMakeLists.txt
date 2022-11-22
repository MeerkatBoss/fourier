add_executable(sample main.c)

target_link_libraries(sample PRIVATE fourier)

target_include_directories(sample PRIVATE 
                        ${CMAKE_CURRENT_LIST_DIR})