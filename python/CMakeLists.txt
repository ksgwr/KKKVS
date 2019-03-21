cmake_minimum_required(VERSION 2.8.12)

find_program(PYTHON "python")
if (PYTHON)
    set(SETUP_PY    "${CMAKE_CURRENT_SOURCE_DIR}/setup.py")
    set(DEPS        "${CMAKE_CURRENT_SOURCE_DIR}/src/__init__.py")
    set(OUTPUT      "${CMAKE_CURRENT_BINARY_DIR}/build")
    
    add_custom_command(OUTPUT ${OUTPUT}
                       COMMAND ${PYTHON}
                       ARGS ${SETUP_PY} bdist_wheel
                       DEPENDS ${DEPS})

    add_custom_target(kkkvspy ALL DEPENDS ${OUTPUT})

    install(CODE "execute_process(COMMAND ${PYTHON} ${SETUP_PY} install)")
endif()
