# netcos/pathutils.py
#
# Weiwei Jia <harryxiyou@gmail.com> (Python)

import os
import sys
import time
import socket
import struct
import logging

from netcos import constants
from netcos.utils import cluster_help
from netcos.utils import NodeHelp
from netcos.utils import io

def _SendNodeCMD(CMDType, IP, Port, filepath):
  sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  e = sock.settimeout(constants.SOCK_TIMEOUT)
  try:
    MasterIP = NodeHelp._GetMasterIP()
    if MasterIP == IP or MasterIP == cluster_help.GetLocalIP():
      sock.connect((IP, Port))
      logging.info("Connect...")
    else:
      sock.connect((MasterIP, Port))
      logging.info("Connect...")
  except socket.timeout, e:
    logging.error("Timeout %s", e)
  except socket.error, e:
    logging.error("Error %s", e)
  except e:
    logging.error("Other %s", e)
  if not e:
    if CMDType == constants.CMD_GET_MASTER_NODE:
      FormatSize = struct.calcsize(constants.SOCK_SEND_FILE_FMT)
      DataFrame = struct.pack(constants.SOCK_SEND_FILE_FMT,
                              CMDType, 0, "None", "None")
      sock.send(DataFrame)
      _contents = sock.recv(constants.SOCK_MASTER_SEND_SIZE)
      MasterName = cluster_help.GetClusterName(_contents)
      MasterIP = cluster_help.GetMasterIP(_contents)
      print "Master node name: %s\nMaster node IP: %s" % (MasterName, MasterIP) 
    elif CMDType == constants.CMD_GET_NODE_LIST:
      FormatSize = struct.calcsize(constants.SOCK_SEND_FILE_FMT)
      DataFrame = struct.pack(constants.SOCK_SEND_FILE_FMT,
                              CMDType, 0, "None", "None")
      sock.send(DataFrame)
      __contents = sock.recv(constants.SOCK_MASTER_SEND_SIZE)
      print "IP Address\tHostname FQDN\t\tHostname\n", __contents.strip()
    elif CMDType == constants.CMD_DESTROY_NODES:
      FormatSize = struct.calcsize(constants.SOCK_SEND_FILE_FMT)
      DataFrame = struct.pack(constants.SOCK_SEND_FILE_FMT,
                              CMDType, 0, "None", "None")
      sock.send(DataFrame)
    elif CMDType == constants.CMD_DESTROY:
      FormatSize = struct.calcsize(constants.SOCK_SEND_FILE_FMT)
      DataFrame = struct.pack(constants.SOCK_SEND_FILE_FMT,
                              CMDType, 0, "None", "None")
      sock.send(DataFrame)
    elif CMDType == constants.CMD_SEND_FILE:
      filename = os.path.basename(filepath)
      filesize = os.stat(filepath).st_size
      DataFrame = struct.pack(constants.SOCK_SEND_FILE_FMT,
                              CMDType, filesize, filename, IP)
      sock.send(DataFrame)
      contents = io.ReadFile(filepath)
      sock.send(contents)
    else:
      logging.error("Error: Unknown command!")
      raise
  sock.close()

def SendMasterCMD(contents, CMDType):
  MasterIP = cluster_help.GetMasterIP(contents)
  _SendNodeCMD(CMDType, MasterIP, constants.FILE_PORT, None)

def SendDestroyNodesCMD(contents):
  MasterIP = cluster_help.GetMasterIP(contents)
  for line in contents.splitlines():
    fileds = line.split()
    if MasterIP not in line:
      logging.debug("CMD %d, IP %s, Port %d" % (constants.CMD_DESTROY_NODES,
                                        fileds[0].strip(), constants.FILE_PORT))
      _SendNodeCMD(constants.CMD_DESTROY_NODES, 
                   fileds[0].strip(), constants.FILE_PORT, None)
    else:
      continue
