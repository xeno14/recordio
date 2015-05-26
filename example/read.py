#!/usr/bin/env python2
# -*- coding: utf-8 -*-

from person_pb2 import Person
import recordio

with open("example.recordio", "rb") as f:
    reader = recordio.RecordReader(f)
    person = Person()
    while reader.ReadProtocolMessage(person):
        print person
