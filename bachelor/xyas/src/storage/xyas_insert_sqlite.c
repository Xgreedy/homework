/*
 *  src/server/xyas_insert_sqlite.c
 *
 *  Harry Wei <harryxiyou@gmail.com> (C) 2011
 */
#include <stdio.h>
#include <glib.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "sqlite3.h"
#include "xyas_sqlite_ctrl.h"

static int
xyas_insert_call_back_print(void *data, 
							int n_cols,
							char **col_values,
							char **col_names) {
	int i = 0;

	for (i = 0; i < n_cols; i++) {
		g_print("%s 77dbg", col_values[i]);
	}
	printf("\n");
	return 0;
}

int
xyas_insert_2sqlite(struct xyas_ctrl *ctrl,
					struct xyas_algo *algo_item) {
	g_message("enter func %s >>>", __func__);
	char *err_msg = NULL;
	char sql[200];
	int ret = 0;

	memset(sql, 0, 200);
	snprintf(sql, 200, 
			"insert into %s (algo_name, ctime, lmtime, author, text) values ('%s', %llu, %llu, '%s', '%s')",
			ctrl->tb_algo_name,
			algo_item->algo_name,
			algo_item->ctime,
			algo_item->lmtime,
			algo_item->author,
			algo_item->text);
	g_message("%s -- algo_name is %s, ctime is %llu, lmtime is %llu, author is %s, text is %s", 
			__func__,
			algo_item->algo_name,
			algo_item->ctime,
			algo_item->lmtime,
			algo_item->author,
			algo_item->text);
	if (SQLITE_OK != sqlite3_open(ctrl->db_name, &ctrl->conn)) {
		g_message("open db error!!!");
		ret = -1;
		goto out;
	}
	if (SQLITE_OK != sqlite3_exec(ctrl->conn, sql, NULL, NULL, &err_msg)) {
		g_message("execute db cmd error!!!");
		ret = -1;
		goto out;
	}
	g_message("test insert item >>");
	memset(sql, 0, 200);
	sprintf(sql, "select * from %s", ctrl->tb_algo_name);
	if (SQLITE_OK != sqlite3_exec(ctrl->conn, sql, xyas_insert_call_back_print, NULL, &err_msg)) {
		g_message("execute db cmd error!!!");
		ret = -1;
		goto out;
	}
	if (SQLITE_OK != sqlite3_close(ctrl->conn)) {
		g_message("close db error!!!");
		ret = -1;
		goto out;
	}
out:
	g_message("leave func %s >>>", __func__);
	return ret;
}
