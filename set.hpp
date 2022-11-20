#ifndef SET_HPP
#define SET_HPP
#include <cstddef>
#include <iostream>
#include "iterators.hpp"
#include "utility.hpp"
#include "set_tree.hpp" 
#include <string.h>
#include <memory>

namespace ft
{
    
    template < class T >
        class set_it: public ft::iterator< ft::bidirectional_iterator_tag, T >
    {
        public:
            typedef std::ptrdiff_t					difference_type;
			typedef T								value_type;
			typedef ft::node<T>*					pointer;
			typedef T&								reference;
			typedef ft::bidirectional_iterator_tag	iterator_category;
        protected:
            pointer supp;
            pointer root(const pointer _node)const
            {
                pointer tmp = _node;
                while(tmp->parent)
                    tmp = tmp->parent;
                return (tmp);
            }
            pointer end(const pointer _node)const
            {
                return past_end(_node)->parent;
            }
            pointer begin(const pointer _node)const
            {
                return past_begin(_node)->parent;
            }
            pointer past_begin(const pointer _node)const
            {
                pointer tmp = _node;
                tmp = root(tmp);
                while(tmp->l_son)
                    tmp = tmp->l_son;
                return tmp;
            }
            pointer past_end(const pointer _node)const
            {
                pointer tmp = _node;
                tmp = root(tmp);
                while(tmp->r_son)
                    tmp = tmp->r_son;
                return tmp;
            }
            pointer next_node(const pointer _node)const
            {
                pointer tmp = _node;
                if(tmp == end(_node) || !tmp)
                    return(past_end(_node));
                else if(tmp->r_son)
                {
                    tmp = tmp->r_son;
                    while(tmp->l_son)
                        tmp = tmp->l_son;
                    return(tmp);
                }
                else
                {
                    while(_node->data >= tmp->data)
                        tmp = tmp->parent;
                    return(tmp);
                }
            }
            pointer prev_node(const pointer _node)const
            {
                pointer tmp = _node;
                if(tmp == begin(_node) || !tmp)
                    return(past_begin(_node));
                else if(tmp->l_son)
                {
                    tmp = tmp->l_son;
                    while(tmp->r_son)
                        tmp = tmp->r_son;
                    return(tmp);
                }
                else
                {
                    while(_node->data <= tmp->data)
                        tmp = tmp->parent;
                    return(tmp);
                }
            }
        public:
            set_it():supp(){}
            ~set_it(){}
            explicit set_it(pointer t):supp(t){}
            set_it(const set_it &copy){*this = copy;}
            set_it &operator=(const set_it &copy){if(this != &copy){supp = copy.supp;}return *this;}
            
            reference operator*()const{return supp->data;}
            pointer operator->()const{return supp;}

            set_it &operator++(){supp = next_node(supp); return *this;}
            set_it operator++(int){set_it tmp(*this); operator++(); return tmp;}
            set_it &operator--(){supp = prev_node(supp); return *this;}
            set_it operator--( int ){set_it tmp(*this); operator--(); return tmp;}

            bool operator==(const set_it &rhs){return supp == rhs.supp;}
            bool operator!=(const set_it &rhs){return supp != rhs.supp;}
    };

    template < class T >
        class const_set_it: public ft::set_it< T >
    {
        public:
            typedef std::ptrdiff_t					    difference_type;
			typedef const T								value_type;
			typedef ft::node<T>*					    pointer;
			typedef const T&							reference;
			typedef ft::bidirectional_iterator_tag	    iterator_category;
        public:
            const_set_it(){}
            ~const_set_it(){}
            explicit const_set_it(pointer t){this->supp = t;}
            const_set_it(const const_set_it &copy){*this = copy;}
            const_set_it &operator=(const const_set_it &copy){if(this != &copy){this->supp = copy.supp;}return *this;}

            reference operator*()const{return this->supp->data;}
            pointer operator->()const{return this->supp;}
    };

