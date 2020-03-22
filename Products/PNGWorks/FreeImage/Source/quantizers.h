// ==========================================================
// Quantizer objects and functions
//
// Design and implementation by Floris van den Berg
//
// This file is part of FreeImage
//
// Use at your own risk!
// ==========================================================

typedef unsigned char	uint8;
typedef unsigned short	uint16;
typedef unsigned long	uint32;
typedef long			int32;

typedef struct {
    int r0;			 // min value, exclusive
    int r1;			 // max value, inclusive
    int g0;  
    int g1;  
    int b0;  
    int b1;
    int vol;
} Box;


class WuQuantizer
{
  protected:
    float *gm2;
	int32 *wt, *mr, *mg, *mb;
	uint16 *Qadd;

	// DIB data
	uint16 width, height;
	uint16 pitch;
	void *m_dib;

  protected:
    void Hist3D(int32 *vwt, int32 *vmr, int32 *vmg, int32 *vmb, float *m2) ;
	void M3D(int32 *vwt, int32 *vmr, int32 *vmg, int32 *vmb, float *m2);
	int32 Vol(Box *cube, int32 *mmt);
	int32 Bottom(Box *cube, uint8 dir, int32 *mmt);
	int32 Top(Box *cube, uint8 dir, int pos, int32 *mmt);
	float Var(Box *cube);
	float Maximize(Box *cube, uint8 dir, int first, int last , int *cut,
				   int32 whole_r, int32 whole_g, int32 whole_b, int32 whole_w);
	bool Cut(Box *set1, Box *set2);
	void Mark(Box *cube, int label, uint8 *tag);

  public:
    WuQuantizer(void *dib);
	~WuQuantizer();
	void* Quantize();
};

