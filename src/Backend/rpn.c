#include "calculator.h"

Node* translation_into_polish_notation(Node* reversed_node) {
  Node* operators = initializeList();
  Node* rpn = initializeList();
  while (reversed_node != NULL) {
    //Ситуация когда в перевернутом стеке попалось число
    if (reversed_node->type == 0)
    {
      push_to_stack(&rpn, reversed_node->value, reversed_node->priority,
                    reversed_node->type);
    } else if (reversed_node->priority != 0) { //Cитуация когда в перевернутом стеке попался оператор
      if (reversed_node->type == 19) {  //Встретилась закрывающая скобка
        while (operators->type != 18) {
          push_to_stack(&rpn, operators->value, operators->priority,
                        operators->type);
          Node* tmp = operators;
          operators = tmp->next;
          free(tmp);
        }
        free(pop(&operators));
      }
      // Ситуация когда приоритетность оператора выше чем у последнего оператора
      // в стеке operators
      else if (operators != NULL &&
               reversed_node->priority > operators->priority) {
        push_to_stack(&operators, reversed_node->value, reversed_node->priority,
                      reversed_node->type);
        // Ситуация когда приоритетность оператора ниже или равна приоритетности
        // последнего оператора в стеке operators (мы забираем из операторс все
        // операторы такой же приоритетности или ниже)
      } else if (operators != NULL &&
                 operators->priority >= reversed_node->priority) {
        while (operators != NULL &&
               operators->priority >= reversed_node->priority &&
               operators->type != 18) {
          push_to_stack(&rpn, operators->value, operators->priority,
                        operators->type);
          Node* tmp = operators;
          operators = tmp->next;
          free(tmp);
        }
        push_to_stack(&operators, reversed_node->value, reversed_node->priority,
                      reversed_node->type);
      } else
        push_to_stack(&operators, reversed_node->value, reversed_node->priority,
                      reversed_node->type);
    }
    Node * tmp = reversed_node;
    reversed_node = reversed_node->next; //Перевод на следующий элемент перевернутого списка списка
    free(tmp);
  }
  while (operators != NULL) { //Пуш всех операторов оставшихся в стеке операторов в польскую нотацию
    push_to_stack(&rpn, operators->value, operators->priority, operators->type);
    Node* tmp = operators;
    operators = tmp->next;
    free(tmp);
  }

  return rpn;
}