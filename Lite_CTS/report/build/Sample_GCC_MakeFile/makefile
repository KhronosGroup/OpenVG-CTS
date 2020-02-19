##---------------------------

ANSWER_CONFIG = -DANSWER_DEFAULT_DIR=\"../../../data/answer\"
REF_CONFIG    = -DREFERENCE_DEFAULT_DIR=\"../../../data/reference\"
INFO_CONFIG   = -DINFO_DEFAULT_DIR=\"../../../data/info\"
VGU_CONFIG    = -DTEST_OPTION_VGU=1

##---------------------------
CTS_SRC    =../../source


##---------------------------
CC 	   =  gcc
INC        = -I$(CTS_SRC)
CFLAGS     = $(INC) $(ANSWER_CONFIG) $(REF_CONFIG) $(INFO_CONFIG) $(VGU_CONFIG)

##---------------------------
TARGET     = bin/report.exe
SRCS       = $(CTS_SRC)/*.c \
             $(CTS_SRC)/util/*.c \
             $(CTS_SRC)/functions/*.c

##---------------------------
all :
	$(CC) -g $(CFLAGS) $(SRCS) -o $(TARGET)
