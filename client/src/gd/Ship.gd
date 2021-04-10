extends MeshInstance

var SPEED = 5
var SPEED_ROT = 2
var theta = 0
var theta_bis = 0 # Va servir a bloquer l'angle
var phi = 0

func _process(delta):
	rotation.x = delta*theta_bis
	rotation.z = delta*phi
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
	translation.x += SPEED*delta*cos(delta*theta)*cos(delta*phi)
	translation.y += SPEED*delta*sin(delta*phi)
	translation.z += SPEED*delta*sin(delta*theta)*cos(delta*phi)

func rotate_right(delta) -> void:
	theta_bis += SPEED_ROT
	theta += SPEED_ROT
	if theta_bis>=44:
		theta_bis = 44
		rotation.y -= delta*SPEED_ROT
		theta -= delta*SPEED_ROT

func rotate_left(delta) -> void:
	theta_bis -= SPEED_ROT
	theta -= SPEED_ROT
	if theta_bis<=-44:
		theta_bis = -44
		rotation.y += delta*SPEED_ROT
		theta += delta*SPEED_ROT

func rotate_up(delta) -> void:
	if theta_bis > SPEED_ROT:
		rotate_left(delta)
	elif theta_bis < SPEED_ROT:
		rotate_right(delta)
	phi += SPEED_ROT
	if phi>=90:
		phi = 90

func rotate_down(delta) -> void:
	if theta_bis > SPEED_ROT:
		rotate_left(delta)
	elif theta_bis < SPEED_ROT:
		rotate_right(delta)
	phi -= SPEED_ROT
	if phi<=-90:
		phi = -90
