# feedBack Piano

A lightweight JUCE 8 VST3 sampler plugin built for [feedBack](https://github.com/slopsmith/slopsmith-desktop). Loads Salamander Grand Piano samples from the VST3 bundle's `Contents/Resources/Salamander/` folder and makes them available as a serial-chain-safe instrument.

## Features

- Full 88-key range (A0–C8), 30 sampled notes with JUCE pitch-shifting between them
- Stereo output, stereo input bus declared for serial chain compatibility
- `Synthesiser::renderNextBlock` accumulates into the buffer — upstream audio in the chain is preserved
- 16-voice polyphony, sustain pedal support via JUCE `SamplerVoice`
- No UI, no external dependencies beyond JUCE and the bundled samples

## Build

Requirements: CMake ≥ 3.22, Visual Studio 2022, JUCE 8.

```bash
# Point CMakeLists.txt JUCE_PATH at your JUCE 8 checkout, then:
cmake -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
```

The built VST3 is at `build/feedback-piano_artefacts/Release/VST3/feedBack Piano.vst3`.

### Adding samples

Copy the v1 velocity layer FLAC files from Salamander Grand Piano into the bundle:

```
feedBack Piano.vst3/
  Contents/
    x86_64-win/
      feedBack Piano.vst3
    Resources/
      Salamander/
        A0v1.flac
        C1v1.flac
        ... (30 files total, see Source/PluginProcessor.cpp for full list)
```

## Credits

### Template

Plugin architecture adapted from [FreesoundSimpleSampler](https://github.com/ffont/FreesoundSimpleSampler) by Font and contributors, licensed under MIT. The Freesound API integration was removed; the JUCE `Synthesiser` / `SamplerSound` / `SamplerVoice` approach and project structure were used as a starting point.

### Samples

**Salamander Grand Piano V3** by Alexander Holm  
<https://github.com/sfzinstruments/SalamanderGrandPiano>  
Licensed under [Creative Commons Attribution 3.0](https://creativecommons.org/licenses/by/3.0/).

This plugin bundles the v1 velocity layer (30 FLAC files, 48 kHz / 24-bit) from the Salamander Grand Piano V3 release.

## License

MIT
