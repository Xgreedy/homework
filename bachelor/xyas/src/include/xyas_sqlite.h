#ifndef		_XYAS_SQLITE_H
#define		_XYAS_SQLITE_H

#include <stdint.h>
#include "xyas_sqlite_ctrl.h"

#ifdef __cplusplus
extern "C" {
#endif

struct xyas_ctrl *xyas_init_sqlite(const char *uri, const char *db);
int xyas_insert_2sqlite(struct xyas_ctrl *ctrl, struct xyas_algo *algo_item);			//add
int xyas_delete_sqlite_item(struct xyas_ctrl *, const char *);							//delete
//int xyas_alter_sqlite_item(void);		//alter
int xyas_search_sqlite_item(struct xyas_ctrl *, const char *, struct xyas_algo *);		//search

#ifdef __cplusplus
}
#endif

#endif
