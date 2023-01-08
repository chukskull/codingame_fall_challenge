#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <queue>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <chrono>
#include <vector>
#include <algorithm>
#include <iostream>

#pragma GCC optimize("Ofast","unroll-loops", "omit-frame-pointer", "inline")
#pragma GCC option("arch=native", "tune=native", "no-zero-upper")
#pragma GCC target("rdrnd", "popcnt", "avx", "bmi2")

using namespace std;

#define ROBOT_X all_squares._My_units[i].x 
#define ROBOT_Y all_squares._My_units[i].y
#define MIDDLE  (all_squares._map.w / 2)
#define MIDDLE_H  (all_squares._map.h / 2)
#define MAP_WIDTH All_squares._map.w
#define MAP_HEIGHT  All_squares._map.h

static constexpr    int NONE = -1;
static constexpr    int OPP = 0;
static constexpr    int ME = 1;

int g_leb = 0;
int g_side_2 = 0;
int g_side_v2 = 0;
int g_spawn  = 0;


int g_take_back = 0;

struct Tile {
    int x, y, scrap_amount, owner, units;
    bool recycler, can_build, can_spawn, in_range_of_recycler;
    bool mid = false;
    int d5el = 1;
   
};

int dr[4] = {0, 0, -1, 1};
int dc[4] = {-1, 1, 0, 0};

int g_turn = 1;
int g_h;
int g_w;
int top_lock = 0;
int bottom_lock = 0;

int dr_to_the_left[4] = {0, -1, 1, 0};
int dc_to_the_left[4] = {-1, 0, 0, 1};

int dr_to_the_right[4] = {0, -1, 1, 0};
int dc_to_the_right[4] = {1, 0, 0, -1};

int dr_to_the_r_first[3] = {0, -1, 1};
int dc_to_the_r_first[3] = {1, 0, 0};

int dr_to_the_r_first_2[3] = {0, 1, -1};
int dc_to_the_r_first_2[3] = {1, 0, 0};

int dr_to_the_l_first[3] = {0, -1, 1};
int dc_to_the_l_first[3] = {-1, 0, 0};

int dr_to_the_l_first_2[3] = {0, 1, -1};
int dc_to_the_l_first_2[3] = {-1, 0, 0};


int dr_sides[3] = {0 ,1, -1};
int dc_sides[3] = {1, 0, 0};
//row
int dr_row_sides[3] = {1, -1, 0};
int dc_row_sides[3] = {0, 0, 1};

int dr_sides_a[3] = {0 ,-1, 1};
int dc_sides_a[3] = {1, 0, 0};

int dr_sides2[3] = {0 ,1, -1};
int dc_sides2[3] = {-1, 0, 0};
// row

int dr_row_sides2[3] = {1, -1, 0};
int dc_row_sides2[3] ={0, 0, -1};
//
int dr_sides2_a[3] = {0 ,-1, 1};
int dc_sides2_a[3] = {-1, 0, 0};

// for voronoi

int dr_sides_v[4] = {0 ,1, -1, 0};
int dc_sides_v[4] = {1, 0, 0, -1};
//
int dr_sides2_v[4] = {0 ,1, -1, 0};
int dc_sides2_v[4] = {-1, 0, 0, 1};

int dr_fight[2] = {0 , 0};
int dc_fight_2[2] = {-1, 1};



class Robots
{
    public:
        int _x;
        int _y;
        int _middle;
    Robots(int y, int x): _y(y), _x(x)
    {

    }
    int _get_x() const
    {
        return(_x);
    }
    int _get_y() const
    {
        return(_y);
    }
};
class Map
{
    public:
        int w;
        int h;
};
class Map_M
{    public:
        int w;
        int h;
    Map_M(int x, int y):w(x), h(y)
    {

    }

};

class   Matter
{
    public:
        int my_mtr;
        int op_mtr;
};


class  Pts
{
    public:
        int x;
        int y;
        Pts(int x_, int y_): x(x_), y(y_)
        {

        };
};
class   my_all_
{
    public:
        Matter              _my_matter;
        Map                  _map;
        vector<Tile>        _squares;
        vector<Tile>        _my_squares;
        vector<Tile>        _opp_squares;
        vector<Tile>        _opp_units;
        vector<Tile>        _neutral_squares;
        vector<Tile>        _My_units;
        vector<Tile>        _my_recyclers;
        vector<Tile>        _opp_recyclers;

        void    set_map_width(int width)
        {
            this->_map.w = width;
        }

        void    set_map_height(int height)
        {
            this->_map.h = height;
        }

        int  get_map_width()const
        {
            return(this->_map.w);
        }

        int    get_map_height()const
        {
            return (this->_map.h);
        }

        void    set_my_mtr(int mtr)
        {
            this->_my_matter.my_mtr = mtr;
        }

        void    set_op_mtr(int mtr)
        {
            this->_my_matter.op_mtr = mtr;
        }

        int get_my_mtr(int mtr)const
        {
            return(this->_my_matter.my_mtr);
        }

