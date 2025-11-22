#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>

class Operation {
 public:
  virtual bool Execute(std::vector<double>& stack, std::string& error_msg) const = 0;
  virtual ~Operation() {}
};

typedef bool (*UnaryFunc)(double, double&, const char**);
typedef bool (*BinaryFunc)(double, double, double&, const char**);
typedef bool (*TernaryFunc)(double, double, double, double&, const char**);

class UnaryOperation : public Operation {
 private:
  UnaryFunc func_;

 public:
  UnaryOperation(UnaryFunc f) : func_(f) {}
  bool Execute(std::vector<double>& stack, std::string& error_msg) const override {
    if (stack.size() < 1) {
      error_msg = "not enough unary operands";
      return false;
    }
    double operand = stack.back();
    stack.pop_back();
    
    double res;
    const char* func_err = nullptr;
    if (!func_(operand, res, &func_err)) {
      error_msg = func_err;
      return false;
    }
    
    stack.push_back(res);
    return true;
  }
};

class BinaryOperation : public Operation {
 private:
  BinaryFunc func_;

 public:
  BinaryOperation(BinaryFunc f) : func_(f) {}
  bool Execute(std::vector<double>& stack, std::string& error_msg) const override {
    if (stack.size() < 2) {
      error_msg = "not enough binary operands";
      return false;
    }
    double operand2 = stack.back();
    stack.pop_back();
    double operand1 = stack.back();
    stack.pop_back();

    double res;
    const char* func_err = nullptr;
    if (!func_(operand1, operand2, res, &func_err)) {
      error_msg = func_err;
      return false;
    }

    stack.push_back(res);
    return true;
  }
};

class TernaryOperation : public Operation {
 private:
  TernaryFunc func_;

 public:
  TernaryOperation(TernaryFunc f) : func_(f) {}
  bool Execute(std::vector<double>& stack, std::string& error_msg) const override {
    if (stack.size() < 3) {
      error_msg = "not enough ternary operands";
      return false;
    }
    double operand3 = stack.back();
    stack.pop_back();
    double operand2 = stack.back();
    stack.pop_back();
    double operand1 = stack.back();
    stack.pop_back();

    double res;
    const char* func_err = nullptr;
    if (!func_(operand1, operand2, operand3, res, &func_err)) {
      error_msg = func_err;
      return false;
    }

    stack.push_back(res);
    return true;
  }
};

bool Add(double a, double b, double& res, const char** err) { res = a + b; return true; }
bool Sub(double a, double b, double& res, const char** err) { res = a - b; return true; }
bool Mul(double a, double b, double& res, const char** err) { res = a * b; return true; }
bool Div(double a, double b, double& res, const char** err) {
  if (b == 0) {
    *err = "division by 0";
    return false;
  }
  res = a / b;
  return true;
}

bool MySin(double a, double& res, const char** err) { res = std::sin(a); return true; }
bool MyCos(double a, double& res, const char** err) { res = std::cos(a); return true; }
bool MyTg(double a, double& res, const char** err) { res = std::tan(a); return true; }
bool MyCtg(double a, double& res, const char** err) { res = 1.0 / std::tan(a); return true; }
bool MyExp(double a, double& res, const char** err) { res = std::exp(a); return true; }
bool MyLog(double a, double& res, const char** err) { res = std::log(a); return true; }
bool MySqrt(double a, double& res, const char** err) {
  if (a < 0) {
    *err = "square of negative number";
    return false;
  }
  res = std::sqrt(a);
  return true;
}

bool MyAtan2(double a, double b, double& res, const char** err) { res = std::atan2(a, b); return true; }
bool MyPow(double a, double b, double& res, const char** err) { res = std::pow(a, b); return true; }

bool MyMedian(double a, double b, double c, double& res, const char** err) {
  if (a > b) std::swap(a, b);
  if (b > c) std::swap(b, c);
  if (a > b) std::swap(a, b);
  res = b;
  return true;
}

struct OpEntry {
  std::string name;
  Operation* op;
};

bool IsNumber(const std::string& s) {
  char* end = nullptr;
  std::strtod(s.c_str(), &end);
  return end != s.c_str() and *end == '\0';
}

std::vector<std::string> Split(const std::string& s) {
  std::vector<std::string> tokens;
  std::string token = "";
  for (size_t i = 0; i < s.length(); ++i) {
    if (s[i] == ' ') {
      if (!token.empty()) {
        tokens.push_back(token);
        token = "";
      }
    } else {
      token = token + s[i];
    }
  }
  if (!token.empty()) tokens.push_back(token);
  return tokens;
}

int main() {
  std::vector<OpEntry> operations;
  operations.push_back({"+", new BinaryOperation(Add)});
  operations.push_back({"-", new BinaryOperation(Sub)});
  operations.push_back({"*", new BinaryOperation(Mul)});
  operations.push_back({"/", new BinaryOperation(Div)});
  operations.push_back({"sin", new UnaryOperation(MySin)});
  operations.push_back({"cos", new UnaryOperation(MyCos)});
  operations.push_back({"tg", new UnaryOperation(MyTg)});
  operations.push_back({"ctg", new UnaryOperation(MyCtg)});
  operations.push_back({"exp", new UnaryOperation(MyExp)});
  operations.push_back({"log", new UnaryOperation(MyLog)});
  operations.push_back({"sqrt", new UnaryOperation(MySqrt)});
  operations.push_back({"atan2", new BinaryOperation(MyAtan2)});
  operations.push_back({"pow", new BinaryOperation(MyPow)});
  operations.push_back({"median", new TernaryOperation(MyMedian)});

  std::string line = "";
  std::getline(std::cin, line);

  std::vector<std::string> tokens = Split(line);
  std::vector<double> stack;
  
  bool error_occurred = false;
  std::string error_msg = "";

  for (size_t i = 0; i < tokens.size(); ++i) {
    std::string token = tokens[i];
    bool found = false;

    for (size_t j = 0; j < operations.size(); ++j) {
      if (operations[j].name == token) {
        if (!operations[j].op->Execute(stack, error_msg)) {
          std::cerr << error_msg << '\n';
          error_occurred = true;
        }
        found = true;
        break;
      }
    }
    
    if (error_occurred) break;

    if (!found) {
      if (IsNumber(token)) {
        stack.push_back(std::strtod(token.c_str(), nullptr));
      } else {
        std::cerr << "unknown command '" + token + "'." << '\n';
        error_occurred = true;
        break;
      }
    }
  }

  if (!error_occurred) {
    if (stack.size() == 1) {
      std::cout << stack.back() << '\n';
    } else if (stack.empty()) {
      std::cerr << "no data" << '\n';
    } else {
      std::cerr << "too many operands left (" + std::to_string(stack.size()) + ")." << '\n';
    }
  }

  for (size_t i = 0; i < operations.size(); ++i) {
    delete operations[i].op;
  }

  //  10 1.5 sin * 20 2 pow + sqrt 3 4 5 median +
  //  + -
  // 10 5 + cos

  return 0;
}