extends Control


var lObject=[]
var Total_weight
var Total_profits
var finished
var Msg

var network
var mplayer
var serverIP = IP.get_local_addresses()[0]
var port = 4242
var player_id 

var username = ""
var username_valid = false
onready var popup1 = get_node("Background/Popup1")
onready var popup2 = get_node("Background/Popup2")
onready var popup3 = get_node("Background/Popup3")


# Declare member variables here. Examples:
# Player info, associate ID to data
var player_info = {}
# Info we send to other players
var my_info = { name = "Ton Daron" }

func _ready():
	print(serverIP)
	installNetworkCallback()
	_connect_to_server()

func installNetworkCallback():
	network=NetworkedMultiplayerENet.new()
	#if get_tree().connect("network_peer_connected",self,"_player_connected") != OK:
	#	print("Error while connect peer")
	#get_tree().connect("network_peer_disconnected",\
	#	self,"_player_disconnected")
	#get_tree().connect("connection_failed",self,\
	#	"_connected_fail")
	#get_tree().connect("server_disconnected",self,\
	#	"_server_disconnected")

func _connect_to_server():
	#if get_tree().connect("connected_to_server",self,"_connected_ok") != OK:
	#	print("Error connecting to server")
	network.create_client(serverIP,port)
	get_tree().set_network_peer(network)
	#player_id = get_tree().get_rpc_sender_id()
	mplayer=get_tree().multiplayer
	#network.connect("peer_connected",self,"_Peer_Connected")
	#network.connect("peer_disconnected",self,"_Peer_Disconnected")
	#mplayer.connect("network_peer_packet",self,"_on_packet_received")
	print("Connected to server")




#func _Peer_Connected(player_id):
#	print("User " + str(player_id) + " Connected")

func sendToServer(mess):
	mplayer.send_bytes(mess.to_ascii())

func _on_Host_pressed() -> void:
	if len(username)==0:
		popup1.hide()
		popup2.hide()
		popup3.show()
	if username_valid:
		Msg = "Hi I am "+ username + " and I am connected"
		sendToServer("Hello")
		if get_tree().change_scene("res://src/tscn/Game.tscn") != OK:
			print("Unexpected error with the scene changement")

func _on_Join_pressed() -> void:
	if len(username)==0:
		popup1.hide()
		popup2.hide()
		popup3.show()
	if username_valid:
		
		if get_tree().change_scene("res://src/tscn/Game.tscn") != OK:
			print("Unexpected error with the scene changement")


func _on_Username_text_entered(new_text) -> void:
	username = new_text
	if len(username) <= 10 && len(username) > 0:
		username_valid = true
		popup1.hide()
		popup3.hide()
		popup2.show()
	elif len(username) == 0:
		username_valid = false
		popup1.hide()
		popup2.hide()
		popup3.show()
	else:
		username_valid = false
		popup2.hide()
		popup3.hide()
		popup1.show()
		
func _on_Quit_pressed():
	get_tree().quit()
