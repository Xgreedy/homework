# netcos/utils/io.py
#
# Weiwei Jia <harryxiyou@gmail.com> (Python) 2013

import os
import sys
import re
import errno
from cStringIO import StringIO

from netcos import constants
from netcos import pathutils

def WriteFile(filepath, buf):
  f = open(filepath, "w")
  try:
    f.write(buf)
  finally:
    f.close()

def ReadFile(filepath):
  f = open(filepath, "r")
  try:
    contents = f.read()
  finally:
    f.close()

  return contents

def MakeDir(dirname):
  mode = 0750
  try:
    os.makedirs(dirname, mode)
  except OSError, err:
    if err.errno != errno.EEXIST or not os.path.exists(dirname):
      raise

def RemoveDir(dirname):
  try:
    os.rmdir(dirname)
  except OSError, err:
    if err.errno != errno.ENOENT:
      raise  

def RemoveFile(filename):
  try:
    os.unlink(filename)
  except OSError, err:
    if err.errno not in (errno.ENOENT, errno.EISDIR):
      raise
