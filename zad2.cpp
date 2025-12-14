#include <iostream>

class List {
 public:
  List() {
    head = nullptr;
    tail = nullptr;
  }
  bool Empty() {
    return head == nullptr;
  }

  void Show() {
    Node* current = head;
    while (current != nullptr) {
      std::cout << current->value << ' ';
      current = current->next;
    }
    std::cout << '\n';
  }

  void Push_front(int val) {
    Node* newNode = new Node{val, head};
    head = newNode;
    if (tail == nullptr) {
      tail = newNode;
    }
  }

  void Push_back(int val) {
    Node* newNode = new Node{val, nullptr};
    if (tail != nullptr) {
      tail->next = newNode;
    } else {
      head = newNode;
    }
    tail = newNode;
  }

  void Pop_front() {
    if (head == nullptr) {
      return;
    }
    Node* temp = head;
    head = head->next;
    if (head == nullptr) {
      tail = nullptr;
    }
    delete temp;
  }

  void Pop_back() {
    if (head == nullptr) {
      return;
    }
    if (head == tail) {
      delete head;
      head = nullptr;
      tail = nullptr;
      return;
    }
    Node* current = head;
    while (current->next != tail) {
      current = current->next;
    }
    delete tail;
    tail = current;
    tail->next = nullptr;
  }

  int Get() {
    if (head == nullptr) {
      std::cout << "empty" << '\n';
      return -1;
    }
    Node* slow = head;
    Node* fast = head;
    while (fast != nullptr and fast->next != nullptr) {
      slow = slow->next;
      fast = fast->next->next;
    }
    return slow->value;
  }

  ~List() {
    while (head != nullptr) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
    tail = nullptr;
  }

 private:
  struct Node {
    int value;
    Node* next;
  };

  Node* head = nullptr;
  Node* tail = nullptr;
};

int main() {
  List list;
  int n = 0;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    int cur = 0;
    std::cin >> cur;
    list.Push_back(cur);
  }
  list.Show();
  std::cout << '\n';
  list.Pop_front();
  list.Pop_back();
  std::cout << list.Get();

  return 0;
}
