/**
 * @file test.cc
 * @brief Test recordio read and write
 */

#include "person.pb.h"
#include "../recordio.h"

#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

void Write() {
  std::ofstream ofs("example.recordio", std::ios::binary);
  recordio::RecordWriter writer(&ofs);

  std::string names[] = {"Smith", "Johnson", "William", "Jones"};
  int age = 20;
  for (const auto& name : names) {
    Person person;
    person.set_name(name);
    person.set_age(age++);
    writer.WriteProtocolMessage(person);
  }
  writer.Close();
}

std::vector<std::pair<std::string, int>> Read() {
  std::vector<std::pair<std::string, int>> res;
  std::ifstream ifs("example.recordio", std::ios::binary);
  recordio::RecordReader reader(&ifs);

  Person person;
  while (reader.ReadProtocolMessage(&person)) {
    res.emplace_back(person.name(), person.age());
  }
  reader.Close();
  return res;
}

int main() {
  Write();
  auto result = Read();

  assert(result[0].first == "Smith");
  assert(result[0].second == 20);
  assert(result[1].first == "Johnson");
  assert(result[1].second == 21);
  assert(result[2].first == "William");
  assert(result[2].second == 22);
  assert(result[3].first == "Jones");
  assert(result[3].second == 23);

  return 0;
}
