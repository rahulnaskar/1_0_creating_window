all:
	g++ ../glad/src/glad.c window.cpp -o out -I. -I../glad/include -I../glfw/deps/ -I../glfw/include/ -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl 
