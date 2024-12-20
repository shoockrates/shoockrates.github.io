#include <microhttpd.h>
#include <stdio.h>
#include <string.h>

#define PORT 80

static int request_handler(void *cls, struct MHD_Connection *connection,
                           const char *url, const char *method, const char *version,
                           const char *upload_data, size_t *upload_data_size, void **con_cls) {
    const char *response_str = "<html><body><h1>Hello, World!</h1></body></html>";
    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(response_str),
                                               (void *)response_str,
                                               MHD_RESPMEM_PERSISTENT);
    if (!response)
        return MHD_NO;

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, 
                              &request_handler, NULL, MHD_OPTION_END);
    if (NULL == daemon) {
        fprintf(stderr, "Failed to start HTTP server\n");
        return 1;
    }

    printf("HTTP server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}

