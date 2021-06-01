extends AudioStreamPlayer

var audioStream: AudioStream = preload("res://data/sound/menu.wav")
 
func _ready() -> void:
	self.set_stream(audioStream)
	self.set_volume_db(3.0)
	self.play()