        int get_op_mtr(int mtr)const
        {
            return(this->_my_matter.op_mtr);
        }
        bool    fusil;
        bool    fusil_const;
        void    set_fusil(int x)
        {
            fusil = fusil_bool(x);
        }
        void    set_fusil_const(int z)
        {
            fusil_const = fusil_bool(z);
        }
        bool    fusil_bool(int x)
        {
            return x > (this->get_map_width() / 2);
        }
};
class   Check
{
    public:
        int    Can_Build;
        int    Can_Spawn;      

};

class   Recycle
{
    public:
        int in_range;

};

class Scrap
{
    public:
        int scrapAM;
};
class   Cell
{
    public:
        int units;
        int owner;
        int recycle;
};
class My_all
{
    public:
        Check   _checker;
        Matter  _matter;
        Map     _map;
        Recycle _recycle;
        Scrap   _scrap;
        Cell    _cell;
        My_all(){};
        My_all(Check l, Matter o, Map d, Recycle r, Scrap s, Cell n):_checker(l), _matter(o), _map(d), _recycle(r), _scrap(s), _cell(n)
        {

        }
};

void    move_(int am, int f_x, int f_y, int to_x, int to_y )
{
    cout << "MOVE";
    cout << " ";
    cout << am;
    cout << " ";
    cout << f_x;
    cout << " ";
    cout << f_y;
    cout << " ";
    cout << to_x;
    cout << " ";
    cout << to_y;
    cout << ";";
}

void    build_(int x, int y)
{
    cout << "BUILD";
    cout << " ";
    cout << x;
    cout << " ";
    cout << y;
    cout << ";";
}

void    spawn_(int amount, int x, int y)
{
    cout << "SPAWN";
    cout << " ";
    cout << amount;
    cout << " ";
    cout << x;
    cout << " ";
    cout << y;
    cout << ";";
}




bool    AmIRight(int x, int middle)
{
    if (x < middle)
        return (false);
    else
        return(true);
}


void    to_the_sides(Robots &s, int r, My_all all)
{
  
}

class  Move_t
{

    public:
        int r;
        int c;
        Move_t(){};
        Move_t & operator=( Move_t const & rhs )
        {
	    if ( this != &rhs )
	    {
	    	this->r = rhs.r;
            this->c = rhs.c;
	    }
	    return *this;
        }
};

bool isValid(vector<vector<bool> > &vis,
             int row, int col, my_all_   &all_squares)
{
    int i;
    for(i = 0; i < all_squares._squares.size() ; i++)
    {
        if (all_squares._squares[i].x == col && all_squares._squares[i].y == row)
            break ;
    }
    if (row < 0 || col < 0
        || row >= all_squares._map.h|| col >= all_squares._map.w || all_squares._squares[i].scrap_amount == 0 || all_squares._squares[i].recycler == 1)
        return false;
    if (vis[row][col])
    {
        return false;
    }
    return true;
}

bool    if_my_robots_in_middle(my_all_  &all_squares)
{
    for(int i= 0; i < all_squares._My_units.size(); i++)
    {
        if (abs(ROBOT_X - MIDDLE) == 1)
            return true;
    }
    return false;
}

vector<int>     BFS(int r, int c, my_all_   &all_squares, vector<vector<int> > &matrix, vector<vector<char>> &my_sq, int w)
{
    vector<vector<bool> >   visited(all_squares._map.h, vector<bool> (all_squares._map.w, false));
    queue<pair<int, int> >  q;
    int                     rr = 0;
    int                     cc = 0;
    bool                    end = false;
    vector<int>             next_move(2);
    vector<int>             null;
    int count_1 = 0;
    int count_2 = 0;      

    q.push({r, c});
    visited[r][c] = true;

    while(q.size()> 0)
    {
        pair<int,int> current = q.front();
        r = current.first;
        c = current.second;
        q.pop();
        count_2++;
        assert(visited[r][c]);
        // //// //cerr << "lol" << endl;
        if (w == 1 && matrix[r][c] == 2)
        {
            // //// //cerr << "OKKK" << endl;
            end = true;
            next_move[0] = r;
            next_move[1] = c;
            break;
        }
        else if (w == 1 && matrix[r][c] == 1)
        {
             end = true;
            next_move[0] = r;
            next_move[1] = c;
            break;
        }
        else if (w == 0 && my_sq[r][c] == 'M')
        {
            end = true;
            next_move[0] = r;
            next_move[1] = c;
            break;
        }
        if (g_leb == 0 && (w == 1) && g_turn < 10)
        {
            for(int i = 0; i < 3; i++)
            {
                if(all_squares.fusil == 0 && MIDDLE_H <= r)
                {
                    rr = r + dr_to_the_r_first[i];
                    cc = c + dc_to_the_r_first[i];
                }
                if (all_squares.fusil == 0 && MIDDLE_H > r)
                {
                    rr = r + dr_to_the_r_first_2[i];
                    cc = c + dc_to_the_r_first_2[i];
                }
                if (all_squares.fusil&& MIDDLE_H <= r)
                {
                    rr = r + dr_to_the_l_first[i];
                    cc = c + dc_to_the_l_first[i];
                }
                if (all_squares.fusil && MIDDLE_H > r)
                {
                    rr = r + dr_to_the_l_first_2[i];
                    cc = c + dc_to_the_l_first_2[i];
                }
                if (isValid(visited, rr, cc, all_squares))
                {
                    visited[rr][cc] = true;
                    q.push({rr, cc});
                }  
            }
        }
        else
        {
            for(int i = 0 ; i < 4; i++)
            {
                if (all_squares.fusil_const == 0)
                {
                    rr = r + dr_to_the_right[i];
                    cc = c + dc_to_the_right[i];
                }
                if (all_squares.fusil_const)
                {
                    rr = r + dr_to_the_left[i];
                    cc = c + dc_to_the_left[i];
                }
                if (isValid(visited, rr, cc, all_squares))
                {
                    visited[rr][cc] = true;
                    q.push({rr, cc});
                }  
            }
        }
    }
  
    if (end)
    {
        return(next_move);
    }
    return (null);
}

