GTK=`pkg-config --cflags --libs gtk+-2.0`

buttons:
	g++ src/Buttons.cpp $(GTK) -o build/gtk_first

layout:
	g++ src/Layout.cpp $(GTK) -o build/gtk_layout

dependencies:
	sudo apt-get install libgtk2.0-dev -y

clean:
	rm -rf build/*    