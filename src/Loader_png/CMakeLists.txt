add_library(Loader_png STATIC)
aux_source_directory(. srcs)
target_sources(Loader_png PRIVATE ${srcs})
target_include_directories(Loader_png PRIVATE ${PROJECT_SOURCE_DIR}/include)