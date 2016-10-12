# netcos/utils/nodesetup.py
#
# Weiwei Jia <harryxiyou@gmail.com> (Python) 2013

import os
import sys
import re
import socket
import logging
from cStringIO import StringIO

from netcos import constants
from netcos import pathutils
from netcos.utils import io

def WriteNcsConfig(contents):
  io.MakeDir(pathutils.CLUSTER_ETC_DIR)
  io.WriteFile(pathutils.CLUSTER_CONFIG_FILE, contents)

def ReadNcsConfig():
  _contents = io.ReadFile(pathutils.CLUSTER_CONFIG_FILE)
  logging.debug("Read contents are: %s", _contents)

def ReadEtcHosts():
  out = StringIO()

  if os.path.exists(pathutils.ETC_HOSTS):
    f = open(pathutils.ETC_HOSTS, "r")
  else:
    sys.exit("""Error: Cannot find "/etc/hosts" file.""")

  LocalIP = socket.gethostbyname(socket.gethostname())
  logging.debug("LocalIP is %s", LocalIP)

  for line in f.read().splitlines(True):
    fields = line.split()
    if (fields and fields[0].startswith("#")
    or fields and fields[0].startswith(":") 
    or fields and fields[0].startswith("f")):
      continue
    else:
      # TODO: Check whether slave nodes are alive
      if (constants.LOCAL_HOST not in line
      and line[:-1].strip()):
        out.write(line)

  logging.debug("contents are %s", out.getvalue())
  contents = out.getvalue()
  # FIXME: Now, master node's IP has to be in the first
  #        line in /etc/hosts. This would be fixed later on
  WriteNcsConfig(contents)
  out.close()
  f.close
