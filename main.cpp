#include <iostream>
#include "stack/Stack.hpp"
#include "vector/Vector.hpp"
#include <vector>
#include <list>

int main() {

//    ft::Stack<int> ft_stack;
    ft::Vector<int> V(5);
    ft::Vector<int> VV(5);

    std::vector<int> v(5);

    V[0] = 100;
    V[1] = 111;
    V[2] = 222;
    V[3] = 333;
    V[4] = 444;
    V.push_back(555);
//    V.push_back(666);
//    V.pop_back();

    VV[0] = 555;
    VV[1] = 444;
    VV[2] = 333;
    VV[3] = 222;
    VV[4] = 111;
    VV.push_back(100);

//    VV = V;

//    V.clear();
//    std::cout << V.capacity() << std::endl;
//    V.reserve(99);
//    std::cout << V.capacity() << std::endl;

//    V.swap(VV);

    for (int i = 0; i < VV.size(); i++)
        std::cout << VV[i] << std::endl;

    for (int i = 0; i < V.size(); i++)
        std::cout << V[i] << std::endl;
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