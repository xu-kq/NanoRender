add_library(Loader_obj OBJECT)
aux_source_directory(. srcs)
target_sources(Loader_obj PRIVATE ${srcs})
target_include_directories(Loader_obj PRIVATE ${PROJECT_SOURCE_DIR}/include)