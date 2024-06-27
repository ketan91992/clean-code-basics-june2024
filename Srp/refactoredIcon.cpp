#include <iostream>
 
class Icon
{
    public:
    Icon() {}
    float speed, glow, energy;
    int x, y;
    virtual void move() = 0;
    virtual void flair() = 0;
};
 
class spinner : public Icon
{
    public:
    spinner() {}
    bool clockwise; // need for spinner
    bool expand; // need for spinner
    void spin() {}
    void move() { std::cout <<"I am in spinner move"<<std::endl;}
    void flair() {std::cout <<"I am in spinner flair"<<std::endl; }
};
 
class slider : public Icon
{
    public:
    slider() {}
    bool vertical; // need for slider
    int distance; // need for slider
    void slide() {}
    void move() {}
    void flair() {}
};
 
class hopper : public Icon
{
    public:
    hopper() {}
    bool visible; // need for hopper
    int xcoord, ycoord; // need for hopper
    void hop() {}
    void move() {}
    void flair() {}
};
 
int main() {
    spinner obj2;
    obj2.move();
    obj2.flair();
    return 0;
}
