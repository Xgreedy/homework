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

static int check = 0;
static char *name = NULL;

// return 0, not found
// return 1, found
// return -1, error
static int
xyas_search_callback_getvalues(void *data, 
								int n_cols,
								char **col_values,
								char **col_names) {
	g_message("enter search call back");
	g_message("77 dbg n_cols is %d", n_cols);
#if 1
	struct xyas_algo *algo_item = (struct xyas_algo *)data;
	col_values -= 1;
	snprintf(algo_item->text, TEXT_LEN, "%s", col_values[n_cols]);
	col_values -= 1;
	snprintf(algo_item->author, LEN, "%s", col_values[n_cols]);
	col_values -= 1;
	char *endptr = NULL;
	algo_item->lmtime = strtoull(col_values[n_cols], &endptr, 0);
	col_values -= 1;
	algo_item->ctime = strtoull(col_values[n_cols], &endptr, 0);
	col_values -= 1;
	snprintf(algo_item->algo_name, LEN, "%s", col_values[n_cols]);
#endif
#if 0
	g_message("data is %s", (char *) data);
	int i = 0;
	for (i = 0; i < n_cols; i++) {
		printf("sql is [%s]\n", col_values[i]);
		if (0 == g_strcmp0(col_values[i], (char *)data)) {
			printf("sql i 77dbg is [%s]", col_values[i]);
			check = 1;
		}
	}
	g_message("check is %d", check);
#endif
	if (0 == g_strcmp0(algo_item->algo_name, name)) {
		check = 1;
	}
	g_message("leave search call back");
	return 0;
}

int
xyas_search_sqlite_item(struct xyas_ctrl *ctrl,
					const char *algo_name,
					struct xyas_algo *algo_item) {
	g_message("enter func %s >>>", __func__);
	g_message("algo_name is %s", algo_name);
	check = 0;
	char *err_msg = NULL;
	char sql[200];
	int ret = 0;
	name = (char *) algo_name;
#if 0
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
#endif
	if (SQLITE_OK != sqlite3_open(ctrl->db_name, &ctrl->conn)) {
		g_message("open db error!!!");
		ret = -1;
		goto out;
	}
#if 0
	if (SQLITE_OK != sqlite3_exec(ctrl->conn, sql, NULL, NULL, &err_msg)) {
		g_message("execute db cmd error!!!");
		ret = -1;
		goto out;
	}
	g_message("test insert item >>");
#endif
	memset(sql, 0, 200);
	sprintf(sql, "select * from %s where algo_name like '%s'", 
			ctrl->tb_algo_name,
			algo_name);
	if (SQLITE_OK != sqlite3_exec(ctrl->conn, sql, xyas_search_callback_getvalues, (void *) algo_item, &err_msg)) {
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
	g_message("leave func %s >>>", __func__, __func__);
#if 1
	if (check == 1) {
		ret = 1;
	}
#endif
	return ret;
}
