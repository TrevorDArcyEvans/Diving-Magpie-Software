#ifndef _S2DArray_hpp
#define _S2DArray_hpp

template <class T>
class S2DArray
{
private:

	int		m_Width;
	int		m_Height;
	int		m_MinX;
	int		m_MinY;
	T*		m_Elements;
	T		m_Dummy;

public:

	S2DArray (int Width,int Height)
	:m_Width (Width),m_Height (Height),m_MinX (0),m_MinY (0)
	{
		m_Elements = new T[m_Width * m_Height];
	}

	S2DArray (int MinX,int MaxX,int MinY,int MaxY)
	:m_Width (MaxX - MinX + 1),m_Height (MaxY - MinY + 1),m_MinX (MinX),m_MinY (MinY)
	{
		m_Elements = new T[m_Width * m_Height];
	}

	virtual ~S2DArray () {delete [] m_Elements;}

	void Initialize (T& InitVal) 
	{
		for (int i = 0; i < (m_Width * m_Height); i++)
			m_Elements[i] = InitVal;
		//for
	}

	const T& Ele (int x,int y) const 
	{
		x -= m_MinX;
		y -= m_MinY;

		if (x < m_Width && y < m_Height)
			return m_Elements[x + y * m_Width];
		else
			return m_Dummy;
		//if
	}

	T& Ele (int x,int y)
	{
		x -= m_MinX;
		y -= m_MinY;

		if (x < m_Width && y < m_Height)
			return m_Elements[x + y * m_Width];
		else
			return m_Dummy;
		//if
	}

	int Width () const {return m_Width;}
	int Height () const {return m_Height;}

	int MinX () const {return m_MinX;}
	int MinY () const {return m_MinY;}
	int MaxX () const {return m_MinX + m_Width - 1;}
	int MaxY () const {return m_MinY + m_Height - 1;}
};//S2DArray

#endif



