build_directory:=build
run_path:=$(build_directory)/Test


$(build_directory):
	mkdir build

clean:
	rm -rf build

compile:$(build_directory)
	cmake -B build -G "Unix Makefiles"
	cmake --build build

$(run_path):
	make compile

run: $(run_path)
	$(run_path) > output.txt
