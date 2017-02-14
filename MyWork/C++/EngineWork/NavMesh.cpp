#include "stdafx.h"
#include "NavMesh.h"


NavMesh::NavMesh(ResourceManager* resources, string fileNav[5]) : BaseModel(fileNav,resources) 
{
	
	//BaseModel::SetScale(10.0f);
	Initialize(resources);
	
}


NavMesh::~NavMesh()
{
	Shutdown();
}

void NavMesh::Initialize(ResourceManager* resources)
{
	//1) Load from fbx
	//m_mesh=new BaseModel(fileNav.c_str(),resources);
	//m_ListofNavNodes.resize(GetVertexes().size());
	int count = 0;
	for (size_t i = 0; i < GetIndices().size(); i+=3)
	{
		NavNode* temp=new NavNode();
		
		temp->m_tri.point1.x = GetVertexes()[GetIndices()[i]].XYZW.x;
		temp->m_tri.point1.y = GetVertexes()[GetIndices()[i]].XYZW.y;
		temp->m_tri.point1.z = GetVertexes()[GetIndices()[i]].XYZW.z;
				   
		//temp->m_t..point2 = GetVertexes()[GetIndices()[i+1]].XYZW;
		temp->m_tri.point2.x = GetVertexes()[GetIndices()[i+1]].XYZW.x;
		temp->m_tri.point2.y = GetVertexes()[GetIndices()[i+1]].XYZW.y;
		temp->m_tri.point2.z = GetVertexes()[GetIndices()[i+1]].XYZW.z;
				   
		//temp->m_t..point3 = GetVertexes()[GetIndices()[i+2]].XYZW;
		temp->m_tri.point3.x = GetVertexes()[GetIndices()[i + 2]].XYZW.x;
		temp->m_tri.point3.y = GetVertexes()[GetIndices()[i + 2]].XYZW.y;
		temp->m_tri.point3.z = GetVertexes()[GetIndices()[i + 2]].XYZW.z;
				   
		temp->m_tri.m_edges[0].m_start = temp->m_tri.point1;
		temp->m_tri.m_edges[0].m_end = temp->m_tri.point2;
		temp->m_tri.m_edges[1].m_start = temp->m_tri.point1;
		temp->m_tri.m_edges[1].m_end = temp->m_tri.point3;
		temp->m_tri.m_edges[2].m_start = temp->m_tri.point2;
		temp->m_tri.m_edges[2].m_end = temp->m_tri.point3;
		FindCenter(temp->m_tri);
		m_ListofNavNodes.push_back(temp);
		//count++;
	}
	
	if (!m_ListofNavNodes.empty())
	{
		for (size_t i = 0; i < m_ListofNavNodes.size(); i += 2)
		{

			Square* temp = new Square();

			temp->Create(&m_ListofNavNodes[i]->m_tri, &m_ListofNavNodes[i + 1]->m_tri);
			m_SquareList.push_back(temp);
		}

	}
	for (size_t i = 0; i < m_SquareList.size(); i++)
	{
		FindNeighbors(m_SquareList[i], 0);
	}

	SetBorderList();
	//unsigned int k = rand() % (m_ListofNavNodes.size()-1);
	m_current = m_walkableList[0];
}
void NavMesh::Update(float dt)
{
	BaseModel::Update(dt);
}
void NavMesh::Shutdown()
{
	clearNodeList();
	BaseModel::Shutdown();
	
}
void NavMesh::SetBorderList()
{
	for (size_t i = 0; i < m_SquareList.size(); i++)
	{
		if (m_SquareList[i]->adj.size() != 4)
		{
			m_SquareList[i]->ToggleWalkable();
			m_borderList.push_back(m_SquareList[i]);
			continue;

		}
		m_walkableList.push_back(m_SquareList[i]);
	}
}
void NavMesh::FindAdjacents(NavNode* lhs,NavNode* rhs)
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if (EdgeCompare(lhs->m_tri.m_edges[i],rhs->m_tri.m_edges[j]))
			{
				lhs->m_adj.push_back(rhs);
			}
		}
	}
}
void NavMesh::FindNeighbors(Square* lhs, int count)
{

	for (size_t i = 0; i < m_SquareList.size(); i++)
	{
		if (lhs->m_left == m_SquareList[i]->m_right)
			lhs->adj.push_back(m_SquareList[i]);
		else if (lhs->m_right == m_SquareList[i]->m_left)
			lhs->adj.push_back(m_SquareList[i]);
		else if (lhs->m_top == m_SquareList[i]->m_bottom)
			lhs->adj.push_back(m_SquareList[i]);
		else if (lhs->m_bottom == m_SquareList[i]->m_top)
			lhs->adj.push_back(m_SquareList[i]);

	}


}
void NavMesh::clearNodeList()
{
	for (size_t i = 0; i < m_ListofNavNodes.size(); i++)
	{
		delete m_ListofNavNodes[i];
	}
	m_ListofNavNodes.clear();
	for (size_t j = 0; j < m_SquareList.size(); j++)
	{
		delete m_SquareList[j];
	}
	m_SquareList.clear();
}

