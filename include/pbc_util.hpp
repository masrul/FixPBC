/**
 * @author      : Masrul Huda (mail2masrul@gmail.com)
 * @file        : pbc_util
 * @created     : Saturday Oct 15, 2022 18:12:22 CDT
 */

#ifndef PBC_UTIL_HPP

#define PBC_UTIL_HPP

#include "gmx_traj.hpp" 
#include <vector>
#include <map> 
#include <iostream>
#include <queue>

namespace PBCUtil 
{
class Graph {
public:
    std::map<size_t,std::vector<size_t>>adjList;
    std::map<size_t,bool> visited; 
    std::vector<size_t>nodes;
    std::vector<std::vector<size_t>>sequence_ref; 

    Graph(std::vector<std::vector<size_t>>& edges){
        // Get unique nods from edges 
        std::set<size_t> unique_nodes;
        for (const auto& edge : edges){
            unique_nodes.insert(edge[0]);
            unique_nodes.insert(edge[1]);
        }

        // Set nodes 
        for (const auto& node : nodes){
            nodes.push_back(node);
            adjList[node] = std::vector<size_t>{};
        }

        // Set edges 
        for (const auto& edge : edges){
            adjList[edge[0]].push_back(edge[1]);
            adjList[edge[1]].push_back(edge[0]);
        }
    }

    void traverse(size_t start){
        // set visited false 
        for (auto node : nodes)
            visited[node] = false;
        
        sequence_ref.clear();
        _BFS(start);
    }

private: 
    void _BFS(size_t node){
        // Slightly modified BFS with ref node for each travel
        visited[node]=true; 
        std::queue<size_t> q;
        q.push(node);

        while (!q.empty()) {
            size_t current = q.front();
            q.pop();

            for (auto neigh : adjList[current]){
                if (!visited[neigh]){
                    sequence_ref.push_back({current,neigh});
                    q.push(neigh);
                    visited[neigh] = true; 
                }
            }
        }
    }
};

void make_whole(GMXTraj& traj, size_t mol_id, std::vector<std::vector<size_t>> bonds){

    size_t rIDx, cIDx; 
    float dx,dy,dz;
    size_t sIDx = traj.molecule_trackers[mol_id].sIDx;
    auto& pos = traj.pos; 
    auto& box = traj.box;     
    float lx = box[0][0];
    float ly = box[1][1];
    float lz = box[2][2];
    float hlx = 0.5*box[0][0];
    float hly = 0.5*box[1][1];
    float hlz = 0.5*box[2][2];
    
    Graph graph{bonds}; 
    graph.traverse(0); // start index 
    
    for (const auto& visited_site : graph.sequence_ref){
        rIDx = visited_site[0] + sIDx;
        cIDx = visited_site[1] + sIDx;

        dx = pos[cIDx][0] - pos[rIDx][0];
        dy = pos[cIDx][1] - pos[rIDx][1];
        dz = pos[cIDx][2] - pos[rIDx][2];

        if (dx > hlx) pos[cIDx][0] -=lx;
        else if (dx < -hlx) pos[cIDx][0] +=lx;

        if (dy > hly) pos[cIDx][1] -=ly;
        else if (dy < -hly) pos[cIDx][1] +=ly;

        if (dz > hlz) pos[cIDx][2] -=lz;
        else if (dz < -hlz) pos[cIDx][2] +=lz;

    }
}


} // PBCUtil

#endif /* end of include guard PBC_UTIL_HPP */

