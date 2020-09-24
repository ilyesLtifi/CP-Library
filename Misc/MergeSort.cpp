/**
* O(N*log(N)) guaranteed complexity
* + O(N) space
*/

vector<int> merge(vector<int> v1, vector<int> v2){
	vector<int> result;
	int ind_1 = 0, ind_2 = 0;

	while(ind_1 < size(v1) && ind_2 < size(v2)){
		if(v1[ind_1] < v2[ind_2]){
			result.emplace_back(v1[ind_1]);
			++ind_1;
		}
		else{
			result.emplace_back(v2[ind_2]);
			++ind_2;
		}
	}

	// Guaranteed that at least one of them is done at this point

	for(int i=ind_1; i<size(v1); ++i) result.emplace_back(v1[i]);

	for(int i=ind_2; i<size(v2); ++i) result.emplace_back(v2[i]);

	return result;
}

vector<int> merge_sort(vector<int> vect){
	if(size(vect) == 1) return vect;

	int mid = size(vect) / 2;
	vector<int> vect_half_1(begin(vect), begin(vect) + mid);
	vector<int> vect_half_2(begin(vect) + mid, end(vect));

	vector<int> v1 = merge_sort(vect_half_1);
	vector<int> v2 = merge_sort(vect_half_2);
	
	vector<int> result = merge(v1, v2);

	return result;
}
