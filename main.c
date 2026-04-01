#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

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
	char *command = strtok(line, " \n\r\t");
	if (command == NULL) {
	    continue;
	}

	char *arg1 = strtok(NULL, " \n\r\t");
	char *arg2 = strtok(NULL, " \n\r\t");

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

void codewriter_write(Command *vmcommands, int *commandSize, FILE *f, char *fname) {

    int label = 0;
    int i = 0;
    while (i < *commandSize) {
	if (strcmp(vmcommands[i].cmd, "push") == 0) {
	    if (strcmp(vmcommands[i].arg1, "constant") == 0) {
	    	fprintf(f, "// %s %s %s\n", vmcommands[i].cmd, vmcommands[i].arg1, vmcommands[i].arg2);
		fprintf(f, "@%s\n", vmcommands[i].arg2);
		fprintf(f, "D=A\n");
		fprintf(f, "@SP\n");
		fprintf(f, "A=M\n");
		fprintf(f, "M=D\n");
		fprintf(f, "@SP\n");
		fprintf(f, "M=M+1\n");
	    } else if (strcmp(vmcommands[i].arg1, "local") == 0) {
	    	fprintf(f, "// %s %s %s\n", vmcommands[i].cmd, vmcommands[i].arg1, vmcommands[i].arg2);
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
	    } else if (strcmp(vmcommands[i].arg1, "static") == 0) {
	    	fprintf(f, "// %s %s %s\n", vmcommands[i].cmd, vmcommands[i].arg1, vmcommands[i].arg2);
		fprintf(f, "@%s.%s\n", fname, vmcommands[i].arg2);
		fprintf(f, "D=M\n");
		fprintf(f, "@SP\n");
		fprintf(f, "A=M\n");
		fprintf(f, "M=D\n");
		fprintf(f, "@SP\n");
		fprintf(f, "M=M+1\n");
	    } else if (strcmp(vmcommands[i].arg1, "this") == 0) {
	    	fprintf(f, "// %s %s %s\n", vmcommands[i].cmd, vmcommands[i].arg1, vmcommands[i].arg2);
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
	    	fprintf(f, "// %s %s %s\n", vmcommands[i].cmd, vmcommands[i].arg1, vmcommands[i].arg2);
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
	    } else if (strcmp(vmcommands[i].arg1, "pointer") == 0) { 
	    	fprintf(f, "// %s %s %s\n", vmcommands[i].cmd, vmcommands[i].arg1, vmcommands[i].arg2);
		fprintf(f, "@%s\n", vmcommands[i].arg2);
		fprintf(f, "D=A\n");
		fprintf(f, "@3\n");
		fprintf(f, "A=D+A\n");
		fprintf(f, "D=M\n");
		fprintf(f, "@SP\n");
		fprintf(f, "A=M\n");
		fprintf(f, "M=D\n");
		fprintf(f, "@SP\n");
		fprintf(f, "M=M+1\n");
	    } else if (strcmp(vmcommands[i].arg1, "temp") == 0) {
	    	fprintf(f, "// %s %s %s\n", vmcommands[i].cmd, vmcommands[i].arg1, vmcommands[i].arg2);
		fprintf(f, "@%s\n", vmcommands[i].arg2);
		fprintf(f, "D=A\n");
		fprintf(f, "@5\n");
		fprintf(f, "A=D+A\n");
		fprintf(f, "D=M\n");
		fprintf(f, "@SP\n");
		fprintf(f, "A=M\n");
		fprintf(f, "M=D\n");
		fprintf(f, "@SP\n");
		fprintf(f, "M=M+1\n");
	    } else if (strcmp(vmcommands[i].arg1, "argument") == 0) {
	    	fprintf(f, "// %s %s %s\n", vmcommands[i].cmd, vmcommands[i].arg1, vmcommands[i].arg2);
		fprintf(f, "@%s\n", vmcommands[i].arg2);
		fprintf(f, "D=A\n");
		fprintf(f, "@ARG\n");
		fprintf(f, "A=D+M\n");
		fprintf(f, "D=M\n");
		fprintf(f, "@SP\n");
		fprintf(f, "A=M\n");
		fprintf(f, "M=D\n");
		fprintf(f, "@SP\n");
		fprintf(f, "M=M+1\n");
	    }
	} else if (strcmp(vmcommands[i].cmd, "pop") == 0) {
	    if (strcmp(vmcommands[i].arg1, "local") == 0) {
	    	fprintf(f, "// %s %s %s\n", vmcommands[i].cmd, vmcommands[i].arg1, vmcommands[i].arg2);
		fprintf(f, "@%s\n", vmcommands[i].arg2);
		fprintf(f, "D=A\n");
		fprintf(f, "@LCL\n");
		fprintf(f, "D=D+M\n");
		fprintf(f, "@R14\n"); //essentially we use R14 as a pseudo D register
		fprintf(f, "M=D\n");
		fprintf(f, "@SP\n");
		fprintf(f, "AM=M-1\n"); //move the stack pointer down 1 and put the value there into D
		fprintf(f, "D=M\n");
		fprintf(f, "@R14\n");
		fprintf(f, "A=M\n"); //earlier we stored the address of the local register in R14
		fprintf(f, "M=D\n"); //set that address (in local) to the value we got off the stack
	    } else if (strcmp(vmcommands[i].arg1, "static") == 0) {
	    	fprintf(f, "// %s %s %s\n", vmcommands[i].cmd, vmcommands[i].arg1, vmcommands[i].arg2);
		fprintf(f, "@SP\n");
		fprintf(f, "AM=M-1\n");
		fprintf(f, "D=M\n");
		fprintf(f, "@%s.%s\n", fname, vmcommands[i].arg2);
		fprintf(f, "M=D\n");
	    } else if (strcmp(vmcommands[i].arg1, "this") == 0) {
	    	fprintf(f, "// %s %s %s\n", vmcommands[i].cmd, vmcommands[i].arg1, vmcommands[i].arg2);
		fprintf(f, "@%s\n", vmcommands[i].arg2);
		fprintf(f, "D=A\n");
		fprintf(f, "@THIS\n");
		fprintf(f, "D=D+M\n");
		fprintf(f, "@R14\n"); //essentially we use R14 as a pseudo D register
		fprintf(f, "M=D\n");
		fprintf(f, "@SP\n");
		fprintf(f, "AM=M-1\n"); //move the stack pointer down 1 and put the value there into D
		fprintf(f, "D=M\n");
		fprintf(f, "@R14\n");
		fprintf(f, "A=M\n"); //earlier we stored the address of the local register in R14
		fprintf(f, "M=D\n"); //set that address (in local) to the value we got off the stack
	    } else if (strcmp(vmcommands[i].arg1, "that") == 0) { 
	    	fprintf(f, "// %s %s %s\n", vmcommands[i].cmd, vmcommands[i].arg1, vmcommands[i].arg2);
		fprintf(f, "@%s\n", vmcommands[i].arg2);
		fprintf(f, "D=A\n");
		fprintf(f, "@THAT\n");
		fprintf(f, "D=D+M\n");
		fprintf(f, "@R14\n"); //essentially we use R14 as a pseudo D register
		fprintf(f, "M=D\n");
		fprintf(f, "@SP\n");
		fprintf(f, "AM=M-1\n"); //move the stack pointer down 1 and put the value there into D
		fprintf(f, "D=M\n");
		fprintf(f, "@R14\n");
		fprintf(f, "A=M\n"); //earlier we stored the address of the local register in R14
		fprintf(f, "M=D\n"); //set that address (in local) to the value we got off the stack
	    } else if (strcmp(vmcommands[i].arg1, "pointer") == 0) {
	    	fprintf(f, "// %s %s %s\n", vmcommands[i].cmd, vmcommands[i].arg1, vmcommands[i].arg2);
		fprintf(f, "@%s\n", vmcommands[i].arg2);
		fprintf(f, "D=A\n");
		fprintf(f, "@3\n");
		fprintf(f, "D=D+A\n");
		fprintf(f, "@R14\n"); //essentially we use R14 as a pseudo D register
		fprintf(f, "M=D\n");
		fprintf(f, "@SP\n");
		fprintf(f, "AM=M-1\n"); //move the stack pointer down 1 and put the value there into D
		fprintf(f, "D=M\n");
		fprintf(f, "@R14\n");
		fprintf(f, "A=M\n"); //earlier we stored the address of the local register in R14
		fprintf(f, "M=D\n"); //set that address (in local) to the value we got off the stack
	    } else if (strcmp(vmcommands[i].arg1, "temp") == 0) {
	    	fprintf(f, "// %s %s %s\n", vmcommands[i].cmd, vmcommands[i].arg1, vmcommands[i].arg2);
		fprintf(f, "@%s\n", vmcommands[i].arg2);
		fprintf(f, "D=A\n");
		fprintf(f, "@5\n");
		fprintf(f, "D=D+A\n");
		fprintf(f, "@R14\n"); //essentially we use R14 as a pseudo D register
		fprintf(f, "M=D\n");
		fprintf(f, "@SP\n");
		fprintf(f, "AM=M-1\n"); //move the stack pointer down 1 and put the value there into D
		fprintf(f, "D=M\n");
		fprintf(f, "@R14\n");
		fprintf(f, "A=M\n"); //earlier we stored the address of the local register in R14
		fprintf(f, "M=D\n"); //set that address (in local) to the value we got off the stack
	    } else if (strcmp(vmcommands[i].arg1, "argument") == 0) {
	    	fprintf(f, "// %s %s %s\n", vmcommands[i].cmd, vmcommands[i].arg1, vmcommands[i].arg2);
		fprintf(f, "@%s\n", vmcommands[i].arg2);
		fprintf(f, "D=A\n");
		fprintf(f, "@ARG\n");
		fprintf(f, "D=D+M\n");
		fprintf(f, "@R14\n"); //essentially we use R14 as a pseudo D register
		fprintf(f, "M=D\n");
		fprintf(f, "@SP\n");
		fprintf(f, "AM=M-1\n"); //move the stack pointer down 1 and put the value there into D
		fprintf(f, "D=M\n");
		fprintf(f, "@R14\n");
		fprintf(f, "A=M\n"); //earlier we stored the address of the local register in R14
		fprintf(f, "M=D\n"); //set that address (in local) to the value we got off the stack
	    }
	} else if (strcmp(vmcommands[i].cmd, "add") == 0) {
	    fprintf(f, "// %s\n", vmcommands[i].cmd);
	    fprintf(f, "@SP\n");
	    fprintf(f, "AM=M-1\n");
	    fprintf(f, "D=M\n");
	    fprintf(f, "@SP\n");
	    fprintf(f, "A=M-1\n");
	    fprintf(f, "M=D+M\n");
	} else if (strcmp(vmcommands[i].cmd, "sub") == 0) {
	    fprintf(f, "// %s\n", vmcommands[i].cmd);
	    fprintf(f, "@SP\n");
	    fprintf(f, "AM=M-1\n");
	    fprintf(f, "D=M\n");
	    fprintf(f, "@SP\n");
	    fprintf(f, "A=M-1\n");
	    fprintf(f, "M=M-D\n");
	} else if (strcmp(vmcommands[i].cmd, "neg") == 0) {
	    fprintf(f, "// %s\n", vmcommands[i].cmd);
	    fprintf(f, "@SP\n");
	    fprintf(f, "A=M-1\n");
	    fprintf(f, "M=-M\n");
	} else if (strcmp(vmcommands[i].cmd, "eq") == 0) {
	    fprintf(f, "// %s\n", vmcommands[i].cmd);
	    fprintf(f, "@SP\n");
	    fprintf(f, "AM=M-1\n");
	    fprintf(f, "D=M\n");
	    fprintf(f, "@SP\n");
	    fprintf(f, "A=M-1\n");
	    fprintf(f, "D=D-M\n");
	    fprintf(f, "M=-1\n");
	    fprintf(f, "@trueeq%d\n", label);
	    fprintf(f, "D;JEQ\n");
	    fprintf(f, "@SP\n");
	    fprintf(f, "A=M-1\n");
	    fprintf(f, "M=0\n");
	    fprintf(f, "(trueeq%d)\n", label);
	    label++;
	} else if (strcmp(vmcommands[i].cmd, "gt") == 0) {
	    fprintf(f, "// %s\n", vmcommands[i].cmd);
	    fprintf(f, "@SP\n");
	    fprintf(f, "AM=M-1\n");
	    fprintf(f, "D=M\n");
	    fprintf(f, "@SP\n");
	    fprintf(f, "A=M-1\n");
	    fprintf(f, "D=M-D\n");
	    fprintf(f, "M=-1\n");
	    fprintf(f, "@truegt%d\n", label);
	    fprintf(f, "D;JGT\n");
	    fprintf(f, "@SP\n");
	    fprintf(f, "A=M-1\n");
	    fprintf(f, "M=0\n");
	    fprintf(f, "(truegt%d)\n", label);
	    label++;
	} else if (strcmp(vmcommands[i].cmd, "lt") == 0) {
	    fprintf(f, "// %s\n", vmcommands[i].cmd);
	    fprintf(f, "@SP\n");
	    fprintf(f, "AM=M-1\n");
	    fprintf(f, "D=M\n");
	    fprintf(f, "@SP\n");
	    fprintf(f, "A=M-1\n");
	    fprintf(f, "D=M-D\n");
	    fprintf(f, "M=-1\n");
	    fprintf(f, "@truelt%d\n", label);
	    fprintf(f, "D;JLT\n");
	    fprintf(f, "@SP\n");
	    fprintf(f, "A=M-1\n");
	    fprintf(f, "M=0\n");
	    fprintf(f, "(truelt%d)\n", label);
	    label++;
	} else if (strcmp(vmcommands[i].cmd, "and") == 0) {
	    fprintf(f, "// %s\n", vmcommands[i].cmd);
	    fprintf(f, "@SP\n");
	    fprintf(f, "AM=M-1\n");
	    fprintf(f, "D=M\n");
	    fprintf(f, "@SP\n");
	    fprintf(f, "A=M-1\n");
	    fprintf(f, "M=D&M\n");
	} else if (strcmp(vmcommands[i].cmd, "or") == 0) {
	    fprintf(f, "// %s\n", vmcommands[i].cmd);
	    fprintf(f, "@SP\n");
	    fprintf(f, "AM=M-1\n");
	    fprintf(f, "D=M\n");
	    fprintf(f, "@SP\n");
	    fprintf(f, "A=M-1\n");
	    fprintf(f, "M=D|M\n");
	} else if (strcmp(vmcommands[i].cmd, "not") == 0) {
	    fprintf(f, "// %s\n", vmcommands[i].cmd);
	    fprintf(f, "@SP\n");
	    fprintf(f, "A=M-1\n");
	    fprintf(f, "M=!M\n");
	} 
	i++;
    }
}