void    defense_test_(my_all_ &all_squares)
{
    int distance = 10000000;
    int k = 0;
    for(int i= 0 ; i < all_squares._opp_units.size(); i++)
    {
        int rb = all_squares._opp_units[i].x - all_squares._my_squares[i].x;
        if (rb == 1)
        {
            if (all_squares._my_squares[i].can_build)
                build_(all_squares._my_squares[i].x, all_squares._my_squares[i].y);
        }
    }
}

void    spawn_first(my_all_  &all_squares, vector<vector<char> > &my_sq, vector<vector<int>> &matrix, vector<Tile> &copy_units)
{
    vector<int> next_spawn;
    int distance = 10000000;
    int k = 0;
    int rb = 0;
    int c = 0;
    int la_somme_de_x = 0;
    int la_somme_de_y = 0;
    int la_somme_de_x_2 = 0;
    int la_somme_de_y_2 = 0;


    if (all_squares._my_squares.size() != 0)
    {
        for (int i = 0; i < all_squares._my_squares.size(); i++)
        {

            la_somme_de_x_2 += all_squares._my_squares[i].x;
            la_somme_de_y_2 += all_squares._my_squares[i].y;
        }
        la_somme_de_x_2 /=   all_squares._my_squares.size();
        all_squares.set_fusil(la_somme_de_x_2);
        if(g_turn == 1)
            all_squares.set_fusil_const(la_somme_de_x_2);
        la_somme_de_y_2 /=   all_squares._my_squares.size();
        sort(all_squares._opp_units.begin(), all_squares._opp_units.end(), [la_somme_de_x_2, la_somme_de_y_2](struct Tile & a, struct Tile &b)
        {
            if (abs(la_somme_de_x_2 - a.x) == abs(la_somme_de_x_2 - b.x))
                return abs(la_somme_de_y_2 - a.y) < abs(la_somme_de_y_2 - b.y);
           return (abs(la_somme_de_x_2 - a.x) < abs(la_somme_de_x_2 - b.x));
        });
    }
     if (all_squares._opp_units.size() != 0)
     {
        for(int i = 0; i < all_squares._opp_units.size(); i++)
        {
            la_somme_de_x += all_squares._opp_units[i].x;
            la_somme_de_y += all_squares._opp_units[i].y;
        }
        la_somme_de_x /=   all_squares._opp_units.size();
        la_somme_de_y /=   all_squares._opp_units.size();
        sort(all_squares._My_units.begin(), all_squares._My_units.end(), [la_somme_de_x, la_somme_de_y](struct Tile & a, struct Tile &b)
        {
            if (abs(la_somme_de_x - a.x) == abs(la_somme_de_x - b.x))
                return abs(la_somme_de_y - a.y) < abs(la_somme_de_y - b.y);
           return (abs(la_somme_de_x - a.x) < abs(la_somme_de_x - b.x));
        });

         all_squares._opp_units.shrink_to_fit();
         for (int i= 0; i < all_squares._opp_units.size(); i++)
         {
             if (all_squares._opp_units.size() != 0)
                 next_spawn = BFS(all_squares._opp_units[i].y, all_squares._opp_units[i].x, all_squares, matrix, my_sq, 0);
             if (next_spawn.size() != 0)
             {
                 g_leb = 0;
                 auto it = find_if(copy_units.begin(), copy_units.end(), [next_spawn](const Tile obj) {
                     return obj.x == next_spawn[1] && obj.y == next_spawn[0];
                     });
                 if (it != all_squares._opp_units.end()) {
                     spawn_(1, next_spawn[1], next_spawn[0]);
                 }
             }
             if (next_spawn.size() == 0)
             {
                 g_leb = 1;
             }
         }      
        }
}   

bool    iis_valid(int row, int col, my_all_ &all_squares)
{
    int i;
    for(i = 0; i < all_squares._squares.size() ; i++)
    {
        if (all_squares._squares[i].x == col && all_squares._squares[i].y == row)
            break ;
    }
    if (row < 0 || col < 0
        || row >= all_squares._map.h|| col >= all_squares._map.w || all_squares._squares[i].scrap_amount == 0)
        return false;
    return true;
}
void    defense_build(my_all_   all_squares,vector<vector<int> > &my_opp)
{
    int r = 0;
    int c = 0;
    all_squares._my_squares.shrink_to_fit();
    for (int i = 0 ; i < all_squares._my_squares.size(); i++)
    {
        for (int j = 0; j < 4; j++)
        {
            r = all_squares._my_squares[i].y + dr[j];
            c = all_squares._my_squares[i].x + dc[j];
            if(iis_valid(r, c, all_squares)){
                if (my_opp[r][c] == 1)
                {
                    build_(all_squares._my_squares[i].x , all_squares._my_squares[i].y);
                    break ;
                }
            }
        }
    }
}

