#ifndef STACK_HPP
#define STACK_HPP
#include <vector>

namespace ft {

    template <class T, class Container = std::vector<T> > class Stack {
        public:
            typedef T value_type;
            typedef Container container_type;
            typedef typename Container::size_type size_type;

        protected:
            container_type _c;

        public:

            /// CONSTRUCTOR
            explicit Stack(const container_type& ctnr = container_type()) : _c(ctnr) {}

            /// MEMBER FUNCTIONS
            bool empty() const {
                return _c.empty();
            }

            size_type size() const {
                return _c.size();
            }

            value_type& top() {
                return _c.back();
            }

            const value_type& top() const {
                return _c.back();
            }

            void push (const value_type& val) {
                _c.push_back(val);
            }

            void pop() {
                _c.pop_back();
            }

        /// RELATIONAL OPERATORS
        friend bool operator== (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {
            return lhs._c == rhs._c;
        }

        friend bool operator!= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {
            return lhs._c != rhs._c;
        }

        friend bool operator<  (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {
            return lhs._c < rhs._c;
        }

        friend bool operator<= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {
            return lhs._c <= rhs._c;
        }

        friend bool operator>  (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {
            return lhs._c > rhs._c;
        }

        friend bool operator>= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {
            return lhs._c >= rhs._c;
        }
    };
}

#endif