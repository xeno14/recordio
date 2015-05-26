#!/usr/bin/env python2
# -*- coding: utf-8 -*-

import struct


class RecordWriter(object):
    MAGIC_NUMBER = 0x3ed7230a

    def __init__(self, fobj):
        self._fobj = fobj
        self._use_compression = False

    def WriteProtocolMessage(self, proto):
        uncompressed_buffer = proto.SerializeToString()
        uncompressed_size = len(uncompressed_buffer)
        # TODO compress
        compressed_size = 0
        compressed_buffer = ""
        self._fobj.write(struct.pack("i", self.MAGIC_NUMBER))
        self._fobj.write(struct.pack("QQ", uncompressed_size, compressed_size))
        if self._use_compression:
            self._fobj.write(compressed_buffer)
        else:
            self._fobj.write(uncompressed_buffer)
        return True
