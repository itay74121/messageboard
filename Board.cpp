#include "Board.hpp"
#include "Direction.hpp"
#include <iostream>
#include <string>
#include <cmath>

using ariel::Direction;
using namespace std;

namespace ariel
{

    Point * Point::take_max(Point other) const 
    {
        Point * p = new Point();
        p->x = max(this->x,other.x); // take maximums between X's 
        p->y = max(this->y,other.y); // do the same with Y's
        return p;
    }
    /**
     * Just like the method above but with minimum
    */
    Point * Point::take_min(Point other) const
    {
        Point * p = new Point();
        p->x = min(this->x,other.x);
        p->y = min(this->y,other.y);
        return p;
    }
    /**
     * Check if a point is within a boards borders.
    */
    bool inside_(Point other,Board * b)
    {
        if (b->max == NULL || b->min == NULL){return false;}
        return ( other.y <= b->max->y &&other.x <= b->max->x  &&other.y >= b->min->y  && other.x >= b->min->x);
    }    
    /**
     * Using the inside_ function but takes argument as x,y and not 
       a Point.
    */
    bool inside_Point(uint x, uint y,Board * b)
    {
        Point p = Point(x,y);
        return inside_(p,b);
    }
    /**
     * Read a line in either vertical or horizontal from the board
    */
    string Board::read(uint x,uint y,Direction direction,uint size)
    {        
        Point p = Point(x,y);
        string s;
        for (size_t i = 0; i < size; i++)
        {
            //if the point is not inside the board's borders append an underscore '_'
            s += (inside_(p,this)) ? this->matrix->at(p.x - this->min->x).at(p.y-this->min->y):'_';
            p.x += (direction == Direction::Horizontal) ? 0:1; // advance x and y respectivley to direction
            p.y += (direction == Direction::Horizontal) ? 1:0;
        }
        return s;
    }
    /**
     * Post a message on the board with a direction
    */
    void Board::post(uint x, uint y, Direction direction,string str)
    {   
        // take the point where it would finish writing to the board      
        Point temp = (direction == Direction::Horizontal)? Point(x,y+str.length()-1):Point(x + str.length()-1,y);
        if(start) // if this is the beginging we would excpect the matrix to empty too
        {
            start = false;
            this->min = new Point(x,y); // set the pointers of points to some points 
            this->max = new Point(x,y);
        }
        if(inside_Point(x,y,this) && inside_(temp,this))
        {   // if we write totaly within the borders there is no need 
            // in extending the board
            Point t = Point(x,y);
            for(uint i = 0;i < str.length();i++)
            {
                this->matrix->at(t.x-this->min->x).at(t.y - this->min->y) = str.at(i); // write the i char of str to the board 
                t.x = (direction==Direction::Horizontal)? t.x:t.x + 1; // advance t respectivley to direction 
                t.y = (direction==Direction::Vertical)? t.y:t.y + 1;
            }
        }
        else // if we are not within borders there is a need in extending the matrix
        {
            Point * max = temp.take_max(*(this->max)); // take the true max 
            Point * min = Point(x,y).take_min(*(this->min));  // take the true min 
            uint addstart = (this->min->y == min->y)?0:this->min->y - min->y+1; // calculate how much to add to the start and end of each line 
            uint addend = (max->y == this->max->y)? 0:max->y - this->max->y+1;
            for (size_t i = 0; i < this->matrix->size() && (addend>0 || addstart>0); i++) // loop through lines 
            {
                (addstart>0)?addtoline(i,true,addstart):0; // add to begining of line and then the end
                (addend>0)?addtoline(i,false,addend):0;
            }
            uint newsize = max->y - min->y + 1; // claculate size of lines to add to start 
            addstart = (this->min->x == min->x)? 0:this->min->x - min->x+1; // calculate how many lines to add at start and end 
            addend = (max->x == this->max->x) ? 0:max->x - this->max->x+1;
            (addstart>0)?addlines(true,addstart,newsize):0; // adding the lines 
            (addend>0)?addlines(false,addend,newsize):0;
            ((addend + addstart)==0 && this->matrix->empty()) ? addlines(true,1,newsize):0;// case of an empty matrix 
            delete this->max; // free last two pointers 
            delete this->min;
            this->max = max; // point them to new true max and min 
            this->min = min;
            this->post(x,y,direction,str); //write the str using post now that the borders are adjusted to the what we need 
        }
    }
    /**
     * add count many vectors whos size is size,
     * and return back the size. function is constant since it's not changing the object 
     * itself, only the pointer which the object is pointing at.
    */
    uint Board::addlines(bool start,uint count,uint size) const
    {
        if (count == 0 || size == 0) {return 0;} // default do nothing
        vector<char> temp = vector<char>(size,'_');
        this->matrix->insert(start?this->matrix->begin():this->matrix->end(),count,temp); 
        return size;
    }
    /**
     * add to line number 'line' either end or start 'size' underscores.
     * and return the size.
    */
    uint Board::addtoline(uint line,bool start,uint size) const
    {
        if (size == 0){return 0;}
        vector<vector<char>> * mat = this->matrix;
        auto position = start ? mat->at(line).begin():mat->at(line).end();
        mat->at(line).insert(position,size,'_');
        return size;
    } 
    /**
     * Presents the board so far.
     * void.
    */
    void Board::show() const
    {
        uint line = this->min->x;
        for (size_t i = 0; i < this->matrix->size(); i++)
        {
            cout << line <<": "; // start of line 
            for (size_t j = 0; j < this->matrix->at(i).size(); j++)
            {
                cout << this->matrix->at(i).at(j); // print what is inside 
            }
            cout << endl; // \n to end the line 
            line++; // advance the line 
        }
        cout << endl;
    }

}