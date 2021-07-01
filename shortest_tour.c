// ALgorithms Group Project
// Naushin(19EE10073)
// CSS Sravya (19EC10018)
// Saicharan (19EC10057)


#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

void initialise(int *a, int n, int value);
int min_first(int **G, int i, int n);
int min_second( int**G, int i, int n);
void shortest_tour_util(int **G, int n, int curr_lower_bound, int current_weight,
            int depth, int *current_path, int* result_path, int *visited, int *result);

void shortest_tour(int **G , int n , int *result_path,int *result);



// Main function
int main()
{
  // Taking the input
  int n;
  printf("Enter the number of nodes: ");
  scanf("%d",&n);
  printf("Enter the distances in form of adjacency matrix:\n");

  // Initialising the graph
  int i,j;
  int **G;
  G = (int**) malloc (sizeof(int*)*n);
  for(i = 0; i < n; i++)
  {
    G[i] = (int*) malloc (sizeof(int)*n);
    for(j = 0; j < n; j++)
      scanf("%d",&G[i][j]);
  }

  // Result path stores the final tour
  // Result stores the cost og the final tour
  int *result_path = (int*) malloc (sizeof(int)*(n+1));
  int result;
  shortest_tour(G,n,result_path,&result);

  // Printing the output
  printf("The shortest tour is: ");
  for (int i=0; i<=n; i++)
  {
    printf("%d ", result_path[i]);
    if(i==n) break;
    printf("->");
  }
  printf("\nCost of the tour is: %d",result);
  return 0;
}



void shortest_tour(int **G , int n , int *result_path,int *result)
{

  // Initialising all the nodes of visited array to false(0)
  int *visited = (int*) malloc (sizeof(int)*n);
  initialise(visited,n,0);

  // Initialising the result/upper bound to infinity
  *result = INT_MAX;

  // Initialising the nodes of the path to -1
  int *current_path = (int*) malloc (sizeof(int)*(n+1));

  // Initialising the lower bound
  int curr_lower_bound=0;
  int i;
  for (i = 0 ; i < n; i++)
  {
    curr_lower_bound += (min_first(G, i,n) + min_second(G, i,n));
  }
  curr_lower_bound = curr_lower_bound/2;

  // Starting the recursion with node 0
  visited[0] = 1;
  current_path[0] = 0;

  // Calling the recursive function
  shortest_tour_util(G,n,curr_lower_bound,0,0,current_path,result_path,visited,result);

}


// Utility function to implement recursion for the shortest_tour function
void shortest_tour_util(int **G, int n, int curr_lower_bound, int current_weight,
            int depth, int *current_path, int* result_path, int *visited, int *result)
{

  if (depth==n-1)
  {
    if (G[current_path[depth]][current_path[0]] != 0)
    {
      int current_res = current_weight + G[current_path[depth]][current_path[0]];

      // If the current result is less than the best final result, it is updated
      if (current_res < *result)
      {
        int i;
        for(i = 0; i < n; i++)
          result_path[i] = current_path[i];
        result_path[n]=current_path[0];
        *result = current_res;
      }
    }
    return;
  }

  int i,j;
  for (i=0; i<n; i++)
  {
      // The node is traversed only if it isn't visited earlier and is not equal to last node of current path
      if (G[current_path[depth]][i] != 0 && visited[i] == 0)
      {
        // The values of current lower bound and current weight are stored in temporary variables
        int temp1 = curr_lower_bound;
        int temp2 = current_weight;

        // Current weight is updated
        current_weight += G[current_path[depth]][i];

        // The current lower bound is also updated
        if (depth==0) // For depth=0 we calculate the lower bound differently
        {
          curr_lower_bound -= ((min_first(G, current_path[depth],n) + min_first(G, i,n))/2);
        }
        else
        {
          curr_lower_bound -= ((min_second(G, current_path[depth],n) + min_first(G, i,n))/2);
        }

        // This is the PRUNING STEP
        // The sum of current lower bound and current weight gives the minimum possible weight of the solution this recursion will given
        // If this minimum value is greater than the best result found so far, it wont be better than the best result_path
        // Hence that possibility is not explored
        if (curr_lower_bound + current_weight < *result)
        {
          current_path[depth+1] = i;
          visited[i] = 1;
          shortest_tour_util(G,n,curr_lower_bound, current_weight, depth+1,current_path,result_path,visited,result);
        }

        // The current lower bound, current weight and visited array are reset to the values before the ith node was traversed
        curr_lower_bound = temp1;
        current_weight = temp2;
        initialise(visited, n, 0);
        for ( j = 0; j <= depth; j++)
        {
          visited[current_path[j]] = 1;
        }

    }

  }
}


// Function to initilise the given array with the given value
void initialise(int *a, int n, int value)
{
  int i;
  for(i = 0; i < n ; i++)
  {
    a[i] = value;
  }
  return;
}


// Function to find the minimum edge in the ith row of the graph
int min_first(int **G, int i, int n)
{
    int minimum = INT_MAX;
    int j;
    for (j=0; j<n; j++)
    {
      if(j==i) continue;
      if (G[i][j]<minimum) minimum = G[i][j];
    }
    return minimum;
}

// Function to find the second minimum edge in the ith row of the graph
int min_second( int**G, int i, int n)
{
    int min_1 = INT_MAX;
    int min_2 = INT_MAX;
    int j;
    for ( j = 0; j < n ; j++)
    {
        if (i == j) continue;
        if (G[i][j] <= min_1)
        {
            min_2 = min_1;
            min_1 = G[i][j];
        }
        else if (G[i][j] <= min_2 &&  G[i][j] != min_1)
            min_2 = G[i][j];
    }
    return min_2;
}
