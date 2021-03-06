#include <signal.h>
#include <time.h>
#include "../utils/struct_server.h"
#include "../utils/struct_message.h"

#define JOIN_STRING "REG"
#define MAX_PENDING 5

extern struct addrinfo *id_server;
struct addrinfo *reg_server(int_fast16_t *fd, server host, char *ip_name, char *udp_port);
// INIT
int init_tcp(server host);
int init_udp(server host);
int send_initial_comm(int processing_fd);

// METHODS
int update_reg(int fd, struct addrinfo* id_server_info);
int connect_to_old_server(server old_server, bool is_comm_sent);
int join_to_old_servers(list servers_list, server host);

int  remove_bad_servers(list servers_list, server host, int max_fd, fd_set *rfds, void (*SET_FD)(int, fd_set *));
int  tcp_new_comm(list servers_list, int listen_fd, fd_set *rfds, int (*STAT_FD)(int, fd_set *));
uint_fast8_t handle_join(list msgsrv_list, int_fast16_t *udp_register_fd, server host, char *id_server_ip, char *id_server_port);
