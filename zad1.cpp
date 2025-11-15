#include <cmath>
#include <iostream>
#include <vector>
#include <string>

struct Coords {
  int x;
  int y;
};

class Rectangle {
 private:
  Coords p_leftup;
  Coords p_rightdown;

 public:
  int Square () {
    return std::abs(p_leftup.x - p_rightdown.x) * std::abs(p_leftup.y - p_rightdown.y);
  }

  void SquareCrossing(std::vector<Rectangle>& rects) {
    Rectangle intersection = rects[0];
    for (size_t i = 1; i < rects.size(); ++i) {
      int left = std::max(intersection.p_leftup.x, rects[i].p_leftup.x);
      int right = std::min(intersection.p_rightdown.x, rects[i].p_rightdown.x);
      int top = std::max(intersection.p_leftup.y, rects[i].p_leftup.y);
      int bottom = std::min(intersection.p_rightdown.y, rects[i].p_rightdown.y);

      if (left > right or top > bottom) {
        std::cout << "None";
        return;
      }
      intersection.p_leftup = {left, top};
      intersection.p_rightdown = {right, bottom};
    }
    std::cout << intersection.Square();
  }

  void RectangleUnion(std::vector<Rectangle>& rects) {
    int left = rects[0].p_leftup.x;
    int top = rects[0].p_leftup.y;
    int right = rects[0].p_rightdown.x;
    int bottom = rects[0].p_rightdown.y;

    for (size_t i = 1; i < rects.size(); ++i) {
      left = std::min(left, rects[i].p_leftup.x);
      top = std::min(top, rects[i].p_leftup.y);
      right = std::max(right, rects[i].p_rightdown.x);
      bottom = std::max(bottom, rects[i].p_rightdown.y);
    }

    std::cout << left << ' ' << top << ' ' << right << ' ' << bottom;
  }

  std::vector<Rectangle> Input() {
    int n = 0;
    std::cin >> n;
    std::vector<Rectangle> rects(n);
    for (int i = 0; i < n; ++i) {
      Rectangle rectangle;
      std::cin >> rectangle.p_leftup.x >> rectangle.p_leftup.y;
      std::cin >> rectangle.p_rightdown.x >> rectangle.p_rightdown.y;
      rects[i] = rectangle;
    }
    return rects;
  }

  void Output(std::vector<Rectangle>& rects) {
    SquareCrossing(rects);
    std::cout << '\n';
    RectangleUnion(rects);
  }
};

int main() {
  Rectangle r;
  std::vector<Rectangle> rects = r.Input();
  r.Output(rects);
  return 0;

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
