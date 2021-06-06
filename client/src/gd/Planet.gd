extends MeshInstance

#var texture00 = preload("res://data/img/objets/res4_00.png")
#var popup1 : Popup = Popup.new()
#var popup2 : Popup = Popup.new()
#var popup3 : Popup = Popup.new()
#var popup4 : Popup = Popup.new()
#var sprite1 : Sprite = Sprite.new()
#var sprite2 : Sprite = Sprite.new()
#var sprite3 : Sprite = Sprite.new()
#var sprite4 : Sprite = Sprite.new()
var rng = RandomNumberGenerator.new()
var rot_speed_x
var rot_speed_y
var rot_speed_z

func _ready():
	rng.randomize()
	rot_speed_x = rng.randf_range(-2.0, 2.0)
	rot_speed_y = rng.randf_range(-2.0, 2.0)
	rot_speed_z = rng.randf_range(-2.0, 2.0)

func _process(delta):
	rotate_x(rot_speed_x * delta)
	rotate_y(rot_speed_y * delta)
	rotate_z(rot_speed_z * delta)
