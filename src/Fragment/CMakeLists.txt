add_library(Fragment OBJECT)
aux_source_directory(. srcs)
target_sources(Fragment PRIVATE ${srcs})
target_include_directories(Fragment PRIVATE ${PROJECT_SOURCE_DIR}/include)