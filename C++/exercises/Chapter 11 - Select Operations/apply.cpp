#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

class Shape
{
public:
    Shape(int e, double s) : edges{ e }, sz{ s } {}
    Shape() : edges{ 0 }, sz{ 10 } {}
    
    int edge() const { return edges; }
    void setEdge(int e) { edges = e; }
    
    double size() const { return sz; }
    double dilate(double f) { return sz *= f; }
    
private:
    int edges;
    double sz;
};

void shrink(Shape *s)
/* shrink shape to size of 1 */
{
    s->dilate(1/s->size());
}

void apply(std::vector<Shape *> v, std::function<void(Shape *)> f)
{
    for (auto &shape : v)
        f(shape);
}

int main()
{
    /* create shapes */
    std::vector<Shape *> shapes;
    for (int i = 0; i < 5; i++)
        shapes.push_back(new Shape(4, 100));
    
    auto printShape = [](Shape *s)
    { 
        std::cout << "Size: " << s->size() << '\n';
        std::cout << "Edges: " << s->edge() << '\n';
    };
    
    /* print shape data */
    for_each(shapes.begin(), shapes.end(), printShape);
    /* modify shape data */
    apply(shapes, shrink);
    /* view shape data after modifications */
    for_each(shapes.begin(), shapes.end(), printShape);
    
    /* delete shapes */
    for (auto s : shapes)
        delete s;
    return 0;
}