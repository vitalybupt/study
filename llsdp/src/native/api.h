#ifndef INCLUDE_LLSDP_API_H_
#define INCLUDE_LLSDP_API_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <stddef.h>

#if defined(__wasm__)
#define LLSDP_EXPORT __attribute__((visibility("default")))
#else
#define LLSDP_EXPORT
#endif

typedef llsdp__internal_t llsdp_t;
typedef struct llsdp_settings_s llsdp_settings_t;

typedef int (*llsdp_data_cb)(llsdp_t*, const char *at, size_t length);
typedef int (*llsdp_cb)(llsdp_t*);

struct llsdp_settings_s {
  /* Possible return values 0, -1, `HPE_PAUSED` */
  llsdp_cb      on_message_begin;

  /* Possible return values 0, -1, HPE_USER */
  llsdp_data_cb on_url;
  llsdp_data_cb on_status;
  llsdp_data_cb on_header_field;
  llsdp_data_cb on_header_value;

  /* Possible return values:
   * 0  - Proceed normally
   * 1  - Assume that request/response has no body, and proceed to parsing the
   *      next message
   * 2  - Assume absence of body (as above) and make `llsdp_execute()` return
   *      `HPE_PAUSED_UPGRADE`
   * -1 - Error
   * `HPE_PAUSED`
   */
  llsdp_cb      on_headers_complete;

  /* Possible return values 0, -1, HPE_USER */
  llsdp_data_cb on_body;

  /* Possible return values 0, -1, `HPE_PAUSED` */
  llsdp_cb      on_message_complete;

  /* When on_chunk_header is called, the current chunk length is stored
   * in parser->content_length.
   * Possible return values 0, -1, `HPE_PAUSED`
   */
  llsdp_cb      on_chunk_header;
  llsdp_cb      on_chunk_complete;

  /* Information-only callbacks, return value is ignored */
  llsdp_cb      on_url_complete;
  llsdp_cb      on_status_complete;
  llsdp_cb      on_header_field_complete;
  llsdp_cb      on_header_value_complete;
};

/* Initialize the parser with specific type and user settings.
 *
 * NOTE: lifetime of `settings` has to be at least the same as the lifetime of
 * the `parser` here. In practice, `settings` has to be either a static
 * variable or be allocated with `malloc`, `new`, etc.
 */
LLSDP_EXPORT
void llsdp_init(llsdp_t* parser, llsdp_type_t type,
                 const llsdp_settings_t* settings);

#if defined(__wasm__)

LLSDP_EXPORT
llsdp_t* llsdp_alloc(llsdp_type_t type);

LLSDP_EXPORT
void llsdp_free(llsdp_t* parser);

LLSDP_EXPORT
uint8_t llsdp_get_type(llsdp_t* parser);

LLSDP_EXPORT
uint8_t llsdp_get_sdp_major(llsdp_t* parser);

LLSDP_EXPORT
uint8_t llsdp_get_sdp_minor(llsdp_t* parser);

LLSDP_EXPORT
uint8_t llsdp_get_method(llsdp_t* parser);

LLSDP_EXPORT
int llsdp_get_status_code(llsdp_t* parser);

LLSDP_EXPORT
uint8_t llsdp_get_upgrade(llsdp_t* parser);

#endif  // defined(__wasm__)

/* Reset an already initialized parser back to the start state, preserving the
 * existing parser type, callback settings, user data, and lenient flags.
 */
LLSDP_EXPORT
void llsdp_reset(llsdp_t* parser);

/* Initialize the settings object */
LLSDP_EXPORT
void llsdp_settings_init(llsdp_settings_t* settings);

/* Parse full or partial request/response, invoking user callbacks along the
 * way.
 *
 * If any of `llsdp_data_cb` returns errno not equal to `HPE_OK` - the parsing
 * interrupts, and such errno is returned from `llsdp_execute()`. If
 * `HPE_PAUSED` was used as a errno, the execution can be resumed with
 * `llsdp_resume()` call.
 *
 * In a special case of CONNECT/Upgrade request/response `HPE_PAUSED_UPGRADE`
 * is returned after fully parsing the request/response. If the user wishes to
 * continue parsing, they need to invoke `llsdp_resume_after_upgrade()`.
 *
 * NOTE: if this function ever returns a non-pause type error, it will continue
 * to return the same error upon each successive call up until `llsdp_init()`
 * is called.
 */
LLSDP_EXPORT
llsdp_errno_t llsdp_execute(llsdp_t* parser, const char* data, size_t len);

