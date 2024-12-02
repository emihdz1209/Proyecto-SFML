cmake_minimum_required(VERSION 3.28)
project(ProyectoSFML)

set(CMAKE_CXX_STANDARD 17)

# Set the path to your SFML installation
set(SFML_DIR "C:/Users/emili/OneDrive/Documents/SFML-2.6.2-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.2/lib/cmake/SFML") # Replace with your actual SFML path

# Find SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Add your executable
add_executable(ProyectoSFML main.cpp
        nonlinearStructures/AVLTree.cpp
        searchAlgorithms/BinarySearch.cpp
        nonlinearStructures/BFS.cpp
        sortingAlgorithms/BubbleSort.cpp
        nonlinearStructures/DFS.cpp
        sortingAlgorithms/InsertionSort.cpp
        LinearDataStructureMenu.cpp
        searchAlgorithms/LinearSearch.cpp
        linearStructures/LinkedList.cpp
        nonlinearStructures/MazeSolver.cpp
        sortingAlgorithms/MergeSort.cpp
        NonLinearDataStructureMenu.cpp
        linearStructures/Queue.cpp
        sortingAlgorithms/QuickSort.cpp
        SearchMenu.cpp
        sortingAlgorithms/SelectionSort.cpp
        SortingMenu.cpp
        linearStructures/Stack.cpp
        nonlinearStructures/Graphs.cpp)

# Link SFML libraries
target_link_libraries(ProyectoSFML sfml-system sfml-window sfml-graphics)