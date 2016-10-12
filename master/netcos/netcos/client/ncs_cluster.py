# netcos/src/client/netcos_cluster.py
#
# Weiwei Jia <harryxiyou@gmail.com> (Python) 2013
# Dawei Zhang <zhangdw91@live.com>(python) 2013
# Xin Liu <474087317@qq.com> (python) 2013

import os
import sys
import logging

from netcos import constants
from netcos import pathutils
from netcos import netutils
from netcos.server import masterd
from netcos.server import noded
from netcos.utils import cluster_help
from netcos.utils import nodesetup
from netcos.utils import log
from netcos.utils import io

def InitCluster(NodeNamespace):
  logging.info("This is InitCluster")
  if NodeNamespace == constants.INIT_PARAMS[0]:
    logging.info("This is master node")
    # TODO: whether all the slave nodes are available or not
    nodesetup.ReadEtcHosts()
    pid = os.fork()
    if pid == 0:
      masterd.masterd()
      os._exit(0)
    else:
      print "Child process id is ", pid
      os._exit(0) # Exit parent process
  elif NodeNamespace == constants.INIT_PARAMS[1]:
    logging.info("This is slave node")
    nodesetup.ReadEtcHosts()
    pid = os.fork()
    if pid == 0:
      noded.noded()
      os._exit(0)
    else:
      print "Child process id is ", pid
      os._exit(0) # Exit parent process
  else:
    print """ Unknown Option.
              "ncs-cluster --help" for help
          """

def InfoCluster():
  logging.info("This is InfoCluster")
  # TODO: run on slave node
  contents = io.ReadFile(pathutils.CLUSTER_CONFIG_FILE)
  ClusterName = cluster_help.GetClusterName(contents)
  ClusterCreateTime = cluster_help.GetClusterCreateTime()
  print "Cluster name: %s\nCreation time: %s\nMaster node: %s" % (ClusterName,
            ClusterCreateTime, ClusterName)

def GetmasterNode():
  logging.info("This is GetmasterNode")
  # TODO: run on slave node
  MasterName = ""
  MasterIP = ""
  contents = io.ReadFile(pathutils.CLUSTER_CONFIG_FILE)
  logging.debug("contents are %s", contents)
  logging.debug("LocalIP is %s", cluster_help.GetLocalIP())
  if cluster_help.GetLocalIP() == cluster_help.GetMasterIP(contents):
    logging.debug("contents are %s", contents)
    MasterName = cluster_help.GetClusterName(contents)
    MasterIP = cluster_help.GetMasterIP(contents)
    print "Master node name: %s\nMaster node IP: %s" % (MasterName, MasterIP)
  else:
    contents = io.ReadFile(pathutils.CLUSTER_CONFIG_FILE)
    netutils.SendMasterCMD(contents, constants.CMD_GET_MASTER_NODE)

def DestroyCluster():
  logging.info("This is DestroyCluster")
  # TODO: Remove dirs on all nodes
  # Remove these dirs directly? shutil.rmtree()?
  contents = io.ReadFile(pathutils.CLUSTER_CONFIG_FILE)
  netutils.SendMasterCMD(contents, constants.CMD_DESTROY)
  netutils.SendDestroyNodesCMD(contents)
  io.RemoveFile(pathutils.CLUSTER_CONFIG_FILE)
  io.RemoveDir(pathutils.CLUSTER_ETC_DIR)
  io.RemoveFile(pathutils.CLUSTER_LOGGING_FILE)
  io.RemoveFile(pathutils.NODE_LOGGING_FILE)
  io.RemoveDir(pathutils.CLUSTER_LOGGING_DIR)

def Main():
  # NOTE: Log file could only initialized one time
  #       and logging can not be used before this
  #       initialization.
  log.InitClusterLogging()
  logging.info("args are %s", sys.argv)
  args = sys.argv
  cluster_help.CheckClusterArgs(args)
  if args[1] == constants.CLUSTER_PARAMS[0]:
    InitCluster(args[2])
  elif args[1] == constants.CLUSTER_PARAMS[1]:
    InfoCluster()
  elif args[1] == constants.CLUSTER_PARAMS[2]:
    GetmasterNode()
  elif args[1] == constants.CLUSTER_PARAMS[3]:
    DestroyCluster()
  elif args[1] == constants.CLUSTER_PARAMS[4]:
    cluster_help.ClusterHelpInfos()
  else:
    print """ Unknown Option.
              "ncs-cluster --help" for help
          """
  return
