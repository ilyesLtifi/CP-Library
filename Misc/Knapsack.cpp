/**
* Classic and simple Dynamic Programming
* It often goes like this: You are given N items, each of which has a weight W and a value V
* You need to choose the optimal subset of items to take, such that there is a condition on the total sum of weights
* and values
* 
* For example, say you can only take X weight of items, and you want to maximize the total value of the items you take
* In other words, among all the subsets such that the total weight <= X, you want the one with the maximum total value
* 
* 
* Solved here with memoization. O(N * X)
* 
* There are other complex forms, like being able to take fractions of items (not just take/leave the whole item) etc..
*/


int n;
int X;
int weights[n + 1];
int values[n + 1];

int memo[n + 1][X + 1] = {0}; 

// Bottom Up Dynamic Programming
for(i = 1; i <= n; i++) { 
	for(w = 1; w <= X; w++) { 
		if(weights[i] <= w) {
			// either we take the ith item or we don't
			// so we take the best of the two options
			memo[i][w] = max(values[i] + memo[i - 1][w - weights[i]], memo[i - 1][w]); 
		}
		else{
			memo[i][w] = memo[i - 1][w]; 
		}
	} 
} 

// answer
cout << memo[n][X];