/**
* Average and Best case complexities are O(N*log(N))
* Worst case theoretically is O(N*N) 
* 
* Commonly faster than MergeSort
* + no space required; an in-place sorting algorithm.
*/


int partition(vector<int>& vect, int i, int j){
    int pivot = vect[j];  
 
    int ind_small = i - 1;

    for(int x=i; x<=j-1; x++){
        if(vect[x] < pivot){
            ind_small++;
			swap(vect[ind_small], vect[x]);
        }
    }

	swap(vect[ind_small + 1], vect[j]);
    return ind_small + 1;
}

void quick_sort(vector<int>& vect, int i, int j){
	if(!(i < j)) return;

	int ind = partition(vect, i, j);

	quick_sort(vect, i, ind - 1);
	quick_sort(vect, ind + 1, j);
}
