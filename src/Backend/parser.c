#include "calculator.h"
#include <math.h>

int isOperator(char op) {
  switch (op) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
    case '%':
    case 'c':
    case 's':
    case 't':
    case 'a':
    case 'l':
    case 'p':
    case 'x':
      return 1;
    default:
      return 0;
  }
}

int getPriority(char op) {
  switch (op) {
    case '+':
    case '-':
      return 1;
    case '*':
    case '/':
    case '%':
      return 2;
    case '^':
    case 'r':
      return 3;
    case 'c':
    case 's':
    case 't':
    case 'a':
    case 'l':
      return 4;
    case '(':
    case ')':
      return 5;
    default:
      return 0;
  }
}

void convertToLexemes(char *input, Node **stack, double x) {
  int len = strlen(input);
  for (int i = 0; i < len; i++) {
    if ((input[i] >= '0' && input[i] <= '9')) {
      // Если текущий символ является числом или десятичной точкой, считываем
      // его значение до конца и кладем в стек
      double value = 0;
      bool dec_num = false;
      int cnt = 0;
      while ((input[i] >= '0' && input[i] <= '9') || input[i] == '.' ||
             input[i] == ',') {
        if (input[i] == ',' || input[i] == '.') {
          dec_num = true;
        } else {
          value = value * 10 + (input[i] - '0');
          if (dec_num) {
            cnt++;
          }
        }
        i++;
      }
      // Если число десятичное, меняем его знак у счетчика и делаем десятичное
      if (dec_num) {
        value = value * pow(10, -cnt);
      }
      // Помещаем лексему в стек с типом "число" и приоритетом 0
      push_to_stack(stack, value, 0, number);
      i--;
    } else if (isOperator(input[i])) {
      // Если текущий символ является оператором, считываем его и записываем в
      // стек с соответствующим типом и приоритетом
      switch (input[i]) {
        case 'x':
          push_to_stack(stack, x, 0, number);
          break;
        case 'p':
          if (input[i + 1] == 'i') push_to_stack(stack, M_PI, 0, number);
          break;
        case '+':
          if (is_empty(*stack)) {
            push_to_stack(stack, 0.0, 0, number);
          } else if (input[i - 1] == '(') {
            push_to_stack(stack, 0.0, 0, number);
          }
          push_to_stack(stack, 0.0, getPriority('+'), plus);
          break;
        case '-':
          if (is_empty(*stack)) {
            push_to_stack(stack, 0.0, 0, number);
          } else if (input[i - 1] == '(') {
            push_to_stack(stack, 0.0, 0, number);
          }
          push_to_stack(stack, 0.0, getPriority('-'), minus);
          break;
        case '*':
          push_to_stack(stack, 0.0, getPriority('*'), mul);
          break;
        case '/':
          push_to_stack(stack, 0.0, getPriority('/'), divv);
          break;
        case '^':
          push_to_stack(stack, 0.0, getPriority('^'), poww);
          break;
        case '%':
          push_to_stack(stack, 0.0, getPriority('%'), mod);
          break;
        case 'c':
          if (input[i + 1] == 'o' && input[i + 2] == 's') {
            push_to_stack(stack, 0.0, getPriority('c'), coss);
            i += 2;
          }
          break;
        case 's':
          if (input[i + 1] == 'i' && input[i + 2] == 'n') {
            push_to_stack(stack, 0.0, getPriority('s'), sinn);
            i += 2;
          } else if (input[i + 1] == 'q' && input[i + 2] == 'r' &&
                     input[i + 3] == 't') {
            push_to_stack(stack, 0.0, getPriority('r'), sqr);
          }
          break;
        case 't':
          if (input[i + 1] == 'a' && input[i + 2] == 'n') {
            push_to_stack(stack, 0.0, getPriority('t'), tann);
            i += 2;
          }
          break;
        case 'a':
          if (input[i + 1] == 's' && input[i + 2] == 'i' &&
              input[i + 3] == 'n') {
            push_to_stack(stack, 0.0, getPriority('a'), asinn);
            i += 3;
          } else if (input[i + 1] == 'c' && input[i + 2] == 'o' &&
                     input[i + 3] == 's') {
            push_to_stack(stack, 0.0, getPriority('a'), acoss);
            i += 3;
          } else if (input[i + 1] == 't' && input[i + 2] == 'a' &&
                     input[i + 3] == 'n') {
            push_to_stack(stack, 0.0, getPriority('a'), atann);
            i += 3;
          }
          break;
        case 'l':
          if (input[i + 1] == 'n') {
            push_to_stack(stack, 0.0, getPriority('l'), lnn);
            i++;
          } else if (input[i + 1] == 'o' && input[i + 2] == 'g') {
            push_to_stack(stack, 0.0, getPriority('l'), logg);
            i += 2;
          }
          break;
      }
    } else if (input[i] == '(') {
      // Если текущий символ является открывающей скобкой, кладем его в стек
      push_to_stack(stack, 0.0, getPriority('('), open_bracket);
    } else if (input[i] == ')') {
      push_to_stack(stack, 0.0, getPriority(')'), close_bracket);
    }
  }
}