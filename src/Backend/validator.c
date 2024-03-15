#include "calculator.h"

int validator(char *string) {
    int flag = 0;
    int length = strlen(string);
    if (length == 1 || length == 0) flag+=1;
    char *s_string = squeeze(string);
    length = strlen(s_string);
    if (length == 1 || length == 0) flag+=1;
    flag += validate_dot_comma(s_string);
    flag += validate_brackets(s_string);
    flag += validate_operators(s_string);
    flag += validate_functions(s_string);
//    Node* src = initializeList();
//    convertToLexemes(string, &src, 0);
//    if (src->type != 0 && src->type != 5) flag++;
    free(s_string);
    return flag;
}

char *squeeze(char *string) {
  int length = strlen(string);
  int count = 0;
  for (int i = 0; i < length; i++) {
    if (string[i] == 32)
      count++;
  }
  char *squeezed_string = malloc(sizeof(char) * (length - count));
  for (int i = 0, j = 0; j < length; j++) {
    if (string[j] != 32) {
      squeezed_string[i] = string[j];
      i++;
    }
  }
  return squeezed_string;
}

int validate_brackets(char *string) {
  int flag = 0, brackets = 0;
  for (size_t i = 0; i < strlen(string); i++) {
    if (string[i] == '(')
      brackets++;
    if (string[i] == ')')
      brackets--;
    if (brackets < 0) {
      flag = 1;
      break;
    }
  }
  if (brackets != 0) {
    flag = 1;
  }
  return flag;
}

int validate_dot_comma(char *string) {
  int flag = 0;
  if ((strlen(string) == 1 && (string[0] == '.' || string[0] == ',')) ||
      string[strlen(string) - 1] == '.' || string[strlen(string) - 1] == ',')
    flag = 1;
  else if (strlen(string) == 2 && (string[0] == '.' || string[1] == '.' ||
                                   string[0] == ',' || string[1] == ','))
    flag = 1;

  for (size_t i = 1; i < strlen(string) - 1; i++) {
    if (string[i] == '.' || string[i] == ',') {
      if (string[i + 1] < '0' || string[i + 1] > '9' || string[i - 1] < '0' ||
          string[i - 1] > '9') {
        flag = 1;
        break;
      }
    }
  }
  return flag;
}
//  mod
int validate_functions(char *string) {
  int flag = 0;
  for (size_t i = 0; i < strlen(string); i++) {
    if (string[i] >= 97 && string[i] <= 122) {
      if (string[i] == 'c' && string[i + 1] == 'o' && string[i + 2] == 's' &&
          string[i + 3] == '(' && i + 5 <= strlen(string) - 1 &&
          string[i + 4] != ')') {
        i += 3;
      } else if (string[i] == 's' && string[i + 1] == 'i' &&
                 string[i + 2] == 'n' && string[i + 3] == '(' &&
                 i + 5 <= strlen(string) - 1 && string[i + 4] != ')') {
        i += 3;
      } else if (string[i] == 't' && string[i + 1] == 'a' &&
                 string[i + 2] == 'n' && string[i + 3] == '(' &&
                 i + 5 <= strlen(string) - 1 && string[i + 4] != ')') {
        i += 3;
      } else if (string[i] == 'l' && string[i + 1] == 'o' &&
                 string[i + 2] == 'g' && string[i + 3] == '(' &&
                 i + 5 <= strlen(string) - 1 && string[i + 4] != ')') {
        i += 3;
      } else if (string[i] == 'l' && string[i + 1] == 'n' &&
                 string[i + 2] == '(' && i + 4 <= strlen(string) - 1 &&
                 string[i + 3] != ')') {
        i += 2;
      } else if (string[i] == 's' && string[i + 1] == 'q' &&
                 string[i + 2] == 'r' && string[i + 3] == 't' &&
                 string[i + 4] == '(' && i + 6 <= strlen(string) - 1 &&
                 string[i + 5] != ')') {
        i += 3;
      } else if (string[i] == 'm' && string[i + 1] == 'o' &&
                 string[i + 2] == 'd' && i + 4 <= strlen(string) - 1 &&
                 i - 1 > 0 && string[i - 1] != '(') {
        i += 2;
      } else if (string[i] == 'a') {
        flag = validate_trigonometry(string, i + 1);
        if (!flag)
          i += 4;
        else
          break;
      } else if (string[i] == 'x') {
        flag = 0;
      } else if (string[i] == 'p' && i != strlen(string) - 1 &&
                 string[i + 1] == 'i') {
        i += 1;
        flag = 0;
      } else {
        flag = 1;
        break;
      }
    }
  }
  return flag;
}

int validate_trigonometry(char *string, size_t index) {
  int flag = 0;
  if (string[index] == 'c' && string[index + 1] == 'o' &&
      string[index + 2] == 's' && string[index + 3] == '(' &&
      index + 5 <= strlen(string) - 1) {
  } else if (string[index] == 's' && string[index + 1] == 'i' &&
             string[index + 2] == 'n' && string[index + 3] == '(' &&
             index + 5 <= strlen(string) - 1 && string[index + 4] != ')') {
  } else if (string[index] == 't' && string[index + 1] == 'a' &&
             string[index + 2] == 'n' && string[index + 3] == '(' &&
             index + 5 <= strlen(string) - 1 && string[index + 4] != ')') {
  } else {
    flag = 1;
  }
  return flag;
}

int validate_operators(char *string) {
  int flag = 0;
  for (size_t i = 0; i < strlen(string); i++) {
    if ((string[i] == '+' || string[i] == '-' || string[i] == '*' ||
         string[i] == '/' || string[i] == '^') &&
        i == strlen(string) - 1) { // поменял на плюс два уточнить
      flag = 1;
    }
  }

  for (size_t i = 0; i < strlen(string) - 1; i++) {
    if ((string[i] == '+' || string[i] == '-' || string[i] == '*' ||
         string[i] == '/' || string[i] == '^') &&
        (string[i + 1] == '+' || string[i + 1] == '-' || string[i + 1] == '*' ||
         string[i + 1] == '/' || string[i + 1] == '^')) {
      flag = 1;
    }
  }
  return flag;
}