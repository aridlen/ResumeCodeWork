#include "PathSearch.h"
#include<iostream>
#include<WinBase.h>

namespace fullsail_ai { namespace algorithms {

	
#if GS
	bool isGreater(PlannerNode* const &lhs, PlannerNode* const &rhs)
	{

		return(lhs->heuristicCost > rhs->heuristicCost);
}
	PathSearch::PathSearch() :m_openList(isGreater)
	{
		m_done = false;
	}
#endif
#if UCS
	bool isGreater(PlannerNode* const &lhs, PlannerNode* const &rhs)
	{

		return(lhs->givenCost> rhs->givenCost);
	}
	PathSearch::PathSearch() : m_openList(isGreater)
	{
		m_done = false;
	}
#endif
#if ASTAR
	bool isGreater(PlannerNode* const &lhs, PlannerNode* const &rhs)
	{

		return(lhs->finalCost > rhs->finalCost);
}
	PathSearch::PathSearch() : m_openList(isGreater)
	{

		m_done = false;
	}
#endif
	PathSearch::~PathSearch()
	{
	}
	void PathSearch::areAdjacent(TileMap* map, SearchNode* node, unsigned int i, unsigned int j)
	{
		if (i % 2 == 0)
		{
			//Make sure it doesnt use black tiles taht have a weight of 0
			//i-1; j-1
			if (map->getTile(i - 1, j - 1) && map->getTile(i - 1, j - 1)->getWeight() != 0)
				node->neighbors.push_back(map->getTile(i - 1, j-1));
			//i+1; j-1
			if (map->getTile(i + 1, j - 1) && map->getTile(i + 1, j - 1)->getWeight() != 0)
				node->neighbors.push_back(map->getTile(i + 1, j - 1));
			//i-1; j
			if (map->getTile(i - 1, j) && map->getTile(i - 1, j)->getWeight() != 0)
				node->neighbors.push_back(map->getTile(i - 1, j ));
			//i; j-1
			if (map->getTile(i, j - 1) && map->getTile(i, j - 1)->getWeight() != 0)
				node->neighbors.push_back(map->getTile(i, j - 1));
			//i; j+1
			if (map->getTile(i, j + 1) && map->getTile(i, j + 1)->getWeight() != 0)
				node->neighbors.push_back(map->getTile(i, j + 1));
			//i+1; j
			if (map->getTile(i + 1, j ) && map->getTile(i + 1, j)->getWeight() != 0)
				node->neighbors.push_back(map->getTile(i + 1, j));

		}
		else
		{
		
			//i+1; j
			if (map->getTile(i + 1, j) && map->getTile(i + 1, j)->getWeight() != 0)
				node->neighbors.push_back(map->getTile(i + 1, j));
			//i-1; j+1
			if (map->getTile(i - 1, j + 1) && map->getTile(i - 1, j + 1)->getWeight() != 0)
				node->neighbors.push_back(map->getTile(i - 1, j + 1));
			//i; j-1
			if (map->getTile(i , j - 1) && map->getTile(i , j - 1)->getWeight() != 0)
				node->neighbors.push_back(map->getTile(i , j - 1));
			//i+1; j+1
			if (map->getTile(i + 1, j + 1) && map->getTile(i + 1, j + 1)->getWeight() != 0)
				node->neighbors.push_back(map->getTile(i + 1, j + 1));
			//i; j+1
			if (map->getTile(i , j + 1) && map->getTile(i , j + 1)->getWeight() != 0)
				node->neighbors.push_back(map->getTile(i , j + 1));
			//i-1; j
			if (map->getTile(i - 1, j) && map->getTile(i - 1, j)->getWeight() != 0)
				node->neighbors.push_back(map->getTile(i - 1, j));
		}
	}
	void PathSearch::initialize(TileMap* _tileMap)
	{
		   /* •	Create a SearchNode for each valid tile in the tile map.
			•	Create edges to connect each pair of adjacent tiles.
			•	Add all created node to an index(such as a map) that be easily accessed to find the nodes by tile and allows for easy clean up later.
*/
		m_Map = _tileMap;
		
		for (size_t i = 0; i < _tileMap->getRowCount(); i++)
		{
			for (size_t j = 0; j < _tileMap->getColumnCount(); j++)
			{
				if (_tileMap->getTile(i, j))
				{
				if (_tileMap->getTile(i, j)->getWeight() == 0)
					continue;
				
					SearchNode* temp = new SearchNode();
					temp->data = _tileMap->getTile(i, j);
					//temp->visited = false;
					//if(areAdjacent())
					areAdjacent(_tileMap, temp, i, j);
					
					m_MySearchGraph[_tileMap->getTile(i, j)] = temp;
				}
			}
		}
		//if(areAdjacent())
		//id have to loop again here twice through the searchgraph and set values again
		
	}


