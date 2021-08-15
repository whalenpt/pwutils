
cmake_minimum_required(VERSION 3.19)

add_executable(report_example report_example.cpp)
add_executable(read_example read_example.cpp)

target_link_libraries(report_example PUBLIC pwutils)
target_link_libraries(read_example PUBLIC pwutils)

if(WIN32)
    foreach(ARG report_example read_example)
        add_custom_command(TARGET ${ARG}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:pwutils> ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Copy pwutils dll file to ${CMAKE_CURRENT_BINARY_DIR} directory" VERBATIM
        )
    endforeach()
endif()

set(READ_FILES
    T_0.json
    T_0.txt
    T_0_sig.txt
    SQ_T_0.dat
    SQ_T_0.txt
    SQ_T_0_sig.txt
)

foreach(ARG ${READ_FILES})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${ARG}
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${ARG}
    )
endforeach(ARG)


#add_custom_command(TARGET read_example POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy
#                    ${CMAKE_CURRENT_SOURCE_DIR}/T_0.json
#                    ${CMAKE_CURRENT_BINARY_DIR}/T_0.json
#)
#
#add_custom_command(TARGET read_example POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy
#        ${CMAKE_CURRENT_SOURCE_DIR}/SQ_T_0.dat
#        ${CMAKE_CURRENT_BINARY_DIR}/SQ_T_0.dat
#)



