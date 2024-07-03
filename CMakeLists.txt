cmake_minimum_required (VERSION 3.26)


project (oop2_project)
set (MY_AUTHORS "Yuval_Hasson-Or_Shain-Yehu_Raccah")

include (cmake/CompilerSettings.cmake)

if(APPLE)
    add_executable (${CMAKE_PROJECT_NAME})
elseif(WIN32)
    add_executable (${CMAKE_PROJECT_NAME} WIN32)
endif()

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)

add_subdirectory (include)
add_subdirectory (src)
add_subdirectory (resources)

include (cmake/Zip.cmake)


if(APPLE)
    set (SFML_LOCATION "/opt/homebrew/Cellar/sfml/2.6.1")
    set (SFML_DIR "${SFML_LOCATION}/lib/cmake/SFML")
    target_link_libraries (${CMAKE_PROJECT_NAME} sfml-graphics sfml-audio)
    find_package (SFML 2.6 COMPONENTS graphics audio REQUIRED)


elseif(WIN32)
    set (SFML_LOCATION "C:/SFML/SFML-2.6.0")
    set (SFML_DIR "${SFML_LOCATION}/lib/cmake/SFML")

    find_package (SFML 2.6 COMPONENTS graphics audio REQUIRED)

    set_target_properties (sfml-main sfml-system sfml-window sfml-graphics sfml-audio sfml-network PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)
    target_link_libraries (${CMAKE_PROJECT_NAME} sfml-graphics sfml-audio sfml-main)
    include (cmake/SFML.cmake)
endif()


