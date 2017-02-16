#pragma once
///////////////////////////////////////////
//                                       //
//       THIS IS THE WORK OF:            //
//     Programmer: Aaron Ridlen          //
//     Instructor: Larri Nori            //
//      Date:  AUGUST 2016               //
//                                       //
///////////////////////////////////////////
#define PI 3.14159F
struct VERTEX4
{
	float xyzw[4];
	//float u;
	//float v;

};
struct MATRIX4X4
{
	VERTEX4 vec[4];

};
struct VERTEX3
{
	float xyz[3];
	unsigned int m_color;


};
struct MATRIX3X3
{
	VERTEX3 vec[3];

};
unsigned int Blend(unsigned int colorA, unsigned int colorB, float ratio)
{
	int sa, sr, sg, sb;
	int da, dr, dg, db;
	int fa, fr, fg, fb;

	sa = (colorA & 0xFF000000) >> 24;
	sr = (colorA & 0x00FF0000) >> 16;
	sg = (colorA & 0x0000FF00) >> 8;
	sb = (colorA & 0x000000FF);

	da = (colorB & 0xFF000000) >> 24;
	dr = (colorB & 0x00FF0000) >> 16;
	dg = (colorB & 0x0000FF00) >> 8;
	db = (colorB & 0x000000FF);

	fa = (int)((da - sa) * ratio + sa);
	fr = (int)((dr - sr) * ratio + sr);
	fg = (int)((dg - sg) * ratio + sg);
	fb = (int)((db - sb) * ratio + sb);

	return (fa << 24) | (fr << 16) | (fg << 8) | fb;

}
unsigned int Convert2D_1D(unsigned int x, unsigned int y, unsigned int width)
{
	unsigned int converted = (y*width + x);

	return converted;

}
MATRIX4X4 Matrix_Transpose(MATRIX4X4 m)
{
	MATRIX4X4 tran;
	tran.vec[0].xyzw[0] = m.vec[0].xyzw[0];  // _e11;
	tran.vec[0].xyzw[1] = m.vec[1].xyzw[0]; //_e21;
	tran.vec[0].xyzw[2] = m.vec[2].xyzw[0];    //_e31;
	tran.vec[0].xyzw[3] = m.vec[3].xyzw[0];  //_e41;

	tran.vec[1].xyzw[0] = m.vec[0].xyzw[1];//_e12;
	tran.vec[1].xyzw[1] = m.vec[1].xyzw[1];//_e22;
	tran.vec[1].xyzw[2] = m.vec[2].xyzw[1];//_e32;
	tran.vec[1].xyzw[3] = m.vec[3].xyzw[1];//_e42;

	tran.vec[2].xyzw[0] = m.vec[0].xyzw[2];// _e13;
	tran.vec[2].xyzw[1] = m.vec[1].xyzw[2]; //_e23;
	tran.vec[2].xyzw[2] = m.vec[2].xyzw[2];
	tran.vec[2].xyzw[3] = m.vec[3].xyzw[2];

	tran.vec[3].xyzw[0] = m.vec[0].xyzw[3];
	tran.vec[3].xyzw[1] = m.vec[1].xyzw[3];// TODO LAB 2: Replace with your implementation.
	tran.vec[3].xyzw[2] = m.vec[2].xyzw[3];
	tran.vec[3].xyzw[3] = m.vec[3].xyzw[3];
	return tran;
}

