#!/bin/bash

mkdir -p output

echo "Generating Square Wave..."
sox -m \
  "|sox -n -r 44100 -c 1 -t wav - synth 3 sine 100 vol 20.0" \
  "|sox -n -r 44100 -c 1 -t wav - synth 3 sine 300 vol 6.66" \
  "|sox -n -r 44100 -c 1 -t wav - synth 3 sine 500 vol 4.0" \
  output/square_wave.wav

echo "Generating Sawtooth Wave..."
sox -m \
  "|sox -n -r 44100 -c 1 -t wav - synth 3 sine 100 vol 20.0" \
  "|sox -n -r 44100 -c 1 -t wav - synth 3 sine 200 vol 10.0" \
  "|sox -n -r 44100 -c 1 -t wav - synth 3 sine 300 vol 6.66" \
  output/sawtooth_wave.wav

echo "Generating Triangle Wave..."
sox -m \
  "|sox -n -r 44100 -c 1 -t wav - synth 3 sine 100 vol 20.0" \
  "|sox -n -r 44100 -c 1 -t wav - synth 3 sine 300 vol 2.222" \
  "|sox -n -r 44100 -c 1 -t wav - synth 3 sine 500 vol 0.8" \
  output/triangle_wave.wav

echo "Applying Filters..."
for wave in square sawtooth triangle; do
  sox output/${wave}_wave.wav output/${wave}_lowpass.wav lowpass 1000
  sox output/${wave}_wave.wav output/${wave}_highpass.wav highpass 1000
done

echo "Generating Spectrograms..."
for file in output/*.wav; do
  base=$(basename "$file" .wav)
  sox "$file" -n spectrogram -o output/"$base".png
done

echo "All done. Check the output folder."
