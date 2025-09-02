# Rubik's Cube Solver - Advanced Computer Vision & AI Implementation

An intelligent 3×3 Rubik's Cube solver implemented in C++ featuring multiple graph algorithms, computer vision integration, and real-time visualization capabilities.

## 🚀 Key Features

### **Advanced Solving Algorithms**
- **Korf's IDA\* Algorithm** - Solves 13-move scrambles in ~10ms using heuristic pattern databases
- **IDDFS (Iterative Deepening Depth-First Search)** - Achieves ~3s solve times for 8-move scrambles  
- **BFS (Breadth-First Search)** - Guaranteed optimal solutions with comprehensive state exploration
- **50MB Pattern Database** - Pre-computed corner permutation heuristics for optimal performance

### **Computer Vision Integration**
- **OpenCV Camera Integration** - Real-time cube scanning using any standard webcam
- **Intelligent Color Classification** - Advanced pixel sampling and color detection algorithms
- **Automated Cube State Capture** - Scan all 6 faces with guided interface and validation
- **Robust Error Handling** - Validates cube configurations and provides helpful feedback

### **Real-Time Visualization**
- **Interactive Face Scanner** - Live camera feed with 3×3 grid overlay for precise alignment
- **Cube State Visualizer** - Complete cube net display showing all faces simultaneously  
- **Solution Animation** - Step-by-step move visualization and solving progress tracking
- **Debug Visualization** - Algorithm performance metrics and search tree exploration

### **Object-Oriented Architecture**
- **Multiple Cube Representations** - 3D Array, 1D Array, and Bitboard implementations
- **Modular Algorithm Design** - Clean separation of solving strategies and cube models
- **Extensible Framework** - Easy to add new algorithms and cube representations

## 🛠️ Installation & Setup

### **Prerequisites**
- **C++ Compiler** - GCC 15.2.0+ or MSVC 2019+
- **CMake** - Version 3.20 or higher
- **vcpkg Package Manager** - For dependency management
- **Webcam** - For camera-based cube scanning (optional)

### **Step 1: Clone the Repository**
```bash
git clone https://github.com/silentwraith-syed/Rubiks-Cube-Solver.git
cd Rubiks-Cube-Solver
```

### **Step 2: Install Dependencies with vcpkg**
```bash
# Install vcpkg (if not already installed)
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat

# Install OpenCV for your platform
# For Windows MinGW:
.\vcpkg install opencv4[core,imgproc,highgui,videoio]:x64-mingw-dynamic

# For Windows MSVC:
.\vcpkg install opencv4[core,imgproc,highgui,videoio]:x64-windows

# For Linux:
.\vcpkg install opencv4[core,imgproc,highgui,videoio]:x64-linux
```

### **Step 3: Configure CMake Build**
```bash
mkdir build
cd build

# Configure with vcpkg toolchain
cmake .. -DCMAKE_TOOLCHAIN_FILE=[path-to-vcpkg]/scripts/buildsystems/vcpkg.cmake

# For MinGW specifically:
cmake .. -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=[path-to-vcpkg]/scripts/buildsystems/vcpkg.cmake
```

### **Step 4: Build the Project**
```bash
cmake --build .
```

## 🎮 Usage Guide

### **Running the Solver**
```bash
./rubiks_cube_solver
```

### **Scanning a Real Cube**
1. **Choose Option 2** - "Scan real cube with camera"
2. **Position Cube** - Align each face within the green 3×3 grid overlay
3. **Capture Faces** - Press SPACEBAR when the face is properly aligned
4. **Review & Confirm** - Press 'N' to accept or 'R' to rescan each face
5. **Validation** - System automatically validates cube configuration
6. **Choose Algorithm** - Select your preferred solving method

### **Demo Mode**
1. **Choose Option 1** - "Demo with random scramble"
2. **View Scramble** - See the randomly generated cube state
3. **Choose Algorithm** - Compare performance across different solvers
4. **Watch Solution** - View the optimal move sequence

### **Algorithm Performance Comparison**
- **IDA\*** ⭐ **Recommended** - Fastest, uses heuristics, optimal solutions
- **IDDFS** - Memory efficient, good performance for medium scrambles  
- **BFS** - Guaranteed optimal but extremely slow for complex scrambles

## 🏗️ Project Architecture

### **Core Components**
```
├── Model/                    # Cube representations
│   ├── RubiksCube.h         # Abstract base class
│   ├── RubiksCube3dArray.cpp # 3D array implementation
│   ├── RubiksCube1dArray.cpp # 1D array implementation
│   └── RubiksCubeBitboard.cpp # Optimized bitboard representation
├── Solver/                   # Algorithm implementations
│   ├── BFSSolver.h          # Breadth-first search
│   ├── IDDFSSolver.h        # Iterative deepening DFS
│   └── IDAstarSolver.h      # Korf's IDA* with pattern database
├── PatternDatabases/         # Heuristic database system
│   ├── CornerPatternDatabase.cpp # Corner permutation patterns
│   └── PermutationIndexer.h # Efficient state indexing
├── Scanner/                  # Computer vision module
│   ├── CubeScanner.h        # OpenCV camera interface
│   └── CubeScanner.cpp      # Color detection & validation
└── Databases/               # Pre-computed pattern databases
    └── cornerDepth5V1.txt   # 50MB corner heuristic database
```

### **Algorithm Complexity Analysis**
- **Space Complexity**: O(1) for IDA*, O(b^d) for BFS
- **Time Complexity**: O(b^d) worst-case, significantly reduced with pattern database heuristics
- **Optimality**: All algorithms guarantee optimal solutions
- **Memory Usage**: Bitboard representation uses minimal memory footprint

## 🔬 Technical Implementation Details

### **Pattern Database Generation**
- **Corner Permutation Patterns** - 88,179,840 possible states indexed efficiently
- **Breadth-First Generation** - Ensures optimal heuristic values
- **Compact Storage** - Nibble array compression for 50MB total size

### **Computer Vision Pipeline**
1. **Camera Initialization** - OpenCV VideoCapture with error handling
2. **Face Detection** - 3×3 grid overlay for precise square alignment  
3. **Color Sampling** - Median color extraction from center regions
4. **Classification** - HSV color space analysis for robust detection
5. **Validation** - Ensures exactly 9 squares of each color

### **Optimization Techniques**
- **Bitboard Representation** - 64-bit efficient state encoding
- **Move Pruning** - Eliminates redundant move sequences
- **Heuristic Functions** - Manhattan distance and pattern database lookup
- **Memory Pool Allocation** - Optimized memory management for search algorithms

## 📊 Performance Benchmarks

| Algorithm | 8-Move Scramble | 13-Move Scramble | Memory Usage | Optimality |
|-----------|----------------|------------------|--------------|------------|
| **IDA\*** | ~10ms | ~10ms | ~50MB | ✅ Optimal |
| **IDDFS** | ~3s | ~300s | <1MB | ✅ Optimal |
| **BFS** | ~100ms | >1hr | >8GB | ✅ Optimal |

## 🎯 Project Highlights

- **Graph Algorithm Mastery** - Implementation of advanced search algorithms with heuristic optimization
- **Computer Vision Integration** - Real-world problem solving with camera-based input
- **Performance Engineering** - Achieved 1000x speedup through algorithmic and data structure optimization  
- **Software Architecture** - Clean, modular, object-oriented design following SOLID principles
- **Mathematical Modeling** - Group theory application for Rubik's Cube state representation

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit changes (`git commit -m 'Add amazing feature'`)
4. Push to branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

**Built with ❤️ by [Syed Mehran Ahmed](https://github.com/silentwraith-syed)**