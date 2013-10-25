/*
 * homework/mlcm/src/mlcm_deinit.c
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

int mlcm_init(struct mlcm_ctrl *ctrl) {
  uint32_t ret = 0;

	if (NULL != ctrl->buf2.buf) {
		free(*ctrl->buf2.buf);
	}
	if (NULL != ctrl->buf1.buf) {
		free(*ctrl->buf1.buf);
	}
	struct mlcm_io *wio = ctrl->write->next;
	struct mlcm_io *rio = ctrl->read->next;
	ctrl->write = wio;
	ctrl->read = rio;
	while (wio != NULL) {
		ctrl->write = ctrl->write->next;
		if (wio->buf != NULL) {
			free(wio->buf);
		}
		free(wio->write);
		wio = ctrl->write;
	}
	while (rio != NULL) {
		ctrl->read = ctrl->read->next;
		if (rio->buf != NULL) {
			free(rio->buf);
		}
		free(rio->write);
		rio = ctrl->read;
	}
	if (NULL != ctrl) {
		free(ctrl);
	}

out:
  return ret;
}
