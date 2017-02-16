///////////////////////////////////////////
//                                       //
//       THIS IS THE WORK OF:            //
//     Programmer: Aaron Ridlen          //
//     Instructor: Johnathan Burnsides   //
//      Date:  10/24/2016                //
//                                       //
///////////////////////////////////////////
#ifndef _FULLSAIL_AI_FUNDAMENTALS_QUEUELIST_TODO_H_
#define _FULLSAIL_AI_FUNDAMENTALS_QUEUELIST_TODO_H_

namespace fullsail_ai { namespace fundamentals {

	
	template <typename T>
	inline QueueList<T>::QueueList()
	{
		front = nullptr;
		back = nullptr;
		
	}
	
	template <typename T>
	inline QueueList<T>::~QueueList()
	{
		removeAll();

	}

	template <typename T>
	 bool QueueList<T>::isEmpty() const
	{
		
		if (front==nullptr && back==nullptr)
			return true;
		else
			return false;
	}
	
	template <typename T>
	 void QueueList<T>::enqueue(T element)
	{
		Node* temp= new Node(element);
		temp->data = element;
		temp->next = nullptr;
		if (isEmpty())
		{
			front = temp;
			back = temp;
			return;
		}
		else
		{
			back->next = temp;

		
		}
		back = temp;
		
	}


	template <typename T>
	T QueueList<T>::getFront() const 
	{
		
		return QueueList<T>::front->data;
	}

	
	template <typename T>
	 void  QueueList<T>::dequeue()
	{
		
		if ( front == nullptr)
			return;
		if (front == back)
		{
			delete front;
			back = nullptr;
		}
		else
		{

			Node* temp = front;
			front = front->next;
			delete temp;

		}
		
	}
	template <typename T>
	 void QueueList<T>::removeAll()
	{
		
		Node* temp =front;
		while (temp)
		{
		
			Node* temp2 = temp;
			temp = temp->next;
			delete temp2;
			//QueueList::Node::destroyedNodeCount++;
		}
		front = nullptr;
		back = nullptr;
	
	}
	
	template <typename T>
	 bool QueueList<T>::contains(T element) const
	{
		Node* temp = front;
		while (temp)
		{
			if (temp->data == element)
				return true;
			temp = temp->next;
		}
		return false;
	}
	///////////////////////
	///////////////////////
	template <typename T>
	 void QueueList<T>::remove(T element)
	{
		
		
			if (contains(element))
			{
				//Node* temp = front;
				if (front == back)
				{
					delete front;
					front = nullptr;
					back = nullptr;
					return;
				}
				if (front->data == element)
				{
					Node* temp = front;
					front = front->next;
					delete temp;
					return;
				}
			}
			Node* curr = front->next;
			Node* prev = front;
			while (curr)
			{
				if (curr->data == element)
				{
					if (curr == back)
					{
						prev = nullptr;
						back = prev;
						delete curr;
						return;
					}
					else
					{
						Node* temp = curr;
						prev->next = curr->next;
						delete temp;
						return;
					}
				}
				prev = curr;
				curr = curr->next;

			}
			
		
	}
	
	template <typename T>
	typename QueueList<T>::Iterator& QueueList<T>::Iterator::operator++()
	{
		// TODO: Complete the definition of this operator.
		if (currentNode == NULL)
			return *this;
		else
		{
			currentNode = currentNode->next;
		}
		return *this;
	}

	template <typename T>
	typename T QueueList<T>::Iterator::operator*() const
	{
		
		return currentNode->data;
	}


}}  

#endif  

