extends MeshInstance

var SPEED = 0.5
var theta
var run = false

func _process(delta):
	if Input.is_key_pressed(KEY_UP):
		translation.x += SPEED
	if Input.is_key_pressed(KEY_RIGHT):
		rotation.y += 0.005
	if Input.is_key_pressed(KEY_LEFT):
		rotation.y -= 0.005
	
	if Input.is_key_pressed(KEY_ENTER) && run == false:
		run = true
		theta = 0
	if run==true:
		theta += SPEED
		yield(get_tree().create_timer(0.1), "timeout")
		translation.x=4*sin(delta*theta)
		translation.z=4*cos(delta*theta)
		translation.y+=delta*0.5*SPEED
		rotation.y = theta*delta
		if theta > 374:
			run = false
