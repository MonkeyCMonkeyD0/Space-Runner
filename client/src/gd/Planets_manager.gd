extends Node

const MY_SCRIPT = preload("res://src/gd/Planet.gd")

var serverIP = IP.get_local_addresses()[0]
var rng = RandomNumberGenerator.new()
var network = NetworkedMultiplayerENet.new()
var textures = ["planet_1.jpg-35e81e9d2d54638791a9ce6ffe870764.stex", 
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

func test():
	var j = 0
	var cpt = 5
	var x
	var x_change
	var y
	var y_change
	var z
	var z_change
	var tmp
	var nodeID = 0
	for i in list_str:
		var planet : MeshInstance = MeshInstance.new()
		var newMaterial : SpatialMaterial = SpatialMaterial.new()
		x = ""
		x_change = true
		y = ""
		y_change = false
		z = ""
		z_change = false
		tmp = ""
		while tmp != ")":
			tmp = i[cpt]
			if tmp == ")":
				break
			if i[cpt] != ",":
				if x_change:
					x = x+i[cpt]
				if y_change:
					y = y+i[cpt]
				if z_change:
					z = z+i[cpt]
			else:
				if x_change:
					x_change = false
					y_change = true
				else:
					y_change = false
					z_change = true
			cpt = cpt + 1
		planet.name = "Planet_" + String(nodeID)
		newMaterial.albedo_color = Color(i[len(i)-15]+i[len(i)-14]+i[len(i)-13]+i[len(i)-12]+i[len(i)-11]+i[len(i)-10])
		newMaterial.metallic = float("0."+i[len(i)-4])
		newMaterial.roughness = float("0."+i[len(i)-1])
		newMaterial.albedo_texture = load("res://.import/"+textures[int(i[len(i)-7])-1])
		planet.material_override = newMaterial
		planet.transform.origin = Vector3(float(x),float(y),float(z))
		planet.mesh = SphereMesh.new()
		planet.scale = Vector3(4,4,4)
		planet.set_script(MY_SCRIPT)
		planet.create_convex_collision()
		add_child(planet)
		cpt = 5
		nodeID = nodeID+1

func _process(delta):
	if len(list_str)==NUMBER_PLANET:
		test()
		list_str=[]
