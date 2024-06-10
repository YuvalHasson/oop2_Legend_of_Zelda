# Function to recursively get all subdirectories
function(get_all_subdirectories base_dir output_var)
    file(GLOB_RECURSE SUBDIRS LIST_DIRECTORIES true RELATIVE ${base_dir} ${base_dir}/*)
    set(result "")
    foreach(subdir ${SUBDIRS})
        if(IS_DIRECTORY ${base_dir}/${subdir})
            list(APPEND result ${base_dir}/${subdir})
        endif()
    endforeach()
    set(${output_var} "${result}" PARENT_SCOPE)
endfunction()

# Add the include directory itself
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# Get all subdirectories and add them to the include directories
get_all_subdirectories(${CMAKE_CURRENT_LIST_DIR} ALL_SUBDIRS)
foreach(subdir ${ALL_SUBDIRS})
    target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${subdir})
endforeach()

# Collect all .h files in the include directory and its subdirectories
file(GLOB_RECURSE MY_HEADER_FILES CONFIGURE_DEPENDS LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_LIST_DIR} *.h)

# Optionally, add the collected header files to the target (useful for IDEs)
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${MY_HEADER_FILES})
