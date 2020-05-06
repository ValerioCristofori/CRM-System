#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"


void add_operator(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[4];
	
	char cf_operator[16];
	char name[45];
	char surname[45];
	
	printf("%s", cf);
	//Get paramenters
	printf("\nOperator CF: ");
	getInput(16, cf_operator, false);
	printf("\nOperator name: ");
	getInput(45, name, false);
	printf("\nOperator surname: ");
	getInput(45, surname, false);
	
	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call inserisci_operatore(?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize operator insertion statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = cf_operator;
	param[0].buffer_length = strlen(cf_operator);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = name;
	param[1].buffer_length = strlen(name);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[2].buffer = surname;
	param[2].buffer_length = strlen(surname);
	
	param[3].buffer_type = MYSQL_TYPE_VAR_STRING; 
	param[3].buffer = cf;
	param[3].buffer_length = strlen(cf);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for operator insertion\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "An error occurred while adding the operator.");
		goto out;
	}

	printf("Operator %s correctly added!\n", cf_operator);

    out:
	mysql_stmt_close(prepared_stmt);
	
}


void add_proposal(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[3];
	
	char code[45];
	char description[100];
	
	//Get paramenters
	printf("\nProposal's code: ");
	getInput(45, code, false);
	printf("\nInsert a description for this proposal: \n");
	getInput(100, description, false);
	
	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call inserisci_proposta(?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize proposal insertion statement\n", false);
	}
	
	memset(param, 0, sizeof(param));
	
	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = code;
	param[0].buffer_length = strlen(code);
	
	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = description;
	param[1].buffer_length = strlen(description);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING; 
	param[2].buffer = cf;
	param[2].buffer_length = strlen(cf);
	
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for proposal insertion\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "An error occurred while adding the proposal.");
		goto out;
	}

	printf("Proposal %s correctly added!\n", code);

    out:
	mysql_stmt_close(prepared_stmt);
}


void archive_proposal(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];
	
	char code[45];

	//Get paramenters
	printf("\nProposal's code you want to archive: ");
	getInput(45, code, false);
	
	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call archivia_proposta(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize proposal archive statement\n", false);
	}
	
	memset(param, 0, sizeof(param));
	
	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = code;
	param[0].buffer_length = strlen(code);
	
	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = cf;
	param[1].buffer_length = strlen(cf);
	
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for proposal archive\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "An error occurred while archiving the proposal.");
		goto out;
	}

	printf("Proposal %s correctly archived\n", code);

    out:
	mysql_stmt_close(prepared_stmt);
	
}


void start_manager_view(MYSQL *conn){
	
	char options[4] = {'1','2','3','4'};
	char op;
	
	printf("Welcome in the system!\n");

	if(!parse_config("users/manager.json", &conf)) {
		fprintf(stderr, "Unable to load manager configuration\n");
		exit(EXIT_FAILURE);
	}

	if(mysql_change_user(conn, conf.db_username, conf.db_password, conf.database)) {
		fprintf(stderr, "mysql_change_user() failed\n");
		exit(EXIT_FAILURE);
	}
	printf("\033[2J\033[H");
	while(1) {
		printf("*** What should I do for you? ***\n\n");
		printf("1) Add new operator\n");
		printf("2) Add new business proposal\n");
		printf("3) Archive a business proposal\n");
		printf("4) Quit\n");

		op = multiChoice("Select an option", options, 4);

		switch(op) {
			case '1':
				add_operator(conn);
				break;
			case '2':
				add_proposal(conn);
				break;
			case '3':
				archive_proposal(conn);
				break;
			case '4':
				printf("Exit\n");
				return;
		
				
			default:
				fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
				abort();
		}

		getchar();
	}
	
}
