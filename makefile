INC_DIR=./inc
OBJ_DIR=./obj
LIB_DIR=./lib
SRC_DIR=./src
BIN_DIR=./bin

CC=gcc
RM=rm -f

SERC_PATH=.serc_framework/serc
CON_DIR=.serc_config

CFLAGS=-I${INC_DIR} -I${CON_DIR} -I${CONNMAN_PATH}/inc -I${BOOMPAR_PATH}/inc -I${JSON_PARSER_PATH}/inc -I${CUTLERY_PATH}/inc -I${RWLOCK_PATH}/inc -I${SERC_PATH}/inc
LFLAFS=-L${CONNMAN_PATH}/bin -lconnman -L${BOOMPAR_PATH}/bin -lpthread -lboompar -L${JSON_PARSER_PATH}/bin -ljsonpar -L${CUTLERY_PATH}/bin -lcutlery -L${RWLOCK_PATH}/bin -lrwlock -lz -L${SERC_PATH}/bin -lserc

TARGET=app.out

clean :
	$(RM) $(BIN_DIR)/*.out $(OBJ_DIR)/*.o
	make -w -C ${SERC_PATH} clean CON_DIR=`pwd`/${CON_DIR}

all :
	make -w -C ${SERC_PATH} all   CON_DIR=`pwd`/${CON_DIR}
	mkdir -p bin
	${CC} ${SRC_DIR}/main.c ${SRC_DIR}/controller/first_controller.c -o ${BIN_DIR}/app.out ${CFLAGS} ${LFLAFS}