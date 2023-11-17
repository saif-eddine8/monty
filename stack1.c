#include "monty.h"


/**
 * stack_add - Adds a node to the stack.
 * @new_node: Pointer to the new node.
 * @ln: Interger representing the line number of of the opcode.
 */
void stack_add(stack_t **new_node, __attribute__((unused))unsigned int ln)
{
	stack_t *tmp;

	if (new_node == NULL || *new_node == NULL)
		exit(EXIT_FAILURE);
	if (head == NULL)
	{
		head = *new_node;
		return;
	}
	tmp = head;
	head = *new_node;
	head->next = tmp;
	tmp->prev = head;
}


/**
 * top_print - Prints the top node of the stack.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_number: Interger representing the line number of of the opcode.
 */
void top_print(stack_t **stack, unsigned int line_number)
{
	if (stack == NULL || *stack == NULL)
		more_err(6, line_number);
	printf("%d\n", (*stack)->n);
}
/**
 * top_pop - functin Adds a node to the stack.
 * @stack: the Pointer to a pointer pointing to top node of the stack.
 * @line_number: is Interger representing the line number of of the opcode.
 */
void top_pop(stack_t **stack, unsigned int line_number)
{
        stack_t *tmp;

        if (stack == NULL || *stack == NULL)
                more_err(7, line_number);

        tmp = *stack;
        *stack = tmp->next;
        if (*stack != NULL)
                (*stack)->prev = NULL;
        free(tmp);
}
/**
 * stack_print - function that Adds a node to the stack.
 * @stack: is the Pointer to a pointer pointing to top node of the stack.
 * @line_number: the line number of  the opcode.
 */
void stack_print(stack_t **stack, unsigned int line_number)
{
        stack_t *tmp;

        (void) line_number;
        if (stack == NULL)
                exit(EXIT_FAILURE);
        tmp = *stack;
        while (tmp != NULL)
        {
                printf("%d\n", tmp->n);
                tmp = tmp->next;
        }
}
