extends MeshInstance

var rot_speed_x
var rot_speed_y
var rot_speed_z
var rng = RandomNumberGenerator.new()

func _ready():
	rng.randomize()
	rot_speed_x = rng.randf_range(-2.0, 2.0)
	rot_speed_y = rng.randf_range(-2.0, 2.0)
	rot_speed_z = rng.randf_range(-2.0, 2.0)	

func _process(delta):
	#rotate_x(rot_speed_x * delta)
	rotate_y(rot_speed_y * delta)
	#rotate_z(rot_speed_z * delta)
