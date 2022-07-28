#include <iostream>
#include "Stack.hpp"
#include "Vector.hpp"
#include <vector>
#include <list>

int main() {

//    ft::Stack<int> ft_stack;
    ft::vector<int> V(5);
    ft::vector<int> VV;

//    std::vector<int> v(5);

    V[0] = 100;
    V[1] = 111;
    V[2] = 222;
    V[3] = 333;
    V[4] = 444;
    V.push_back(555);
    V.push_back(666);
    V.push_back(777);
    V.push_back(888);
    V.push_back(999);
    V.push_back(1000);
    V.pop_back();

    ft::vector<int> VVV(V);

//    VV[0] = 555;
//    VV[1] = 444;
//    VV[2] = 333;
//    VV[3] = 222;
//    VV[4] = 111;
//    VV.push_back(100);

//    VV = V;

//    V.clear();
//    std::cout << V.capacity() << std::endl;
//    V.reserve(99);
//    std::cout << V.capacity() << std::endl;

//    V.swap(VV);

//    for (int i = 0; i < VV.size(); i++)
//        std::cout << VV[i] << std::endl;

//    std::cout << V.back() << std::endl;
//    ft::vector<int>::iterator a = V.begin();
//    for (size_t i = 0; i < V.size(); i++)
//        std::cout << V[i] << std::endl;

//    V.insert(V.begin() + 2, 12345678);

//    for (ft::vector<int>::iterator it = V.begin(); it != V.end(); ++it) {
//        std::cout << *it << std::endl;
//    }
//
//
//    for (ft::vector<int>::reverse_iterator it = V.rbegin(); it != V.rend(); ++it) {
//        std::cout << *it << std::endl;
//    }

//    std::cout << V.at(1) << std::endl;
//    std::cout << V.front() << std::endl;
//    std::cout << V.back() << std::endl;

    std::cout << "begin: " << *V.begin() << std::endl;
    std::cout << "end-1: " << *(V.end() - 1) << std::endl;
    std::cout << "rbegin: " << *V.rbegin() << std::endl;
    std::cout << "rend-1: " << *(V.rend() - 1) << std::endl;

    std::cout << std::endl;

    std::cout << "empty - 1: " << VV.empty() << std::endl;
    std::cout << "empty - 0: " << V.empty() << std::endl;

    std::cout << std::endl;

    std::cout << "size: " << V.size() << std::endl;
    std::cout << "capacity: " << V.capacity() << std::endl;

    std::cout << std::endl;
    std::cout << "reserve 100" << std::endl;
    V.reserve(100);

//    std::cout << "assign 500/33" << std::endl;
//    V.assign(500, 1);
//
//    std::cout << std::endl;

    std::cout << "size: " << V.size() << std::endl;
    std::cout << "capacity: " << V.capacity() << std::endl;

//    std::cout << "resize 5" << std::endl;
//    V.resize(5);

    std::cout << std::endl;

    std::cout << "size: " << V.size() << std::endl;
    std::cout << "capacity: " << V.capacity() << std::endl;

    for (ft::vector<int>::iterator it = VVV.begin(); it != VVV.end(); ++it) {
        std::cout << "yes " << *it << std::endl;
    }
//
//    std::cout << "\nAT" << std::endl;
//    std::cout << "ft\t" << V.at(2) << std::endl;
//    std::cout << "std\t" << v.at(2) << std::endl;
//
//    std::cout << "\nFRONT" << std::endl;
//    std::cout << "ft\t" << V.front() << std::endl;
//    std::cout << "std\t" << v.front() << std::endl;
//
//    std::cout << "\nBACK" << std::endl;
//    std::cout << "ft\t" << V.back() << std::endl;
//    std::cout << "std\t" << v.back() << std::endl;

//    ft_stack.push(2);
//    ft_stack.push(5);
//    ft_stack.push(-3);
//
//    std::cout << ft_stack.top() << std::endl;
//    ft_stack.pop();
//    std::cout << ft_stack.top() << std::endl;
//    ft_stack.pop();
//    std::cout << ft_stack.top() << std::endl;
//    for (int i = 0; i < 5; i++)
//        std::cout << ft_vector[i] << std::endl;

    return 0;
}