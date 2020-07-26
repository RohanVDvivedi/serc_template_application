INC_DIR=./inc
OBJ_DIR=./obj
LIB_DIR=./lib
SRC_DIR=./src
BIN_DIR=./bin

CC=gcc
RM=rm -f

SERC_PATH=.serc_framework/serc
CON_DIR=.serc_config

CFLAGS=-Wall -O3 -I${INC_DIR}
LFLAFS=-lserc -lconnman -lboompar -lpthread -ljsonpar -lcutlery -lrwlock -lz -lssl -lcrypto

TARGET=app.out

clean :
	$(RM) -r $(BIN_DIR) $(OBJ_DIR) $(OBJ_DIR)

${SRC_DIR}/distributer.c : ${CON_DIR}/routing.con
	route.py ${CON_DIR}/routing.con
	mv distributer.c ${SRC_DIR}/

routes: ${SRC_DIR}/distributer.c

all : routes
	mkdir -p bin
	${CC} ${CFLAGS} ${SRC_DIR}/main.c ${SRC_DIR}/distributer.c  ${SRC_DIR}/controller/*.c ${LFLAFS} -o ${BIN_DIR}/app.out 

# builds a self signed ssl key and certificate for your server
ssl_cert :
	openssl req -new -x509 -pubkey -newkey rsa:4096 -days 365 -nodes -keyout ${CON_DIR}/server.key -out ${CON_DIR}/server.crt
