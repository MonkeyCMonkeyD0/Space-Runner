extends Control


var lObject=[]
var Total_weight
var Total_profits
var finished

var network
var mplayer
var serverIP = "192.168.1.91"

var username = ""
var username_valid = false
onready var popup1 = get_node("Background/Popup1")
onready var popup2 = get_node("Background/Popup2")
onready var popup3 = get_node("Background/Popup3")

# Declare member variables here. Examples:

func installNetworkCallback(serverAddress):
	network=NetworkedMultiplayerENet.new()
	network.create_client(serverAddress,4242)
	get_tree().set_network_peer(network)
	mplayer=get_tree().multiplayer
	mplayer.connect("network_peer_packet",self,"_on_packet_received")
	print("Connected to server")
	#mplayer.send_bytes("Connnndetesmorts".to_ascii)

func sendToServer(mess):
	mplayer.send_bytes(mess.to_ascii())

func _on_Host_pressed() -> void:
	if len(username)==0:
		popup1.hide()
		popup2.hide()
		popup3.show()
	if username_valid:
		installNetworkCallback(serverIP)
		sendToServer("I'm connected")
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