VERTEX4 MultiplyVertexByMatrix4X4(VERTEX4 v, MATRIX4X4 x)
{
	MATRIX4X4 tan;
	tan = Matrix_Transpose(x);
	VERTEX4 h;
	h.xyzw[0] = (tan.vec[0].xyzw[0] *v.xyzw[0]) + (tan.vec[0].xyzw[1] *v.xyzw[1]) + (tan.vec[0].xyzw[2] *v.xyzw[2]) + (tan.vec[0].xyzw[3] *v.xyzw[3]);
	h.xyzw[1] = (tan.vec[1].xyzw[0] *v.xyzw[0]) + (tan.vec[1].xyzw[1] *v.xyzw[1]) + (tan.vec[1].xyzw[2] *v.xyzw[2]) + (tan.vec[1].xyzw[3] *v.xyzw[3]);
	h.xyzw[2] = (tan.vec[2].xyzw[0] *v.xyzw[0]) + (tan.vec[2].xyzw[1] *v.xyzw[1]) + (tan.vec[2].xyzw[2] *v.xyzw[2]) + (tan.vec[2].xyzw[3] *v.xyzw[3]);
	h.xyzw[3] = (tan.vec[3].xyzw[0] *v.xyzw[0]) + (tan.vec[3].xyzw[1] *v.xyzw[1]) + (tan.vec[3].xyzw[2] *v.xyzw[2]) + (tan.vec[3].xyzw[3] *v.xyzw[3]);
	
	//h.u = v.u;
	//h.v = v.v;
	return h;
}
unsigned int ConvertColor(unsigned int colorA)
{
	int sa, sr, sg, sb;
	sa = (colorA & 0x0000FF);
	sr = (colorA & 0x0000FF00) >> 8;
	sg = (colorA & 0x00FF0000) >> 16;
	sb = (colorA & 0xFF000000)>>24;
	return(sa << 24) | (sr << 16) | (sg << 8) | sb;
}

