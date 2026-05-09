// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int getPriority(char ch) {
  switch (ch) {
    case '(': return 0;
    case '+':
    case '-': return 1;
    case '*':
    case '/': return 2;
    default: return -1;
  }
}

std::string infx2pstfx(const std::string& inf) {
  std::string pstfx = "";
  TStack<char, 100> stack;
  bool last_was_digit = false;

  for (size_t i = 0; i < inf.length(); ++i) {
    char ch = inf[i];

    if (ch >= '0' && ch <= '9') {
      pstfx += ch;
      last_was_digit = true;
    } else {
      if (last_was_digit) {
        pstfx += ' ';
        last_was_digit = false;
      }

      if (ch == '(') {
        stack.push(ch);
      } else if (ch == ')') {
        while (!stack.isEmpty() && stack.get() != '(') {
          pstfx += stack.pop();
          pstfx += ' ';
        }
        if (!stack.isEmpty()) stack.pop();
      } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
        while (!stack.isEmpty() &&
               getPriority(stack.get()) >= getPriority(ch)) {
          pstfx += stack.pop();
          pstfx += ' ';
        }
        stack.push(ch);
      }
    }
  }

  if (last_was_digit) pstfx += ' ';

  while (!stack.isEmpty()) {
    pstfx += stack.pop();
    pstfx += ' ';
  }

  if (!pstfx.empty() && pstfx[pstfx.length() - 1] == ' ') {
    pstfx.pop_back();
  }

  return pstfx;
}

int eval(const std::string& post) {
  TStack<int, 100> stack;
  int num = 0;
  bool is_parsing_num = false;

  for (size_t i = 0; i < post.length(); ++i) {
    char ch = post[i];

    if (ch >= '0' && ch <= '9') {
      num = num * 10 + (ch - '0');
      is_parsing_num = true;
    } else if (ch == ' ') {
      if (is_parsing_num) {
        stack.push(num);
        num = 0;
        is_parsing_num = false;
      }
    } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
      if (is_parsing_num) {
        stack.push(num);
        num = 0;
        is_parsing_num = false;
      }
      int val2 = stack.pop();
      int val1 = stack.pop();
      if (ch == '+') stack.push(val1 + val2);
      else if (ch == '-') stack.push(val1 - val2);
      else if (ch == '*') stack.push(val1 * val2);
      else if (ch == '/') stack.push(val1 / val2);
    }
  }

  if (is_parsing_num) stack.push(num);

  return stack.get();
}
