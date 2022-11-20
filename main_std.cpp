#include <stdio.h>
#include <functional>
#include <iostream>
#include <string.h>
#include <typeinfo>
#include <vector>
#include <cassert>
#include <map>
#include <stack>
#include <set>
void    test_vectors(void)
{
	{
		{
			std::cout << "/*begin*/\n";
			std::vector<int> myvector;
			for (int i=1; i<=5; i++) myvector.push_back(i);
 
			std::cout << "myvector contains:";
			for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
			std::cout << "Expected Output:\n"<<"myvector contains: 1 2 3 4 5"<<"\n";
		}
		{
			std::cout << "/*end*/\n";
			std::vector<int> myvector;
			for (int i=1; i<=5; i++) myvector.push_back(i);
 
			std::cout << "myvector contains:";
			for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
			std::cout << "Expected Output:\n"<<"myvector contains: 1 2 3 4 5"<<"\n";
		}
		{
			std::cout << "/*rbegin*/\n";
			std::vector<int> myvector (5);  // 5 default-constructed ints
			int i=0;
			std::vector<int>::reverse_iterator rit = myvector.rbegin();
			for (; rit!= myvector.rend(); ++rit)
				*rit = ++i;
			std::cout << "myvector contains:";
			for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
			std::cout << "Expected Output:\n"<<"myvector contains: 5 4 3 2 1"<<"\n";
		}
		{
			std::cout << "/*rend*/\n";
			std::vector<int> myvector (5);  // 5 default-constructed int
			std::vector<int>::reverse_iterator rit = myvector.rbegin();
			int i=0;
			for (rit = myvector.rbegin(); rit!= myvector.rend(); ++rit)
				*rit = ++i;
			std::cout << "myvector contains:";
			for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
			std::cout << "Expected Output:\n"<<"myvector contains: 5 4 3 2 1"<<"\n";
		}
    }
    {
        std::cout<< "/*resize*/\n";
        std::vector<int> myvector;
 
        // set some initial content:
        for (int i=1;i<10;i++) myvector.push_back(i);
 
        std::cout << myvector.size() << " " << myvector.capacity() << '\n';
        myvector.resize(5);
        std::cout << myvector.size() << " " << myvector.capacity() << '\n';
        myvector.resize(8,100);
        std::cout << myvector.size() << " " << myvector.capacity() << '\n';
        myvector.resize(44);
        myvector.push_back(442);
        std::cout << myvector.size() << " " << myvector.capacity() << '\n';
 
        std::cout << "myvector contains:";
        for (unsigned long i=0;i<myvector.size();i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';
        std::cout << "Expected Output:\n"<<"9 16\n5 16\n8 16\n45 88\nmyvector contains: 1 2 3 4 5 100 100 100 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 442"<<"\n";
    }
    {
        std::cout<< "/*reserve*/\n";
        std::vector<int>::size_type sz;
        std::vector<int> foo;
        sz = foo.capacity();
        std::cout << "making foo grow:\n";
        for (int i=0; i<100; ++i)
        {
            foo.push_back(i);
            if (sz!=foo.capacity())
            {
                sz = foo.capacity();
                std::cout << "capacity changed: " << sz << '\n';
            }
        }
        std::vector<int> bar;
        sz = bar.capacity();
        bar.reserve(100);   // this is the only difference with foo above
        std::cout << "making bar grow:\n";
        for (int i=0; i<100; ++i)
        {
            bar.push_back(i);
            if (sz!=bar.capacity())
            {
                sz = bar.capacity();
                std::cout << "capacity changed: " << sz << '\n';
            }
        }
        std::cout << "Expected Output:\n"<<"making foo grow:\ncapacity changed: 1\ncapacity changed: 2\ncapacity changed: 4\ncapacity changed: 8\ncapacity changed: 16\ncapacity changed: 32\ncapacity changed: 64\ncapacity changed: 128\nmaking bar grow:\ncapacity changed: 100"<<"\n";
    }
 
    {
        std::cout<< "/*push_back e pop_back*/\n";
        std::vector<int> myvector;
        int sum (0);
        myvector.push_back (100);
        myvector.push_back (200);
        myvector.push_back (300);
        while (!myvector.empty())
        {
            sum+=myvector.back();
            myvector.pop_back();
        }
        std::cout << "The elements of myvector add up to " << sum << '\n';
        std::cout << "Expected Output:\n"<<"The elements of myvector add up to 600"<<"\n";
    }
    {
        std::cout << "/*insert*/\n"; 
        std::vector<int> myvector (3,100);
        std::vector<int>::iterator it;
        it = myvector.begin();
        it = myvector.insert ( it , 200 );
        myvector.insert(it,2,300);
        // "it" no longer valid, get a new one:
        it = myvector.begin();
 
        std::vector<int> anothervector (2,400);
        myvector.insert(it+2,anothervector.begin(),anothervector.end());

        int myarray [] = { 501,502,503 };
        myvector.insert(myvector.begin(), myarray, myarray+3);
        std::cout << "myvector contains:";
        for (it=myvector.begin(); it<myvector.end(); it++)
            std::cout << ' ' << *it;
        std::cout << '\n';
        std::cout << "Expected Output:\n"<< "myvector contains: 501 502 503 300 300 400 400 200 100 100 100"<<"\n";
    }

    {
        std::cout << "\n/* erase */\n";
        std::vector<int> myvector;
        for (int i=1; i<=10; i++) myvector.push_back(i);
        std::cout << *myvector.erase(myvector.begin()+5) << '\n';
        std::cout << *myvector.erase(myvector.begin(),myvector.begin()+3) << '\n';
        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); ++i)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';
        std::cout << "Expected Output:\n"<<"7\n4\nmyvector contains: 4 5 7 8 9 10"<<"\n";
    }
    {
        std::cout << "\n/* swap */\n";
        std::vector<int> foo (3,100);   // three ints with a value of 100
        std::vector<int> bar (5,200);   // five ints with a value of 200
        foo.swap(bar);
        std::cout << "foo contains:";
        for (unsigned i=0; i<foo.size(); i++)
            std::cout << ' ' << foo[i];
        std::cout << '\n';
        std::cout << "bar contains:";
        for (unsigned i=0; i<bar.size(); i++)
            std::cout << ' ' << bar[i];
        std::cout << '\n';
        std::cout << "Expected Output:\n"<<"foo contains: 200 200 200 200 200\nbar contains: 100 100 100"<<"\n";
    }
    {
        std::cout << "\n/* clear */\n";
        std::vector<int> myvector;
        myvector.push_back (100);
        myvector.push_back (200);
        myvector.push_back (300);
        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';
        myvector.clear();
        myvector.push_back (1101);
        myvector.push_back (2202);
        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';
        std::cout << "Expected Output:\nmyvector contains: 100 200 300\nmyvector contains: 1101 2202\n";
    }
    {
        std::cout << "\n/* get allocator */\n";
        std::vector<int> myvector;
        int * p;
        unsigned int i;
 
        // allocate an array with space for 5 elements using vector's allocator:
        p = myvector.get_allocator().allocate(5);
 
        // construct values in-place on the array:
        for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);
 
        std::cout << "The allocated array contains:";
        for (i=0; i<5; i++) std::cout << ' ' << p[i];
        std::cout << '\n';
 
        // destroy and deallocate:
        for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
        myvector.get_allocator().deallocate(p,5);
        std::cout << "Expected Output:\n" << "The allocated array contains: 0 1 2 3 4" << "\n";
    }
 
}
 
