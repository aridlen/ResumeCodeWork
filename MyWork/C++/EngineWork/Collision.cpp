#include "stdafx.h"
#include "Collision.h"

#define SMALL_NUM   0.00000001 // anything that avoids division overflow
// dot product (3D) which allows vector operations in arguments
#define dot(u,v)   ((u).x * (v).x + (u).y * (v).y + (u).z * (v).z)
#define dot1(u,v)   ((u).x * (v).x + (u).y * (v).y + (u).z * (v).z + (u).w * (v).w)
float ScalarTriple(XMFLOAT3 _u, XMFLOAT3 _v, XMFLOAT3 _w)
{
	float Result = 0.0f;

	float i, j, k;

	i = _u.x * ((_v.y * _w.z) - (_w.y * _v.z));
	j = _u.y * ((_v.x * _w.z) - (_w.x * _v.z));
	k = _u.z * ((_v.x * _w.y) - (_w.x * _v.y));

	return Result = i - j + k;
}

void cross_product(XMFLOAT3 &vectorO, const XMFLOAT3 &vectorA, const XMFLOAT3 &vectorB)
{
	vectorO.x = vectorA.y*vectorB.z - vectorA.z*vectorB.y;
	vectorO.y = vectorA.z*vectorB.x - vectorA.x*vectorB.z;
	vectorO.z = vectorA.x*vectorB.y - vectorA.y*vectorB.x;
}
bool SphereToAABB(const Sphere*  lhs, const vector<AABB>& rhs,int numSpheres)
{
	int check = 0;
	for (int i = 0; i < numSpheres; i++)
	{

		for (size_t j = 0; j < rhs.size(); j++)
		{

			XMFLOAT3 x;
			x.x = max(rhs[j].min.x, min(lhs[i].m_Center.x, rhs[j].max.x));
			x.y = max(rhs[j].min.y, min(lhs[i].m_Center.y, rhs[j].max.y));
			x.z = max(rhs[j].min.z, min(lhs[i].m_Center.z, rhs[j].max.z));

			float d = sqrtf((x.x - lhs[i].m_Center.x)*(x.x - lhs[i].m_Center.x) +
				(x.y - lhs[i].m_Center.y)*(x.y - lhs[i].m_Center.y) +
				(x.z - lhs[i].m_Center.z)*(x.z - lhs[i].m_Center.z));
			if (d < lhs[i].m_Radius)
				check += 1;
		}
	}
	if (check != 0)
		return true;
	else
		return false;
}
bool SphereToSphere(const Sphere& lhs, const Sphere& rhs)
{
	float distanceSquared = pow((rhs.m_Center.x - lhs.m_Center.x), 2) + pow((rhs.m_Center.y - lhs.m_Center.y), 2) + pow((rhs.m_Center.z - lhs.m_Center.z), 2);
	float radiusSquared = pow(lhs.m_Radius + rhs.m_Radius, 2);

	if (distanceSquared < radiusSquared)
		return true;
	else
		return false;

}

bool CapsuleToCapsule(const Capsule& lhs, const Capsule& rhs, float& penetration)
{
	float startDistanceSquared = pow((rhs.m_segment.m_start.x - lhs.m_segment.m_start.x), 2) + pow((rhs.m_segment.m_start.y - lhs.m_segment.m_start.y), 2) + pow((rhs.m_segment.m_start.z - lhs.m_segment.m_start.z), 2);
	float startRadiusSquared = pow(rhs.radius + lhs.radius, 2);

	float endDistanceSquared = pow((rhs.m_segment.m_end.x - lhs.m_segment.m_end.x), 2) + pow((rhs.m_segment.m_end.y - lhs.m_segment.m_end.y), 2) + pow((rhs.m_segment.m_end.z - lhs.m_segment.m_end.z), 2);
	float endRadiusSquared = pow(rhs.radius + lhs.radius, 2);

	float distance = sqrt(startDistanceSquared);
	float radii = sqrt(startRadiusSquared);
	penetration = radii - distance;

	if (startDistanceSquared < startRadiusSquared || endDistanceSquared < endRadiusSquared)
		return true;
	else
		return false;
}

bool SphereToCapsule(const Sphere& lhs, const Capsule& rhs)
{
	float startDistanceSquared = pow((rhs.m_segment.m_start.x - lhs.m_Center.x), 2) + pow((rhs.m_segment.m_start.y - lhs.m_Center.y), 2) + pow((rhs.m_segment.m_start.z - lhs.m_Center.z), 2);
	float startRadiusSquared = pow(rhs.radius + lhs.m_Radius, 2);

	float endDistanceSquared = pow((rhs.m_segment.m_end.x - lhs.m_Center.x), 2) + pow((rhs.m_segment.m_end.y - lhs.m_Center.y), 2) + pow((rhs.m_segment.m_end.z - lhs.m_Center.z), 2);
	float endRadiusSquared = pow(rhs.radius + lhs.m_Radius, 2);

	if (startDistanceSquared < startRadiusSquared || endDistanceSquared < endRadiusSquared)
		return true;
	else
		return false;
}

