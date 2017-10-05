#include <string.h>

#include "commands.h"

#include <stdio.h>		// for printf
#include <unistd.h>		// for linux system call
#define BUFF_SIZE 512	// size of buffer for getcwd

int do_cd(int argc, char** argv) {
	if (!validate_cd_argv(argc, argv))
    	return -1;

	if(chdir(argv[1])== 0)	return 0;	// success to system call : chdir 
	else					return -1;	// error in chdir, can check the error number using errno.h's errno
}

int do_pwd(int argc, char** argv) {
	if (!validate_pwd_argv(argc, argv))
    	return -1;

	// declare and initialize the buffer
	// for path from getcwd system call
	char buff[BUFF_SIZE] = {0, };

	if(getcwd(buff, 512) == NULL) {
		// error in getcwd, can check the error number using errno.h's errno
		return -1;
	} else {
		// success to system call : getcwd
		printf("%s\n", buff);
		return 0;
	}
}

int validate_cd_argv(int argc, char** argv) {
	// mysh's cd can only has two argv(1:cd, 2:path)
  	return (argc == 2) && (strcmp(argv[0], "cd") == 0) ? 1 : 0;
}

int validate_pwd_argv(int argc, char** argv) {
	// mysh's pwd can only has one argv(1:pwd)
	return (argc == 1) && (strcmp(argv[0], "pwd") == 0) ? 1 : 0;
}
