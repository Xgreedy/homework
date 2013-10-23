#ifndef __MLCM_H
#define __MLCM_H

#define BUFFER_SIZE (0x0000000000001000)

struct mlcm_io {
  int fd;
  void *buf;
  size_t count;
  struct mlcm_io *next;
};

enum protocol_cmd {
  FC = 1,
  IB = 2,
  ISCSI = 3,
  OTHER = 4
} PCMD;

struct mlcm_ctrl {
  uint32_t t_io2b1;
  uint32_t t_b12b2;
  uint32_t t_b22sd;
};

#endif
