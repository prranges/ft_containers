#include <iostream>
#include "Stack.hpp"
#include "Vector.hpp"
#include "Map.hpp"

#include "RB_Tree.hpp"
#include "Pair.hpp"

#include <vector>
#include <list>
#include <map>
#include "BD_Iterator.hpp"

int main() {

    /// NODE
//    ft::node<ft::pair<int, int> > node(ft::make_pair(1, 3));
//    std::cout << node.key_value.first << " : " << node.key_value.second << std::endl;
//    std::cout << node.left << " : " << node.right << std::endl;

    /// FT_MAP
    ft::map<int, int> ft_map1;
    ft_map1.insert(ft::make_pair(5, 5000));
    ft_map1.insert(ft::make_pair(1, 1000));
    ft_map1.insert(ft::make_pair(3, 3000));

    ft::map<int, int> ft_map2(ft_map1);
    ft::map<int, int> ft_map(ft_map2.begin(), ft_map2.end());

//    ft_map[1] = 1234;
//    std::cout << "[1] - " << ft_map[1] << std::endl;
//    std::cout << "[5] - " << ft_map[5] << std::endl;
//    std::cout << "[3] - " << ft_map[3] << std::endl;
//    std::cout << std::endl;


    ft::map<int, int>::iterator xx = ft_map.begin();
    ft::map<int, int>::iterator start;
    start = xx;
    ft::map<int, int>::iterator end = ft_map.end();

    end++;
    if (end == NULL)
        std::cout << "HALLO" << std::endl;

    std::cout << end->first << " : " << end->second << "?!!?" << std::endl;

    std::cout << "PRINT MAP" << std::endl;
    for (; start != end; ++start)
        std::cout << start->first << " : " << start->second << std::endl;

//    std::cout << "PRINT MAP reverse" << std::endl;



//    --end;

    std::cout << end->first << " : " << end->second << std::endl;

//    for (; end != --ft_map.begin(); --end)
//        std::cout << end->first << " : " << end->second << std::endl;


//
//    std::cout << "ft_find - " << ft_map.find(1)->first << std::endl;
//    std::cout << "ft_begin - "  << ft_map.begin()->first << std::endl;
//
//    std::cout << std::endl << "tree-size: " << ft_map.size() << std::endl;

    /// STD_MAP
//    std::map<int, int> std_map1;
//    std::map<int, int> std_map2(std_map1);
//    std::map<int, int> std_map(std_map2.begin(), std_map2.end());
//
//    std_map.insert(std::make_pair(5, 5));
//    std_map.insert(std::make_pair(1, 1));
//    std_map.insert(std::make_pair(3, 3));
//
//    std::map<int, int>::iterator y = std_map.begin();
//    for (; y != std_map.end(); ++y)
//        std::cout << y->first << " : " << y->second << std::endl;
//
//    std::map<int, int>::iterator end = --std_map.end();
//    for (; end != --std_map.begin(); --end)
//        std::cout << end->first << " : " << end->second << std::endl;

//    std::cout << "std_find - " << std_map.find(1)->first << std::endl;
//    std::cout << "std_begin - " << std_map.begin()->first << std::endl;
    /// MAP

    /// TREE
//    ft::RB_Tree<ft::pair<int, int> > tree;
//    tree.insert_node(ft::make_pair(11,6), 0);
//    tree.insert_node(ft::make_pair(2,5), 0);
//    tree.insert_node(ft::make_pair(13,4), 0);
//    tree.insert_node(ft::make_pair(4,3), 0);
//    tree.insert_node(ft::make_pair(15,2), 0);
//
//    ft::node<ft::pair<int, int> >* s = tree.search(11);
////    std::cout << s << "\t" <<  s->key_value->first << " : " << s->key_value->second << std::endl;
//
//    tree.printTree();
//
//    std::cout << "tree-size: " << tree.size() << std::endl;
//    tree.delete_node(s);
//    tree.printTree();
//    std::cout << "tree-size: " << tree.size() << std::endl;
    /// TREE



//

//    rbt.insertFixup(ft::make_pair(222,111);;
//    rbt.insertFixup(ft::make_pair(333,333));

//    ft::map<int, int>::iterator IT;
//    IT = rbt.begin();

//    std::cout << IT->first << " : " << IT->second << std::endl;

//    ft::map<int, int> M; // FT
//    M.insert(ft::make_pair(4, 1));
//    M.insert(ft::make_pair(2, 2));
//    M.insert(ft::make_pair(5, 3));
//    M.insert(ft::make_pair(3, 4));
//    M.insert(ft::make_pair(1, 5));
//
//    ft::map<int, int>::iterator IT;
//
//    for (IT = M.begin(); IT != M.end(); ++IT)
//        std::cout << IT->first << " : " << IT->second << std::endl;

//    /// STD
//
//    std::map<int, int> m;
//    m.insert(std::make_pair(4, 1));
//    m.insert(std::make_pair(2, 2));
//    m.insert(std::make_pair(5, 3));
//    m.insert(std::make_pair(3, 4));
//    m.insert(std::make_pair(1, 5));
//    std::map<int, int>::iterator it;
//    for (it = m.begin(); it != m.end(); ++it)
//        std::cout << it->first << " : " << it->second << std::endl;


//        ft::stack<int> stack3;
//        stack3 = stack2;
//        while (stack.size() > 0) {
//            v.push_back(stack.top());
//            stack.pop();
//        }
//        while (stack2.size() > 0) {
//            v.push_back(stack2.top());
//            stack2.pop();
//        }

////    ft::Stack<int> ft_stack;
////    ft::vector<int> V(5);
////    ft::vector<int> VV(5);
//
//    //insert
//    std::vector<int> s;
//    ft::vector<int> f;
//    for (int i = 0; i < 8; ++i) {
//        s.push_back(i+1);
//        f.push_back(i+1);
//    }
////    V.assign(1, 1);
////    VV.assign(1, 2);
////    VV.swap(V);
////    std::cout << "VV: " << VV[0] << std::endl;
////    std::cout << "V: " << V[0] << std::endl;
//
//    s.insert(s.begin()+3, 3, 1000);
//    f.insert(f.begin()+3, 3, 1000);
//
//
//    for (std::vector<int>::iterator it = s.begin(); it != s.end(); ++it) {
//        std::cout << "s " << *it << std::endl;
//    }
//    std::cout << "size: " << s.size() << std::endl;
//    std::cout << "capacity: " << s.capacity() << std::endl;
//
//    std::cout << std::endl;
//
//    for (ft::vector<int>::iterator it = f.begin(); it != f.end(); ++it) {
//        std::cout << "f " << *it << std::endl;
//    }
//    std::cout << "size: " << f.size() << std::endl;
//    std::cout << "capacity: " << f.capacity() << std::endl;

//    std::vector<int> v(5);

//    V[0] = 100;
//    V[1] = 111;
//    V[2] = 222;
//    V[3] = 333;
//    V[4] = 444;
//    V.push_back(555);
//    V.push_back(666);
//    V.push_back(777);
//    V.push_back(888);
//    V.push_back(999);
//    V.push_back(1000);
//    V.pop_back();
//
//    ft::vector<int> VVV(V);
//
////    VV[0] = 555;
////    VV[1] = 444;
////    VV[2] = 333;
////    VV[3] = 222;
////    VV[4] = 111;
////    VV.push_back(100);
//
////    VV = V;
//
////    V.clear();
////    std::cout << V.capacity() << std::endl;
////    V.reserve(99);
////    std::cout << V.capacity() << std::endl;
//
////    V.swap(VV);
//
////    for (int i = 0; i < VV.size(); i++)
////        std::cout << VV[i] << std::endl;
//
////    std::cout << V.back() << std::endl;
////    ft::vector<int>::iterator a = V.begin();
////    for (size_t i = 0; i < V.size(); i++)
////        std::cout << V[i] << std::endl;
//
////    V.insert(V.begin() + 2, 12345678);
//
////    for (ft::vector<int>::iterator it = V.begin(); it != V.end(); ++it) {
////        std::cout << *it << std::endl;
////    }
////
////
////    for (ft::vector<int>::reverse_iterator it = V.rbegin(); it != V.rend(); ++it) {
////        std::cout << *it << std::endl;
////    }
//
////    std::cout << V.at(1) << std::endl;
////    std::cout << V.front() << std::endl;
////    std::cout << V.back() << std::endl;
//
//    std::cout << "begin: " << *V.begin() << std::endl;
//    std::cout << "end-1: " << *(V.end() - 1) << std::endl;
//    std::cout << "distance: " << ft::distance(V.begin(), V.end()) << std::endl;
//    std::cout << "rbegin: " << *V.rbegin() << std::endl;
//    std::cout << "rend-1: " << *(V.rend() - 1) << std::endl;
//
//    std::cout << std::endl;
//
//    std::cout << "empty - 1: " << VV.empty() << std::endl;
//    std::cout << "empty - 0: " << V.empty() << std::endl;
//
//    std::cout << std::endl;
//
//    std::cout << "size: " << V.size() << std::endl;
//    std::cout << "capacity: " << V.capacity() << std::endl;
//
//    std::cout << std::endl;
//    std::cout << "reserve 100" << std::endl;
//    V.reserve(100);
//
////    std::cout << "assign 500/33" << std::endl;
////    V.assign(500, 1);
////
////    std::cout << std::endl;
//
//    std::cout << "size: " << V.size() << std::endl;
//    std::cout << "capacity: " << V.capacity() << std::endl;
//
////    std::cout << "resize 5" << std::endl;
////    V.resize(5);
//
//    std::cout << std::endl;
//
//    std::cout << "size: " << V.size() << std::endl;
//    std::cout << "capacity: " << V.capacity() << std::endl;
//
//    for (ft::vector<int>::iterator it = VVV.begin(); it != VVV.end(); ++it) {
//        std::cout << "yes " << *it << std::endl;
//    }
////
////    std::cout << "\nAT" << std::endl;
////    std::cout << "ft\t" << V.at(2) << std::endl;
////    std::cout << "std\t" << v.at(2) << std::endl;
////
////    std::cout << "\nFRONT" << std::endl;
////    std::cout << "ft\t" << V.front() << std::endl;
////    std::cout << "std\t" << v.front() << std::endl;
////
////    std::cout << "\nBACK" << std::endl;
////    std::cout << "ft\t" << V.back() << std::endl;
////    std::cout << "std\t" << v.back() << std::endl;
//
////    ft_stack.push(2);
////    ft_stack.push(5);
////    ft_stack.push(-3);
////
////    std::cout << ft_stack.top() << std::endl;
////    ft_stack.pop();
////    std::cout << ft_stack.top() << std::endl;
////    ft_stack.pop();
////    std::cout << ft_stack.top() << std::endl;
////    for (int i = 0; i < 5; i++)
////        std::cout << ft_vector[i] << std::endl;

    return 0;
}