
#pragma once

#include "sml/type.h"

SML_NAMESPACE_BEGIN

//-----------------------------------
// List
//-----------------------------------
template<typename T>
class List
{
	SML_NONCOPYABLE(List)
public:
	//-----------------------------------
	// List::Node
	//-----------------------------------
	class Node
	{
		friend class List;
	public:
		Node(void);
		virtual ~Node(void);

		void remove(void);
	private:
		Node*	prev_;
		Node*	next_;
	};

	//-----------------------------------
	// List::iterator
	//-----------------------------------
	class iterator
	{
	public:
		iterator( Node* node );
		iterator( const iterator& rhs );

		virtual ~iterator(void);

		T& operator*(void);
		const T& operator*(void) const;

		T* operator->(void);
		const T* operator->(void) const;

		iterator& operator++(void);
		iterator operator++(int);

		iterator& operator--(void);
		iterator operator--(int);

		bool operator==( const iterator& rhs ) const;
		bool operator!=( const iterator& rhs ) const;
	private:
		Node* node_;
	};

public:
	List(void);
	virtual ~List(void);

	void insert( iterator itr, T& ref );
	void pushBack( T& ref );
	void pushFront( T& ref );

	iterator begin(void);
	const iterator begin(void) const;

	iterator end(void);
	const iterator end(void) const;

private:
	Node root_;
};

#include "sml/inl/list.inl"

SML_NAMESPACE_END
