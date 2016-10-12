# netcos/fabfile.py
#
# Weiwei Jia <harryxiyou@gmail.com> (Python) 2013

import os
from fabric.api import *

from netcos import pathutils 

project = "netcos"

# Install commands and dir
SYS_BIN = "/usr/local/sbin"
CLUSTER_BIN = "./netcos/tools/ncs-cluster"
NODE_BIN = "./netcos/tools/ncs-node"
SYS_DIR = "/usr/local/lib/python2.7/dist-packages"
NCS_DIR = "./netcos"

def setup():
  """
  setup stuffs
  """
  local("python setup.py")

def install():
  """
  install NetCoS
  """
  # FIXME: Error happen if DIRS don't belong to NCS
  if os.path.exists(pathutils.CLUSTER_ETC_DIR):
    local("rm -r %s" % pathutils.CLUSTER_ETC_DIR)
  if os.path.exists(pathutils.CLUSTER_LOGGING_DIR):
    local("rm -r %s" % pathutils.CLUSTER_LOGGING_DIR)
  if os.path.exists(pathutils.FILE_STORAGE_DIR):
    local("rm -r %s" % pathutils.FILE_STORAGE_DIR)
  local("sudo chmod +x %s" % CLUSTER_BIN)
  local("sudo chmod +x %s" % NODE_BIN)
  local("cp %s %s" % (CLUSTER_BIN, SYS_BIN))
  local("cp %s %s" % (NODE_BIN, SYS_BIN))
  local("cp -r %s %s" % (NCS_DIR, SYS_DIR))
