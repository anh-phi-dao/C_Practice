function(target_set_warnings TARGET ENABLED ENABLED_AS_ERRORS)
    if (NOT ${ENABLED})
        message(STATUS "Warnings Disabled for: ${TARGET}")
        return()
    endif()

    set(MSVC_WARNINGS
        /W4
        /permissive-)

    set(CLANG_WARNINGS
        -Wall
        -Wextra
        -Wpedantic
        -save-temps
        )

    set(GCC_WARNINGS
        ${CLANG_WARNINGS})

    if(${ENABLED_AS_ERRORS})
        set(MSVC_WARNINGS ${MSVC_WARNINGS} /WX)
        set(CLANG_WARNINGS ${CLANG_WARNINGS} -Werror)
        set(GCC_WARNINGS ${GCC_WARNINGS} -Werror)
    endif()

    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        set(WARNINGS ${MSVC_WARNINGS})
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(WARNINGS ${CLANG_WARNINGS})
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        set(WARNINGS ${GCC_WARNINGS})
    endif()

    target_compile_options(${TARGET} PRIVATE ${WARNINGS})
    message(STATUS ${WARNINGS})

endfunction(target_set_warnings)

function(target_generate_assembly TARGET)

    set(CLANG_OPTIONS
        -S -fverbose-asm -o
        )
        
    set(GCC_OPTIONS
        ${CLANG_OPTIONS})

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(OPTIONS ${CLANG_OPTIONS})
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        set(OPTIONS ${GCC_OPTIONS})
    else()
        message(STATUS "target_generate_map only set for GNU or CLANG")
        return()
    endif()

    execute_process(COMMAND gcc ${OPTIONS} "${CMAKE_SOURCE_DIR}/build/${TARGET}.s" "${CMAKE_SOURCE_DIR}/${TARGET}.c")

    
endfunction(target_generate_assembly)