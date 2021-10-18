#include <bits/stdc++.h>
#include <iostream>
#include <regex>
#include<vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
struct Edge {
   int src, dest, weight;
};
struct Graph {
   int V, E;
   struct Edge * edge;
};
struct Graph * createGraph(int V, int E) {
   struct Graph * graph = new Graph;
   graph -> V = V;
   graph -> E = E;
   graph -> edge = new Edge[E];
   return graph;
}
void printArr(int dist[], int n) {
   printf("Vertex   Distance from Source\n");
   for (int i = 0; i < n; ++i)
      printf("%d \t\t %d\n", i+1, dist[i]);
}
void BellmanFord(struct Graph * graph, int src) {
   int V = graph -> V;
   int E = graph -> E;
   int dist[V];
   for (int i = 0; i < V; i++)
      dist[i] = INT_MAX;
   dist[src] = 0;
   for (int i = 1; i <= V - 1; i++) {
      for (int j = 0; j < E; j++) {
         int u = graph -> edge[j].src;
         int v = graph -> edge[j].dest;
         int weight = graph -> edge[j].weight;
         if (dist[u] != INT_MAX && (dist[u] + weight < dist[v])) {
            dist[v] = dist[u] + weight;
         }
      }
   }
   for (int i = 0; i < E; i++) {
      int u = graph -> edge[i].src;
      int v = graph -> edge[i].dest;
      int weight = graph -> edge[i].weight;
      if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
         printf("Graph contains negative weight cycle");
         return;
      }
   }

   printArr(dist, V);

   return;
}
int main() {
   int V = 7301;
   int E = 65053;
   int j=-2;
   struct Graph * graph = createGraph(V, E);
   fstream newfile;
   newfile.open("out.chess", ios:: in );
   if (newfile.is_open()) {
      string tp;
      while (getline(newfile, tp)) {
         regex regex("([0-9/-]+)");
		 if(j<0){
		 	j++;
			 continue;
			 
		 }
         vector < std::string > out(
            sregex_token_iterator(tp.begin(), tp.end(), regex, 1),
            sregex_token_iterator()
         );
		  int i=1;
         for (auto & s: out) {
            if (i == 1) {
               graph -> edge[j].src = stoi(s) - 1;
            }
            else if (i == 2) {
               graph -> edge[j].dest = stoi(s) - 1;
			} 
            else if(i==3){
               graph -> edge[j].weight = stoi(s);
               j++;
            }
            i++;
			
         }
      }
      newfile.close();
   }

   BellmanFord(graph, 0);

   return 0;
}
