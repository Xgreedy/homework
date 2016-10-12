/*
 *  unittest/test.c
 *
 *  Harry Wei <harryxiyou@gmail.com> (C) 2011
 */
#include <glib.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "xyas_sqlite.h"
#include "sqlite3.h"

# if 0
#define LEN			(50)

struct xyas_ctrl {
	char *uri;
	char db_name[LEN];
	sqlite3 *conn;
	char tb_algo_name[LEN];
};
#endif

int main(void) {
	const char *uri = "/tmp/testdb";
	const char *db = "xyas.db";

	struct xyas_ctrl *ctrl = NULL;
	ctrl = xyas_init_sqlite(uri, db);
	if (NULL == ctrl) {
		g_message("xyas_init_sqlite error!");
		exit(-1);
	}
	g_message("ctrl's addr is %p", ctrl);
	//g_message("ctrl's conn addr is %p", ctrl->conn);
#if 1
	g_message("uri is %s", ctrl->uri);
	g_message("db_name is %s", ctrl->db_name);
	g_message("tb_algo_name is %s", ctrl->tb_algo_name);
#endif
	struct xyas_algo algo_item = {
		.algo_name = "1.c",
		.ctime = 1,
		.lmtime = 2,
		.author = "jiawei",
		.text = "This is 1.c",
	};
	if (-1 == xyas_insert_2sqlite(ctrl, &algo_item)) {
		g_message("%s -- xyas_insert_2sqlite error", __func__);
		exit(-1);
	}
	struct xyas_algo __algo_item = {
		.algo_name = "2.c",
		.ctime = 1,
		.lmtime = 2,
		.author = "jiawei",
		.text = "This is 2.c",
	};
	if (-1 == xyas_insert_2sqlite(ctrl, &__algo_item)) {
		g_message("%s -- xyas_insert_2sqlite error", __func__);
		exit(-1);
	}
	struct xyas_algo _algo_item;
	memset(&_algo_item, 0, sizeof(struct xyas_algo));
	if (-1 == xyas_search_sqlite_item(ctrl, "1.c", &_algo_item)) {
		g_message("%s -- xyas_search_sqlite_item error", __func__);
		exit(-1);
	}
	g_print("algo_name is %s, ctime is %llu, lmtime is %llu, author is %s, text is %s\n", 
			_algo_item.algo_name,
			_algo_item.ctime,
			_algo_item.lmtime,
			_algo_item.author,
			_algo_item.text);
	if (-1 == xyas_delete_sqlite_item(ctrl, "1.c")) {
		g_message("%s -- xyas_delete_sqlite_item error", __func__);
		exit(-1);
	}
	return 0;
}
