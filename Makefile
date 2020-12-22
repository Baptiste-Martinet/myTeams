##
## EPITECH PROJECT, 2020
## Make file
## File description:
## clean rule
##

SRCCLI1		=	main.c \
				socket.c \
				read.c \
				read_server_and_client.c \
				rfc/rfc_filtering.c \
				rfc/treating_code.c \
				rfc/events1.c \
				rfc/events2.c \
				rfc/events_errors.c \
				rfc/event_thread_print_replies.c \
				rfc/event_print_teams.c \
				rfc/event_print_threads.c \
				rfc/event_mp_print_msg.c \
				rfc/event_team_print_channels.c \
				rfc/event_thread_msg_received.c \
				rfc/events_already_exist.c \
				rfc/events_created.c \
				rfc/events_print_utct.c \
				rfc/events_subed.c \
				rfc/event_created.c \

SRCCOMMCLI	=	help.c \
				command.c \
				send_command.c \
				treat_arguments.c \
				verify_arguments.c \
				send_struct1.c \
				send_struct2.c \
				send_struct3.c \
				send_struct_base.c \
				stock_rest.c \

SRCSERV1	=	main.c \
				server_utils.c \
				clients_manager.c \
				client_reader.c \
				disconnect_client.c \
				event.c \
				commands/cmd_login.c \
				commands/cmd_logout.c \
				commands/cmd_users.c \
				commands/cmd_user.c \
				commands/cmd_send.c \
				commands/cmd_messages.c \
				commands/cmd_subscribe.c \
				commands/cmd_subscribed.c \
				commands/cmd_unsubscribe.c \
				commands/cmd_use.c \
				commands/cmd_create.c \
				commands/cmd_create_utils.c \
				commands/cmd_list.c \
				commands/cmd_info.c \
				linked_lists/client_list.c \
				linked_lists/team_list.c \
				linked_lists/channel_list.c \
				linked_lists/thread_list.c \
				linked_lists/reply_list.c \
				linked_lists/message_list.c \
				linked_lists/bvector/bvector.c \
				linked_lists/bvector/bvector2.c \
				db_functions/saver/saver.c \
				db_functions/saver/team_saver.c \
				db_functions/saver/channel_saver.c \
				db_functions/saver/thread_saver.c \
				db_functions/saver/replies_saver.c \
				db_functions/saver/clients_saver.c \
				db_functions/saver/messages_saver.c \
				db_functions/loader/loader.c \
				db_functions/loader/client_loader.c \
				db_functions/loader/message_loader.c \
				db_functions/loader/team_loader.c \

SRCCCOMM	=	help.c \
				tools.c \
				tools2.c \
				str_to_word_array.c \
				string_utils.c \
				time_converting.c \
				my_getline.c \
				more_pipe.c \

SRCCLI2 	=	$(addprefix src/cli/, $(SRCCLI1)) \
				$(addprefix src/cli/commands/, $(SRCCOMMCLI)) \
				$(addprefix src/common/, $(SRCCCOMM)) \

SRCSERV2	=	$(addprefix src/server/, $(SRCSERV1)) \
				$(addprefix src/common/, $(SRCCCOMM)) \

OBJSERV		=	$(SRCSERV2:.c=.o)
OBJCLI		=	$(SRCCLI2:.c=.o)

NAMESERV	=	myteams_server
NAMECLI		=	myteams_cli

CC		=	gcc
CFLAGS	=	-I./ -I./include/ -I./libs/myteams/ -g -Wall -luuid
CFLAGS += -iquote ./libs/myteams/
LDFLAGS += -lmyteams -L./libs/myteams/ -L./libs/

all: server cli

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

server: $(OBJSERV)
	$(CC) -o $(NAMESERV) $(OBJSERV) $(CFLAGS) $(LDFLAGS)

cli: $(OBJCLI)
	$(CC) -o $(NAMECLI) $(OBJCLI) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OBJSERV)
	rm -f $(OBJCLI)
	rm -f *.so
	rm -f vgcore.*

fclean:	clean
	rm -f $(NAMESERV)
	rm -f $(NAMECLI)

re:	fclean	all

.PHONY:	clean re fclean all