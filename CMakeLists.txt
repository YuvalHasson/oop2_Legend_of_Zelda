cmake_minimum_required (VERSION 3.28.1)

project (Cat-Mouse)
set (MY_AUTHORS "")

include (cmake/CompilerSettings.cmake)

add_executable (${CMAKE_PROJECT_NAME})

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)

add_subdirectory (include)
add_subdirectory (src)
add_subdirectory (resources)

include (cmake/Zip.cmake)

set (SFML_LOCATION "/opt/homebrew/Cellar/sfml/2.6.1")
set (SFML_DIR "${SFML_LOCATION}/lib/cmake/SFML")

find_package (SFML 2.6 COMPONENTS graphics REQUIRED)



target_link_libraries (${CMAKE_PROJECT_NAME} sfml-graphics sfml-audio)



