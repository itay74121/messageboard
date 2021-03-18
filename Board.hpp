#ifndef BOARD_
#define BOARD_
#include <string>
#include "Direction.hpp"
#include <array>

namespace ariel
{
    typedef unsigned int uint;
    class Point // helper class 
    {
        uint x,y;
        public:
        Point()
        {
            this->x=0;
            this->y=0;
        }
        Point(uint x, uint y)
        {
            this->x = x;
            this->y = y;
        }
        Point take_max (Point other);
        Point take_min (Point other);
    };
    class Board
    {
        Point * min;
        Point * max;
        public:
            Board()
            {
                this->min = new Point(0,0);
                this->max = new Point(0,0);
            }
            std::string read(uint x,uint y,Direction direction,uint size);
            uint post(uint x, uint y, Direction direction,std::string str);
            void show();
            void clear();
    };

}


#endif