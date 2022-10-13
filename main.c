#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aux
{
    float value;
    struct aux *next;
} No;

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

No *insert_in_stack(float num, No *list)
{
    No *new = malloc(sizeof(No));

    if (new)
    {
        new->value = num;
        new->next = list;

        return new;
    }
    else
    {
        printf("Erro ao alocar memória!");
    }
    return NULL;
}

No *remove_from_stack(No **list)
{
    No *remove = NULL;

    if (*list)
    {
        remove = *list;
        *list = remove->next;
    }
    else
    {
        printf("Expressão inválida");
    }
    return remove;
}

float solve_expression(char expression[])
{
    char *element;
    float result;
    No *n1, *n2;
    No *list = NULL;
    element = strtok(expression, " ");

    // pointer[0] é um operador

    while (element != NULL)
    {
        if (element[0] == '+' || element[0] == '-' || element[0] == '*' || element[0] == '/')
        {
            n1 = remove_from_stack(&list);
            n2 = remove_from_stack(&list);
            result = operate(n2->value, n1->value, element[0]);
            list = insert_in_stack(result, list);
            free(n1);
            free(n2);
        }
        else
        {
            result = strtol(element, NULL, 10); // string to long
            list = insert_in_stack(result, list);
        }
        element = strtok(NULL, " ");
    }
    n1 = remove_from_stack(&list);
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