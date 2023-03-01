add_library(Utility OBJECT)
aux_source_directory(. srcs)
target_sources(Utility PRIVATE ${srcs})
target_include_directories(Utility PRIVATE ${PROJECT_SOURCE_DIR}/include)