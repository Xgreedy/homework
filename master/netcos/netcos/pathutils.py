# netcos/pathutils.py
#
# Weiwei Jia <harryxiyou@gmail.com> (Python)

import os
import sys

# System config files
ETC_HOSTS = "/etc/hosts"
CLUSTER_ETC_DIR = "/etc/netcos"
CLUSTER_CONFIG_FILE = CLUSTER_ETC_DIR + "/config"

# Longging files
CLUSTER_LOGGING_DIR = "/var/log/netcos"
CLUSTER_LOGGING_FILE = CLUSTER_LOGGING_DIR + "/netcos.cluster.log"
NODE_LOGGING_FILE = CLUSTER_LOGGING_DIR + "/netcos.node.log"

# File storage dir
FILE_STORAGE_DIR = "/tmp/netcos/"
