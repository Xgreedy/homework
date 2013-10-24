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
 2. HOWTO <br>
    Develop a library named libmlcm and it has some interfaces for <br>
	users to call to check each way's performance. The interfaces are <br>
	as follows. <br>
	* int mlcm_init(struct mlcm_ctrl **, uint32_t buf1_size, uint32_t buf2_size) <br>
	   Init MLCM, see mlcm structure for details. <br>
	* uint32_t mlcm_write(struct mlcm_ctrl *, int fd, char *buf, int count, <br>
			               int pos, uint8_t mode) <br>
	   mode has two ways, one is write-through and another one is <br>
	   write-back. <br>
	* uint32_t mlcm_read(struct mlcm_ctrl *, int fd, char *buf, <br>
			              int count, int pos, uint8_t mode) <br>
	   mode has two ways, one is pre-read way and another one is Least <br>
	   Recently Used (LRU) way. <br>
	* mlcm_deinit(struct mlcm_ctrl *) <br>
	   Destroy MLCM.
