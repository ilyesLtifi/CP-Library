/**
* Unordered maps in C++ are just like maps but they don't order the elements
* and so the access and update complexities are O(1) on average instead of O(log(N)) 
* But this is because it works with hashing(which has probabilities of failure that can lead to O(N) query)
* and the default C++ unordered_map tends to be bad(sometimes slower than the usual map)
* This is a custom hashing class that makes it fast and safe
*/

struct custom_hash {
      static uint64_t splitmix64(uint64_t x) {
            x += 0x9e3779b97f4a7c15;
            x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
            x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
            return x ^ (x >> 31);
      }

      size_t operator()(uint64_t x) const {
            static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
            return splitmix64(x + FIXED_RANDOM);
      }
};

unordered_map<int, int, custom_hash> safe_map;






