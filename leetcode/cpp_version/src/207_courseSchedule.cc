#include <iostream>
#include <cstring>
#include <vector>
#include <unordered_set>

using std::vector;
using std::unordered_set;


class Graph {
public:
  Graph(int numCourses, vector<vector<int>>& prerequisites) {fillGraph(numCourses, prerequisites);}

  void displayGraph() {
    int vertex = 0;
    for(const struct adjList & adjlist : *graph) {
      std::cout <<( adjlist.valid ? "valid vertex " : "invalid vertex ") << vertex << std::endl;
      std::cout << "the ingress list is" << std::endl;
      for(const int & ingressVertex : adjlist.ingress)
	std::cout << " " << ingressVertex;
      std::cout << std::endl;
      std::cout << "the egress list is: " << std::endl;
      for(const int & egressVertex : adjlist.egress)
	std::cout << " " << egressVertex;
      std::cout << std::endl;
      vertex++;
    }
  }
  void fillGraph(int numCourses, vector<vector<int>>& prerequisites) {
    graph = new vector<struct adjList>(numCourses, {false});
    for( const vector<int> & prerequisite : prerequisites) {
      int source = prerequisite[0];
      int sink = prerequisite[1];
      graph->at(sink).egress.insert(source); graph->at(sink).valid = true;
      graph->at(source).ingress.insert(sink); graph->at(sink).valid = true;
    }
    return;
  }
  bool isEmpty() {
    for(const struct adjList & vertex : *graph) {
      if(vertex.valid == true) {
	return false;
      }
    }
    return true;
  }
  void removeVertex() {
    bool moreToRemove = false;
    do {
      moreToRemove = false;
      for(int curVertex = 0; curVertex < graph->size(); curVertex++ ) {
    	if(graph->at(curVertex).valid && graph->at(curVertex).ingress.empty()) {
    	  moreToRemove = true;
    	  for(const int & adjVertex : graph->at(curVertex).egress) {
    	    graph->at(adjVertex).ingress.erase(curVertex);
    	  }
	  graph->at(curVertex).valid = false;
    	}
      }
    } while(moreToRemove == 1);
    return;
  }
  
private:
  /* represent directed graph
     0 <----- 1 <---- 2
     [ [0, [1], [ ]],
       [1, [2], [0]],
       [2, [ ], [2]]
     ]
   */
  struct adjList {
    bool valid;
    unordered_set<int> ingress;
    unordered_set<int> egress;
  };
  vector<struct adjList> *graph = NULL;
};

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
      graph = new class Graph(numCourses, prerequisites);
      graph->removeVertex();
      //graph->displayGrapha();
      return graph->isEmpty();
    }

private:
  class Graph* graph;
};

int main() {
  class Solution sol;
  vector<vector<int>>input({{0,1}, {0,2}, {1,2}});
  std::cout << (sol.canFinish(3, input) ? "can finish" : "can not finish") << std::endl;
  return 0;
}
