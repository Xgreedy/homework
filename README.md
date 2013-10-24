# Homework


Trivial homework stuffs finished by Weiwei Jia <harryxiyou@gmail.com>

### Bachelor degree
You could also find my bachelor homework here
https://code.google.com/p/homeworkxy/

### Master degree
The homework is divided by different courses.

#### Network storage curriculum
* MLCM is Multiple level Cache Management. <br>
[Framework image](https://github.com/HarryWei/homework/blob/master/images/MLCM.jpg) <br>
 1. I/O sequence <br>
    I/O Request -> Buffer1 at applicaition level <br>
    -> (iSCSI, IfiniBand, Fibre Channel) Buffer2 at storage level <br>
    -> Storage device <br>
 2. HOWTO
    Develop a library named libmlcm and it has some interfaces for
	users to call to check each way's performance. The interfaces are
	as follows.
	* int mlcm_init(struct mlcm_ctrl **, uint32_t buf1_size, uint32_t buf2_size)
	   Init MLCM, see mlcm structure for details.
	* uint32_t mlcm_write(struct mlcm_ctrl *, int fd, char *buf, int count,
			               int pos, uint8_t mode)
	   mode has two ways, one is write-through and another one is
	   write-back.
	* uint32_t mlcm_read(struct mlcm_ctrl *, int fd, char *buf,
			              int count, int pos, uint8_t mode)
	   mode has two ways, one is pre-read way and another one is Least
	   Recently Used (LRU) way.
	* mlcm_deinit(struct mlcm_ctrl *)
	   Destroy MLCM.
