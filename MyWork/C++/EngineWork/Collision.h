#pragma once
#include"CollisionDefines.h"


float ScalarTriple(XMFLOAT3 _u, XMFLOAT3 _v, XMFLOAT3 _w);
bool SphereToSphere(const Sphere& lhs, const Sphere& rhs);
bool CapsuleToCapsule(const Capsule& lhs, const Capsule& rhs, float& penetration);
bool SphereToCapsule(const Sphere& lhs, const Capsule& rhs);
///////NAVMATH
bool NavMeshCollision(XMFLOAT3 pos, vector<Square*>  current);
bool BorderCollision(XMFLOAT3 start, XMFLOAT3 end, vector<Square*> current);
//////////////////
bool SphereToAABB(const Sphere*  lhs, const vector<AABB>& rhs, int numSpheres);
bool LineToTriangle(Line& ray, MeshTriangle& current);
bool LineToAABB(const Line& segment, const AABB& box);
bool CapsuleToAABB(const Capsule& lhs, const AABB& rhs);
int NavMeshMovement(XMFLOAT3 start, XMFLOAT3 end, NavNode* current);
bool LineToTriangleAARON(Line ray, MeshTriangle& current);
bool LineToLine(Line a, Edge b);
bool IntersectLineTriangle(Line& ray, MeshTriangle* Tri);
int ClassifyCapsuleToPlane(const Plane& plane, const Capsule& capsule);
bool FrustumToPoint(const Frustum& frustum, const XMFLOAT3& Point);
bool FrustumToCapsule(const Frustum& frustum, const Capsule& capsule);
void BuildFrustum(Frustum& m_frustum, float m_fov, float m_nearPlane, float m_farPlane, float m_aspect, const XMFLOAT4X4& m_viewMatrix);
void BuildFrustum(Frustum& frustum, float ScreenDepth, XMMATRIX projection, XMMATRIX viewMatrix);
void ComputePlane(Plane &plane, const XMFLOAT3& pointA, const XMFLOAT3& pointB, const XMFLOAT3 &pointC);
float Magnitude(XMFLOAT3 _pos);
XMFLOAT3 Normalize(XMFLOAT3 _Normalize);
float VectorLength(XMFLOAT3 _vector);
float Distance(XMFLOAT3 _start, XMFLOAT3 _end);
int ClassifyAabbToPlane(const Plane& plane, const AABB& aabb);
bool FrustumToAABB(const Frustum& frustum, const AABB& aabb);

XMFLOAT3 operator+(const XMFLOAT3&_Lvalue, const XMFLOAT3& _Rvalue);
XMFLOAT3 operator-(const XMFLOAT3&_Lvalue, const XMFLOAT3& _Rvalue);
XMFLOAT3 operator*(const XMFLOAT3&_Lvalue, const float& _Rvalue);
XMFLOAT3 operator*(const float& _Rvalue, const XMFLOAT3&_Lvalue);
