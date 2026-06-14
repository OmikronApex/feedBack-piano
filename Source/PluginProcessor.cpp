#include "PluginProcessor.h"

// Salamander Grand Piano v3 — v1 velocity layer sample map
// Each entry: { filename, rootMidiNote, loNote, hiNote }
struct SampleEntry { const char* filename; int root, lo, hi; };
static const SampleEntry kSamples[] = {
    { "A0v1.flac",  21,  21,  22 },
    { "C1v1.flac",  24,  23,  25 },
    { "D#1v1.flac", 27,  26,  28 },
    { "F#1v1.flac", 30,  29,  31 },
    { "A1v1.flac",  33,  32,  34 },
    { "C2v1.flac",  36,  35,  37 },
    { "D#2v1.flac", 39,  38,  40 },
    { "F#2v1.flac", 42,  41,  43 },
    { "A2v1.flac",  45,  44,  46 },
    { "C3v1.flac",  48,  47,  49 },
    { "D#3v1.flac", 51,  50,  52 },
    { "F#3v1.flac", 54,  53,  55 },
    { "A3v1.flac",  57,  56,  58 },
    { "C4v1.flac",  60,  59,  61 },
    { "D#4v1.flac", 63,  62,  64 },
    { "F#4v1.flac", 66,  65,  67 },
    { "A4v1.flac",  69,  68,  70 },
    { "C5v1.flac",  72,  71,  73 },
    { "D#5v1.flac", 75,  74,  76 },
    { "F#5v1.flac", 78,  77,  79 },
    { "A5v1.flac",  81,  80,  82 },
    { "C6v1.flac",  84,  83,  85 },
    { "D#6v1.flac", 87,  86,  88 },
    { "F#6v1.flac", 90,  89,  91 },
    { "A6v1.flac",  93,  92,  94 },
    { "C7v1.flac",  96,  95,  97 },
    { "D#7v1.flac", 99,  98, 100 },
    { "F#7v1.flac", 102, 101, 103 },
    { "A7v1.flac",  105, 104, 106 },
    { "C8v1.flac",  108, 107, 108 },
};

SlopsmithPianoProcessor::SlopsmithPianoProcessor()
    : AudioProcessor(BusesProperties()
        .withInput ("Input",  juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
    formatManager.registerBasicFormats();
}

SlopsmithPianoProcessor::~SlopsmithPianoProcessor() {}

void SlopsmithPianoProcessor::loadSamples()
{
    sampler.clearVoices();
    sampler.clearSounds();

    for (int i = 0; i < 16; ++i)
        sampler.addVoice(new juce::SamplerVoice());

    juce::File dllFile = juce::File::getSpecialLocation(
        juce::File::SpecialLocationType::currentExecutableFile);
    juce::File samplesDir = dllFile
        .getParentDirectory()   // x86_64-win
        .getParentDirectory()   // Contents
        .getChildFile("Resources")
        .getChildFile("Salamander");

    for (auto& entry : kSamples)
    {
        juce::File f = samplesDir.getChildFile(entry.filename);
        if (!f.exists()) continue;

        std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(f));
        if (!reader) continue;

        juce::BigInteger range;
        range.setRange(entry.lo, entry.hi - entry.lo + 1, true);

        sampler.addSound(new juce::SamplerSound(
            entry.filename, *reader, range, entry.root,
            0.01,  // attack
            0.5,   // release
            30.0   // max sample length
        ));
    }
}

void SlopsmithPianoProcessor::prepareToPlay(double sampleRate, int)
{
    sampler.setCurrentPlaybackSampleRate(sampleRate);
    loadSamples();
}

void SlopsmithPianoProcessor::releaseResources() {}

bool SlopsmithPianoProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void SlopsmithPianoProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi)
{
    // renderNextBlock ADDS to buffer — serial chain safe, no clear needed
    sampler.renderNextBlock(buffer, midi, 0, buffer.getNumSamples());
}

juce::AudioProcessorEditor* SlopsmithPianoProcessor::createEditor() { return nullptr; }

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SlopsmithPianoProcessor();
}
