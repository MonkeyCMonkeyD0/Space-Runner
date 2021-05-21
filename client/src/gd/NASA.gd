extends MeshInstance

var SPEED = 500
var SPEED_ROT = 2

func _process(delta):
	rotate_right(delta)

func rotate_right(delta) -> void:
	rotate_object_local(Vector3(0, 1, 0), SPEED_ROT * delta)



