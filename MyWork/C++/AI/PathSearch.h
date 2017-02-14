
#ifndef _FULLSAIL_AI_PATH_PLANNER_PATH_SEARCH_H_
#define _FULLSAIL_AI_PATH_PLANNER_PATH_SEARCH_H_

// change this to start the program on whatever default map as you like from the table below
#define USEDEFAULTMAP hex035x035

#define hex006x006 "./Data/hex006x006.txt"
#define hex014x006 "./Data/hex014x006.txt"
#define hex035x035 "./Data/hex035x035.txt"
#define hex054x045 "./Data/hex054x045.txt"
#define hex098x098 "./Data/hex098x098.txt"
#define hex113x083 "./Data/hex113x083.txt"

// change this to 1(true), and change the data below when you want to test specific starting and goal locations on startup
#define OVERRIDE_DEFAULT_STARTING_DATA 0

// Make sure your start and goal are valid locations!
#define DEFAULT_START_ROW 0
#define DEFAULT_START_COL 0
#define DEFAULT_GOAL_ROW ?
#define DEFAULT_GOAL_COL ?

#define GS 0
#define UCS 0
#define ASTAR 1
#include "../TileSystem/Tile.h"
#include "../TileSystem/TileMap.h"
#include "../platform.h"
#include <vector>
#include <map>
#include<unordered_map>
#include "../PriorityQueue.h"
#include<queue>
namespace fullsail_ai { namespace algorithms {

	struct SearchNode
	{
		Tile* data;
		std::vector<Tile*> neighbors;

	};
	struct PlannerNode
	{
		SearchNode* vertex;
		PlannerNode* parent;
		float heuristicCost;
		float givenCost;
		float finalCost;
		bool visited;
	};
	class PathSearch
	{
	public:
		
		
		TileMap* m_Map;
		std::unordered_map<Tile*, SearchNode*> m_MySearchGraph;
		PriorityQueue<PlannerNode*> m_openList;
		
		std::vector<Tile const*> m_solutionList;
		std::unordered_map<Tile*, PlannerNode*> visited;
		SearchNode* start;
		SearchNode* goal;
	
		
		bool m_done;
		// run the algorithm with a heuristic weight of 2. 
		float m_heuristicWeight = 1.2f;
		//! \brief Default constructor.
		DLLEXPORT PathSearch();

		//! \brief Destructor.
		DLLEXPORT ~PathSearch();

		//! \brief Sets the tile map.
		//!
		//! Invoked when the user opens a tile map file.
		//!
		//! \param   _tileMap  the data structure that this algorithm will use
		//!                    to access each tile's location and weight data.
		DLLEXPORT void initialize(TileMap* _tileMap);

		//! \brief Enters and performs the first part of the algorithm.
		//!
		//! Invoked when the user presses one of the play buttons.
		//!
		//! \param   startRow         the row where the start tile is located.
		//! \param   startColumn      the column where the start tile is located.
		//! \param   goalRow          the row where the goal tile is located.
		//! \param   goalColumn       the column where the goal tile is located.
		DLLEXPORT void enter(int startRow, int startColumn, int goalRow, int goalColumn);

		//! \brief Returns <code>true</code> if and only if no nodes are left open.
		//!
		//! \return  <code>true</code> if no nodes are left open, <code>false</code> otherwise.
		DLLEXPORT bool isDone() const;

		//! \brief Performs the main part of the algorithm until the specified time has elapsed or
		//! no nodes are left open.
		DLLEXPORT void update(long timeslice);

		//! \brief Returns an unmodifiable view of the solution path found by this algorithm.
		DLLEXPORT std::vector<Tile const*> const getSolution() const;

		//! \brief Resets the algorithm.
		DLLEXPORT void exit();

		//! \brief Uninitializes the algorithm before the tile map is unloaded.
		DLLEXPORT void shutdown();
		//////MY FUNCTIONS////////////
		DLLEXPORT void areAdjacent(TileMap* map, SearchNode* node,unsigned int i,unsigned int j);
		DLLEXPORT bool GreedySearch(SearchNode* start, SearchNode* goal);
		DLLEXPORT bool UniformSearch(SearchNode* start, SearchNode* goal);
		DLLEXPORT bool AstarSearch(SearchNode* start, SearchNode* goal);
		DLLEXPORT float estimateHeuristicCost(SearchNode* lhs, SearchNode* rhs);
	};
}}  

#endif