bool CapsuleToAABB(const Capsule& lhs, const AABB& rhs)
{
	//XMFLOAT3 closestPoint;
	//if (lhs.m_segment.m_end.x < rhs.min.x)
	//{
	//	closestPoint.x = rhs.min.x;
	//}
	//else if (lhs.m_segment.m_end.x > rhs.max.x)
	//{
	//	closestPoint.x = rhs.max.x;
	//}
	//else
	//{
	//	closestPoint.x = lhs.m_segment.m_end.x;
	//}

	//if (lhs.m_segment.m_end.y < rhs.min.y)
	//{
	//	closestPoint.y = rhs.min.y;
	//}
	//else if (lhs.m_segment.m_end.y > rhs.max.y)
	//{
	//	closestPoint.y = rhs.max.y;
	//}
	//else
	//{
	//	closestPoint.y = lhs.m_segment.m_end.y;
	//}

	//if (lhs.m_segment.m_end.z < rhs.min.z)
	//{
	//	closestPoint.z = rhs.min.z;
	//}
	//else if (lhs.m_segment.m_end.z > rhs.max.z)
	//{
	//	closestPoint.z = rhs.max.z;
	//}
	//else
	//{
	//	closestPoint.z = lhs.m_segment.m_end.z;
	//}

	//float distanceSquared = pow((closestPoint.x - lhs.m_segment.m_end.x), 2) + pow((closestPoint.y - lhs.m_segment.m_end.y), 2) + pow((closestPoint.z - lhs.m_segment.m_end.z), 2);
	//float rSquared = pow(lhs.radius, 2);

	//if (distanceSquared < rSquared)
	//{
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}

	XMFLOAT3 closestPointStart, closestPointEnd;
	if (lhs.m_segment.m_start.x < rhs.min.x)
	{
		closestPointStart.x = rhs.min.x;
	}
	else if (lhs.m_segment.m_start.x > rhs.max.x)
	{
		closestPointStart.x = rhs.max.x;
	}
	else
	{
		closestPointStart.x = lhs.m_segment.m_start.x;
	}



	if (lhs.m_segment.m_start.y < rhs.min.y)
	{
		closestPointStart.y = rhs.min.y;
	}
	else if (lhs.m_segment.m_start.y > rhs.max.y)
	{
		closestPointStart.y = rhs.max.y;
	}
	else
	{
		closestPointStart.y = lhs.m_segment.m_start.y;
	}



	if (lhs.m_segment.m_start.z < rhs.min.z)
	{
		closestPointStart.z = rhs.min.z;
	}
	else if (lhs.m_segment.m_start.z > rhs.max.z)
	{
		closestPointStart.z = rhs.max.z;
	}
	else
	{
		closestPointStart.z = lhs.m_segment.m_start.z;
	}



	if (lhs.m_segment.m_end.x < rhs.min.x)
	{
		closestPointEnd.x = rhs.min.x;
	}
	else if (lhs.m_segment.m_end.x > rhs.max.x)
	{
		closestPointEnd.x = rhs.max.x;
	}
	else
	{
		closestPointEnd.x = lhs.m_segment.m_end.x;
	}



	if (lhs.m_segment.m_end.y < rhs.min.y)
	{
		closestPointEnd.y = rhs.min.y;
	}
	else if (lhs.m_segment.m_end.y > rhs.max.y)
	{
		closestPointEnd.y = rhs.max.y;
	}
	else
	{
		closestPointEnd.y = lhs.m_segment.m_end.y;
	}



	if (lhs.m_segment.m_end.z < rhs.min.z)
	{
		closestPointEnd.z = rhs.min.z;
	}
	else if (lhs.m_segment.m_end.z > rhs.max.z)
	{
		closestPointEnd.z = rhs.max.z;
	}
	else
	{
		closestPointEnd.z = lhs.m_segment.m_end.z;
	}

	float startDistanceSquared = pow((closestPointStart.x - lhs.m_segment.m_start.x), 2) + pow((closestPointStart.y - lhs.m_segment.m_start.y), 2) + pow((closestPointStart.z - lhs.m_segment.m_start.z), 2);
	float endDistanceSquared   = pow((closestPointEnd.x - lhs.m_segment.m_end.x), 2) + pow((closestPointEnd.y - lhs.m_segment.m_end.y), 2) + pow((closestPointEnd.z - lhs.m_segment.m_end.z), 2);
	float radiusSquared        = pow(lhs.radius, 2);

	if (startDistanceSquared < radiusSquared || endDistanceSquared < radiusSquared)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LineToAABB(const Line& segment, const AABB& box)
{
	XMFLOAT3 c;
	XMStoreFloat3(&c, (XMLoadFloat3(&box.min) + XMLoadFloat3(&box.max)) * 0.5f);
	XMFLOAT3 e;
	XMStoreFloat3(&e, XMLoadFloat3(&box.max) - XMLoadFloat3(&c));
	XMFLOAT3 m;
	XMStoreFloat3(&m, (XMLoadFloat3(&segment.m_start) + XMLoadFloat3(&segment.m_end)) * 0.5f);
	XMFLOAT3 d;
	XMStoreFloat3(&d, XMLoadFloat3(&segment.m_end) - XMLoadFloat3(&m));

	XMStoreFloat3(&m, XMLoadFloat3(&m) - XMLoadFloat3(&c));

	float adx = abs(d.x);
	if (abs(m.x) > e.x + adx) return false;
	float ady = abs(d.y);
	if (abs(m.y) > e.y + ady) return false;
	float adz = abs(d.z);
	if (abs(m.z) > e.z + adz) return false;

	adx += FLT_EPSILON; ady += FLT_EPSILON; adz += FLT_EPSILON;

	if (abs(m.y*d.z - m.z*d.y) > e.y * adz + e.z * ady) return false;
	if (abs(m.z*d.x - m.x*d.z) > e.x * adz + e.z * adx) return false;
	if (abs(m.x*d.y - m.y*d.x) > e.x * ady + e.y * adx) return false;

	return true;
}

bool NavMeshCollision(XMFLOAT3 pos, vector<Square*>  current)
{
	XMFLOAT3 temp = XMFLOAT3(pos.x, pos.y - 100.0f, pos.z);
	XMFLOAT3 Temp1 = XMFLOAT3(pos.x, pos.y + 100.0f, pos.z);
	//int hr = NavMeshMovement(pos, temp, current);
	if (BorderCollision(Temp1, temp, current))
		return true;

	return false;
}

bool BorderCollision(XMFLOAT3 start, XMFLOAT3 end, vector<Square*> current)
{
	Line ray;
	ray.m_start = start;
	ray.m_end = end;
	for (size_t i = 0; i < current.size(); i++)
	{
		

		MeshTriangle temp;
		temp.point1 = current[i]->m_top.m_start;
		temp.point2 = current[i]->m_top.m_end;
		temp.point3 = current[i]->m_bottom.m_start;

		MeshTriangle temp2;
		temp2.point1 = current[i]->m_bottom.m_start;
		temp.point2 = current[i]->m_top.m_end;
		temp.point3 = current[i]->m_bottom.m_end;
		if (IntersectLineTriangle(ray, current[i]->m_leftTri) && current[i]->walkable == false)
			return true;
		else if (IntersectLineTriangle(ray, current[i]->m_rightTri) && current[i]->walkable == false)
			return true;
	}
	return false;


}

