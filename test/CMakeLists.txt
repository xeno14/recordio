include_directories(..)

enable_testing()

add_custom_command(
  OUTPUT person.pb.cc person.pb.h
  WORKING_DIRECTORY .
  DEPENDS person.proto
  COMMAND "protoc" "person.proto" "--cpp_out=."
)

add_test(recordio_test recordio_test)
add_executable(recordio_test test.cc person.pb.cc)
target_link_libraries(recordio_test recordio)
