#ifndef MAP_HPP
#define MAP_HPP
#include <cstddef>
#include <iostream>
#include "iterators.hpp"
#include "utility.hpp"
#include "map_tree.hpp" 
#include <string.h>
#include <memory>

namespace ft
{
    
    template < class Key, class Value >
        class map_it: public ft::iterator< ft::bidirectional_iterator_tag, ft::pair<Key,Value> >
    {
        public:
            typedef std::ptrdiff_t					difference_type;
            typedef Key								key_type;
			typedef Value							mapped_type;
            typedef ft::pair<Key, Value>            value_type;
			typedef ft::map_node<value_type>*		pointer;
			typedef value_type&			            reference;
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
                    while(_node->data.first >= tmp->data.first)
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
                    while(_node->data.first <= tmp->data.first)
                        tmp = tmp->parent;
                    return(tmp);
                }
            }
        public:
            map_it():supp(){}
            ~map_it(){}
            explicit map_it(pointer t):supp(t){}
            map_it(const map_it &copy){*this = copy;}
            map_it &operator=(const map_it &copy){if(this != &copy){supp = copy.supp;}return *this;}

            reference operator*(void)const{return supp->data;}
            value_type* operator->(void){return &supp->data;}
			

            map_it &operator++(){supp = next_node(supp); return *this;}
            map_it operator++(int){map_it tmp(*this); operator++(); return tmp;}
            map_it &operator--(){supp = prev_node(supp); return *this;}
            map_it operator--( int ){map_it tmp(*this); operator--(); return tmp;}

            bool operator==(const map_it &rhs){return supp == rhs.supp;}
            bool operator!=(const map_it &rhs){return supp != rhs.supp;}
    };

    template < class Key, class Value >
        class const_map_it: public ft::map_it<Key, Value>
    {
        public:
            typedef std::ptrdiff_t					    difference_type;
			typedef const Key						    key_type;
            typedef const Value							mapped_type;
            typedef const ft::pair<Key, Value>          value_type;
			typedef ft::map_node<value_type>*				pointer;
			typedef const value_type&			reference;
			typedef ft::bidirectional_iterator_tag	    iterator_category;
        public:
            const_map_it(){}
            ~const_map_it(){}
            explicit const_map_it(pointer t){this->supp = t;}
            const_map_it(const const_map_it &copy){*this = copy;}
            const_map_it &operator=(const const_map_it &copy){if(this != &copy){this->supp = copy.supp;}return *this;}

            reference operator*()const{return this->supp->data;}
            pointer operator->()const{return this->supp;}
    };

    template < class it >
        class reverse_map_it: public ft::map_it< typename it::key_type, typename it::value_type >
    {
        public:
            typedef std::ptrdiff_t					                difference_type;
            typedef typename it::key_type	                        key_type;
			typedef typename it::mapped_type	                    mapped_type;
            typedef typename it::value_type	                        value_type;
			typedef ft::map_node<value_type>*			            pointer;
			typedef value_type&				                        reference;
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
                    while(_node->data.first >= tmp->data.first)
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
                    while(_node->data.first <= tmp->data.first)
                        tmp = tmp->parent;
                    return(tmp);
                }
            }
        public:
            reverse_map_it():supp(){}
            ~reverse_map_it(){}
            explicit reverse_map_it(pointer t):supp(t){t=NULL;}
            reverse_map_it(const reverse_map_it &copy):supp(){*this = copy;}
            reverse_map_it &operator=(const reverse_map_it &copy){if(this != &copy){supp = copy.supp;}return *this;}

            reference operator*(void)const{return supp->data;}
            value_type* operator->(void){return &supp->data;}

            reverse_map_it &operator++(){supp = prev_node(supp); return *this;}
            reverse_map_it operator++(int){reverse_map_it tmp(*this); operator++(); return tmp;}
            reverse_map_it &operator--(){supp = next_node(supp); return *this;}
            reverse_map_it operator--( int ){reverse_map_it tmp(*this); operator--(); return tmp;}

            bool operator==(const reverse_map_it &rhs){return supp == rhs.supp;}
            bool operator!=(const reverse_map_it &rhs){return supp != rhs.supp;}
    };

    template < class it >
        class const_reverse_map_it: public ft::map_it< typename it::key_type, typename it::value_type >
    {
        public:
            typedef std::ptrdiff_t					                        difference_type;
            typedef const typename it::key_type		                        key_type;
			typedef const typename it::value_type		                    value_type;
            typedef const typename it::mapped_type	                        mapped_type;
			typedef ft::map_node<value_type>*					            pointer;
			typedef const value_type&	                        			    reference;
			typedef ft::bidirectional_iterator_tag	                        iterator_category;
        public:
            const_reverse_map_it(){}
            ~const_reverse_map_it(){}
            explicit const_reverse_map_it(pointer t){this->supp = t;} 
            const_reverse_map_it(const const_reverse_map_it &copy){*this = copy;}
            const_reverse_map_it &operator=(const const_reverse_map_it &copy){if(this != &copy){this->supp = copy.supp;}return *this;}

            reference operator*()const{return this->supp->data;}
            pointer operator->()const{return this->supp;}
    };

    template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >class map
    {
        public:
            typedef Key                                             key_type;
            typedef T                                               mapped_type;
            typedef ft::pair<Key, T>                                value_type;
            typedef std::size_t                                     size_type;
            typedef std::ptrdiff_t                                  difference_type;
            typedef Compare                                         key_compare;
            typedef Compare                                         value_compare;
            typedef Allocator                                       allocator_type;
            typedef value_type&                                     reference;
            typedef const value_type&                               const_reference;
            typedef typename allocator_type::pointer                pointer;
            typedef typename allocator_type::const_pointer          const_pointer;
            typedef map_it<Key, T>                                  iterator;
            typedef const_map_it<const Key, const T>                const_iterator;
            typedef reverse_map_it<iterator>                        reverse_iterator;
            typedef const_reverse_map_it<const_iterator>            const_reverse_iterator;
        protected:
            allocator_type  _alloc;
            Compare         _compare;
            ft::map_tree<Key, T>        tree;
            size_type       n_nodes;
        public:
        //constructors
            map():_alloc(Allocator()), _compare(Compare()), tree(), n_nodes(0){}
            explicit map( const Compare& comp, const Allocator& alloc = Allocator() ):_alloc(alloc), _compare(comp), tree(), n_nodes(0){}
            template< class InputIt >
                map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ):_alloc(alloc), _compare(comp), tree(), n_nodes(0){insert(first, last);}
            map( const map& copy ):_alloc(Allocator()), _compare(Compare()), tree(), n_nodes(0){*this = copy;}
            ~map(){}
            map& operator=( const map& copy ){if(this == &copy){return *this;}clear();tree=copy.tree;_alloc=copy._alloc;_compare=copy._compare;n_nodes=copy.n_nodes;return *this;}
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
            //element access
            T& at( const Key& key )
            {
                iterator temp(tree.find(key));
                if(temp == NULL)
                    throw std::out_of_range("");
                return (temp->second);
            }
            const T& at( const Key& key ) const
            {
                iterator temp(tree.find(key));
                if(temp == NULL)
                    throw std::out_of_range("");
                return (temp->second);
            }
            T& operator[]( const Key& key )
            {return (*((this->insert(ft::make_pair(key,mapped_type()))).first)).second;}
            //capacity
            bool empty() const{if(n_nodes == 0)return(1);else return(0);}
            size_type size() const{return n_nodes;}
            size_type max_size() const{return _alloc.max_size();}

            //modifiers
            void clear(){tree.clear();n_nodes=0;}
            ft::pair<iterator,bool> insert( const value_type& value )
            {
                if(tree.insert(value) == NULL)
                    return(ft::make_pair(iterator(find(value.first)), false));
                n_nodes++;
                return(ft::make_pair(iterator(find(value.first)), true));
            }
            template <class InputIterator> void insert(InputIterator first, InputIterator last,
              typename ft::enable_if<!ft::is_integral< InputIterator >::value >::type* = nullptr)
            {
                while(first != last)
                {
                    tree.insert(*first);
                    first++;
                }
            }
            iterator insert( iterator hint, const value_type& value )
            {
                if (hint != hint)
                    return(find(value.first));
                if(tree.insert(value) == NULL)
                    return(find(value.first));
                else
                {
                    n_nodes++;
                    return(find(value.first));
                }
            }
            void erase( iterator pos )
            {
                if(tree.erase((*pos).first)==1)
                    n_nodes--;
            }
            size_type erase (const key_type& key)
            {
                if(tree.erase(key)==1)
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
                    erase(arr[i].first);
            }
            void swap( map& other )
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