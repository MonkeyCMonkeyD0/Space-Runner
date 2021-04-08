extends Spatial

var pos_x
var pos_y
var pos_z
var num
var path
var rng = RandomNumberGenerator.new()
var nodeId = 0

# Preloads script to be attached
const my_script = preload("res://godot/src/Planete.gd")

func _ready():  # Runs when scene is initialized
	rng.randomize()
	pos_x = rng.randi_range(-10, 10)
	pos_y = rng.randi_range(-10, 10)
	pos_z = rng.randi_range(-10, 10)
	var planete : MeshInstance = MeshInstance.new()
	planete.name = "Planete_" + String(nodeId)
	#nodeId += 1
	
	planete.mesh = SphereMesh.new()
	#var randomOffset = Vector3(randi() % 25 + 1, randi() % 25 + 1, randi() % 25 + 1)
	#planete.transform.origin = randomOffset
	#add_child(planete)
	#planete.mesh = SphereMesh.new()
	planete.transform.origin = Vector3(pos_x,pos_y,pos_z)
	#planete.transform.origin = Vector3(0,0,0)
	planete.set_script(my_script)
	add_child(planete)
	#var new_texture = ImageTexture.new()
	#num = rng.randi_range(1,6)
	#path = "res://data/img/colors/color"+str(num)+".png"
	#new_texture.load(path)
