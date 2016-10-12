#ifndef		_XYAS_SQLITE_CTRL_H
#define		_XYAS_SQLITE_CTRL_H

#include <stdint.h>
#include <glib.h>

#include "sqlite3.h"

#define	LEN							(50)
#define	TEXT_LEN					(1024)

struct xyas_algo {
	char algo_name[LEN];
	uint64_t ctime;
	uint64_t lmtime;
	char author[LEN];
	char text[TEXT_LEN];
};

struct xyas_ctrl {
	char uri[LEN];
	char db_name[LEN];
	sqlite3 *conn;
	char tb_algo_name[LEN];
};

#endif
