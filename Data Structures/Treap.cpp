
namespace Treap{
	// #define int long long
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    struct node {
        int sz, prior;
        int val, sum, lazy;
        node* l,* r;
        node() { }
        node(int _val) {
            sz = 1; prior = uniform_int_distribution<int>(1,1e9)(rng);
            val = sum = _val; lazy = 0;
            l = r = NULL;
        }
    };
    typedef node* treap;

    int sz(treap t) { return t ? t->sz : 0; }

    int sum(treap t) { return t ? t->sum + t->lazy*sz(t) : 0; }

    void propagate(treap t) {
        if(t && t->lazy!=0){
            t->val += t->lazy;
            if(t->l) (t->l)->lazy += t->lazy;
            if(t->r) (t->r)->lazy += t->lazy;
            t->lazy = 0;
        }
    }

    void update(treap t) {
        if(t){
            propagate(t);
            t->sz = 1 + sz(t->l) + sz(t->r);
            t->sum = t->val + (t->lazy)*(t->sz) + sum(t->l) + sum(t->r);
        }
    }

    void split(treap t, treap& l, treap& r, int key, int cum = 0) {
        update(t);
        int cur_key = t ? cum+sz(t->l)+1 : -1;
        if(!t) l = r = NULL;
        else if(cur_key < key) split(t->r, t->r, r, key, cur_key),  l = t;
        else split(t->l, l, t->l, key, cum),  r = t;
        update(l);
        update(r);
    }

    void merge(treap& t, treap l, treap r) {
        update(l);
        update(r);
        if(!l || !r) t = l ? l : r;
        else if(l->prior > r->prior) merge(l->r, l->r, r),  t = l;
        else merge(r->l, l, r->l),  t = r;
        update(t);
    }

    void insert(treap& t, treap newt, int key) {
        if(!t){ t = newt; return; }
        treap t1, t2;
        split(t, t1, t2, key);
        merge(t1, t1, newt);
        merge(t, t1, t2);
    }

    void erase(treap& t, int key, int cum = 0) {
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

    int sumRange(treap& t, int qL, int qR) {
        treap al, ar; split(t, al, ar, qL);
        treap bl, br; split(ar, bl, br, qR-qL+2);
        int ans = sum(bl);
        treap tmp; merge(tmp, al, bl);
        merge(t, tmp, br);
        return ans;
    }

    void addRange(treap& t, int qL, int qR, int qVal) {
        treap al, ar; split(t, al, ar, qL);
        treap bl, br; split(ar, bl, br, qR-qL+2);
        bl->lazy += qVal;
        treap tmp; merge(tmp, al, bl);
        merge(t, tmp, br);
    }

} using namespace Treap;