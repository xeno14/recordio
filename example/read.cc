#include "person.pb.h"
#include "../recordio.h"

#include <iostream>
#include <string>


int main() {
  // Read
  std::ifstream ifs("example.recordio", std::ios::binary);
  recordio::RecordReader reader(&ifs);

  Person person;
  while(reader.ReadProtocolMessage(&person)) {
    std::cout << person.name() << " (" << person.age() << ")" << std::endl;
  }

  return 0;
}
