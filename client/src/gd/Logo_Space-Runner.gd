extends MeshInstance


# Declare member variables here. Examples:
var sens = true
var ROT = 0.5
# Called when the node enters the scene tree for the first time.
func _process(delta):
	if sens:
		if(rotation.x > 0.10):
			rotation.x -=delta*ROT
		else:
			sens = false	
	else:
		if(rotation.x < 1.57):
			rotation.x +=delta*ROT
		else:
			sens = true
		#if(rotation.x < 1.57):
		#	rotation.x += delta
		#else :
		#	if(rotation.x < 1.57):
		#		rotation.x +=delta
	


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
