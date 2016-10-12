/*
 *  test/test.c
 *
 *  Harry Wei <harryxiyou@gmail.com>
 */
#include <stdio.h>
#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "sqlite3.h"
//#include "sqlite3ext.h"

int sqlite3_exec_callback(void *data, int n_columns, char **col_values, char **col_names) {
	int i = 0;

	for (i = 0; i < n_columns; i++) {
		printf("%s  77dbg", col_values[i]);
		printf("******\n");
	}
	printf("\n");
	return 0;
}

int main(int argc, char **argv) {
	int i = 0;
	sqlite3 *conn = NULL;
	char *err_msg = NULL;
	char sql[200];

	memset(sql, 0, 200);
	if (SQLITE_OK != sqlite3_open("test.db", &conn)) {
		g_message("open database error!");
		exit(EXIT_FAILURE);
	}
	snprintf(sql, sizeof(char) * 200, "create table if not exists test1(id int, name varchar(20), age int)");
	if (SQLITE_OK != sqlite3_exec(conn, sql, NULL, NULL, &err_msg)) {
		g_message("exec table error, %s", err_msg);
		exit(EXIT_FAILURE);
	}
	memset(sql, 0, 200);
	for (i = 0; i < 10; i++) {
		snprintf(sql, sizeof(char) * 200, "insert into test1 (id, name, age) values (%d, '%s', %d)", i, "jiawei", i + 1);
		if (SQLITE_OK != sqlite3_exec(conn, sql, NULL, NULL, &err_msg)) {
			g_message("exec table error, %s", err_msg);
			exit(EXIT_FAILURE);
		}
		memset(sql, 0, 200);
	}
	snprintf(sql, sizeof(char) * 200, "select * from test1");
	sqlite3_exec(conn, sql, &sqlite3_exec_callback, NULL, &err_msg);
	if (SQLITE_OK != sqlite3_close(conn)) {
		g_message("close database error, %s", err_msg);
		exit(EXIT_FAILURE);
	}
	return 0;
}
