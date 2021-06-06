extends MeshInstance

var sens = true
var ROT = 0.5

func _process(delta):
	if sens:
		if(rotation.x > 0):
			rotation.x -= delta*ROT
		else:
			sens = false	
	else:
		if(rotation.x < 1.57):
			rotation.x += delta*ROT
		else:
			sens = true
