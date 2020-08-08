INC_DIR=./inc
OBJ_DIR=./obj
LIB_DIR=./lib
SRC_DIR=./src
BIN_DIR=./bin

CC=gcc
RM=rm -f

CON_DIR=.serc_config

CFLAGS=-Wall -O3 -I${INC_DIR} -I${CON_DIR}
LFLAFS=-lserc -lcashed -lconnman -lboompar -lpthread -ljsonpar -lcutlery -lrwlock -lz -lssl -lcrypto

TARGET=app.out

clean :
	$(RM) -r $(BIN_DIR) $(OBJ_DIR) $(OBJ_DIR)
	$(RM) ./src/distributer.c

${SRC_DIR}/distributer.c : ${CON_DIR}/routing.con
	route.py ${CON_DIR}/routing.con
	mv distributer.c ${SRC_DIR}/

routes: ${SRC_DIR}/distributer.c

# figure out all the sources in the project
SOURCES=${shell find $(SRC_DIR) -name '*.c'}

all : routes ${SOURCES}
	mkdir -p bin
	${CC} ${CFLAGS} ${SOURCES} ${LFLAFS} -o ${BIN_DIR}/app.out 

# builds a self signed ssl key and certificate for your server
ssl_cert :
	openssl req -new -x509 -pubkey -newkey rsa:4096 -days 365 -nodes -keyout ${CON_DIR}/server.key -out ${CON_DIR}/server.crt
