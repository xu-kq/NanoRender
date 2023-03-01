add_library(Math OBJECT)
aux_source_directory(. srcs)
target_sources(Math PRIVATE ${srcs})
target_include_directories(Math PRIVATE ${PROJECT_SOURCE_DIR}/include)