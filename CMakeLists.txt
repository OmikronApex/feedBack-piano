cmake_minimum_required(VERSION 3.22)
project(feedback-piano VERSION 1.0.0)

set(JUCE_PATH "C:/Users/rkasp/PycharmProjects/slopsmith-desktop/JUCE" CACHE PATH "Path to JUCE" FORCE)
if(NOT EXISTS "${JUCE_PATH}/CMakeLists.txt")
    message(FATAL_ERROR "JUCE not found at ${JUCE_PATH}")
endif()
add_subdirectory("${JUCE_PATH}" "${CMAKE_BINARY_DIR}/JUCE" EXCLUDE_FROM_ALL)

juce_add_plugin(feedback-piano
    COMPANY_NAME "feedBack"
    PLUGIN_MANUFACTURER_CODE Fbck
    PLUGIN_CODE Fpno
    FORMATS VST3
    PRODUCT_NAME "feedBack Piano"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    COPY_PLUGIN_AFTER_BUILD FALSE
    VST3_CATEGORIES "Instrument" "Sampler"
)

juce_generate_juce_header(feedback-piano)

target_sources(feedback-piano PRIVATE
    Source/PluginProcessor.cpp
)

target_compile_definitions(feedback-piano PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_USE_FLAC=1
)

target_link_libraries(feedback-piano PRIVATE
    juce::juce_audio_utils
    juce::juce_audio_plugin_client
    juce::juce_audio_processors
    juce::juce_audio_formats
    juce::juce_audio_basics
    juce::juce_core
    juce::juce_events
    juce::juce_data_structures
PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
)
