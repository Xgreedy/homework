# netcos/src/client/netcos_node.py
#
# Weiwei Jia <harryxiyou@gmail.com> (Python) 2013
# Dawei Zhang <zhangdw91@live.com>(python) 2013
# Xin Liu <474087317@qq.com> (python) 2013

import os
import sys
import logging
import socket

from netcos import constants
from netcos import pathutils
from netcos import netutils
from netcos.server import masterd
from netcos.server import noded
from netcos.utils import cluster_help
from netcos.utils import NodeHelp
from netcos.utils import nodesetup
from netcos.utils import log
from netcos.utils import io

def AddNode(Node):
  logging.info("This is AddNode")

def RemoveNode(Node):
  logging.info("This is RemoveNode")

def NodeInfo():
  logging.info("This is NodeInfo")

def NodeList():
  logging.info("This is NodeList")
  contents = io.ReadFile(pathutils.CLUSTER_CONFIG_FILE)
  if cluster_help.GetLocalIP() == cluster_help.GetMasterIP(contents):
    print "IP Address\tHostname FQDN\t\tHostname\n", contents.strip()
  else:
    netutils.SendMasterCMD(contents, constants.CMD_GET_NODE_LIST)

def NodeSend(args):
  logging.info("This is NodeSend")
  Hostname = args[3]
  FilePath = args[5]
  IsSameNode = NodeHelp.CheckNodeWithHostname(Hostname)
  if IsSameNode:
    sys.exit("Send Datas with same node!")
  RemoteIP = socket.gethostbyname(Hostname)
  netutils._SendNodeCMD(constants.CMD_SEND_FILE,
                        RemoteIP, constants.FILE_PORT, FilePath)

def Main():
  # NOTE: Log file could only initialized one time
  #       and logging can not be used before this
  #       initialization.
  log.InitNodeLogging()
  logging.info("args are %s", sys.argv)
  args = sys.argv
  NodeHelp.CheckNodeArgs(args)
  if args[1] == constants.NODE_PARAMS[0]:
    AddNode(args[2])
  elif args[1] == constants.NODE_PARAMS[1]:
    RemoveNode(args[2])
  elif args[1] == constants.NODE_PARAMS[2]:
    NodeInfo()
  elif args[1] == constants.NODE_PARAMS[3]:
    NodeList()
  elif args[1] == constants.NODE_PARAMS[4]:
    NodeSend(args)
  elif args[1] == constants.NODE_PARAMS[5]:
    NodeHelp.NodeHelpInfos()
  else:
    print """ Unknown Option.
              "ncs-node --help" for help
          """
  return
