extends MeshInstance

var menu = load("res://src/gd/Menu.gd")


var lObject=[]
var Total_weight
var Total_profits
var finished
var usr_sent = false

var network = NetworkedMultiplayerENet.new()
var mplayer 
var serverIP = IP.get_local_addresses()[0]
var port = 4242
var player_info = {}

var SPEED = 500
var SPEED_ROT = 2


func _ready():
	print(serverIP)
	_connect_to_server()
	#send_username(mplayer,"Aissam")


func send_username(Msg):
	var mess = "xxxxxxxx0"+Msg
	sendToServer(mplayer,mess)
	print("message_sent")
	usr_sent = true

func _process(delta):
	#if network.is_connected():
	send_username("Aissam")
		
	if Input.is_key_pressed(KEY_SPACE):	
		move_forward(delta)
	if Input.is_key_pressed(KEY_RIGHT):
		rotate_right(delta)
	if Input.is_key_pressed(KEY_LEFT):
		rotate_left(delta)
	if Input.is_key_pressed(KEY_UP):
		rotate_up(delta)
	if Input.is_key_pressed(KEY_DOWN):
		rotate_down(delta)
	#if Input.is_key_pressed(KEY_A):
		

func move_forward(delta) -> void:
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

remote func send_pos() -> void:
	sendToServer(mplayer,"xxxxxxxx0"+"Aissam123456")
	#rpc_unreliable("setPosition", global_transform.origin)
	#player_info['type'] = ""
	#rset(player_info['type'], "USERNAME_DECLARATION")
	#var id = get_tree().get_rpc_sender_id()
	# Store the info
	#print(id)
	#player_info[id] = "name"
		#if (event.get_event_type() == GDNetEvent.RECEIVE):
		#	print(event.get_var())

func _connect_to_server():
	network.create_client(serverIP,port)
	get_tree().set_network_peer(network)
	mplayer = get_tree().multiplayer
	print("Connected to server")
