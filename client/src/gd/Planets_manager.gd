extends Node

var nodeId
var pos_x
var pos_y
var pos_z
var rng = RandomNumberGenerator.new()

const MY_SCRIPT = preload("res://src/gd/Planet.gd")
const NUMBER_PLANET = 20

func _ready() -> void:
	rng.randomize() # On randomise

	for i in range(NUMBER_PLANET):
		nodeId = i
		# Generation d'eniter aléatoire compris dans un intervale
		pos_x = rng.randi_range(-50,50)
		pos_y = rng.randi_range(0,50)
		pos_z = rng.randi_range(-50,50)
		# Creation d'une MeshInstance

		var planet : MeshInstance = MeshInstance.new()
		var newMaterial : SpatialMaterial = SpatialMaterial.new()
		
		#Random Planet Material
		newMaterial.albedo_color = Color(rng.randf_range(0,5), rng.randf_range(0,5), rng.randf_range(0,5), rng.randf_range(0,5))
		newMaterial.metallic = rng.randf_range(0,1)
		planet.material_override = newMaterial
		# Mesh de type Sphere
		planet.mesh = SphereMesh.new()
		# Nom du MeshInstance
		planet.name = "Planet_" + String(nodeId)
		# Position du MeshInstance Vector3 prend des int en argument
		planet.transform.origin = Vector3(pos_x,pos_y,pos_z)
		# Scale du MeshInstance
		planet.scale = Vector3(4,4,4)
		# Scrpit associer au MeshIstance
		planet.set_script(MY_SCRIPT)
		# On ajoute le meshInstance planet au noeud courant (Planet_manager)
		planet.create_convex_collision()
		add_child(planet)
