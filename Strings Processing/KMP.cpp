/**
* The KMP algorithm for substring search
*/



void KMPprefixfunction(string s, int pf[]) {
    for(int i=1; i<size(s); i++) {
        int j = pf[i-1];
        while(j > 0 && s[i] != s[j]) j = pf[j-1];
        if(s[i] == s[j]) j++;
        pf[i] = j;
    }
}

void computeNext(string s, int pf[], int nxt[][26]) {
    s += '#';
    KMPprefixfunction(s, pf);
    for(int i=0; i<size(s); i++) {
        for(int c=0; c<26; c++) {
            if(i > 0 && 'a' + c != s[i]) nxt[i][c] = nxt[pf[i-1]][c];
            else nxt[i][c] = i + ('a' + c == s[i]);
        }
    }
}
