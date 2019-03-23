cmake_minimum_required(VERSION 2.8.12)

find_program(PYTHON "python3")
if (PYTHON)
    set(VENV        "${CMAKE_CURRENT_BINARY_DIR}/venv")
    set(VENVPY      "${VENV}/bin/python")
    set(SETUP_PY    "${CMAKE_CURRENT_SOURCE_DIR}/setup.py")
    set(DEPS        "${CMAKE_CURRENT_SOURCE_DIR}/src/__init__.py")
    set(OUTPUT      "${CMAKE_CURRENT_BINARY_DIR}/dist")
    
    add_custom_command(OUTPUT ${VENV}
                        COMMAND ${PYTHON} -m venv ${VENV})

    add_custom_command(OUTPUT venv.stamp
                        COMMAND ${VENVPY} -m pip install pybind11 wheel --upgrade
                        COMMAND touch venv.stamp
                        DEPENDS ${VENV})

    add_custom_command(OUTPUT ${BUILD_STAMP}
                       COMMAND ${VENVPY} ${SETUP_PY} bdist_wheel
                       COMMAND touch ${BUILD_STAMP}
                       DEPENDS ${DEPS} venv.stamp)

    add_custom_target(kkkvspy ALL DEPENDS ${BUILD_STAMP})

    install(CODE "
    file(GLOB whl \"${OUTPUT}/*.whl\")
    if (whl)
        execute_process(COMMAND ${PYTHON} -m pip install \${whl})
    endif()")
else()
    message(WARNING "skip python library build in case of not found python3 program")
endif()
