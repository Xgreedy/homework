#ifndef MCMR_H
#define MCMR_H

#include <pthread.h>

#define MCMR_DEBUG
//#define MCMR_TEST_ON
#define MCMR_TEST_INIT
//#define MCMR_ARM_PLATFORM

//Button keys semantics
#define MCMR_ON				(1)  //On state
#define MCMR_OFF			(2)  //Off state
#define MCMR_COIN			(3)  //Coin button
#define MCMR_START			(4)  //MCMR start
#define MCMR_RETURN			(5)  //MCMR return

#define MCMR_BPATH			"/dev/keypad"

struct coffee_vending_machine {
	int on;
	int off;
	int empty;
};

struct controller {
	int standby;
	int cup_ready;
	int coffee_ready;
};

struct light {
	int light_off;
	int light_on;
};

struct cup {
	int cup_idle;
	int cup_busy;
};

struct coffee {
	int coffee_idle;
	int coffee_busy;
};

struct mcmr {
	int money;
	int power_on;
	int power_off;
	int cup_empty;
	int cup_start;
	int cup_done;
	int coffee_empty;
	int coffee_start;
	int coffee_done;
	int time;
	int bfd;			//button fd
	int bnum;			//button number
	pthread_mutex_t mutex;
	struct coffee_vending_machine cvm;
	struct controller con;
	struct light light;
	struct cup cup;
	struct coffee coffee;
	struct action *_do;
};

struct action {
	int (*coin)(struct mcmr *);
	int (*button)(struct mcmr *);
	int (*cup)(struct mcmr *);
	int (*coffee)(struct mcmr *);
	int (*time)(struct mcmr *);
	int (*power)(struct mcmr *);
	int (*_return)(struct mcmr *);
};


#endif /*end for MCMR_H*/
