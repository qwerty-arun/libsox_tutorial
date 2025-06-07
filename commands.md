# Convert mp3 to wav
sox input.mp3 output.wav

# Trim the first 10 seconds
sox input.wav output.wav trim 0 10

# Add fade in and fade out
sox input.wav output.wav fade t 3 0 3

# Increase volume by 3dB
sox input.wav output.wav vol 3dB

# Change pitch
sox input.wav output.wav pitch 300

# Create File
sox -V -r 48000 -n -b 16 -c 1 sawtooth_1k.wav synth 10 sawtooth 1000 vol 20 dB

# Sweep frequency and store in file:
sox -V -r 48000 -n -b 16 -c 1 sin1k_to_18k.wav synth 30 sin 1000+18000 vol 20dB

# Play mixed frequencies (here beats) :
play -V -r 44100 -n synth 30 square 1000 square 998 remix 1,2 channels 2

# Create spectrogram:
sox -V -r 44100 -n synth 10 sin 1000+20000 remix 1,2 spectrogram -o single_sin.png

# Remix signals and store in a file:
sox -V -r 48000 -n -b 16 -c 1 mixed_freq.wav synth 10 sin 1000 sin 990 sin 980 remix 1,2,3 channels 1 vol 20dB

# Output of lowpass filter and store it in a file:
sox mixed_freq.wav output_lowpass.wav lowpass  1000 0.707q

# Output of bandpass filter and store in a file:
sox mixed_freq.wav output_bandpass.wav bandpass -c



### 🔊 **Volume & Normalization**

```bash
sox input.wav output.wav vol 0.5        # Reduce volume to 50%
sox input.wav output.wav vol -3dB       # Reduce volume by 3 decibels
sox input.wav output.wav norm           # Normalize to 0 dB peak
sox input.wav output.wav gain -n -3     # Gain -3 dB, no clipping
```

---

### 🎚️ **EQ & Filtering**

```bash
sox input.wav output.wav lowpass 1000          # Low-pass filter at 1 kHz
sox input.wav output.wav highpass 500          # High-pass filter at 500 Hz
sox input.wav output.wav bandpass 1000 200     # Band-pass center 1kHz, width 200Hz
sox input.wav output.wav equalizer 1000 1q +6  # Boost 1kHz with Q=1 by +6dB
sox input.wav output.wav bass +6               # Boost bass
sox input.wav output.wav treble -3             # Cut treble
sox input.wav output.wav compand 0.3,1 6:-70,-60,-20 -5 -90 0.2
```

---

### 🎵 **Pitch & Tempo**

```bash
sox input.wav output.wav pitch 300     # Shift pitch up by 300 cents
sox input.wav output.wav pitch -300    # Shift pitch down
sox input.wav output.wav tempo 1.2     # Speed up tempo (keep pitch)
sox input.wav output.wav speed 1.5     # Speed up tempo & pitch
sox input.wav output.wav stretch 1.5   # Time-stretch (preserves pitch)
```

---

### 🔈 **Dynamics & Silence**

```bash
sox input.wav output.wav compand 0.3,1 6:-70,-60,-20 -5 -90 0.2   # Compress
sox input.wav output.wav silence 1 0.1 1% -1 2.0 1%                # Remove silence
```

---

### 🌈 **Creative FX**

```bash
sox input.wav output.wav reverb 50 50 100         # Reverb with wet/dry mix
sox input.wav output.wav chorus 0.7 0.9 55 0.4 0.25 2 -t
sox input.wav output.wav flanger
sox input.wav output.wav phaser 0.9 0.6 3.0 0.4 0.5 -t
sox input.wav output.wav overdrive 5              # Distortion
```

---

### 📈 **Spectrogram & Stats**

```bash
sox input.wav -n spectrogram -o spectro.png       # Generate spectrogram image
sox input.wav -n stat                             # Print audio statistics
sox input.wav output.wav rate 48000               # Change sample rate
```

---

### 🧹 **Noise Reduction**

```bash
sox noisy.wav -n trim 0 1 noiseprof noise.prof          # Capture noise profile
sox noisy.wav cleaned.wav noisered noise.prof 0.3       # Apply noise reduction
```
