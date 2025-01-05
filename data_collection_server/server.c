#include <microhttpd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8080
#define DB_FILENAME "matches.csv"

struct RequestData
{
  char *data;
  size_t size;
};

static int append_match_to_file(const char *ip_address, char *match_data)
{
  FILE *file = fopen(DB_FILENAME, "a");
  if (file == NULL)
  {
    printf("Failed to open file\n");
    return 0;
  }

  if (fprintf(file, "%s,%s\n", ip_address, match_data) < 0)
  {
    printf("Failed to write to file\n");
    fclose(file);
    return 0;
  }

  if (fclose(file) != 0)
  {
    printf("Failed to close file\n");
    return 0;
  }

  return 1;
}

static const char *get_client_ip(struct MHD_Connection *connection)
{
  const union MHD_ConnectionInfo *info;
  static char ip_str[16]; // xxx.xxx.xxx.xxx\0

  info = MHD_get_connection_info(connection, MHD_CONNECTION_INFO_CLIENT_ADDRESS);
  unsigned char *bytes = (unsigned char *)info->client_addr->sa_data;

  // Pirmi du baitai - portas, kiti 4 baitai - IPV4 adresas
  sprintf(ip_str, "%d.%d.%d.%d", bytes[2], bytes[3], bytes[4], bytes[5]);
  return ip_str;
}

static enum MHD_Result add_cors_headers(struct MHD_Response *response)
{
  MHD_add_response_header(response, MHD_HTTP_HEADER_ACCESS_CONTROL_ALLOW_ORIGIN, "*");
  MHD_add_response_header(response, MHD_HTTP_HEADER_ACCESS_CONTROL_ALLOW_METHODS, "POST, OPTIONS");
  MHD_add_response_header(response, MHD_HTTP_HEADER_ACCESS_CONTROL_ALLOW_HEADERS, "Content-Type, Authorization, X-Requested-With");
  MHD_add_response_header(response, MHD_HTTP_HEADER_ACCESS_CONTROL_MAX_AGE, "86400");
  return MHD_YES;
}

static enum MHD_Result
handle_request(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **ptr)
{
  struct MHD_Response *response;
  int ret;

  if (0 == strcmp(method, "OPTIONS"))
  {
    response = MHD_create_response_from_buffer(0, "", MHD_RESPMEM_PERSISTENT);
    add_cors_headers(response);
    enum MHD_Result ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
  }

  if (0 != strcmp(method, "POST"))
  {
    const char *error_message = "Only POST method is supported";
    response = MHD_create_response_from_buffer(strlen(error_message), (void *)error_message, MHD_RESPMEM_PERSISTENT);
    add_cors_headers(response);
    ret = MHD_queue_response(connection, MHD_HTTP_METHOD_NOT_ALLOWED, response);
    MHD_destroy_response(response);
    return ret;
  }

  if (*ptr == NULL)
  {
    struct RequestData *req_data = malloc(sizeof(struct RequestData));
    if (!req_data)
    {
      return MHD_NO;
    }
    req_data->data = NULL;
    req_data->size = 0;
    *ptr = req_data;
    return MHD_YES;
  }

  struct RequestData *req_data = *ptr;

  if (*upload_data_size != 0)
  {
    char *new_data = realloc(req_data->data, req_data->size + *upload_data_size + 1);
    if (!new_data)
    {
      free(req_data->data);
      free(req_data);
      *ptr = NULL;
      return MHD_NO;
    }
    req_data->data = new_data;
    memcpy(req_data->data + req_data->size, upload_data, *upload_data_size);
    req_data->size += *upload_data_size;
    req_data->data[req_data->size] = '\0';
    *upload_data_size = 0;
    return MHD_YES;
  }
  const char *client_ip = get_client_ip(connection);
  // printf("IP: %s. Received CSV: %s\n", client_ip, req_data->data);
  append_match_to_file(client_ip, req_data->data);

  const char *response_message = "CSV received successfully";
  response = MHD_create_response_from_buffer(strlen(response_message), (void *)response_message, MHD_RESPMEM_PERSISTENT);

  add_cors_headers(response);

  ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
  MHD_destroy_response(response);

  free(req_data->data);
  free(req_data);
  *ptr = NULL;

  return ret;
}

int main()
{
  struct MHD_Daemon *daemon;

  daemon = MHD_start_daemon(MHD_USE_INTERNAL_POLLING_THREAD, PORT, NULL, NULL, &handle_request, NULL, MHD_OPTION_END);

  if (NULL == daemon)
  {
    printf("Failed to start server\n");
    return 1;
  }

  printf("Server running on port %d...\n", PORT);
  getchar();
  MHD_stop_daemon(daemon);
  return 0;
}