bool LineToTriangle(Line& ray, MeshTriangle& current)
{
	//XMFLOAT3 u, v, n;		//Triangle
	//XMFLOAT3 dir, w0, w;	//Line
	//float r, a, b;			//Line-Plane intersection

	//XMVECTOR edge0 = XMLoadFloat3(&current.m_edges[0].m_start) - XMLoadFloat3(&current.m_edges[0].m_end);
	//XMVECTOR edge1 = XMLoadFloat3(&current.m_edges[1].m_start) - XMLoadFloat3(&current.m_edges[1].m_end);
	//XMVECTOR edge2 = XMLoadFloat3(&current.m_edges[2].m_start) - XMLoadFloat3(&current.m_edges[2].m_end);

	//XMStoreFloat3(&u, edge1 - edge0);
	//XMStoreFloat3(&v, edge2 - edge0);
	//XMStoreFloat3(&n, (edge1 - edge0)*(edge2 - edge0));

	//if (n.x == 0 && n.y == 0 && n.z == 0)
	//	return 0;

	//XMVECTOR direction = XMLoadFloat3(&ray.m_end) - XMLoadFloat3(&ray.m_start);
	//XMVECTOR W0 = XMLoadFloat3(&ray.m_start) - edge0;
	//XMStoreFloat3(&dir, direction);
	//XMStoreFloat3(&w0, W0);

	//a = -dot(n, w0);

	//b = dot(n, dir);
	//if (fabs(b) < SMALL_NUM)
	//{
	//	if (a == 0)
	//		return 1;
	//	else
	//		return 0;
	//}

	//r = a / b;
	//if (r < 0.0)
	//	return 0;
	//XMFLOAT3 collisionPoint;
	//XMStoreFloat3(&collisionPoint, XMLoadFloat3(&ray.m_start) + r*direction);

	//float uu, uv, vv, wu, wv, D;
	//uu = dot(u, u);
	//uv = dot(u, v);
	//vv = dot(v, v);
	//XMStoreFloat3(&w, XMLoadFloat3(&collisionPoint) - edge0);
	//wu = dot(w, u);
	//wv = dot(w, v);
	//D = uv*uv - uu*vv;

	//float s, t;
	//s = (uv*wv - vv*wu) / D;
	//if (s < 0.0 || s > 1.0)
	//	return 0;
	//t = (uv*wu - uu*wv) / D;
	//if (t < 0.0 || (s + t) > 1.0)
	//	return 0;

	//return 1;

	XMFLOAT3 normal = { 0,1,0 };
	XMFLOAT3 currentStart, currentEnd;
	XMStoreFloat3(&currentStart, XMLoadFloat3(&current.point1) - XMLoadFloat3(&ray.m_start));
	//currentEnd = ray.m_end;
	XMStoreFloat3(&currentEnd, XMLoadFloat3(&current.point1) - XMLoadFloat3(&ray.m_end));
	//XMStoreFloat3(&currentEnd, (XMLoadFloat3(&current.point1) + XMLoadFloat3(&current.point2) + XMLoadFloat3(&current.point3)) / 3);

	/*if ((dot(currentStart, normal) < 0 && dot(currentEnd, normal) < 0) || (dot(currentStart, normal) > 0 && dot(currentEnd, normal)) > 0)
		return false;*/

	float dot0 = dot(normal, currentStart);
	float dot1 = dot(normal, current.point1);
	float dot2 = dot0 - dot1;

	XMFLOAT3 line;
	XMStoreFloat3(&line, XMLoadFloat3(&currentEnd) - XMLoadFloat3(&currentStart));

	float dot3 = dot(normal, line);
	float dotFinal = -(dot2 / dot3);

	XMFLOAT3 collisionPoint;
	collisionPoint.x = ray.m_start.x + dotFinal * line.x;
	collisionPoint.y = ray.m_start.y + dotFinal * line.y;
	collisionPoint.z = ray.m_start.z + dotFinal * line.z;

	XMFLOAT3 edge1;
	XMFLOAT3 edge2;
	XMFLOAT3 edge3;

	XMStoreFloat3(&edge1, XMLoadFloat3(&current.m_edges[0].m_end) - XMLoadFloat3(&current.m_edges[0].m_start));
	XMStoreFloat3(&edge2, XMLoadFloat3(&current.m_edges[1].m_end) - XMLoadFloat3(&current.m_edges[1].m_start));
	XMStoreFloat3(&edge3, XMLoadFloat3(&current.m_edges[2].m_end) - XMLoadFloat3(&current.m_edges[2].m_start));

	XMFLOAT3 cpToPoint1;
	XMStoreFloat3(&cpToPoint1, XMLoadFloat3(&collisionPoint) - XMLoadFloat3(&current.point1));
	XMFLOAT3 normal1;
	cross_product(normal1, edge1, normal);

	if (dot(cpToPoint1, normal1) > 0)
		return false;

	XMFLOAT3 cpToPoint2;
	XMStoreFloat3(&cpToPoint2, XMLoadFloat3(&collisionPoint) - XMLoadFloat3(&current.point2));
	XMFLOAT3 normal2;
	cross_product(normal2, edge2, normal);

	if (dot(cpToPoint2, normal2) > 0)
		return false;

	XMFLOAT3 cpToPoint3;
	XMStoreFloat3(&cpToPoint3, XMLoadFloat3(&collisionPoint) - XMLoadFloat3(&current.point3));
	XMFLOAT3 normal3;
	cross_product(normal3, edge3, normal);

	if (dot(cpToPoint3, normal3) > 0)
		return false;

	return true;

	//XMFLOAT3 edge0; 
	//XMStoreFloat3(&edge0, XMLoadFloat3(&current.point2) - XMLoadFloat3(&current.point1);

}

