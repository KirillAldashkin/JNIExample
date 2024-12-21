find_package(Java REQUIRED)
find_package(JNI REQUIRED)

add_library(wrapper SHARED jni_wrapper.cc)
target_include_directories(wrapper PRIVATE ${JNI_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR})
target_link_libraries(wrapper library ${JAVA_JVM_LIBRARY})

# Java header uses 'char*' for string literals for whatever reason
target_compile_options(wrapper PRIVATE -Wno-writable-strings -Wno-write-strings)
