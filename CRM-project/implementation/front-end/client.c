/*
 * 
 ************** CLIENT MAIN ***************** 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"



void show_phone_numbers(){
	MYSQL *conn;
	conn = connection_db();
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	
	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_numeri_telefono(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize phone number statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING; // IN
	param[0].buffer = cf;  //use cf of the current user 
	param[0].buffer_length = strlen(cf);
	
	// Bind parameters and store procedure
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for phone number\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "An error occurred while retrieving the phone number.");
		goto out;
	}
	
	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nPhone numbers");
	
	
	out:
	mysql_stmt_close(prepared_stmt);
	

}

void show_accepted_proposals(){
	MYSQL *conn;
	conn = connection_db();
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	
	
	
	
	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_proposte_accettate(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize proposal statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;	//IN
	param[0].buffer = cf;
	param[0].buffer_length = strlen(cf);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for accepted proposals\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "An error occurred while retrieving the accepted proposals.");
		goto out;
	}
	
	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nAccepted proposals");
	
	out:
	mysql_stmt_close(prepared_stmt);
	

}

void show_client(){
	MYSQL *conn;
	conn = connection_db();
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	
	
	
	
	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_cliente(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize client statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;	//IN
	param[0].buffer = cf;
	param[0].buffer_length = strlen(cf);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for client report\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "An error occurred while retrieving the client report.");
		goto out;
	}
	
	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nClient's credentials");
	
	out:
	mysql_stmt_close(prepared_stmt);
	
	
	
	
	
	
}

void start_client_view(MYSQL *conn){
	// Client main
	char options[2] = {'1','2'};
	char op;
	
	printf("Welcome in the system!\n");

	if(!parse_config("users/cliente.json", &conf)) {
		fprintf(stderr, "Unable to load client configuration\n");
		exit(EXIT_FAILURE);
	}

	if(mysql_change_user(conn, conf.db_username, conf.db_password, conf.database)) {
		fprintf(stderr, "mysql_change_user() failed\n");
		exit(EXIT_FAILURE);
	}
	printf("\033[2J\033[H");
	while(1) {
		printf("********** CLIENT VIEW **********\n\n");
		printf("*** What should I do for you? ***\n\n");
		printf("1) Show my features\n");
		printf("2) Quit\n");

		op = multiChoice("Select an option", options, 2);

		switch(op) {
			case '1':				
				show_client();
				show_phone_numbers();
				show_accepted_proposals();
				break;
			case '2':
				return;
		
				
			default:
				fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
				abort();
		}

		getchar();
	}

}
