#include "CubeScanner.h"
#include "bits/stdc++.h"
#include <chrono>
#include <thread>

using namespace cv;
using namespace std;

// Static color map definition - moved to function to avoid static initialization order issues
const map<RubiksCube::COLOR, Scalar>& CubeScanner::getColorMap() {
    static const map<RubiksCube::COLOR, Scalar> colorMap = {
        {RubiksCube::COLOR::WHITE,  Scalar(255, 255, 255)},
        {RubiksCube::COLOR::RED,    Scalar(0, 0, 255)},
        {RubiksCube::COLOR::ORANGE, Scalar(0, 165, 255)},
        {RubiksCube::COLOR::YELLOW, Scalar(0, 255, 255)},
        {RubiksCube::COLOR::GREEN,  Scalar(0, 255, 0)},
        {RubiksCube::COLOR::BLUE,   Scalar(255, 0, 0)},
        {RubiksCube::COLOR::UNKNOWN, Scalar(50, 50, 50)}
    };
    return colorMap;
}

CubeScanner::CubeScanner(int camIndex, int boxSize) : boxSize(boxSize) {
    cap.open(camIndex);
    if (!cap.isOpened()) throw runtime_error("Failed to open webcam");
}

CubeScanner::~CubeScanner() {
    cap.release();
    destroyAllWindows();
}

RubiksCube::COLOR CubeScanner::classifyColor(const Vec3b& bgr) {
    Mat bgrPixel(1, 1, CV_8UC3, bgr);
    Mat hsvPixel;
    cvtColor(bgrPixel, hsvPixel, COLOR_BGR2HSV);
    Vec3b hsv = hsvPixel.at<Vec3b>(0, 0);
    int h = hsv[0];

    if (
        bgr[2] > 200 && bgr[1] > 200 && bgr[0] > 200 &&
        abs(bgr[2] - bgr[1]) < 30 &&
        abs(bgr[1] - bgr[0]) < 30 &&
        abs(bgr[0] - bgr[2]) < 30
    ) return RubiksCube::COLOR::WHITE;

    if (h >= 160 && h <= 190) return RubiksCube::COLOR::RED;
    if (h >= 3 && h <= 19)   return RubiksCube::COLOR::ORANGE;
    if (h >= 20 && h <= 30)  return RubiksCube::COLOR::YELLOW;
    if (h >= 60 && h <= 90)  return RubiksCube::COLOR::GREEN;
    if (h >= 100 && h <= 120)return RubiksCube::COLOR::BLUE;

    return RubiksCube::COLOR::WHITE;
}

Vec3b CubeScanner::medianColor(const Mat& frame, int centerX, int centerY, int region) {
    int half = region / 2;
    vector<uchar> B, G, R;
    for (int dy = -half; dy <= half; ++dy)
        for (int dx = -half; dx <= half; ++dx) {
            int x = centerX + dx, y = centerY + dy;
            if (x >= 0 && x < frame.cols && y >= 0 && y < frame.rows) {
                Vec3b bgr = frame.at<Vec3b>(y, x);
                B.push_back(bgr[0]); G.push_back(bgr[1]); R.push_back(bgr[2]);
            }
        }
    sort(B.begin(), B.end()); sort(G.begin(), G.end()); sort(R.begin(), R.end());
    int mid = B.size() / 2;
    return Vec3b(B[mid], G[mid], R[mid]);
}

vector<vector<RubiksCube::COLOR>> CubeScanner::captureFace() {
    Mat frame;
    int rows, cols;

    cout << "Position the cube face in the camera view." << endl;
    cout << "Press SPACEBAR to capture the face when ready." << endl;
    cout << "Make sure the camera window is active (click on it) before pressing keys!" << endl;

    while (true) {
        cap >> frame;
        if (frame.empty()) {
            cout << "Error: Cannot read from camera!" << endl;
            throw runtime_error("Camera feed lost");
        }
        
        rows = frame.rows; cols = frame.cols;
        int startX = (cols - 3 * boxSize) / 2;
        int startY = (rows - 3 * boxSize) / 2;

        // Draw 3x3 grid overlay
        for (int i = 0; i <= 3; ++i) {
            line(frame, Point(startX, startY + i * boxSize), Point(startX + 3 * boxSize, startY + i * boxSize), Scalar(0, 255, 0), 2);
            line(frame, Point(startX + i * boxSize, startY), Point(startX + i * boxSize, startY + 3 * boxSize), Scalar(0, 255, 0), 2);
        }

        // Add instructions
        putText(frame, "Press SPACEBAR to capture", Point(30, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2, LINE_AA);
        putText(frame, "ESC to exit", Point(30, 60), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1, LINE_AA);
        putText(frame, "Click this window first!", Point(30, 90), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 0), 1, LINE_AA);
        
        imshow("Camera Feed - Align Cube Face", frame);
        
        int key = waitKey(1) & 0xFF; // Reduce wait time to 1ms for more responsive input
        if (key == 32) { // SPACEBAR
            cout << "Face captured!" << endl;
            destroyWindow("Camera Feed - Align Cube Face");
            break;
        } else if (key == 27) { // ESC
            destroyWindow("Camera Feed - Align Cube Face");
            throw runtime_error("User cancelled scanning");
        }
    }

    // Capture the final frame for analysis
    cap >> frame;
    int startX = (cols - 3 * boxSize) / 2;
    int startY = (rows - 3 * boxSize) / 2;

    vector<vector<RubiksCube::COLOR>> face(3, vector<RubiksCube::COLOR>(3));
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            int x = startX + j * boxSize + boxSize / 2;
            int y = startY + i * boxSize + boxSize / 2;
            Vec3b bgr = medianColor(frame, x, y);
            face[i][j] = classifyColor(bgr);
        }
    return face;
}

