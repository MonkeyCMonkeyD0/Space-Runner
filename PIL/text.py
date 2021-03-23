from PIL import Image, ImageFont, ImageDraw, ImageEnhance

source_img = Image.new(mode = 'RGB', size = (256,256 ), color = (20,20,128))
#source_img = Image.open("sci-fi-icon-11.png").convert("RGBA")

draw = ImageDraw.Draw(source_img)
font = ImageFont.truetype("bebas.ttf", 150)
w,h= draw.textsize("$503", font=font)
print (w,h)
draw.text((128-w/2, 128-h/2), "$503", font=font)
#draw.text((20, 70), "something123")

source_img.save("test.png", "png")
