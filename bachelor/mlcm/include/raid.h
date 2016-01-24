#ifndef __RAID_H
#define __RAID_H

#include <unistd.h>
#include <stdint.h>
#include "mlcm.h"

int raid_create(struct mlcm_ctrl *, uint32_t, uint32_t, uint8_t);
int raid0_create(struct mlcm_ctrl *, uint32_t, uint32_t);
int raid1_create(struct mlcm_ctrl *, uint32_t, uint32_t);
int raid2_create(struct mlcm_ctrl *, uint32_t, uint32_t);
int raid3_create(struct mlcm_ctrl *, uint32_t, uint32_t);
int raid4_create(struct mlcm_ctrl *, uint32_t, uint32_t);
int raid5_create(struct mlcm_ctrl *, uint32_t, uint32_t);
int raid6_create(struct mlcm_ctrl *, uint32_t, uint32_t);

#endif
