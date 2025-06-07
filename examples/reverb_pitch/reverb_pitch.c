#include <sox.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s input.wav output.wav\n", argv[0]);
        return 1;
    }

    sox_format_t *in, *out;

    // Initialize SoX
    if (sox_init() != SOX_SUCCESS) {
        fprintf(stderr, "SoX init failed.\n");
        return 1;
    }

    // Open input file
    in = sox_open_read(argv[1], NULL, NULL, NULL);
    if (!in) {
        fprintf(stderr, "Failed to open input file.\n");
        return 1;
    }

    // Open output file with same signal and encoding
    out = sox_open_write(argv[2], &in->signal, &in->encoding, NULL, NULL, NULL);
    if (!out) {
        fprintf(stderr, "Failed to open output file.\n");
        sox_close(in);
        return 1;
    }

    // Create effect chain
    sox_effects_chain_t *chain = sox_create_effects_chain(&in->encoding, &out->encoding);
    sox_effect_t *effect;
    char *args[10];

    // Input effect
    effect = sox_create_effect(sox_find_effect("input"));
    args[0] = (char *)in;
    sox_effect_options(effect, 1, args);
    sox_add_effect(chain, effect, &in->signal, &in->signal);

    // Reverb effect
    effect = sox_create_effect(sox_find_effect("reverb"));
    char *reverb_args[] = { "50", "50", "100", "100", "0", "0" };  // default reverb settings
    sox_effect_options(effect, 6, reverb_args);
    sox_add_effect(chain, effect, &in->signal, &in->signal);

    // Pitch shift effect (e.g., +300 cents = 3 semitones up)
    effect = sox_create_effect(sox_find_effect("pitch"));
    char *pitch_args[] = { "300" };
    sox_effect_options(effect, 1, pitch_args);
    sox_add_effect(chain, effect, &in->signal, &in->signal);

    // Output effect
    effect = sox_create_effect(sox_find_effect("output"));
    args[0] = (char *)out;
    sox_effect_options(effect, 1, args);
    sox_add_effect(chain, effect, &in->signal, &in->signal);

    // Apply all effects
    sox_flow_effects(chain, NULL, NULL);

    // Clean up
    sox_delete_effects_chain(chain);
    sox_close(in);
    sox_close(out);
    sox_quit();

    printf("Done! Effects applied.\n");
    return 0;
}
