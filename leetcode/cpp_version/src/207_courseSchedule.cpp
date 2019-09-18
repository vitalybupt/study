#include <vector>
#include <iostream>

using std::vector;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
      fillGraph(numCourses, prerequisites);
      removeVertices();
      return true;
    }
private:
  void removeVertices() {
    bool moreVertex = true;
    do{
      moreVertex = false;
      for(int i = 0; i < graph->size(); i++) {
	struct adjVertices & cur = graph->at(i);
	if(cur.ingressList != NULL) continue;
	moreVertex = true;
	struct vertices *node  = cur.egressList; 
	while(node != NULL) {
	  int val = node->val;
	  struct vertices *next = node->next;
	  struct adjVertices adj = graph->at(val);
	  struct vertices *node2 = adj.ingressList;
	  while(node2 != NULL) {
	    if(node2->val == i) {
	      //if(node2->next == NULL)
	      //node2->val = node2->next
	    }
	  }
	  delete(node);
	  node = next;
	}
	cur.egressList = NULL;
      }
    }while(moreVertex);
  }
  void fillGraph(int numCourses, vector<vector<int>>& prerequisites) {
    graph = new vector<struct adjVertices>(numCourses);
    for(const vector<int> & prerequisite : prerequisites) {
      struct vertices *source = new struct vertices; source->val = prerequisite[0]; source->next = NULL;
      struct vertices *sink = new struct vertices; sink->val = prerequisite[1]; source->next = NULL;
      if(graph->at(source->val).egressList == NULL) {
	graph->at(source->val).egressList = sink;
      } else {
	graph->at(source->val).egressList->next = sink;
      }
      if(graph->at(sink->val).ingressList == NULL) {
	graph->at(sink->val).ingressList = source;
      } else {
	graph->at(sink->val).ingressList->next = source;
      }
    }
    return;
  }
  void displayGraph() {
    for(int i = 0; i < graph->size(); i++) {
      struct vertices* vertex = graph->at(i).ingressList;
      while(vertex != NULL) {
	std::cout << "the edge from " << i << " to " << vertex->val << std::endl;
	vertex = vertex->next;
      }
      vertex = graph->at(i).egressList;
      while(vertex != NULL) {
	std::cout << "the edge from " << vertex->val << " to " << i << std::endl; 
	vertex = vertex->next;
      }
    }
  }
  void destroyGraph() {
    for(int i = 0; i < graph->size(); i++) {
      struct vertices* vertex = graph->at(i).ingressList;
      while(vertex != NULL) {
	struct vertices* tmp = vertex->next;
	delete(vertex);
	vertex = tmp;
      }
      vertex =  graph->at(i).egressList;
      while(vertex != NULL) {
	struct vertices* tmp = vertex->next;
	delete(vertex);
	vertex = tmp;
      }
    }
  }
private:
  struct vertices {
    int val;
    struct vertices* next;
  };
  struct adjVertices {
    struct vertices* ingressList;
    struct vertices* egressList;
  };
  vector<struct adjVertices> *graph = NULL;
};

int main(){
  class Solution sol;
  vector<vector<int>> input = {{0,1}, {1,0}};
  sol.canFinish(2, input);
  return 0;
}