MATRIX4X4 MultiplyMatrixByMatrix4X4(MATRIX4X4 x, MATRIX4X4 y)
{
	/// --->
	/// [i1 j1 k1 n1]	   [i1] j1 k1 n1 |
	///  i2 j2 k2 n2	   [i2] j2 k2 n2 |
	///  i3 j3 k3 n3	   [i3] j3 k3 n3 V
	///  i4 j4 k4 n4	   [i4] j4 k4 n4
	VERTEX4 temp[4];
	
	////					[			1				]	[				2				  ]   [					3				]   [				4					]
	////						X				Y					X				Y					X					Y					X					Y
	temp[0].xyzw[0]=    x.vec[0].xyzw[0] * y.vec[0].xyzw[0]        + x.vec[0].xyzw[1] * y.vec[1].xyzw[0] +        x.vec[0].xyzw[2] * y.vec[2].xyzw[0] +      x.vec[0].xyzw[3] * y.vec[3].xyzw[0];
	temp[0].xyzw[1]=    x.vec[0].xyzw[0] * y.vec[0].xyzw[1]        + x.vec[0].xyzw[1] * y.vec[1].xyzw[1] +        x.vec[0].xyzw[2] * y.vec[2].xyzw[1] +      x.vec[0].xyzw[3] * y.vec[3].xyzw[1];
	temp[0].xyzw[2]=    x.vec[0].xyzw[0] * y.vec[0].xyzw[2]        + x.vec[0].xyzw[1] * y.vec[1].xyzw[2] +        x.vec[0].xyzw[2] * y.vec[2].xyzw[2] +      x.vec[0].xyzw[3] * y.vec[3].xyzw[2];
	temp[0].xyzw[3] =   x.vec[0].xyzw[0] * y.vec[0].xyzw[3] +        x.vec[0].xyzw[1] * y.vec[1].xyzw[3] +        x.vec[0].xyzw[2] * y.vec[2].xyzw[3] +      x.vec[0].xyzw[3] * y.vec[3].xyzw[3];
	//////			    			w					w	       				w				    w      					  w					 w	        
	temp[1].xyzw[0]=    x.vec[1].xyzw[0] * y.vec[0].xyzw[0]        + x.vec[1].xyzw[1] * y.vec[1].xyzw[0] +        x.vec[1].xyzw[2] * y.vec[2].xyzw[0] +      x.vec[1].xyzw[3] * y.vec[3].xyzw[0];
	temp[1].xyzw[1]=    x.vec[1].xyzw[0] * y.vec[0].xyzw[1]        + x.vec[1].xyzw[1] * y.vec[1].xyzw[1] +        x.vec[1].xyzw[2] * y.vec[2].xyzw[1] +      x.vec[1].xyzw[3] * y.vec[3].xyzw[1];
	temp[1].xyzw[2]=    x.vec[1].xyzw[0] * y.vec[0].xyzw[2]        + x.vec[1].xyzw[1] * y.vec[1].xyzw[2] +        x.vec[1].xyzw[2] * y.vec[2].xyzw[2] +      x.vec[1].xyzw[3] * y.vec[3].xyzw[2];
	temp[1].xyzw[3] =   x.vec[1].xyzw[0] * y.vec[0].xyzw[3] +        x.vec[1].xyzw[1] * y.vec[1].xyzw[3] +        x.vec[1].xyzw[2] * y.vec[2].xyzw[3] +      x.vec[1].xyzw[3] * y.vec[3].xyzw[3];
	//////			    			w					w	       				w				    w      					  w					 w	        
	temp[2].xyzw[0]=    x.vec[2].xyzw[0] * y.vec[0].xyzw[0]        + x.vec[2].xyzw[1] * y.vec[1].xyzw[0] +        x.vec[2].xyzw[2] * y.vec[2].xyzw[0] +      x.vec[2].xyzw[3] * y.vec[3].xyzw[0];
	temp[2].xyzw[1]=    x.vec[2].xyzw[0] * y.vec[0].xyzw[1]        + x.vec[2].xyzw[1] * y.vec[1].xyzw[1] +        x.vec[2].xyzw[2] * y.vec[2].xyzw[1] +      x.vec[2].xyzw[3] * y.vec[3].xyzw[1];
	temp[2].xyzw[2]=    x.vec[2].xyzw[0] * y.vec[0].xyzw[2]        + x.vec[2].xyzw[1] * y.vec[1].xyzw[2] +        x.vec[2].xyzw[2] * y.vec[2].xyzw[2] +      x.vec[2].xyzw[3] * y.vec[3].xyzw[2];
	temp[2].xyzw[3] =   x.vec[2].xyzw[0] * y.vec[0].xyzw[3] +        x.vec[2].xyzw[1] * y.vec[1].xyzw[3] +        x.vec[2].xyzw[2] * y.vec[2].xyzw[3] +      x.vec[2].xyzw[3] * y.vec[3].xyzw[3];

	temp[3].xyzw[0] =   x.vec[3].xyzw[0] * y.vec[0].xyzw[0] +	   x.vec[3].xyzw[1] * y.vec[1].xyzw[0] +		  x.vec[3].xyzw[2] * y.vec[2].xyzw[0] +      x.vec[3].xyzw[3] * y.vec[3].xyzw[0];
	temp[3].xyzw[1] =   x.vec[3].xyzw[0] * y.vec[0].xyzw[1] +	   x.vec[3].xyzw[1] * y.vec[1].xyzw[1] +		  x.vec[3].xyzw[2] * y.vec[2].xyzw[1] +      x.vec[3].xyzw[3] * y.vec[3].xyzw[1];
	temp[3].xyzw[2] =   x.vec[3].xyzw[0] * y.vec[0].xyzw[2] +	   x.vec[3].xyzw[1] * y.vec[1].xyzw[2] +		  x.vec[3].xyzw[2] * y.vec[2].xyzw[2] +      x.vec[3].xyzw[3] * y.vec[3].xyzw[2];
	temp[3].xyzw[3] =   x.vec[3].xyzw[0] * y.vec[0].xyzw[3] +	   x.vec[3].xyzw[1] * y.vec[1].xyzw[3] +		  x.vec[3].xyzw[2] * y.vec[2].xyzw[3] +      x.vec[3].xyzw[3] * y.vec[3].xyzw[3];
	MATRIX4X4 k;
	k.vec[0] = temp[0];
	k.vec[1] = temp[1];
	k.vec[2] = temp[2];
	k.vec[3] = temp[3];
	return k;


}

