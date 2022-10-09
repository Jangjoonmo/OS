/**********************************************************************
 * Copyright (c) 2021-2022
 *  Sang-Hoon Kim <sanghoonkim@ajou.ac.kr>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTIABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>

#include <string.h>

#include "types.h"
#include "list_head.h"
#include "parser.h"

/***********************************************************************
 * struct list_head history
 *
 * DESCRIPTION
 *   Use this list_head to store unlimited command history.
 */
extern struct list_head history;

struct entry{
	int index;
	char *string;
	struct list_head list;
};

char name[MAX_TOKEN_LEN];
int timeout;
pid_t pid;
int status;

int process_command(char * command);

/***********************************************************************
 * run_command()
 *
 * DESCRIPTION
 *   Implement the specified shell features here using the parsed
 *   command tokens.
 *
 * RETURN VALUE
 *   Return 1 on successful command execution
 *   Return 0 when user inputs "exit"
 *   Return <0 on error
 */

// char* findEntry(int i){
// 	struct entry* pos;
	
// 	int k=0;
// 	for (pos = list_first_entry(&history, __typeof__(*pos), list);k<i;k++){
// 		pos = list_next_entry(pos, list);
// 	}

// 	return pos->string;
// }

void timeout_handler (int sin){
	fprintf(stderr, "%s is timed out\n", name);
	kill(pid, SIGKILL);
}

struct sigaction sa = {
	.sa_handler = timeout_handler,
	.sa_flags = 0,
}, old_sa;

int run_command(int nr_tokens, char * const tokens[])
{	
	strcpy(name, tokens[0]);

	if (strncmp(tokens[0], "exit", strlen("exit")) == 0) return 0;

		else if(strcmp(tokens[0], "cd")==0){//cd command
			if(nr_tokens == 1){
			chdir(getenv("HOME"));
			}
			else if (strncmp(tokens[1], "~", strlen("~")) == 0){
				chdir(getenv("HOME"));
			}
			else{
				chdir(tokens[1]);
			}
			}

		else if(strcmp(tokens[0], "history")==0){//history command
			struct entry* new;
			int index = 0;
			list_for_each_entry(new, &history, list){
				fprintf(stderr, "%2d: %s", index, new->string);
				index++;
			}
			return 1;
		}

		else if(strcmp(tokens[0], "!")==0){//! <number> history
			// char index[MAX_COMMAND_LEN];
			struct entry* new;
			int index = 0;
			list_for_each_entry(new, &history, list){
				if(index == atoi(tokens[1])){
					int x = 0;
					char *new_tokens[MAX_NR_TOKENS] = {NULL};
					char* new_cmd = malloc(MAX_COMMAND_LEN);
					strcpy(new_cmd, new->string);
					parse_command(new_cmd, &x, new_tokens);
					run_command(x, new_tokens);
					return 1;
				}
				else
			index++;
			}
			
			return 1;
		}

		else if(strcmp(tokens[0],"timeout")==0){//timeout
		if(nr_tokens == 1){
			fprintf(stderr, "Current timeout is %d seconds\n", timeout);
		}
		else{
			timeout = (atoi(tokens[1]));
			if(timeout == 0){
				fprintf(stderr, "Timeout is disabled\n");
			}
			else if (timeout>=2){
				fprintf(stderr, "Timeout is set to %d seconds\n", timeout);
			}
			else
				fprintf(stderr, "Timeout is set to %d second\n", timeout);

		}
		}

		else{//external command

			pid = fork();
			if(pid > 0){
				status = 0;
				sigaction(SIGALRM, &sa, &old_sa);
				alarm(timeout);
				waitpid(pid, &status, 0);
			}
			else if (pid == 0){
 				if(execvp(tokens[0],tokens)==-1){	//에러 메시지
				fprintf(stderr, "Unable to execute %s\n", tokens[0]);
				 return -1;
				}
			}
		}
			
	if(strcmp(tokens[0],"sleep")==0){
		if(timeout<atoi(tokens[1])){
			alarm(timeout);
		}
	}
	if(strcmp(tokens[0],"./toy")==0){
		if(strcmp(tokens[1],"zzz")==0){
			if(timeout<atoi(tokens[2])){
				alarm(timeout);
			}
		}
	}
	
	alarm(0);
	return 1;

}


/***********************************************************************
 * append_history()
 *
 * DESCRIPTION
 *   Append @command into the history. The appended command can be later
 *   recalled with "!" built-in command
 */
void append_history(char * const command)
{
	struct entry *cmd = (struct entry*)malloc(sizeof(struct entry));
	
	if (cmd != NULL){
		list_add_tail(&cmd->list, &history);
		cmd->string = (char *)malloc(MAX_COMMAND_LEN);
		if(cmd->string != NULL){
			strcpy(cmd->string,command);
		}
	}

}


/***********************************************************************
 * initialize()
 *
 * DESCRIPTION
 *   Call-back function for your own initialization code. It is OK to
 *   leave blank if you don't need any initialization.
 *
 * RETURN VALUE
 *   Return 0 on successful initialization.
 *   Return other value on error, which leads the program to exit.
 */
int initialize(int argc, char * const argv[])
{
	 timeout = 2;

	return 0;
}


/***********************************************************************
 * finalize()
 *
 * DESCRIPTION
 *   Callback function for finalizing your code. Like @initialize(),
 *   you may leave this function blank.
 */
void finalize(int argc, char * const argv[])
{

}


/***********************************************************************
 * process_command(command)
 *
 * DESCRIPTION
 *   Process @command as instructed.
 */
int process_command(char * command)
{

	char *tokens[MAX_NR_TOKENS] = { NULL };
	int nr_tokens = 0;

	if (parse_command(command, &nr_tokens, tokens) == 0)
		return 1;

	return run_command(nr_tokens, tokens);
}