CC=gcc
LDFLAGS=-pthread

all: mcmr

mcmr:
	$(CC) $(LDFLAGS) mcmr.c mcmr_action.c mcmr_helper.c -o $@

clean:
	rm -rf mcmr
