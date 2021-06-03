extends Control

const menu = preload("res://src/gd/Menu.gd")
var menu_node = preload("res://src/tscn/Menu.tscn")

func _on_Quit_pressed() -> void:
	get_tree().quit()

func _on_Menu_pressed():
	if get_tree().change_scene("res://src/tscn/Menu.tscn") != OK:
		print("Unexpected error with the scene changement")

func _connect_from_game():
	#menu.network.create_client(menu.serverIP,menu.port)
	#get_tree().set_network_peer(menu.network)
	#menu.mplayer = get_tree().multiplayer
	print(menu)

func pull_save():
	var file = File.new()
	file.open("res://src/dat/save_game.dat", File.READ)
	var content = file.get_as_text()
	file.close()
	return content

func _ready():
	print("Entered in game")
	
	print(pull_save())

