This is a program to compute the shortest tour (that is a path which starts at any given vertex(here the starting) 
and ends at that vertex such that the path traverses through all the vertices of the given graph once.

Compiler: g++
Input: 
->The number of vertices n
->The graph in form of adjacency matrix
Constraints on the input:
1) The weight of edge (a,b) and (b,a) is to be the same;
2) The weight of the "self edges" (a,a) are to be 0;

Ex:
n=4
{ {0, 21, 17, 49},
  {21, 0, 35, 67},
  {17, 35, 0, 31},
  {49, 67, 31, 0} }

Output:

The shortest tour is given along with the cost of the tour.