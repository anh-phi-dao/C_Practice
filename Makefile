build_directory:=build
run_path:=$(build_directory)/Test
run_path_2:=$(build_directory)/priority


$(build_directory):
	mkdir build

clean:
	rm -rf build

compile:$(build_directory)
	cmake -B build -G "Unix Makefiles"
	cmake --build build

memory:$(run_path_2)
	size $(run_path_2)

$(run_path):
	make compile

$(run_path_2):
	make compile

run: $(run_path)
	$(run_path) > output.txt

run2: $(run_path_2)
	$(run_path_2) >output.txt
