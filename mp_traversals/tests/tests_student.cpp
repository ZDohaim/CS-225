// #include <catch2/catch_test_macros.hpp>
// #include "cs225/PNG.h"
// #include "cs225/HSLAPixel.h"
// #include "Animation.h"
// #include "FloodFilledImage.h"
// #include "ImageTraversal/DFS.h"
// #include "colorPicker/SolidColorPicker.h"

// using namespace cs225;

// TEST_CASE("My Test Case: FloodFill with SolidColorPicker and DFS", "") {
//     PNG img;
//     img.readFromFile("tests/original.png"); // Make sure this file exists

//     FloodFilledImage image(img);
//     DFS dfs(img, Point(0, 0), 0.2); // Assuming DFS is properly implemented
//     HSLAPixel color(120, 1.0, 0.5); // A green color for the fill
//     SolidColorPicker solidColor(color);

//     image.addFloodFill(dfs, solidColor);
//     Animation animation = image.animate(1000); // Using a large frameInterval to simplify

//     PNG lastFrame = animation.getFrame(animation.frameCount() - 1);
//     lastFrame.writeToFile("tests/floodfill_solidcolor_dfs.png"); // Output for visual verification

//     // This variable tracks whether you've written a meaningful test case
//     bool student_wrote_test_case = true;

//     // Check if a specific pixel has been colored as expected
//     HSLAPixel & pixel = lastFrame.getPixel(10, 10); // Assuming this pixel should be filled
    
//     // Verify that the pixel has been colored as expected, thus fulfilling the test case
//     REQUIRE( pixel == color );
//     REQUIRE( student_wrote_test_case );
// }
