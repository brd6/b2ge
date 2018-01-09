# b2ge

C++ Entity System for game development. There are 2 versions : b2ge-light and b2ge.

#### b2ge-light :

- Entity
- World
- System
- Manager (for Entity and System)
- Filtering entities for systems
- SystemUpdatable
- Utils

#### b2ge :

b2ge contains the b2ge-light features + others features for fast game development with SFML.

- b2ge-light features
- ... (TODO)

### Installation

Clone the repository

	git clone git@github.com:brd6/b2ge.git
	cd b2ge
    	git checkout master
    	git submodule update --init --recursive
    
Installation

	mkdir build
	cd build
	cmake ..
	make test
	make example
	make install

Enjoy!

# Windows prerequisite

set SFML_ROOT in CmakeLists.txt or in windows path
https://stackoverflow.com/questions/21387504/cmake-and-make-in-windows

### Usage
