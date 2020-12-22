#include <janet.h>
#include "base64.h"
#include "picohash.h"

#define PICOHASH_MD5_HEX_LENGTH 32
#define PICOHASH_SHA1_HEX_LENGTH 40
#define PICOHASH_SHA256_HEX_LENGTH 64

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

static void bin2hex(JanetBuffer *buffer, char *hexresult) {
  int32_t offset;

  for( offset = 0; offset < buffer->capacity; offset++) {
    sprintf( ( hexresult + (2*offset)), "%02x", buffer->data[offset]&0xff);
  }
}

static Janet c_md5(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);

  picohash_ctx_t ctx;
  JanetBuffer *buffer = janet_buffer(PICOHASH_MD5_DIGEST_LENGTH);

  const uint8_t *str = janet_getstring(argv, 0);
  int len = janet_string_length(str);

  picohash_init_md5(&ctx);
  picohash_update(&ctx, str, len);
  picohash_final(&ctx, buffer->data);

  char hexresult[PICOHASH_MD5_HEX_LENGTH];
  bin2hex(buffer, hexresult);

  return janet_stringv((const uint8_t *)hexresult, PICOHASH_MD5_HEX_LENGTH);
}

static Janet c_sha1(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);

  picohash_ctx_t ctx;
  JanetBuffer *buffer = janet_buffer(PICOHASH_SHA1_DIGEST_LENGTH);

  const uint8_t *str = janet_getstring(argv, 0);
  int len = janet_string_length(str);

  picohash_init_sha1(&ctx);
  picohash_update(&ctx, str, len);
  picohash_final(&ctx, buffer->data);

  char hexresult[PICOHASH_MD5_HEX_LENGTH];
  bin2hex(buffer, hexresult);

  return janet_stringv((const uint8_t *)hexresult, PICOHASH_SHA1_HEX_LENGTH);
}

static Janet c_sha256(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);

  picohash_ctx_t ctx;
  JanetBuffer *buffer = janet_buffer(PICOHASH_SHA256_DIGEST_LENGTH);

  const uint8_t *str = janet_getstring(argv, 0);
  int len = janet_string_length(str);

  picohash_init_sha256(&ctx);
  picohash_update(&ctx, str, len);
  picohash_final(&ctx, buffer->data);

  char hexresult[PICOHASH_SHA256_HEX_LENGTH];
  bin2hex(buffer, hexresult);

  return janet_stringv((const uint8_t *)hexresult, PICOHASH_SHA256_HEX_LENGTH);
}

static Janet c_hmac_md5(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);

  const uint8_t *secret = janet_getstring(argv, 0);
  const uint8_t *payload = janet_getstring(argv, 1);

  picohash_ctx_t ctx;
  JanetBuffer *buffer = janet_buffer(PICOHASH_MD5_DIGEST_LENGTH);

  picohash_init_hmac(&ctx, picohash_init_md5, secret, janet_string_length(secret));
  picohash_update(&ctx, payload, janet_string_length(payload));
  picohash_final(&ctx, buffer->data);

  char hexresult[PICOHASH_MD5_HEX_LENGTH];
  bin2hex(buffer, hexresult);

  return janet_stringv((const uint8_t *)hexresult, PICOHASH_MD5_HEX_LENGTH);
}

static Janet c_hmac_sha1(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);

  const uint8_t *secret = janet_getstring(argv, 0);
  const uint8_t *payload = janet_getstring(argv, 1);

  picohash_ctx_t ctx;
  JanetBuffer *buffer = janet_buffer(PICOHASH_SHA1_DIGEST_LENGTH);

  picohash_init_hmac(&ctx, picohash_init_sha1, secret, janet_string_length(secret));
  picohash_update(&ctx, payload, janet_string_length(payload));
  picohash_final(&ctx, buffer->data);

  char hexresult[PICOHASH_SHA1_HEX_LENGTH];
  bin2hex(buffer, hexresult);

  return janet_stringv((const uint8_t *)hexresult, PICOHASH_SHA1_HEX_LENGTH);
}

static Janet c_hmac_sha256(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);

  const uint8_t *secret = janet_getstring(argv, 0);
  const uint8_t *payload = janet_getstring(argv, 1);

  picohash_ctx_t ctx;
  JanetBuffer *buffer = janet_buffer(PICOHASH_SHA256_DIGEST_LENGTH);

  picohash_init_hmac(&ctx, picohash_init_sha256, secret, janet_string_length(secret));
  picohash_update(&ctx, payload, janet_string_length(payload));
  picohash_final(&ctx, buffer->data);

  char hexresult[PICOHASH_SHA256_HEX_LENGTH];
  bin2hex(buffer, hexresult);

  return janet_stringv((const uint8_t *)hexresult, PICOHASH_SHA256_HEX_LENGTH);
}

static const JanetReg cfuns[] = {
  {"encode", encode, "(codec/encode str)\n\nBase64 encodes a string."},
  {"decode", decode, "(codec/decode base64-encoded-str)\n\nDecodes a base64 encoded string."},
  // this is only here to not break existing uses of this lib (if any)
  {"hmac-sha1", c_hmac_sha1, "(codec/hmac-sha1 \"secret\" \"payload\")\n\nPerforms a sha1 hmac digest on payload with the given secret"},
  {"md5", c_md5, "Example:\n\n(codec/md5 \"payload\")\n\nPerforms an md5 digest on payload"},
  {"sha1", c_sha1, "Example:\n\n(codec/sha1 \"payload\")\n\nPerforms a sha1 digest on payload"},
  {"sha256", c_sha256, "Example:\n\n(codec/sha256 \"payload\")\n\nPerforms a sha256 digest on payload"},
  {"hmac/md5", c_hmac_md5, "Example:\n\n(codec/hmac/md5 \"secret\", \"payload\")\n\nPerforms an hmac md5 digest on payload with secret"},
  {"hmac/sha1", c_hmac_sha1, "Example:\n\n(codec/hmac/sha1 \"secret\" \"payload\")\n\nPerforms an hmac sha1 digest on payload with secret"},
  {"hmac/sha256", c_hmac_sha256, "Example:\n\n(codec/hmac/sha256 \"secret\" \"payload\")\n\nPerforms an hmac sha256 digest on payload with secret"},
  {NULL, NULL, NULL}
};

JANET_MODULE_ENTRY(JanetTable *env) {
  janet_cfuns(env, "codec", cfuns);
}