vector<int> BFS_for_sides(int r, int c,my_all_ &all_squares, vector<vector<int> > &matrix, int f_, int row)
{
    vector<vector<bool> >   visited(all_squares._map.h, vector<bool> (all_squares._map.w, false));
    queue<pair<int, int> >  q;
    int                     rr = 0;
    int                     cc = 0;
    bool                    end = false;
    vector<int>             next_move(4);
    vector<int>             null;
    int flag = 0;

    q.push({r, c});
    visited[r][c] = true;
    while(q.size()> 0)
    {
        pair<int,int> current = q.front();
        r = current.first;
        c = current.second;
        q.pop();
        if (matrix[r][c] == 1)
        {
            end = true;
            next_move[0] = r;
            next_move[1] = c;
            break;
        }
        for(int i = 0 ; i < 4; i++)
        {
                if (rr >= 0 && cc >= 0 && rr < all_squares.get_map_height() && cc < all_squares.get_map_width())
                {
                    if (matrix[rr][cc] == 1 && flag == 0)
                    {
                        next_move[2] = r;
                        next_move[3] = c;
                        flag = 1;
                    }
                }
                rr = r + dr[i];
                cc = c + dc[i];
            if (all_squares.fusil && f_ == 1)
            {
                if (rr >= 0 && cc >= 0 && rr < all_squares.get_map_height() && cc < all_squares.get_map_width())
                {
                    if (matrix[rr][cc] == 1 && flag == 0)
                    {
                        next_move[2] = r;
                        next_move[3] = c;
                        flag = 1;
                    }
                }
                rr = r + dr_sides[i];
                cc = c + dc_sides[i];
            }
            else if (all_squares.fusil  && f_ == 2)
            {
                if (rr >= 0 && cc >= 0 && rr < all_squares.get_map_height() && cc < all_squares.get_map_width())
                {
                    if (matrix[rr][cc] == 1 && flag == 0)
                    {
                        next_move[2] = r;
                        next_move[3] = c;
                        flag = 1;
                    }
                }
                rr = r + dr_sides_a[i];
                cc = c + dc_sides_a[i];
            }
            else if (all_squares.fusil == 0 && f_ == 1)
            {
                 if (rr >= 0 && cc >= 0 && rr < all_squares.get_map_height() && cc < all_squares.get_map_width())
                {
                    if (matrix[rr][cc] == 1 && flag == 0)
                    {
                        next_move[2] = r;
                        next_move[3] = c;
                        flag = 1;
                    }
                }
                rr = r + dr_sides2[i];
                cc = c + dc_sides2[i];
            } 
            else if (all_squares.fusil == 0 && f_ == 2)
            {
                if (rr >= 0 && cc >= 0 && rr < all_squares.get_map_height() && cc < all_squares.get_map_width())
                {
                    if (matrix[rr][cc] == 1 && flag == 0)
                    {
                        next_move[2] = r;
                        next_move[3] = c;
                        flag = 1;
                    }
                }
                rr = r + dr_sides2_a[i];
                cc = c + dc_sides2_a[i];
            }
            if (isValid(visited, rr, cc, all_squares))
            {
                visited[rr][cc] = true;
                q.push({rr, cc});
            }  
        }
    }
    if (end)
    {
        return(next_move);
    }
    return (null);
}

vector<int>    for_sides(my_all_ &all_squares, vector<vector<int> >&my_un)
{
    vector<int> a_top;
    vector<int> a_bottom;
    vector<int> next_BFT(4);

    int size = all_squares._My_units.size();
    int j = 0;                      
    int k = 0;
    int flag = 0;
    for(j = 0; j < all_squares._squares.size(); j++)
    {
        if (all_squares._squares[j].mid == 1)
        {
           if(all_squares._squares[j].scrap_amount != 0 && flag == 0)
           {
            flag = 1;
               next_BFT[0] = all_squares._squares[j].x;
               next_BFT[1] = all_squares._squares[j].y;
           }
           k = j;
        }
    }
    while (k)
    {
        if (all_squares._squares[k].mid == 1)
        {
            if (all_squares._squares[k].scrap_amount != 0)
            {
                next_BFT[2] = all_squares._squares[k].x;
                next_BFT[3] = all_squares._squares[k].y;
                break ;
            }
        }
        k--;
    }
    return (next_BFT);
}

