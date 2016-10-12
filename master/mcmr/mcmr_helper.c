/*
 * mcmr/mcmr_helper.c
 *
 * Weiwei Jia <harryxiyou@gmail.com> (C) 2014
 */
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "mcmr.h"
#include "action.h"

int de_init(struct mcmr *mcmr) {
#ifdef MCMR_DEBUG
	printf("enter func %s\n", __func__);
	sleep(1);
#endif
	mcmr->money = 0;
	mcmr->power_on = 0;
	mcmr->power_off = 0;
	mcmr->cup_empty = 0;
	mcmr->cup_start = 0;
	mcmr->cup_done = 0;
	mcmr->coffee_empty = 0;
	mcmr->coffee_start = 0;
	mcmr->coffee_done = 0;
	mcmr->time = 0;
	mcmr->cvm.on = 0;
	mcmr->cvm.off = 0;
	mcmr->cvm.empty = 0;
	mcmr->con.standby = 0;
	mcmr->con.cup_ready = 0;
	mcmr->con.coffee_ready = 0;
	mcmr->light.light_off = 0;
	mcmr->light.light_on = 0;
	mcmr->cup.cup_idle = 0;
	mcmr->cup.cup_busy = 0;
	mcmr->coffee.coffee_idle = 0;
	mcmr->coffee.coffee_busy = 0;
	//(*mcmr)->_do = get_action();
#ifdef MCMR_DEBUG
	printf("leave func %s\n", __func__);
	sleep(1);
#endif
	return 0;
}

int mcmr_init(struct mcmr **mcmr) {
#ifdef MCMR_DEBUG
	printf("enter func %s\n", __func__);
	sleep(1);
#endif
	(*mcmr) = (struct mcmr *) malloc(sizeof(struct mcmr));
	//TODO: check mem here
	(*mcmr)->money = 0;
	(*mcmr)->power_on = 0;
	(*mcmr)->power_off = 0;
	(*mcmr)->cup_empty = 0;
	(*mcmr)->cup_start = 0;
	(*mcmr)->cup_done = 0;
	(*mcmr)->coffee_empty = 0;
	(*mcmr)->coffee_start = 0;
	(*mcmr)->coffee_done = 0;
	(*mcmr)->time = 0;
	((*mcmr)->cvm).on = 0;
	((*mcmr)->cvm).off = 0;
	((*mcmr)->cvm).empty = 0;
	((*mcmr)->con).standby = 0;
	((*mcmr)->con).cup_ready = 0;
	((*mcmr)->con).coffee_ready = 0;
	((*mcmr)->light).light_off = 0;
	((*mcmr)->light).light_on = 0;
	((*mcmr)->cup).cup_idle = 0;
	((*mcmr)->cup).cup_busy = 0;
	((*mcmr)->coffee).coffee_idle = 0;
	((*mcmr)->coffee).coffee_busy = 0;
	(*mcmr)->_do = get_action();
	pthread_mutex_init(&((*mcmr)->mutex), NULL);

#ifdef MCMR_ARM_PLATFORM
	(*mcmr)->bfd = open(MCMR_BPATH, 0); //TODO: check return
#endif
	//TODO: check ret here
#ifdef MCMR_DEBUG
	printf("leave func %s\n", __func__);
	sleep(1);
#endif
	return 0;
}

int mcmr_off(struct mcmr *mcmr) {
#ifdef MCMR_DEBUG
	printf("enter func %s\n", __func__);
	sleep(1);
#endif
	mcmr->power_off = 1;
	mcmr->cvm.off = 1;
	//If button pushed, set power_on to be true.
	if (mcmr->_do->button(mcmr) == MCMR_ON) {
		mcmr->power_on = 1;
		mcmr->cvm.on = 1;
		mcmr->power_off = 0;
		mcmr->cvm.off = 0;
		mcmr->money = 0;
		fprintf(stdout, "CVM in on state!\n");
	}
#ifdef MCMR_DEBUG
	printf("leave func %s\n", __func__);
	sleep(1);
#endif
	return 0;
}