void NavMesh::FindCenter(MeshTriangle& tri)
{
	tri.m_center.x = (tri.point1.x + tri.point2.x + tri.point3.x) / 3;
	tri.m_center.y = (tri.point1.y + tri.point2.y + tri.point3.y) / 3;
	tri.m_center.z = (tri.point1.z + tri.point2.z + tri.point3.z) / 3;
	
}

bool NavMesh::EdgeCompare(const Edge& lhs, const Edge& rhs)
{
	
	if (CompareXMFLOAT3(lhs.m_start, rhs.m_start) && (CompareXMFLOAT3(lhs.m_end, rhs.m_end)))
		return true;
	else if (CompareXMFLOAT3(lhs.m_start, rhs.m_end) && (CompareXMFLOAT3(lhs.m_end, rhs.m_start)))
		return true;
	else if (CompareXMFLOAT3(lhs.m_end, rhs.m_start) && (CompareXMFLOAT3(lhs.m_start, rhs.m_end)))
		return true;
	else
		return false;
}

bool NavMesh::CompareXMFLOAT3(XMFLOAT3 lhs, XMFLOAT3 rhs)
{
	if ((lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z))
		return true;
	else
		return false;
}

Square* NavMesh::getCurrPosition(float x, float y, float z)
{
	Square* ptr = nullptr;
	Line ray;
	ray.m_start = XMFLOAT3(x, y + 100, z);
	ray.m_end = XMFLOAT3(x, y - 100, z);
	for (size_t i = 0; i < m_walkableList.size(); i++)
	{
		if (IntersectLineTriangle(ray, m_walkableList[i]->m_leftTri))
		{
			ptr = m_walkableList[i];
			return ptr;
		}
		else if (IntersectLineTriangle(ray, m_walkableList[i]->m_rightTri))
		{
			ptr = m_walkableList[i];
			return ptr;
		}
		
	}
	return ptr;
}

void NavMesh::AddtoNonWalkable(Square* data)
{
	m_borderList.push_back(data);
}
void NavMesh::RemovefromNonWalkable(Square* data)
{
	Square* temp = data;

	m_borderList.erase(remove(m_borderList.begin(), m_borderList.end(), temp), m_borderList.end());
	delete temp;
}
void NavMesh::AddtoWalkabale(Square* data)
{
	m_walkableList.push_back(data);
}
void NavMesh::RemoveFromWalkable(Square* data)
{
	Square* temp = data;

	m_walkableList.erase(remove(m_walkableList.begin(), m_walkableList.end(), temp), m_walkableList.end());
	delete temp;
}
void NavMesh::SetSquareActive(Square* data)
{
	AddtoWalkabale(data);
	RemovefromNonWalkable(data);
}
void NavMesh::SetSquareDeactive(Square* data)
{
	AddtoNonWalkable(data);
	RemoveFromWalkable(data);
}
XMFLOAT3 NavMesh::SpawnLocation()
{
	int k = rand() % (m_walkableList.size());
	spawnIndex.push_back(k);
	for (size_t i = 0; i < spawnIndex.size(); i++)
	{
		if (spawnIndex[i] <= k-1&&spawnIndex[i] >= k + 1)
		{
			k = rand() % (m_walkableList.size());
			i = 0;
		}
	}
	
	m_currentSquare = m_walkableList[k];
	return m_walkableList[k]->m_rightTri->m_center;

}
void NavMesh::FindCurrentSquare(Entity* obj)
{
	Line ray;
	ray.m_start = XMFLOAT3(obj->getTransform().Translate._41, obj->getTransform().Translate._42, obj->getTransform().Translate._43);
	ray.m_end = XMFLOAT3(0, -20, 0);
	for (size_t i = 0; i < m_walkableList.size(); i++)
	{
		if (IntersectLineTriangle(ray, m_walkableList[i]->m_leftTri) || IntersectLineTriangle(ray, m_walkableList[i]->m_rightTri))
			m_currentSquare = m_walkableList[i];
	}

}