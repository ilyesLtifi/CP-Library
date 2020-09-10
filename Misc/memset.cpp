/**
* Memset is a C function to fill a range with a constant value
* Remember that not all numbers will work with it
* The reason it is fast is because it sets the array numbers byte by byte
* Let's take 32 bit numbers as example(int). A byte is 8 bits. So every number is 4 bytes
* You pass a byte to the function, and the final number you'll get is that byte repeated 4 times
* memset(0) will fill the array with 0
* memset(-1) will also fill the array with -1 (because -1 in binary is all ones)
* 0x3f is 63 in hexa, so 1111 in binary, so memset(0x3f) will fill the array with numbers having all ones in binary - so the maximum value
* You can now notice that not all numbers are possible to achieve using memset().
* For that you can use C++ fill() but that is regular O(N) - just as if you made a loop and filled the array yourself
*/

memset(arr, 0x3f, sizeof(arr));   // 1e9 + ....      4e18 + ....

memset(arr, 0xc0, sizeof(arr));   // -1e9 + ....     -4e18 + ....
