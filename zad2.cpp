#include <iostream>
#include <source_location>

class Tracer {
 private:
  std::source_location location_;

 public:
  Tracer(std::source_location loc = std::source_location::current()) {
    location_ = loc; 
    std::cout << "enter -> " << location_.function_name() << ' '
              << location_.file_name() << ":" << location_.line() << '\n';
  }

  ~Tracer() {
    std::cout << "exit " << location_.function_name() << '\n';
  }
};

#define CONCAT_IMPL(x, y) x##y
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)

#ifdef NDEBUG
  #define trace() ((void)0)
#else
  #define trace() Tracer MACRO_CONCAT(tracer_, __LINE__)
#endif


void Deep_function() {
  trace();
  std::cout << "  working deep inside\n";
}

void Middle_function() {
  trace();
  std::cout << "  calling deep function\n";
  Deep_function();
}

void Test_block_scope() {
  std::cout << "  before block\n";
  {
    trace();
    std::cout << "  inside block\n";
  }
  std::cout << "  after block\n";
}

int main() {
  std::cout << "test 1: nested calls\n";
  {
    trace();
    Middle_function();
  }
  std::cout << '\n';

  std::cout << "test 2: into scope lifetime\n";
  Test_block_scope();
  std::cout << '\n';

  std::cout << "test 3: default call\n";
  Deep_function();

  return 0;
}