int NavMeshMovement(XMFLOAT3 start, XMFLOAT3 end, NavNode* current)
{
	//Line ray;
	//ray.m_start = start;
	//ray.m_end = end;

	//if (/*LineToTriangleAARON(ray ,current->m_tri)*/IntersectLineTriangle(ray, current->m_tri))
	//	return 1;
	//else
	//{
	//	for (int i = 0; i < current->m_adj.size(); i++)
	//	{
	//		if (/*LineToTriangleAARON(ray, current->m_adj[i]->m_tri)*/IntersectLineTriangle(ray, current->m_adj[i]->m_tri))
	//		{
	//			//	current = current->m_adj[i];
	//			current = &current->operator=(*current->m_adj[i]);
	//			return 2;
	//		}
	//	}
	//}
	//return 3;
	return 0;
}

bool LineToTriangleAARON(Line ray, MeshTriangle& current)
{
	/*intIntersectSegmentTriangle(Pointp, Pointq, Pointa, Pointb, Pointc,
		float&u, float&v, float&w, float&t)*/
	XMFLOAT3 ab = XMFLOAT3(current.point2.x - current.point1.x, current.point2.y - current.point1.y, current.point2.z - current.point1.z);
	XMFLOAT3 ac = XMFLOAT3(current.point3.x - current.point1.x, current.point3.y - current.point1.y, current.point3.z - current.point1.z);
	XMFLOAT3 qp = XMFLOAT3(ray.m_end.x - ray.m_start.x, ray.m_end.y - ray.m_start.y, ray.m_end.z - ray.m_start.z);

	XMFLOAT3 n;
	cross_product(n, ab, ac);
	float   d = dot(qp, n);
	if (d <= FLT_EPSILON)
		return false;
	//FLT_EPSILON
	XMFLOAT3 ap = XMFLOAT3(ray.m_start.x - current.point1.x, ray.m_start.y - current.point1.y, ray.m_start.z - current.point1.z);

	float t = dot(ap, n);
	if (t < FLT_EPSILON)
		return false;
	if (t > d)
		return false;
	XMFLOAT3 e;
	cross_product(e, qp, ap);

	float v = dot(ac, e);
	if (v<FLT_EPSILON || v>d)
		return false;
	float w = -dot(ab, e);
	if (w<FLT_EPSILON || (v + w)>d)
		return false;

	return true;

}

bool LineToLine(Line a, Edge b)
{
	XMFLOAT3 da = XMFLOAT3(a.m_end.x - a.m_start.x, a.m_end.y - a.m_start.y, a.m_end.z - a.m_start.z);
	XMFLOAT3 db = XMFLOAT3(b.m_end.x - b.m_start.x, b.m_end.y - b.m_start.y, b.m_end.z - b.m_start.z);
	XMFLOAT3 dc = XMFLOAT3(b.m_start.x - a.m_start.x, b.m_start.y - a.m_start.y, b.m_start.z - a.m_start.z);
	XMFLOAT3 d;
	cross_product(d, da, db);
	if (dot(dc, d) != 0.0)
		return false;
	XMFLOAT3 c1, c2;
	cross_product(c1, dc, db);
	cross_product(c2, da, db);
	float n = c2.x*c2.x + c2.y*c2.y + c2.z*c2.z;
	float s = dot(c1, c2) / n;
	if (s >= 0.0f&&s <= 1.0)
		return true;

	return false;

}

bool IntersectLineTriangle(Line& ray, MeshTriangle* Tri)
{
	XMFLOAT3 PQ = XMFLOAT3(ray.m_end.x - ray.m_start.x, ray.m_end.y - ray.m_start.y, ray.m_end.z - ray.m_start.z);
	XMFLOAT3 PA = XMFLOAT3(Tri->point1.x - ray.m_start.x, Tri->point1.y - ray.m_start.y, Tri->point1.z - ray.m_start.z);
	XMFLOAT3 PB = XMFLOAT3(Tri->point2.x - ray.m_start.x, Tri->point2.y - ray.m_start.y, Tri->point2.z - ray.m_start.z);
	XMFLOAT3 PC = XMFLOAT3(Tri->point3.x - ray.m_start.x, Tri->point3.y - ray.m_start.y, Tri->point3.z - ray.m_start.z);

	float u, v, w;

	u = ScalarTriple(PQ, PC, PB);
	if (u < FLT_EPSILON)
		return false;
	v = ScalarTriple(PQ, PA, PC);
	if (v < FLT_EPSILON)
		return false;
	w = ScalarTriple(PQ, PB, PA);
	if (w < FLT_EPSILON)
		return false;

	return true;
}

int ClassifyCapsuleToPlane(const Plane& plane, const Capsule& capsule)
{
	//XMFLOAT4(capsule.m_segment.m_start.x, capsule.m_segment.m_start.y, capsule.m_segment.m_start.z, 1);
	/*float begin = dot(plane.normal, capsule.m_segment.m_start);
	float end = dot(plane.normal, capsule.m_segment.m_end);*/

	//float begin = dot1(plane.normal4, XMFLOAT4(capsule.m_segment.m_start.x, capsule.m_segment.m_start.y, capsule.m_segment.m_start.z, 1));
	//float end = dot1(plane.normal4, XMFLOAT4(capsule.m_segment.m_end.x, capsule.m_segment.m_end.y, capsule.m_segment.m_end.z, 1));
	//
	//if ((begin) + capsule.radius > 0 && (end) + capsule.radius > 0)
	//	return 1;
	//else if ((begin) + capsule.radius < 0 && (end) + capsule.radius < 0)
	//	return 2;
	//else
	//	return 3;
	//
	//return -1; // DELETE THIS LINE.

	float begin = dot(capsule.m_segment.m_start, plane.normal);
	float end = dot(capsule.m_segment.m_end, plane.normal);

	if ((begin)-plane.offset > capsule.radius && (end)-plane.offset > capsule.radius)
		return 1;
	else if ((begin)-plane.offset < -capsule.radius && (end)-plane.offset < -capsule.radius)
		return 2;
	else
		return 3;

	return -1; // DELETE THIS LINE.
}

bool FrustumToPoint(const Frustum & frustum, const XMFLOAT3& Point)
{
	for (size_t i = 0; i < 6; i++)
	{
		if (dot(frustum.planes[i].normal, Point) < frustum.planes[i].offset)
			return false;
	}
	return true;
}