template <class T>typename std::enable_if<std::is_integral<T>::value,bool>::type is_odd (T i)
{
	return bool(i%2);
}
template <class T> typename std::enable_if<std::is_integral<T>::value,bool>::type is_even (T i)
{
	return !bool(i%2);
}
bool mycomp (char c1, char c2)
{
	return std::tolower(c1)<std::tolower(c2);
}
bool mypredicate (int i, int j)
{
  return (i==j);
}
 

void check_set(void)
{
	std::cout << "\n\n~~~~~~~~~~~~~~ SET TESTS ~~~~~~~~~~~~~~\n\n";
	{
		std::cout << "\nConstructor test:\n\n";
		std::set<std::string> a;
		a.insert("cat");
		a.insert("dog");
		a.insert("horse");
		for(std::set<std::string>::iterator it = a.begin(); it != a.end(); it++) std::cout << *it << ' ';
		std::cout << '\n';
 
		// (2) Iterator constructor
		std::set<std::string> b(a.find("dog"), a.end());
		for(std::set<std::string>::iterator it = b.begin(); it != b.end(); it++) std::cout << *it << ' ';
		std::cout << '\n';
 
		// (3) Copy constructor
		std::set<std::string> c(a);
		c.insert("another horse");
		for(std::set<std::string>::iterator it = c.begin(); it != c.end(); it++) std::cout << *it << ' ';
		std::cout << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "cat dog horse\ndog horse\nanother horse cat dog horse\n";
 
	}
    {
		std::cout << "\nBegin test:\n\n";
		int myints[]={ 12,82,37,64,15 };
		std::set<int> first (myints,myints+5);   // set with 5 ints
		std::set<int> second;                    // empty set
		second = first;                         // now second contains the 5 ints
		first = std::set<int>();                 // and first is empty
		std::cout << "Size of first: " << int (first.size()) << '\n';
		std::cout << "Size of second: " << int (second.size()) << '\n';
		std::cout << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "Size of first: 0\nSize of second: 5\n";
	}
	{
		std::cout << "\nEnd test:\n\n";
		int myints[] = {75,23,65,42,13};
		std::set<int> myset (myints,myints+5);
		std::cout << "myset contains:";
		for (std::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "myset contains: 13 23 42 65 75\n";
 
	}
	{
		std::cout << "\nRbegin test:\n\n";
		int myints[] = {21,64,17,78,49};
		std::set<int> myset (myints,myints+5);
		std::set<int>::reverse_iterator rit;
		std::cout << "myset contains:";
		for (rit=myset.rbegin(); rit != myset.rend(); ++rit)
			std::cout << ' ' << *rit;
		std::cout << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "myset contains: 78 64 49 21 17\n";
	}
	{
		std::cout << "\nRend test:\n\n";
		int myints[] = {21,64,17,78,49};
		std::set<int> myset (myints,myints+5);
		std::set<int>::reverse_iterator rit;
		std::cout << "myset contains:";
		for (rit=myset.rbegin(); rit != myset.rend(); ++rit)
			std::cout << ' ' << *rit;
		std::cout << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "myset contains: 78 64 49 21 17\n";
	}
	{
		std::cout << "\nEmpty test:\n\n";
		std::set<int> myset;
		myset.insert(20);
		myset.insert(30);
		myset.insert(10);
		std::cout << "myset contains:";
		while (!myset.empty())
		{
			std::cout << ' ' << *myset.begin();
			myset.erase(myset.begin());
		}
		std::cout << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "myset contains: 10 20 30\n";
 
	}
	{
		std::cout << "\nSize test:\n\n";
		std::set<int> myints;
		std::cout << "0. size: " << myints.size() << '\n';
		for (int i=0; i<10; ++i) myints.insert(i);
		std::cout << "1. size: " << myints.size() << '\n';
		myints.insert (100);
		std::cout << "2. size: " << myints.size() << '\n';
		myints.erase(5);
		std::cout << "3. size: " << myints.size() << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "0. size: 0\n1. size: 10\n2. size: 11\n3. size: 10\n";
	}
	{
		std::cout << "\nMax Size test:\n\n";
		int i;
		std::set<int> myset;
 
		if (myset.max_size()>1000)
		{
			for (i=0; i<1000; i++) myset.insert(i);
			std::cout << "The set contains 1000 elements.\n";
		}
		else std::cout << "The set could not hold 1000 elements.\n";
		std::cout << "Expected Output:\n";
		std::cout << "The set contains 1000 elements.\n";
	}
	{
		std::cout << "\nInsert test:\n\n";
		std::set<int> myset;
		std::set<int>::iterator it;
		std::pair<std::set<int>::iterator,bool> ret;
		// set some initial values:
		for (int i=1; i<=5; ++i) myset.insert(i*10);    // set: 10 20 30 40 50
		ret = myset.insert(20);               // no new element inserted
		if (ret.second==false) it=ret.first;  // "it" now points to element 20
		myset.insert (it,25);                 // max efficiency inserting
		myset.insert (it,24);                 // max efficiency inserting
		myset.insert (it,26);                 // no max efficiency inserting
		int myints[]= {5,10,15};              // 10 already in set, not inserted
		myset.insert(myints + 0 ,myints+3);
		std::cout << "myset contains:";
		for (it=myset.begin(); it!=myset.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "myset contains: 5 10 15 20 24 25 26 30 40 50\n";
	}
	{
		std::cout << "\nErase test:\n\n";
		std::set<int> myset;
		std::set<int>::iterator it;
 
		// insert some values:
		for (int i=1; i<10; i++) myset.insert(i*10);  // 10 20 30 40 50 60 70 80 90
 
		it = myset.begin();
		++it;                                         // "it" points now to 20
 
		myset.erase (it);
 
		myset.erase (40);
 
		it = myset.find (60);
		myset.erase (it, myset.end());
 
		std::cout << "myset contains:";
		for (it=myset.begin(); it!=myset.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "myset contains: 10 30 50\n";
	}
	{
		std::cout << "\nSwap test:\n\n";
		int myints[]={12,75,10,32,20,25};
		std::set<int> first (myints,myints+3);     // 10,12,75
		std::set<int> second (myints+3,myints+6);  // 20,25,32
		first.swap(second);
		std::cout << "first contains:";
		for (std::set<int>::iterator it=first.begin(); it!=first.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
		std::cout << "second contains:";
		for (std::set<int>::iterator it=second.begin(); it!=second.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "first contains: 20 25 32\nsecond contains: 10 12 75\n";
	}
	{
		std::cout << "\nClear test:\n\n";
		std::set<int> myset;
		myset.insert (100);
		myset.insert (200);
		myset.insert (300);
		std::cout << "myset contains:";
		for (std::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
		myset.clear();
		myset.insert (1101);
		myset.insert (2202);
		std::cout << "myset contains:";
		for (std::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "myset contains: 100 200 300\nmyset contains: 1101 2202\n";
	}
	{
		std::cout << "\nKey Comp test:\n\n";
		std::set<int> myset;
		int highest;
		std::set<int>::key_compare mycomp = myset.key_comp();
		for (int i=0; i<=5; i++) myset.insert(i);
		std::cout << "myset contains:";
		highest = *myset.rbegin();
		std::set<int>::iterator it=myset.begin();
		do {
			std::cout << ' ' << *it;
		} while ( mycomp(*(++it),highest) );
		std::cout << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "myset contains: 0 1 2 3 4\n";
	}
	{
		std::cout << "\nValue Comp test:\n\n";
		std::set<int> myset;
 
		std::set<int>::value_compare mycomp = myset.value_comp();
 
		for (int i=0; i<=5; i++) myset.insert(i);
 
		std::cout << "myset contains:";
 
		int highest = *myset.rbegin();
		std::set<int>::iterator it=myset.begin();
		do {
			std::cout << ' ' << *it;
		} while ( mycomp(*(++it),highest) );
 
		std::cout << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "myset contains: 0 1 2 3 4\n";
	}
	{
		std::cout << "\nFind test:\n\n";
		std::set<int> myset;
		std::set<int>::iterator it;
		// set some initial values:
		for (int i=1; i<=5; i++) myset.insert(i*10);    // set: 10 20 30 40 50
		it=myset.find(20);
		myset.erase (it);
		myset.erase (myset.find(40));
		std::cout << "myset contains:";
		for (it=myset.begin(); it!=myset.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "myset contains: 10 30 50\n";
	}
	{
		std::cout << "\nCount test:\n\n";
		std::set<int> myset;
 
		// set some initial values:
		for (int i=1; i<5; ++i) myset.insert(i*3);    // set: 3 6 9 12
 
		for (int i=0; i<10; ++i)
		{
			std::cout << i;
			if (myset.count(i)!=0)
			std::cout << " is an element of myset.\n";
			else
			std::cout << " is not an element of myset.\n";
		}
		std::cout << "Expected Output:\n";
		std::cout << "0 is not an element of myset.\n1 is not an element of myset.\n2 is not an element of myset.\n3 is an element of myset.\n4 is not an element of myset.\n5 is not an element of myset.\n6 is an element of myset.\n7 is not an element of myset.\n8 is not an element of myset.\n9 is an element of myset.\n";
	}
	{
		std::cout << "\nLower Bound test:\n\n";
		std::set<int> myset;
		std::set<int>::iterator itlow,itup;
 
		for (int i=1; i<10; i++) myset.insert(i*10); // 10 20 30 40 50 60 70 80 90
 
		itlow=myset.lower_bound (30);                //       ^
		itup=myset.upper_bound (60);                 //                   ^
 
		myset.erase(itlow,itup);                     // 10 20 70 80 90
 
		std::cout << "myset contains:";
		for (std::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "myset contains: 10 20 70 80 90\n";
	}
	{
		std::cout << "\nUpper Bound test:\n\n";
		std::set<int> myset;
		std::set<int>::iterator itlow,itup;
		for (int i=1; i<10; i++) myset.insert(i*10); // 10 20 30 40 50 60 70 80 90
		itlow=myset.lower_bound (30);                //       ^
		itup=myset.upper_bound (60);                 //                   ^
		myset.erase(itlow,itup);                     // 10 20 70 80 90
		std::cout << "myset contains:";
		for (std::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "myset contains: 10 20 70 80 90\n";
	}
	{
		std::cout << "\nEqual Range test:\n\n";
		std::set<int> myset;
		for (int i=1; i<=5; i++) myset.insert(i*10);   // myset: 10 20 30 40 50
		std::pair<std::set<int>::iterator, std::set<int>::iterator> ret;
		ret = myset.equal_range(30);
		std::cout << "the lower bound points to: " << *ret.first << '\n';
		std::cout << "the upper bound points to: " << *ret.second << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "the lower bound points to: 30\nthe upper bound points to: 40\n";
		return ;
	}
	{
			std::set<int> myset;
			myset.insert(0);
			myset.insert(1);
			myset.insert(2);
			myset.insert(7);
			myset.insert(14);
			myset.insert(9);
			myset.insert(10);
			myset.insert(19);
			myset.insert(17);
			myset.insert(28);
			myset.insert(54);
			myset.insert(32);
			myset.insert(29);
			myset.insert(42);
			myset.insert(44);
			myset.insert(79);
			myset.insert(76);
			myset.insert(65);
			myset.insert(60);
			myset.insert(77);
			myset.insert(78);
			myset.insert(81);
			myset.insert(80);
			myset.insert(97);
			myset.insert(82);
			std::cout << "Iterating\n";
			for(std::set<int>::iterator it = myset.begin(); it != myset.end(); it++)
				std::cout << *it;
			for(std::set<int>::reverse_iterator it = myset.rbegin(); it != myset.rend(); it++)
				std::cout << *it;
		}
}
void check_map(void)
{
	std::cout << "\n\n~~~~~~~~~~~~~~ MAP TESTS ~~~~~~~~~~~~~~\n\n";
	{
		std::cout << "\nConstructor test:\n\n";
		std::map<char,int> first;
		first['a']=10;
		first['b']=30;
		first['c']=50;
		first['d']=70;
		std::map<char,int> second (first.begin(),first.end());
		std::map<char,int> third (second);
		std::cout << "Expected Output:\n";
		std::cout << "\n";
	}
	{
		std::cout << "\nOperator= test:\n\n";
		std::map<char,int> first;
		std::map<char,int> second;
		first['x']=8;
		first['y']=16;
		first['z']=32;
		second=first;                // second now contains 3 ints
		first=std::map<char,int>();  // and first is now empty
		std::cout << "Size of first: " << first.size() << '\n';
		std::cout << "Size of second: " << second.size() << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "Size of first: 0\nSize of second: 3\n";
	}
	{
		std::cout << "\nBegin&End test:\n\n";
		std::map<char,int> mymap;
		mymap['b'] = 100;
		mymap['a'] = 200;
		mymap['c'] = 300;
		// show content:
		for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "a => 200\nb => 100\nc => 300\n";
	}
	{
		std::cout << "\nRBegin&REnd test:\n\n";
		std::map<char,int> mymap;
		mymap['x'] = 100;
		mymap['y'] = 200;
		mymap['z'] = 300;
		// show content:
		std::map<char,int>::reverse_iterator rit;
		for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
			std::cout << rit->first << " => " << rit->second << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "z => 300\ny => 200\nx => 100\n";
	}
	{
		std::cout << "\nEmpty test:\n\n";
		std::map<char,int> mymap;
		mymap['a']=10;
		mymap['b']=20;
		mymap['c']=30;
		while (!mymap.empty())
		{
			std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
			mymap.erase(mymap.begin());
		}
		std::cout << "Expected Output:\n";
		std::cout << "a => 10\nb => 20\nc => 30\n";
	}
	{
		std::cout << "\nSize test:\n\n";
		std::map<char,int> mymap;
		mymap['a']=101;
		mymap['b']=202;
		mymap['c']=302;
 
		std::cout << "mymap.size() is " << mymap.size() << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "mymap.size() is 3\n";
	}
	{
		std::cout << "\nMax_size test:\n\n";
		int i;
		std::map<int,int> mymap;
		if (mymap.max_size()>1000)
		{
			for (i=0; i<1000; i++) mymap[i]=0;
			std::cout << "The map contains 1000 elements.\n";
		}
		else std::cout << "The map could not hold 1000 elements.\n";
		std::cout << "Expected Output:\n";
		std::cout << "\n";
	}
	{
		std::cout << "\nOperator[] test:\n\n";
		std::map<char,std::string> mymap;
		mymap['a']="an element";
		mymap['b']="another element";
		mymap['c']=mymap['b'];
		std::cout << "mymap['a'] is " << mymap['a'] << '\n';
		std::cout << "mymap['b'] is " << mymap['b'] << '\n';
		std::cout << "mymap['c'] is " << mymap['c'] << '\n';
		std::cout << "mymap['d'] is " << mymap['d'] << '\n';
 
		std::cout << "mymap now contains " << mymap.size() << " elements.\n";
		std::cout << "Expected Output:\n";
		std::cout << "mymap['a'] is an element\nmymap['b'] is another element\nmymap['c'] is another element\nmymap['d'] is\nmymap now contains 4 elements.\n";
	}
	{
		std::cout << "\nInsert test:\n\n";
		std::map<char,int> mymap;
		// first insert function version (single parameter):
		mymap.insert ( std::pair<char,int>('a',100) );
		mymap.insert ( std::pair<char,int>('z',200) );
		std::pair<std::map<char,int>::iterator,bool> ret;
		ret = mymap.insert ( std::pair<char,int>('z',500) );
		if (ret.second==false) {
			std::cout << "element 'z' already existed";
			std::cout << " with a value of " << ret.first->second << '\n';
		}
		// second insert function version (with hint position):
		std::map<char,int>::iterator it = mymap.begin();
		mymap.insert (it, std::pair<char,int>('b',300));  // max efficiency inserting
		mymap.insert (it, std::pair<char,int>('c',400));  // no max efficiency inserting
		// third insert function version (range insertion):
		std::map<char,int> anothermap;
		anothermap.insert(mymap.begin(),mymap.find('c'));
		// showing contents:
		std::cout << "mymap contains:\n";
		for (it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
		std::cout << "anothermap contains:\n";
		for (it=anothermap.begin(); it!=anothermap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "element 'z' already existed with a value of 200\nmymap contains:\na => 100\nb => 300\nc => 400\nz => 200\nanothermap contains:\na => 100\nb => 300\n";
	}
	{
		std::cout << "\nErase test:\n\n";
		std::map<char,int> mymap;
		std::map<char,int>::iterator it;
		// insert some values:
		mymap['a']=10;
		mymap['b']=20;
		mymap['c']=30;
		mymap['d']=40;
		mymap['e']=50;
		mymap['f']=60;
		it=mymap.find('b');
		mymap.erase (it);                   // erasing by iterator
		mymap.erase ('c');                  // erasing by key
		it=mymap.find ('e');
		mymap.erase ( it, mymap.end() );    // erasing by range
		// show content:
		for (it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "a => 10\nd => 40\n";
	}
	{
		std::cout << "\nSwap test:\n\n";
		std::map<char,int> foo,bar;
		foo['x']=100;
		foo['y']=200;
		bar['a']=11;
		bar['b']=22;
		bar['c']=33;
		foo.swap(bar);
		std::cout << "foo contains:\n";
		for (std::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
		std::cout << "bar contains:\n";
		for (std::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "foo contains:\na => 11\nb => 22\nc => 33\nbar contains:\nx => 100\ny => 200\n";
	}
	{
		std::cout << "\nClear test:\n\n";
		std::map<char,int> mymap;
		mymap['x']=100;
		mymap['y']=200;
		mymap['z']=300;
		std::cout << "mymap contains:\n";
		for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
		mymap.clear();
		mymap['a']=1101;
		mymap['b']=2202;
		std::cout << "mymap contains:\n";
		for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "mymap contains:\nx => 100\ny => 200\nz => 300\nmymap contains:\na => 1101\nb => 2202\n";
	}
	{
		std::cout << "\nKey Comp test:\n\n";
		std::map<char,int> mymap;
		std::map<char,int>::key_compare mycomp = mymap.key_comp();
		mymap['a']=100;
		mymap['b']=200;
		mymap['c']=300;
		std::cout << "mymap contains:\n";
		char highest = mymap.rbegin()->first;     // key value of last element
		std::map<char,int>::iterator it = mymap.begin();
		do {
			std::cout << it->first << " => " << it->second << '\n';
		} while ( mycomp((*it++).first, highest) );
		std::cout << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "mymap contains:\na => 100\nb => 200\nc => 300\n";
	}
	{
		std::cout << "\nFind test:\n\n";
		std::map<char,int> mymap;
		std::map<char,int>::iterator it;
		mymap['a']=50;
		mymap['b']=100;
		mymap['c']=150;
		mymap['d']=200;
		it = mymap.find('b');
		if (it != mymap.end())
			mymap.erase (it);
		// print content:
		std::cout << "elements in mymap:" << '\n';
		std::cout << "a => " << mymap.find('a')->second << '\n';
		std::cout << "c => " << mymap.find('c')->second << '\n';
		std::cout << "d => " << mymap.find('d')->second << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "elements in mymap:\na => 50\nc => 150\nd => 200\n";
	}
	{
		std::cout << "\nCount test:\n\n";
		std::map<char,int> mymap;
		char c;
		mymap ['a']=101;
		mymap ['c']=202;
		mymap ['f']=303;
		for (c='a'; c<'h'; c++)
		{
			std::cout << c;
			if (mymap.count(c)>0)
			std::cout << " is an element of mymap.\n";
			else 
			std::cout << " is not an element of mymap.\n";
		}
		std::cout << "Expected Output:\n";
		std::cout << "a is an element of mymap.\nb is not an element of mymap.\nc is an element of mymap.\nd is not an element of mymap.\ne is not an element of mymap.\nf is an element of mymap.\ng is not an element of mymap.\n";
	}
	{
		std::cout << "\nLower_Bound test:\n\n";
		std::map<char,int> mymap;
		std::map<char,int>::iterator itlow,itup;
		mymap['a']=20;
		mymap['b']=40;
		mymap['c']=60;
		mymap['d']=80;
		mymap['e']=100;
		itlow=mymap.lower_bound('b');  // itlow points to b
		itup=mymap.upper_bound('d');   // itup points to e (not d!)
		mymap.erase(itlow,itup);        // erases [itlow,itup)
		// print content:
		for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "a => 20\ne => 100\n";
	}
	{
		std::cout << "\nUpper_bound test:\n\n";
		std::map<char,int> mymap;
		std::map<char,int>::iterator itlow,itup;
		mymap['a']=20;
		mymap['b']=40;
		mymap['c']=60;
		mymap['d']=80;
		mymap['e']=100;
		itlow=mymap.lower_bound ('b');  // itlow points to b
		itup=mymap.upper_bound ('d');   // itup points to e (not d!)
		mymap.erase(itlow,itup);        // erases [itlow,itup)
		// print content:
		for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "a => 20\ne => 100\n";
	}
	{
		std::cout << "\nEqual Bound test:\n\n";
		std::map<char,int> mymap;
		mymap['a']=10;
		mymap['b']=20;
		mymap['c']=30;
		std::pair<std::map<char,int>::iterator,std::map<char,int>::iterator> ret;
		ret = mymap.equal_range('b');
		std::cout << "lower bound points to: ";
		std::cout << ret.first->first << " => " << ret.first->second << '\n';
		std::cout << "upper bound points to: ";
		std::cout << ret.second->first << " => " << ret.second->second << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "lower bound points to: 'b' => 20\nupper bound points to: 'c' => 30\n";
	}
		{
			std::map<int, char> myset;
			myset.insert(std::make_pair(0, 'a'));
			myset.insert(std::make_pair(1, 's'));
			myset.insert(std::make_pair(2, 'd'));
			myset.insert(std::make_pair(7, 'f'));
			myset.insert(std::make_pair(14,'g'));
			myset.insert(std::make_pair(9, 'h'));
			myset.insert(std::make_pair(10,'j'));
			myset.insert(std::make_pair(19,'k'));
			myset.insert(std::make_pair(17,'l'));
			myset.insert(std::make_pair(28,'z'));
			myset.insert(std::make_pair(54,'x'));
			myset.insert(std::make_pair(32,'c'));
			myset.insert(std::make_pair(29,'v'));
			myset.insert(std::make_pair(42,'b'));
			myset.insert(std::make_pair(44,'n'));
			myset.insert(std::make_pair(79,'m'));
			myset.insert(std::make_pair(76,'q'));
			myset.insert(std::make_pair(65,'w'));
			myset.insert(std::make_pair(60,'e'));
			myset.insert(std::make_pair(77,'r'));
			myset.insert(std::make_pair(78,'t'));
			myset.insert(std::make_pair(81,'y'));
			myset.insert(std::make_pair(80,'u'));
			myset.insert(std::make_pair(97,'i'));
			myset.insert(std::make_pair(82,'o'));
			for(std::map<int, char>::iterator it = myset.begin(); it != myset.end(); it++)
				std::cout << (*it).first << " " << (*it).second << std::endl;
			for(std::map<int, char>::reverse_iterator it = myset.rbegin(); it != myset.rend(); it++)
				std::cout << (*it).first << " " << (*it).second << std::endl;
		}
}

void reportStackSize(const std::stack<int>& s){std::cout << s.size() << " elements on stack\n";}
void reportStackTop(const std::stack<int>& s){std::cout << "Top element: " << s.top() << '\n';}
void check_stack()
{
	std::cout << "\n\n~~~~~~~~~~~~~~ STACK TESTS ~~~~~~~~~~~~~~\n\n";
	{
		std::cout << "\nConstructor test:\n\n";
		std::stack<int> c1;
		c1.push(5);
		std::cout << c1.size() << '\n';
 
		std::stack<int> c2(c1);
		std::cout << c2.size() << '\n';
		std::cout << "Expected Output:\n";	
		std::cout << "1\n1\n";
	}
	{
		std::cout << "\nTop test:\n\n";
		std::stack<int> s;
		s.push(2);
		s.push(6);
		s.push(51);
		reportStackSize(s);
		reportStackTop(s);
		reportStackSize(s);
		s.pop();
		reportStackSize(s);
		reportStackTop(s);
		std::cout << "Expected Output:\n";
		std::cout << "3 elements on stack\nTop element: 51\n3 elements on stack\n2 elements on stack\nTop element: 6\n";
	}
	{
		std::cout << "\nEmpty test:\n\n";
		std::cout << std::boolalpha;
		std::stack<int> container;
		std::cout << "Initially, container.empty(): " << container.empty() << '\n';
		container.push(42);
		std::cout << "After adding elements, container.empty(): " << container.empty() << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "Initially, container.empty(): true\nAfter adding elements, container.empty(): false\n";
	}
	{
		std::cout << "\nSize test:\n\n";
		std::stack<int> container;
		std::cout << "Initially, container.size(): " << container.size() << '\n';
		for (int i = 0; i < 7; ++i)
			container.push(i);
		std::cout << "After adding elements, container.size(): " << container.size() << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "Initially, container.size(): 0\nAfter adding elements, container.size(): 7\n";
	}
	{
		std::cout << "\nPush test:\n\n";
		std::stack<int> mystack;
		for (int i=0; i<5; ++i) mystack.push(i);
		std::cout << "Popping out elements...";
		while (!mystack.empty())
		{
			std::cout << ' ' << mystack.top();
			mystack.pop();
		}
		std::cout << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "Popping out elements... 4 3 2 1 0\n";
	}
	{
		std::cout << "\nPop test:\n\n";
		std::stack<int> mystack;
		for (int i=0; i<5; ++i) mystack.push(i);
		std::cout << "Popping out elements...";
		while (!mystack.empty())
		{
			std::cout << ' ' << mystack.top();
			mystack.pop();
		}
		std::cout << '\n';
		std::cout << "Expected Output:\n";
		std::cout << "Popping out elements... 4 3 2 1 0\n";
	}
}


int main()
{
 
	{
		test_vectors();
        check_set();
		check_map();
		check_stack();
	}
	
}