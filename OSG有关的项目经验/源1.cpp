#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
//四边形
class Point
{
public:
	Point(int a, int b);
	double  x, y;

};
class Quadrilateral
{
public:
	Quadrilateral();
	vector <Point> polygon;

	int getArea2();
	double getDis(double x1, double y1, double x2, double y2);
	double getPerimeter();
	//声明成纯虚函数
	friend istream& operator>>(istream& is, Quadrilateral& a);
	virtual bool check();
};
//梯形

class Trapezoid :public Quadrilateral
{
public:
	Trapezoid();
	Trapezoid(Quadrilateral a);
	bool check();


};
//平行四边形
class Parallelogram :public Quadrilateral
{
public:
	Parallelogram();
	Parallelogram(Quadrilateral a);
	bool check();

};
//矩形
class Rectangle :public Parallelogram
{
public:
	Rectangle();
	Rectangle(Quadrilateral a);
	bool check();
};
//正方形
class Square :public Rectangle

{
public:
	Square();
	Square(Quadrilateral a);
	bool check();
};

double Distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}
//判断三个点是否构成直角，第一个参数点是顶点
bool IsRightAngle(int x1, int y1, int x2, int y2, int x3, int y3) {
    if ((x2 - x1) * (x3 - x1) + (y2 - y1) * (y3 - y1) == 0)
        return true;
    return false;
}
bool IsSquare(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    if (x1 == x2 && x2 == x3)
        return false;
    double s12 = Distance(x1, y1, x2, y2);
    double s13 = Distance(x1, y1, x3, y3);
    double s14 = Distance(x1, y1, x4, y4);
    double s23 = Distance(x2, y2, x3, y3);
    double s24 = Distance(x2, y2, x4, y4);
    double s34 = Distance(x3, y3, x4, y4);
    if (s12 == s13 && s24 == s34 && s12 == s24) {
        if (IsRightAngle(x1, y1, x2, y2, x3, y3)) return true;
        else return false;
    }
    if (s12 == s14 && s23 == s34 && s12 == s23) {
        if (IsRightAngle(x1, y1, x2, y2, x4, y4)) return true;
        else return false;
    }
    if (s13 == s14 && s23 == s24 && s13 == s23) {
        if (IsRightAngle(x1, y1, x3, y3, x4, y4)) return true;
        else return false;
    }
    return false;
}

Quadrilateral::Quadrilateral()
{
    polygon.push_back(Point(0, 0));
    polygon.push_back(Point(0, 0));
    polygon.push_back(Point(0, 0));
    polygon.push_back(Point(0, 0));
}

int Quadrilateral::getArea2()
{
    int i, j;
    double area = 0;
    for (i = 0; i < 4; i++) {
        j = (i + 1) % 4;
        area += polygon[i].x * polygon[j].y;
        area -= polygon[i].y * polygon[j].x;
    }

    return(area < 0 ? -area : area);

    return 0;
}

double Quadrilateral::getDis(double x1, double y1, double x2, double y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));

}

double Quadrilateral::getPerimeter()
{
    double distance = 0;
    distance += getDis(polygon[0].x, polygon[0].y, polygon[1].x, polygon[1].y);
    distance += getDis(polygon[1].x, polygon[1].y, polygon[2].x, polygon[2].y);
    distance += getDis(polygon[2].x, polygon[2].y, polygon[3].x, polygon[3].y);
    distance += getDis(polygon[3].x, polygon[3].y, polygon[0].x, polygon[0].y);
    return  distance;
}

bool Quadrilateral::check()
{
    return true;
}

istream& operator>>(istream& is, Quadrilateral& a)
{
    is >> a.polygon[0].x;
    is >> a.polygon[0].y;
    is >> a.polygon[1].x;
    is >> a.polygon[1].y;
    is >> a.polygon[2].x;
    is >> a.polygon[2].y;
    is >> a.polygon[3].x;
    is >> a.polygon[3].y;
    return is;
    // TODO: 在此处插入 return 语句
}

Trapezoid::Trapezoid()
{
    polygon.push_back(Point(0, 0));
    polygon.push_back(Point(0, 0));
    polygon.push_back(Point(0, 0));
    polygon.push_back(Point(0, 0));
}