bool FrustumToCapsule(const Frustum& frustum, const Capsule& capsule)
{
	for (int i = 0; i < 6; i++)
	{
		if (ClassifyCapsuleToPlane(frustum.planes[i], capsule) == 2)
			return false;
	}
	return true;
}

void BuildFrustum(Frustum& m_frustum, float m_fov, float m_nearPlane, float m_farPlane, float m_aspect, const XMFLOAT4X4& m_viewMatrix)
{
	XMFLOAT4X4 temp;
	XMStoreFloat4x4(&temp, XMMatrixInverse(nullptr, XMLoadFloat4x4(&m_viewMatrix)));
	//temp = m_viewMatrix;
	XMStoreFloat4x4(&temp, XMMatrixMultiply(XMMatrixRotationY(XMConvertToRadians(180)), XMLoadFloat4x4(&temp)));
	//temp = XMMatrixMultiply(XMMatrixRotationY(XMConvertToRadians(180)), temp);
	XMFLOAT3 vNearCenter = XMFLOAT3(temp._41, temp._42, temp._43) - XMFLOAT3(temp._31, temp._32, temp._33) * m_nearPlane;
	XMFLOAT3 vFarCenter = XMFLOAT3(temp._41, temp._42, temp._43) - XMFLOAT3(temp._31, temp._32, temp._33) * m_farPlane;

	/*XMFLOAT3 NearCenter = XMFLOAT3(vNearCenter.m128_f32[0], vNearCenter.m128_f32[1], vNearCenter.m128_f32[2]);
	XMFLOAT3 FarCenter = XMFLOAT3(vFarCenter.m128_f32[0], vFarCenter.m128_f32[1], vFarCenter.m128_f32[2]);*/

	float Hnear = 2 * tanf(m_fov / 2) * m_nearPlane;
	float Wnear = Hnear * m_aspect;
	float Hfar = 2 * tanf(m_fov / 2) * m_farPlane;
	float Wfar = Hfar * m_aspect;

	m_frustum.corners[FTL] = vFarCenter + XMFLOAT3(temp.m[1][0], temp.m[1][1], temp.m[1][2]) * (Hfar * 0.5f) - XMFLOAT3(temp.m[0][0], temp.m[0][1], temp.m[0][2]) * (Wfar * 0.5f);
	m_frustum.corners[FTR] = vFarCenter + XMFLOAT3(temp.m[1][0], temp.m[1][1], temp.m[1][2]) * (Hfar * 0.5f) + XMFLOAT3(temp.m[0][0], temp.m[0][1], temp.m[0][2]) * (Wfar * 0.5f);
	m_frustum.corners[FBL] = vFarCenter - XMFLOAT3(temp.m[1][0], temp.m[1][1], temp.m[1][2]) * (Hfar * 0.5f) - XMFLOAT3(temp.m[0][0], temp.m[0][1], temp.m[0][2]) * (Wfar * 0.5f);
	m_frustum.corners[FBR] = vFarCenter - XMFLOAT3(temp.m[1][0], temp.m[1][1], temp.m[1][2]) * (Hfar * 0.5f) + XMFLOAT3(temp.m[0][0], temp.m[0][1], temp.m[0][2]) * (Wfar * 0.5f);

	m_frustum.corners[NTL] = vNearCenter + XMFLOAT3(temp.m[1][0], temp.m[1][1], temp.m[1][2]) * (Hnear * 0.5f) - XMFLOAT3(temp.m[0][0], temp.m[0][1], temp.m[0][2]) * (Wnear * 0.5f);
	m_frustum.corners[NTR] = vNearCenter + XMFLOAT3(temp.m[1][0], temp.m[1][1], temp.m[1][2]) * (Hnear * 0.5f) + XMFLOAT3(temp.m[0][0], temp.m[0][1], temp.m[0][2]) * (Wnear * 0.5f);
	m_frustum.corners[NBL] = vNearCenter - XMFLOAT3(temp.m[1][0], temp.m[1][1], temp.m[1][2]) * (Hnear * 0.5f) - XMFLOAT3(temp.m[0][0], temp.m[0][1], temp.m[0][2]) * (Wnear * 0.5f);
	m_frustum.corners[NBR] = vNearCenter - XMFLOAT3(temp.m[1][0], temp.m[1][1], temp.m[1][2]) * (Hnear * 0.5f) + XMFLOAT3(temp.m[0][0], temp.m[0][1], temp.m[0][2]) * (Wnear * 0.5f);

	// Use the corner points to calculate the frustum planes.
	// This step is completed for you.
	ComputePlane(m_frustum.planes[NEAR_PLANE], m_frustum.corners[NBR], m_frustum.corners[NBL], m_frustum.corners[NTL]);
	ComputePlane(m_frustum.planes[FAR_PLANE], m_frustum.corners[FBL], m_frustum.corners[FBR], m_frustum.corners[FTR]);
	ComputePlane(m_frustum.planes[LEFT_PLANE], m_frustum.corners[NBL], m_frustum.corners[FBL], m_frustum.corners[FTL]);
	ComputePlane(m_frustum.planes[RIGHT_PLANE], m_frustum.corners[FBR], m_frustum.corners[NBR], m_frustum.corners[NTR]);
	ComputePlane(m_frustum.planes[TOP_PLANE], m_frustum.corners[NTR], m_frustum.corners[NTL], m_frustum.corners[FTL]);
	ComputePlane(m_frustum.planes[BOTTOM_PLANE], m_frustum.corners[NBL], m_frustum.corners[NBR], m_frustum.corners[FBR]);
	//// TO DO:
	//// Calculate the 8 corner points of the frustum and store them in the frustum.corners[] array.
	//// Use the FrustumCorners enum in CollisionLibrary.h to index into the corners array.
	//XMFLOAT3 NearCenter = XMFLOAT3(camXform.r[3].m128_f32[0], camXform.r[3].m128_f32[1], camXform.r[3].m128_f32[2]) - XMFLOAT3(camXform.r[2].m128_f32[0], camXform.r[2].m128_f32[1], camXform.r[2].m128_f32[2]) * nearDist;
	//XMFLOAT3 FarCenter = XMFLOAT3(camXform.r[3].m128_f32[0], camXform.r[3].m128_f32[1], camXform.r[3].m128_f32[2]) - XMFLOAT3(camXform.r[2].m128_f32[0], camXform.r[2].m128_f32[1], camXform.r[2].m128_f32[2]) * farDist;
	//
	//float Hnear = 2 * tan(fov / 2) * nearDist;
	//float Wnear = Hnear * ratio;
	//float Hfar = 2 * tan(fov / 2) * farDist;
	//float Wfar = Hfar * ratio;
	//
	//frustum.corners[FTL] = FarCenter + XMFLOAT3(camXform.r[1].m128_f32[0], camXform.r[1].m128_f32[1], camXform.r[1].m128_f32[2]) * (Hfar * 0.5f) - XMFLOAT3(camXform.r[0].m128_f32[0], camXform.r[0].m128_f32[1], camXform.r[0].m128_f32[2]) * (Wfar * 0.5f);
	//frustum.corners[FTR] = FarCenter + XMFLOAT3(camXform.r[1].m128_f32[0], camXform.r[1].m128_f32[1], camXform.r[1].m128_f32[2]) * (Hfar * 0.5f) + XMFLOAT3(camXform.r[0].m128_f32[0], camXform.r[0].m128_f32[1], camXform.r[0].m128_f32[2]) * (Wfar * 0.5f);
	//frustum.corners[FBL] = FarCenter - XMFLOAT3(camXform.r[1].m128_f32[0], camXform.r[1].m128_f32[1], camXform.r[1].m128_f32[2]) * (Hfar * 0.5f) - XMFLOAT3(camXform.r[0].m128_f32[0], camXform.r[0].m128_f32[1], camXform.r[0].m128_f32[2]) * (Wfar * 0.5f);
	//frustum.corners[FBR] = FarCenter - XMFLOAT3(camXform.r[1].m128_f32[0], camXform.r[1].m128_f32[1], camXform.r[1].m128_f32[2]) * (Hfar * 0.5f) + XMFLOAT3(camXform.r[0].m128_f32[0], camXform.r[0].m128_f32[1], camXform.r[0].m128_f32[2]) * (Wfar * 0.5f);
	//
	//frustum.corners[NTL] = NearCenter + XMFLOAT3(camXform.r[1].m128_f32[0], camXform.r[1].m128_f32[1], camXform.r[1].m128_f32[2]) * (Hnear * 0.5f) - XMFLOAT3(camXform.r[0].m128_f32[0], camXform.r[0].m128_f32[1], camXform.r[0].m128_f32[2]) * (Wnear * 0.5f);
	//frustum.corners[NTR] = NearCenter + XMFLOAT3(camXform.r[1].m128_f32[0], camXform.r[1].m128_f32[1], camXform.r[1].m128_f32[2]) * (Hnear * 0.5f) + XMFLOAT3(camXform.r[0].m128_f32[0], camXform.r[0].m128_f32[1], camXform.r[0].m128_f32[2]) * (Wnear * 0.5f);
	//frustum.corners[NBL] = NearCenter - XMFLOAT3(camXform.r[1].m128_f32[0], camXform.r[1].m128_f32[1], camXform.r[1].m128_f32[2]) * (Hnear * 0.5f) - XMFLOAT3(camXform.r[0].m128_f32[0], camXform.r[0].m128_f32[1], camXform.r[0].m128_f32[2]) * (Wnear * 0.5f);
	//frustum.corners[NBR] = NearCenter - XMFLOAT3(camXform.r[1].m128_f32[0], camXform.r[1].m128_f32[1], camXform.r[1].m128_f32[2]) * (Hnear * 0.5f) + XMFLOAT3(camXform.r[0].m128_f32[0], camXform.r[0].m128_f32[1], camXform.r[0].m128_f32[2]) * (Wnear * 0.5f);
	//
	//// Use the corner points to calculate the frustum planes.
	//// This step is completed for you.
	//ComputePlane(frustum.planes[NEAR_PLANE], frustum.corners[NBR], frustum.corners[NBL], frustum.corners[NTL]);
	//ComputePlane(frustum.planes[FAR_PLANE], frustum.corners[FBL], frustum.corners[FBR], frustum.corners[FTR]);
	//ComputePlane(frustum.planes[LEFT_PLANE], frustum.corners[NBL], frustum.corners[FBL], frustum.corners[FTL]);
	//ComputePlane(frustum.planes[RIGHT_PLANE], frustum.corners[FBR], frustum.corners[NBR], frustum.corners[NTR]);
	//ComputePlane(frustum.planes[TOP_PLANE], frustum.corners[NTR], frustum.corners[NTL], frustum.corners[FTL]);
	//ComputePlane(frustum.planes[BOTTOM_PLANE], frustum.corners[NBL], frustum.corners[NBR], frustum.corners[FBR]);
}

