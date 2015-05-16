//-----------------------------------
// List::Node
//-----------------------------------
template<typename T>
List<T>::Node::Node(void)
	: prev_(nullptr)
	, next_(nullptr)
{}

template<typename T>
List<T>::Node::~Node(void)
{
	remove();
}

template<typename T>
void List<T>::Node::remove(void)
{
	if( nullptr!=prev_ )
	{
		prev_->next_ = next_;
	}
	if( nullptr!=next_ )
	{
		next_->prev_ = prev_;
	}
	prev_ = nullptr;
	next_ = nullptr;
}

//-----------------------------------
// List::iterator
//-----------------------------------
template<typename T>
List<T>::iterator::iterator( Node* node )
	: node_(node)
{}

template<typename T>
List<T>::iterator::iterator( const iterator& rhs )
	: node_(rhs.node_)
{}

template<typename T>
List<T>::iterator::~iterator(void)
{}

template<typename T>
T& List<T>::iterator::operator*(void)
{
	T* ptr = static_cast<T*>(node_);
	return *ptr;
}

template<typename T>
const T& List<T>::iterator::operator*(void) const
{
	T* ptr = static_cast<T*>(node_);
	return *ptr;
}

template<typename T>
T* List<T>::iterator::operator->(void)
{
	T* ptr = static_cast<T*>(node_);
	return ptr;
}

template<typename T>
const T* List<T>::iterator::operator->(void) const
{
	T* ptr = static_cast<T*>(node_);
	return ptr;
}

template<typename T>
auto List<T>::iterator::operator++(void)->iterator&
{
	if( nullptr!=node_ )
	{
		node_ = node_->next_;
	}
	return *this;
}

template<typename T>
auto List<T>::iterator::operator++(int)->iterator
{
	iterator ret = *this;
	operator++();
	return ret;
}

template<typename T>
auto List<T>::iterator::operator--(void) ->iterator&
{
	if( nullptr!=node_ )
	{
		node_ = node_->prev_;
	}
	return *this;
}

template<typename T>
auto List<T>::iterator::operator--(int) ->iterator
{
	iterator ret = *this;
	operator--();
	return ret;
}

template<typename T>
bool List<T>::iterator::operator==( const iterator& rhs ) const
{
	return node_ == rhs.node_;
}

template<typename T>
bool List<T>::iterator::operator!=( const iterator& rhs ) const
{
	return !operator==(rhs);
}

//-----------------------------------
// List 
//-----------------------------------
template<typename T>
List<T>::List(void)
{
	root_.next_ = &root_;
	root_.prev_ = &root_;
}

template<typename T>
List<T>::~List(void)
{}

template<typename T>
void List<T>::insert(iterator itr, T& ref )
{
	ref.remove();

	T& dest = *itr;

	if( nullptr!=dest.prev_ )
	{
		dest.prev_->next_ = &ref;
	}
	ref.prev_ = dest.prev_;
	ref.next_ = &dest;
	dest.prev_ = &ref;
}

template<typename T>
void List<T>::pushBack( T& ref )
{
	insert( end(), ref );
}

template<typename T>
void List<T>::pushFront( T& ref )
{
	insert( begin(), ref );
}

template<typename T>
auto List<T>::begin(void) ->iterator
{
	return iterator( root_.next_ );
}

template<typename T>
auto List<T>::begin(void) const ->const iterator
{
	return iterator( root_.next_ );
}

template<typename T>
auto List<T>::end(void) ->iterator
{
	return iterator( &root_ );
}

template<typename T>
auto List<T>::end(void) const ->const iterator
{
	return iterator( &root_ );
}