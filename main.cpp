#include <iostream>
#include "stack/Stack.hpp"
#include "vector/Vector.hpp"
#include <vector>
#include <list>

int main() {

//    ft::Stack<int> ft_stack;
    ft::Vector<int> V(5);
    ft::Vector<int> VV(15);

    std::vector<int> v(5);

    V[0] = 100;
    v[0] = 100;
    V[2] = 222;
    v[2] = 222;
    V[4] = 444;
    v[4] = 444;

    VV = V;
    for (int i = 0; i < 15; i++)
        std::cout << VV[i] << std::endl;
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