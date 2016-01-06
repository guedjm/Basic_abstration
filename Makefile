
NAME		=	libbasic_abstraction.a

SRCS		=	src/StandardInput.cpp			\
			src/myTCPRemoteClient.cpp		\
			src/RandomGenerator.cpp			\
			src/linux/LinuxPMutex.cpp		\
			src/linux/LinuxPThread.cpp		\
			src/linux/LinuxPCondVariable.cpp	\
			src/linux/LinuxTCPSocket.cpp		\
			src/linux/LinuxTCPClient.cpp		\
			src/linux/LinuxSelect.cpp		\
			src/linux/LinuxTCPServer.cpp		\
			src/linux/LinuxTCPRemoteClient.cpp	\
			src/linux/LinuxSelect.cpp		\
			src/windows/WindowsMutex.cpp		\
			src/windows/WindowsThread.cpp		\
			src/windows/WindowsCondVariable.cpp	\
			src/windows/WindowsTCPSocket.cpp	\
			src/windows/WindowsTCPClient.cpp	\
			src/windows/WindowsTCPServer.cpp	\
			src/windows/WindowsTCPRemoteClient.cpp	\


OBJS		=	$(SRCS:.cpp=.o)

CXXFLAGS	=	-Wall -Werror -Wextra -Iinclude

LNFLAGS		=	-lpthread

RM		=	rm -rf

BUILD_REPO	=	../../build


$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)
	mkdir -p $(BUILD_REPO)
	cp -f $(NAME) $(BUILD_REPO)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BUILD_REPO)/$(NAME)

re: fclean all
