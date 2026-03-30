#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VMMAX 10000
#define HACKMAX 40000

typedef struct {
    char *cmd;
    char *arg1;
    char *arg2;
} Command;

Command *parser_read_file(FILE *vm, int *count) {
    char line[75];
    Command *parsed = malloc(sizeof(Command) * VMMAX);
    int i = 0;
    
    while (fgets(line, sizeof(line), vm)) {
	char *comment = strstr(line, "//");
	if (comment != NULL) {
	    *comment = '\0';
	}
	char *command = strtok(line, " \n");
	if (command == NULL) {
	    continue;
	}

	char *arg1 = strtok(NULL, " \n");
	char *arg2 = strtok(NULL, " \n");

	parsed[i].cmd = strdup(command);
	if (arg1 == NULL) {
	    parsed[i].arg1 = NULL;
	} else {
	    parsed[i].arg1 = strdup(arg1);
	}

	if (arg2 == NULL) {
	    parsed[i].arg2 = NULL;
	} else {
	    parsed[i].arg2 = strdup(arg2);
	}

	i++;
    }

    *count = i;

    return parsed;
}

void codewriter_write(Command *vmcommands, int *commandSize, FILE *f) {

    int i = 0;
    while (i < *commandSize) {
	fprintf(f, "// %s %s %s\n", vmcommands[i].cmd, vmcommands[i].arg1, vmcommands[i].arg2);
	if (strcmp(vmcommands[i].cmd, "push") == 0) {
	    if (strcmp(vmcommands[i].arg1, "constant") == 0) {
		fprintf(f, "@%s\n", vmcommands[i].arg2);
		fprintf(f, "D=A\n");
		fprintf(f, "@SP\n");
		fprintf(f, "A=M\n");
		fprintf(f, "M=D\n");
		fprintf(f, "@SP\n");
		fprintf(f, "M=M+1\n");
	    } else if (strcmp(vmcommands[i].arg1, "local") == 0) {
		fprintf(f, "@%s\n", vmcommands[i].arg2);
		fprintf(f, "D=A\n");
		fprintf(f, "@LCL\n");
		fprintf(f, "A=D+M\n");
		fprintf(f, "D=M\n");
		fprintf(f, "@SP\n");
		fprintf(f, "A=M\n");
		fprintf(f, "M=D\n");
		fprintf(f, "@SP\n");
		fprintf(f, "M=M+1\n");
	    } else if (strcmp(vmcommands[i].arg1, "static") == 0) { //idk where static isssss
	    } else if (strcmp(vmcommands[i].arg1, "this") == 0) {
		fprintf(f, "@%s\n", vmcommands[i].arg2);
		fprintf(f, "D=A\n");
		fprintf(f, "@THIS\n");
		fprintf(f, "A=D+M\n");
		fprintf(f, "D=M\n");
		fprintf(f, "@SP\n");
		fprintf(f, "A=M\n");
		fprintf(f, "M=D\n");
		fprintf(f, "@SP\n");
		fprintf(f, "M=M+1\n");
	    } else if (strcmp(vmcommands[i].arg1, "that") == 0) { 
		fprintf(f, "@%s\n", vmcommands[i].arg2);
		fprintf(f, "D=A\n");
		fprintf(f, "@THAT\n");
		fprintf(f, "A=D+M\n");
		fprintf(f, "D=M\n");
		fprintf(f, "@SP\n");
		fprintf(f, "A=M\n");
		fprintf(f, "M=D\n");
		fprintf(f, "@SP\n");
		fprintf(f, "M=M+1\n");
	    } else if (strcmp(vmcommands[i].arg1, "pointer") == 0) { //NVM i figured it out but i have to re implement later cuz im tired
	    } else if (strcmp(vmcommands[i].arg1, "temp") == 0) { //SAme
	    } else if (strcmp(vmcommands[i].arg1, "argument") == 0) {
		fprintf(f, "@%s\n", vmcommands[i].arg2);
		fprintf(f, "D=A\n");
		fprintf(f, "@ARG\n");
		fprintf(f, "A=D+M\n");
		fprintf(f, "D=M\n");
		fprintf(f, "@SP\n");
		fprintf(f, "A=M\n");
		fprintf(f, "M=D\n");
		fprintf(f, "@SP\n");
	    } 
	}






	i++;
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
	printf("VM files or directory must be provided\n");
	return 1;
    }
    FILE *vmfile = fopen(argv[1], "r");

    if (vmfile == NULL) {
	printf("Error opening file\n");
	return 1;
    }


    int* numcommands = malloc(sizeof(int));
    Command *commandlist = parser_read_file(vmfile, numcommands);
    fclose(vmfile);

    FILE *asmfile = fopen("Test.asm", "w");
    if (asmfile == NULL) {
	printf("Error opening file\n");
	return 1;
    }

    codewriter_write(commandlist, numcommands, asmfile);

    fclose(asmfile);
    return 0;
}
