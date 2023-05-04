#include "calc.h"

// int main(void) {
//   double res = 0;
//   const char *a = malloc(100 * sizeof(char));
//   char *aboba = "x^x";
//   strcpy((char *)a, aboba);
//   int aaa = SmartCalculator(a, &res, 5);
//   free((void *)a);
//   return 0;
// }

int SmartCalculator(const char *str, double *result, double x) {
  setlocale(LC_ALL, "en_GB");
  Stack *stack = NULL, *calc = NULL;
  char parsed[4096] = {0}, PN[4096] = {0}, string_res[4096] = {0};
  char *string = NULL;
  string = malloc(1000 * sizeof(char));
  strcpy(string, str);
  int i = 0, x_counter = 0;
  while (string[i] != '\0') {
    if (string[i] == 'x') {
      x_counter++;
    }
    i++;
  }
  if (x_counter != 0) {
    char *pointer = NULL;
    char buff[50];
    sprintf(buff, "%f", x);
    if (*str == 'x') {
      strcat(string_res, buff);
      pointer = strtok(string + 1, "x");
      x_counter--;
    } else {
      pointer = strtok(string, "x");
    }
    while (x_counter) {
      strcat(string_res, pointer);
      if (x < 0) strcat(string_res, "(");
      strcat(string_res, buff);
      if (x < 0) strcat(string_res, ")");
      pointer = strtok(NULL, "x");
      x_counter--;
    }
    if (pointer != NULL) {
      strcat(string_res, pointer);
    }
  } else {
    strcat(string_res, string);
  }
  char *lex, *sep = " ";
  int ans_len = 0, pn_iter = 0, rtrn = 0, ans_op = 0, open_br_count = 0;
  ans_len = parsing(string_res, parsed);
  if (ans_len == 0) {
    printf("Error1234\n");
  }

  lex = strtok(parsed, sep);
  while (lex != NULL) {
    if ((*lex >= '0' && *lex <= '9') || *lex == '.') {
      number(lex, PN, &pn_iter);
    } else {
      ans_op = operand(lex, PN, &stack, &pn_iter, &open_br_count);
    }
    lex = strtok(NULL, sep);
  }
  if (open_br_count != 0) {
    return 1;
  }
  while (stack != NULL && ans_op != 1) {
    PN[pn_iter] = (char)peek(stack);
    pn_iter += 1;
    PN[pn_iter] = ' ';
    pn_iter += 1;
    pop(&stack);
  }
  PN[strlen(PN)] = '\0';
  rtrn = calculate(PN, &calc);

  if (rtrn == 1) {
    *result = S21_NAN;
    free_stack(&calc);
    free(string);
    return 1;
  }
  *result = calc->value;

  free_stack(&calc);
  free(string);

  return 0;
}

int calculate(char *PN, Stack **numbers) {
  char *lexema = NULL;
  char *sep = " ";
  lexema = strtok(PN, sep);
  while (lexema != NULL) {
    if ((*lexema >= '0' && *lexema <= '9') || *lexema == '.') {
      push(numbers, strtod(lexema, NULL));
    } else {
      if ((char)(*lexema) == '~') {
        double temp = peek(*numbers) * (-1);
        pop(numbers);
        push(numbers, temp);
      } else if (strchr("+-*/^m", *lexema) != NULL) {
        binary_op(numbers, lexema);
      } else if (strchr("stcoiarlg", *lexema) != NULL) {
        int func_ans = functions(numbers, lexema);
        if (func_ans == 1) {
          return 1;
        }
      }
    }
    lexema = strtok(NULL, sep);
  }
  return 0;
}

int functions(Stack **numbers, char *func) {
  double number = peek(*numbers);
  pop(numbers);
  double ans = 0;
  int flag = 0;
  switch (*func) {
    case 's':
      ans = sin(number);
      push(numbers, ans);
      break;
    case 'c':
      ans = cos(number);
      push(numbers, ans);
      break;
    case 't':
      ans = tan(number);
      push(numbers, ans);
      break;
    case 'o':
      ans = acos(number);
      push(numbers, ans);
      break;
    case 'i':
      ans = asin(number);
      push(numbers, ans);
      break;
    case 'a':
      ans = atan(number);
      push(numbers, ans);
      break;
    case 'r':
      if (number < 0) {
        flag = 1;
        break;
      }
      ans = sqrt(number);
      push(numbers, ans);
      break;
    case 'l':
      ans = log(number);
      push(numbers, ans);
      break;
    case 'g':
      ans = log10(number);
      push(numbers, ans);
      break;
  }
  return flag;
}

void binary_op(Stack **numbers, char *oper) {
  double second = peek(*numbers);
  pop(numbers);
  double first = peek(*numbers);
  pop(numbers);
  double ans = 0;
  switch (*oper) {
    case '+':
      ans = first + second;
      push(numbers, ans);
      break;
    case '-':
      ans = first - second;
      push(numbers, ans);
      break;
    case '*':
      ans = first * second;
      push(numbers, ans);
      break;
    case '/':
      ans = first / second;
      push(numbers, ans);
      break;
    case '^':
      ans = pow(first, second);
      push(numbers, ans);
      break;
    case 'm':
      ans = fmod(first, second);
      push(numbers, ans);
      break;
  }
}