add_library(Triangle OBJECT)
aux_source_directory(. srcs)
target_sources(Triangle PRIVATE ${srcs})
target_include_directories(Triangle PRIVATE ${PROJECT_SOURCE_DIR}/include)