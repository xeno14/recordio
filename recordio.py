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
        compressed_buffer = "" if not self._use_compression else self._Compress(uncompressed_buffer)
        self._fobj.write(struct.pack("i", self.MAGIC_NUMBER))
        self._fobj.write(struct.pack("QQ", uncompressed_size, compressed_size))
        if self._use_compression:
            self._fobj.write(compressed_buffer)
        else:
            self._fobj.write(uncompressed_buffer)
        return True

    def set_use_compression(self, val):
        self._use_compression = val

    def _Compress(self, data):
        raise NotImplementedError


class RecordReader(object):

    def __init__(self, fobj):
        self._fobj = fobj

    def ReadProtocolMessage(self, proto):
        try:
            magic_number, = struct.unpack("i", self._fobj.read(4))
        except:
            return False
        if not magic_number == RecordWriter.MAGIC_NUMBER:
            return False
        usize, csize= struct.unpack("QQ", self._fobj.read(16))
        buf = ""
        if csize != 0:
            buf = self._fobj.read(csize)
            raise NotImplementedError
        else:
            buf = self._fobj.read(usize)
        proto.ParseFromString(buf)
        return True
