#ifndef BOARD_
#define BOARD_
#include <string>
#include "Direction.hpp"
#include <vector>
#include <limits>

// switches for 
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

namespace ariel
{
    typedef unsigned int uint;
    class Point // helper class 
    {
        public:
        uint x,y;
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
        Point * take_max (Point other);
        Point * take_min (Point other);
    };
    class Board
    {
        public:
            Point * min;
            Point * max;
            std::vector<std::vector<char>> * matrix;
            bool start;
            Board()
            {
                this->start = true;
                this->matrix = new std::vector<std::vector<char>>();
            }
            ~Board()
            {
                delete this->min;
                delete this->max;
                delete this->matrix;
            }
            std::string read(uint x,uint y,Direction direction,uint size);
            void post(uint x, uint y, Direction direction,std::string str);
            void show();
            void clear();
        private:
            uint addlines(bool start,uint count,uint size);
            uint addtoline(uint line,bool start,uint size);
    };

}


#endif