int main(int argc, char **argv) {
    
    if (argc < 2) {
	printf("VM files or directory must be provided\n");
	return 1;
    }

    char *cpy= strdup(argv[1]);
    char *baseName = strtok(cpy, ".");
    char *ext = strtok(NULL, ".");
    char *asmName = malloc(strlen(baseName) + 5);

    strcpy(asmName, baseName);
    strcat(asmName, ".asm");

    if (ext == NULL) {
	DIR *vmdir = opendir(baseName);
	struct dirent *entry;


	if (vmdir == NULL) {
	    printf("failed to open directory!\n");
	    return 1;
	}

	FILE **files = malloc(sizeof(FILE*)*100);
	int numFiles = 0;
	while ((entry = readdir(vmdir)) != NULL) {
	    char path[4096];
	    snprintf(path, sizeof(path), "%s/%s", baseName, entry->d_name);
	    struct stat st;
	    if (stat(path, &st) == -1) {
		printf("stat error\n");
		continue;
	    }


	    if (S_ISREG(st.st_mode)) {
		files[numFiles] = fopen(path, "r");
		if (files[numFiles] == NULL) {
		    printf("Failed to open file %s", path);
		    return 1;
		}
		numFiles++;
	    }  
	}

	closedir(vmdir);

	FILE *asmfile = fopen(asmName, "w");
	if (asmfile == NULL) {
	    printf("Error opening file\n");
	    return 1;
	}

	for (int i = 0; i < numFiles; i++) {
	    int* numcommands = malloc(sizeof(int));
	    Command *cmdlist = parser_read_file(*(files + i), numcommands);

	    codewriter_write(cmdlist, numcommands, asmfile, baseName);
	    for (int j = 0; j < *numcommands; j++) {
		free(cmdlist[j].cmd);
		free(cmdlist[j].arg1);
		free(cmdlist[j].arg2);
	    }
	    free(cmdlist);
	    free(numcommands);
	    fclose(files[i]);
	}
	fclose(asmfile);
	free(files);
    } else if (strcmp(ext, "vm") == 0) {
	FILE *vmfile = fopen(argv[1], "r");

	if (vmfile == NULL) {
	    printf("Error opening file\n");
	    return 1;
	}

	int* numcommands = malloc(sizeof(int));
	Command *commandlist = parser_read_file(vmfile, numcommands);
	fclose(vmfile);

	FILE *asmfile = fopen(asmName, "w");
	if (asmfile == NULL) {
	    printf("Error opening file\n");
	    return 1;
	}

	codewriter_write(commandlist, numcommands, asmfile, baseName);
	fclose(asmfile);

	for (int i = 0; i < *numcommands; i++) {
	    free(commandlist[i].cmd);
	    free(commandlist[i].arg1);
	    free(commandlist[i].arg2);
	}
	free(commandlist);
	free(numcommands);

    } else {
	printf("Must provide directory of vm files or single vm file\n");
	return 1;
    }

    free(asmName);
    free(cpy);
    return 0;
}
