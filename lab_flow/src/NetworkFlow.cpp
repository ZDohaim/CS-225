#include <vector>
#include <algorithm>
#include <set>

#include "cs225_graph/graph.h"
#include "cs225_graph/edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE

  std::vector<Vertex> Vecticies = startingGraph.getVertices();


  for (Vertex v : Vecticies){
    residual_.insertVertex(v);
    flow_.insertVertex(v);
  }
  vector<Edge> edges = startingGraph.getEdges();
  for (Edge e : edges){
    //res normal
    if (!residual_.insertEdge(e.source, e.dest)){
      std::cout << "ERROR inserting edge" << std::endl;
    } 
    residual_.setEdgeWeight(e.source, e.dest, e.getWeight());
    //res opposite 0
    if (!residual_.insertEdge(e.dest, e.source)){
      std::cout << "ERROR inserting edge" << std::endl;
    } 
    residual_.setEdgeWeight(e.dest, e.source, 0);
    //flow
    if (!flow_.insertEdge(e.source, e.dest)){
      std::cout << "ERROR inserting edge" << std::endl;
    } 
    flow_.setEdgeWeight(e.source, e.dest, 0);
  }

}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, 
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @param path   The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
   Vertex prev = path[0];
  int cap = residual_.getEdgeWeight(prev, path[1]);
  for (Vertex v : path){
    if (prev != v){
      int w = residual_.getEdgeWeight(prev, v);
      if (w < cap){
        cap = w;
      } 
    }
    prev = v;
  }
  return cap;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  vector<Vertex> path_;
  while (findAugmentingPath(source_, sink_, path_)){
    int cap = pathCapacity(path_);
    Vertex prev = path_[0];
    for (Vertex v : path_){
      if (prev != v){
        if (flow_.edgeExists(prev, v)){
            flow_.setEdgeWeight(prev, v, flow_.getEdgeWeight(prev, v) + cap);
        }
        else{
            flow_.setEdgeWeight(v, prev, flow_.getEdgeWeight(v, prev) - cap);
        }
        residual_.setEdgeWeight(prev, v, residual_.getEdgeWeight(prev, v) - cap);
        residual_.setEdgeWeight(v, prev, residual_.getEdgeWeight(v, prev) + cap);
      }
      prev = v;
    }
  }
  int maxFlow = 0;
  for (Vertex v : flow_.getAdjacent(source_)){
    maxFlow += flow_.getEdgeWeight(source_, v);
  }
  maxFlow_ = maxFlow;
  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}

