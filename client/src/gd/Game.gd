extends Control

func _on_Quit_pressed() -> void:
	get_tree().quit()

func _on_Menu_pressed():
	if get_tree().change_scene("res://src/tscn/Menu.tscn") != OK:
		print("Unexpected error with the scene changement")
