find_package( binary_reader ${SEARCH_PARAMETERS} COMPONENTS	binary_reader)

find_package( Boost ${SEARCH_PARAMETERS} COMPONENTS system )

compile_project( ${module_name} "*.cpp" "*.h" BINARY binaries binary_reader Boost )