void    tactic_1(my_all_ &all_squares, vector<int> &find_TB, vector<vector<int>> &my_un)
{
    vector<int> next_move;
    vector<int> next_move_2;
    int flag =0;
        find_TB = for_sides(all_squares, my_un);
        if (g_side_2 != 1)
            next_move = BFS_for_sides(find_TB[1], find_TB[0], all_squares, my_un, 1, 0);
        if (next_move.size() != 0)
        {
            if (find_TB[1] == next_move[0] && find_TB[0] == next_move[1])
            {
                g_side_2 = 1;
                my_un[next_move[0]][next_move[1]]  = 0;
            }
        }
        if (next_move.size() != 0 && g_side_2 != 1)
        {
            move_(1, next_move[1], next_move[0], next_move[3], next_move[2]);
        }

        if(g_side_v2 != 1)
            next_move_2 = BFS_for_sides(find_TB[3], find_TB[2], all_squares, my_un, 2, 0);
        if (next_move_2.size() != 0)
        {
            if(g_side_v2 == 0 && find_TB[2] == next_move_2[1] && find_TB[3] == next_move_2[0])
            {

                g_side_v2 = 1;
                my_un[next_move_2[0]][next_move_2[1]]  = 0;
            }
        }
        if(next_move_2.size() != 0 && g_side_v2 != 1)
             move_(1, next_move_2[1], next_move_2[0], next_move_2[3], next_move_2[2]);

}

void    debugger(vector<vector<char>>   &_voronoi_diagram)
{
    for(int i = 0; i < _voronoi_diagram.size(); i++)
    {
        for(int j = 0 ; j < _voronoi_diagram[i].size(); j++)
        {
            cerr <<" "<< _voronoi_diagram[i][j] << " ";
        }
        cerr << endl;
    }
}


vector<vector<char>>    BFS_My_units(vector<vector<char>>   &_voronoi_diagram, my_all_  all_squares, int r, int c)
{
     vector<vector<bool> >   visited(all_squares._map.h, vector<bool> (all_squares._map.w, false));
    queue<pair<int, int> >  q;
    int                     rr = 0;
    int                     cc = 0;
    bool                    end = false;
    vector<vector<char>>             null;
    int flag = 0;

    q.push({r, c});
    visited[r][c] = true;
        int count = 0;
    while(q.size()> 0)
    {
        pair<int,int> current = q.front();
        r = current.first;
        c = current.second;
        q.pop();
        if (count == 4)
        {
            end = true;
            break ;
        }
        if (_voronoi_diagram[r][c] == 'X')
        { 
            count++;
            _voronoi_diagram[r][c] = 'R';
        }
        else if (_voronoi_diagram[r][c] == 'B')
        {
            count++;
            _voronoi_diagram[r][c] = 'T';
        }
        for(int i = 0 ; i < 4; i++)
        {
            if (all_squares.fusil_const == 0)
            {
                rr = r + dr_sides_v[i];
                cc = c + dc_sides_v[i];
            }
            else if (all_squares.fusil_const)
            {
                rr = r + dr_sides2_v[i];
                cc = c + dc_sides2_v[i];
            }
            if (isValid(visited, rr, cc, all_squares))
            {
                if (_voronoi_diagram[rr][cc] != 'T' && _voronoi_diagram[rr][cc] != 'H' && _voronoi_diagram[rr][cc] != '7')
                {
                    visited[rr][cc] = true;
                    q.push({rr, cc});
                }
            }  
        }
    }
    if (end)
    {
        return(_voronoi_diagram);
    }
    return (null);
}

vector<vector<char>>    BFS_for_temp(vector<vector<char>>   &_voronoi_diagram, my_all_  &all_squares, vector<Tile> &_enemy_breaker,int iter)
{
  vector<vector<bool> >   visited(all_squares._map.h, vector<bool> (all_squares._map.w, false));
    queue<pair<int, int> >  q;
    int r = _enemy_breaker[iter].y;
    int c = _enemy_breaker[iter].x;
    int                     rr = 0;
    int                     cc = 0;
    bool                    end = false;
    vector<vector<char>>             null;
    int flag = 0;
    int count  = 0;

    q.push({r, c});
    visited[r][c] = true;
    while(q.size()> 0)
    {
        pair<int,int> current = q.front();
        r = current.first;
        c = current.second;
        q.pop();
        if (count == 4)
        {
            end = true;
            break ;
        }
        if (_voronoi_diagram[r][c] == 'X')
        { 
            count++;
            _voronoi_diagram[r][c] = 'B';
        }
        else if (_voronoi_diagram[r][c] == 'R')
        {
            count++;
            _voronoi_diagram[r][c] = 'T';
        }
        for(int i = 0 ; i < 4; i++)
        {
            rr = r +dr[i];
            cc = c +dc[i];
            if (isValid(visited, rr, cc, all_squares))
            {
                if (_voronoi_diagram[rr][cc] != 'T' && _voronoi_diagram[rr][cc] != 'M' && _voronoi_diagram[rr][cc] != '7')
                {
                    visited[rr][cc] = true;
                    q.push({rr, cc});
                }
            }  
        }
    }
    if (end)
    {
        return(_voronoi_diagram);
    }
    return (null);
}
void    diagram_voronoi(my_all_ &all_squares, vector<vector<char>>    &_voronoi_diagram)
{
    vector<Tile>    _enemy_breaker(all_squares._opp_units);
    vector<vector<char> > vor;

    while(1)
    {
        for(int i = 0; i < all_squares._My_units.size(); i++)
        {
            vor = BFS_My_units(_voronoi_diagram, all_squares, ROBOT_Y, ROBOT_X);
            if (vor.size() != 0)
            {
                _voronoi_diagram.clear();
                _voronoi_diagram = vor;

            }
        }
        if (vor.size() == 0)
            break;
        for(int i = 0; i < _enemy_breaker.size(); i++)
        {
            vor = BFS_for_temp(_voronoi_diagram, all_squares, _enemy_breaker, i);
            
            if (vor.size() != 0)
            {
                 _voronoi_diagram.clear();
                _voronoi_diagram = vor;
            }
        }
        if (vor.size() == 0)
            break;
    }
}
 

