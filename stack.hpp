#ifndef STACK_HPP
#define STACK_HPP
#include "iterators.hpp"
#include "utility.hpp"
#include "vector.hpp"


namespace ft
{
    template <class T, class Container = ft::vector<T> > class stack
    {
        public:
            typedef typename Container::value_type             value_type;
            typedef Container                         container_type;
            typedef std::size_t                       size_type;
            typedef typename Container::reference              reference;
            typedef typename Container::const_reference        const_reference;
        protected:
            Container _data;
        public:
            explicit stack (const container_type& ctnr = container_type()): _data(ctnr){}
            stack( const stack& other ): _data(other._data){}
            ~stack(){}
            stack& operator=( const stack& other ){_data = other; return *this;}
            bool empty() const{return _data.empty();}
            size_type size() const{return _data.size();}
            value_type& top(){return _data.back();}
            const value_type& top() const{return _data.back();}
            void push (const value_type& val){_data.push_back(val);}
            void pop(){_data.pop_back();}
    };
    template <class T, class Container>  bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs){return lhs.container_type == rhs.container_type;}
    template <class T, class Container>  bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){return lhs.container_type != rhs.container_type;}
    template <class T, class Container>  bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){return lhs.container_type < rhs.container_type;}
    template <class T, class Container>  bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){return lhs.container_type <= rhs.container_type;}
    template <class T, class Container>  bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){return lhs.container_type > rhs.container_type;}
    template <class T, class Container>  bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){return lhs.container_type >= rhs.container_type;}
}
#endif