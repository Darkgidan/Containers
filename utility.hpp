#ifndef UTILITY_HPP
#define UTILITY_HPP
#include <iostream>
#include <string.h>

namespace ft
{
	template <bool Cond, class T = void> 
	struct enable_if{};
	template<class T> struct enable_if<true, T> { typedef T type; };
	
	template <class T, T v>
	struct integral_constant 
	{
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T,v> type;
		operator T()const { return v; }
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	template <class T> struct is_integral : public false_type{};
	
	template <class T> struct is_integral<const T> : public is_integral<T>{};
	template <class T> struct is_integral<const volatile T> : public is_integral<T>{};
	template <class T> struct is_integral<volatile T> : public is_integral<T>{};

	template <> struct is_integral<bool> : public true_type{};

	template <> struct is_integral<char> : public true_type{};
	template <> struct is_integral<wchar_t> : public true_type{};
	template <> struct is_integral<signed char> : public true_type{};

	template <> struct is_integral<int> : public true_type{};
	template <> struct is_integral<short int> : public true_type{};
	template <> struct is_integral<long int> : public true_type{};
	template <> struct is_integral<long long int> : public true_type{};

	template <> struct is_integral<unsigned char> : public true_type{};
	template <> struct is_integral<unsigned short int> : public true_type{};
	template <> struct is_integral<unsigned int> : public true_type{};
	template <> struct is_integral<unsigned long int> : public true_type{};
	template <> struct is_integral<unsigned long long int> : public true_type{};


	template <class InI, class InJ>
	bool lexicographical_compare (InI first1, InI last1, InJ first2, InJ last2)
	{
	  	while (first1!=last1)
	  	{
	    	if (first2==last2 || *first2<*first1) 
				return false;
	    	else if (*first1<*first2) 
				return true;
	    	first1++;
			first2++;
	  	}
	  	return (first2!=last2);
	}
	template <class InI, class InJ, class Compare> 
	bool lexicographical_compare (InI first1, InI last1, InJ first2, InJ last2, Compare comp)
	{
	  	while (first1!=last1)
	  	{
	    	if (first2==last2 || comp(*first2, *first1)) 
				return false;
	    	else if (comp(*first1, *first2)) 
				return true;
	    	first1++;
			first2++;
	  	}
	  	return (first2!=last2);
	}
	template <class InI, class InJ>
	bool equal (InI first1, InI last1, InJ first2)
	{
  		while (first1!=last1) 
		{
    		if (!(*first1 == *first2))
      			return false;
    		first1++;
			first2++;
		}
		return true;
  	}
	template <class InI, class InJ, class BinaryPredicate>
	bool equal (InI first1, InI last1, InJ first2, BinaryPredicate pred)
	{
  		while (first1!=last1) 
		{
    		if (!pred(*first1,*first2))
      			return false;
    		first1++;
			first2++;
		}
		return true;
  	}
	template <class T1, class T2> struct pair
	{
		public:
			T1 first;
			T2 second;
			pair(): first(T1()), second(T2())
			{
			}
			template<class U, class V> pair (const pair<U,V>& pr): first(pr.first), second(pr.second)
			{
			}
			pair (const T1& a, const T2& b): first(a), second(b)
			{
			}
			pair& operator= (const pair& pr)
			{
				this->first = pr.first;
				this->second = pr.second;
				return(*this);
			}	
	};
	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ 
		return lhs.first==rhs.first && lhs.second==rhs.second; 
	}

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ 
		return !(lhs==rhs); 
	}

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ 
		return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); 
	}

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ 
		return !(rhs<lhs); 
	}

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ 
		return rhs<lhs; 
	}

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ 
		return !(lhs<rhs); 
	}

	template <class T1,class T2>
  	pair<T1,T2> make_pair (T1 x, T2 y)
  	{
    	return ( pair<T1,T2>(x,y) );
  	}

	template <class T>
	const T &min(const T &a,const T &b)
	{
		if (a < b)
			return(a);
		else
			return(b);
	}

	template <class T>
	const T &max(const T &a,const T &b)
	{
		if (a > b)
			return(a);
		else
			return(b);
	}

	template <class T>
	bool lt(const T &a,const T &b)
	{
		if (a < b)
			return(1);
		else
			return(0);
	}

	template <class T>
	bool gt(const T &a,const T &b)
	{
		if (a > b)
			return(1);
		else
			return(0);
	}

	template <class T>
	bool equal(const T &a,const T &b)
	{
		if (a == b)
			return(1);
		else
			return(0);
	}

	template <class T>
	void swap(T &a,T &b)
	{
		std::swap(a,b);
		//T supp = a;
		//a = b;
		//b = supp;
		return;
	}
}

#endif