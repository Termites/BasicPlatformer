// Revient à faire #ifndef tralala #define tralala #endif
#pragma once
#include <cmath>

template<typename T>
struct Vector2D
{
	T x,y;

	Vector2D()
	{
		x=0;
		y=0;
	}

	Vector2D(const T&x, const T&y)
	{
		this->x = x;
		this->y = y;
	}

	// Converti un vector<A> en vector<B>
	template<typename T2>
	Vector2D(const Vector2D<T2> & O)
	{
		x = O.x;
		y = O.y;
	}

	float GetLength()
	{
		return sqrt(x*x + y*y);
	}

	void Normalize()
	{
		float m = GetLength();
		x/=m;
		y/=m;
	}
};

template<typename T>
Vector2D<T> operator + (const Vector2D<T>& A,const Vector2D<T>& B)
{
	return Vector2D<T>(A.x + B.x,A.y + B.y);
}

template<typename T>
Vector2D<T> operator - (const Vector2D<T>& A,const Vector2D<T>& B)
{
	return Vector2D<T>(A.x - B.x,A.y - B.y);
}

template<typename T>
Vector2D<T> operator - (const Vector2D<T>& A)
{
	return Vector2D<T>(-A.x,-A.y);
}


template<typename T>
Vector2D<T> operator * (const Vector2D<T>& A,const Vector2D<T>& B)
{
	return Vector2D<T>(A.x * B.x,A.y * B.y);
}

template<typename T>
Vector2D<T> operator / (const Vector2D<T>& A,const Vector2D<T>& B)
{
	return Vector2D<T>(A.x / B.x,A.y / B.y);
}

template<typename T>
Vector2D<T> operator * (const Vector2D<T>& A,const T&B)
{
	return Vector2D<T>(A.x * B,A.y * B);
}

template<typename T>
Vector2D<T> operator / (const Vector2D<T>& A,const T&B)
{
	return Vector2D<T>(A.x / B,A.y / B);
}

template<typename T>
Vector2D<T> & operator+= (Vector2D<T> & A,const Vector2D<T> & B)
{
    A.x+=B.x;
    A.y+=B.y;

    return A;
}

template<typename T>
Vector2D<T> & operator-= (Vector2D<T> & A,const Vector2D<T> & B)
{
    A.x-=B.x;
    A.y-=B.y;

    return A;
}

template<typename T>
Vector2D<T> & operator*= (Vector2D<T> & A,const Vector2D<T> & B)
{
    A.x*=B.x;
    A.y*=B.y;

    return A;
}

template<typename T>
Vector2D<T> & operator/= (Vector2D<T> & A,const Vector2D<T> & B)
{
    A.x/=B.x;
    A.y/=B.y;

    return A;
}

template<typename T,typename T2>
Vector2D<T> & operator*= (Vector2D<T> & A,const T2&B)
{
    A.x*=B;
    A.y*=B;

    return A;
}

template<typename T,typename T2>
Vector2D<T> & operator/= (Vector2D<T> & A,const T2&B)
{
    A.x/=B;
    A.y/=B;

    return A;
}

typedef Vector2D<float> vec2f;
typedef Vector2D<int> vec2i;

template<typename T>
int sign(const T&value)
{
	return value<0 ? -1 : 1;
}
inline int GetSnappedValue(int x)
{
    int r = x;
    int m = x%16;
    if (m>=8)
        r+=16-m;
    else
        r-=m;

    return r;
}

inline vec2i SnapToGrid(const vec2i&V)
{
    return vec2i(GetSnappedValue(V.x)/16,GetSnappedValue(V.y)/16);

}
