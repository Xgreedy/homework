# netcos/utils/log.py
#
# Weiwei Jia <harryxiyou@gmail.com> (Python) 2013

import os
import sys
import logging
from cStringIO import StringIO

from netcos import constants
from netcos import pathutils
from netcos.utils import io
    
def InitClusterLogging():
  io.MakeDir(pathutils.CLUSTER_LOGGING_DIR)
  logging.basicConfig(
    level = logging.NOTSET,
	format = constants.FORMAT,
    filename = pathutils.CLUSTER_LOGGING_FILE,
    filemode = "a")

def InitNodeLogging():
  logging.basicConfig(
    level = logging.NOTSET,
	format = constants.FORMAT,
    filename = pathutils.NODE_LOGGING_FILE,
    filemode = "a")
