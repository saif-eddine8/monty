#include "monty.h"

/**
 * char_print - that Prints the Ascii value.
 * @stack:is the Pointer to a pointer pointing to top node of the stack.
 * @line_number: is the Interger representing the line number of of the opcode.
 */
void char_print(stack_t **stack, unsigned int line_number)
{
	int ascii;

	if (stack == NULL || *stack == NULL)
		string_err(11, line_number);

	ascii = (*stack)->n;
	if (ascii < 0 || ascii > 127)
		string_err(10, line_number);
	printf("%c\n", ascii);
}


/**
 * rot_l - functin that Rotates the last node of the stack to the top.
 * @stack: is Pointer to a pointer pointing to top node of the stack.
 * @ln: is the Interger representing the line number of of the opcode.
 */
void rot_l(stack_t **stack, __attribute__((unused))unsigned int ln)
{
	stack_t *tmp;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		return;

	tmp = *stack;

	while (tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = *stack;
	tmp->prev->next = NULL;
	tmp->prev = NULL;
	(*stack)->prev = tmp;
	(*stack) = tmp;
}
/**
 * rot_f - is the Rotates the first node of the stack to the bottom.
 * @stack: the Pointer to a pointer pointing to top node of the stack.
 * @ln: the Interger representing the line number of of the opcode.
 */
void rot_f(stack_t **stack, __attribute__((unused))unsigned int ln)
{
        stack_t *tmp;

        if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
                return;

        tmp = *stack;
        while (tmp->next != NULL)
                tmp = tmp->next;

        tmp->next = *stack;
        (*stack)->prev = tmp;
        *stack = (*stack)->next;
        (*stack)->prev->next = NULL;
        (*stack)->prev = NULL;
}

/**
 * str_print - function that Prints a string.
 * @stack: is the Pointer to a pointer pointing to top node of the stack.
 * @ln: the Interger representing the line number of of the opcode.
 */
void str_print(stack_t **stack, __attribute__((unused))unsigned int ln)
{
        int ascii;
        stack_t *tmp;

        if (stack == NULL || *stack == NULL)
        {
                printf("\n");
                return;
        }

        tmp = *stack;
        while (tmp != NULL)
        {
                ascii = tmp->n;
                if (ascii <= 0 || ascii > 127)
                        break;
                printf("%c", ascii);
                tmp = tmp->next;
        }
        printf("\n");
}
