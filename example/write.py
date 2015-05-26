#!/usr/bin/env python2
# -*- coding: utf-8 -*-

from person_pb2 import Person
import recordio

p = Person(name="John", age=100)

names = ["Smith", "Johnson", "William", "Jones", "Brown"]
ages = range(20, 20 + len(names))

with open("example.recordio", "wb") as f:
    for name, age in zip(names, ages):
        person = Person(name=name, age=age)
        writer = recordio.RecordWriter(f)
        writer.WriteProtocolMessage(person)
