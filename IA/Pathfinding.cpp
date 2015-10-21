#include "Pathfinding.hpp"
using std::pair;
using std::cout;
using std::endl;

std::map<std::pair<int, int>, Square> Pathfinding::graph;
bool Pathfinding::enable = true;

std::vector<Point> Pathfinding::find_path(pair<int, int> const start, pair<int, int> const finish)
{
    //Offset
    Graph open_list,    //All node already evaluate
          closed_list;  //Node can be choose for the final path
    pair<int, int> current; //Current node selected
    std::vector<Point> path; //Final path

    if(Pathfinding::graph[finish].obstacle == true) return path;

    //Add the starting node to the open_list
    open_list[start] = Node(start);

    //Until the target node isn't finded or the open_list isn't empty
    while(1 == 1)
    {
        if(Pathfinding::exist(finish, closed_list)) break;
        if(open_list.empty()) break;

        //Look for the lowest F in the open_list
        uint min(0);
        pair<int, int> current;
        for(auto& i : open_list) {
            if(min == 0 || i.second.F < min) {
                min = i.second.F;
                current = i.first;
            }
        }

        //Switch it in the closed_list
        closed_list[current] = open_list[current];
        open_list.erase(current);

        //Evaluate his neightbors
        for(int _x(-1); _x < 2; _x++) for(int _y(-1); _y < 2; _y++) if(_x != 0 && _y != 0)
        {
            pair<int, int> node = current;
            node.first  += _x;
            node.second += _y;

            //If not walkable or already in the closed_list, ignore it
            if(node.first  < 0 || node.first  > 128 * 30 / 64 ||
               node.second < 0 || node.second > 128 * 30 / 64 ||
               Pathfinding::graph[node].obstacle == true || Pathfinding::exist(node, closed_list)) continue;
            else {
                //Distance Manhattan
                int d = abs(finish.first - node.first) + abs(finish.second - node.second);
                //Determine G, H, F
                Node n(current);
                n.G = closed_list[current].F;
                n.H = Pathfinding::graph[current].H + d;
                n.F = n.H + n.G;

                //Not in open_list, add it
                if(!Pathfinding::exist(node, open_list)) {
                    open_list[node] = n;
                }
                //Alreay in ? Is his new F lowest than the previous ? If yes, switch it
                else {
                    if(open_list[node].F > n.F) {
                        open_list[node] = n;
                    }
                }
            }
        }
    }

    //Target node finded !
    if(Pathfinding::exist(finish, closed_list))
    {
        //Construct path
        pair<int, int> last_node = finish;
        while(last_node != start)
        {
            path.push_back(Point({(float)last_node.first * 64 + 32, (float)last_node.second * 64 + 32}));
            last_node = closed_list[last_node].parent;
        }
    }

    return path;
}

bool Pathfinding::enough_place(std::pair<int, int> node)
{
    for(int _x(-1); _x < 2; _x++) for(int _y(-1); _y < 2; _y++)
    {
        pair<int, int> n = node;
        n.first  += _x;
        n.second += _y;
        if(n.first  < 0 || n.first  > 128 * 30 / 64 ||
           n.second < 0 || n.second > 128 * 30 / 64 ||
           Pathfinding::graph[n].obstacle == true) {
            return false;
        }
    }
    return true;
}

bool Pathfinding::exist(pair<int, int> n, Graph& graph)
{
    if(graph.find(n) != graph.end()) return true;
    else return false;
}


int Pathfinding::heuristic(std::pair<int, int> p1, std::pair<int, int> p2) {
    return (p2.first - p1.first) * (p2.first - p1.first) + (p2.second - p1.second) * (p2.second - p1.second);
}

pair<int, int> Pathfinding::convert_pos(sf::Vector2f pos)
{
    return pair<int, int>((int)(pos.x / 64), (int)(pos.y / 64));
}
