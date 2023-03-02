add_library(Texture OBJECT)
aux_source_directory(. srcs)
target_sources(Texture PRIVATE ${srcs})
target_include_directories(Texture PRIVATE ${PROJECT_SOURCE_DIR}/include)