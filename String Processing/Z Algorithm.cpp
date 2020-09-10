/**
* A string processing algorithm that preprocesses a string and constructs a Z-array
* This can be used to compare substrings along with other string queries
*/

vector<int> computeZ(const string& _s) {
    vector<int> _z(size(_s), 0);
    int l = 0, r = 0;
	for(int i = 1; i < size(_s); i++) {
		_z[i] = clamp(r - i + 1, 0, _z[i - l]);
		while (i + _z[i] < size(_s) && _s[_z[i]] == _s[i + _z[i]]) { l = i, r = i + _z[i], ++_z[i]; }
	}
	return _z;
}