lib_LTLIBRARIES = libteoccl.la

AM_CFLAGS = -fPIC -Wpointer-arith

libteoccl_la_SOURCES = \
	teoccl/memory.c \
	teoccl/queue.c \
	teoccl/hash.c \
	teoccl/map.c \
	teoccl/list.c \
	teoccl/array_list.c \
	teoccl/linked_list.c \
	teoccl/deque.c \
	teoccl/que.c \
	teoccl/stack.c \
	# end of libteoccl_la_SOURCES

libteocclincludedir=$(includedir)/teoccl

libteocclinclude_HEADERS = \
	../include/teoccl/memory.h \
	../include/teoccl/list.h \
	../include/teoccl/hash.h \
	../include/teoccl/array_list.h \
	../include/teoccl/linked_list.h \
	../include/teoccl/map.h \
	../include/teoccl/map.hpp \
	../include/teoccl/queue.h \
	../include/teoccl/queue.hpp \
	../include/teoccl/deque.h \
	../include/teoccl/que.h \
	../include/teoccl/stack.h \
	teoccl/teoccl.hpp \
	# end of libteocclinclude_HEADERS

libteoccl_la_CFLAGS = -I$(top_srcdir)/include
libteoccl_la_LDFLAGS = -version-info $(LIBRARY_CURRENT):$(LIBRARY_REVISION):$(LIBRARY_AGE)

uninstall-hook:
	-rmdir $(libteocclincludedir)
