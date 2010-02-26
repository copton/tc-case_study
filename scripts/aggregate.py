#!/usr/bin/env python

import csv
import sys
from function_deco import FunctionDeco

deco = FunctionDeco()

class Values(object):
    __slots__=["text", "data", "bss"]
    def __init__(self, values):
        self.text = int(values[0])
        self.data = int(values[1])
        self.bss = int(values[2])

    def __repr__(self):
        return "%s, %s, %s" % (self.text, self.data, self.bss)

data = { }

reader = csv.reader(sys.stdin, delimiter=',', quotechar='"')
for row in reader:
    if len(row) == 0 or row[0].startswith('#'):
        continue
    data[deco(row[0])] = Values(row[1:])


def sum(*keys):
    def _sum(select):
        res = 0
        for key in keys:
            values = data[key]
            value = getattr(values, select)
            res += value
        return res
    return dict((select, _sum(select)) for select in ["text", "data", "bss"])

libevent = sum("collect.o", "main.o", "receive.o", "send.o")
libpal = sum("layout.o", "logr.o", "logw.o", "pal.o", "receive.o#2", "send.o#2", "sensor.o", "timer.o")
libgen = sum("app.o", "main.o#2")

appevent = sum("src/application/collect_and_forward/event-based/event-based")
appgen = sum("src/application/collect_and_forward/generated/generated")


res = """results:
Codesize: (in bytes)
  hand-written: %d
  generated total: %d
    application: %d
    pal: %d
  ratio:
    incl. pal: %.2f
    excl. pal: %.2f

Memory consumption (bytes):
   hand-written:
      data: %d
      bss: %d
      total: %d
   generated:
      data: %d
      bss: %d
      total: %d
    ratio:
      data: %.2f
      bss: %.2f
      total: %.2f
""" % (
    libevent["text"],
    libgen["text"] + libpal["text"],
    libgen["text"],
    libpal["text"],
    1.0 * (libgen["text"] + libpal["text"]) / libevent["text"],
    1.0 * libgen["text"] / libevent["text"],
    appevent["data"],
    appevent["bss"],
    appevent["data"] + appevent["bss"],
    appgen["data"],
    appgen["bss"],
    appgen["data"] + appgen["bss"],
    1.0 * appgen["data"] / appevent["data"],
    1.0 * appgen["bss"] / appevent["bss"],
    1.0 * (appgen["data"] + appgen["bss"]) / (appevent["data"] + appevent["bss"]),
)

sys.stdout.write(res)
