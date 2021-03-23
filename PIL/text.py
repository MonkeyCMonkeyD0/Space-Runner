from PIL import Image, ImageFont, ImageDraw, ImageEnhance

source_img = Image.new(mode = 'RGB', size = (256,256 ), color = (0,0,0))
#source_img = Image.open("sci-fi-icon-11.png").convert("RGBA")

draw = ImageDraw.Draw(source_img)
font = ImageFont.truetype("bebas.ttf", 50)
#draw.rectangle(((0, 00), (100, 100)), fill="black")
draw.text((20, 70), "MAIN4", font=font)
#draw.text((20, 70), "something123")

source_img.save("test.png", "png")
