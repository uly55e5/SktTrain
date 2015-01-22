
aux_source_directory(. LIB_SRC_LIST)

add_library(skttrain SHARED ${LIB_SRC_LIST})
target_link_libraries(skttrain jack)