Mat CubeScanner::drawColorFace(const vector<vector<RubiksCube::COLOR>>& faceGrid) {
    int gridSize = 3 * boxSize;
    int padding = 50;
    Mat result(gridSize + padding, gridSize, CV_8UC3, Scalar(0, 0, 0));

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            Rect box(j * boxSize, i * boxSize, boxSize, boxSize);
            rectangle(result, box, getColorMap().at(faceGrid[i][j]), FILLED);
            rectangle(result, box, Scalar(0, 0, 0), 2);
        }

    putText(result, "Press [R] to rescan or [N] for next", Point(10, gridSize + 35), FONT_HERSHEY_SIMPLEX, 0.45, Scalar(255, 255, 255), 1, LINE_AA);
    return result;
}

Mat CubeScanner::drawFullCube(const vector<vector<vector<RubiksCube::COLOR>>>& cubeGrid) {
    int gap = 5, w = 12 * boxSize, h = 9 * boxSize;
    Mat canvas(h, w, CV_8UC3, Scalar(30, 30, 30));

    auto drawFace = [&](int faceIndex, int row, int col) {
        Point topLeft(col * boxSize, row * boxSize);
        rectangle(canvas, Rect(topLeft, Size(3 * boxSize, 3 * boxSize)), Scalar(255, 255, 255), 4);

        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                int x = (col + j) * boxSize;
                int y = (row + i) * boxSize;
                Rect rect(x, y, boxSize - gap, boxSize - gap);
                rectangle(canvas, rect, getColorMap().at(cubeGrid[faceIndex][i][j]), FILLED);
                rectangle(canvas, rect, Scalar(0, 0, 0), 2);
            }
    };

    drawFace(0, 0, 3);
    drawFace(1, 3, 0); drawFace(2, 3, 3); drawFace(3, 3, 6); drawFace(4, 3, 9);
    drawFace(5, 6, 3);

    return canvas;
}

void CubeScanner::scan(RubiksCube& cube) {
    vector<vector<vector<RubiksCube::COLOR>>> cubeGrid(6, vector<vector<RubiksCube::COLOR>>(3, vector<RubiksCube::COLOR>(3, RubiksCube::COLOR::WHITE)));
    
    const string faceNames[] = {"Front", "Right", "Back", "Left", "Top", "Bottom"};
    
    cout << "\n=== Starting Cube Scanning Process ===" << endl;
    cout << "You will scan 6 faces in this order:" << endl;
    for (int i = 0; i < 6; i++) {
        cout << (i + 1) << ". " << faceNames[i] << endl;
    }
    cout << "\nControls:" << endl;
    cout << "- SPACEBAR: Capture current face (click camera window first!)" << endl;
    cout << "- N: Accept and move to next face" << endl;
    cout << "- R: Rescan current face" << endl;
    cout << "- ESC: Cancel scanning" << endl;
    cout << "\nStarting in 3 seconds..." << endl;
    
    // Use a 3-second countdown instead of waiting for Enter
    for (int i = 3; i > 0; i--) {
        cout << i << "..." << endl;
        this_thread::sleep_for(chrono::seconds(1)); // Cross-platform sleep
    }
    cout << "Starting scan!" << endl;

    for (int face = 0; face < 6; face++) {
        cout << "\n--- Scanning Face " << (face + 1) << "/6: " << faceNames[face] << " ---" << endl;
        
        while (true) {
            try {
                auto grid = captureFace();
                cubeGrid[face] = grid;

                Mat faceImg = drawColorFace(grid);
                Mat cubeImg = drawFullCube(cubeGrid);

                imshow("Scanned Face - Review", faceImg);
                imshow("Complete Cube Progress", cubeImg);

                cout << "Face captured! Review the colors in the windows." << endl;
                cout << "Press: [N] Next face, [R] Rescan, [ESC] Cancel" << endl;

                while (true) {
                    int key = waitKey(0) & 0xFF;
                    if (key == 'n' || key == 'N') {
                        cout << faceNames[face] << " face accepted!" << endl;
                        for (int i = 0; i < 3; ++i)
                            for (int j = 0; j < 3; ++j)
                                cube.setColor(static_cast<RubiksCube::FACE>(face), i, j, grid[i][j]);
                        destroyWindow("Scanned Face - Review");
                        goto nextFace;
                    } else if (key == 'r' || key == 'R') {
                        cout << "Rescanning " << faceNames[face] << " face..." << endl;
                        destroyWindow("Scanned Face - Review");
                        break;
                    } else if (key == 27) { // ESC
                        cout << "Scanning cancelled by user." << endl;
                        cap.release();
                        destroyAllWindows();
                        throw runtime_error("Scanning cancelled");
                    }
                }
            } catch (const exception& e) {
                cout << "Error during scanning: " << e.what() << endl;
                cap.release();
                destroyAllWindows();
                throw;
            }
        }
        nextFace:;
    }

    cout << "\n=== Scanning Complete! ===" << endl;
    cout << "All 6 faces have been scanned successfully." << endl;
    
    // Validate the scanned cube
    cout << "\n=== Validating Cube Configuration ===" << endl;
    if (validateCube(cube)) {
        cout << "Cube validation passed! The cube is in a valid, solvable state." << endl;
    } else {
        cout << "Cube validation failed! The scanned cube has an invalid configuration." << endl;
        cout << "Please check your scanning and try again. Common issues:" << endl;
        cout << "- Wrong color detection (check lighting conditions)" << endl;
        cout << "- Incorrect cube orientation during scanning" << endl;
        cout << "- Each color should appear exactly 9 times" << endl;
        cap.release();
        destroyAllWindows();
        throw runtime_error("Invalid cube configuration detected");
    }
    
    cap.release();
    destroyAllWindows();
}