	void PathSearch::enter(int startRow, int startColumn, int goalRow, int goalColumn)
	{
		/*•	Find the SearchNode that represents the starting tile.
		  •	Set the goal tile(or node) so that you know when to stop the algorithm.• Add the starting node to the open queue and mark it as visited.
*/
		
		
		Tile* s = m_Map->getTile(startRow, startColumn);
			Tile*g = m_Map->getTile(goalRow, goalColumn);
		start = m_MySearchGraph[s];
		goal = m_MySearchGraph[g];
		PlannerNode* temp = new PlannerNode();
			temp->vertex=start;
			temp->parent = nullptr;
			temp->givenCost = 0.0f;
		//distance formula
		float x = g->getXCoordinate() - s->getXCoordinate();
		x *= x;
		float y= g->getYCoordinate() - s->getYCoordinate();
		y *= y;
		temp->heuristicCost = sqrtf(x + y);
		temp->finalCost = temp->heuristicCost*m_heuristicWeight;
		temp->visited = true;
		visited[start->data] = temp;
		//next = temp;
		m_openList.push(temp);
		m_done = false;

	}

	void PathSearch::update(long timeslice)
	{
		/*•	While the open list contains planner nodes...
			1.	Dequeue what will become the current node.
			2.	Once you find the goal, build the solution list and exit.
			3.	Determine the successor nodes.Make sure that you go through only those nodes whose tiles are adjacent to that of the current node.
			■ If a node has not been visited—this check is called a dupe check—add it to the open queue and mark it as visited.
			■ Don't forget the rule regarding impassable tiles. */
		//GreedySearch(start, goal);
		DWORD startTime=GetTickCount();
		DWORD elaspedTime;
		
		while (true)
		{
		
			//timeslice--;
			elaspedTime = GetTickCount();
			elaspedTime -= startTime;
			//m_openList.push(visited[start->data]);
#if GS
			if (GreedySearch(start, goal))
				return;
#endif
#if UCS
			if (UniformSearch(start, goal))
				return;
#endif
#if ASTAR
			if (AstarSearch(start, goal))
				return;
#endif
			if(timeslice < elaspedTime || timeslice<=0)
				return;
		}
	}

	void PathSearch::exit()
	{
		while (!m_openList.empty())
		{
			m_openList.pop();
		}
		m_solutionList.clear();
		for (auto i = visited.begin(); i != visited.end(); ++i)
		{
			delete i->second;
		}
		visited.clear();

	}

	void PathSearch::shutdown()
	{
		for (auto i = m_MySearchGraph.begin(); i != m_MySearchGraph.end();++i )
		{
			delete i->second;
			
		}
		m_MySearchGraph.clear();
		for (auto i = visited.begin(); i != visited.end();++i )
		{
			delete i->second;
		 
		}
		visited.clear();
		m_done = false;
		/*while (!m_openList.empty())
		{
			m_openList.pop();
		}*/
		
		m_solutionList.clear();
		
		//m_openList.clear();
		//m_Map->reset();
	}

	bool PathSearch::isDone() const
	{
		return m_done;
	}