void    testing_voronoi(my_all_ &all_squares, vector<Pts> &inters, vector<vector<int>>  &my_un, vector<Tile>    &copy_units, vector<vector<char>> &_diagram_voronoi)
{
    vector<int> next_move;
    vector<int> Robyo;
    vector<Pts> petit_check;
    vector<bool>    units( inters.size(), false);
        for(int i = 0; i < inters.size(); i++)
        {
            next_move = BFS_for_sides(inters[i].y, inters[i].x,  all_squares, my_un, 1, 2);
            //cerr <<  units.size() << endl;
            if (next_move.size() != 0 && units[i] == false)
            {
                if (i == 0)
                    Robyo = next_move;
                units[i] = true;
                auto it = find_if(petit_check.begin(), petit_check.end(), [next_move](const Pts &obj) {
                        return obj.x == next_move[1] && obj.y == next_move[0];
                    });
                if (it == petit_check.end()) {
                    //cerr << "ipretend" << endl;
                        petit_check.push_back(Pts(next_move[1],next_move[0]));
                    }
                     auto it_2 = find_if(copy_units.begin(), copy_units.end(), [next_move](const Tile &obj) {
                        return obj.x == next_move[1] && obj.y == next_move[0];
                    });
                    if (it_2 != copy_units.end())
                    {
                        move_(1, next_move[1], next_move[0], next_move[3], next_move[2]);
                    }
            }
        }
        for(int i = 0; i < copy_units.size(); i++)
        { 
            cerr << i << endl;
            cerr << copy_units[i].x <<" " << copy_units[i].y << endl;
            auto it_3 = find_if(petit_check.begin(), petit_check.end(), [copy_units, i](const Pts &obj) {
                        return obj.x == copy_units[i].x && obj.y == copy_units[i].y;
                    });
                    if (it_3 == petit_check.end())
                    {
                    if (next_move.size() != 0)
                        move_(copy_units[i].units, copy_units[i].x, copy_units[i].y, next_move[3], next_move[2]);

                    }
        }
        petit_check.clear();
}

vector<Pts>    sorting_intersections_pts(vector<vector<char>> &voronoi_diagram, my_all_ &all_squares)
{
    vector<Pts> pts_intesc;
    int la_somme_de_x = 0;
    int la_somme_de_y = 0;
                debugger(voronoi_diagram);
    for(int i = 0; i < voronoi_diagram.size(); i++)
    {
        for(int j = 0; j < voronoi_diagram[i].size(); j++)
        {
            if (voronoi_diagram[i][j] == 'T')
            {
                auto it = find_if(all_squares._squares.begin(), all_squares._squares.end(), [i, j](const Tile obj) {
                        return obj.x == j && obj.y == i;
                        });
                    if (it != all_squares._squares.end()) {
                        if (it->owner == NONE && it->scrap_amount != 0)
                            pts_intesc.push_back(Pts(j, i));
                    }
            }
        }
    }
    if (pts_intesc.size() != 0)
    {

        if (all_squares._my_squares.size() != 0)
        {
            for (int i = 0; i < all_squares._my_squares.size(); i++)
            {

                la_somme_de_x += all_squares._my_squares[i].x;
                la_somme_de_y += all_squares._my_squares[i].y;
            }
            la_somme_de_x /=   all_squares._my_squares.size();
            la_somme_de_y /=   all_squares._my_squares.size();
            sort(pts_intesc.begin(), pts_intesc.end(), [la_somme_de_x, la_somme_de_y](struct Pts& a, struct Pts &b)
            {
                if (abs(la_somme_de_x - a.x) == abs(la_somme_de_x - b.x))
                    return abs(la_somme_de_y - a.y) > abs(la_somme_de_y - b.y);
               return (abs(la_somme_de_x - a.x) > abs(la_somme_de_x - b.x));
            });
        }
    }
    return(pts_intesc);
}
void    average_idea(my_all_    &all_squares, vector<vector<int> > &matrix, vector<vector<char> > &my_sq, vector<Tile>  &copy_units)
{
    vector<int> next_move;
    int flag = 0;
    int rand_num = rand();

    for (int i = 0; i < copy_units.size(); i++)
    {
        next_move = BFS(copy_units[i].y, copy_units[i].x, all_squares, matrix, my_sq, 1);
        if (next_move.size() != 0)
        {
                move_(copy_units[i].d5el ,copy_units[i].x, copy_units[i].y, next_move[1], next_move[0]);

        }
        else if (flag == 0)
        {
            flag =1;
            spawn_(1, all_squares._my_squares[rand_num % all_squares._my_squares.size()].x, all_squares._my_squares[rand_num % all_squares._my_squares.size()].y);
        }
    }
}

