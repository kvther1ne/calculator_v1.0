#include "calc.h"

//-------------------------------------ЛЕКСЕМЫ-------------------------------------
void number(char *lex, char *PN, int *pn_iter) {
  int lex_lenght = strlen(lex);
  for (int i = 0; i < lex_lenght; i++) {
    PN[*pn_iter] = lex[i];
    *pn_iter += 1;
  }
  PN[*pn_iter] = ' ';
  *pn_iter += 1;
}

int operand(char *lex, char *PN, Stack **stack, int *i,
            int *open_brackets_counter) {
  int c = *lex;
  if ((char)c == '(' || strchr("stcoiarlg", (char)c) != NULL) {
    (*open_brackets_counter)++;
    push(stack, (int)c);
    return 0;
  } else {
    if (empty(*stack) && (char)c != ')') {
      push(stack, (int)c);
      return 0;
    }
    if ((char)c == ')') {
      if (*open_brackets_counter != 0) {
        brackets(PN, stack, i);
        (*open_brackets_counter)--;
        return 0;
      } else {
        return 1;
      }
    }
  }
  while (
      priority((char)c) < priority((char)peek(*stack)) ||
      (priority((char)c) == priority((char)peek(*stack)) && (char)c != '^')) {
    PN[*i] = (char)peek(*stack);
    *i += 1;
    PN[*i] = ' ';
    *i += 1;
    pop(stack);
    if (*stack == NULL) {
      break;
    }
  }
  push(stack, (int)c);
  return 0;
}

void brackets(char *PN, Stack **stack, int *i) {
  while ((char)peek(*stack) != '(' &&
         strchr("stcoiarlg", (char)peek(*stack)) == NULL) {
    PN[*i] = (char)peek(*stack);
    *i += 1;
    PN[*i] = ' ';
    *i += 1;
    pop(stack);
  }
  if (strchr("stcoiarlg", (char)peek(*stack)) != NULL) {
    PN[*i] = (char)peek(*stack);
    *i += 1;
    PN[*i] = ' ';
    *i += 1;
  }
  pop(stack);
}

int priority(char c) {
  int ans = 0;
  if (c == '(') {
    ans = -1;
  } else if (c == 's' || c == 'c' || c == 't' || c == 'o' || c == 'i' ||
             c == 'a' || c == 'r' || c == 'l' || c == 'g') {
    ans = 0;
  } else if (c == '+' || c == '-') {
    ans = 1;
  } else if (c == '*' || c == '/' || c == 'm') {
    ans = 2;
  } else if (c == '^') {
    ans = 3;
  } else if (c == '~' || c == '!') {
    ans = 4;
  }
  return ans;
}

//-------------------------------------ПАРСЕР-------------------------------------
int parsing(char *str, char *pars) {
  int noerr = 1;
  int i = 0, j = 0;
  if (str[i] == '-') {
    add(pars, '~', &i, &j, 1, 2);
  } else if (str[i] == '+') {
    add(pars, '!', &i, &j, 1, 2);
  }
  parsing_helper(str, pars, &i, &j, &noerr);
  if (noerr) {
    pars[j] = '\0';
  }
  pars[j] = '\0';
  return noerr;
}

void parsing_helper(char *str, char *pars, int *i, int *j, int *noerr) {
  while (str[*i] != '\0' && *noerr) {
    switch (str[*i]) {
      case '*':
        add(pars, str[*i], i, j, 1, 2);
        break;
      case '/':
        add(pars, str[*i], i, j, 1, 2);
        break;
      case '(':
        add(pars, str[*i], i, j, 1, 2);
        break;
      case ')':
        add(pars, str[*i], i, j, 1, 2);
        break;
      case '^':
        add(pars, str[*i], i, j, 1, 2);
        break;
      case 'x':
        add(pars, str[*i], i, j, 1, 2);
        break;
      default:
        composite_parser(str, pars, i, j, noerr);
        break;
    }
  }
}

