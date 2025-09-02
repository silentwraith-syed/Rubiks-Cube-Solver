//
// Created by Syed Mehran Ahmed
//

#include <bits/stdc++.h>
#include <chrono>
//#include "Model/RubiksCube3dArray.cpp"
//#include "Model/RubiksCube1dArray.cpp"
//#include "Model/RubiksCubeBitboard.cpp"
#include "Solver/DFSSolver.h"
#include "Solver/BFSSolver.h"
#include "Solver/IDDFSSolver.h"
#include "Solver/IDAstarSolver.h"
//#include "PatternDatabases/CornerPatternDatabase.h"
#include "PatternDatabases/CornerDBMaker.h"
#include "Scanner/CubeScanner.h"

using namespace std;

int main() {
    cout << "Starting Rubik's Cube Solver with OpenCV Camera Support..." << endl;
//    RubiksCube3dArray object3DArray;
//    RubiksCube1dArray object1dArray;
//    RubiksCubeBitboard objectBitboard;
//
//    object3DArray.print();
//
//    if (object3DArray.isSolved()) cout << "SOLVED\n\n";
//    else cout << "NOT SOLVED\n\n";
//
//    if (object1dArray.isSolved()) cout << "SOLVED\n\n";
//    else cout << "NOT SOLVED\n\n";
//
//    if (objectBitboard.isSolved()) cout << "SOLVED\n\n";
//    else cout << "NOT SOLVED\n\n";
//
//    objectBitboard.u();
//    object3DArray.u();
//    object1dArray.u();
//    objectBitboard.print();
//    object3DArray.print();
//    object1dArray.print();
//
//    objectBitboard.l();
//    object3DArray.l();
//    object1dArray.l();
//    objectBitboard.print();
//    object3DArray.print();
//    object1dArray.print();
//
//    objectBitboard.f();
//    object3DArray.f();
//    object1dArray.f();
//    objectBitboard.print();
//    object3DArray.print();
//    object1dArray.print();
//
//    objectBitboard.r();
//    object3DArray.r();
//    object1dArray.r();
//    objectBitboard.print();
//    object3DArray.print();
//    object1dArray.print();
//
//    objectBitboard.b();
//    object3DArray.b();
//    object1dArray.b();
//    objectBitboard.print();
//    object3DArray.print();
//    object1dArray.print();
//
//    objectBitboard.d();
//    object3DArray.d();
//    object1dArray.d();
//    objectBitboard.print();
//    object3DArray.print();
//    object1dArray.print();
//
//    if (object3DArray.isSolved()) cout << "SOLVED\n\n";
//    else cout << "NOT SOLVED\n\n";
//
//    if (object1dArray.isSolved()) cout << "SOLVED\n\n";
//    else cout << "NOT SOLVED\n\n";
//
//    if (objectBitboard.isSolved()) cout << "SOLVED\n\n";
//    else cout << "NOT SOLVED\n\n";
//
//    objectBitboard.dPrime();
//    object3DArray.dPrime();
//    object1dArray.dPrime();
//    objectBitboard.print();
//    object3DArray.print();
//    object1dArray.print();
//
//    objectBitboard.bPrime();
//    object3DArray.bPrime();
//    object1dArray.bPrime();
//    objectBitboard.print();
//    object3DArray.print();
//    object1dArray.print();
//
//    objectBitboard.rPrime();
//    object3DArray.rPrime();
//    object1dArray.rPrime();
//    objectBitboard.print();
//    object3DArray.print();
//    object1dArray.print();
//
//    objectBitboard.fPrime();
//    object3DArray.fPrime();
//    object1dArray.fPrime();
//    objectBitboard.print();
//    object3DArray.print();
//    object1dArray.print();
//
//    objectBitboard.lPrime();
//    object3DArray.lPrime();
//    object1dArray.lPrime();
//    objectBitboard.print();
//    object3DArray.print();
//    object1dArray.print();
//
//    objectBitboard.uPrime();
//    object3DArray.uPrime();
//    object1dArray.uPrime();
//    objectBitboard.print();
//    object3DArray.print();
//    object1dArray.print();
//
//    if (object3DArray.isSolved()) cout << "SOLVED\n\n";
//    else cout << "NOT SOLVED\n\n";
//
//    if (object1dArray.isSolved()) cout << "SOLVED\n\n";
//    else cout << "NOT SOLVED\n\n";
//
//    if (objectBitboard.isSolved()) cout << "SOLVED\n\n";
//    else cout << "NOT SOLVED\n\n";

    // Create two Cubes ------------------------------------------------------------------------------------------

//    RubiksCube3dArray cube1;
//    RubiksCube3dArray cube2;

//    RubiksCube1dArray cube1;
//    RubiksCube1dArray cube2;

//    RubiksCubeBitboard cube1;
//    RubiksCubeBitboard cube2;


//  Equality and assignment of cubes --------------------------------------------------------------------------

//    if(cube1 == cube2) cout << "Is equal\n";
//    else cout << "Not Equal\n";
//
//    cube1.randomShuffleCube(1);
//
//    if(cube1 == cube2) cout << "Is equal\n";
//    else cout << "Not Equal\n";
//
//    cube2 = cube1;
//
//    if(cube1 == cube2) cout << "Is equal\n";
//    else cout << "Not Equal\n";


//  Unordered_map of Cubes  ------------------------------------------------------------------------------------


//    unordered_map<RubiksCube3dArray, bool, Hash3d> mp1;

//    unordered_map<RubiksCube1dArray, bool, Hash1d> mp1;

//    unordered_map<RubiksCubeBitboard, bool, HashBitboard> mp1;
//
//    mp1[cube1] = true;
//    cube2.randomShuffleCube(8);
//    if (mp1[cube1]) cout << "Cube1 is present\n";
//    else cout << "Cube1 is not present\n";
//
//    if (mp1[cube2]) cout << "Cube2 is present\n";
//    else cout << "Cube2 is not present\n";
//

// DFS Solver Testing __________________________________________________________________________________________
//    RubiksCube3dArray cube;
//    cube.print();
//
//    vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(6);
//    for (auto move: shuffle_moves) cout << cube.getMove(move) << " ";
//    cout << "\n";
//    cube.print();
//
//    DFSSolver<RubiksCube3dArray, Hash3d> dfsSolver(cube, 8);
//    vector<RubiksCube::MOVE> solve_moves = dfsSolver.solve();
//
//    for (auto move: solve_moves) cout << cube.getMove(move) << " ";
//    cout << "\n";
//    dfsSolver.rubiksCube.print();


//BFS Solver -----------------------------------------------------------------------------------------------------
//    RubiksCubeBitboard cube;
//    cube.print();
//
//    vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(6);
//    for(auto move: shuffle_moves) cout << cube.getMove(move) << " ";
//    cout << "\n";
//    cube.print();
//
//    BFSSolver<RubiksCubeBitboard, HashBitboard> bfsSolver(cube);
//    vector<RubiksCube::MOVE> solve_moves = bfsSolver.solve();
//
//    for(auto move: solve_moves) cout << cube.getMove(move) << " ";
//    cout << "\n";
//    bfsSolver.rubiksCube.print();

// IDDFS Solver ----------------------------------------------------------------------------------------------------
//    RubiksCubeBitboard cube;
//    cube.print();
//
//    vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(7);
//    for (auto move: shuffle_moves) cout << cube.getMove(move) << " ";
//    cout << "\n";
//    cube.print();
//
//    IDDFSSolver<RubiksCubeBitboard, HashBitboard> iddfsSolver(cube, 7);
//    vector<RubiksCube::MOVE> solve_moves = iddfsSolver.solve();
//
//    for (auto move: solve_moves) cout << cube.getMove(move) << " ";
//    cout << "\n";
//    iddfsSolver.rubiksCube.print();

// IDA* SOLVER ---------------------------------------------------------------------------------------------------
//    RubiksCubeBitboard cube;
//    cube.print();
//
//    vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(5);
//    for (auto move: shuffle_moves) cout << cube.getMove(move) << " ";
//    cout << "\n";
//    cube.print();
//
//    IDAstarSolver<RubiksCubeBitboard, HashBitboard> idAstarSolver(cube);
//    vector<RubiksCube::MOVE> solve_moves = idAstarSolver.solve();
//    for (auto move: solve_moves) cout << cube.getMove(move) << " ";
//    cout << "\n";
//    idAstarSolver.rubiksCube.print();

// CornerPatternDatabase Testing ---------------------------------------------------------------------------------

//    CornerPatternDatabase cornerDB;
//    RubiksCubeBitboard cube;
//    cube.print();
//
//    cout << (int)cornerDB.getNumMoves(cube) << "\n";
//
//    cornerDB.setNumMoves(cube, 5);
//
//    cout << (int)cornerDB.getNumMoves(cube) << "\n";
//
//    cube.randomShuffleCube(1);
//    cube.print();
//    cout << (int)cornerDB.getNumMoves(cube) << "\n";
//
//    cornerDB.setNumMoves(cube, 6);
//
//    cout << (int)cornerDB.getNumMoves(cube) << "\n";


// CornerDBMaker Testing --------------------------------------------------------------------------
    // Path relative to the build directory where the executable runs
    string fileName = "..\\Databases\\cornerDepth5V1.txt";

//    Code to create Corner Database
//    CornerDBMaker dbMaker(fileName, 0x99);
//    dbMaker.bfsAndStore();

    cout << "Rubik's Cube Solver Options:" << endl;
    cout << "1. Demo with random scramble" << endl;
    cout << "2. Scan real cube with camera" << endl;
    cout << "Enter your choice (1 or 2): ";
    
    int choice;
    cin >> choice;
    cin.ignore(); // Clear the input buffer
    
    RubiksCubeBitboard cube;
    
    if (choice == 2) {
        cout << "\nStarting camera scanner..." << endl;
        cout << "=== Camera Scanning Instructions ===" << endl;
        cout << "1. Make sure your camera is connected and working" << endl;
        cout << "2. You'll scan 6 faces: Front, Right, Back, Left, Top, Bottom" << endl;
        cout << "3. For each face:" << endl;
        cout << "   - Position the face in the green grid" << endl;
        cout << "   - Press SPACEBAR to capture" << endl;
        cout << "   - Review colors, then press N for next or R to rescan" << endl;
        cout << "4. Good lighting is important for accurate color detection" << endl;
        cout << "\nPress Enter to start camera..." << endl;
        cin.get();
        
        try {
            CubeScanner scanner(0); // Use default camera (index 0)
            scanner.scan(cube);
            cout << "Camera scanning completed successfully!" << endl;
        } catch (const exception& e) {
            cout << "Camera error: " << e.what() << endl;
            cout << "Falling back to demo mode..." << endl;
            // Create a fresh, clean cube for demo mode since the scanned one is invalid
            cube = RubiksCubeBitboard(); // Reset to solved state
            choice = 1; // Fall back to demo
        }
    }
    
    if (choice == 1) {  // Only run demo mode if explicitly chosen or fallback occurred
        cout << "Creating scrambled cube..." << endl;
        auto shuffleMoves = cube.randomShuffleCube(13);
        cube.print();  // The print() method already includes "Rubik's Cube:" header
        cout << "Scramble moves: ";
        for (auto move: shuffleMoves) cout << cube.getMove(move) << " ";
        cout << "\n" << endl;
    }

    // Let user choose solving algorithm
    cout << "Choose solving algorithm:" << endl;
    cout << "1. BFS (Basic, slow but guaranteed optimal)" << endl;
    cout << "2. IDDFS (Faster, memory efficient, optimal)" << endl;
    cout << "3. IDA* (Best, uses heuristics, optimal)" << endl;
    cout << "Enter your choice (1, 2, or 3): ";
    
    int algorithmChoice;
    cin >> algorithmChoice;
    cin.ignore();

    vector<RubiksCube::MOVE> moves;
    auto startTime = chrono::high_resolution_clock::now();

    if (algorithmChoice == 1) {
        cout << "WARNING: BFS selected! This may take hours for complex scrambles." << endl;
        cout << "BFS explores all possible states and can be extremely slow." << endl;
        cout << "Recommended: Press Ctrl+C and choose option 3 (IDA*) instead." << endl;
        cout << "Continue with BFS anyway? (y/N): ";
        
        char confirm;
        cin >> confirm;
        cin.ignore();
        
        if (confirm != 'y' && confirm != 'Y') {
            cout << "Switching to IDA* for better performance..." << endl;
            algorithmChoice = 3;
        } else {
            cout << "Solving cube using BFS (this will likely take a very long time)..." << endl;
            cout << "Press Ctrl+C if you want to cancel." << endl;
            BFSSolver<RubiksCubeBitboard, HashBitboard> bfsSolver(cube);
            moves = bfsSolver.solve();
        }
    }
    if (algorithmChoice == 2) {
        cout << "Solving cube using IDDFS (faster iterative deepening)..." << endl;
        IDDFSSolver<RubiksCubeBitboard, HashBitboard> iddfsSolver(cube, 10); // Max depth 10
        moves = iddfsSolver.solve();
    }
    if (algorithmChoice == 3) {
        cout << "Solving cube using IDA* with Korf's algorithm (most efficient)..." << endl;
        cout << "Loading pattern database..." << endl;
        IDAstarSolver<RubiksCubeBitboard, HashBitboard> idAstarSolver(cube, fileName);
        moves = idAstarSolver.solve();
    }

    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);

    cout << "Solution found in " << duration.count() << " milliseconds!" << endl;
    cout << "Solution length: " << moves.size() << " moves" << endl;
    cout << "Solved cube state:" << endl;
    
    // Apply moves to show solved state
    RubiksCubeBitboard solvedCube = cube;
    for (auto move : moves) {
        solvedCube.move(move);
    }
    solvedCube.print();
    
    cout << "Solution moves: ";
    for (auto move: moves) cout << cube.getMove(move) << " ";
    cout << "\n" << endl;

    cout << "Program completed successfully!" << endl;
    cout << "Press Enter to exit..." << endl;
    cin.get(); // Wait for user input before exiting

    return 0;
}