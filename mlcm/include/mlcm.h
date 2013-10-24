#ifndef __MLCM_H
#define __MLCM_H

/*Page size is 4KB*/
#define PAGE_SIZE (0x0000000000001000)

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

struct mlcm_buf {
  uint32_t buf_size;
  uint32_t buf_used;
};

struct mlcm_ctrl {
  uint32_t t_io2b1;
  uint32_t t_b12b2;
  uint32_t t_b22sd;
  struct mlcm_buf buf1;
  struct mlcm_buf buf2;
  struct mlcm_io *write;
  struct mlcm_io *read;
};

#endif
