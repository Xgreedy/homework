#ifndef ACTION_H
#define ACTION_H

#include "mcmr.h"

#ifdef __cplusplus
extern "C" {
#endif

int do_coin(struct mcmr *mcmr);
int do_button(struct mcmr *mcmr);
int do_cup(struct mcmr *mcmr);
int do_coffee(struct mcmr *mcmr);
int do_time(struct mcmr *mcmr);
int do_power(struct mcmr *mcmr);
int do_return(struct mcmr *mcmr);

#ifdef __cplusplus
}
#endif

static struct action *get_action(void) {
#ifdef MCMR_DEBUG
	printf("enter func %s\n", __func__);
	sleep(1);
#endif
	struct action *ac = (struct action *) malloc(sizeof(struct action));
	//TODO: memory check
	ac->coin = do_coin;
	ac->button = do_button;
	ac->cup = do_cup;
	ac->coffee = do_coffee;
	ac->time = do_time;
	ac->power = do_power;
	ac->_return = do_return;

#ifdef MCMR_DEBUG
	printf("leave func %s\n", __func__);
	sleep(1);
#endif
	return ac;
}

#endif /*end ACTION_H*/
