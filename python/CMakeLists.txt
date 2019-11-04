cmake_minimum_required(VERSION 2.8.12)

configure_file("setup.cfg" "setup.cfg" COPYONLY)
configure_file("pytest.ini.in" "pytest.ini")

if (WIN32)
    find_program(PYTHON "python.exe")
else()
    find_program(PYTHON "python3")
endif()
if (PYTHON)
    set(VENV "${CMAKE_CURRENT_BINARY_DIR}/venv")
    if (WIN32)
        set(VENVPY "${VENV}/Scripts/python.exe")
    else()
        set(VENVPY "${VENV}/bin/python")
    endif()
    set(SETUP_PY    "${CMAKE_CURRENT_SOURCE_DIR}/setup.py")
    set(BUILD_STAMP "${CMAKE_CURRENT_BINARY_DIR}/dist.stamp")
    set(OUTPUT      "${CMAKE_CURRENT_BINARY_DIR}/dist")
    file(GLOB_RECURSE DEPS 
            "${CMAKE_CURRENT_SOURCE_DIR}/*.py"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/*.py"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.py")


    execute_process(
        COMMAND ${PYTHON} -m venv ${VENV}
        RESULT_VARIABLE result
    )
    if(result)
        message(FATAL_ERROR "Build step for creating python venv failed: ${result}")
    endif()

    execute_process(
        COMMAND ${VENVPY} -m pip install -r ${CMAKE_CURRENT_SOURCE_DIR}/requirements-dev.txt --upgrade --quiet
        RESULT_VARIABLE result
    )
    if(result)
        message(FATAL_ERROR "Build step for installing pip requirements failed: ${result}")
    endif()

    add_custom_command(OUTPUT ${BUILD_STAMP}
                       COMMAND ${VENVPY} ${SETUP_PY} bdist_wheel
                       COMMAND ${CMAKE_COMMAND} -E touch ${BUILD_STAMP}
                       DEPENDS ${DEPS} kkkvs_static)
    add_custom_target(kkkvspy ALL DEPENDS ${BUILD_STAMP})

    if(NOT without-test)
        enable_testing()
        add_test(NAME testkkkvspy
                COMMAND ${VENVPY} ${SETUP_PY} test)
    endif()

    install(CODE "
    file(GLOB WHL \"${OUTPUT}/*.whl\")
    if (WHL)
        execute_process(COMMAND ${PYTHON} -m pip install \${WHL} --upgrade)
    endif()")
else()
    message(WARNING "skip building python library in case of not found python3 program")
endif()
