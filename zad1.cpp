#include <iostream>
#include <vector>
#include <string>
#include <cmath>

void Split(const std::string& line, std::vector<std::string>& toks) {
  std::string cur;
  for (char c : line) {
    if (c == ' ') {
      if (!cur.empty()) {
        toks.push_back(cur);
        cur.clear();
      }
    } else {
      cur = cur + c;
    }
  }
  if (!cur.empty()) {
    toks.push_back(cur);
  }
}

void ObrOpers(const std::vector<std::string>& toks, std::vector<double>& stek, std::string& err) {
  for (size_t k = 0; k < toks.size() and err.empty(); ++k) {
    const std::string& tk = toks[k];
    try {
      double v = std::stod(tk); //  каст в число если можем
      stek.push_back(v);
      continue;
    } catch (...) {
      // не число
    }

    if (tk == "+") {
      if (stek.size() < 2) { err = "недостаточно данных для +"; break; }
      double b = stek.back(); stek.pop_back();
      double a = stek.back(); stek.pop_back();
      stek.push_back(a + b);

    } else if (tk == "-") {
      if (stek.size() < 2) { err = "недостаточно данных для -"; break; }
      double b = stek.back(); stek.pop_back();
      double a = stek.back(); stek.pop_back();
      stek.push_back(a - b);

    } else if (tk == "*") {
      if (stek.size() < 2) { err = "недостаточно данных для *"; break; }
      double b = stek.back(); stek.pop_back();
      double a = stek.back(); stek.pop_back();
      stek.push_back(a * b);

    } else if (tk == "/") {
      if (stek.size() < 2) { err = "недостаточно данных для /"; break; }
      double b = stek.back(); stek.pop_back();
      double a = stek.back(); stek.pop_back();
      if (b == 0.0) { err = "деление на ноль"; break; }
      stek.push_back(a / b);

    } else if (tk == "sin") {
      if (stek.empty()) { err = "недостаточно данных для sin"; break; }
      double a = stek.back(); stek.pop_back();
      stek.push_back(std::sin(a));

    } else if (tk == "cos") {
      if (stek.empty()) { err = "недостаточно данных для cos"; break; }
      double a = stek.back(); stek.pop_back();
      stek.push_back(std::cos(a));

    } else if (tk == "tg" or tk == "tan") {
      if (stek.empty()) { err = "недостаточно данных для tg"; break; }
      double a = stek.back(); stek.pop_back();
      double r = std::tan(a);
      stek.push_back(r);

    } else if (tk == "ctg" or tk == "cot") {
      if (stek.empty()) { err = "недостаточно данных для ctg"; break; }
      double a = stek.back(); stek.pop_back();
      double t = std::tan(a);
      if (t == 0.0) { err = "деление на ноль в ctg"; break; }
      stek.push_back(1.0 / t);

    } else if (tk == "exp") {
      if (stek.empty()) { err = "недостаточно данных для exp"; break; }
      double a = stek.back(); stek.pop_back();
      double r = std::exp(a);
      stek.push_back(r);

    } else if (tk == "log") {
      if (stek.empty()) { err = "недостаточно данных для log"; break; }
      double a = stek.back(); stek.pop_back();
      if (a <= 0.0) { err = "логарифм от отрицательного"; break; }
      stek.push_back(std::log(a));

    } else if (tk == "sqrt") {
      if (stek.empty()) { err = "недостаточно данных для sqrt"; break; }
      double a = stek.back(); stek.pop_back();
      if (a < 0.0) { err = "корень из отрицательного числа"; break; }
      stek.push_back(std::sqrt(a));

    } else if (tk == "atan2") {
      if (stek.size() < 2) { err = "недостаточно данных для atan2"; break; }
      double x = stek.back(); stek.pop_back();
      double y = stek.back(); stek.pop_back();
      double r = std::atan2(y, x);
      stek.push_back(r);

    } else if (tk == "pow" or tk == "^") {
      if (stek.size() < 2) { err = "недостаточно данных для pow"; break; }
      double b = stek.back(); stek.pop_back();
      double a = stek.back(); stek.pop_back();
      double r = std::pow(a, b);
      stek.push_back(r);

    } else if (tk == "median") {
      if (stek.size() < 3) { err = "недостаточно данных для median"; break; }
      double c = stek.back(); stek.pop_back();
      double b = stek.back(); stek.pop_back();
      double a = stek.back(); stek.pop_back();
      double arr[3] = {a, b, c};
      if (arr[0] > arr[1]) { double tmp = arr[0]; arr[0] = arr[1]; arr[1] = tmp; }
      if (arr[1] > arr[2]) { double tmp = arr[1]; arr[1] = arr[2]; arr[2] = tmp; }
      if (arr[0] > arr[1]) { double tmp = arr[0]; arr[0] = arr[1]; arr[1] = tmp; }
      stek.push_back(arr[1]);
    } else {
      err = std::string("некорректная операуци ") + tk;
      break;
    }
  }
}

void Print(const std::vector<double> &stek, const std::string &err) {
  if (!err.empty()) {
    std::cout << err << '\n';
  } else {
    if (stek.size() == 1) {
      std::cout << stek.back() << '\n';
    } else if (stek.empty()) {
      std::cout << "слишком мало чисел" << '\n';
    } else {
      std::cout << "слишком много чисел" << '\n';
    }
  }
}

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    if (line == "exit") {
      break;
    }

    std::vector<std::string> toks;
    Split(line, toks);

    std::vector<double> stek;
    std::string err;
    ObrOpers(toks, stek, err);

    Print(stek, err);
  }
  return 0;

  /* 3 4 +
    5 1 2 + 4 * + 3 -
    9 0 /
    2 3 pow
    1 2 atan2
    3 1 2 median
    2 3 + */
}
