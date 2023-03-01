add_library(Scene OBJECT)
aux_source_directory(. srcs)
target_sources(Scene PRIVATE ${srcs})
target_include_directories(Scene PRIVATE ${PROJECT_SOURCE_DIR}/include)