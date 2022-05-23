cmake_minimum_required(VERSION 3.8)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
set(NAME_PROJECT "ip_filter")
set(LIB_NAME "ip_pool")

project(${NAME_PROJECT} VERSION ${PROJECT_VERSION})

option(WITH_BOOST_TEST "Whether to build with tests" ON)

add_executable(${NAME_PROJECT} main.cpp)

set_target_properties(${NAME_PROJECT} PROPERTIES
CXX_STANDARD 17
CXX_STANDARD_REQUIRED ON
)

add_library(
    ${LIB_NAME} SHARED
    ip_pool.hpp
    ip_pool.cpp
)
# target_include_directories(${LIB_NAME}
#     PRIVATE "${CMAKE_BINARY_DIR}"
# )

target_link_libraries(${NAME_PROJECT} 
    PRIVATE ${LIB_NAME}
)

if(WITH_BOOST_TEST)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    add_executable(test_filtration test_filtration.cpp)

    set_target_properties(test_filtration PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )

    set_target_properties(test_filtration PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    )

    target_link_libraries(test_filtration
        ${Boost_LIBRARIES}
        ${LIB_NAME}
    )
endif()

if (MSVC)
    target_compile_options(${NAME_PROJECT} PRIVATE
        /W4
    )
    if(WITH_BOOST_TEST)
        target_compile_options(test_filtration PRIVATE
            /W4
        )
    endif()
else ()
    target_compile_options(${NAME_PROJECT} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    if(WITH_BOOST_TEST)
        target_compile_options(test_filtration PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS ${NAME_PROJECT} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(WITH_BOOST_TEST)
    enable_testing()
    add_test(test_filtration test_filtration)
endif()
