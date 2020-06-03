#pragma once

#include <mysql.h>

struct configuration{
	char *host;
	char *db_username;
	char *db_password;
	unsigned int port;
	char *database;	
	char password[45];
};
extern char cf[16];
extern struct configuration conf;


extern MYSQL* connection_db();
extern int parse_config(char *path, struct configuration *conf);
extern char *getInput(unsigned int lung, char *stringa, bool hide);
extern bool setup_prepared_stmt(MYSQL_STMT **stmt, char *statement, MYSQL *conn);
extern void print_error (MYSQL *conn, char *message);
extern void print_stmt_error (MYSQL_STMT *stmt, char *message);
extern char multiChoice(char *domanda, char choices[], int num);
extern void dump_result_set(MYSQL *conn, MYSQL_STMT *stmt, char *title);

extern void finish_with_error(MYSQL *conn, char *message);
extern void finish_with_stmt_error(MYSQL *conn, MYSQL_STMT *stmt, char *message, bool close_stmt);

extern void start_client_view(MYSQL *conn);
extern void start_operator_view(MYSQL *conn);
extern void start_manager_view(MYSQL *conn);
extern void start_member_view(MYSQL *conn);