    template < class it >
        class reverse_set_it: public ft::iterator< typename iterator_traits<it>::iterator_category, typename iterator_traits<it>::value_type >
    {
        public:
            typedef std::ptrdiff_t					                difference_type;
			typedef typename ft::iterator_traits<it>::value_type	value_type;
			typedef ft::node<value_type>*			                pointer;
			typedef value_type&						                reference;
			typedef ft::bidirectional_iterator_tag	                iterator_category;
        protected:
            pointer supp;
            pointer root(const pointer _node)const
            {
                pointer tmp = _node;
                while(tmp->parent)
                    tmp = tmp->parent;
                return (tmp);
            }
            pointer end(const pointer _node)const
            {
                return past_end(_node)->parent;
            }
            pointer begin(const pointer _node)const
            {
                return past_begin(_node)->parent;
            }
            pointer past_begin(const pointer _node)const
            {
                pointer tmp = _node;
                tmp = root(tmp);
                while(tmp->l_son)
                    tmp = tmp->l_son;
                return tmp;
            }
            pointer past_end(const pointer _node)const
            {
                pointer tmp = _node;
                tmp = root(tmp);
                while(tmp->r_son)
                    tmp = tmp->r_son;
                return tmp;
            }
            pointer next_node(const pointer _node)const
            {
                pointer tmp = _node;
                if(tmp == end(_node) || !tmp)
                    return(past_end(_node));
                else if(tmp->r_son)
                {
                    tmp = tmp->r_son;
                    while(tmp->l_son)
                        tmp = tmp->l_son;
                    return(tmp);
                }
                else
                {
                    while(_node->data >= tmp->data)
                        tmp = tmp->parent;
                    return(tmp);
                }
            }
            pointer prev_node(const pointer _node)const
            {
                pointer tmp = _node;
                if(tmp == begin(_node) || !tmp)
                    return(past_begin(_node));
                else if(tmp->l_son)
                {
                    tmp = tmp->l_son;
                    while(tmp->r_son)
                        tmp = tmp->r_son;
                    return(tmp);
                }
                else
                {
                    while(_node->data <= tmp->data)
                        tmp = tmp->parent;
                    return(tmp);
                }
            }
        public:
            reverse_set_it():supp(){}
            ~reverse_set_it(){}
            explicit reverse_set_it(pointer t):supp(t){t=NULL;}
            reverse_set_it(const reverse_set_it &copy):supp(){*this = copy;}
            reverse_set_it &operator=(const reverse_set_it &copy){if(this != &copy){supp = copy.supp;}return *this;}
            
            reference operator*()const{return supp->data;}
            pointer operator->()const{return supp;}

            reverse_set_it &operator++(){supp = prev_node(supp); return *this;}
            reverse_set_it operator++(int){reverse_set_it tmp(*this); operator++(); return tmp;}
            reverse_set_it &operator--(){supp = next_node(supp); return *this;}
            reverse_set_it operator--( int ){reverse_set_it tmp(*this); operator--(); return tmp;}

            bool operator==(const reverse_set_it &rhs){return supp == rhs.supp;}
            bool operator!=(const reverse_set_it &rhs){return supp != rhs.supp;}
    };

    template < class it >
        class const_reverse_set_it: public ft::iterator< typename iterator_traits<it>::iterator_category, typename iterator_traits<it>::value_type >
    {
        public:
            typedef std::ptrdiff_t					                        difference_type;
			typedef const typename ft::iterator_traits<it>::value_type		value_type;
			typedef ft::node<value_type>*					                pointer;
			typedef const value_type&							            reference;
			typedef ft::bidirectional_iterator_tag	                        iterator_category;
        public:
            const_reverse_set_it(){}
            ~const_reverse_set_it(){}
            explicit const_reverse_set_it(pointer t){this->supp = t;} 
            const_reverse_set_it(const const_reverse_set_it &copy){*this = copy;}
            const_reverse_set_it &operator=(const const_reverse_set_it &copy){if(this != &copy){this->supp = copy.supp;}return *this;}

            reference operator*()const{return this->supp->data;}
            pointer operator->()const{return this->supp;}
    };

