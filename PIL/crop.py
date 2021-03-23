# PIL = Python Image Library

from PIL import Image
import sys

nameorig=sys.argv[1]
print (nameorig)

lx=[15,149,285,421,556,698,829,964]
ly=[3,138,274,410]
im_orig=Image.open(nameorig)
w,h = im_orig.size
print (w,h)
for y in range(4):
	for x in range(8):
		# 15, 149, 285, 421, 556
		#box=(x*135+15,y*135+3,x*135+15+122,y*135+3+122)
		box=(lx[x],ly[y],lx[x]+120,ly[y]+120)
		im_crop=im_orig.crop(box)
		im_resize=im_crop.resize((256,256))

		namesave="ressources/res4_%d%d.png"%(y,x)
		print (namesave)
		im_resize.save(namesave,"PNG")

