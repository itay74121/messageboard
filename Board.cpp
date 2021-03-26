#include "Board.hpp"
#include "Direction.hpp"
#include <iostream>
#include <string>
#include <cmath>

using ariel::Direction;
using namespace std;

namespace ariel
{

    Point * Point::take_max(Point other)
    {
        Point * p = new Point();
        p->x = max(this->x,other.x);
        p->y = max(this->y,other.y);
        return p;
    }
    Point * Point::take_min(Point other)
    {
        Point * p = new Point();
        p->x = min(this->x,other.x);
        p->y = min(this->y,other.y);
        return p;
    }
    bool Board::inside_(Point other)
    {
        if(other.y <= this->max->y && other.x <= this->max->x && other.y >= this->min->y && other.x >= this->min->x)
        {
            return true;
        }
        return false;
    }    
    bool Board::inside_Point(uint x, uint y)
    {
        Point p = Point(x,y);
        return this->inside_(p);
    }
    string Board::read(uint x,uint y,Direction direction,uint size)
    {        
        Point p = Point(x,y);
        string s;
        uint temp = size;
        for (size_t i = 0; i < size; i++)
        {
            s += (this-inside_(p))? this->matrix->at(p.x).at(p.y) : '_';
            p.x += (direction == Direction::Horizontal) ? 0:1;
            p.y += (direction == Direction::Horizontal) ? 1:0;
        }
        return s;
    }

    uint Board::post(uint x, uint y, Direction direction,string str)
    {        
        Point temp = (direction == Direction::Horizontal)? Point(x,y+str.length()-1):Point(x + str.length()-1,y);
        if(start)
        {
            start = false;
            this->min = new Point(x,y);
            this->max = new Point(x,y);
        }
        if(this->inside_Point(x,y) && this->inside_(temp))
        {   
            Point t = Point(x,y);
            for(uint i = 0;i < str.length();i++)
            {
                this->matrix->at(t.x-this->min->x).at(t.y - this->min->y) = str.at(i);
                t.x = (direction==Direction::Horizontal)? t.x:t.x + 1;
                t.y = (direction==Direction::Vertical)? t.y:t.y + 1;
            }
            return str.length();
        }
        else
        {
            Point * max = temp.take_max(*(this->max));
            Point * min = temp.take_min(*(this->min));  
            uint addstart = (this->min->y == min->y)?0:this->min->y - min->y+1;
            uint addend = (max->y == this->max->y)? 0:max->y - this->max->y;
            for (size_t i = 0; i < this->matrix->size() && (addend>0 || addstart>0); i++)
            {
                (addstart>0)?addtoline(i,true,addstart):0;
                (addend>0)?addtoline(i,false,addend):0;
            }
            uint newsize = max->y - min->y + 1;
            addstart = (this->min->x == min->x)? 0:this->min->x - min->x+1;
            addend = (max->x == this->max->x) ? 0:max->x - this->max->x+1;
            (addstart>0)?addlines(true,addstart,newsize):0;
            (addend>0)?addlines(false,addend,newsize):0;
            delete this->max;
            delete this->min;
            this->max = max;
            this->min = min;
            return this->post(x,y,direction,str);
        }
    }

    uint Board::addlines(bool start,uint count,uint size)
    {
        if (count == 0)
            return 0;
        vector<char> temp = vector<char>(size,'_');
        this->matrix->insert(start?this->matrix->begin():this->matrix->end(),count,temp);
        return size;
    }
    uint Board::addtoline(uint line,bool start,uint size)
    {
        if (size == 0)
            return 0;
        vector<vector<char>> * mat = this->matrix;
        auto position = start ? mat->at(line).begin():mat->at(line).end();
        mat->at(line).insert(position,size,'_');
        return size;
    }
    void Board::show()
    {
        uint line = this->min->x;
        for (size_t i = 0; i < this->matrix->size(); i++)
        {
            cout << line <<": ";
            for (size_t j = 0; j < this->matrix->at(i).size(); j++)
            {
                cout << this->matrix->at(i).at(j);
            }
            cout << endl;
            line++;
        }
        cout << endl;
    }
    void Board::clear()
    {
        
    }

}