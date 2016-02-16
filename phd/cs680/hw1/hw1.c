/*
 * cs680/hw1.c
 *
 * Weiwei Jia <wj47@njit.edu> (C & Inline Assembly language) 2016
 */
#define HW1_DEBUG__
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int help(void) {
	fprintf(stderr, "Error input, please run in the following format\n");
	fprintf(stderr, "./hw1 string start_index end_index\n");
	fprintf(stderr, "NOTE: start_index or end_index cannot bigger than\n");
	fprintf(stderr, "string length; start_index cannot bigger or equal than end_index\n");
	return 0;
}

static inline char *sub_str(char *src, int s_idx, int e_idx) {
	int dest_len = e_idx - s_idx + 2;
#ifdef HW1_DEBUG__
	printf("dest_len is %d\n", dest_len);
#endif
	char *dest = (char *) malloc(sizeof(dest_len));
	if (dest == NULL) {
		fprintf(stderr, "Allocate memory error!\n");
		return NULL;
	}
	memset(dest, '\0', dest_len);
    strncpy(dest, &src[s_idx], dest_len - 1);
	return dest;
}

static inline char *asm_sub_str(char *src, int s_idx, int e_idx) {
	int dest_len = e_idx - s_idx + 2;
#ifdef HW1_DEBUG__
	printf("asm_dest_len is %d\n", dest_len);
#endif
	char *dest = (char *) malloc(sizeof(dest_len));
	if (dest == NULL) {
		fprintf(stderr, "Allocate memory error!\n");
		return NULL;
	}
	memset(dest, '\0', dest_len);
	dest_len = dest_len - 1;
    char *_src = &src[s_idx];
	//TODO
	src[e_idx + 1] = '\0';
	__asm__ __volatile__ ("cld\n\t"
						  "rep\n\t"
						  "movsl"
						  :
						  : "S" (_src), "D" (dest), "c" (dest_len)
						  );
#ifdef HW1_DEBUG__
	printf("asm_dest is %s\n", dest);
#endif
	return dest;
}

int main(int argc, char **argv) {
#ifdef HW1_DEBUG__
	printf("argc is %d\n", argc);
#endif
	int ret = 0;
	int num = argc;
	char **str = argv;
	if (num != 4) {
		help();
		ret = -1;
		goto out;
	}
    char *_str = str[1];
	int s_idx = atoi(argv[2]);
	int e_idx = atoi(argv[3]);
	int s_len = strlen(_str);
	if (s_idx >= s_len || e_idx > s_len || s_idx >= e_idx) {
		help();
		ret = -2;
        goto out;
	}
#ifdef HW1_DEBUG__
	printf("string is %s, s_idx is %d, e_idx is %d\n", _str, s_idx, e_idx);
	printf("string length is %d\n", s_len);
#endif
	char *dest = sub_str(_str, s_idx, e_idx);
	char *_dest = asm_sub_str(_str, s_idx, e_idx);
#ifdef HW1_DEBUG__
	printf("dest is %s\nasm_dest is %s\n", dest, _dest);
#endif
    ret = strcmp(dest, _dest);
#ifdef HW1_DEBUG__
	printf("strcmp return is %d\n", ret);
#endif
out:
	return ret;
}
