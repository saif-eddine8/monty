#include "monty.h"

/**
 * openFile - opens a file
 * @fileName: the file namepath
 * Return: void
 */

void openFile(char fileName)
{
	FILE *fileDes = fopen(fileName, "r");

	if (fileName == NULL || fileDes == NULL)
		err(2, fileName);

	readFile(fileDes);
	fclose(fileDes);
}


/**
 * readFile - reads a file
 * @fileDes: pointer to file descriptor
 * Return: void
 */

void readFile(FILE *fileDes)
{
	int lineNumber, formt = 0;
	char *buff = NULL;
	size_t len = 0;

	for (lineNumber = 1; getline(&buff, &len, fileDes) != -1; lineNumber++)
	{
		formt = parseLine(buff, lineNumber, formt);
	}
	free(buff);
}


/**
 * parseLine - Separates each line into tokens to determine
 * which function to call
 * @buff: line from the file
 * @lineNumber: line number
 * @formt:  storage formt. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 * Return: Returns 0 if the opcode is stack. 1 if queue.
 */

int parseLine(char *buff, int lineNumber, int formt)
{
	char *opcode, *value;
	const char *delimiter = "\n ";

	if (buff == NULL)
		err(4);

	opcode = strtok(buff, delimiter);
	if (opcode == NULL)
		return (formt);
	value = strtok(NULL, delimiter);

	if (strcmp(opcode, "stack") == 0)
		return (0);
	if (strcmp(opcode, "queue") == 0)
		return (1);

	findFunction(opcode, value, lineNumber, formt);
	return (formt);
}

/**
 * findFunction - find the appropriate function for the opcode
 * @opcode: opcode
 * @value: argument of opcode
 * @formt:  storage formt. If 0 Nodes will be entered as a stack.
 * @ln: line number
 * if 1 nodes will be entered as a queue.
 * Return: void
 */
void findFunction(char *opcode, char *value, int ln, int formt)
{
	int i;
	int flag;

	instruction_t func_list[] = {
		{"push", add_to_stack},
		{"pall", print_stack},
		{"pint", print_top},
		{"pop", pop_top},
		{"nop", nop},
		{"swap", swap_nodes},
		{"add", add_nodes},
		{"sub", sub_nodes},
		{"div", div_nodes},
		{"mul", mul_nodes},
		{"mod", mod_nodes},
		{"pchar", print_char},
		{"pstr", print_str},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	for (flag = 1, i = 0; func_list[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, func_list[i].opcode) == 0)
		{
			callFunc(func_list[i].f, opcode, value, ln, formt);
			flag = 0;
		}
	}
	if (flag == 1)
		err(3, ln, opcode);
}


/**
 * callFunc - Calls the required function.
 * @func: Pointer to the function that is about to be called.
 * @op: string representing the opcode.
 * @val: string representing a numeric value.
 * @ln: line numeber for the instruction.
 * @formt: Format specifier. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 */
void callFunc(op_func func, char *op, char *val, int ln, int formt)
{
	stack_t *node;
	int flag;
	int i;

	flag = 1;
	if (strcmp(op, "push") == 0)
	{
		if (val != NULL && val[0] == '-')
		{
			val = val + 1;
			flag = -1;
		}
		if (val == NULL)
			err(5, ln);
		for (i = 0; val[i] != '\0'; i++)
		{
			if (isdigit(val[i]) == 0)
				err(5, ln);
		}
		node = create_node(atoi(val) * flag);
		if (formt == 0)
			func(&node, ln);
		if (formt == 1)
			add_to_queue(&node, ln);
	}
	else
		func(&head, ln);
}
