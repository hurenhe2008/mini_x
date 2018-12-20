
typedef struct http_error_info_s
{
  unsigned errcode;
  const char *perrmsg;
} http_error_info_t;

const http_error_info_t http_error_info_list[] = 
{
  {100, "Continue"},
  {101, "Switching Protocols"},
  {102, "Processing"},

  {200, "OK"},
  {201, "Created"},
  {202, "Accepted"},
  {203, "Non-Authoritative Information"},
  {204, "No Content"},
  {205, "Reset Content"},
  {206, "Partial Content"},
  {207, "Multi-Status"},

  {400, "Bad Request"},
  {401, "Unauthorized"},
  {402, ""},  // reserve
  {403, "Forbidden"},
  {404, "Not Found"},
  {405, "Method Not Allowed"},
  {406, "Not Acceptable"},
  {407, "Proxy Authentication Required"},
  {408, "Request Timeout"},
  {409, "Conflict"},
  {416, "Requested Range not satisfiable"},

  {500, "Internal Server Error"},
  {501, "Not Implemented"},
  {502, "Bad Gateway"},
  {503, "Service Unavailable"},
  {504, "Gateway Timeout"},
  {505, "HTTP Version Not Supported"},
  {506, "Variant Also Negotiates"},
  {507, "Insufficient Storage"},
  {508, "Bandwidth Limit Exceeded"},
  {509, "Not Extended"},
};
