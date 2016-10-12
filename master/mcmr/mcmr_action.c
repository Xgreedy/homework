/*
 * mcmr/mcmr_action.c
 *
 * Weiwei Jia <harryxiyou@gmail.com> (C) 2014
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include "mcmr.h"
#include "action.h"

int do_coin(struct mcmr *mcmr) {
#ifdef MCMR_DEBUG
	printf("enter func %s\n", __func__);
	sleep(1);
#endif

#ifdef MCMR_DEBUG
	printf("leave func %s\n", __func__);
	sleep(1);
#endif
	return 0;
}

int do_button(struct mcmr *mcmr) {
#ifdef MCMR_DEBUG
	printf("enter func %s\n", __func__);
	sleep(1);
#endif
	//uint32_t fd;
#ifdef MCMR_ARM_PLATFORM
	uint8_t bnum = 0;

	if(read(mcmr->bfd, &bnum, (size_t) 1) == -1) {
		fprintf(stderr, "Read button error!\n");
		return -1;
	}
#else
	uint32_t bnum = 0;

	printf("Enter button number: ");
	scanf("%d", &bnum);
#endif

#ifdef MCMR_DEBUG
	printf("leave func %s\n", __func__);
	sleep(1);
#endif
	printf("Button get number is %d\n", bnum);
	return (uint32_t) bnum;
}

int do_cup(struct mcmr *mcmr) {
#ifdef MCMR_DEBUG
	printf("enter func %s\n", __func__);
	sleep(1);
#endif

#ifdef MCMR_DEBUG
	printf("leave func %s\n", __func__);
	sleep(1);
#endif
	return 0;
}

int do_coffee(struct mcmr *mcmr) {
#ifdef MCMR_DEBUG
	printf("enter func %s\n", __func__);
	sleep(1);
#endif

#ifdef MCMR_DEBUG
	printf("leave func %s\n", __func__);
	sleep(1);
#endif
	return 0;
}

int do_time(struct mcmr *mcmr) {
#ifdef MCMR_DEBUG
	printf("enter func %s\n", __func__);
	sleep(1);
#endif

#ifdef MCMR_DEBUG
	printf("leave func %s\n", __func__);
	sleep(1);
#endif
	return 0;
}

int do_power(struct mcmr *mcmr) {
#ifdef MCMR_DEBUG
	printf("enter func %s\n", __func__);
	sleep(1);
#endif

#ifdef MCMR_DEBUG
	printf("leave func %s\n", __func__);
	sleep(1);
#endif
	return 0;
}

int do_return(struct mcmr *mcmr) {
#ifdef MCMR_DEBUG
	printf("enter func %s\n", __func__);
	sleep(1);
#endif

#ifdef MCMR_DEBUG
	printf("leave func %s\n", __func__);
	sleep(1);
#endif
	return 0;
}
