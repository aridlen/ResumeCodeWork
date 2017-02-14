#pragma once
#include"stdafx.h"

using namespace DirectX;
using namespace std;

enum FrustumCorners { FTL = 0, FBL, FBR, FTR, NTL, NTR, NBR, NBL };
enum FrustumPlanes { NEAR_PLANE = 0, FAR_PLANE, LEFT_PLANE, RIGHT_PLANE, TOP_PLANE, BOTTOM_PLANE };
static bool operator==(XMFLOAT3 lhs, XMFLOAT3 rhs)
{
	if ((lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z))
		return true;
	else
		return false;

	return false;
}

struct Plane
{
	XMFLOAT3 normal;
	XMFLOAT4 normal4;
	float offset;
};

struct Frustum
{
	Plane planes[6];
	XMFLOAT3 corners[8];
};

struct Sphere
{
	XMFLOAT3 m_Center;
	float m_Radius;
};
struct Line
{
	XMFLOAT3 m_start;
	XMFLOAT3 m_end;
};
struct Edge
{
	XMFLOAT3 m_start;
	XMFLOAT3 m_end;
	
};
static bool operator==(Line lhs, Line rhs)
{
	if (lhs.m_start == rhs.m_start&&lhs.m_end == rhs.m_end)
		return true;
	else if (lhs.m_start == rhs.m_end&&lhs.m_end == rhs.m_start)
		return true;
	else
		return false;
}
struct Capsule
{
	Line m_segment;
	float radius;
};

struct MeshTriangle
{
	 XMFLOAT3 point1, point2, point3;
	XMFLOAT3 m_center;
	Edge m_edges[3];
};

struct Square
{
	MeshTriangle* m_leftTri;
	MeshTriangle* m_rightTri;
	vector<Square*> adj;
	Line m_top;
	Line m_left;
	Line m_right;
	Line m_bottom;
	XMFLOAT3 center;
	bool walkable;

	void Create(MeshTriangle* lhs, MeshTriangle* rhs)
	{
		m_bottom.m_start = lhs->point3;
		m_bottom.m_end = rhs->point3;

		m_left.m_start = lhs->point1;
		m_left.m_end = lhs->point3;

		m_top.m_start = lhs->point1;
		m_top.m_end = rhs->point2;

		m_right.m_start = lhs->point2;
		m_right.m_end = rhs->point3;

		walkable = true;
		m_leftTri = lhs;
		m_rightTri = rhs;
		//center=m_left.m_start-m_right.m_end;
		center = m_top.m_start;

	}
	void ToggleWalkable() { walkable = !walkable; }

};
struct NavNode
{
	MeshTriangle m_tri;
	unsigned int ID;
	std::vector<NavNode*> m_adj;
	bool walkable;
	bool border;
	unsigned char weight;

	NavNode()
	{

	}
	NavNode(NavNode& rhs)
	{
		m_tri = rhs.m_tri;
		ID = rhs.ID;
		m_adj = rhs.m_adj;
		walkable = rhs.walkable;
		border = rhs.border;
	}
	unsigned char getWeight() const
	{
		return weight;
	}
	NavNode& operator=(const NavNode& rhs)
	{
		m_tri = rhs.m_tri;
		ID = rhs.ID;
		m_adj = rhs.m_adj;
		walkable = rhs.walkable;
		border = rhs.border;
		return *this;
	}
	void Shutdown()
	{
		
	}
};
struct AABB
{
	XMFLOAT3 min;
	XMFLOAT3 max;
};

