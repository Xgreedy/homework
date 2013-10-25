/*
 * homework/mlcm/src/mlcm_read.c
 *
 * Weiwei Jia <harryxiyou@gmail.com> (C) 2013
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <glib.h>
#include "debug.h"
#include "mlcm.h"

uint32_t preread(char *buf, uint32_t count, uint32_t pos) {
	/*TODO: Preread from RAID pool*/
	return 0;
}

uint32_t lru(struct mlcm_ctrl *ctrl, char *buf,
		                uint32_t count, uint32_t pos) {
	/*TODO: LRU algorithm*/
	return 0;
}

/*Mode: Pre-read is 2, LRU is 3*/
int mlcm_read(struct mlcm_ctrl *ctrl, char *buf,
               int count, int pos, uint8_t mode) {
  uint32_t ret = 0;

	if (NULL == ctrl || NULL == buf ||
		 (ctrl->buf1.buf_size < count)) {
		fprintf(stderr, "Beyond buffer size!\n");
		ret = -1;
		goto out;
	}
	if (mode == PREREAD) {
		ret = preread(ctrl, buf, count, pos);
		if (ret < 0) {
      fprintf(stderr, "Pre-read error!\n");
			ret = -1;
			goto out;
		}
	} else if (mode == LRU) {
		ret = lru(ctrl, buf, count, pos);
		if (ret < 0) {
      fprintf(stderr, "LRU error!\n");
			ret = -1;
			goto out;
		}
	} else {
    fprintf(stderr, "Mode: Pre-read is 2, LRU is 3\n");
		ret = -1;
	}

out:
  return ret;
}
