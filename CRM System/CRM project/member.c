#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"

void add_client( MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[10];
	
	char cf_client[16];
	char cf_operator[16];
	char name[45];
	char surname[45];
	char email[45];
	char address[45];
	char fax[45];
	int num_phone;
	MYSQL_TIME date;
	
	
	
	//Get paramenters
	printf("\nClient CF: ");
	getInput(16, cf_client, false);
	printf("\nOperatore CF: ");
	getInput(16, cf_operator, false);
	printf("\nClient name: ");
	getInput(45, name, false);
	printf("\nClient surname: ");
	getInput(45, surname, false);
	printf("\nClient email: ");
	getInput(45, email, false);
	printf("\nClient address: ");
	getInput(45, address, false);
	printf("\nClient fax: ");
	getInput(45, fax, false);
	
	printf("\nDate: \n");
	printf("\nYear: ");
	scanf("%d", &(date.year) );
	printf("\nMonth: ");
	scanf("%d", &(date.month) );
	printf("\nDay: ");
	scanf("%d", &(date.day) );
	
	printf("\nPhone number: ");
	scanf("%d", &num_phone );
	
	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call inserisci_cliente(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize client insertion statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = cf_client;
	param[0].buffer_length = strlen(cf_client);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = name;
	param[1].buffer_length = strlen(name);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[2].buffer = surname;
	param[2].buffer_length = strlen(surname);

	param[3].buffer_type = MYSQL_TYPE_VAR_STRING; 
	param[3].buffer = email;
	param[3].buffer_length = strlen(email);
	
	param[4].buffer_type = MYSQL_TYPE_VAR_STRING; 
	param[4].buffer = address;
	param[4].buffer_length = strlen(address);
	
	param[5].buffer_type = MYSQL_TYPE_VAR_STRING; 
	param[5].buffer = fax;
	param[5].buffer_length = strlen(fax);
	
	param[6].buffer_type = MYSQL_TYPE_DATE; 
	param[6].buffer = &date;
	param[6].buffer_length = sizeof(date);
	
	param[7].buffer_type = MYSQL_TYPE_LONG; 
	param[7].buffer = &num_phone;
	param[7].buffer_length = sizeof(num_phone);
	
	param[8].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[8].buffer = cf_operator;
	param[8].buffer_length = strlen(cf_operator);
		
	param[9].buffer_type = MYSQL_TYPE_VAR_STRING; 
	param[9].buffer = cf;
	param[9].buffer_length = strlen(cf);
	
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for client insertion\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "An error occurred while adding the client.");
		goto out;
	}

	printf("Client %s correctly added!\n", cf_client);

    out:
	mysql_stmt_close(prepared_stmt);
	
}

void add_company_client( MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[12];
	
	char cf_client[16];
	char cf_operator[16];
	char name[45];
	char surname[45];
	char email[45];
	char address[45];
	char fax[45];
	char company_name[45];
	char iva[45];
	int num_phone;
	MYSQL_TIME date;
	
	
	
	//Get paramenters
	printf("\nClient CF: ");
	getInput(16, cf_client, false);
	printf("\nOperatore CF: ");
	getInput(16, cf_operator, false);
	printf("\nClient name: ");
	getInput(45, name, false);
	printf("\nClient surname: ");
	getInput(45, surname, false);
	printf("\nClient email: ");
	getInput(45, email, false);
	printf("\nClient address: ");
	getInput(45, address, false);
	printf("\nClient fax: ");
	getInput(45, fax, false);
	printf("\nPartita IVA: ");
	getInput(45, iva, false);
	printf("\nCompany name: ");
	getInput(45, company_name, false);
	
	printf("\nDate: \n");
	printf("\nYear: ");
	scanf("%d", &(date.year) );
	printf("\nMonth: ");
	scanf("%d", &(date.month) );
	printf("\nDay: ");
	scanf("%d", &(date.day) );
	
	printf("\nPhone number: ");
	scanf("%d", &num_phone );
	
	
	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call inserisci_cliente_societa(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize client insertion statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = cf_client;
	param[0].buffer_length = strlen(cf_client);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = name;
	param[1].buffer_length = strlen(name);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[2].buffer = surname;
	param[2].buffer_length = strlen(surname);

	param[3].buffer_type = MYSQL_TYPE_VAR_STRING; 
	param[3].buffer = email;
	param[3].buffer_length = strlen(email);
	
	param[4].buffer_type = MYSQL_TYPE_VAR_STRING; 
	param[4].buffer = address;
	param[4].buffer_length = strlen(address);
	
	param[5].buffer_type = MYSQL_TYPE_VAR_STRING; 
	param[5].buffer = fax;
	param[5].buffer_length = strlen(fax);
	
	param[6].buffer_type = MYSQL_TYPE_DATE; 
	param[6].buffer = &date;
	param[6].buffer_length = sizeof(date);
	
	param[7].buffer_type = MYSQL_TYPE_LONG; 
	param[7].buffer = &num_phone;
	param[7].buffer_length = sizeof(num_phone);
	
	param[8].buffer_type = MYSQL_TYPE_VAR_STRING; 
	param[8].buffer = iva;
	param[8].buffer_length = strlen(iva);
	
	param[9].buffer_type = MYSQL_TYPE_VAR_STRING; 
	param[9].buffer = company_name;
	param[9].buffer_length = strlen(company_name);
	
	param[10].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[10].buffer = cf_operator;
	param[10].buffer_length = strlen(cf_operator);
		
	param[11].buffer_type = MYSQL_TYPE_VAR_STRING; 
	param[11].buffer = cf;
	param[11].buffer_length = strlen(cf);
	
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for client insertion\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "An error occurred while adding the client.");
		goto out;
	}

	printf("Company contact %s correctly added!\n", cf_client);

    out:
	mysql_stmt_close(prepared_stmt);
	
}

void start_member_view(MYSQL *conn){
	
	char options[3] = {'1','2','3'};
	char op;
	
	printf("Welcome in the system!\n");

	if(!parse_config("users/membro settore commerciale.json", &conf)) {
		fprintf(stderr, "Unable to load member configuration\n");
		exit(EXIT_FAILURE);
	}

	if(mysql_change_user(conn, conf.db_username, conf.db_password, conf.database)) {
		fprintf(stderr, "mysql_change_user() failed\n");
		exit(EXIT_FAILURE);
	}
	printf("\033[2J\033[H");
	while(1) {
		
		printf("*** What should I do for you? ***\n\n");
		printf("1) Add new client\n");
		printf("2) Add new company contact\n");
		printf("3) Quit\n");

		op = multiChoice("Select an option", options, 3);

		switch(op) {
			case '1':
				add_client(conn);
				break;
			case '2':
				add_company_client(conn);
				break;
			case '3':
				printf("Exit\n");
				return;
		
				
			default:
				fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
				abort();
		}

		getchar();
	}
	
	
}
