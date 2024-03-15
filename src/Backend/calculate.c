#include "calculator.h"
double calculate(Node** stack) {
  Node* current = *stack;
  Node* operandStack = initializeList();
  Node * tmp;
  while (current != NULL) {
    if (current->type == number) {
      push_to_stack(&operandStack, current->value, current->priority,
                    current->type);
    } else {
      double result = 0, operand1, operand2;
      if (current->type == sinn || current->type == coss ||
          current->type == tann || current->type == acoss ||
          current->type == asinn || current->type == atann ||
          current->type == sqr || current->type == lnn ||
          current->type == logg) {
        tmp = operandStack;
        operand2 = operandStack->value;
        operandStack = operandStack->next;
        free(tmp);
      } else {
        tmp = operandStack;
        operand2 = operandStack->value;
        operandStack = operandStack->next;
        free(tmp);
        tmp = operandStack;
        operand1 = operandStack->value;
        operandStack = operandStack->next;
        free(tmp);
      }

      switch (current->type) {
        case logg:
          result = log10(operand2);
          break;
        case lnn:
          result = log(operand2);
          break;
        case sqr:
          result = sqrt(operand2);
          break;
        case atann:
          result = atan(operand2);
          break;
        case asinn:
          result = asin(operand2);
          break;
        case tann:
          result = tan(operand2);
          break;
        case acoss:
          result = acos(operand2);
          break;
        case sinn:
          result = sin(operand2);
          break;
        case coss:
          result = cos(operand2);
          break;
        case plus:
          result = operand1 + operand2;
          break;
        case minus:
          result = operand1 - operand2;
          break;
        case mul:
          result = operand1 * operand2;
          break;
        case divv:
          result = operand1 / operand2;
          break;
        case poww:
          result = pow(operand1, operand2);
          break;
        case mod:
          result = fmod(operand1, operand2);
          break;
        default:
          printf("Error: unknown operation\n");
          break;
      }
      push_to_stack(&operandStack, result, 0, number);
    }
    tmp = current;
    current = current->next;
    free(tmp);
  }
  tmp = operandStack;
  double finalResult = operandStack->value;
  free(tmp);
  //printf("\n%lf\n", finalResult);
  return finalResult;
}

double calculate_string(char* string, double x) {
  Node* src = initializeList();
  Node* dst = initializeList();
  Node* rpn = initializeList();
  convertToLexemes(string, &src, x);
  reverse_node(src, &dst);
  Node* pn = translation_into_polish_notation(dst);
  reverse_node(pn, &rpn);
  double result = calculate(&rpn);
  return result;
}