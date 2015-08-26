#include "Pathfinding.hpp"
using std::pair;

std::map<std::pair<int, int>, bool> Pathfinding::graph;

std::vector<Point> Pathfinding::find_path(pair<int, int> const start, pair<int, int> const finish)
{
    //Offset
    Graph open_list,    //All node already evaluate
          closed_list;  //Node can be choose for the final path
    pair<int, int> current = start; //Current node selected

    //Starting loop
    while(current != finish)
    {
        //Evaluate his 8 neigthbors
        for(int _x(-1); _x < 2; _x++) for(int _y(-1); _y < 2; _y++)
        {
            pair<int, int> actual(current.first  + _x, current.second + _y);

            //Node can be evaluate
            if(actual.first < 0  || actual.first  >= limit_x ||
               actual.second < 0 || actual.second >= limit_y)          continue;
            if(!Pathfinding::exist(actual, closed_list)) continue;
            if(Pathfinding::graph[actual])               continue;

            //Evaluation
            Node n;
            n.G = closed_list[current].F;
            n.H = heuristic(current, actual);

            n.F = n.G + n.H;
            n.parent = current;

            //Add to the open_list
            //Already inside
            if(Pathfinding::exist(actual, open_list))
            {
                //Is this one best ?
                if(open_list[actual].F > n.F)
                //If yes, remplace the other
                {
                    open_list[actual] = n;
                }
                //If no, go away !
            }
            else {
                open_list[actual] = n;
            }
        }

        //Search the best node in the open_list
        pair<int, int> best;
        uint min(0);
        for(auto& n : open_list)
        {
            if(min == 0 || n.second.F < min)
            {
                min = n.second.F;
                best = n.first;
            }
        }

        //Add it to the closed_list
        closed_list[best] = open_list[best];

        //Define it as the current node
        current = best;

        //Remove it from the open_list
        open_list.erase(best);
    }

    std::vector<Point> path;

    //Construct the path
    current = finish;
    while(current != start)
    {
        path.push_back(Point({(float)current.first * 32 + 16, (float)current.second * 32 + 16}));
        current = closed_list[current].parent;
    }

    return path;
}

bool Pathfinding::exist(pair<int, int> n, Graph& graph)
{
    if(graph.find(n) != graph.end()) return true;
    else return false;
}


int Pathfinding::heuristic(std::pair<int, int> p1, std::pair<int, int> p2) {
    return (p2.first - p1.first) * (p2.first - p1.first) + (p2.second - p1.second) * (p2.second - p1.second);
}
