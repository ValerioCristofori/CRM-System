/*
 * 
 ************** OPERATOR MAIN ***************** 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"

void add_appointment(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[6];
	
	int num_sala;
	char address[45];
	MYSQL_TIME date;
	date.second_part = 0;
	char cf_client[16];
	char codice_proposta[45];
	
	
	//Get paramenters
	
	printf("\nClient's CF: ");
	getInput(16, cf_client, false);
	printf("\nProposal code: ");
	getInput(45, codice_proposta, false);
	printf("\nAddress : ");
	getInput(45, address, false);
	printf("\nNumber sala: ");
	scanf("%d", &num_sala);
	
	bzero(&date, sizeof(MYSQL_TIME));	//init struct MYSQL_TIME
	date.time_type = MYSQL_TYPE_DATETIME;
	
	printf("\nDate: \n");
	printf("\nYear: ");
	scanf("%d", &(date.year) );
	printf("\nMonth: ");
	scanf("%d", &(date.month) );
	printf("\nDay: ");
	scanf("%d", &(date.day) );
	
	
	
	printf("\nTime: \n");
	printf("\nHour: ");
	scanf("%d", &(date.hour) );
	printf("\nMinute: ");
	scanf("%d", &(date.minute) );
	
	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call inserisci_appuntamento(?, ?, ?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize operator insertion statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_LONG;		 	//IN
	param[0].buffer = &num_sala;
	param[0].buffer_length = sizeof(num_sala);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;	//IN
	param[1].buffer = address;
	param[1].buffer_length = strlen(address);

	param[2].buffer_type = MYSQL_TYPE_DATETIME;		//IN
	param[2].buffer = (char *)&date;
	param[2].buffer_length = sizeof(date);
	param[2].is_null=0;
	
	param[3].buffer_type = MYSQL_TYPE_VAR_STRING;	//IN
	param[3].buffer = cf_client;
	param[3].buffer_length = strlen(cf_client);

	param[4].buffer_type = MYSQL_TYPE_VAR_STRING;	//IN
	param[4].buffer = cf;
	param[4].buffer_length = strlen(cf);

	param[5].buffer_type = MYSQL_TYPE_VAR_STRING; 	//IN
	param[5].buffer = codice_proposta;
	param[5].buffer_length = strlen(codice_proposta);


	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for appointment insertion\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "An error occurred while adding the appointment.");
		goto out;
	}

	printf("Appointment correctly added!\n");

    out:
	mysql_stmt_close(prepared_stmt);

}

void show_appointments(){
	MYSQL *conn;
	conn = connection_db();
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	
	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_appuntamenti(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize operator display statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;	//IN
	param[0].buffer = cf;
	param[0].buffer_length = strlen(cf);


	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for appointments display\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "An error occurred while display the appointments.");
		goto out;
	}
	
	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nList of appointments assigned to you");
	
	
	out:
	mysql_stmt_close(prepared_stmt);

}

void add_conversation(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[3];
	
	
	char cf_client[16];
	char note[100];
	
	
	//Get paramenters
	printf("\nClient's CF : ");
	getInput(45, cf_client, false);
	printf("\nNote: \n");
	getInput(100, note, false);

	
	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call inserisci_conversazione(?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize operator insertion statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;	//IN
	param[0].buffer = cf_client;
	param[0].buffer_length = strlen(cf_client);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;	//IN
	param[1].buffer = cf;
	param[1].buffer_length = strlen(cf);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING;	//IN
	param[2].buffer = note;
	param[2].buffer_length = strlen(note);



	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for conversation insertion\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "An error occurred while adding the conversation.");
		goto out;
	}

	printf("Conversation correctly added!\n");

    out:
	mysql_stmt_close(prepared_stmt);

}

void edit_note(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[4];
	
	
	char cf_client[16];
	char note[100];
	int num = 0;
	
	//Get paramenters
	printf("\nClient's CF : ");
	getInput(45, cf_client, false);
	printf("\nNote: \n");
	getInput(100, note, false);
	printf("\nConversation number: \n");
	scanf("%d", &num);

	
	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call modifica_nota_conversazione(?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize operator modification statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;	//IN
	param[0].buffer = cf_client;
	param[0].buffer_length = strlen(cf_client);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;	//IN
	param[1].buffer = cf;
	param[1].buffer_length = strlen(cf);
	
	param[2].buffer_type = MYSQL_TYPE_LONG;			//IN
	param[2].buffer = &num;
	param[2].buffer_length = sizeof(num);
	
	param[3].buffer_type = MYSQL_TYPE_VAR_STRING;	//IN
	param[3].buffer = note;
	param[3].buffer_length = strlen(note);



	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for conversation modification\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "An error occurred while modifing the conversation.");
		goto out;
	}

	printf("Conversation correctly modified!\n");

    out:
	mysql_stmt_close(prepared_stmt);

}

void delete_note(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[3];
	
	
	char cf_client[16];
	int num = 0;
	
	//Get paramenters
	printf("\nClient's CF : ");
	getInput(45, cf_client, false);
	printf("\nConversation number: \n");
	scanf("%d", &num);

	
	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call elimina_nota_conversazione(?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize operator modification statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;	//IN
	param[0].buffer = cf_client;
	param[0].buffer_length = strlen(cf_client);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;	//IN
	param[1].buffer = cf;	
	param[1].buffer_length = strlen(cf);
	
	param[2].buffer_type = MYSQL_TYPE_LONG;			//IN
	param[2].buffer = &num;
	param[2].buffer_length = sizeof(num);




	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for conversation modification\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "An error occurred while modifing the conversation.");
		goto out;
	}

	printf("Conversation correctly modified!\n");

    out:
	mysql_stmt_close(prepared_stmt);

}

void show_list(){
	MYSQL *conn;
	conn = connection_db();
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	
	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_elenco_clienti(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize operator display statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;	//IN
	param[0].buffer = cf;
	param[0].buffer_length = strlen(cf);


	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for clients display\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "An error occurred while display the clients.");
		goto out;
	}
	
	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nList of clients assigned to you");
	
	
	out:
	mysql_stmt_close(prepared_stmt);
}

void get_phone(char *cf_client){
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

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;	//IN
	param[0].buffer = cf_client;
	param[0].buffer_length = strlen(cf_client);

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

void get_proposals(char *cf_client){
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
	param[0].buffer = cf_client;
	param[0].buffer_length = strlen(cf_client);
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

void show_client_features(){
	MYSQL *conn;
	conn = connection_db();
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	
	char cf_client[16];
	
	printf("\nClient CF: ");
	getInput(16, cf_client, false);
	
	
	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_cliente(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize client statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;	//IN
	param[0].buffer = cf_client;
	param[0].buffer_length = strlen(cf_client);

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
	
	get_phone(cf_client);
	get_proposals(cf_client);
	
	out:
	mysql_stmt_close(prepared_stmt);
	
}

void add_accepted_proposal(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];
	
	
	char cf_client[16];
	char proposal_code[45];
	
	
	//Get paramenters
	printf("\nClient CF: ");
	getInput(16, cf_client, false);
	printf("\nProposal code: \n");
	getInput(45, proposal_code, false);

	
	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call inserisci_proposta_accettata(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize accepted proposal insertion statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;	//IN
	param[0].buffer = cf_client;
	param[0].buffer_length = strlen(cf_client);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;	//IN
	param[1].buffer = proposal_code;
	param[1].buffer_length = strlen(proposal_code);

	



	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for accepted proposal insertion\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "An error occurred while adding the accepted proposal.");
		goto out;
	}

	printf("Accepted proposal correctly added!\n");

    out:
	mysql_stmt_close(prepared_stmt);

}


void add_managment(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];
	
	
	char cf_client[16];
	
	
	//Get paramenters
	printf("\nClient CF: ");
	getInput(16, cf_client, false);


	
	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call inserisci_gestione_cliente(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize managment insertion statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;	//IN
	param[0].buffer = cf_client;
	param[0].buffer_length = strlen(cf_client);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;	//IN
	param[1].buffer = cf;
	param[1].buffer_length = strlen(cf);

	



	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for managment insertion\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "An error occurred while adding the managment.");
		goto out;
	}

	printf("Managment with %s correctly added!\n", cf_client);

    out:
	mysql_stmt_close(prepared_stmt);
}


void show_conversations(){
	MYSQL *conn;
	conn = connection_db();
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
	
	
	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_conversazioni(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize operator statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;	//IN
	param[0].buffer = cf;
	param[0].buffer_length = strlen(cf);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for conversations report\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "An error occurred while retrieving the conversations report.");
		goto out;
	}
	
	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nConversations");
	
	out:
	mysql_stmt_close(prepared_stmt);
	

}

void start_operator_view(MYSQL *conn){
	
	char options[11] = {'0', '1','2','3','4','5','6','7','8','9','a'};
	char op;
	
	printf("Welcome in the system!\n");

	if(!parse_config("users/operatore.json", &conf)) {
		fprintf(stderr, "Unable to load operator configuration\n");
		exit(EXIT_FAILURE);
	}

	if(mysql_change_user(conn, conf.db_username, conf.db_password, conf.database)) {
		fprintf(stderr, "mysql_change_user() failed\n");
		exit(EXIT_FAILURE);
	}
	printf("\033[2J\033[H");
	while(1) {
		printf("********* OPERATOR VIEW *********\n\n");
		printf("*** What should I do for you? ***\n\n");
		printf("0) Enter appointment\n");
		printf("1) Show appointments\n");
		printf("2) Enter conversation\n");
		printf("3) Edit conversation note\n");
		printf("4) Delete conversation note\n");
		printf("5) Show clients list\n");
		printf("6) Show client features\n");
		printf("7) Enter accepted proposal\n");
		printf("8) Show your conversations\n");
		printf("9) Enter client's managment\n");
		printf("a) Quit\n");

		op = multiChoice("Select an option", options, 11);

		switch(op) {
			case '0':
				add_appointment(conn);
				break;
			case '1':
				show_appointments();
				break;
			case '2':
				add_conversation(conn);
				break;
			case '3':
				edit_note(conn);
				break;
			case '4':
				delete_note(conn);
				break;
			case '5':
				show_list();
				break;
			case '6':
				show_client_features();
				break;
			case '7':
				add_accepted_proposal(conn);
				break;
			case '8':
				show_conversations();
				break;
			case '9':
				add_managment(conn);
				break;
			case 'a':
				return;
		
				
			default:
				fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
				abort();
		}

		getchar();
	}
	
}