class Fight
{
    public:
        int par_y;
        int par_x;
        int x, y;
        int flag;
        Fight(int fla,int parx, int pary, int iks, int iy):flag(fla),par_x(parx), par_y(pary), x(iks), y(iy)
        {

        }
        Fight(int fla): flag(fla)
        {

        }



};
void    tactics_war(vector<pair<Tile, Tile>> &danger, my_all_ &all_squares, vector<vector<int>> &my_un, vector<Tile> &copy_units, vector<vector<int>> & my_opp)
{
    sort(danger.begin(), danger.end(), [](const pair<Tile, Tile> &a, const pair<Tile, Tile> &b) {
    return a.first.units < b.first.units;
  });


     for (auto& p : danger) {
        if(p.first.units > p.second.units)
        {
            p.first.d5el = p.second.units;
        }
        if (p.first.units < p.second.units)
        {
            my_un[p.first.y][p.first.x] = 0;
            if (p.first.units == 0)
            {
                int d = p.second.units + 1;
                if ((all_squares._my_matter.my_mtr / 10) == d)
                    spawn_(all_squares._my_matter.my_mtr / 10, p.first.x, p.first.y);
                else
                    defense_build(all_squares, my_opp);
            }
            else
            {
                int d = p.second.units +1;
                if ((all_squares._my_matter.my_mtr / 10) > d)
                    spawn_(d, p.first.x, p.first.y);
                else
                    spawn_(p.second.units ,p.first.x, p.first.y); 
                auto it = find_if(copy_units.begin(), copy_units.end(), [p](const Tile &obj) {
                    return obj.x == p.first.x && obj.y == p.first.y;
                });
                if (it != copy_units.end() && it->recycler != 1) {
                    copy_units.erase(it);
                }
            }
        }
        else if (p.first.units == 0 && p.second.units != 0)
        {
            build_(p.first.x, p.first.y);
        }
        if (p.first.units == p.second.units)
        {
            auto it = find_if(copy_units.begin(), copy_units.end(), [p](const Tile &obj) {
                return obj.x == p.first.x && obj.y == p.first.y;
                });
            if (it != copy_units.end() && it->recycler != 1) {
                copy_units.erase(it);
            }
            my_un[p.first.y][p.first.x] = 0;
            spawn_((1 + p.second.units) - p.first.units, p.first.x, p.first.y);
        }
    }
}
void    preparing_for_fight(my_all_ &all_squares, vector<vector<int> > &my_opp, vector<vector<int>> &my_un, vector<Tile> &copy_units)
{
    int r  = 0;
    int c = 0;
    vector<pair<Tile, Tile> >  danger;
     if(g_turn == 1)
            all_squares.set_fusil_const(all_squares._My_units[0].x);
    for(int i = 0; i < all_squares._my_squares.size(); i++)
    {
        for(int j = 0; j < 2; j++)
        {
            r  = all_squares._my_squares[i].y + dr_fight[j];
            c = all_squares._my_squares[i].x  + dc_fight_2[j];
            if (iis_valid(r, c, all_squares))
            {
                if (my_opp[r][c] == 1)
                {
                     auto it = find_if(all_squares._opp_units.begin(), all_squares._opp_units.end(), [c, r](const Tile obj) {
                        return obj.x == c && obj.y == r;
                        });
                    if (it != all_squares._opp_units.end()) {
                        danger.emplace_back(all_squares._my_squares[i], *it);
                    }
                }
            } 
        }
    }
    tactics_war(danger, all_squares, my_un, copy_units, my_opp);
}

void    farm_ok_sure(my_all_    &all_squares)
{
    vector<Tile> N;
    int r = 0;
    int c = 0;
    int d = 0;
    for(int i = 0 ; i < all_squares._my_squares.size(); i++)
    {
        if(all_squares._my_squares[i].units == 0)
        {

            for(int p = 0 ; p < 4; p++)
            {
                d = all_squares._my_squares[i].scrap_amount;
                r =  all_squares._my_squares[i].y + dr[p];
                c = all_squares._my_squares[i].x +  dc[p];
                if(iis_valid(r,c, all_squares))
                {
                    auto it = find_if(all_squares._squares.begin(), all_squares._squares.end(), [r, c](const Tile &obj) {
                                return obj.x == c && obj.y == r;
                                });
                            if (it != all_squares._squares.end()) {
                                N.push_back(*it);
                            }
                }
            }
                int flag = 0;
                if (N.size() > 3 && d > 2)
                {
                    for(int k = 0; k < N.size(); k++)
                    {
                        if(d >= N[k].scrap_amount)
                        {
                            flag = 1;
                        }
                    }
                    if (flag == 0)
                    {
                        if (all_squares._my_squares[i].can_build)
                            build_(all_squares._my_squares[i].x, all_squares._my_squares[i].y);
                    }
                }
        }   
        N.clear();
    }
}
void    first(my_all_   &all_squares, vector<vector<int> > &matrix, vector<vector<int> > &my_opp, vector<vector<char> > &my_sq, vector<vector<int>> &my_un, vector<vector<char>>    &_voronoi_diagram)
{
    vector<int> next_move_2;
    vector<int> find_TB(4);
    vector<Pts> inter;
    int flag = 0;
    int rand_num = rand();
    vector<Tile>    copy_units(all_squares._My_units);
    cerr << all_squares._My_units.size() << " " << g_leb << endl;
    if (all_squares._My_units.size() == 0 && g_leb == 1)
    {
        flag = 1;
        spawn_(1, all_squares._my_squares[rand_num % all_squares._my_squares.size()].x, all_squares._my_squares[rand_num % all_squares._my_squares.size()].y);
    }
    if (g_turn % 2 == 0 && all_squares.get_map_width() > 15 && g_leb == 0)
        farm_ok_sure(all_squares);
    preparing_for_fight(all_squares, my_opp, my_un, copy_units);
    spawn_first(all_squares, my_sq, matrix, copy_units);
    diagram_voronoi(all_squares ,_voronoi_diagram);
    _voronoi_diagram.resize(all_squares.get_map_height());
    inter = sorting_intersections_pts(_voronoi_diagram, all_squares);
    if (g_turn == 1)
        g_spawn = inter.size() - 2;
    if (inter.size() != 0)
        testing_voronoi(all_squares, inter , my_un, copy_units, _voronoi_diagram);
 
    average_idea(all_squares, matrix, my_sq, copy_units);
    // defense_build(all_squares, my_opp);
}



