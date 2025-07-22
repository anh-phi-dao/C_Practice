function(target_generate_map TARGET)

    set(CLANG_OPTIONS
        -Xlinker
        -Map=${TARGET}.map
        )

    set(GCC_OPTIONS
        ${CLANG_OPTIONS})
    
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(OPTIONS ${CLANG_OPTIONS})
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        set(OPTIONS ${GCC_OPTIONS})
    else()
        message(STATUS "target_generate_map only set for GNU or CLANG")
    endif()

    target_link_options(${TARGET} PRIVATE ${OPTIONS})
    message(STATUS ${WARNINGS})

endfunction(target_generate_map)
