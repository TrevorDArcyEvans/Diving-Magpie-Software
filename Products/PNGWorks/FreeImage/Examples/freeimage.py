import FreeImagePy as FreeImage

# Example 1: load, convert and save a bitmap

i = FreeImage.LoadBMP('e:\projects\images\money-24bit.bmp')

if (FreeImage.GetBPP(i) != 24) :
	j = FreeImage.ConvertTo24Bits(i)

	FreeImage.Unload(i)

	i = j

FreeImage.SaveJPEG(i, 'test.jpeg')

FreeImage.Unload(i)

# Example 2: making use of FreeImage's alpha blending capabilities

i = freeimage.LoadBMP('e:\projects\images\money-24bit.bmp')
j = freeimage.LoadJPEG('e:\projects\images\\forsaken.jpg')

freeimage.Combine(i, j, 0, 0, 100)

freeimage.SaveBMP(i, 'test.bmp')

FreeImage.Unload(j)
FreeImage.Unload(i)