	std::vector<Tile const*> const PathSearch::getSolution() const
	{
		
		return m_solutionList;
	}
	bool PathSearch::GreedySearch(SearchNode* start, SearchNode* goal)
	{
		
		
			PlannerNode* curr = m_openList.front();
			m_openList.pop();
			
			if (curr->vertex == goal)
			{
				PlannerNode* currSolution = curr;
				while (currSolution->vertex != start)
				{
					m_solutionList.push_back(currSolution->vertex->data);
					currSolution = currSolution->parent;
				}
				m_solutionList.push_back(currSolution->vertex->data);
				//visited[curr->vertex] = goal;
				m_done = true;
				return true;
			}
			for (size_t i = 0; i < curr->vertex->neighbors.size(); i++)
			{
				if (curr->vertex->neighbors[i]->getWeight() == 0)
					continue;
				//successor->data=curr->vertex->neighbors[i];
				if (visited[curr->vertex->neighbors[i]] == NULL)
				{
					SearchNode* successor = m_MySearchGraph[curr->vertex->neighbors[i]];
					PlannerNode* successorNode = new PlannerNode();
					successorNode->vertex = successor;
					successorNode->parent = curr;
					successorNode->heuristicCost = estimateHeuristicCost(successor, goal);
					visited[curr->vertex->neighbors[i]] = successorNode;
					m_openList.push(successorNode);

				}
			}

			return false;
	}
	bool PathSearch::UniformSearch(SearchNode* start, SearchNode* goal)
	{
		
			PlannerNode* curr = m_openList.front();
			m_openList.pop();
		
			if (curr->vertex == goal)
			{
				PlannerNode* currSolution = curr;
				while (currSolution->vertex != start)
				{
					m_solutionList.push_back(currSolution->vertex->data);
					currSolution = currSolution->parent;
				}
				m_solutionList.push_back(currSolution->vertex->data);
				//visited[curr->vertex] = goal;
				
				m_done = true;
				return true;
			}
			for (size_t i = 0; i < curr->vertex->neighbors.size(); i++)
			{
				SearchNode* successor = m_MySearchGraph[curr->vertex->neighbors[i]];
				PlannerNode* successorNode = new PlannerNode();
				successorNode->givenCost = 0;
				if (curr->vertex->neighbors[i]->getWeight() == 0)
					continue;
				float tempGivenCost = curr->givenCost + estimateHeuristicCost(curr->vertex, successor)*successor->data->getWeight();
				if (visited[curr->vertex->neighbors[i]] != NULL)
				{

					if (tempGivenCost < visited[curr->vertex->neighbors[i]]->givenCost)
					{
						successorNode = visited[curr->vertex->neighbors[i]];
						m_openList.remove(successorNode);
						successorNode->givenCost = tempGivenCost;
						successorNode->parent = curr;
						//std::cout << "GivenCost-Not Null: " << successorNode->givenCost << std::endl;
						m_openList.push(successorNode);
					}
				}
				else
				{

					successorNode->vertex = successor;
					successorNode->parent = curr;
					//successorNode->heuristicCost = estimateHeuristicCost(successor, goal);
					successorNode->givenCost = tempGivenCost;
					visited[curr->vertex->neighbors[i]] = successorNode;

					m_openList.push(successorNode);

				}

			}
			return false;
	}
	bool PathSearch::AstarSearch(SearchNode* start, SearchNode* goal)
	{
		
			PlannerNode* curr = m_openList.front();
			m_openList.pop();
			
			if (curr->vertex == goal)
			{
				PlannerNode* currSolution = curr;
				while (currSolution->vertex != start)
				{
					m_solutionList.push_back(currSolution->vertex->data);
					currSolution = currSolution->parent;
				}
				m_solutionList.push_back(currSolution->vertex->data);
				

				m_done = true;
				return true;
			}
			for (size_t i = 0; i < curr->vertex->neighbors.size(); i++)
			{
				SearchNode* successor = m_MySearchGraph[curr->vertex->neighbors[i]];
				
				PlannerNode* successorNode;
				
				if (curr->vertex->neighbors[i]->getWeight() == 0)
					continue;
				float tempGivenCost = curr->givenCost + estimateHeuristicCost(curr->vertex, successor)*successor->data->getWeight();
				if (visited[curr->vertex->neighbors[i]] != NULL)
				{
					
					successorNode = visited[curr->vertex->neighbors[i]];
				

					if (tempGivenCost < visited[curr->vertex->neighbors[i]]->givenCost)
					{

						m_openList.remove(successorNode);
						successorNode->givenCost = tempGivenCost;
						successorNode->finalCost = successorNode->givenCost + successorNode->heuristicCost*m_heuristicWeight;
						successorNode->parent = curr;

						
						m_openList.push(successorNode);
					}
				}
				else
				{
					successorNode = new PlannerNode();
					successorNode->vertex = successor;

					successorNode->heuristicCost = estimateHeuristicCost(successor, goal);
					successorNode->givenCost = tempGivenCost;
					successorNode->finalCost = successorNode->givenCost + successorNode->heuristicCost*m_heuristicWeight;
					successorNode->parent = curr;

					visited[curr->vertex->neighbors[i]] = successorNode;

					m_openList.push(successorNode);

				}

			}
		
		
			return false;
	}
	float PathSearch::estimateHeuristicCost(SearchNode* lhs, SearchNode* rhs)
	{
		float x = rhs->data->getXCoordinate() - lhs->data->getXCoordinate();
		x *= x;
		float y = rhs->data->getYCoordinate() - lhs->data->getYCoordinate();
		y *= y;
		return sqrtf(x + y);
	}
}}  