// Cube validation methods
bool CubeScanner::validateCube(const RubiksCube& cube) {
    // Extract cube colors for validation
    vector<vector<vector<RubiksCube::COLOR>>> cubeGrid(6, vector<vector<RubiksCube::COLOR>>(3, vector<RubiksCube::COLOR>(3)));
    
    for (int face = 0; face < 6; face++) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cubeGrid[face][i][j] = cube.getColor(static_cast<RubiksCube::FACE>(face), i, j);
            }
        }
    }
    
    // Perform validation checks
    cout << "Checking color count distribution..." << endl;
    if (!validateColorCount(cubeGrid)) {
        cout << "Invalid color count detected!" << endl;
        return false;
    }
    cout << "Color count validation passed" << endl;
    
    cout << "Checking center piece colors..." << endl;
    if (!validateCenterColors(cubeGrid)) {
        cout << "Invalid center colors detected!" << endl;
        return false;
    }
    cout << "Center color validation passed" << endl;
    
    return true;
}

bool CubeScanner::validateColorCount(const vector<vector<vector<RubiksCube::COLOR>>>& cubeGrid) {
    // Count each color - should be exactly 9 of each
    map<RubiksCube::COLOR, int> colorCount;
    
    // Initialize counts
    colorCount[RubiksCube::COLOR::WHITE] = 0;
    colorCount[RubiksCube::COLOR::YELLOW] = 0;
    colorCount[RubiksCube::COLOR::RED] = 0;
    colorCount[RubiksCube::COLOR::ORANGE] = 0;
    colorCount[RubiksCube::COLOR::GREEN] = 0;
    colorCount[RubiksCube::COLOR::BLUE] = 0;
    
    // Count colors from all faces
    for (int face = 0; face < 6; face++) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                colorCount[cubeGrid[face][i][j]]++;
            }
        }
    }
    
    // Print color counts for debugging
    cout << "Color distribution:" << endl;
    cout << "  White: " << colorCount[RubiksCube::COLOR::WHITE] << endl;
    cout << "  Yellow: " << colorCount[RubiksCube::COLOR::YELLOW] << endl;
    cout << "  Red: " << colorCount[RubiksCube::COLOR::RED] << endl;
    cout << "  Orange: " << colorCount[RubiksCube::COLOR::ORANGE] << endl;
    cout << "  Green: " << colorCount[RubiksCube::COLOR::GREEN] << endl;
    cout << "  Blue: " << colorCount[RubiksCube::COLOR::BLUE] << endl;
    
    // Check if each color appears exactly 9 times
    for (auto& pair : colorCount) {
        if (pair.second != 9) {
            cout << "Error: Color " << static_cast<int>(pair.first) << " appears " << pair.second << " times (should be 9)" << endl;
            return false;
        }
    }
    
    return true;
}

bool CubeScanner::validateCenterColors(const vector<vector<vector<RubiksCube::COLOR>>>& cubeGrid) {
    // Check that all center pieces (1,1) have different colors
    set<RubiksCube::COLOR> centerColors;
    
    for (int face = 0; face < 6; face++) {
        RubiksCube::COLOR centerColor = cubeGrid[face][1][1]; // Center piece is at [1][1]
        if (centerColors.find(centerColor) != centerColors.end()) {
            cout << "Error: Duplicate center color detected on face " << face << endl;
            return false;
        }
        centerColors.insert(centerColor);
    }
    
    // Should have exactly 6 different center colors
    if (centerColors.size() != 6) {
        cout << "Error: Found " << centerColors.size() << " different center colors (should be 6)" << endl;
        return false;
    }
    
    return true;
}
