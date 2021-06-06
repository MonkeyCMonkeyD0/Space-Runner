extends Node

const MY_SCRIPT = preload("res://src/gd/Planet.gd")

var serverIP = IP.get_local_addresses()[0]
var rng = RandomNumberGenerator.new()
var network = NetworkedMultiplayerENet.new()
var colors = ["planet_1.jpg-35e81e9d2d54638791a9ce6ffe870764.stex", 
"planet_2.jpg-468c21c4322bd70e78ac2dac96c1920c.stex",
"planet_3.jpg-3970e1c4179e15bf647a17a82339f1d4.stex",
"planet_4.jpg-05c14bd63956c59fbdfaf5dfffd20d11.stex",
"planet_5.jpg-69409df79733ee5c1851966d0717a015.stex",
"planet_6.jpg-ff1fc805ccf7d025ee8f34e1016d8746.stex",
"planet_7.jpg-5db5d1b954837bf23ca9bcd96e0ff6c6.stex",
"planet_8.jpg-358e609a652c520c6ad3405ff96aca24.stex",
"planet_9.jpg-5740a9f998c087287daba6a5fb78c5b8.stex"]
var list_str = []
var port = 8080
var nodeId
var pos_x
var pos_y
var pos_z
var mplayer 
var mess

const NUMBER_PLANET = 20

func wait(sec):
	var t = Timer.new()
	t.set_wait_time(sec)
	t.set_one_shot(true)
	self.add_child(t)
	t.start()
	yield(t, "timeout")

func _ready() -> void:
	_connect_to_server()
	rng.randomize() # On randomise
	
func _connect_to_server():
	network.create_client(serverIP,port)
	get_tree().set_network_peer(network)
	mplayer = get_tree().multiplayer
	mplayer.connect("network_peer_packet",self,"_on_packet_received")
	print("Connected from planete")

func sendToServer(player,string):
	player.send_bytes(string.to_ascii())

func _on_packet_received(id, packet):
	mess = packet.get_string_from_ascii()
	if mess[0] == '1':
		list_str.append(mess)
		print(mess)
		
func set_planet():
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
		newMaterial.albedo_texture = load("res://.import/planet_5.jpg-69409df79733ee5c1851966d0717a015.stex")
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

func set_planets():
	var j = 0
	for i in list_str:
		var planet : MeshInstance = MeshInstance.new()
		var newMaterial : SpatialMaterial = SpatialMaterial.new()
		nodeId = j
		# Nom de la planete
		planet.name = "Planet_" + String(nodeId)
		# Style de la planete
		newMaterial.albedo_color = Color(rng.randf_range(0,5), rng.randf_range(0,5), rng.randf_range(0,5), rng.randf_range(0,5))
		newMaterial.metallic = rng.randf_range(0,1)
		newMaterial.albedo_texture = colors[6]
		planet.material_override = newMaterial
		# Mesh de type Sphere
		planet.mesh = SphereMesh.new()
		# Nom du MeshInstance
		j = j + 1

func test():
	var j = 0
	for i in list_str:
		print(list_str[j])
		j = j + 1

func _process(delta):
	if len(list_str)==NUMBER_PLANET:
		test()
		list_str=[]
