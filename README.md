
# DJ-Mix

**DJ-Mix** is a dynamic DJ-ing application built using the [JUCE framework](https://juce.com/), offering an intuitive and interactive interface for music mixing. It allows users to load audio files, mix them in real time, adjust track parameters like volume and tempo, and create seamless audio transitions.

## Features

- **Audio File Loading**: Import audio tracks for mixing.
- **Volume Control**: Adjust the volume of each track.
- **Tempo Control**: Change the speed of tracks to match the beats.
- **Crossfading**: Transition smoothly between tracks.
- **Real-time Playback**: Mix music tracks live with instant feedback.
- **Interactive UI**: User-friendly interface for seamless music creation.

## Requirements

Before running the project, ensure you have the following installed:

- JUCE framework: [Download JUCE](https://juce.com/get-juce)
- C++ development environment (Visual Studio, Xcode, etc.)
- An audio interface and speakers or headphones for output

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/Moumita-Mou/DJ-Mix.git
   ```

2. Open the project in your preferred IDE that supports JUCE (e.g., Visual Studio, Xcode).

3. Build the project using your IDE's build system.

4. Run the application, and you will be able to start loading audio files for mixing.

## How to Use

1. **Load Tracks**: Start by loading two audio tracks into the app.
2. **Adjust Settings**: Control the volume and tempo for each track.
3. **Mix Tracks**: Use the crossfader to transition between the tracks smoothly.
4. **Real-Time Output**: Hear your mix in real time as you control the tracks.

## Built With

- **JUCE Framework**: A powerful and flexible C++ framework for audio application development. Learn more at [juce.com](https://juce.com/).
  
## Current Status

The app is functional for basic mixing tasks, with room for future enhancements:

- Adding more advanced effects (e.g., reverb, equalizer).
- Enabling support for MIDI controllers.
- Providing enhanced UI/UX for a professional-level DJ experience.

## Future Enhancements

- **MIDI Integration**: Add support for DJ controllers and external devices.
- **FX Effects**: Implement real-time audio effects like echo, reverb, and filters.
- **Recording**: Enable live recording of DJ sessions for export.
- **Expanded UI**: Improve the graphical interface for a more immersive experience.

## Troubleshooting

1. **No audio output**:
   - Ensure your audio interface or speakers are properly configured.
   - Check the volume settings inside the app.

2. **Crashes or errors**:
   - Ensure the JUCE framework is installed correctly and all dependencies are set up in your IDE.
   - If you encounter issues with specific audio file formats, ensure the files are supported (e.g., .mp3, .wav).
