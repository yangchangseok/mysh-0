#include "utils.h"

#include <memory.h>	// for malloc and realloc
#include <stdlib.h>	// str* methods
#include <string.h>	// for strtok
#include <stdio.h>	// for NULL

void mysh_parse_command(
		const char* command,
        int *argc,
		char*** argv) {

	// reset number of arguments to 0
	(*argc) = 0;

	// get length of command, and add 1. last 1 is the space for '\0'
	const int command_length = strlen(command) + 1;	

	// allocate the memory space for copy of command
	// cause method:strtok's first parameter shoud be char*
	// but mysh_parse_command's first parameter is const char*
	char* copied_command = (char*) malloc(command_length * sizeof(char));

	// copy the command 
	strncpy(copied_command, command, command_length);
	
	// split the string using delimeter space, tab and newline
	const char* delim = " \t\n";

	// STRTOK -> take full string to be tokenized at first call
	char* token = strtok(copied_command, delim);

	// return NULL from the strtok at first call
	// mean the string is empty or all member of string are delim

	// so if strtok's first call return NULL, just make array of argv and push empty string:""
	// else read and copy the tokenized arg one by one
	do {

		// grow an array dinamically
		// if first argument, just malloc
		// else re-allocate the argv array
		switch (*argc) {
			case 0:		*argv = (char**) malloc(sizeof(char*));							break;
			default:	*argv = (char**) realloc(*argv, ((*argc) + 1) * sizeof(char*));	break;
		}

		// allocate the memory and copy the argument
		// then point the growed argv array
		strcpy(
			*((*argv) + (*argc)++) = (char*) malloc(token == NULL ? 1 : strlen(token)),
			token == NULL ? "" : token);

	// STRTOK -> from the second time, strtok take NULL
	// end if there is no more token, return zero
	// let's loop untill strtok return NULL...
	} while((token = strtok(NULL, delim)) != NULL);

	// return the allocated memory
	free(copied_command);
}
