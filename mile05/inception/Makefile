NAME    = inception
COMPOSE = docker compose -f srcs/docker-compose.yml
DATA    = /home/ppaula-s/data

all: up

up:
	@mkdir -p $(DATA)/wordpress $(DATA)/mariadb
	$(COMPOSE) up -d --build

down:
	$(COMPOSE) down

stop:
	$(COMPOSE) stop

start:
	$(COMPOSE) start

clean: down
	@docker image rm -f nginx wordpress mariadb 2>/dev/null || true

fclean: clean
	@sudo rm -rf $(DATA)

re: fclean all

.PHONY: all up down stop start clean fclean re
