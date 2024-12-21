add_executable(example main.cc)
target_link_libraries(example library)
target_include_directories(example PRIVATE ${PROJECT_SOURCE_DIR})