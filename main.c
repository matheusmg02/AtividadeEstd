#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct aux
{
    float value;
    struct aux *next;
} Node;

float operate(float a, float b, char operator)
{
    switch (operator)
    {
    case '+':
        return a + b;
        break;
    case '-':
        return a - b;
        break;
    case '*':
        return a * b;
        break;
    case '/':
        return a / b;
        break;

    default:
        return 0.0;
    }
}

Node *insert_in_stack(float num, Node *stack)
{
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
    {
        printf("Erro ao alocar memória!");
        return NULL;
    }
    else
    {
        new_node->value = num;
        new_node->next = stack;

        return new_node;
    }
}

// Se o nó retornado for NULL: interprte como erro
Node *remove_from_stack(Node **list)
{
    Node *last_node = NULL;

    if (*list == NULL)
    {
        printf("Erro: expressão inválida");
        return NULL;
    }
    else
    {
        last_node = *list;
        *list = last_node->next;

        return last_node;
    }
}

float solve_expression(char expression[])
{
    char *elements;
    float result;
    Node *n1, *n2;
    Node *stack = NULL;
    elements = strtok(expression, " ");

    // pointer[0] é um operador

    while (elements != NULL)
    {
        bool element_is_operator = elements[0] == '+' || elements[0] == '-' || elements[0] == '*' || elements[0] == '/';
        if (element_is_operator)
        {
            n1 = remove_from_stack(&stack);
            n2 = remove_from_stack(&stack);
            result = operate(n2->value, n1->value, elements[0]);
            stack = insert_in_stack(result, stack);
            free(n1);
            free(n2);
        }
        else
        {
            result = strtol(elements, NULL, 10); // string to long
            stack = insert_in_stack(result, stack);
        }
        elements = strtok(NULL, " ");
    }
    n1 = remove_from_stack(&stack);
    result = n1->value;
    free(n1);

    return result;
}

void main()
{
    char expression[200];
    printf("Digite aqui sua expressão posfixada: ");
    fgets(expression, 200, stdin);
    printf("\n resultado:%f\n", solve_expression(expression));
}

// "20 30 + 7 4 - 9 50 * 9 8 +"
// "20" "30 + 7 4 - 9 50 * 9 8 +"
// "20" "30" "+ 7 4 - 9 50 * 9 8 +"
// "20" "30" "+" "7 4 - 9 50 * 9 8 +"
// .......
// "20" "30" "+" "7" "4" "-" "9" "50" "*" "9" "8 +"
// "20" "30" "+" "7" "4" "-" "9" "50" "*" "9" "8" "+"
// NULL = '\0'

/*
20 30 + 7 4 - 9 50 * 9 8 + = 17

1- Criar um vetor fixo de 200
2- Pedir a expressão por usuário (em String)
3- Fazer validação
4- Retornar o resultado







*/