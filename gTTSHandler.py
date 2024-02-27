# This Python file uses the following encoding: utf-8

from gtts import gTTS

class gTTSHandler:
    def __init__(self):
        pass

    def make(self, text, path):
        tts = gTTS(text=text, lang='ko')
        tts.save(path)
