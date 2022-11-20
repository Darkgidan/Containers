#ifndef ITERATORS_HPP
#define ITERATORS_HPP
#include <iostream>
#include <iterator>

namespace ft
{

    struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    template<typename Category, typename Type, typename Distance = std::ptrdiff_t,
					 typename Pointer = Type*, typename Reference = Type&>
	struct iterator
	{
		typedef Category	iterator_category;
		typedef Type    value_type;
		typedef Distance	difference_type;
		typedef Pointer pointer;
		typedef Reference	reference;
	};

    template<class I>
    struct iterator_traits
    {
        typedef typename I::difference_type difference_type;
        typedef typename I::value_type value_type;
        typedef typename I::pointer pointer;
        typedef typename I::reference reference;
        typedef typename I::iterator_category iterator_category;
    };

    template<typename Type>
	struct iterator_traits<Type*>
	{
		typedef std::random_access_iterator_tag	iterator_category;
		typedef Type  value_type;
		typedef ptrdiff_t   difference_type;
		typedef Type* pointer;
		typedef Type& reference;
	};

	template<typename Type>
	struct iterator_traits<const Type*>
	{
		typedef std::random_access_iterator_tag	iterator_category;
		typedef Type    value_type;
		typedef ptrdiff_t   difference_type;
		typedef const Type*  pointer;
		typedef const Type&  reference;
	};

    template<typename I>
		class reverse_iterator
		: public iterator<typename iterator_traits<I>::iterator_category,
						typename iterator_traits<I>::value_type,
						typename iterator_traits<I>::difference_type,
						typename iterator_traits<I>::pointer,
						typename iterator_traits<I>::reference>
    {
		public:
			typedef typename iterator_traits<I>::iterator_category	iterator_category;
			typedef typename iterator_traits<I>::value_type    value_type;
			typedef typename iterator_traits<I>::difference_type	difference_type;
			typedef typename iterator_traits<I>::pointer pointer;
			typedef typename iterator_traits<I>::reference	reference;
			typedef I iterator_type;
        protected:
			iterator_type		current;
			typedef iterator_traits<I>		traits_type;
		public:
			reverse_iterator():current(){}
			explicit reverse_iterator( iterator_type x ): current(x){}
			template< class U >	reverse_iterator( const reverse_iterator<U>& other ){*this = other;}
			template< class U > reverse_iterator& operator=( const reverse_iterator<U>& other ){current = other.current; return(*this);}

			iterator_type base() const{return(current);}
			reference operator*()const{I tmp = current; return *--tmp;}
			pointer operator->()const{return &(operator*());}
			reference operator[]( difference_type n ) const{return (base()[-n-1]);}
			reverse_iterator& operator++(){--current;return(*this);}
			reverse_iterator& operator--(){++current;return(*this);}
			reverse_iterator operator++( int ){reverse_iterator tmp = *this; --current;return(tmp);}
			reverse_iterator operator--( int ){reverse_iterator tmp = *this; ++current;return(tmp);}
			reverse_iterator operator+( difference_type n ) const{return reverse_iterator(base() - n);}
			reverse_iterator operator-( difference_type n ) const{return reverse_iterator(base() + n);}
			reverse_iterator& operator+=( difference_type n ){current -= n; return(*this);}
			reverse_iterator& operator-=( difference_type n ){current = current + n; return(*this);}
    };
	
	template< class Iterator>
		bool operator==( const reverse_iterator<Iterator>& lhs,const reverse_iterator<Iterator>& rhs ){return (lhs.base() == rhs.base());}
	template< class Iterator>
		bool operator!=( const reverse_iterator<Iterator>& lhs,const reverse_iterator<Iterator>& rhs ){return (!(lhs == rhs));}
	template< class Iterator>
		bool operator<( const reverse_iterator<Iterator>& lhs,const reverse_iterator<Iterator>& rhs ){return (rhs.base() < lhs.base());}
	template< class Iterator>
		bool operator<=( const reverse_iterator<Iterator>& lhs,const reverse_iterator<Iterator>& rhs ){return (!(rhs < lhs));}
	template< class Iterator>
		bool operator>( const reverse_iterator<Iterator>& lhs,const reverse_iterator<Iterator>& rhs ){return (rhs.base() > lhs.base());}
	template< class Iterator>
		bool operator>=( const reverse_iterator<Iterator>& lhs,const reverse_iterator<Iterator>& rhs ){return (!(rhs > lhs));}
	template<typename Iter>
		reverse_iterator<Iter>&
		operator-(typename ft::reverse_iterator<Iter>::difference_type lhs, const ft::reverse_iterator<Iter>& rhs)
		{return rhs - lhs;}
	template<typename Iter> reverse_iterator<Iter>
		operator+(const typename ft::reverse_iterator<Iter>::difference_type lhs, const ft::reverse_iterator<Iter>& rhs)
		{return rhs + lhs;}
	/*template<typename Iter>
		reverse_iterator<Iter>&
		operator+(const ft::reverse_iterator<Iter>& lhs, typename Iter::difference_type n)
		{
			return reverse_iterator<Iter>(lhs.base() - n);
		}
	template<typename Iter>
		reverse_iterator<Iter>&
		operator-(const ft::reverse_iterator<Iter>& lhs, typename Iter::difference_type n)
		{
			return reverse_iterator<Iter>(lhs.base() + n);
		}*/
	template<typename Iter1, typename Iter2> 
		ptrdiff_t operator-(const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs)
		{return rhs - lhs;}
	template<typename Iter1, typename Iter2> 
		ptrdiff_t operator+(const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs)
		{return rhs + lhs;}
};
#endif
