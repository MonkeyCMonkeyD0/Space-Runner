extends MeshInstance

var SPEED = 5
var SPEED_ROT = 2
var theta = 0

func _process(delta):
	if Input.is_key_pressed(KEY_SPACE):	
		move_forward(delta)
	if Input.is_key_pressed(KEY_RIGHT):
		rotate_right(delta)
	elif Input.is_key_pressed(KEY_LEFT):
		rotate_left(delta)
	elif Input.is_key_pressed(KEY_UP):
		rotate_up(delta)
	elif Input.is_key_pressed(KEY_DOWN):
		rotate_down(delta)

func move_forward(delta) -> void:
	translation.x += SPEED*delta*cos(rotation.y)*cos(rotation.x)
	translation.y += SPEED*delta*sin(rotation.z)
	translation.z += SPEED*delta*sin(rotation.y)*cos(rotation.x)

func rotate_right(delta) -> void:
	# rotation.x -= 0.02
	rotate_object_local(Vector3(1, 0, 0), -0.02)
	# print("rot z : ", rotation.z)
	# rotation.z += SPEED_ROT*delta

func rotate_left(delta) -> void:
	# rotation.x += 0.02
	rotate_object_local(Vector3(1, 0, 0), 0.02)
	# print("rot z : ", rotation.z)
	# rotation.z -= SPEED_ROT*delta

func rotate_up(delta) -> void:
	# rotation.z -= 0.01
	rotate_object_local(Vector3(0, 0, 1), -0.02)
	# print("rot y : ", rotation.y)
	# rotation.x += SPEED_ROT*delta
	# print("rot x : ", rotation.x, "\t-\trot y : ", rotation.y)
	# rotation.x -= SPEED_ROT*delta*cos(rotation.z)
	# rotation.y -= SPEED_ROT*delta*sin(rotation.z)

func rotate_down(delta) -> void:
	# rotation.z += 0.01
	rotate_object_local(Vector3(0, 0, 1), 0.02)
	# print("rot y : ", rotation.y)
	# rotation.x -= SPEED_ROT*delta
	# print("rot x : ", rotation.x, "\t-\trot y : ", rotation.y)
	# rotation.x += SPEED_ROT*delta*cos(rotation.z)
	# rotation.y += SPEED_ROT*delta*sin(rotation.z)
