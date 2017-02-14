
#include <stack>
#include "Behavior.h"
#include "..//QueueList/QueueList.h"
namespace fullsail_ai { namespace fundamentals {

	// DO NOT Edit or Use these two variables for any reason, it is for memory leak check purposes only.
	unsigned Behavior::createdCount = 0;
	unsigned Behavior::destroyedCount = 0;
	size_t  Behavior::getChildCount() const
	{
		return children.size();
	}
	Behavior*  Behavior::getChild(size_t index)
	{
		return children[index];
	 }
	Behavior const*  Behavior::getChild(size_t index) const
	{
		return children[index];
	 }
	void  Behavior::addChild(Behavior* child)
	{
		children.push_back(child);
	}
	unsigned Behavior::getCreatedCount()
	{
		return createdCount;
	}

	unsigned Behavior::getDestroyedCount()
	{
		return destroyedCount;
	}

	Behavior::Behavior(char const* _description)
	{
		description = _description;
	}

	char const* Behavior::toString() const
	{
		return description;
	}

	// DO NOT edit this function, it is supposed to just return false
	bool Behavior::isLeaf() const
	{
		return false;
	}

	
	void Behavior::breadthFirstTraverse(void(*dataFunction)(Behavior const*)) const
	{
		QueueList<Behavior const*> list;
		list.enqueue(this);
		while (!list.isEmpty())
		{
			Behavior const* temp = list.getFront();
			dataFunction(temp);
			list.remove(temp);
			for (size_t i = 0; i < temp->children.size(); i++)
			{
				list.enqueue(temp->children[i]);
			}
			
		}
	}
	void Behavior::preOrderTraverse(void(*dataFunction)(Behavior const*)) const
	{
		preOrderHelp(dataFunction, this);
	
		
	}
	void Behavior::postOrderTraverse(void(*dataFunction)(Behavior const*)) const
	{
		postOrderHelp(dataFunction, this);
	
	}
	/////////////HELPER FUNCTIONS////////////////
	void Behavior::postOrderHelp(void(*dataFunction)(Behavior const*),Behavior const* node) const
	{
		
*/
		
		for (size_t i = 0; i < node->getChildCount(); i++)
		{
			postOrderHelp(dataFunction, node->children[i]);
		}
		dataFunction(node);

	}
	void Behavior::preOrderHelp(void(*dataFunction)(Behavior const*),Behavior const* node) const
	{
		

		dataFunction(node);
		for (size_t i = 0; i < node->getChildCount(); i++)
		{
			preOrderHelp(dataFunction, node->children[i]);
		}
		
	}
}}  
