# necos/src/server/noded.py
#
# Weiwei Jia <harryxiyou@gmail.com> (Python) 2013

import logging
import socket
import sys
import time
import threading
import struct

from netcos import constants
from netcos import pathutils
from netcos.utils import io
from netcos.utils import NodeHelp

def noded():
  logging.info("This is noded")
  sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  MasterIP = NodeHelp._GetMasterIP()
  logging.info("MasterIP is %s", MasterIP)
  sock.bind((constants.HOST, constants.FILE_PORT))
  sock.listen(constants.MAX_CONNECTION)
  while True:
    NewSock, Address = sock.accept()
    logging.info("Accept a new connection, address: %s", Address[0])
    FormatSize = struct.calcsize(constants.SOCK_SEND_FILE_FMT)
    DataFrame = NewSock.recv(FormatSize)
    CMD_Format, FileSize, FileName, IP = struct.unpack(constants.SOCK_SEND_FILE_FMT, 
                                                       DataFrame)
    logging.info("999 CMD Format is %d", CMD_Format)
    if CMD_Format == constants.CMD_SEND_FILE:
      logging.info("999 master send file, filesize %d, filename %s" % (FileSize, 
                                                                       FileName))
      _FileName = pathutils.FILE_STORAGE_DIR + FileName.strip("\0\0")
      logging.info("999 FileName is %s", _FileName)
      io.MakeDir(pathutils.FILE_STORAGE_DIR)
      contents = NewSock.recv(FileSize)
      logging.info("999 contents are %s", contents)
      io.WriteFile(_FileName, contents)
    elif CMD_Format == constants.CMD_DESTROY_NODES:
      NewSock.close()
      break
    else:
      continue
  sock.close()
