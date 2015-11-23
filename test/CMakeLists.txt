set(TEST_DIR ${PROJECT_SOURCE_DIR}/test)
include_directories(.. ${TEST_DIR})


add_custom_command(
  OUTPUT ${TEST_DIR}/person.pb.cc ${TEST_DIR}/person.pb.h
  WORKING_DIRECTORY ${TEST_DIR}
  DEPENDS ${TEST_DIR}/person.proto
  COMMAND "protoc" "--proto_path=${TEST_DIR}" "${TEST_DIR}/person.proto" "--cpp_out=."
)

add_test(recordio_test recordio_test)
add_executable(recordio_test test.cc ${TEST_DIR}/person.pb.cc)
target_link_libraries(recordio_test recordio)