void *controller(void *arg) {
	struct mcmr *mcmr = (struct mcmr *) arg;
	int ret = 0;

#ifdef MCMR_DEBUG
	mcmr->_do->coin(mcmr);
	printf("Enter controller thread!\n");
	sleep(1);
#endif
	while (1) {
		fprintf(stdout, "Controller in standby state!\n");
		sleep(1);
		mcmr->con.standby = 1;
		pthread_mutex_lock(&(mcmr->mutex));
		sleep(1);
		mcmr->bnum = mcmr->_do->button(mcmr);
		sleep(5);
		pthread_mutex_unlock(&(mcmr->mutex));
		if(mcmr->bnum == (uint32_t) MCMR_COIN) {
			fprintf(stdout, "Money plus one!\n");
			sleep(1);
			mcmr->money += 1;
		}
		if (mcmr->bnum == (uint32_t) MCMR_START &&
				mcmr->money > 0) {
			mcmr->cup_start = 1;
			mcmr->con.standby = 0;
			mcmr->con.cup_ready = 1;
			fprintf(stdout, "Controller in cup-ready state!\n");
			sleep(1);
		}
		if (mcmr->con.cup_ready == 1 &&
				mcmr->cup_done == 1) {
			mcmr->coffee_start == 1;
			mcmr->con.cup_ready = 0;
			mcmr->con.coffee_ready = 1;
			fprintf(stdout, "Controller in coffee-ready state!\n");
			sleep(1);
		}
		if (mcmr->con.coffee_ready == 1 && mcmr->coffee_done == 1) {
			mcmr->money -= 1;
			mcmr->con.coffee_ready = 0;
			mcmr->con.standby = 1;
			fprintf(stdout, "Controller in standby state!\n");
			sleep(1);
		}
		if (mcmr->con.standby == 1 &&
				mcmr->bnum == (uint32_t) MCMR_RETURN) {
			mcmr->money = 0;
			fprintf(stdout, "Money returns to be zero!\n");
			sleep(1);
		}
		if(mcmr->bnum == MCMR_OFF) {
			fprintf(stdout, "CVM in off state!\n");
			sleep(1);
			break;
		}
	}
#ifdef MCMR_DEBUG
	printf("Leave controller thread!\n");
	sleep(1);
#endif
	//pthread_exit("Controller done");
}

void time_out(int n) {
	sleep(n);
	return ;
}

void *cup(void *arg) {
	struct mcmr *mcmr = (struct mcmr *) arg;

#ifdef MCMR_DEBUG
	//mcmr->_do->button(mcmr);
	printf("Enter cup thread!\n");
	sleep(1);
#endif
	while (1) {
		//TODO: add empty state
		mcmr->cup.cup_idle = 1;
		fprintf(stdout, "Cup in cup-idle state!\n");
		sleep(1);
		if (mcmr->cup_start == 1) {
			mcmr->cup.cup_busy = 1;
			mcmr->cup.cup_idle = 0;
			fprintf(stdout, "Cup in cup-busy state!\n");
			time_out(1);
			mcmr->cup_done = 1;
			mcmr->cup.cup_busy = 0;
			mcmr->cup.cup_idle = 1;
		}
		if(mcmr->bnum == MCMR_OFF) {
			fprintf(stdout, "CVM in off state!\n");
			sleep(1);
			break;
		}
	}
#ifdef MCMR_DEBUG
	printf("Leave cup thread!\n");
	sleep(1);
#endif
	//pthread_exit("Cup done");
}

void *light(void *arg) {
	struct mcmr *mcmr = (struct mcmr *) arg;

#ifdef MCMR_DEBUG
	mcmr->_do->coin(mcmr);
	printf("Enter light thread!\n");
	sleep(1);
#endif
	while (1) {
		mcmr->light.light_off = 1;
		fprintf(stdout, "Light in light-off state!\n");
		sleep(1);
		if (mcmr->cup_start == 1) {
			mcmr->light.light_on = 1;
			mcmr->light.light_off = 0;
			fprintf(stdout, "Light in light-on state!\n");
			sleep(1);
		}
		if (mcmr->cup_done == 1) {
			mcmr->light.light_on = 0;
			mcmr->light.light_off = 1;
			fprintf(stdout, "Light in light-off state!\n");
			sleep(1);
		}
		if(mcmr->bnum == MCMR_OFF) {
			fprintf(stdout, "CVM in off state!\n");
			sleep(1);
			break;
		}
	}
#ifdef MCMR_DEBUG
	printf("Leave light thread!\n");
	sleep(1);
#endif
	//pthread_exit("Light done");
}

