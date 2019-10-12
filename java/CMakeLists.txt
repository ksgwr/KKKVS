cmake_minimum_required(VERSION 2.8.12)

find_program(JAVA "java")
if (JAVA)
    if (WIN32)
    	set(GRADLE "${CMAKE_CURRENT_SOURCE_DIR}/gradlew")
    else()
        set(GRADLE "${CMAKE_CURRENT_SOURCE_DIR}/gradlew")
    endif()
    set(BUILD_GRADLE "${CMAKE_CURRENT_SOURCE_DIR}/build.gradle")
    set(JAVA_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/build")
    set(JAVA_BUILD_STAMP "${CMAKE_CURRENT_BINARY_DIR}/build.stamp")
    set(LIBSTATIC   "${CMAKE_BINARY_DIR}/lib/kkkvs/libkkkvs.a")
    file(GLOB_RECURSE JAVA_DEPS 
            "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/*.java")

    add_custom_command(OUTPUT ${JAVA_BUILD_STAMP}
                       COMMAND ${GRADLE} -b ${BUILD_GRADLE} build -x test -Dorg.gradle.project.buildDir=${JAVA_BUILD_DIR}
                       COMMAND ${CMAKE_COMMAND} -E touch ${JAVA_BUILD_STAMP}
                       DEPENDS ${JAVA_DEPS} ${LIBSTATIC})
    add_custom_target(jkkkvs ALL DEPENDS ${JAVA_BUILD_STAMP})

    if(NOT without-test)
        enable_testing()
        add_test(NAME testjkkkvs
                COMMAND ${GRADLE} -b ${BUILD_GRADLE} test -Dorg.gradle.project.buildDir=${JAVA_BUILD_DIR})
    endif()

else()
    message(WARNING "skip building java library in case of not found java program")
endif()