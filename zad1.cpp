#include <cmath>
#include <iostream>
#include <vector>
#include <string>

struct Coords {
  int x;
  int y;
};

class Rectangle {
 public:
  Coords leftup;
  Coords rightdown;

  int Square () {
    return std::abs(leftup.x - rightdown.x) * std::abs(leftup.y - rightdown.y);
  }

  void SquareCrossing(std::vector<Rectangle>& rects) {
    Rectangle intersection = rects[0];
    for (size_t i = 1; i < rects.size(); ++i) {
      int left = std::max(intersection.leftup.x, rects[i].leftup.x);
      int right = std::min(intersection.rightdown.x, rects[i].rightdown.x);
      int top = std::max(intersection.leftup.y, rects[i].leftup.y);
      int bottom = std::min(intersection.rightdown.y, rects[i].rightdown.y);

      if (left > right or top > bottom) {
        std::cout << "None";
        return;
      }
      intersection.leftup = {left, top};
      intersection.rightdown = {right, bottom};
    }
    std::cout << intersection.Square();
  }

  void RectangleUnion(std::vector<Rectangle>& rects) {
    int left = rects[0].leftup.x;
    int top = rects[0].leftup.y;
    int right = rects[0].rightdown.x;
    int bottom = rects[0].rightdown.y;

    for (size_t i = 1; i < rects.size(); ++i) {
      left = std::min(left, rects[i].leftup.x);
      top = std::min(top, rects[i].leftup.y);
      right = std::max(right, rects[i].rightdown.x);
      bottom = std::max(bottom, rects[i].rightdown.y);
    }

    std::cout << left << ' ' << top << ' ' << right << ' ' << bottom;
  }
};

int main() {
  //  ввод координат
  int n = 0;
  std::cin >> n;
  std::vector<Rectangle> rects(n);
  for (int i = 0; i < n; ++i) {
    Rectangle rectangle;
    std::cin >> rectangle.leftup.x >> rectangle.leftup.y;
    std::cin >> rectangle.rightdown.x >> rectangle.rightdown.y;
    rects[i] = rectangle;
  }

  Rectangle r;

  r.SquareCrossing(rects);
  std::cout << '\n';
  r.RectangleUnion(rects);

  /*
  ---тест 1
  2
  0 0 2 2
  0 0 1 1
  ---тест 2
  3
  0 0 4 3
  1 2 5 6
  2 1 8 7
  --тест 3
  1
  1 2 3 8
  ---тест 4
  2
  0 0 1 1
  2 1 3 1
  */
  return 0;
}