void composite_parser(char *str, char *pars, int *i, int *j, int *noerr) {
  if (str[*i] == '-' && str[*i - 1] == '(') {
    add(pars, '~', i, j, 1, 2);
  } else if (str[*i] == '+' && str[*i - 1] == '(') {
    add(pars, '!', i, j, 1, 2);
  } else if (str[*i] == '-') {
    add(pars, '-', i, j, 1, 2);
  } else if (str[*i] == '+') {
    add(pars, '+', i, j, 1, 2);
  } else if (str[*i] == 's' && str[*i + 1] == 'q' && str[*i + 2] == 'r' &&
             str[*i + 3] == 't' && str[*i + 4] == '(') {  // sqrt()
    add(pars, 'r', i, j, 5, 2);
  } else if (str[*i] == 's' && str[*i + 1] == 'i' && str[*i + 2] == 'n' &&
             str[*i + 3] == '(') {  // sin()
    add(pars, 's', i, j, 4, 2);
  } else if (str[*i] == 'c' && str[*i + 1] == 'o' && str[*i + 2] == 's' &&
             str[*i + 3] == '(') {  // cos()
    add(pars, 'c', i, j, 4, 2);
  } else if (str[*i] == 't' && str[*i + 1] == 'a' && str[*i + 2] == 'n' &&
             str[*i + 3] == '(') {  // tan()
    add(pars, 't', i, j, 4, 2);
  } else if (str[*i] == 'a' && str[*i + 1] == 'c' && str[*i + 2] == 'o' &&
             str[*i + 3] == 's' && str[*i + 4] == '(') {  // acos()
    add(pars, 'o', i, j, 5, 2);
  } else if (str[*i] == 'a' && str[*i + 1] == 's' && str[*i + 2] == 'i' &&
             str[*i + 3] == 'n' && str[*i + 4] == '(') {  // asin()
    add(pars, 'i', i, j, 5, 2);
  } else if (str[*i] == 'a' && str[*i + 1] == 't' && str[*i + 2] == 'a' &&
             str[*i + 3] == 'n' && str[*i + 4] == '(') {  // atan()
    add(pars, 'a', i, j, 5, 2);
  } else if (str[*i] == 'l' && str[*i + 1] == 'n' &&
             str[*i + 2] == '(') {  // ln()
    add(pars, 'l', i, j, 3, 2);
  } else if (str[*i] == 'l' && str[*i + 1] == 'o' && str[*i + 2] == 'g' &&
             str[*i + 3] == '(') {  // log()
    add(pars, 'g', i, j, 4, 2);
  } else if (str[*i] == 'm' && str[*i + 1] == 'o' &&
             str[*i + 2] == 'd') {  // mod
    add(pars, 'm', i, j, 3, 2);
  } else if ((str[*i] >= '0' && str[*i] <= '9') ||
             str[*i] == '.') {  // числа или точка
    num_parcer(str, pars, i, j, noerr);
  } else {
    *noerr = 0;
  }
}

void num_parcer(char *str, char *pars, int *i, int *j, int *noerr) {
  int pnt = 0;
  do {
    pars[*j] = str[*i];
    if (str[*i] == '.') {
      pnt++;
    }
    (*i)++;
    (*j)++;
  } while ((str[*i] >= '0' && str[*i] <= '9') || str[*i] == '.');
  pars[*j] = ' ';
  (*j)++;
  if (pnt > 1) {
    *noerr = 0;
  }
}

void add(char *pars, char symb, int *i, int *j, int i_add, int j_add) {
  pars[*j] = symb;
  pars[*j + 1] = ' ';
  *i += i_add;
  *j += j_add;
}

//-------------------------------------СТЕК-------------------------------------
void push(Stack **head, double value) {
  Stack *node = malloc(sizeof(Stack));
  node->next = *head;
  node->value = value;
  *head = node;
}

int pop(Stack **head) {
  Stack *out;
  double value;
  if ((*head)->next != NULL) {
    out = *head;
    *head = (*head)->next;
    value = out->value;
    free(out);
  } else {
    out = *head;
    *head = NULL;
    free(out);
  }
  return value;
}

double peek(Stack *head) { return head->value; }

void free_stack(Stack **head) {
  while (*head != NULL) {
    Stack *tmp = (*head)->next;
    free(*head);
    *head = tmp;
  }
}
int empty(Stack *head) { return head == NULL; }

void printStack(Stack *head) {
  while (head) {
    printf("%f \n", head->value);
    head = head->next;
  }
}