void BuildFrustum(Frustum & frustum, float ScreenDepth, XMMATRIX projection, XMMATRIX viewMatrix)
{
	

#if 0
	// Calculate the minimum Z distance in the frustum.
	float zMinimum, r;
	XMMATRIX matrix;
	zMinimum = -projection.r[3].m128_f32[2] / projection.r[2].m128_f32[2];
	r = ScreenDepth / (ScreenDepth - zMinimum);
	projection.r[2].m128_f32[2] = r;
	projection.r[3].m128_f32[2] = -r * zMinimum;

	matrix = XMMatrixMultiply(viewMatrix, projection);

	frustum.planes[NEAR_PLANE].normal4.x = matrix.r[3].m128_f32[0] + matrix.r[2].m128_f32[0];
	frustum.planes[NEAR_PLANE].normal4.y = matrix.r[3].m128_f32[1] + matrix.r[2].m128_f32[1];
	frustum.planes[NEAR_PLANE].normal4.z = matrix.r[3].m128_f32[2] + matrix.r[2].m128_f32[2];
	frustum.planes[NEAR_PLANE].normal4.w = matrix.r[3].m128_f32[3] + matrix.r[2].m128_f32[3];
	XMStoreFloat4(&frustum.planes[NEAR_PLANE].normal4, XMVector4Normalize(XMLoadFloat4(&frustum.planes[NEAR_PLANE].normal4)));
	frustum.planes[NEAR_PLANE].offset = zMinimum;
	
	frustum.planes[FAR_PLANE].normal4.x = matrix.r[3].m128_f32[0] - matrix.r[2].m128_f32[0];
	frustum.planes[FAR_PLANE].normal4.y = matrix.r[3].m128_f32[1] - matrix.r[2].m128_f32[1];
	frustum.planes[FAR_PLANE].normal4.z = matrix.r[3].m128_f32[2] - matrix.r[2].m128_f32[2];
	frustum.planes[FAR_PLANE].normal4.w = matrix.r[3].m128_f32[3] - matrix.r[2].m128_f32[3];
	XMStoreFloat4(&frustum.planes[FAR_PLANE].normal4, XMVector4Normalize(XMLoadFloat4(&frustum.planes[FAR_PLANE].normal4)));
	frustum.planes[FAR_PLANE].offset = ScreenDepth;

	frustum.planes[LEFT_PLANE].normal4.x = matrix.r[3].m128_f32[0] + matrix.r[0].m128_f32[0];
	frustum.planes[LEFT_PLANE].normal4.y = matrix.r[3].m128_f32[1] + matrix.r[0].m128_f32[1];
	frustum.planes[LEFT_PLANE].normal4.z = matrix.r[3].m128_f32[2] + matrix.r[0].m128_f32[2];
	frustum.planes[LEFT_PLANE].normal4.w = matrix.r[3].m128_f32[3] + matrix.r[0].m128_f32[3];
	XMStoreFloat4(&frustum.planes[LEFT_PLANE].normal4, XMVector4Normalize(XMLoadFloat4(&frustum.planes[LEFT_PLANE].normal4)));
	frustum.planes[LEFT_PLANE].offset = zMinimum;

	frustum.planes[RIGHT_PLANE].normal4.x = matrix.r[3].m128_f32[0] - matrix.r[0].m128_f32[0];
	frustum.planes[RIGHT_PLANE].normal4.y = matrix.r[3].m128_f32[1] - matrix.r[0].m128_f32[1];
	frustum.planes[RIGHT_PLANE].normal4.z = matrix.r[3].m128_f32[2] - matrix.r[0].m128_f32[2];
	frustum.planes[RIGHT_PLANE].normal4.w = matrix.r[3].m128_f32[3] - matrix.r[0].m128_f32[3];
	XMStoreFloat4(&frustum.planes[RIGHT_PLANE].normal4, XMVector4Normalize(XMLoadFloat4(&frustum.planes[RIGHT_PLANE].normal4)));
	frustum.planes[RIGHT_PLANE].offset = zMinimum;

	frustum.planes[TOP_PLANE].normal4.x = matrix.r[3].m128_f32[0] + matrix.r[1].m128_f32[0];
	frustum.planes[TOP_PLANE].normal4.y = matrix.r[3].m128_f32[1] + matrix.r[1].m128_f32[1];
	frustum.planes[TOP_PLANE].normal4.z = matrix.r[3].m128_f32[2] + matrix.r[1].m128_f32[2];
	frustum.planes[TOP_PLANE].normal4.w = matrix.r[3].m128_f32[3] + matrix.r[1].m128_f32[3];
	XMStoreFloat4(&frustum.planes[TOP_PLANE].normal4, XMVector4Normalize(XMLoadFloat4(&frustum.planes[TOP_PLANE].normal4)));
	frustum.planes[TOP_PLANE].offset = zMinimum;

	frustum.planes[BOTTOM_PLANE].normal4.x = matrix.r[3].m128_f32[0] - matrix.r[0].m128_f32[0];
	frustum.planes[BOTTOM_PLANE].normal4.y= matrix.r[3].m128_f32[1] - matrix.r[0].m128_f32[1];
	frustum.planes[BOTTOM_PLANE].normal4.z = matrix.r[3].m128_f32[2] - matrix.r[0].m128_f32[2];
	frustum.planes[BOTTOM_PLANE].normal4.w = matrix.r[3].m128_f32[3] - matrix.r[0].m128_f32[3];
	XMStoreFloat4(&frustum.planes[BOTTOM_PLANE].normal4, XMVector4Normalize(XMLoadFloat4(&frustum.planes[BOTTOM_PLANE].normal4)));
	frustum.planes[BOTTOM_PLANE].offset = zMinimum;
#endif

	XMMATRIX viewProjection = XMMatrixMultiply(viewMatrix, projection);

	frustum.planes[NEAR_PLANE].normal4.x = viewProjection.r[2].m128_f32[0];
	frustum.planes[NEAR_PLANE].normal4.y = viewProjection.r[2].m128_f32[1];
	frustum.planes[NEAR_PLANE].normal4.z = viewProjection.r[2].m128_f32[2];
	frustum.planes[NEAR_PLANE].normal4.w = viewProjection.r[2].m128_f32[3];

	frustum.planes[FAR_PLANE].normal4.x = viewProjection.r[3].m128_f32[0] - viewProjection.r[2].m128_f32[0];
	frustum.planes[FAR_PLANE].normal4.y = viewProjection.r[3].m128_f32[1] - viewProjection.r[2].m128_f32[1];
	frustum.planes[FAR_PLANE].normal4.z = viewProjection.r[3].m128_f32[2] - viewProjection.r[2].m128_f32[2];
	frustum.planes[FAR_PLANE].normal4.w = viewProjection.r[3].m128_f32[3] - viewProjection.r[2].m128_f32[3];

	frustum.planes[LEFT_PLANE].normal4.x = viewProjection.r[3].m128_f32[0] + viewProjection.r[0].m128_f32[0];
	frustum.planes[LEFT_PLANE].normal4.y = viewProjection.r[3].m128_f32[1] + viewProjection.r[0].m128_f32[1];
	frustum.planes[LEFT_PLANE].normal4.z = viewProjection.r[3].m128_f32[2] + viewProjection.r[0].m128_f32[2];
	frustum.planes[LEFT_PLANE].normal4.w = viewProjection.r[3].m128_f32[3] + viewProjection.r[0].m128_f32[3];

	frustum.planes[RIGHT_PLANE].normal4.x = viewProjection.r[3].m128_f32[0] - viewProjection.r[0].m128_f32[0];
	frustum.planes[RIGHT_PLANE].normal4.y = viewProjection.r[3].m128_f32[1] - viewProjection.r[0].m128_f32[1];
	frustum.planes[RIGHT_PLANE].normal4.z = viewProjection.r[3].m128_f32[2] - viewProjection.r[0].m128_f32[2];
	frustum.planes[RIGHT_PLANE].normal4.w = viewProjection.r[3].m128_f32[3] - viewProjection.r[0].m128_f32[3];

	frustum.planes[TOP_PLANE].normal4.x = viewProjection.r[3].m128_f32[0] - viewProjection.r[1].m128_f32[0];
	frustum.planes[TOP_PLANE].normal4.y = viewProjection.r[3].m128_f32[1] - viewProjection.r[1].m128_f32[1];
	frustum.planes[TOP_PLANE].normal4.z = viewProjection.r[3].m128_f32[2] - viewProjection.r[1].m128_f32[2];
	frustum.planes[TOP_PLANE].normal4.w = viewProjection.r[3].m128_f32[3] - viewProjection.r[1].m128_f32[3];

	frustum.planes[BOTTOM_PLANE].normal4.x = viewProjection.r[3].m128_f32[0] + viewProjection.r[1].m128_f32[0];
	frustum.planes[BOTTOM_PLANE].normal4.y = viewProjection.r[3].m128_f32[1] + viewProjection.r[1].m128_f32[1];
	frustum.planes[BOTTOM_PLANE].normal4.z = viewProjection.r[3].m128_f32[2] + viewProjection.r[1].m128_f32[2];
	frustum.planes[BOTTOM_PLANE].normal4.w = viewProjection.r[3].m128_f32[3] + viewProjection.r[1].m128_f32[3];

	for (size_t i = 0; i < 6; i++)
	{
		XMStoreFloat4(&frustum.planes[i].normal4, XMVector4Normalize(XMLoadFloat4(&frustum.planes[i].normal4)));
	}
}

