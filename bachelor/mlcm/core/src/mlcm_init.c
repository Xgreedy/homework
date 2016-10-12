/*
 * homework/mlcm/src/mlcm_init.c
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

int mlcm_init(struct mlcm_ctrl **ctrl,
              uint32_t buf1_size, uint32_t buf2_size) {
  uint32_t ret = 0;

	/*NOTE: buf size % PAGE_SIZE == 0*/
	if (buf1_size % PAGE_SIZE != 0 || buf2_size % PAGE_SIZE != 0) {
		fprintf(stderr, "Buf size % PAGE_SIZE should be zero!\n");
		ret = -1;
		goto out;
	}
	(*ctrl) = (struct mlcm_ctrl *) g_malloc(sizeof(struct mlcm_ctrl));
	if (NULL == (*ctrl)) {
		fprintf(stderr, "Allocate Error!\n");
		ret = -1;
		goto out;
	}
  *ctrl->buf1.buf = (char *) g_malloc(sizeof(char) * buf1_size);
	if (NULL == *ctrl->buf1.buf) {
		fprintf(stderr, "Allocate Error!\n");
		free(*ctrl);
		ret = -1;
		goto out;
	}
	*ctrl->buf1.buf_size = buf1_size;
	*ctrl->buf1.buf_used = 0;
  *ctrl->buf2.buf = (char *) g_malloc(sizeof(char) * buf2_size);
	if (NULL == *ctrl->buf1.buf) {
		fprintf(stderr, "Allocate Error!\n");
		free(*ctrl);
		free(*ctrl->buf1.buf);
		ret = -1;
		goto out;
	}
	*ctrl->buf2.buf_size = buf2_size;
	*ctrl->buf2.buf_used = 0;

out:
  return ret;
}
