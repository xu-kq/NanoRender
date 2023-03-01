add_library(Rasterizer OBJECT)
aux_source_directory(. srcs)
target_sources(Rasterizer PRIVATE ${srcs})
target_include_directories(Rasterizer PRIVATE ${PROJECT_SOURCE_DIR}/include)