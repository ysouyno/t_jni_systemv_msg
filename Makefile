INCLUDES = -I/usr/lib/jvm/java-16-openjdk/include \
-I/usr/lib/jvm/java-16-openjdk/include/linux
CXXFLAGS = -shared -fPIC

libjni_tmain.so: jni_tmain.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) $? -o $@

.PHONY: clean
clean:
	rm -f libjni_tmain.so
