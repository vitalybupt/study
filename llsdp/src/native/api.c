#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "llsdp.h"

#define CALLBACK_MAYBE(PARSER, NAME)                                          \
  do {                                                                        \
    const llsdp_settings_t* settings;                                        \
    settings = (const llsdp_settings_t*) (PARSER)->settings;                 \
    if (settings == NULL || settings->NAME == NULL) {                         \
      err = 0;                                                                \
      break;                                                                  \
    }                                                                         \
    err = settings->NAME((PARSER));                                           \
  } while (0)

#define SPAN_CALLBACK_MAYBE(PARSER, NAME, START, LEN)                         \
  do {                                                                        \
    const llsdp_settings_t* settings;                                        \
    settings = (const llsdp_settings_t*) (PARSER)->settings;                 \
    if (settings == NULL || settings->NAME == NULL) {                         \
      err = 0;                                                                \
      break;                                                                  \
    }                                                                         \
    err = settings->NAME((PARSER), (START), (LEN));                           \
    if (err == -1) {                                                          \
      err = HPE_USER;                                                         \
      llsdp_set_error_reason((PARSER), "Span callback error in " #NAME);     \
    }                                                                         \
  } while (0)

void llsdp_init(llsdp_t* parser, llsdp_type_t type,
                 const llsdp_settings_t* settings) {
  llsdp__internal_init(parser);

  parser->type = type;
  parser->settings = (void*) settings;
}


#if defined(__wasm__)

extern int wasm_on_message_begin(llsdp_t * p);
extern int wasm_on_url(llsdp_t* p, const char* at, size_t length);
extern int wasm_on_status(llsdp_t* p, const char* at, size_t length);
extern int wasm_on_header_field(llsdp_t* p, const char* at, size_t length);
extern int wasm_on_header_value(llsdp_t* p, const char* at, size_t length);
extern int wasm_on_headers_complete(llsdp_t * p);
extern int wasm_on_body(llsdp_t* p, const char* at, size_t length);
extern int wasm_on_message_complete(llsdp_t * p);

const llsdp_settings_t wasm_settings = {
  wasm_on_message_begin,
  wasm_on_url,
  wasm_on_status,
  wasm_on_header_field,
  wasm_on_header_value,
  wasm_on_headers_complete,
  wasm_on_body,
  wasm_on_message_complete,
  NULL,
  NULL,
};


llsdp_t* llsdp_alloc(llsdp_type_t type) {
  llsdp_t* parser = malloc(sizeof(llsdp_t));
  llsdp_init(parser, type, &wasm_settings);
  return parser;
}

void llsdp_free(llsdp_t* parser) {
  free(parser);
}

/* Some getters required to get stuff from the parser */

uint8_t llsdp_get_type(llsdp_t* parser) {
  return parser->type;
}

uint8_t llsdp_get_sdp_major(llsdp_t* parser) {
  return parser->sdp_major;
}

uint8_t llsdp_get_sdp_minor(llsdp_t* parser) {
  return parser->sdp_minor;
}

uint8_t llsdp_get_method(llsdp_t* parser) {
  return parser->method;
}

int llsdp_get_status_code(llsdp_t* parser) {
  return parser->status_code;
}

uint8_t llsdp_get_upgrade(llsdp_t* parser) {
  return parser->upgrade;
}

#endif  // defined(__wasm__)


void llsdp_reset(llsdp_t* parser) {
  llsdp_type_t type = parser->type;
  const llsdp_settings_t* settings = parser->settings;
  void* data = parser->data;
  uint8_t lenient_flags = parser->lenient_flags;

  llsdp__internal_init(parser);

  parser->type = type;
  parser->settings = (void*) settings;
  parser->data = data;
  parser->lenient_flags = lenient_flags;
}


llsdp_errno_t llsdp_execute(llsdp_t* parser, const char* data, size_t len) {
  return llsdp__internal_execute(parser, data, data + len);
}


void llsdp_settings_init(llsdp_settings_t* settings) {
  memset(settings, 0, sizeof(*settings));
}


llsdp_errno_t llsdp_finish(llsdp_t* parser) {
  int err;

  /* We're in an error state. Don't bother doing anything. */
  if (parser->error != 0) {
    return 0;
  }

  switch (parser->finish) {
    case SDP_FINISH_SAFE_WITH_CB:
      CALLBACK_MAYBE(parser, on_message_complete);
      if (err != HPE_OK) return err;

    /* FALLTHROUGH */
    case SDP_FINISH_SAFE:
      return HPE_OK;
    case SDP_FINISH_UNSAFE:
      parser->reason = "Invalid EOF state";
      return HPE_INVALID_EOF_STATE;
    default:
      abort();
  }
}


void llsdp_pause(llsdp_t* parser) {
  if (parser->error != HPE_OK) {
    return;
  }

  parser->error = HPE_PAUSED;
  parser->reason = "Paused";
}


void llsdp_resume(llsdp_t* parser) {
  if (parser->error != HPE_PAUSED) {
    return;
  }

  parser->error = 0;
}


void llsdp_resume_after_upgrade(llsdp_t* parser) {
  if (parser->error != HPE_PAUSED_UPGRADE) {
    return;
  }

  parser->error = 0;
}


llsdp_errno_t llsdp_get_errno(const llsdp_t* parser) {
  return parser->error;
}


const char* llsdp_get_error_reason(const llsdp_t* parser) {
  return parser->reason;
}


void llsdp_set_error_reason(llsdp_t* parser, const char* reason) {
  parser->reason = reason;
}


const char* llsdp_get_error_pos(const llsdp_t* parser) {
  return parser->error_pos;
}


const char* llsdp_errno_name(llsdp_errno_t err) {
#define SDP_ERRNO_GEN(CODE, NAME, _) case HPE_##NAME: return "HPE_" #NAME;
  switch (err) {
    SDP_ERRNO_MAP(SDP_ERRNO_GEN)
    default: abort();
  }
#undef SDP_ERRNO_GEN
}


const char* llsdp_method_name(llsdp_method_t method) {
#define SDP_METHOD_GEN(NUM, NAME, STRING) case SDP_##NAME: return #STRING;
  switch (method) {
    SDP_ALL_METHOD_MAP(SDP_METHOD_GEN)
    default: abort();
  }
#undef SDP_METHOD_GEN
}


void llsdp_set_lenient_headers(llsdp_t* parser, int enabled) {
  if (enabled) {
    parser->lenient_flags |= LENIENT_HEADERS;
  } else {
    parser->lenient_flags &= ~LENIENT_HEADERS;
  }
}


void llsdp_set_lenient_chunked_length(llsdp_t* parser, int enabled) {
  if (enabled) {
    parser->lenient_flags |= LENIENT_CHUNKED_LENGTH;
  } else {
    parser->lenient_flags &= ~LENIENT_CHUNKED_LENGTH;
  }
}


void llsdp_set_lenient_keep_alive(llsdp_t* parser, int enabled) {
  if (enabled) {
    parser->lenient_flags |= LENIENT_KEEP_ALIVE;
  } else {
    parser->lenient_flags &= ~LENIENT_KEEP_ALIVE;
  }
}

/* Callbacks */


int llsdp__on_message_begin(llsdp_t* s, const char* p, const char* endp) {
  int err;
  CALLBACK_MAYBE(s, on_message_begin);
  return err;
}


int llsdp__on_url(llsdp_t* s, const char* p, const char* endp) {
  int err;
  SPAN_CALLBACK_MAYBE(s, on_url, p, endp - p);
  return err;
}


int llsdp__on_url_complete(llsdp_t* s, const char* p, const char* endp) {
  int err;
  CALLBACK_MAYBE(s, on_url_complete);
  return err;
}


int llsdp__on_status(llsdp_t* s, const char* p, const char* endp) {
  int err;
  SPAN_CALLBACK_MAYBE(s, on_status, p, endp - p);
  return err;
}


int llsdp__on_status_complete(llsdp_t* s, const char* p, const char* endp) {
  int err;
  CALLBACK_MAYBE(s, on_status_complete);
  return err;
}


int llsdp__on_header_field(llsdp_t* s, const char* p, const char* endp) {
  int err;
  SPAN_CALLBACK_MAYBE(s, on_header_field, p, endp - p);
  return err;
}


int llsdp__on_header_field_complete(llsdp_t* s, const char* p, const char* endp) {
  int err;
  CALLBACK_MAYBE(s, on_header_field_complete);
  return err;
}


int llsdp__on_header_value(llsdp_t* s, const char* p, const char* endp) {
  int err;
  SPAN_CALLBACK_MAYBE(s, on_header_value, p, endp - p);
  return err;
}


int llsdp__on_header_value_complete(llsdp_t* s, const char* p, const char* endp) {
  int err;
  CALLBACK_MAYBE(s, on_header_value_complete);
  return err;
}


int llsdp__on_headers_complete(llsdp_t* s, const char* p, const char* endp) {
  int err;
  CALLBACK_MAYBE(s, on_headers_complete);
  return err;
}


int llsdp__on_message_complete(llsdp_t* s, const char* p, const char* endp) {
  int err;
  CALLBACK_MAYBE(s, on_message_complete);
  return err;
}


int llsdp__on_body(llsdp_t* s, const char* p, const char* endp) {
  int err;
  SPAN_CALLBACK_MAYBE(s, on_body, p, endp - p);
  return err;
}


int llsdp__on_chunk_header(llsdp_t* s, const char* p, const char* endp) {
  int err;
  CALLBACK_MAYBE(s, on_chunk_header);
  return err;
}


int llsdp__on_chunk_complete(llsdp_t* s, const char* p, const char* endp) {
  int err;
  CALLBACK_MAYBE(s, on_chunk_complete);
  return err;
}


/* Private */


void llsdp__debug(llsdp_t* s, const char* p, const char* endp,
                   const char* msg) {
  if (p == endp) {
    fprintf(stderr, "p=%p type=%d flags=%02x next=null debug=%s\n", s, s->type,
            s->flags, msg);
  } else {
    fprintf(stderr, "p=%p type=%d flags=%02x next=%02x   debug=%s\n", s,
            s->type, s->flags, *p, msg);
  }
}
