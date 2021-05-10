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

func _connect_to_server():
	network.create_client(serverIP,port)
	get_tree().set_network_peer(network)
	mplayer=get_tree().multiplayer
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
		sendToServer(Msg)
		if get_tree().change_scene("res://src/tscn/Game.tscn") != OK:
			print("Unexpected error with the scene changement")

func _on_Join_pressed() -> void:
	if len(username)==0:
		popup1.hide()
		popup2.hide()
		popup3.show()
	if username_valid:
		#mplayer.send_bytes(my_info)
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

# Appling texture to veiwport
func _process(delta):
	var texture = $Viewport.get_texture()
	$Background/Logo.texture = texture