Trapezoid::Trapezoid(Quadrilateral a)
{
    this->polygon = a.polygon;
}

bool Trapezoid::check()
{
    int x1 = polygon[0].x - polygon[1].x;
    int y1 = polygon[0].y - polygon[1].y;
    int x2 = polygon[3].x - polygon[2].x;
    int y2 = polygon[3].y - polygon[2].y;

    int x3 = polygon[2].x - polygon[1].x;
    int y3 = polygon[2].y - polygon[1].y;

    int x4 = polygon[0].x - polygon[3].x;
    int y4 = polygon[0].y - polygon[3].y;
    if ((x1 * x2 + y1 * y2) == 0 && (x3 * x4 + y3 * y4) != 0)
        return true;
    else if ((x1 * x2 + y1 * y2) != 0 && (x3 * x4 + y3 * y4) == 0)
        return true;
    else
        return false;
}

Point::Point(int a, int b) :x(a), y(b)
{
}



Parallelogram::Parallelogram()
{
    polygon.push_back(Point(0, 0));
    polygon.push_back(Point(0, 0));
    polygon.push_back(Point(0, 0));
    polygon.push_back(Point(0, 0));
}

Parallelogram::Parallelogram(Quadrilateral a)
{
    this->polygon = a.polygon;
}

bool Parallelogram::check()
{
    int x1 = polygon[0].x - polygon[1].x;
    int y1 = polygon[0].y - polygon[1].y;
    int x2 = polygon[3].x - polygon[2].x;
    int y2 = polygon[3].y - polygon[2].y;

    int x3 = polygon[2].x - polygon[1].x;
    int y3 = polygon[2].y - polygon[1].y;

    int x4 = polygon[0].x - polygon[3].x;
    int y4 = polygon[0].y - polygon[3].y;
    if ((x1 * x2 + y1 * y2) == 0 && (x3 * x4 + y3 * y4) == 0)
        return true;

    else
        return false;

}

Rectangle::Rectangle(Quadrilateral a)
{
    this->polygon = a.polygon;
}
bool Rectangle::check()
{
    int x1 = polygon[0].x - polygon[1].x;
    int y1 = polygon[0].y - polygon[1].y;
    int x2 = polygon[3].x - polygon[2].x;
    int y2 = polygon[3].y - polygon[2].y;

    int x3 = polygon[2].x - polygon[1].x;
    int y3 = polygon[2].y - polygon[1].y;

    int x4 = polygon[0].x - polygon[3].x;
    int y4 = polygon[0].y - polygon[3].y;
    if ((x1 * x2 + y1 * y2) == 0 && (x3 * x4 + y3 * y4) == 0 && (x2 * y1 - x1 * y2) == 0)
        return true;

    else
        return false;
}
Square::Square()
{
    polygon.push_back(Point(0, 0));
    polygon.push_back(Point(0, 0));
    polygon.push_back(Point(0, 0));
    polygon.push_back(Point(0, 0));
}
Square::Square(Quadrilateral a)
{
    this->polygon = a.polygon;
}

bool Square::check()
{
    if (IsSquare(polygon[0].x, polygon[0].y, polygon[1].x, polygon[1].y, polygon[2].x, polygon[2].y, polygon[3].x, polygon[3].y))
        return true;
    else
        return false;
}

Rectangle::Rectangle()
{
    polygon.push_back(Point(0, 0));
    polygon.push_back(Point(0, 0));
    polygon.push_back(Point(0, 0));
    polygon.push_back(Point(0, 0));
}

// 四边形,梯形,平行四边形,矩形,正方形.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

int main()
{

    Quadrilateral a;
    cin >> a;
    cout << fixed << setprecision(2) << a.getPerimeter();
    cout << ' ';
    cout << a.getArea2() << endl;

    Trapezoid tr(a);
    if (tr.check()) cout << "YES\n";
    else cout << "NO\n";

    //套娃警告
    Parallelogram par(a);
    if (par.check())
    {
        Rectangle rec(par);
        if (rec.check())
        {
            Square sq(rec);
            if (sq.check()) cout << "square";
            else cout << "rectangle";
        }
        else cout << "parallelogram";
    }
    else cout << "NO";

}



