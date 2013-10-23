/*
 * homework/mlcm/src/protocol.c
 *
 * Weiwei Jia <harryxiyou@gmail.com> (C) 2013
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <glib.h>
#include "mlcm.h"

int mock_protocol(PCMD cmd, uint32_t time) {
  uint32_t ret = 0;

  if (cmd == FC) {
	  fprintf(stdout, "Mock FC protocol!\n");
  } else if (cmd == IB) {
	  fprintf(stdout, "Mock IB protocol!\n");
  } else if (cmd == ISCSI) {
	  fprintf(stdout, "Mock iSCSI protocol!\n");
  } else {
	  fprintf(stdout, "Mock other protocol!\n");
  }
  ret = sleep(time);
  if (ret < 0) {
	  fprintf(stderr, "Sleep Error!\n");
	  ret = -1;
  }
  return ret;
}
