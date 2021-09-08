INCLUDES = -I/usr/lib/jvm/java-16-openjdk/include \
-I/usr/lib/jvm/java-16-openjdk/include/linux
CXXFLAGS = -shared -fPIC

all: libjni_tmain.so svmsg_server

libjni_tmain.so: jni_tmain.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) $? -o $@

svmsg_server: svmsg_server.cpp
	$(CXX) $? -o $@

.PHONY: clean
clean:
	rm -f libjni_tmain.so
	rm -f svmsg_server
