cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(fourier VERSION 1.0)


set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS}-D _DEBUG -ggdb3 -O0 -Wall -Wextra\
    -Waggressive-loop-optimizations -Wmissing-declarations\
    -Wcast-align -Wcast-qual -Wchar-subscripts -Wconversion\
    -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security\
    -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wopenmp-simd\
    -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow\
    -Wsign-conversion -Wstrict-overflow=2\
    -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types\
    -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code\
    -Wunused -Wvariadic-macros -Wno-missing-field-initializers\
    -Wno-narrowing -Wno-varargs -Wstack-protector\
    -fcheck-new -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -fPIE\
    -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr\
    -pie -Wlarger-than=8192 -Wstack-usage=8192 -lm") 
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_CXX_FLAGS}-D _DEBUG -ggdb3 -O0 -Wall -Wextra\
    -Waggressive-loop-optimizations -Wmissing-declarations\
    -Wcast-align -Wcast-qual -Wchar-subscripts -Wconversion\
    -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security\
    -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wopenmp-simd\
    -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow\
    -Wsign-conversion -Wstrict-overflow=2\
    -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types\
    -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code\
    -Wunused -Wvariadic-macros -Wno-missing-field-initializers\
    -Wno-narrowing -Wno-varargs -Wstack-protector\
    -fcheck-new -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -fPIE\
    -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr\
    -pie -Wlarger-than=8192 -Wstack-usage=8192 -lm") 

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS}-O3 -Wall")
set(CMAKE_LINKER_FLAGS_RELEASE "${CMAKE_C_FLAGS}-O3 -Wall")

add_subdirectory(src)

add_subdirectory(sample)

add_custom_target(run
    COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} && ${CMAKE_CURRENT_BINARY_DIR}/sample/sample
    DEPENDS sample)
