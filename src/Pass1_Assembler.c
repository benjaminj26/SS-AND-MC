#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned OPCODE_LEN = 6;
const char * symtab = "Symtab.txt";
const char * optab = "Optab.txt";
const char * src = "Source_Code.txt";
const char * int_file = "Intermediate_File.txt";

int main()
{	
	FILE * f_optab = (FILE *)fopen(optab, "r");
	
	if (f_optab == NULL)
	{
		printf("Invalid File Name\n");
		return 0;
	}
	
	
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
		sscanf(line, "%s %s %s\n", label, opcode, operand);
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
			fprintf(f_int, "%u %s %s %s\n", locctr, label, opcode, operand);
		}
	}
	free(line);

	//To clear the symtab from the previous output
	fclose(fopen(symtab, "w"));
	
	while (exit_condition)
	{
		line = NULL;
		line_len = 0;
		if (getline(&line, &line_len, f_src) == -1)
		{
			exit_condition = 0;
			continue;
		}
		if (line[0] != ';')
		{
			sscanf(line, "%s %s %s\n", label, opcode, operand);
			//Writing to intermediate file
			fprintf(f_int, "%u %s %s %s\n", locctr, label, opcode, operand);
			
			if (strcmp (opcode, "END") == 0)
			{
				prog_len = locctr - starting_location;
				fprintf(f_int, "Program Length: %u\n", prog_len);
				exit_condition = 0;
			}
			else
			{
				//Updating the Symtab
				FILE * f_symtab = (FILE *)fopen(symtab, "r+");
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
							break;
						}

						free(symbol);
						symbol = NULL;
						symbol_len = 0;
					}
					if (flag == 1)
					{
						exit_condition = 1;
						fclose(f_symtab);
						free(line);
						continue;
					}
					else
					{
						fseek(f_symtab, 0, SEEK_END);
						fprintf(f_symtab, "%s %u\n", label, locctr);
					}

				}
				char temp_opcode[10];
				unsigned obj_code;
				char flag = 0;
				char *temp_line = NULL;
				size_t temp_len = 0;
				while (getline(&temp_line, &temp_len, f_optab) != -1)
				{
					sscanf(temp_line, "%s %u\n", temp_opcode, &obj_code);
					if (strcmp(temp_opcode, opcode) == 0)
					{
						locctr += 3;
						flag = 1;
						break;
					}
					free(temp_line);
					temp_line = NULL;
					temp_len = 0;
				}
				if (flag == 0)
				{
					if (strcmp(opcode, "WORD") == 0)
					{
						locctr += 3;
					}
					else if (strcmp(opcode, "RESW") == 0)
					{
						locctr += 3 * atoi(operand);
					}
					else if (strcmp(opcode, "RESB") == 0)
					{
						locctr += atoi(operand);
					}
					else if (strcmp(opcode, "BYTE") == 0)
					{
						//To exclude the single quotes and character 'C'
						locctr += (strlen(operand) - 3);
					}
					else
					{
						printf("Invalid Opcode: %s\n", opcode);
						exit_condition = 0;
					}
				}
				fclose(f_symtab);				
			}
			
			free(line);
		}
		
	}
	
	fclose(f_src);
	fclose(f_int);
	fclose(f_optab);

	return 0;
}
