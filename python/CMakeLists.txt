cmake_minimum_required(VERSION 2.8.12)

find_program(PYTHON "python3")
if (PYTHON)
    set(VENV        "${CMAKE_CURRENT_BINARY_DIR}/venv")
    set(VENVPY      "${VENV}/bin/python")
    set(SETUP_PY    "${CMAKE_CURRENT_SOURCE_DIR}/setup.py")
    set(DEPS        "${CMAKE_CURRENT_SOURCE_DIR}/src/__init__.py")
    set(BUILD_STAMP "${CMAKE_CURRENT_BINARY_DIR}/dist.stamp")
    set(OUTPUT      "${CMAKE_CURRENT_BINARY_DIR}/dist")
    
    execute_process(
        COMMAND ${PYTHON} -m venv ${VENV}
        RESULT_VARIABLE result
    )
    if(result)
        message(FATAL_ERROR "Build step for creating python venv failed: ${result}")
    endif()

    execute_process(
        COMMAND ${VENVPY} -m pip install pybind11 wheel --upgrade
        RESULT_VARIABLE result
    )
    if(result)
        message(FATAL_ERROR "Build step for installing pip requirements failed: ${result}")
    endif()

    add_custom_command(OUTPUT ${BUILD_STAMP}
                       COMMAND ${VENVPY} ${SETUP_PY} bdist_wheel
                       COMMAND touch ${BUILD_STAMP}
                       DEPENDS ${DEPS})

    add_custom_target(kkkvspy ALL DEPENDS ${BUILD_STAMP})

    install(CODE "
    file(GLOB whl \"${OUTPUT}/*.whl\")
    if (whl)
        execute_process(COMMAND ${PYTHON} -m pip install \${whl})
    endif()")
else()
    message(WARNING "skip python library build in case of not found python3 program")
endif()
