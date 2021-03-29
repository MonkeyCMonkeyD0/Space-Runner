extends MeshInstance


# Declare member variables here. Examples:
# var a = 2
# var b = "text"
var SPEED = 10

# Called when the node enters the scene tree for the first time.
func _ready():
	pass
	
	
func _process(delta):
	if Input.is_action_pressed("ui_right"):
		translation.x+=delta*SPEED
	if Input.is_action_pressed("ui_left"):
		translation.x-=delta*SPEED
	if Input.is_action_pressed("ui_down"):
		translation.z+=delta*SPEED
	if Input.is_action_pressed("ui_up"):
		translation.z-=delta*SPEED
	if Input.is_key_pressed(65):
		translation.y+=delta*SPEED
	if Input.is_key_pressed(90):
		translation.y-=delta*SPEED
 # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
