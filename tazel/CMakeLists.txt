tazel_sources_append(Tazel_LIB_SOURCES "src/")
tazel_sources_append(Tazel_LIB_SOURCES "include/")

add_library(Tazel STATIC "${Tazel_LIB_SOURCES}")

target_include_directories(Tazel
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Tazel PUBLIC PkgConfig::SDL3)
target_link_libraries(Tazel PUBLIC spdlog::spdlog)
target_link_libraries(Tazel PUBLIC glm::glm)
