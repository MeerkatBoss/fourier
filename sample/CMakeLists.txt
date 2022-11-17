add_executable(sample main.cpp)

target_link_libraries(sample PRIVATE fourier)

target_include_directories(sample PRIVATE 
                        ${CMAKE_CURRENT_LIST_DIR})