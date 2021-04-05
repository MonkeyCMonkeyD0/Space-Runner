extends MeshInstance

var SPEED = 1
var SPEED_ROT = 2*SPEED
var theta = 0
var theta_bis = 0 # Va servir a bloquer l'angle
var phi = 0
var run = false

	

func _process(delta):
	rotation.x = delta*theta_bis
	rotation.z = delta*phi
	if Input.is_key_pressed(KEY_SPACE):	
		translation.x += 3*SPEED*delta*cos(delta*theta)*cos(delta*phi)
		translation.y += 3*SPEED*delta*sin(delta*phi)
		translation.z += 3*SPEED*delta*sin(delta*theta)*cos(delta*phi)
	if Input.is_key_pressed(KEY_RIGHT):
		theta_bis += SPEED_ROT
		theta += SPEED_ROT
		if theta_bis>45:
			theta_bis = 45
			rotation.y -= delta*SPEED_ROT
			theta -= delta*SPEED_ROT
	if Input.is_key_pressed(KEY_LEFT):
		theta_bis -= SPEED_ROT
		theta -= SPEED_ROT
		if theta_bis<-45:
			theta_bis = -45
			rotation.y += delta*SPEED_ROT
			theta += delta*SPEED_ROT
	if Input.is_key_pressed(KEY_UP):
		phi += SPEED_ROT
		if phi>25:
			phi = 25
	if Input.is_key_pressed(KEY_DOWN):
		phi -= SPEED_ROT
		if phi<-25:
			phi = -25

	#if Input.is_key_pressed(KEY_ENTER) && run == false:
	#	run = true
	#	theta = 0
	#if run==true:
	#	theta += SPEED
	#	yield(get_tree().create_timer(0.1), "timeout")
	#	translation.x=4*sin(delta*theta)
	#	translation.z=4*cos(delta*theta)
	#	translation.y+=delta*0.5*SPEED
	#	rotation.y = theta*delta
	#	if theta > 374:
	#		run = false