MATRIX4X4 RotateX(float _rot)
{

	MATRIX4X4 temp;
	temp.vec[0].xyzw[0]= 1.0f;
	temp.vec[0].xyzw[1] = 0.0f;
	temp.vec[0].xyzw[2] = 0.0f;
	temp.vec[0].xyzw[3] = 0.0f;
	
	temp.vec[1].xyzw[0] = 0.0f;
	temp.vec[1].xyzw[1]= (float)cos(_rot);
	temp.vec[1].xyzw[2]= (float)-sin(_rot);
	temp.vec[1].xyzw[3] = 0.0f;
	
	temp.vec[2].xyzw[0]= 0.0f;
	temp.vec[2].xyzw[1]= (float)sin(_rot);
	temp.vec[2].xyzw[2] = (float)cos(_rot);
	temp.vec[2].xyzw[3] = 0.0f;
	
	temp.vec[3].xyzw[0]= 0.0f;
	temp.vec[3].xyzw[1]= 0.0f;
	temp.vec[3].xyzw[2]= 0.0f;
	temp.vec[3].xyzw[3]= 1.0f;
	
	return temp;
}
MATRIX4X4 RotateY(float _rot)
{
	MATRIX4X4 temp;
	temp.vec[0].xyzw[0] = (float)cos(_rot);
	temp.vec[0].xyzw[1] = 0.0f;
	temp.vec[0].xyzw[2] = (float)sin(_rot);
	temp.vec[0].xyzw[3] = 0.0f;

	temp.vec[1].xyzw[0] = 0.0f;
	temp.vec[1].xyzw[1] = 1.0f;
	temp.vec[1].xyzw[2] = 0.0f;
	temp.vec[1].xyzw[3] = 0.0f;

	temp.vec[2].xyzw[0] = (float)-sin(_rot);
	temp.vec[2].xyzw[1] = 0.0f;
	temp.vec[2].xyzw[2] = (float)cos(_rot);
	temp.vec[2].xyzw[3] = 0.0f;

	temp.vec[3].xyzw[0] = 0.0f;
	temp.vec[3].xyzw[1] = 0.0f;
	temp.vec[3].xyzw[2] = 0.0f;
	temp.vec[3].xyzw[3] = 1.0f;


	return temp;
}
MATRIX4X4 RotateZ(unsigned int _rot)
{
	MATRIX4X4 temp;
	temp.vec[0].xyzw[0] = (float)cos(_rot*3.14F / 180.0F);
	temp.vec[0].xyzw[1] = (float)-sin(_rot*3.14F / 180.0F);
	temp.vec[0].xyzw[2] = 0.0f;
	temp.vec[0].xyzw[3] = 0.0f;

	temp.vec[1].xyzw[0] = (float)-sin(_rot*3.14F / 180.0F);
	temp.vec[1].xyzw[1] = (float)cos(_rot*3.14F / 180.0F);
	temp.vec[1].xyzw[2] = 0.0f;
	temp.vec[1].xyzw[3] = 0.0f;

	temp.vec[2].xyzw[0] = 0.0f;
	temp.vec[2].xyzw[1] = 0.0f;
	temp.vec[2].xyzw[2] = 1.0f;
	temp.vec[2].xyzw[3] = 0.0f;

	temp.vec[3].xyzw[0] = 0.0f;
	temp.vec[3].xyzw[1] = 0.0f;
	temp.vec[3].xyzw[2] = 0.0f;
	temp.vec[3].xyzw[3] = 1.0f;

	return temp;
}
MATRIX4X4 IdentityMatrix()
{
	MATRIX4X4 temp;
	temp.vec[0].xyzw[0] = 1.0f;
	temp.vec[0].xyzw[1] = 0.0f;
	temp.vec[0].xyzw[2] = 0.0f;
	temp.vec[0].xyzw[3] = 0.0f;

	temp.vec[1].xyzw[0] = 0.0f;
	temp.vec[1].xyzw[1] = 1.0f;
	temp.vec[1].xyzw[2] = 0.0f;
	temp.vec[1].xyzw[3] = 0.0f;

	temp.vec[2].xyzw[0] = 0.0f;
	temp.vec[2].xyzw[1] = 0.0f;
	temp.vec[2].xyzw[2] = 1.0f;
	temp.vec[2].xyzw[3] = 0.0f;

	temp.vec[3].xyzw[0] = 0.0f;
	temp.vec[3].xyzw[1] = 0.0f;
	temp.vec[3].xyzw[2] = 0.0f;
	temp.vec[3].xyzw[3] = 1.0f;
	return temp;

}
MATRIX3X3 Matrix_Transpose3(MATRIX3X3 m)
{
	MATRIX3X3 tran;
	tran.vec[0].xyz[0] = m.vec[0].xyz[0];  // _e11;
	tran.vec[0].xyz[1] = m.vec[1].xyz[0]; //_e21;
	tran.vec[0].xyz[2] = m.vec[2].xyz[0];    //_e31;
											 //tran.vec[0].xyzw[3] = m.vec[3].xyzw[0];  //_e41;

	tran.vec[1].xyz[0] = m.vec[0].xyz[1];//_e12;
	tran.vec[1].xyz[1] = m.vec[1].xyz[1];//_e22;
	tran.vec[1].xyz[2] = m.vec[2].xyz[1];//_e32;
										 //tran.vec[1].xyzw[3] = m.vec[3].xyzw[1];//_e42;

	tran.vec[2].xyz[0] = m.vec[0].xyz[2];// _e13;
	tran.vec[2].xyz[1] = m.vec[1].xyz[2]; //_e23;
	tran.vec[2].xyz[2] = m.vec[2].xyz[2];
	//tran.vec[2].xyzw[3] = m.vec[3].xyzw[2];


	//tran.vec[3].xyzw[3] = m.vec[3].xyzw[3];
	return tran;
}
VERTEX3 MultiplyVertexByMatrix(VERTEX3 x, MATRIX3X3 v)
{
	v = Matrix_Transpose3(v);
	VERTEX3 temp;
	//temp.xyz[0] = multiplyMe.xyz[0] * SV_WorldMatrix.vec[0].xyz[0] + multiplyMe.xyz[1] * SV_WorldMatrix.vec[1].xyz[0] + multiplyMe.xyz[2] * SV_WorldMatrix.vec[2].xyz[0];
	//temp.xyz[1] = multiplyMe.xyz[0] * SV_WorldMatrix.vec[0].xyz[1] + multiplyMe.xyz[1] * SV_WorldMatrix.vec[1].xyz[1] + multiplyMe.xyz[2] * SV_WorldMatrix.vec[2].xyz[1];
	//temp.xyz[2] = multiplyMe.xyz[0] * SV_WorldMatrix.vec[0].xyz[2] + multiplyMe.xyz[1] * SV_WorldMatrix.vec[1].xyz[2] + multiplyMe.xyz[2] * SV_WorldMatrix.vec[2].xyz[2];
	///Final
	temp.xyz[0] = (x.xyz[0] * v.vec[0].xyz[0]) + (x.xyz[1] * v.vec[0].xyz[1]) + (x.xyz[2] * v.vec[0].xyz[2]);
	temp.xyz[1] = (x.xyz[0] * v.vec[1].xyz[0]) + (x.xyz[1] * v.vec[1].xyz[1]) + (x.xyz[2] * v.vec[1].xyz[2]);
	temp.xyz[2] = (x.xyz[0] * v.vec[2].xyz[0]) + (x.xyz[1] * v.vec[2].xyz[1]) + (x.xyz[2] * v.vec[2].xyz[2]);
	return temp;
}
MATRIX4X4 FastInverse(MATRIX4X4 v)
{
	MATRIX3X3 temp;
	temp.vec[0].xyz[0] = v.vec[0].xyzw[0];
	temp.vec[0].xyz[1] = v.vec[0].xyzw[1];
	temp.vec[0].xyz[2] = v.vec[0].xyzw[2];
	temp.vec[1].xyz[0] = v.vec[1].xyzw[0];
	temp.vec[1].xyz[1] = v.vec[1].xyzw[1];
	temp.vec[1].xyz[2] = v.vec[1].xyzw[2];
	temp.vec[2].xyz[0] = v.vec[2].xyzw[0];
	temp.vec[2].xyz[1] = v.vec[2].xyzw[1];
	temp.vec[2].xyz[2] = v.vec[2].xyzw[2];
	temp = Matrix_Transpose3(temp);

	VERTEX3 c;
	c.xyz[0] = v.vec[3].xyzw[0];
	c.xyz[1] = v.vec[3].xyzw[1];
	c.xyz[2] = v.vec[3].xyzw[2];
	VERTEX3 b;
	b = MultiplyVertexByMatrix(c, temp);
	MATRIX4X4 d;
	d.vec[0].xyzw[0] = temp.vec[0].xyz[0];
	d.vec[0].xyzw[1] = temp.vec[0].xyz[1];
	d.vec[0].xyzw[2] = temp.vec[0].xyz[2];
	d.vec[0].xyzw[3] = v.vec[0].xyzw[3];

	d.vec[1].xyzw[0] = temp.vec[1].xyz[0];
	d.vec[1].xyzw[1] = temp.vec[1].xyz[1];
	d.vec[1].xyzw[2] = temp.vec[1].xyz[2];
	d.vec[1].xyzw[3] = v.vec[1].xyzw[3];

	d.vec[2].xyzw[0] = temp.vec[2].xyz[0];
	d.vec[2].xyzw[1] = temp.vec[2].xyz[1];
	d.vec[2].xyzw[2] = temp.vec[2].xyz[2];
	d.vec[2].xyzw[3] = v.vec[2].xyzw[3];

	d.vec[3].xyzw[0] = -b.xyz[0];
	d.vec[3].xyzw[1] = -b.xyz[1];
	d.vec[3].xyzw[2] = -b.xyz[2];
	d.vec[3].xyzw[3] = v.vec[3].xyzw[1];

	return d;

}
MATRIX4X4 Projection()
{
	MATRIX4X4 v;
	v.vec[0].xyzw[0] =1;
	v.vec[0].xyzw[1] = 0;
	v.vec[0].xyzw[2] = 0;
	v.vec[0].xyzw[3] = 0;

	v.vec[1].xyzw[0] = 0;
	v.vec[1].xyzw[1] = 1;
	v.vec[1].xyzw[2] = 0;
	v.vec[1].xyzw[3] = 0;

	v.vec[2].xyzw[0] = 0;
	v.vec[2].xyzw[1] = 0;
	v.vec[2].xyzw[2] = 100.0f/(100.0f-0.1f);
	v.vec[2].xyzw[3] = 1;
	
	v.vec[3].xyzw[0] = 0;
	v.vec[3].xyzw[1] = 0;
	v.vec[3].xyzw[2] = -(100.0f*0.1f)/(100.0f-0.1f);
	v.vec[3].xyzw[3] = 0;
	return v;

}
MATRIX4X4 Translation(float x, float y, float z)
{
	/////Make Identity;
	MATRIX4X4 id;
	id = IdentityMatrix();
	id.vec[3].xyzw[0] = x;
	id.vec[3].xyzw[1] = y;
	id.vec[3].xyzw[2] = z;
	id.vec[3].xyzw[3] = 1;
	return id;
}
float DegreeToRadian(float deg)
{
	return deg * 0.0174527777777778f;
}