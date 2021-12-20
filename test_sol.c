// SOURCE FROM: https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/
// CODE HERE ONLY TO TEST SOLUTION EXTRACTOR,
// Base code comes from url above
// A Dynamic Programming based
// solution for 0-1 Knapsack problem
#include <stdio.h>

// A utility function that returns
// maximum of two integers
int max(int a, int b) { return (a > b) ? a : b; }

// Returns the maximum value that
// can be put in a knapsack of capacity W
// modified to save table
int knapSack(int W, int wt[], int val[], int n, int K[6][12]) {
  int i, w;
  // static int K[7 + 1][18 + 1];
  printf("|000");
  for (w = 0; w <= W; w++) {
    printf("|%3d", w);
  }
  printf("\n");
  // Build table K[][] in bottom up manner
  for (i = 0; i <= n; i++) {
    printf("|%3d", i);
    for (w = 0; w <= W; w++) {
      if (i == 0 || w == 0)
        K[i][w] = 0;
      else if (wt[i - 1] <= w)
        K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
      else {
        K[i][w] = K[i - 1][w];
      }
      printf("|%3d", K[i][w]);
    }
    printf("\n");
  }

  return K[n][W];
}

int ans[8] = {0, 0, 0, 0, 0, 0, 0, 0};
// solution extractor
void sol(int i, int w, int wt[], int val[], int K[6][12]) {
  printf("\nitem: %d, weight: %d, value: %d", i, wt[i - 1], val[i - 1]);
  printf("\ncurrent coord: %2d, %2d", w, i);
  printf("\nK[i][w] - val[i-1] is: %d", (K[i][w] - val[i - 1]));
  printf("\nK[i - 1][w - wt[i - 1] is: %d", (K[i - 1][w - wt[i - 1]]));
  if (wt[i - 1] < w) {
    if ((K[i][w] - val[i - 1]) != (K[i - 1][w - wt[i - 1]])) {
      sol(i - 1, w, wt, val, K);
    } else if ((K[i - 1][w - wt[i - 1]]) == 0) {
      printf("\n%d, part of ans", i);
      ans[i] = 1;
      return;
    } else {
      sol(i - 1, w - wt[i - 1], wt, val, K);
      printf("\n%d, part of ans", i);
      ans[i] = 1;
    }
  } else {
    sol(i - 1, w, wt, val, K);
  }
}

// Driver Code
int main() {
  // int val[] = {4, 6, 5, 7, 3, 1, 6};
  // int wt[] = {12, 10, 8, 11, 14, 7, 9};
  int wt[] = {1, 2, 5, 6, 7};
  int val[] = {1, 6, 18, 22, 28};
  int W = 11;
  int n = sizeof(val) / sizeof(val[0]);
  int L[n + 1][W + 1];
  knapSack(W, wt, val, n, L);
  printf("%d\n", L[5][11]);
  sol(5, 11, wt, val, L);
  printf("\n");
  for (int i = 0; i < 6; i++) {
    if (ans[i] == 1) {
      printf("%d ", i); // print out solution
    }
  }
  printf("\n");
  return 0;
}
