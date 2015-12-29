/**
 * @file test.cc
 * @brief Test recordio read and write
 */

#include "person.pb.h"
#include "../recordio.h"
#include "../recordio_range.h"

#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

void Write(const std::string& path) {
  std::ofstream ofs(path, std::ios::binary);
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

std::vector<std::pair<std::string, int>> Read(const std::string& path) {
  std::vector<std::pair<std::string, int>> res;
  std::ifstream ifs(path, std::ios::binary);
  recordio::RecordReader reader(&ifs);

  Person person;
  while (reader.ReadProtocolMessage(&person)) {
    res.emplace_back(person.name(), person.age());
  }
  reader.Close();
  return res;
}

int main() {
  const std::string path = "example.recordio";

  Write(path);
  auto result = Read(path);

  assert(result[0].first == "Smith");
  assert(result[0].second == 20);
  assert(result[1].first == "Johnson");
  assert(result[1].second == 21);
  assert(result[2].first == "William");
  assert(result[2].second == 22);
  assert(result[3].first == "Jones");
  assert(result[3].second == 23);

  std::vector<std::string> names;
  for (const auto& person : recordio::ReaderRange<Person>(path)) {
    names.push_back(person.name());
  }
  assert(names[0] == "Smith");
  assert(names[1] == "Johnson");
  assert(names[2] == "William");
  assert(names[3] == "Jones");

  return 0;
}
