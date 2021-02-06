/**
* A trie, or a prefix-tree, is a tree data structure that can solve many string related problems efficiently
* Its representation and traversal are close the ones of a real dictionary
* See an example picture of it here: upload.wikimedia.org/wikipedia/commons/thumb/b/be/Trie_example.svg/1200px-Trie_example.svg.png
* 
* In normal cases, one would use the alphabet characters as links(26 links) to form words at the leaves
* But this implementation solves another problem, that requires using numbers in binary, so we'int use 0 and 1
* as our only links, and so at the leaves we'int be forming integers based on the path of 0s and 1s we went through.
* 
* The problem is as follows:
* You are given q queries and a multiset A, initially containing only integer 0.
* There are three types of queries: 
*    "+ x" — add integer x to multiset A.
*    "- x" — erase one occurrence of integer x from multiset A. It's guaranteed that at least one x is present in the multiset A before this query.
*    "? x" — you are given integer x and need to compute the maximum value of bitwise exclusive OR (also know as XOR) of integer x and some integer y from the multiset A.
* Multiset is a set, where equal elements are allowed.
* 
* Here is the problem link on Codeforces: codeforces.com/contest/706/problem/D
* 
* It's kinda a famous problem, and there are many tutorials on it, so I won't explain the code.
*
* The trie structure remains the same, you only need to change the "node" class to represent different problems.
*/


struct node{
    struct node *next_zero , *next_one;
    int nb;
    node(){
        next_zero=NULL;
        next_one=NULL;
        nb=0;
    }
};
node* root = new node();
 
void add_number(int x){
    node* cur_node = root;
    ++cur_node->nb;
	
    for(int i = 29; i >= 0; --i){{
        if(x&(1 << i)){
            if(cur_node->next_one == NULL) cur_node->next_one = new node();
            cur_node=cur_node->next_one;
        }else{
            if(cur_node->next_zero == NULL) cur_node->next_zero = new node();
            cur_node=cur_node->next_zero;
        }
        ++cur_node->nb;
    }
}
 
void delete_number(int x){
    node *cur_node = root , *prv;
    --cur_node->nb;
    
	for(int i = 29; i >= 0; --i){{
        prv = cur_node;
 
        if(x&(1 << i)) cur_node = cur_node->next_one;
        else cur_node = cur_node->next_zero;
        
        --cur_node->nb;
        if(cur_node->nb == 0){
            if(x&(1 << i)) prv->next_one = NULL;
            else prv->next_zero = NULL;
            return;
        }
    }
}
 
int query_answer(int x){
    node* cur_node = root;
    
	for(int i = 29; i >= 0; --i){{
        if(x&(1 << i)){
            if(cur_node->next_zero != NULL) cur_node = cur_node->next_zero;
            else x -= (1 << i) , cur_node = cur_node->next_one;
        }else{
            if(cur_node->next_one != NULL) x += (1 << i) , cur_node = cur_node->next_one;
            else  cur_node = cur_node->next_zero;
        }
    }
 
    return x;
}
 
int main(){
 
    add_number(0);

    int queries; cin >> queries;
    while(queries--){
        string query_type;
		int number;

        cin >> query_type >> number;

        if(query_type == "+") add_number(number);
        if(query_type == "-") delete_number(number);
        if(query_type == "?") cout << query_answer(number) << endl;
    }
 
}
 