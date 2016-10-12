/*
 * mcmr/mcmr.c
 *
 * Weiwei Jia <harryxiyou@gmail.com> (C) 2014
 */
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "mcmr.h"
#include "action.h"
#include "mcmr_helper.h"

int main(int argc, char **argv) {
	/*
	 * 1, Init stuffs.
	 * 2, Coffee machine off stuffs.
	 * 3, Coffee machine on stuffs.
	 * 4, Coffee machine empty stuffs*/
	int ret = 0;
	struct mcmr *mcmr = NULL;

	ret = mcmr_init(&mcmr);
	//TODO: check return here

#ifdef MCMR_TEST_INIT
	mcmr->_do->coin(mcmr);
	ret = mcmr->_do->button(mcmr);
	mcmr->_do->cup(mcmr);
	mcmr->_do->coffee(mcmr);
	mcmr->_do->time(mcmr);
	mcmr->_do->power(mcmr);
	mcmr->_do->_return(mcmr);
#endif

	while (1) {
		// Off stuffs
		ret = mcmr_off(mcmr);
		//TODO: check return here

#ifdef MCMR_TEST_ON
		mcmr->power_on = 1;
#endif
		if (mcmr->power_on == 1) {
			// On stuffs, which involve empty stuffs
			ret = mcmr_on(mcmr);
			//TODO: check return here
		}
		de_init(mcmr);
	}

	return 0;

}
