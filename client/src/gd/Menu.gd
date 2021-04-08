extends Control

var username = ""
var username_valid = false
onready var popup1 = get_node("Background/Popup1")
onready var popup2 = get_node("Background/Popup2")
onready var popup3 = get_node("Background/Popup3")

func _ready():
	pass
	
func _on_Host_pressed() -> void:
	if len(username)==0:
		popup1.hide()
		popup2.hide()
		popup3.show()
	if username_valid:
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

func _on_Quit_pressed() -> void:
	get_tree().quit()

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