void ComputePlane(Plane &plane, const XMFLOAT3& pointA, const XMFLOAT3& pointB, const XMFLOAT3 &pointC)
{
	//vec3f PlaneNormal;
	cross_product(plane.normal, 
		XMFLOAT3(pointB.x - pointA.x, pointB.y - pointA.y, pointB.z - pointA.z), 
		XMFLOAT3(pointC.x - pointB.x, pointC.y - pointB.y, pointC.z - pointB.z));

	plane.normal = Normalize(plane.normal);
	plane.offset = dot(plane.normal, pointA);
}

float Magnitude(XMFLOAT3 _pos)
{
	float Magnitude;

	Magnitude = sqrtf(_pos.x*_pos.x + _pos.y*_pos.y + _pos.z*_pos.z); 
	
	return Magnitude;
}

XMFLOAT3 Normalize(XMFLOAT3 _Normalize)
{
	float RSqrt = 1 / Magnitude(_Normalize);

	_Normalize.x *= RSqrt;
	_Normalize.y *= RSqrt;
	_Normalize.z *= RSqrt;

	return _Normalize;
}

float VectorLength(XMFLOAT3 _vector)
{
	float result;
	result = sqrtf(_vector.x * _vector.x +
		_vector.y * _vector.y +
		_vector.z * _vector.z);
	return result;
}

