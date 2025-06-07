#include <sox.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s input.wav output.wav\n", argv[0]);
        return 1;
    }

    sox_format_t *in, *out;
    sox_init();

    in = sox_open_read(argv[1], NULL, NULL, NULL);
    if (!in) {
        fprintf(stderr, "Failed to open input file.\n");
        return 1;
    }

    out = sox_open_write(argv[2], &in->signal, &in->encoding, NULL, NULL, NULL);
    if (!out) {
        fprintf(stderr, "Failed to open output file.\n");
        sox_close(in);
        return 1;
    }

    sox_effects_chain_t * chain = sox_create_effects_chain(&in->encoding, &out->encoding);
    sox_effect_t *e;
    char *args[10];

    e = sox_create_effect(sox_find_effect("input"));
    args[0] = (char *)in;
    sox_effect_options(e, 1, args);
    sox_add_effect(chain, e, &in->signal, &in->signal);

    e = sox_create_effect(sox_find_effect("output"));
    args[0] = (char *)out;
    sox_effect_options(e, 1, args);
    sox_add_effect(chain, e, &in->signal, &in->signal);

    sox_flow_effects(chain, NULL, NULL);

    sox_delete_effects_chain(chain);
    sox_close(in);
    sox_close(out);
    sox_quit();

    return 0;
}
