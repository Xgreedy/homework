/*
 * homework/mlcm/src/raid.c
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

int raid_create(struct mlcm_ctrl *ctrl, uint32_t disk_size,
		            uint32_t disk_nums, uint8_t raid_type) {
  uint32_t ret = 0;

	if (NULL == ctrl || (disk_size % PAGE_SIZE != 0) ||
			disk_nums <= 0) {
		fprintf(stderr, "Parameter Error!\n");
		ret = -1;
		goto out;
	}
	switch (raid_type) {
		case RAID0:
			ret = raid0_create(ctrl, disk_size, disk_nums);
			if (ret < 0) {
        fprintf(stderr, "Raid0 create error!\n");
				ret = -1;
				goto out;
			}
		break;
		case RAID1:
			ret = raid1_create(ctrl, disk_size, disk_nums);
			if (ret < 0) {
        fprintf(stderr, "Raid1 create error!\n");
				ret = -1;
				goto out;
			}
		break;
		case RAID2:
			ret = raid2_create(ctrl, disk_size, disk_nums);
			if (ret < 0) {
        fprintf(stderr, "Raid2 create error!\n");
				ret = -1;
				goto out;
			}
		break;
		case RAID3:
			ret = raid3_create(ctrl, disk_size, disk_nums);
			if (ret < 0) {
        fprintf(stderr, "Raid3 create error!\n");
				ret = -1;
				goto out;
			}
		break;
		case RAID4:
			ret = raid4_create(ctrl, disk_size, disk_nums);
			if (ret < 0) {
        fprintf(stderr, "Raid4 create error!\n");
				ret = -1;
				goto out;
			}
		break;
		case RAID5:
			ret = raid5_create(ctrl, disk_size, disk_nums);
			if (ret < 0) {
        fprintf(stderr, "Raid5 create error!\n");
				ret = -1;
				goto out;
			}
		break;
		case RAID6:
			ret = raid6_create(ctrl, disk_size, disk_nums);
			if (ret < 0) {
        fprintf(stderr, "Raid6 create error!\n");
				ret = -1;
				goto out;
			}
		break;
		default:
		  fprintf(stderr, "Raid just has 0~6 way!\n");
			ret = -1;
			goto out;
	}


out:
  return ret;
}
