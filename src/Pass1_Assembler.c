#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned OPCODE_LEN = 6;
const char * symtab = "Symtab.txt";
const char * optab = "Optab.txt";
const char * src = "Source_Code.txt";
const char * int_file = "Intermediate_File.txt";

struct Pass_1
{
	char opcode[5];
};

struct Symtab
{
	label[20];
};

int main()
{
	struct Pass_1 *opcodes = (struct Pass_1 *) calloc (OPCODE_LEN, sizeof(struct Pass_1));
	
	//=============Reading the Opcode values from Opcode.txt and storing them to a struct===============
	FILE * f_optab = (FILE *)fopen(optab, "r");
	
	if (f_optab == NULL)
	{
		printf("Invalid File Name\n");
		return 0;
	}
	
	unsigned iterator = 0;
	while (!feof(f_optab) && iterator < OPCODE_LEN)
	{
		char *line = NULL;
		size_t line_len = 0;
		getline(&line, &line_len, f_optab);
		
		if (line[0] == '#')
		{
			free (line);
			continue;
		}
		else
		{
			sscanf(line, "%s", opcodes[iterator].opcode);
			//printf("%s %d\n", opcodes[iterator].opcode, opcodes[iterator].value);
			iterator++;
			free(line);
		}
		
	}
	
	fclose(f_optab);
	//=============================================END==============================================
	
	FILE * f_src = (FILE *)fopen(src, "r");
	if (f_src == NULL)
	{
		printf("Invalid File Path %s\n", src);
		return 0;
	}
	
	FILE * f_int = (FILE *)fopen(int_file, "w");
	if (f_int == NULL)
	{
		printf("Unable to open file %s\n", int_file);
		return 0;
	}
	
	//fprintf(f_int, "Hello World\n");
	//fprintf(f_int, "Good Bye\n");
	//fprintf(f_int, "Finished this problem now\n");
	
	unsigned exit_condition = 1;
	unsigned locctr = 0;
	
	while (exit_condition)
	{
		char * line = NULL;
		size_t line_len = 0;
		getline(&line, &line_len, f_src);
		
		if (line[0] != ';')
		{
			char label[20];
			char opcode[4];
			char operand[20];
			sscanf(line, "%s %s %s", label, opcode, operand);
			int flag = 0;
			if (strcmp (opcode, "START") == 0)
			{
			
			}
			else if (strcmp (opcode, "END") == 0)
			{
			
			}
			else
			{
				FILE * f_symtab = (FILE *)fopen(symtab, "r");
				if (f_symtab == NULL)
				{
					printf("Unable to open file %s\n", symtab);
					return 0;
				}
				size_t true_len = 10;
				size_t sym_len = 0;
				struct Symtab * sym = (struct Symtab *) calloc (true_len, sizeof (struct Symtab));
				while (!feof(f_symtab))
				{
					if (sym_len == true_len)
					{
						true_len += 10;
						sym = (struct Symtab *) realloc (sym, true_len * sizeof (struct Symtab));
					}
					char * sym_line = NULL;
					size_t sym_line_len = 0;
					getline(&sym_line, &sym_line_len, f_symtab);

					strcpy(sym[sym_len], sym_line);
					sym_len++;

					free(sym_line);
				}
				fclose(f_symtab);
				
				f_symtab = (FILE *) fopen(symtab, "a");
				fclose();
				
				free(sym);
			}
			
		}
		
		free(line);
	}
	
	fclose(f_src);
	fclose(f_int);
	
	free(opcodes);
	return 0;
}
