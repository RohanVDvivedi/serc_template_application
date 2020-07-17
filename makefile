INC_DIR=./inc
OBJ_DIR=./obj
LIB_DIR=./lib
SRC_DIR=./src
BIN_DIR=./bin

CC=gcc
RM=rm -f

SERC_PATH=.serc_framework/serc
CON_DIR=.serc_config

CFLAGS=-Wall -O3 -I${INC_DIR} -I${CON_DIR} -I${SERC_PATH}/inc
LFLAFS=-L${SERC_PATH}/bin -lserc -lconnman -lboompar -lpthread -ljsonpar -lcutlery -lrwlock -lz -lssl -lcrypto

TARGET=app.out

update_serc :
	cd ${SERC_PATH}; git checkout -- .
	cd ${SERC_PATH}; git checkout master
	cd ${SERC_PATH}; git pull origin master

clean :
	$(RM) -r $(BIN_DIR) $(OBJ_DIR)
	make -w -C ${SERC_PATH} clean		CON_DIR=`pwd`/${CON_DIR}

routes :
	make -w -C ${SERC_PATH} routes		CON_DIR=`pwd`/${CON_DIR}

ssl_cert :
	make -w -C ${SERC_PATH} ssl_cert	CON_DIR=`pwd`/${CON_DIR}

all :
	make -w -C ${SERC_PATH} all   		CON_DIR=`pwd`/${CON_DIR}
	mkdir -p bin
	${CC} ${SRC_DIR}/main.c ${SRC_DIR}/controller/*.c -o ${BIN_DIR}/app.out ${CFLAGS} ${LFLAFS}