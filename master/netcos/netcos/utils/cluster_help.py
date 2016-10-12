# netcos/utils/cluster_helper.py
#
# Weiwei Jia <harryxiyou@gmail.com> (Python) 2013

import os
import sys
import time
import logging
import socket

from netcos import pathutils
from netcos import constants

def ClusterHelpInfos():
  print """
    Network Controller System Cluster Operations.
	Options include:
      ncs-cluster init --master : Initialize NCS cluster on master node
      ncs-cluster init --slave  : Initialize NCS cluster on slave nodes
      ncs-cluster info          : Get NCS cluster information
      ncs-cluster getmaster     : Get NCS master information
      ncs-cluster destroy       : Destroy NCS cluster on the master node
      ncs-cluster --help        : Display help information
    """

def CheckClusterArgs(args):
  ArgsLen = len(sys.argv)
  if ArgsLen < 2:
    ClusterHelpInfos();
    sys.exit("Unknown option")
  else:
    SecondParam = sys.argv[1]
    if SecondParam not in constants.CLUSTER_PARAMS:
      ClusterHelpInfos();
      sys.exit("Unknown option")
    else:
      if SecondParam == constants.CLUSTER_PARAMS[0]:
        if ArgsLen < 3:
          ClusterHelpInfos();
          sys.exit("Unknown option")
        else:
          ThirdParam = sys.argv[2]
          if ThirdParam not in constants.INIT_PARAMS:
            ClusterHelpInfos();
            sys.exit("Unknown option")
  return

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

def GetLocalIP():
  LocalIP = socket.gethostbyname(socket.gethostname())
  return LocalIP
