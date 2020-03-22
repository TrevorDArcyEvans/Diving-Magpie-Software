#ifndef _S3DMatrix_hpp
#define _S3DMatrix_hpp

class S3DVector;

class S3DMatrix
{
friend S3DVector operator * (const S3DVector& Vec,const S3DMatrix& Mat);

private:

	double m_11;
	double m_12;
	double m_13;
	double m_21;
	double m_22;
	double m_23;
	double m_31;
	double m_32;
	double m_33;

public:

	S3DMatrix ();

	void RotateAboutX (double Radians);
	void RotateAboutY (double Radians);
	void RotateAboutZ (double Radians);

	S3DMatrix operator * (const S3DMatrix& RVal) const;
	S3DMatrix operator ~ () const;

	double Determinant () const;
};//S3DMatrix

S3DVector operator * (const S3DVector& Vec,const S3DMatrix& Mat);

#endif


