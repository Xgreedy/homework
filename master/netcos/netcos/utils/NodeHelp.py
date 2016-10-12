# netcos/utils/NodeHelp.py
#
# Weiwei Jia <harryxiyou@gmail.com> (Python) 2013

import os
import sys
import time
import logging
import socket

from netcos import pathutils
from netcos import constants
from netcos.utils import io

def NodeHelpInfos():
  print """
    Network Controller System Node Operations.
    Options include:
    ncs-node add node.example.com    : Add a node into NCS cluster
    ncs-node remove node.example.com : Remove the node from NCS cluster
    ncs-node info                    : Check the node information
    ncs-node list                    : List all the nodes in NCS cluster
    ncs-node send --to-node node -f file -t xs -p n : Send the file to node2
    ncs-node --help                  : Display help information
    """

def CheckNodeArgs(args):
  ArgsLen = len(sys.argv)
  if ArgsLen < 2:
    NodeHelpInfos();
    sys.exit("Unknown option")
  else:
    SecondParam = sys.argv[1]
    if SecondParam not in constants.NODE_PARAMS:
      NodeHelpInfos();
      sys.exit("Unknown option")
    else:
      if (SecondParam == constants.NODE_PARAMS[0] or
          SecondParam == constants.NODE_PARAMS[1]):
        if ArgsLen != 3:
          NodeHelpInfos();
          sys.exit("Unknown option")
        else:
          ThirdParam = sys.argv[2]
          # TODO: Check the third parameter
      elif SecondParam == constants.NODE_PARAMS[4]:
        if ArgsLen != 10:
          NodeHelpInfos();
          sys.exit("Unknown option")
        else:
          ThirdParam = sys.argv[2]
          # TODO: Check rest parameters
  return

def _GetMasterIP():
  # FIXME: handle Master IP normal
  contents = io.ReadFile(pathutils.CLUSTER_CONFIG_FILE)
  _contents = contents.split()
  return _contents[0]

def GetClusterName(contents):
  # FIXME: handle Clusetr Name normal
  _contents = contents.split()
  return _contents[1]

def GetClusterCreateTime():
  # Normal?
  # Just for master node
  return time.ctime(os.path.getmtime(pathutils.CLUSTER_CONFIG_FILE))

def GetMasterIP(contents):
  # FIXME: handle Master IP normal
  _contents = contents.split()
  return _contents[0]

def CheckNodeWithHostname(Hostname):
  RemoteIP = socket.gethostbyname(Hostname)
  LocalIP = socket.gethostbyname(socket.gethostname())
  if RemoteIP == LocalIP:
    return True
  else:
    return False
