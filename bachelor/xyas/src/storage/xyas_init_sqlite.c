/*
 *  src/server/xyas_init_sqlite.c
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

struct xyas_ctrl *xyas_init_sqlite(const char *uri, const char *db) {
	g_message("enter func %s >>>", __func__);
	char *err_msg = NULL;
	char sql[200];
//	char text[LEN];
	struct xyas_ctrl *ctrl = NULL;

	g_message("struct xyas_ctrl's size is %d", sizeof(struct xyas_ctrl));
	ctrl = (struct xyas_ctrl *)g_malloc0(sizeof(struct xyas_ctrl));
	if (NULL == ctrl) {
		g_message("get xyas ctrl error!");
		return NULL;
	}
//	ctrl->uri = (char *)g_malloc0(sizeof(char) * LEN);
#if 0
	memset(text, 0, LEN);
	snprintf(text, LEN, "%s", uri);
	g_strlcpy(ctrl->uri, text, LEN);
	memset(text, 0, LEN);
	snprintf(text, LEN, "%s/%s", uri, db);
	g_strlcpy(ctrl->db_name, text, LEN);
	memset(text, 0, LEN);
	snprintf(text, LEN, "%s", "algo");
	g_strlcpy(ctrl->tb_algo_name, text, LEN);
#endif
	snprintf(ctrl->uri, LEN, "%s", uri);
	snprintf(ctrl->db_name, LEN, "%s/%s", uri, db);
	snprintf(ctrl->tb_algo_name, LEN, "%s", "algo");
	g_message("%s -- uri is %s", __func__, ctrl->uri);
	g_message("%s -- db_name is %s", __func__, ctrl->db_name);
	g_message("%s -- tb_algo_name is %s", __func__, ctrl->tb_algo_name);
	if (SQLITE_OK != sqlite3_open(ctrl->db_name, &ctrl->conn)) {
		g_message("create db error!!!");
		return NULL;
	}
//	ctrl->tb_algo_name = (char *)g_malloc0(sizeof(char) * TB_NAME_LEN);
//	snprintf(ctrl->tb_algo_name, TB_NAME_LEN, "%s", "algo");
//	memset(sql, 0, 200);
	snprintf(sql, 200, 
			"create table if not exists %s(algo_name char(50), ctime int(10), lmtime int(10), author char(50), text char(4096))",
			ctrl->tb_algo_name);
	if (SQLITE_OK != sqlite3_exec(ctrl->conn, sql, NULL, NULL, &err_msg)) {
		g_message("execute db cmd error!!!");
		return NULL;
	}
	if (SQLITE_OK != sqlite3_close(ctrl->conn)) {
		g_message("close db error!!!");
		return NULL;
	}
	g_message("%s -- ctrl's addr is %p", __func__, ctrl);
	g_message("%s -- leave func %s", __func__, __func__);
	return ctrl;
}
