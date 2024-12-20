#include "header.h"

void andt_loop(){
	char *line = 0, **arg = 0;
	int status;

	do {
		printf("-> ");
		line = andt_read_line();
		arg = andt_split_line(line);
		status = andt_execute(arg);

		free(line);
		free(arg);
	}while(status);
}

char *andt_read_line(void) {
	int buffsize = ANDT_RL_BUFFSIZE;
	int position = 0, c = 0;
	char *buffer = malloc(buffsize * sizeof(char));
	
	if(0 == buffer) {
	fprintf(stderr, "andt: alocare esuata\n");
	exit(EXIT_FAILURE); }

	while(1) {
		c = getchar(); //EOF - integer
		if(c == EOF || c == '\n') {	// c == -1
			buffer[position] = '\0';
			return buffer;
			} else {
				buffer[position] = c;
			}
		position++;

		if(position >= buffsize) {
			buffsize += ANDT_RL_BUFFSIZE;
			buffer = realloc(buffer, buffsize);
			if(0 == buffer) {
			fprintf(stderr, "andt: alocare esuata\n"); 
			exit(EXIT_FAILURE);
			}			
		}	
	}
}

char **andt_split_line(char *line) {
	int buffsize = ANDT_TOK_BUFFSIZE;
	int position = 0;
	char **tokens = malloc(buffsize *sizeof(char*));
	char *p;

	if(0 == tokens) {
		fprintf(stderr, "andt: alocare esuata\n'"); 
		exit(EXIT_FAILURE);
	}
	p = strtok(line, ANDT_DELIMITATORS);
	while(p) {
		tokens[position] = p;
		position++;
	
	if(position >= buffsize) {
		buffsize += ANDT_TOK_BUFFSIZE;
		tokens = realloc(tokens, buffsize * sizeof(char*));
		if(0 == tokens) {
			fprintf(stderr, "andt: alocare esuate\n");
			exit(EXIT_FAILURE);
		}
	}
	p = strtok(NULL, ANDT_DELIMITATORS);
	}
	tokens[position] = NULL;
	return tokens;
}

int andt_launch(char **arg) {
	pid_t pid, wpid;
	int status;

	pid = fork();
	if(pid == 0) {
		if(execvp(arg[0], arg) == -1) {
			perror("andt");
		}
		exit(EXIT_FAILURE);
	} else if(pid < 0) {
	perror("andt");
	} else {
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
	}while(!WIFEXITED(status) && !WIFSIGNALED(status)); }
			return 1;
}
