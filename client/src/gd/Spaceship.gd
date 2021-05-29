extends MeshInstance

onready var Click = get_node("Click_sound")
onready var acceleration = get_node("Acceleration_sound")
onready var not_acceleration = get_node("!Acceleration_sound")

var menu = load("res://src/gd/Menu.gd")

var lObject=[]
var Total_weight
var Total_profits
var finished
var usr_sent = false

var network = NetworkedMultiplayerENet.new()
var mplayer 
#var serverIP = "10.64.9.3"
var serverIP = IP.get_local_addresses()[0]
var port = 4242
var player_info = {}

var SPEED = 500
var SPEED_ROT = 2

func _ready():
	print(serverIP)
	_connect_to_server()
	#send_username("Aissam")
	acceleration.playing = false
	not_acceleration.playing = false

func _process(delta):
	#if network.is_connected():
	#send_username("Aissam")
		
	if Input.is_key_pressed(KEY_SPACE):	
		move_forward(delta)
	else:
		if acceleration.playing:
			acceleration.stop()
			not_acceleration.play()
	
	if Input.is_key_pressed(KEY_RIGHT):
		rotate_right(delta)
	if Input.is_key_pressed(KEY_LEFT):
		rotate_left(delta)
	if Input.is_key_pressed(KEY_UP):
		rotate_up(delta)
	if Input.is_key_pressed(KEY_DOWN):
		rotate_down(delta)
	if Input.is_key_pressed(KEY_A):
		send_username("Nawelle")
	if Input.is_key_pressed(KEY_B):
		send_pos()
		
func move_forward(delta) -> void:
	
	if not_acceleration.playing:
		not_acceleration.stop()
		acceleration.play()
	translation += transform.basis.x * SPEED * delta
	
func rotate_right(delta) -> void:
	rotate_object_local(Vector3(1, 0, 0), SPEED_ROT * delta)

func rotate_left(delta) -> void:
	rotate_object_local(Vector3(-1, 0, 0), SPEED_ROT * delta)

func rotate_up(delta) -> void:
	rotate_object_local(Vector3(0, 0, 1), SPEED_ROT * delta)

func rotate_down(delta) -> void:
	rotate_object_local(Vector3(0, 0, -1), SPEED_ROT * delta)

############################################################

func setPosition(Pos):
	translation.x = Pos.x
	translation.y = Pos.y
	translation.z = Pos.z

func sendToServer(player,mess):
	print(mess)
	player.send_bytes(mess.to_ascii())

func send_username(Msg):
	var mess = "xxxxxxxx0"+Msg
	sendToServer(mplayer,mess)
	
func send_pos():
	#-- Plus facile à traiter pour l'envoi d'entiers
	var pos_x = stepify(translation.x,0.00001)
	var Msg = String(pos_x)
	var mess = "xxxxxxxx5"+String((len(Msg)+3)*pos_x)
	sendToServer(mplayer,mess)

func _connect_to_server():
	network.create_client(serverIP,port)
	get_tree().set_network_peer(network)
	mplayer = get_tree().multiplayer
	print("Connected to server")

func round_to_dec(num, digit):
	return round(num * pow(10.0, digit)) / pow(10.0, digit)
