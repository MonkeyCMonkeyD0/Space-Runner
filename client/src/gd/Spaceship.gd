extends MeshInstance

var SPEED = 500
var SPEED_ROT = 2

func _process(delta):
	if Input.is_key_pressed(KEY_SPACE):	
		move_forward(delta)
	if Input.is_key_pressed(KEY_RIGHT):
		rotate_right(delta)
	if Input.is_key_pressed(KEY_LEFT):
		rotate_left(delta)
	if Input.is_key_pressed(KEY_UP):
		rotate_up(delta)
	if Input.is_key_pressed(KEY_DOWN):
		rotate_down(delta)

func move_forward(delta) -> void:
	translation += transform.basis.x * SPEED * delta

func rotate_right(delta) -> void:
	rotate_object_local(Vector3(1, 0, 0), SPEED_ROT * delta)

func rotate_left(delta) -> void:
	rotate_object_local(Vector3(-1, 0, 0), SPEED_ROT * delta)

func rotate_up(delta) -> void:
	rotate_object_local(Vector3(0, 0, 1), SPEED_ROT * delta)

func rotate_down(delta) -> void:
	rotate_object_local(Vector3(0, 0, -1), SPEED_ROT * delta)