float Distance(XMFLOAT3  _start, XMFLOAT3 _end)
{
	float x = (_end.x - _start.x);
	x *= x;
	float z = (_end.z - _start.z);
	z *= z;
	return sqrtf((x + z));
}

int ClassifyAabbToPlane(const Plane& plane, const AABB& aabb)
{

	XMFLOAT3 CenterP = (aabb.min + aabb.max) * 0.5f;
	XMFLOAT3 exTend = aabb.max - CenterP;
	float projRadius = exTend.x * abs(plane.normal.x) + exTend.y * abs(plane.normal.y) + exTend.z * abs(plane.normal.z);

	if (dot(CenterP, plane.normal) - plane.offset > projRadius)
		return 1;
	else if (dot(CenterP, plane.normal) - plane.offset < -projRadius)
		return 2;
	else //if (dot_product(sphere.m_Center, plane.normal) - plane.offset == sphere.m_Radius)
		return 3;

	//return -1; // DELETE THIS LINE.
}

bool FrustumToAABB(const Frustum& frustum, const AABB& aabb)
{
	for (int i = 0; i < 6; i++)
	{
		if (ClassifyAabbToPlane(frustum.planes[i], aabb) == 2)
			return false;
	}

	return true;
}

XMFLOAT3 operator+(const XMFLOAT3 & _Lvalue, const XMFLOAT3& _Rvalue)
{
	XMFLOAT3 result;
	
	result.x = _Lvalue.x + _Rvalue.x;
	result.y = _Lvalue.y + _Rvalue.y;
	result.z = _Lvalue.z + _Rvalue.z;

	return result;
}

XMFLOAT3 operator-(const XMFLOAT3 & _Lvalue, const XMFLOAT3& _Rvalue)
{
	XMFLOAT3 result;

	result.x = _Lvalue.x - _Rvalue.x;
	result.y = _Lvalue.y - _Rvalue.y;
	result.z = _Lvalue.z - _Rvalue.z;

	return result;
}

XMFLOAT3 operator*(const XMFLOAT3 & _Lvalue, const float & _Rvalue)
{
	XMFLOAT3 result;

	result.x = _Lvalue.x * _Rvalue;
	result.y = _Lvalue.y * _Rvalue;
	result.z = _Lvalue.z * _Rvalue;

	return result;
}

XMFLOAT3 operator*(const float & _Rvalue, const XMFLOAT3 & _Lvalue)
{
	return _Lvalue * _Rvalue;
}
