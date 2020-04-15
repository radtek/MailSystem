#pragma once

#define HTTP_VERSION			"HTTP/1.1"

#define HTTP_HEAD_CONTENT_TYPE	"CONTENT-TYPE"
#define HTTP_HEAD_HOSE			"HOST"
#define HTTP_HEAD_CONTENT_LEN	"CONTENT-LENGTH"
#define HTTP_HEAD_CONNECTION	"CONNECTION"
#define HTTP_HEAD_KEEP_ALIVE	"KEEP-ALIVE"
#define HTTP_HEAD_CLOSE			"CLOSE"

#define HTTP_HEAD_JSON_TYPE		"application/json"
#define HTTP_HEAD_FORM_TYPE		"multipart/form-data"
#define HTTP_HEAD_HTML_TYPE		"text/html"
#define HTTP_HEAD_CSS_TYPE		"text/css"
#define HTTP_HEAD_PLAIN_TYPE	"text/plain"
#define HTTP_HEAD_GIF_TYPE		"image/gif"
#define HTTP_HEAD_JPG_TYPE		"image/jpeg"
#define HTTP_HEAD_PNG_TYPE		"image/png"

#define HTTP_URL_LOGIN				"/login"
#define HTTP_URL_SEND_NO_ATTACH		"/send_mail_no_attach"
#define HTTP_URL_SEND_WITH_ATTACH	"/send_mail_with_attach"
#define HTTP_URL_RECV_NO_ATTACH		"/recv_mail_no_attach"
#define HTTP_URL_RECV_WITH_ATTACH	"/recv_mail_with_attach"
#define HTTP_URL_DELETE_MAIL		"/delete_mails"