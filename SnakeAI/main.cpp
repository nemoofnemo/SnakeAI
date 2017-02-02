#include <cstdio>
#include <iostream>
#include <list>
#include <cstdlib>
#include <array>

using namespace std;

//struct definition
struct Vector2 {
	int x;
	int y;

	bool operator==(const Vector2 & right) {
		return this->x == right.x && this->y == right.y;
	}

	Vector2 operator+(const Vector2 & right) {
		Vector2 ret;
		ret.x = this->x + right.x;
		ret.y = this->y + right.y;
		return ret;
	}
};

typedef struct Vector2 Point;

struct Node {
	Point point;
	Vector2 vec;

	bool operator==(const Node & node) {
		return this->point == node.point && this->vec == node.point;
	}
};

//directions
Vector2 UP = { -1,0 };
Vector2 DOWN = { 1, 0 };
Vector2 LEFT = { 0, -1 };
Vector2 RIGHT = { 0,1 };

//snake
class Snake {
private:
	list<Node> snake;
	int count;

	list<list<Node>> pathHistory;
public:
	Snake() {
		count = 2;
		Node n = { { 0,0 }, DOWN };
		snake.push_back(n);
		n.point.x = 1;
		snake.push_front(n);
	}

	Node GetHead(void) {
		return *snake.begin();
	}

	list<Node> GetSnake(void) {
		return snake;
	}

	bool PushHead(Vector2 direction) {
		list<Node>::iterator it = snake.begin();

		//direction error.
		it++;
		if (it->point == (snake.begin()->point + direction)) {
			return false;
		}
		it--;

		snake.push_front({ it->point + direction , direction});
		count ++ ;

		return true;
	}

	bool MoveFoward(Vector2 direction) {
		if ((direction.x >= 0 ? direction.x : -direction.x) > 1) {
			direction.x /= direction.x;
		}

		if ((direction.y >= 0 ? direction.y : -direction.y) > 1) {
			direction.y /= direction.y;
		}

		list<Node>::iterator it = snake.begin();
		list<Node>::iterator end = snake.end();
		pathHistory.push_front(snake);
		Point dest = it->point + direction;
		int num = 0;
		Vector2 prev = direction;
		Vector2 temp;

		while (it != end) {
			it->point = it->point + prev;
			temp = it->vec;
			it->vec = prev;
			prev = temp;
			if (it->point == dest) {
				num++;
			}
			it++;
		}

		if (num > 1) {
			snake = *(pathHistory.begin());
			pathHistory.pop_front();
			return false;
		}

		return true;
	}

	void MoveBackward() {
		if (pathHistory.size()) {
			snake = *(pathHistory.begin());
			pathHistory.pop_front();
			count = snake.size();
		}
	}

	void ClearDirectionHistory(void) {
		pathHistory.clear();
	}
};

class Main {
private:
	//map array
	static const int WIDTH = 20;
	static const int LENGTH = 20;
	char map[WIDTH][LENGTH] ;
	char calcMap[WIDTH][LENGTH] ;

	//snake: head&body
	list<Node> snake;
	list<Node> calcSnake;

	int count;
	int score;



public:
	Main() {
		memset(map, '.', sizeof(char) * WIDTH * LENGTH);
		
		score = 0;
		count = 1;

		Node n = { { 0,0 }, DOWN };
		snake.push_back(n);
	}

	void moveFoward(list<Node> * list) {
		
	}



	void show() {
		for (int i = 0; i < WIDTH; ++i) {
			for (int d = 0; d < LENGTH; ++d) {
				printf("%2c", map[i][d]);
			}
			putchar('\n');
		}
	}

	Vector2 calcNext(void) {

	}

	void run(void) {
		Vector2 vec;
		Point pt;

		while (true) {
			vec = calcNext();
			/*pt.x = snake[0].point.x + vec.x;
			pt.y = snake[0].point.y + vec.y;*/

			if (pt.x < 0 || pt.x >= WIDTH || pt.y < 0 || pt.y >= LENGTH) {
				system("clear");
				puts("done");
				break;
			}
		}
	}
};

int main(void) {
	Snake s;
	s.PushHead(DOWN);
	s.MoveFoward(RIGHT);
	return 0;
}