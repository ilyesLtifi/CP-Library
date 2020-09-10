/**
* A helper function to compress a range
* It can be an array, a vector, a set etc.. Because it's generic
* You pass it the range begin and end For example:
* vector<int> vect; compress(vect.begin(), vect.end());
* set<int> my_set; compress(my_set.begin(), my_set.end());
* char my_word[100]; compress(my_word, my_word + 100);
*
* It doesn't remove duplicates, but it assigns a unique ID to every
* integer based on its order compared to the others starting from 1.
* For example: [4,26,17,300,18] => [1,4,2,5,3]
* This is very useful in problems where containers' length is small, but
* the values themselves are very large. (like N <= 100 but maximum_element <= a billion)
*/

template<typename T, class U = typename iterator_traits<T>::value_type>
void compress(T _first, T _last){
	if(_first == _last) return;
	set<U> _sss; map<U, int> _assign;
	auto it1 = _first; while(it1 != _last) _sss.insert(*it1), ++it1;
	int _cnt = 1; for(U _el: _sss) _assign[_el] = _cnt, ++_cnt;
	auto it2 = _first; while(it2 != _last) *it2 = _assign[*it2], ++it2;
}