#ifndef BOARD_
#define BOARD_
#include <string>
#include "Direction.hpp"
#include <vector>
#include <limits>

namespace ariel
{
    typedef unsigned int uint; // typdef for uint 
    /**
     * Class Point perpouse is to store a point data like x and y cordinates.
    */
    class Point // helper class 
    {
        public:
        uint x,y; 
        Point() // default constructor 
        {
            this->x=0;
            this->y=0;
        }
        Point(uint x, uint y) // not default constructor 
        {
            this->x = x;
            this->y = y;
        }
        Point * take_max  (Point other) const;
        Point * take_min (Point other) const;
    };
    class Board
    {
        public:
            // keep pointers to min  and max 
            Point * min;
            Point * max;
            std::vector<std::vector<char>> * matrix;
            bool start; // say if board is at the begining 
            Board() // default constructor 
            {
                this->start = true;
                this->matrix = new std::vector<std::vector<char>>();
            }
            ~Board() // default destructor 
            {   // freeing all the pointers 
                delete this->min;
                delete this->max;
                delete this->matrix;
            }
            // declare public methods 
            std::string read(uint x,uint y,Direction direction,uint size);
            void post(uint x, uint y, Direction direction,std::string str);
            void show() const;
        private:
            // declare private methods 
            uint addlines(bool start,uint count,uint size) const;
            uint addtoline(uint line,bool start,uint size) const;
    };

}


#endif