extends AudioStreamPlayer

var audioStream: AudioStream = preload("res://data/sound/!acceleration.wav")
 
func _ready() -> void:
	self.set_stream(audioStream)
	self.set_volume_db(-5.0)
	self.play()
