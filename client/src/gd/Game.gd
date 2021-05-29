extends Control

const menu = preload("res://src/gd/Menu.gd")

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


# Called when the node enters the scene tree for the first time.
