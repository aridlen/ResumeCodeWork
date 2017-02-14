
#ifndef _FULLSAIL_AI_FUNDAMENTALS_QUEUELIST_H_
#define _FULLSAIL_AI_FUNDAMENTALS_QUEUELIST_H_

namespace fullsail_ai { namespace fundamentals {


	template <typename T>
	class QueueList
	{
		struct Node
		{
			T data;
			Node* next;

			explicit Node(T);
			~Node();

			static unsigned int getCreatedNodeCount();
			static unsigned int getDestroyedNodeCount();

		private:
			static unsigned int createdNodeCount;
			static unsigned int destroyedNodeCount;
		};

	public:
		
		class Iterator
		{
			Node const* currentNode;

		
			friend class QueueList<T>;

		
			explicit Iterator(Node const* node);

		public:
			
			Iterator();

		
			Iterator& operator++();

			Iterator operator++(int);

			
			T operator*() const;

		
			inline friend bool operator==(Iterator const& lhs, Iterator const& rhs)
			{
				return lhs.currentNode == rhs.currentNode;
			}

			inline friend bool operator!=(Iterator const& lhs, Iterator const& rhs)
			{
				return lhs.currentNode != rhs.currentNode;
			}
		};

	private:
		Node* front;
		Node* back;

	public:
		//! \brief Default constructor.
		QueueList();

		//! \brief Cleans up all internal memory.
		~QueueList();

	private:
		// Do not implement.
		QueueList(QueueList const&);
		QueueList& operator=(QueueList const&);

	public:
		static unsigned int getCreatedNodeCount();
		static unsigned int getDestroyedNodeCount();

		//! \brief Returns an iterator pointing to the beginning of this <code>%QueueList</code>.
		Iterator begin() const;

		//! \brief Returns an iterator pointing past the end of this <code>%QueueList</code>.
		Iterator end() const;

		//! \brief Returns <code>true</code> if this <code>%QueueList</code> does not contain any
		//! elements, <code>false</code> otherwise.
		bool isEmpty() const;

		
		void enqueue(T element);

		//! \brief Returns the first element in this <code>%QueueList</code>.
		//!
	
		T getFront() const;

		//! \brief Removes the first element from this <code>%QueueList</code>.
		//!
		//! \pre
		//!   - <code>isEmpty()</code> returns <code>false</code>.
		//! \post
		//!   - <code>contains()</code> will return <code>false</code> if the removed element
		//!     is passed in.
		void dequeue();

		//! \brief Removes all elements from this <code>%QueueList</code>.
		//!
		//! \post
		//!   - <code>isEmpty()</code> will return <code>true</code>.
		void removeAll();

		//! \brief Returns <code>true</code> if this <code>%QueueList</code>
		//! possesses the specified element, <code>false</code> otherwise.
		bool contains(T element) const;

		//! \brief Finds the first occurrence of the specified element and
		//! removes it from the <code>%QueueList</code>.
		//!
		//! \pre
		//!   - <code>isEmpty()</code> returns <code>false</code>.
		void remove(T element);
	};

	template <typename T>
	unsigned int QueueList<T>::Node::createdNodeCount = 0;

	template <typename T>
	unsigned int QueueList<T>::Node::destroyedNodeCount = 0;

	template <typename T>
	QueueList<T>::Node::Node(T element) : data(element), next(0)
	{
		++createdNodeCount;
	}

	template <typename T>
	QueueList<T>::Node::~Node()
	{
		++destroyedNodeCount;
	}

	template <typename T>
	unsigned int QueueList<T>::getCreatedNodeCount()
	{
		return QueueList<T>::Node::getCreatedNodeCount();
	}

	template <typename T>
	unsigned int QueueList<T>::getDestroyedNodeCount()
	{
		return QueueList<T>::Node::getDestroyedNodeCount();
	}

	template <typename T>
	unsigned int QueueList<T>::Node::getCreatedNodeCount()
	{
		return createdNodeCount;
	}

	template <typename T>
	unsigned int QueueList<T>::Node::getDestroyedNodeCount()
	{
		return destroyedNodeCount;
	}

	template <typename T>
	QueueList<T>::Iterator::Iterator(Node const* node) : currentNode(node)
	{
	}

	template <typename T>
	QueueList<T>::Iterator::Iterator()
	{
	}

	template <typename T>
	typename QueueList<T>::Iterator QueueList<T>::Iterator::operator++(int)
	{
		Iterator itr(*this);
		++(*this);
		return itr;
	}

	template <typename T>
	typename QueueList<T>::Iterator QueueList<T>::begin() const
	{
		return Iterator(front);
	}

	template <typename T>
	typename QueueList<T>::Iterator QueueList<T>::end() const
	{
		return Iterator(0);
	}
}} 

#include "QueueList_TODO.h"

#endif 

