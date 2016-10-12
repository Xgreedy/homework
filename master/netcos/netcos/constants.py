# netcos/constants.py
#
# Weiwei Jia <harryxiyou@gmail.com> (Python)

import os
import sys

# Parameters
CLUSTER_PARAMS = ("init", "info", "getmaster", "destroy", "--help")
INIT_PARAMS = ("--master", "--slave")
NODE_PARAMS = ("add", "remove", "info", "list", "send", "--help")

# IP Address
LOCAL_HOST = "127.0.0.1"

# FORMAT
FORMAT = "%(asctime)s: %(filename)s: %(funcName)s: %(lineno)d: %(levelname)s: %(message)s"

# Socket
HOST = ""
PORT = 50007
FILE_PORT = 50008
MAX_CONNECTION = 5
SOCK_TIMEOUT = 1
# Slave send CMD request
SOCK_CMD_FMT = "I"
CMD_GET_MASTER_NODE = 1
CMD_GET_NODE_LIST = 2
CMD_SEND_FILE = 3
CMD_DESTROY_NODES = 4095
CMD_DESTROY = 4096
# Master send data
SOCK_SEND_FILE_FMT = "II128s20s"
SOCK_MASTER_SEND_SIZE = 1024