int main()
{
    srand(time(0));
    int w;
    int h;
    vector<vector<int>>     matrix;
    vector<vector<int>>     my_opp;
    vector<vector<char>>    my_squares_xD;
    vector<vector<int>>     my_units;
    vector<vector<char>>    _voronoi_diagram;
    
    cin >> w >> h; cin.ignore();
    // game loop
    while (1) {
        my_all_ All_squares;
        All_squares.set_map_height(h);
        All_squares.set_map_width(w); 
        All_squares._squares.reserve(MAP_WIDTH * MAP_HEIGHT);
        cin >> All_squares._my_matter.my_mtr >> All_squares._my_matter.op_mtr; cin.ignore();
        for (int y = 0; y < MAP_HEIGHT; y++) {
            vector<int> tmp(MAP_WIDTH, 0);
            vector<int> tmp2(MAP_WIDTH, 0);
            vector<int> my_un(MAP_WIDTH, 0);
            vector<char>    my_tmp(MAP_WIDTH, 'N');
            vector<char>    _voronoi(MAP_WIDTH, '7');
            for (int x = 0; x < MAP_WIDTH; x++) {
                int scrap_amount;
                int owner; // 1 = me, 0 = foe, -1 = neutral
                int units;
                int recycler;
                int can_build;
                int can_spawn;
                int in_range_of_recycler;
                cin >> scrap_amount >> owner >> units >> recycler >> can_build >> can_spawn >> in_range_of_recycler ; cin.ignore();
                Tile    square = {x, y, scrap_amount, owner, units, recycler == 1,
                     can_build == 1, can_spawn == 1, in_range_of_recycler == 1};
                int middle = All_squares.get_map_width() / 2;
                All_squares._squares.emplace_back(square);
                if (middle == x)
                {
                    square.mid = 1;
                    All_squares._squares.emplace_back(square);
                }
                All_squares._squares.emplace_back(square);
                if (square.owner == ME)
                {
                    if (!square.recycler)
                    {
                        my_tmp[x] = 'M';
                        _voronoi[x] ='r';
                    }
                    All_squares._my_squares.emplace_back(square);
                    if (square.units > 0)
                    {
                        _voronoi[x] = 'M';
                        my_un[x] = 1;
                        All_squares._My_units.emplace_back(square);
                    }
                    else if (square.recycler)
                    {
                        _voronoi[x] = '7';
                        All_squares._my_recyclers.push_back(square);
                    }
                }
                else if (square.owner == OPP)
                {
                    if (square.recycler != 1)
                    {
                        tmp[x] = 1;
                        _voronoi[x] ='b';
                    }
                    All_squares._opp_squares.emplace_back(square);
                    if (square.units > 0)
                    {
                        _voronoi[x] = 'H';
                        All_squares._opp_units.emplace_back(square);
                        tmp2[x] = 1;
                    }
                    else if (square.recycler)
                    {
                        _voronoi[x] = '7';
                        All_squares._opp_recyclers.emplace_back(square);
                        tmp[x] = 0;
                    }
                }
                else 
                {
                    if (square.scrap_amount > 0)
                        _voronoi[x] = 'X';
                    tmp[x] = 2;
                    All_squares._neutral_squares.emplace_back(square);
                }
            }
            my_units.emplace_back(my_un);
            my_squares_xD.emplace_back(my_tmp);
            my_opp.emplace_back(tmp2);
            matrix.emplace_back(tmp);
            _voronoi_diagram.emplace_back(_voronoi);
        }
        auto start = chrono::steady_clock::now(); 
        first(All_squares, matrix, my_opp, my_squares_xD, my_units, _voronoi_diagram);
        my_opp.clear();
        matrix.clear();
        my_squares_xD.clear();
        my_units.clear();
        _voronoi_diagram.clear();
        g_turn++;
        auto end = chrono::steady_clock::now();
        cerr << "Elapsed time in milliseconds: " ;
        if (g_turn > 0)
             cerr << chrono::duration_cast<chrono::milliseconds>(end - start).count()  << " ms" << endl;
        cout << "WAIT" << endl;
    }
}