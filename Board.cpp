#include "Board.hpp"
#include "Direction.hpp"
#include <string>

using namespace std;

namespace ariel
{
    Point Point::take_max(Point other)
    {
        Point p;
        return p;
    }
    Point Point::take_min(Point other)
    {
        Point p;
        return p;
    }
    string Board::read(uint x,uint y,Direction direction,uint size)
    {
        return string(" ");
    }

    uint Board::post(uint x, uint y, Direction direction,std::string str)
    {
        return 0;
    }
    
    void Board::show()
    {

    }
    void Board::clear()
    {
        
    }
}