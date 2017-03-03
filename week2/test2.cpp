#include <iostream>
using namespace std;

class Circle{
    private :
        double radius;
        double length;
    public :
        Circle();
        ~Circle();
        void setLength(double len);
        double getLength();
};

Circle::Circle(){
    cout << "this is constructor" << endl;
}
Circle::~Circle(){
    cout << "this is destructor" << endl;
}

void Circle::setLength(double len){
    length = len;
}
double Circle::getLength(){
    return length;
}

int main(int argc, char const *argv[]) {
    Circle c;
    c.setLength(32.1);
    cout << c.getLength() << "??? " << endl;
    return 0;
}
