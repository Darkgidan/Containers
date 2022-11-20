#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include "iterators.hpp"
#include "utility.hpp" 
#include <string.h>
#include <memory>

namespace ft
{
    template < class T >
        class vector_it: public ft::iterator< ft::random_access_iterator_tag, T >
    {
        public:
            typedef std::ptrdiff_t					difference_type;
			typedef T								value_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef ft::random_access_iterator_tag	iterator_category;
        private:
            pointer supp;
        public:
            vector_it(){}
            ~vector_it(){}
            explicit vector_it(pointer t):supp(t){}
            vector_it(const vector_it &copy){*this = copy;}
            vector_it &operator=(const vector_it &copy){if(this != &copy){supp = &(*copy);}return *this;}
            bool operator==(const vector_it &rhs){return supp == &(*rhs);}
            bool operator!=(const vector_it &rhs){return supp != &(*rhs);}
            reference operator*()const{return *supp;}
            pointer operator->()const{return supp;}
            vector_it &operator++(){++supp; return *this;}
            vector_it operator++(int){vector_it tmp(*this); operator++(); return tmp;}
            vector_it &operator--(){--supp; return *this;}
            vector_it operator--( int ){vector_it tmp(*this); operator--(); return tmp;}
            vector_it operator+(const size_t x){return vector_it(supp + x);}
            vector_it operator-(const size_t x){return vector_it(supp - x);}
            bool operator<(const vector_it &rhs){return supp < &(*rhs);}
            bool operator<=(const vector_it &rhs){return supp <= &(*rhs);}
            bool operator>(const vector_it &rhs){return supp > &(*rhs);}
            bool operator>=(const vector_it &rhs){return supp >= &(*rhs);}
            vector_it &operator+=(const size_t x){supp + x; return *this;}
            vector_it &operator-=(const size_t x){supp - x; return *this;}
            reference operator[](size_t position){return supp[position];}
    };

