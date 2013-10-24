/*
 * homework/mlcm/src/mlcm_write.c
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

uint32_t write_through(char *buf, uint32_t count, uint32_t pos) {
	/*TODO: Write buf to RAID file */
	return 0;
}

uint32_t write_back(struct mlcm_ctrl *ctrl, char *buf,
		                uint32_t count, uint32_t pos) {
	/*TODO: BUFFER1 write queue (FULL or else mechanisms, 
	 *      flush to) -> (with SAN protocol) BUFFER2 write
	 *      queue (FULL or else mechanisms, flush to) -> 
	 *      RAID storage pool*/
	return 0;
}

/*Mode: WRITE_THROUGH is 0, WRITE_BACK is 1*/
int mlcm_write(struct mlcm_ctrl *ctrl, char *buf,
               int count, int pos, uint8_t mode) {
  uint32_t ret = 0;

	if (NULL == ctrl || NULL == buf ||
		 (ctrl->buf1.buf_size - ctrl->buf1.buf_used) < count) {
		fprintf(stderr, "Buf size % PAGE_SIZE should be zero!\n");
		ret = -1;
		goto out;
	}
	if (mode == WRITE_THROUGH) {
		ret = write_through(buf, count, pos);
		if (ret < 0) {
      fprintf(stderr, "Write through error!\n");
			ret = -1;
			goto out;
		}
	} else if (mode == WRITE_BACK) {
		ret = write_back(ctrl, buf, count, pos);
		if (ret < 0) {
      fprintf(stderr, "Write back error!\n");
			ret = -1;
			goto out;
		}
	} else {
    fprintf(stderr, "Mode: WRITE_THROUGH is 0, WRITE_BACK is 1\n");
		ret = -1;
	}

out:
  return ret;
}
