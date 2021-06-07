extends Node2D

var serverIP = IP.get_local_addresses()[0]
var rng = RandomNumberGenerator.new()
var network = NetworkedMultiplayerENet.new()
var list_str = []
var lObject = []
var port = 8080
var mplayer 
var mess

# Called when the node enters the scene tree for the first time.
func _ready():
	_connect_to_server()

func _connect_to_server():
	network.create_client(serverIP,port)
	get_tree().set_network_peer(network)
	mplayer = get_tree().multiplayer
	mplayer.connect("network_peer_packet",self,"_on_packet_received")
	print("Connected from items")

func sendToServer(player,string):
	player.send_bytes(string.to_ascii())

func _on_packet_received(id, packet):
	mess = packet.get_string_from_ascii()
	if mess[0] == '2':
		list_str.append(mess)
