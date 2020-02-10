#include <janet.h>
#include "base64.h"
#include "hmac.h"

static Janet decode(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);

  const uint8_t *str = janet_getstring(argv, 0);
  int b64_len = Base64decode_len((char *)str);

  char out[b64_len];
  int out_len = Base64decode(out, (char *)str);

  return janet_stringv((const uint8_t *)out, out_len);
}

static Janet encode(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);

  const uint8_t *str = janet_getstring(argv, 0);
  int len = janet_string_length(str);
  int b64_len = Base64encode_len(len);

  char out[b64_len];

  Base64encode(out, (char *)str, len);

  return janet_stringv((const uint8_t *)out, b64_len - 1);
}

static Janet c_hmac_sha1(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);

  const uint8_t *secret = janet_getstring(argv, 0);
  const uint8_t *payload = janet_getstring(argv, 1);

  JanetBuffer *buffer = janet_buffer(20);
  char hexresult[41];
  size_t offset;

  hmac_sha1(secret, janet_string_length(secret), payload, janet_string_length(payload), buffer->data, (size_t *)&buffer->count);

  for( offset = 0; offset < 20; offset++) {
    sprintf( ( hexresult + (2*offset)), "%02x", buffer->data[offset]&0xff);
  }

  return janet_stringv((const uint8_t *)hexresult, (sizeof(hexresult) / sizeof(char)) - 1);
}

static const JanetReg cfuns[] = {
  {"encode", encode, "(codec/encode str)\n\nBase64 encodes a string."},
  {"decode", decode, "(codec/decode base64-encoded-str)\n\nDecodes a base64 encoded string."},
  {"hmac-sha1", c_hmac_sha1, "(codec/hmac-sha1 \"secret\" \"payload\")\n\nPerforms a sha1 hmac digest on payload with the given secret"},
  {NULL, NULL, NULL}
};

JANET_MODULE_ENTRY(JanetTable *env) {
  janet_cfuns(env, "codec", cfuns);
}