/* This method should be called when the other side has no further bytes to
 * send (e.g. shutdown of readable side of the TCP connection.)
 *
 * Requests without `Content-Length` and other messages might require treating
 * all incoming bytes as the part of the body, up to the last byte of the
 * connection. This method will invoke `on_message_complete()` callback if the
 * request was terminated safely. Otherwise a error code would be returned.
 */
LLSDP_EXPORT
llsdp_errno_t llsdp_finish(llsdp_t* parser);

/* Returns `1` if the incoming message is parsed until the last byte, and has
 * to be completed by calling `llsdp_finish()` on EOF
 */
LLSDP_EXPORT
int llsdp_message_needs_eof(const llsdp_t* parser);

/* Returns `1` if there might be any other messages following the last that was
 * successfully parsed.
 */
LLSDP_EXPORT
int llsdp_should_keep_alive(const llsdp_t* parser);

/* Make further calls of `llsdp_execute()` return `HPE_PAUSED` and set
 * appropriate error reason.
 *
 * Important: do not call this from user callbacks! User callbacks must return
 * `HPE_PAUSED` if pausing is required.
 */
LLSDP_EXPORT
void llsdp_pause(llsdp_t* parser);

/* Might be called to resume the execution after the pause in user's callback.
 * See `llsdp_execute()` above for details.
 *
 * Call this only if `llsdp_execute()` returns `HPE_PAUSED`.
 */
LLSDP_EXPORT
void llsdp_resume(llsdp_t* parser);

/* Might be called to resume the execution after the pause in user's callback.
 * See `llsdp_execute()` above for details.
 *
 * Call this only if `llsdp_execute()` returns `HPE_PAUSED_UPGRADE`
 */
LLSDP_EXPORT
void llsdp_resume_after_upgrade(llsdp_t* parser);

/* Returns the latest return error */
LLSDP_EXPORT
llsdp_errno_t llsdp_get_errno(const llsdp_t* parser);

/* Returns the verbal explanation of the latest returned error.
 *
 * Note: User callback should set error reason when returning the error. See
 * `llsdp_set_error_reason()` for details.
 */
LLSDP_EXPORT
const char* llsdp_get_error_reason(const llsdp_t* parser);

/* Assign verbal description to the returned error. Must be called in user
 * callbacks right before returning the errno.
 *
 * Note: `HPE_USER` error code might be useful in user callbacks.
 */
LLSDP_EXPORT
void llsdp_set_error_reason(llsdp_t* parser, const char* reason);

/* Returns the pointer to the last parsed byte before the returned error. The
 * pointer is relative to the `data` argument of `llsdp_execute()`.
 *
 * Note: this method might be useful for counting the number of parsed bytes.
 */
LLSDP_EXPORT
const char* llsdp_get_error_pos(const llsdp_t* parser);

/* Returns textual name of error code */
LLSDP_EXPORT
const char* llsdp_errno_name(llsdp_errno_t err);

/* Returns textual name of SDP method */
LLSDP_EXPORT
const char* llsdp_method_name(llsdp_method_t method);


/* Enables/disables lenient header value parsing (disabled by default).
 *
 * Lenient parsing disables header value token checks, extending llsdp's
 * protocol support to highly non-compliant clients/server. No
 * `HPE_INVALID_HEADER_TOKEN` will be raised for incorrect header values when
 * lenient parsing is "on".
 *
 * **(USE AT YOUR OWN RISK)**
 */
LLSDP_EXPORT
void llsdp_set_lenient_headers(llsdp_t* parser, int enabled);


/* Enables/disables lenient handling of conflicting `Transfer-Encoding` and
 * `Content-Length` headers (disabled by default).
 *
 * Normally `llsdp` would error when `Transfer-Encoding` is present in
 * conjunction with `Content-Length`. This error is important to prevent SDP
 * request smuggling, but may be less desirable for small number of cases
 * involving legacy servers.
 *
 * **(USE AT YOUR OWN RISK)**
 */
LLSDP_EXPORT
void llsdp_set_lenient_chunked_length(llsdp_t* parser, int enabled);


/* Enables/disables lenient handling of `Connection: close` and SDP/1.0
 * requests responses.
 *
 * Normally `llsdp` would error on (in strict mode) or discard (in loose mode)
 * the SDP request/response after the request/response with `Connection: close`
 * and `Content-Length`. This is important to prevent cache poisoning attacks,
 * but might interact badly with outdated and insecure clients. With this flag
 * the extra request/response will be parsed normally.
 *
 * **(USE AT YOUR OWN RISK)**
 */
void llsdp_set_lenient_keep_alive(llsdp_t* parser, int enabled);

#ifdef __cplusplus
}  /* extern "C" */
#endif
#endif  /* INCLUDE_LLSDP_API_H_ */
