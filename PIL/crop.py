# PIL = Python Image Library

from PIL import Image
import sys

nameorig=sys.argv[1]
print (nameorig)

im_orig=Image.open(nameorig)
w,h = im_orig.size
print (w,h)
for y in range(8):
	for x in range(14):
		box=(x*123,y*123,(x+1)*123,(y+1)*123)
		im_crop=im_orig.crop(box)

		namesave="ressources/res4_%d%d.png"%(y,x)
		print (namesave)
		im_crop.save(namesave,"PNG")

