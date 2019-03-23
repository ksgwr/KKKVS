cmake_minimum_required(VERSION 2.8.12)

find_program(PYTHON "python3")
if (PYTHON)
    set(VENV        "${CMAKE_CURRENT_BINARY_DIR}/venv")
    set(VENVPY      "${VENV}/bin/python")
    set(VENVPIP     "${VENV}/bin/pip3")
    set(SETUP_PY    "${CMAKE_CURRENT_SOURCE_DIR}/setup.py")
    set(DEPS        "${CMAKE_CURRENT_SOURCE_DIR}/src/__init__.py")
    set(OUTPUT      "${CMAKE_CURRENT_BINARY_DIR}/build")
    
    add_custom_command(OUTPUT ${VENV}
                        COMMAND ${PYTHON} -m venv ${VENV})

    add_custom_command(OUTPUT ${VENVPIP}
                        COMMAND ${VENVPY} -m pip install --upgrade pip
                        COMMAND ls ${VENV}/bin
                        DEPENDS ${VENV})

    add_custom_command(OUTPUT venv.stamp
                        COMMAND ${VENVPIP} install pybind11 wheel --upgrade
                        DEPENDS ${VENVPIP})

    add_custom_command(OUTPUT ${OUTPUT}
                       COMMAND ${VENVPY} ${SETUP_PY} bdist_wheel
                       DEPENDS ${DEPS} venv.stamp)

    add_custom_target(kkkvspy ALL DEPENDS ${OUTPUT})

    install(CODE "execute_process(COMMAND ${PYTHON} ${SETUP_PY} install)")
else()
    message(WARNING "skip python library build in case of not found python3 program")
endif()
