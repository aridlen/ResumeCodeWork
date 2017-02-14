#pragma once
template<typename List>
class DList
{
private:
	struct Node
	{
		Node *prev, *next;
		List data;
		Node(List& _data, Node* _prev,Node* _next) : data(_data), prev(_prev), next(_next)
		{}

	};
	Node *first, *last;
	int count;
public:
	DList(){ count = 0; first = last = nullptr; };
	~DList();
	
	void push_front(List _data);
	int size()const { return count; }
	void push_back(List _data);

	List& operator[](int _index);
	List const& operator[](int _index)const;
	void Clear();
	bool erase(int _index);
	

};

template<typename List>
DList<List>::~DList()
{
	Node* temp = first;
	while (first)
	{
		first = first->next;
		delete temp;
		temp = first;
	}

}
template<typename List>
void DList<List>::push_front(List _data)
{
	Node* temp = new Node(_data, NULL,first);
	if (!last)
	{
		last = temp;
	}
	if (first != NULL)
	{
		
		first->prev = temp;
	}
	first = temp;
	++count;
}
template<typename List>
void DList<List>::push_back(List _data)
{
	Node* temp = new Node(_data, last,NULL);
	if (!first)
	{
		first = temp;
	}
	else
	{
		last->next = temp;
	}
	last = temp;
	++count;
}
template<typename List>
List& DList<List>::operator[](int _index)
{
	Node* temp = first;
	for (int i = 0; i < _index; ++i)
	{
		temp = temp->next;
	}
	return temp->data;
}

template<typename List>
void DList<List>::Clear()
{
	
	Node* temp = first;
	while (first)
	{
		first = first->next;
		delete temp;
		temp = first;
	}
	count = 0;
	first = last = nullptr;
}
template<typename List>
bool DList<List>::erase(int _index)
{
	Node* temp = first;
	//First check for your count and index against each other
	
	if (count <= 0 || count  <= _index || _index < 0)
	{
		return false;
	}
	else
	{
		for (int i = _index; i > 0; i--)
		{
			temp = temp->next;
		}
		if (temp != last&& temp != first)
		{
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete temp;
			--count;
			return true;
		}
		
		//Delete temp but adjust count
		if (temp == first)
		{
			first = first->next;
			if (first != NULL)
			{
				first->prev = NULL;
			}
			delete temp;
			--count;
			return true;


		}
		if (temp == last)
		{
			last = last->prev;
			if (last != NULL)
			{
				last->next = NULL;
			}
			delete temp;
			--count;
			return true;
		}
		
		// Check temp is first,is count null,temp is last,and if temp is first or last

		if (count == NULL)
		{
			last = first = NULL;
			delete temp;
			count = 0;
			return true;
		}
	}
	return true;
}
template<typename List>
List const&DList<List>:: operator[](int _index)const
{
	Node* temp = first;
	for (int i = 0; i < _index; ++i)
	{
		temp = temp->next;
	}
	return temp->data;

}