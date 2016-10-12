# necos/src/server/masterd.py
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
from netcos import netutils
from netcos.utils import io
from netcos.utils import cluster_help

def masterd():
  logging.info("This is masterd")
  sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
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
    if CMD_Format == constants.CMD_GET_MASTER_NODE:
      logging.info("999 masterd get master node")
      contents = io.ReadFile(pathutils.CLUSTER_CONFIG_FILE)
      NewSock.send(contents)
    if CMD_Format == constants.CMD_SEND_FILE:
      logging.info("999 slave send file, filesize %d, filename %s" % (FileSize,
                                                                      FileName))
      _FileName = pathutils.FILE_STORAGE_DIR + FileName.strip("\0\0")
      logging.info("999 FileName is %s", _FileName)
      RemoteIP = IP.strip("\0\0")
      logging.info("999 RemoteIP is %s", IP.strip("\0\0"))
      io.MakeDir(pathutils.FILE_STORAGE_DIR)
      contents = NewSock.recv(FileSize)
      logging.info("999 contents are %s", contents)
      io.WriteFile(_FileName, contents)
      if RemoteIP != cluster_help.GetLocalIP():
        netutils._SendNodeCMD(constants.CMD_SEND_FILE, RemoteIP,
                              constants.FILE_PORT, _FileName)
        io.RemoveFile(_FileName)
    elif CMD_Format == constants.CMD_GET_NODE_LIST:
      logging.info("999 masterd get node list")
      contents = io.ReadFile(pathutils.CLUSTER_CONFIG_FILE)
      NewSock.send(contents)
    elif CMD_Format == constants.CMD_DESTROY:
      NewSock.close()
      break
    else:
      continue
  sock.close()
