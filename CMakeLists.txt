cmake_minimum_required(VERSION 3.8)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
set(NAME_PROJECT "allocator")

project(${NAME_PROJECT} VERSION ${PROJECT_VERSION})

add_executable(${NAME_PROJECT} main.cpp)

set_target_properties(${NAME_PROJECT} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(${NAME_PROJECT} PRIVATE
        /W4
    )
else ()
    target_compile_options(${NAME_PROJECT} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS ${NAME_PROJECT} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
