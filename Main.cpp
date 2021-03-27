#include "Board.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace ariel;

void showmatrix(vector<vector<char>> * matrix)
{
    //cout << "running" << endl;
    char temp;
    uint size1 = matrix->size();
    uint size2;
    for (uint i = 0; i < matrix->size(); i++)
    {
        size2 = matrix->at(i).size();
        for (uint j = 0; j < matrix->at(i).size(); j++)
        {
            temp = matrix->at(i).at(j);
            cout << matrix->at(i).at(j) << " ";
        }
        cout << endl;
    }
    
}

void addline_start(vector<vector<char>> * matrix,uint size)
{
    vector<char> temp(size,'_');
    matrix->insert(matrix->begin(),1,temp);
}
void addline_end(vector<vector<char>> * matrix,uint size)
{
    vector<char> temp(size,'_');
    matrix->insert(matrix->end(),1,temp);
}
void inseret_at(uint x, uint y,vector<vector<char>> *matrix ,const char value)
{
    matrix->at(x).at(y) = value;
}
int main(int argc, char const *argv[])
{
    // vector<vector<char>> * matrix = new vector<vector<char>>();
    // addline_start(matrix,5);
    // addline_end(matrix,6);
    // inseret_at(0,2,matrix,'c');
    // addline_start(matrix,7);
    // addline_end(matrix,2);
    // showmatrix(matrix);
    // delete matrix;
    // Board b;
    // string s = "some text";
    // //cout << "lines: "<<  b.matrix->size() << endl;
    // b.post(400,500,Direction::Vertical,s);
    // //cout << "lines: "<<  b.matrix->size() << endl;
    // b.post(400,502,Direction::Vertical,s);
    // b.post(402,503,Direction::Horizontal,s);
    // b.show();
    Board b;
    b.post(0,0,Direction::Horizontal,"abc");
    b.show();
    Point temp = Point(0,2);
    cout << "The point: " << b.max->x << " "<< b.max->y << endl;
   // cout << "result: "<<inside_(temp,&b) << endl;
   //string s = b.read(0,0,Direction::Horizontal,4);
    return 0;
}
