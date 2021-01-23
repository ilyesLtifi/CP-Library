
namespace Treap{
    #define T int
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    struct node {
        int sz, prior;
        T val, sum, lazy;
        node* l,* r;
        node() { }
        node(T _val) {
            sz = 1; prior = uniform_int_distribution<int>(1,1e9)(rng);
            val = sum = _val; lazy = 0;
            l = r = NULL;
        }
    };
    typedef node* treap;

    int sz(treap t) { return t ? t->sz : 0; }

    T sum(treap t) { return t ? t->sum + t->lazy*sz(t) : 0; }

    void update(treap t) {
        if(t){
            t->sz = 1 + sz(t->l) + sz(t->r);
            t->sum = t->val + (t->lazy)*(t->sz) + sum(t->l) + sum(t->r);
        }
    }

    void propagate(treap t) {
        if(t && t->lazy!=0){
            t->val += t->lazy;
            if(t->l) (t->l)->lazy += t->lazy;
            if(t->r) (t->r)->lazy += t->lazy;
            t->lazy = 0;
            update(t);
        }
    }

    void split(treap t, treap& l, treap& r, const int& key, int cum = 0) {
        int cur_key = t ? cum+sz(t->l)+1 : -1;
        if(!t) l = r = NULL;
        else if(key < cur_key) split(t->l, l, t->l, key, cum),  r = t;
        else split(t->r, t->r, r, key, cur_key),  l = t;
        update(t);
    }

    void insert(treap& t, treap newt, const int& key, int cum = 0) {
        int cur_key = t ? cum+sz(t->l)+1 : -1;
        if(!t) t = newt;
        else if(newt->prior > t->prior) split(t, newt->l, newt->r, key),  t = newt;
        else if(key < cur_key) insert(t->l, newt, key, cum);
        else insert(t->r, newt, key, cur_key);
        update(t);
    }

    void merge(treap& t, treap l, treap r) {
        if(!l || !r){ t = l ? l : r; return; }
        propagate(l);
        propagate(r);
        if(l->prior > r->prior) merge(l->r, l->r, r),  t = l;
        else merge(r->l, l, r->l),  t = r;
        update(t);
    }

    void merge(treap& t, const initializer_list<treap>& list){
        vector<treap> vect(list);
        merge(t, vect[0], vect[1]);
        for(int i=2; i<size(vect); ++i) merge(t, t, vect[i]);
    }

    void erase(treap& t, const int& key, int cum = 0) {
        int cur_key = t ? cum+sz(t->l)+1 : -1;
        if(cur_key == key) {
            treap tmp = t;
            merge(t, t->l, t->r);
            delete tmp;
        }
        else if(key < cur_key) erase(t->l, key, cum);
        else erase(t->r, key, cur_key);
        update(t);
    }

    T sumRange(treap& t, const int& qL, const int& qR) {
        treap al, ar; split(t, al, ar, qL-1);
        treap bl, br; split(ar, bl, br, qR-qL+1);
        T ans = sum(bl);
        merge(t, {al, bl, br});
        return ans;
    }

    T getInd(treap& t, const int& qInd) { return sumRange(t, qInd, qInd); }

    void swapRanges(treap& t, const int& qA, const int& qB, const T& qLen) {
        treap al, ar; split(t, al, ar, qA-1);
        treap bl, br; split(ar, bl, br, qLen);
        treap cl, cr; split(br, cl, cr, qB-1-(qA+qLen-1));
        treap dl, dr; split(cr, dl, dr, qLen);
        merge(t, {al, dl, cl, bl, dr});
    }

    void addRange(treap& t, const int& qL, const int& qR, const T& qVal) {
        treap al, ar; split(t, al, ar, qL-1);
        treap bl, br; split(ar, bl, br, qR-qL+1);
        bl->lazy += qVal;
        merge(t, {al, bl, br});
    }

} using namespace Treap;
