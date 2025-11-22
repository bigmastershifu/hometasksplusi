#include <iostream>
#include <string>

int main() {
  std::string s = "\n  std::cout << \"#include <iostream>\\\\n#include <string>\\\\n\\\\nint main() {\\\\n  std::string s = \\\\\"\";\n  for (char c : s) {\n    if (c == 10) std::cout << \"\\\\n\";\n    else if (c == 34) std::cout << \"\\\\\\\"\";\n    else if (c == 92) std::cout << \"\\\\\\\\\";\n    else std::cout << c;\n  }\n  std::cout << \"\\\";\" << s;\n  return 0;\n}";
  std::cout << "#include <iostream>\n#include <string>\n\nint main() {\n  std::string s = \"";
  for (char c : s) {
    if (c == 10) std::cout << "\\n";
    else if (c == 34) std::cout << "\\\"";
    else if (c == 92) std::cout << "\\\\";
    else std::cout << c;
  }
  std::cout << "\";" << s;
  return 0;
}