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
	char label[20];
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
	
	unsigned exit_condition = 1;
	unsigned locctr;
	unsigned starting_location;
	unsigned prog_len;

	char label[20];
	char opcode[10];
	char operand[20];

	char * line = NULL;
	size_t line_len = 0;
	getline(&line, &line_len, f_src);
	if (line[0] != ';')
	{
		sscanf(line, "%s %s %s", label, opcode, operand);
		if (strcmp(opcode, "START") == 0)
		{
			sscanf(operand, "%u", &starting_location);
			locctr = starting_location;
			fputs(line, f_int);
		}
		else
		{
			starting_location = 0;
			locctr = 0;
		}
	}
	free(line);

	//To clear the symtab from the previous output
	fclose(fopen(symtab, "w"));
	
	while (exit_condition)
	{	
		if (line[0] != ';')
		{
			line = NULL;
			line_len = 0;
			getline(&line, &line_len, f_src);
			sscanf(line, "%s %s %s", label, opcode, operand);
			// printf("%s %s %s\n", label, opcode, operand);
			
			if (strcmp (opcode, "END") == 0)
			{
				prog_len = locctr - starting_location;
				fputs(line, f_int);
				fprintf(f_int, "Program Length: %d\n", prog_len);
				exit_condition = 0;
			}
			else
			{
				//Updating the Symtab
				FILE * f_symtab = (FILE *)fopen(symtab, "a+");
				if (f_symtab == NULL)
				{
					printf("Unable to open file %s\n", symtab);
					return 0;
				}
				if (strcmp("**", label) != 0)
				{
					int flag = 0;
					char *symbol;
					size_t symbol_len = 0;
					while (getline(&symbol, &symbol_len, f_symtab) != -1)
					{
						char symtab_label[20];
						unsigned symtab_location;

						sscanf(symbol, "%s %u", symtab_label, &symtab_location);
						if (strcmp(symtab_label, label) == 0)
						{
							printf("Error\nThe symbol %s is repeating\n", symtab_label);
							flag = 1;
						}

						free(symbol);
						symbol = NULL;
						symbol_len = 0;
					}
					rewind(f_symtab);
					if (flag == 1)
					{
						return 0;
					}
					else
					{
						fprintf(f_symtab, "%s %u\n", label, locctr);
					}
				}
				fclose(f_symtab);

				//Writing to intermediate file
				
			}
			
			free(line);
		}
		
	}
	
	fclose(f_src);
	fclose(f_int);
	
	free(opcodes);
	return 0;
}
