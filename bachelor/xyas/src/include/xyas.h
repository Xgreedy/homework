#ifndef __XYAS_H
#define __XYAS_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#define ITEMS		(4)

static GtkWidget *submit_button = NULL;
static GtkWidget *help_button = NULL;
static GtkWidget *exit_button = NULL;
static GtkWidget *table = NULL;
static GtkWidget *label = NULL;
static GtkWidget *text[ITEMS] = {NULL};
const char *get_text[ITEMS] = {NULL};
static char *buff[ITEMS] = {NULL};
static GtkWindow *window = NULL;
static const int window_height = 400;
static const int window_width = 400;
static char ip[50] = {0};
static int port = 0;
static GtkWindow *algo_window = NULL;
static GtkWidget *algo_table = NULL;
static GtkWidget *algo_label = NULL;

static GtkWindow *add_window = NULL;
static GtkWidget *add_table = NULL;
static GtkWidget *add_view = NULL;
static GtkWidget *add_submit = NULL;
static gchar *add_text = NULL;

static GtkWindow *alter_window = NULL;
static GtkWidget *alter_table = NULL;
static GtkWidget *alter_view = NULL;
static GtkWidget *alter_submit = NULL;
static gchar *alter_text = NULL;
#include "create_window.h"

#endif
