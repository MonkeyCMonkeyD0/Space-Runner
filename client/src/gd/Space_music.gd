extends AudioStreamPlayer

var audioStream: AudioStream = preload("res://data/sound/space.wav")
 
func _ready() -> void:
	self.set_stream(audioStream)
	self.set_volume_db(2.0)
	self.play()
