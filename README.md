recordio
========

recordio provides a interface to read/write multiple Protocol Buffers messages
from/to a single binary file.

Forked from [google/or-tools](https://github.com/google/or-tools)


# Usage

See [test.cc](https://github.com/xeno1991/recordio/blob/master/test/test.cc)
for an example

## Write

```cpp
Person person;    // a protobuf message

std::ofstream ofs("example.recordio", std::ios::binary);
recordio::RecordWriter writer(&ofs);

writer.WriteProtocolMessage(person);
writer.Close()
```

## Read

```cpp
std::ifstream ifs("example.recordio", std::ios::binary);
recordio::RecordReader reader(&ifs);

Person person;
while (reader.ReadProtocolMessage(&person)) {
  // do something
}
reader.Close();
```

# Dependencies

- zlib
- protocol buffer


# License

Apache License, Version 2.0 (see the codes for more details)
