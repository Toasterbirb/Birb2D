# Audio
<details>
	<summary>bool Audio::initAudio(int flags)</summary>

Initializes the SDL_mixer library. Needs to be called before any other audio features are used
</details>
<details>
	<summary>MusicFile::MusicFile(std::string p_filePath)</summary>

Loads up a music file from given path. Shouldn't be used for short sound effects
</details>
<details>
	<summary>SoundFile::SoundFile(std::string p_filePath)</summary>

Loads up a sound file from given path. Used for shorter sound effects and not music
</details>