    template< class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> > class set
    {
        public:
            typedef Key                                             key_type;
            typedef Key                                             value_type;
            typedef std::size_t                                     size_type;
            typedef std::ptrdiff_t                                  difference_type;
            typedef Compare                                         key_compare;
            typedef Compare                                         value_compare;
            typedef Allocator                                       allocator_type;
            typedef value_type&                                     reference;
            typedef const value_type&                               const_reference;
            typedef typename allocator_type::pointer                pointer;
            typedef typename allocator_type::const_pointer          const_pointer;
            typedef set_it<value_type>                              iterator;
            typedef const_set_it<const value_type>                  const_iterator;
            typedef reverse_set_it<iterator>                        reverse_iterator;
            typedef const_reverse_set_it<const_iterator>            const_reverse_iterator;
        protected:
            allocator_type  _alloc;
            Compare         _compare;
            ft::tree<value_type>        tree;
            size_type       n_nodes;
        public:
        //constructors
            set():_alloc(Allocator()), _compare(Compare()), tree(), n_nodes(0){}
            explicit set( const Compare& comp, const Allocator& alloc = Allocator() ):_alloc(alloc), _compare(comp), tree(), n_nodes(0){}
            template< class InputIt >
                set( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ):_alloc(alloc), _compare(comp), tree(), n_nodes(0){insert(first, last);}
            set( const set& copy ):_alloc(Allocator()), _compare(Compare()), tree(), n_nodes(0){*this = copy;}
            ~set(){}
            set& operator=( const set& copy ){if(this == &copy){return *this;}clear();tree=copy.tree;_alloc=copy._alloc;_compare=copy._compare;n_nodes=copy.n_nodes;return *this;}
            allocator_type get_allocator() const{return(_alloc);}

            //iterators
            iterator begin(){return(iterator(tree.begin()));}
            const_iterator begin() const{return(const_iterator(tree.begin()));}
            iterator end(){return(iterator(tree.fpast_end()));}
            const_iterator end() const{return(const_iterator(tree.fpast_end()));}
            reverse_iterator rbegin(){return(reverse_iterator(tree.end()));}
            const_reverse_iterator rbegin() const{return(const_reverse_iterator(tree.end()));}
            reverse_iterator rend(){return(reverse_iterator(tree.fpast_begin()));}
            const_reverse_iterator rend() const{return(const_reverse_iterator(tree.fpast_begin()));}

            //capacity
            bool empty() const{if(n_nodes == 0)return(1);else return(0);}
            size_type size() const{return n_nodes;}
            size_type max_size() const{return _alloc.max_size();}

            //modifiers
            void clear(){tree.clear();n_nodes=0;}
            ft::pair<iterator,bool> insert( const value_type& value )
            {
                if(tree.insert(value) == NULL)
                    return(ft::make_pair(iterator(find(value)), false));
                n_nodes++;
                return(ft::make_pair(iterator(find(value)), true));
            }
            iterator insert( iterator hint, const value_type& value )
            {
                if (hint != hint)
                    return(find(value));
                if(tree.insert(value) == NULL)
                    return(find(value));
                else
                {
                    n_nodes++;
                    return(find(value));
                }
            }
            template< class InputIt >
                void insert( InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral< InputIt >::value >::type* = NULL)
                {
                    while(first != last)
                    {
                        insert(*first);
                        first++;
                    }                  
                }
            void erase( iterator pos )
            {
                if(tree.erase(*pos)==1)
                    n_nodes--;
            }
            size_type erase (const value_type& val)
            {
                if(tree.erase(val)==1)
                {
                    n_nodes--;
                    return 1;
                }
                return 0;
            }
            void erase( iterator first, iterator last )
            {
                size_type dim = 0;
                for(iterator it = first; it != last; it++)
                    dim++;
                value_type arr[dim];
                dim = 0;
                for(iterator it = first; it != last; it++,dim++)
                   arr[dim] = *it;
                for(size_type i = 0; i < dim; i++)
                    erase(arr[i]);
            }
            void swap( set& other )
            {
                ft::swap(this->tree, other.tree);
                ft::swap(this->n_nodes, other.n_nodes);
                ft::swap(this->_alloc, other._alloc);
                ft::swap(this->_compare, other._compare);
            }

            //lookup
            size_type count( const Key& key ) const
            {
                if(tree.find(key) != NULL)
                    return(1);
                else
                    return(0);                    
            }
            iterator find( const Key& key ){return(iterator(tree.find(key)));}
            const_iterator find( const Key& key ) const{return(const_iterator(tree.find(key)));}
            ft::pair<iterator,iterator> equal_range( const Key& key ){return(ft::make_pair(iterator(tree.find_lb(key)),iterator(tree.find_ub(key))));}
            ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const{return(ft::make_pair(const_iterator(tree.find_lb(key)),const_iterator(tree.find_ub(key))));}
            iterator lower_bound( const Key& key ){return(iterator(tree.find_lb(key)));}
            const_iterator lower_bound( const Key& key ) const{return(const_iterator(tree.find_lb(key)));}
            iterator upper_bound( const Key& key ){return(iterator(tree.find_ub(key)));}
            const_iterator upper_bound( const Key& key ) const{return(const_iterator(tree.find_ub(key)));}

            //observers
            key_compare key_comp() const{return(_compare);}
            value_compare value_comp() const{return(_compare);}
    };
}

#endif