void *coffee(void *arg) {
	struct mcmr *mcmr = (struct mcmr *) arg;

#ifdef MCMR_DEBUG
	mcmr->_do->coin(mcmr);
	printf("Enter coffee thread!\n");
	sleep(1);
#endif
	while (1) {
		//TODO: add empty state
		mcmr->coffee.coffee_idle = 1;
		fprintf(stdout, "Coffee in Coffee-idle state!\n");
		sleep(1);
		if (mcmr->coffee_start == 1) {
			mcmr->coffee.coffee_busy = 1;
			mcmr->coffee.coffee_idle = 0;
			fprintf(stdout, "Coffee in Coffee-busy state!\n");
			time_out(5);
			mcmr->coffee_done = 1;
			mcmr->coffee.coffee_busy = 0;
			mcmr->coffee.coffee_idle = 1;
			fprintf(stdout, "Coffee in Coffee-idle state!\n");
			sleep(1);
		}
		if(mcmr->bnum == MCMR_OFF) {
			fprintf(stdout, "CVM in off state!\n");
			break;
		}
	}
#ifdef MCMR_DEBUG
	printf("Leave coffee thread!\n");
	sleep(1);
#endif
	//pthread_exit("Coffee done");
}

int mcmr_on(struct mcmr *mcmr) {
#ifdef MCMR_DEBUG
	printf("leave func %s\n", __func__);
	sleep(1);
#endif
	//TODO: fork four porcess/threads to handle controller, cup, light and
	//coffee respectively.
#if 0
	int ret = fork();
	if (ret == 0) {
		//Controller process.
#ifdef MCMR_DEBUG
		printf("This is the controller process stuffs.\n");
		sleep(1);
#endif
		exit(0);
	}
	ret = fork();
	if (ret == 0) {
		//Cup process.
#ifdef MCMR_DEBUG
		printf("This is the cup process stuffs.\n");
		sleep(1);
#endif
		exit(0);
	}
	ret = fork();
	if (ret == 0) {
		//Light process.
#ifdef MCMR_DEBUG
		printf("This is the light process stuffs.\n");
		sleep(1);
#endif
		exit(0);
	}
	ret = fork();
	if (ret == 0) {
		//Coffee process.
#ifdef MCMR_DEBUG
		printf("This is the coffee process stuffs.\n");
		sleep(1);
#endif
		exit(0);
	}
#endif
	//Thread is more convenient for this course project
	//Mutex should be uesed to access mcmr
	//Controller thread
	pthread_t ctid;
	pthread_t cup_tid;
	pthread_t ltid;
	pthread_t coftid;
	int ret = pthread_create(&ctid, NULL, controller, mcmr);
	if (ret != 0) {
		printf("Thread create error!\n");
		return -1;
	}
	//Cup thread
	ret = pthread_create(&cup_tid, NULL, cup, mcmr);
	if (ret != 0) {
		printf("Thread create error!\n");
		return -1;
	}
	//Light thread
	ret = pthread_create(&ltid, NULL, light, mcmr);
	if (ret != 0) {
		printf("Thread create error!\n");
		return -1;
	}
	//Coffee thread
	ret = pthread_create(&coftid, NULL, coffee, mcmr);
	if (ret != 0) {
		printf("Thread create error!\n");
		return -1;
	}
	pthread_join(ctid, NULL);
	pthread_join(cup_tid, NULL);
	pthread_join(ltid, NULL);
	pthread_join(coftid, NULL);

#ifdef MCMR_DEBUG
	printf("leave func %s\n", __func__);
	sleep(1);
#endif
	return 0;
}
