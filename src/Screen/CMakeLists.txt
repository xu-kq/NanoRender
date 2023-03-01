add_library(Screen OBJECT)
aux_source_directory(. srcs)
target_sources(Screen PRIVATE ${srcs})
target_include_directories(Screen PRIVATE ${PROJECT_SOURCE_DIR}/include)