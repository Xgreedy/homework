#ifndef MCMR_HELPER
#define MCMR_HELPER

int de_init(struct mcmr*);
int mcmr_init(struct mcmr**);
void time_out(int);
int mcmr_on(struct mcmr*);
int mcmr_off(struct mcmr*);

#endif
