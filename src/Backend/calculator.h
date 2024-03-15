#ifndef SRC_CALCULATOR_H_
#define SRC_CALCULATOR_H_
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!
 * \mainpage
 * \author truckjyn
 * \version 1.0
 * \section intro_sec Calculator_v1.0 was done with
 * 1. C language \n
 * 2. Qt Creator, Qt
 * 3. Qcustomplot
 * 4. Qmake6
 * 5. Doxygen
 */

//Функция проверки входной строки. Если с введенным выражением все ок вернет 0,
//если нет то 1

typedef enum {
  number = 0,
  plus = 1,
  minus = 2,
  mul = 3,
  divv = 4,
  poww = 5,
  mod = 6,
  uplus = 7,
  umin = 8,
  coss = 9,
  sinn = 10,
  tann = 11,
  acoss = 12,
  asinn = 13,
  atann = 14,
  sqr = 15,
  lnn = 16,
  logg = 17,
  open_bracket = 18,
  close_bracket = 19,
} types;

typedef struct Node Node;
// Определение структуры узла списка
typedef struct Node {
  double value;
  int priority;
  Node *next;
  types type;
} Node;

/// @brief Initializes a singly linked list and gives it the value NULL
/// @return Node
Node *initializeList();
/// @brief Adds an element to the top of the stack
/// @param  plist Node
/// @param value double
/// @param priority int
/// @param type types
/// @return void
void push_to_stack(Node **plist, double value, int priority,
                   types type);  // изменить
/// @brief The function returns an element (Node *) of the top of the stack and
/// deletes
/// @param  list Node
/// @return Node
Node *pop(Node **list);
/// @brief The function outputs the entire contents of the stack
/// @param  list Node
/// @return void
void print(Node *list);
/// \brief Test stack for empty,
/// \param  list Node
/// \return If empty returns 1 else 0
int is_empty(Node *list);
// Returns element from the top of the stack
/// \brief  Reverse Node src into Node dst
/// \param  src Node
/// \param  dst Node
/// \return void
void reverse_node(Node *src, Node **dst);
/// \brief To check a string for correctness
/// \param  string char
/// \return Number of mistakes
int validator(char *string);
/// \brief To check a string for correctness brackets
/// \param  string char
/// \return If correct returns 1 1 else 0
int validate_brackets(char *string);
/// \brief To check a string for correctness dot
/// \param  string char
/// \return If correct returns 1 1 else 0
int validate_dot_comma(char *string);
/// \brief To check a string for correctness functions
/// \param  string char
/// \return If correct returns 1 1 else 0
int validate_functions(char *string);
/// \brief To check a string for correctness trigonometry
/// \param  string char
/// \return If correct returns 1 1 else 0
int validate_trigonometry(char *string, size_t index);
/// \brief To check a string for correctness operators
/// \param  string char
/// \return If correct returns 1 else 0
int validate_operators(char *string);
/// \brief To create a string without spaces
/// \param  string char
/// \return String without spaces
char *squeeze(char *string);
int validate_incorrect_sym(char *string);

// Parser
/// \brief Checks the type of a variable
/// \param  op char
/// \return If operator returns 1 else 0
int isOperator(char op);
/// \brief Checks the priority of a variable
/// \param  op char
/// \return priority of a variable
int getPriority(char op);
/// \brief Сonverts a string to a stack, assigns a value to x
/// \param  input char
/// \param  stack Node
/// \param  x double
/// \return Priority of a variable
void convertToLexemes(char *input, Node **stack, double x);

// RPN
/// \brief Forms a stack with Polish notation
/// \param  reversed_node Node
/// \return First node in stack
Node *translation_into_polish_notation(Node *reversed_node);
/// \brief Сounts the expression written to the stack
/// \param stack Node
/// \return Сalculation result
double calculate(Node **stack);
/// \brief Performs all procedures to produce the final result
/// \param string char
/// \param x double
/// \return Сalculation result
double calculate_string(char *string, double x);

// annuity
/// \brief Сalculates monthly payment
/// \param amount double
/// \param percent double
/// \param term int
/// \return Monthly loan payment
double monthly_annuity_payment(double amount, double percent, int term);
/// \brief calculates the overpayment on the loan
/// \param amount double
/// \param percent double
/// \param term int
/// \return Overpayment for the credit
double overpayment_on_loan(double amount, double percent, int term);
/// \brief calculates the total amount of payments
/// \param amount double
/// \param percent double
/// \param term int
/// \return Total amount of payments
double total_loan_payment(double amount, double percent, int term);

// differential
/// \brief calculates the total amount of payments
/// \param amount double
/// \param percent double
/// \param term int
/// \return Total amount of payments
double differential_payment(double amount, double percent, int term);
/// \brief Counts payments for the first and last month
/// \param amount double
/// \param percent double
/// \param term int
/// \param payments double *
/// \return  an array of two numbers of the first and last payment
void monthly_differential_payment(double amount, double percent, int term,
                                  double *payments);
/// \brief calculates the overpayment on the loan
/// \param amount double
/// \param percent double
/// \param term int
/// \return Overpayment for the credit
double differential_overpayment(double amount, double percent, int term);
#endif  // SRC_CALCULATOR_H_

void freeList(Node *head);
