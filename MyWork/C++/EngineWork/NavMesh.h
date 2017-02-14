#pragma once
#include"stdafx.h"
#include"CollisionDefines.h"
#include "BaseModel.h"


class NavMesh : public BaseModel
{
private:
	void AddtoNonWalkable(Square* data);
	void RemovefromNonWalkable(Square* data);
	void AddtoWalkabale(Square* data);
	void RemoveFromWalkable(Square* data);
	Square* m_currentSquare;
	vector<int> spawnIndex;
public:
	std::vector<NavNode*> m_ListofNavNodes;
	vector<Square*>m_SquareList;
	vector<Square*>m_borderList;
	vector<Square*>m_walkableList;
	Square* m_current;
	NavMesh(ResourceManager* resources, string fileNav[5]);
	~NavMesh();

	void FindAdjacents(NavNode* lhs, NavNode* rhs);
	//////////////
	void FindNeighbors(Square* lhs, int count);
	void SetBorderList();
	///////////////
	void Initialize(ResourceManager* resources);
	void Update(float dt);
	void Shutdown();
	Square* getCurrPosition(float x, float y, float z);

	
	//ACCESSORS
	
	//MUTATORS
	
	//HELPERS
	void clearNodeList();
	
	void FindCenter(MeshTriangle& tri);
	bool EdgeCompare(const Edge& lhs, const Edge& rhs);
	bool CompareXMFLOAT3(XMFLOAT3 lhs, XMFLOAT3 rhs);
	//unsigned char GetWeight()const { return weight; }
	//////////////////////
	std::vector<NavNode*> GetListNodes() { return m_ListofNavNodes; }
	vector<Square*> GetBorder() { return m_borderList; }
	vector<Square*> GetSquares() { return m_SquareList; }
	vector<Square*> GetWalkableSquares() { return m_walkableList; }
	void SetSquareActive(Square* data);
	void SetSquareDeactive(Square* data);
	void FindCurrentSquare(Entity* obj);
	XMFLOAT3 SpawnLocation();
};