    template < class T, class Alloc = std::allocator<T> > class vector
    {
        public:
            typedef T                                           value_type;
            typedef Alloc                                       allocator_type;
            typedef typename allocator_type::reference          reference;
            typedef typename allocator_type::const_reference    const_reference;
            typedef typename allocator_type::pointer            pointer;
            typedef typename allocator_type::const_pointer      const_pointer;
            typedef vector_it<value_type>                       iterator;
            typedef vector_it<const value_type>                 const_iterator;
            typedef ft::reverse_iterator<iterator>              reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;
            typedef std::ptrdiff_t                              difference_type;
            typedef std::size_t                                 size_type;
        protected:
            allocator_type _alloc;
            size_type _capacity;
            size_type _dim;
            pointer _data;
            size_type distance(iterator first, iterator last)
			{
				size_type n = 0;
				if (first > last)
					std::swap(first, last);
				while (first++ != last)
					++n;
				return n;
			}
			template <class InputIterator>
			difference_type distance_diff(InputIterator first, InputIterator last)
			{
				difference_type n = 0;
				if (first > last)
					std::swap(first, last);
				while (first++ != last)
					++n;
				return n;
			}
        public:
            explicit vector (const allocator_type& alloc = allocator_type()):_alloc(alloc),_capacity(0),_dim(0),_data(_alloc.allocate(_capacity))
            {}
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()):_alloc(alloc), _capacity(n), _dim(0), _data(_alloc.allocate(_capacity))
            {insert(begin(), n, val);}
            template <class InputIterator>
                vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()):_alloc(alloc),_capacity(0),_dim(0),_data(_alloc.allocate(_capacity)){assign(first, last);}
            vector (const vector& x):_alloc(x.get_allocator()),_capacity(0),_dim(0),_data(_alloc.allocate(_capacity))
            {*this = x;}
            vector& operator= (const vector& x)
            {clear();assign(x.begin(),x.end());_alloc = x.get_allocator();_capacity = x.capacity();return *this;}
            ~vector(){clear();_alloc.deallocate(_data, _capacity);}
            allocator_type get_allocator() const{return _alloc;}
            //iterators
            iterator begin(){return iterator(_data);}
            const_iterator begin() const{return const_iterator(_data);}
            iterator end(){return iterator(_data + _dim);}
            const_iterator end() const{return const_iterator(_data + _dim);}
            reverse_iterator rbegin(){return reverse_iterator(iterator(_data + _dim));}
            const_reverse_iterator rbegin() const{return const_reverse_iterator(iterator(_data + _dim));}
            reverse_iterator rend(){return reverse_iterator(iterator(_data));}
            const_reverse_iterator rend() const{return const_reverse_iterator(iterator(_data));}
            //capacity
            size_type size() const{return _dim;}
            size_type max_size() const{return _alloc.max_size();}
            void resize (size_type n, value_type val = value_type())
            {
                if(n == size())
                    return;
                else if(n < size())
                {
                    while(n < size())
                        pop_back();
                }
                else
                {
                    size_type supp = capacity();
                    while (supp < n)
                        supp*=2;
                    reserve(supp);
                    for(size_type i = size(); i < n; i++)
                        push_back(val);
                }
            }
            size_type capacity() const{return _capacity;}
            bool empty() const{if(size() == 0)return 1;else return 0;}
            void reserve (size_type n)
            {
                if(n <= capacity())
                    return;
                pointer temp;
                if (n < _capacity)
                    n = _capacity;
                temp = _alloc.allocate(n);
                for(size_type i = 0; i < size(); i++)
                {
                    _alloc.construct(temp + i, *(_data + i));
                    _alloc.destroy(_data + i);
                }
                _alloc.deallocate(_data, _capacity);
                _data = temp;
                _capacity = n;
            }
            //element access
            reference operator[] (size_type n){return(*(_data + n));}
            const_reference operator[] (size_type n) const{return(*(_data + n));}
            reference at (size_type n){if(n >= size()) throw(std::out_of_range("Error: out of range"));return(*(_data + n));}
            const_reference at (size_type n) const{return const_reference(at(n));}
            reference front(){return(*(_data));}
            const_reference front() const{return(*(_data));}
            reference back(){return(*(_data + size() - 1));}
            const_reference back() const{return(*(_data + size() - 1));}
            //modifiers
            template <class InputIterator>
                void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral< InputIterator >::value >::type* = NULL)
                {clear();size_type temp = 0;
                InputIterator first1(first);
                while(first1 != last)
                {temp++;first1++;}
                reserve(temp);
                while(first != last){push_back(*first);first++;}}
            void assign (size_type n, const value_type& val)
            {clear();reserve(n);for(size_type i = 0; i < n; i++)push_back(val);}
            void push_back (const value_type& val){if(size() == capacity()){if(capacity()==0)reserve(1);else reserve(capacity() * 2);}_alloc.construct(_data + _dim, val); _dim++;}
            void pop_back(){_alloc.destroy(_data + size() - 1); _dim--;}
            iterator insert (iterator position, const value_type& val)
            {
                iterator i;
                push_back(val);
                for(i = end() - 1; (i != position && i > begin()); i--)
                    std::swap(*i, *(i - 1));
                return(i);
            }
            void insert (iterator position, size_type n, const value_type& val){for(size_type i = 0; i < n; i++){insert(position, val);}}
            template <class InputIterator>
                void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral< InputIterator >::value >::type* = NULL)
            {
                while(first != last)
                {
                    last--;
                    insert(position, *last);
                }
            } 
            iterator erase (iterator position){iterator tmp = position;while(position < end()){std::swap(*position, *(position + 1));position++;}pop_back();return(tmp);}
            iterator erase (iterator first, iterator last){iterator tmp = first; while(first != last){erase(tmp);first++;}return (tmp);}
            void swap (vector& x){std::swap(_dim, x._dim);std::swap(_capacity, x._capacity);std::swap(_alloc, x._alloc);std::swap(_data, x._data);}
            void clear(){while(empty() == 0){pop_back();}}
            friend void swap (vector& x, vector& y){ x.swap(y); }
    };
    template <class T, class Alloc>
        bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){if(lhs.size() != rhs.size())return 0;else {for(std::size_t  i = 0; i < rhs.size(); i++){if(lhs[i] != rhs[i])return 0;}return 1;}}
    template <class T, class Alloc>
        bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){return(!(rhs == lhs));}
    template <class T, class Alloc>
        bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){return(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));}
    template <class T, class Alloc>
        bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){return(!(rhs < lhs));}
    template <class T, class Alloc>
        bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){return(rhs < lhs);}
    template <class T, class Alloc>
        bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){return(!(lhs < rhs));}
    template <class T, class Alloc>
        void swap (vector<T,Alloc>& x, vector<T,Alloc>& y){x.swap(y);}



    /*
    template<typename Iter>ft::vector_it<Iter>
	operator-(const ft::vector_it<Iter>& lhs, typename ft::vector_it<Iter>::difference_type rhs)
		{return lhs - rhs;}
	template<typename Iter>ft::vector_it<Iter>
	operator+(const ft::vector_it<Iter>& lhs, typename ft::vector_it<Iter>::difference_type rhs)
		{return lhs + rhs;}
    template<typename Iter>ft::vector_it<Iter>
	operator-(typename ft::vector_it<Iter>::difference_type lhs, const ft::vector_it<Iter>& rhs)
		{return rhs - lhs;}
	template<typename Iter>ft::vector_it<Iter>
	operator+(typename ft::vector_it<Iter>::difference_type lhs, const ft::vector_it<Iter>& rhs)
		{return lhs + rhs;}
        */
}

#endif