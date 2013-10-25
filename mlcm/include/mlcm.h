#ifndef __MLCM_H
#define __MLCM_H

/*Page size is 4KB*/
#define WRITE_THROUGH   (0U)
#define WRITE_BACK      (1U)
#define PREREAD      	  (2U)
#define LRU      	      (3U)
#define RAID0_POOL		  "/tmp/raid0.txt"
#define RAID1_POOL		  "/tmp/raid1.txt"
#define RAID2_POOL		  "/tmp/raid2.txt"
#define RAID3_POOL		  "/tmp/raid3.txt"
#define RAID4_POOL		  "/tmp/raid4.txt"
#define RAID5_POOL		  "/tmp/raid5.txt"
#define RAID6_POOL		  "/tmp/raid6.txt"
#define PAGE_SIZE       (0x0000000000001000)

struct mlcm_io {
  uint32_t pos;
  void *buf;
  size_t count;
  enum BUF_TYPE {
    BUF1 = 1,
	BUF2 = 2
  } buf_type;
  struct mlcm_io *next;
};

enum protocol_cmd {
  FC = 1,
  IB = 2,
  ISCSI = 3,
  OTHER = 4
} PCMD;

struct mlcm_buf {
  char *buf;
  uint32_t buf_size;
  uint32_t buf_used;
};

enum RAID_MODE {
		RAID0 = 0,
		RAID1 = 1,
		RAID2 = 2,
		RAID3 = 3,
		RAID4 = 4,
		RAID5 = 5,
		RAID6 = 6
};

struct mlcm_ctrl {
	int fd;
  uint32_t t_io2b1;
  uint32_t t_b12b2;
  uint32_t t_b22sd;
  struct mlcm_buf buf1;
  struct mlcm_buf buf2;
  struct mlcm_io *write;
  struct mlcm_io *read;
	enum RAID_MODE raid_type;
};

int mlcm_init(struct mlcm_ctrl **, uint32_t, uint32_t);
int mlcm_read(struct mlcm_ctrl *, char *, int, int, uint8_t);
int mlcm_write(struct mlcm_ctrl *, char *, int, int, uint8_t);
int mlcm_deinit(struct mlcm_ctrl *);

#endif
