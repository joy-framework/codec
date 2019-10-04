#include <janet.h>
#include "base64.h"

static Janet decode(int32_t argc, const Janet *argv) {
  janet_fixarity(argc, 1);

  const uint8_t *str = janet_getstring(argv, 0);
  int b64_len = Base64decode_len((char *)str);

  char out[b64_len];
  int out_len = Base64decode(out, (char *)str);

  return janet_stringv((const uint8_t *)out, out_len);
}

static Janet encode(int32_t argc, const Janet *argv) {
  janet_fixarity(argc, 1);

  const uint8_t *str = janet_getstring(argv, 0);
  int len = janet_string_length(str);
  int b64_len = Base64encode_len(len);

  char out[b64_len];

  Base64encode(out, (char *)str, len);

  return janet_stringv((const uint8_t *)out, b64_len);
}

static const JanetReg cfuns[] = {
  {"encode", encode, "(codec/encode str)\n\nBase64 encodes a string."},
  {"decode", decode, "(codec/decode base64-encoded-str)\n\nDecodes a base64 encoded string."},
  {NULL, NULL, NULL}
};

JANET_MODULE_ENTRY(JanetTable *env) {
  janet_cfuns(env, "codec", cfuns);
}
