/*
 File name: CS112_A3_Part2B_S16_20230269_20230134_20230520.cpp

 Description: This program displays a menu of choices for the user continuously until the user
 chooses exit. The menu will allow the user to load an image and choose the filter to apply. The
 user can choose (save) to store the image resulting from applying the filter after specifying the
 name of the target file. The program will loop until the user chooses exit.
******************************************
 Author 1:
 Omar Hani Tohami
 Parts he did: Black and white filter
               Flip filter
               Crop filter
               Resize filter
               Infrared filter
               purple filter
               sunlight filter
               TV filter
               Menu
 ID: 20230269
 Section no.: S16
 Email: otohami95@gmail.com
*******************************************
 Author 2:
 Dima Khaled Allam
 Parts she did: Grayscale filter
                Darken and Lighten filter
                Merge filter
                edge detection filter
                Validation of input and output paths
 ID: 20230134
 Section no.: S16
 Email: dkh3462@gmail.com
********************************************
 Author 3:
 Youana Joseph Ayoub
 Parts she did: Frame filter
                Invert filter
                Blur filter
                Rotate filter
                Skew filter
                Oil painting filter
 ID: 20230520
 Section no.: S16
 Email: youanajoseph8@gmail.com
 */

// link for the system diagram: https://drive.google.com/file/d/1x5_XyOnNuNGI0AwpI00jH6xQARLQswyo/view?usp=sharing
// link for github repository: https://github.com/OmarTohami/Filters.git
#include <iostream>
#include <filesystem> // for validition of image path
#include <string>
#include <cmath> // for skew filter
#include <random> // for tv filter
#include "Image_Class.h"
using namespace std;
namespace fs = std::filesystem;

string input_Path = ""; // global path variable for input image and multiple filters editing
string temp_path; // for saving on the original image

// Define menu.
void Menu(){
    cout << "Choose the filter you want to apply or if you want to load, save an image or end the program: \n";
    cout << "1- Black and White filter\n";
    cout << "2- Gray scale filter\n";
    cout << "3- Flip filter\n";
    cout << "4- Darken and Lighten filter\n";
    cout << "5- Add a Frame\n";
    cout << "6- invert filter\n";
    cout << "7- Crop filter\n";
    cout << "8- Resize filter\n";
    cout << "9- Merge filter\n";
    cout << "10- Oil Painting filter\n";
    cout << "11- Infrared filter\n";
    cout << "12- Purple filter\n";
    cout << "13- Sunlight filter\n";
    cout << "14- Rotate filter\n";
    cout << "15- Edge Detection filter\n";
    cout << "16- Blur filter\n";
    cout << "17- Image Skewing filter\n";
    cout << "18- Tv filter\n";
    cout << "19- Load an image\n";
    cout << "20- Save an image\n";
    cout << "21- End\n";
}

// Define a function to check the validty of the input at the menu.
int getValidInput(){
    int choice;
    while(true) {
        // Get user's choice.
        cout << "Enter your choice: ";
        cin >> choice;
        // check the validty of the choice.
        if(cin.good() && choice >= 1 && choice <= 21) {
            return choice;
        }
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Invalid input. Please enter a valid option." << endl;
    }
}

// function to check validity for 2 choices.
int getValidInput_2Choices(){
    int choice;
    while(true) {
        // Get user's choice.
        cout << "Enter your choice: ";
        cin >> choice;
        // check the validty of the choice.
        if(cin.good() && choice >= 1 && choice <= 2) {
            return choice;
        }
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Invalid input. Please enter a valid option." << endl;
    }
}

// function to check validity for 3 choices.
int getValidInput_3Choices(){
    int choice;
    while(true) {
        // Get user's choice.
        cout << "Enter your choice: ";
        cin >> choice;
        // check the validty of the choice.
        if(cin.good() && choice >= 1 && choice <= 3) {
            return choice;
        }
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Invalid input. Please enter a valid option." << endl;
    }
}

// function to check validity for 4 choices.
int getValidInput_4Choices(){
    int choice;
    while(true) {
        // Get user's choice.
        cout << "Enter your choice: ";
        cin >> choice;
        // check the validty of the choice.
        if(cin.good() && choice >= 1 && choice <= 4) {
            return choice;
        }
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Invalid input. Please enter a valid option." << endl;
    }
}

// function to check the validity of the ratio number at resize filter.
float getValidInput_ratio(){
    float input;
    cout << "Enter the resize ratio (integer for increase size or decimal for decrease size): ";
    while(true) {
        // Get user's input.
        cin >> input;
        // check the validty of the input.
        if(cin.good() && input > 0) {
            return input;
        }
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Invalid input. Please enter a valid number." << endl;
    }
}
// function to check the validity of the input path
string getValidInputPath(string imagePath) {
    // Check if the file exists
    if (!fs::exists(imagePath)) {
        cout << "This file does not exist. Please enter a valid path\n";
        cout << "Notice that file extension must be .jpg or .bmp. or .png or .tga: ";
        return ""; // Return an empty string if the file does not exist
    }
    // Check if the file extension is ".jpg" or ".bmp" or ".png" or ".tga"
    string extension = fs::path(imagePath).extension().string();
    if (extension != ".jpg" && extension != ".bmp" && extension != ".png"  && extension != ".tga") {
        cout << "Invalid file extension. Extensions must be .jpg or .bmp. or .png or .tga\n";
        cout << "Enter a valid extension: ";
        return ""; // Return an empty string if the file extension is invalid
    }
    return imagePath; // Return the input path if it is valid
}

// function to check the validity of the output path
string getValidOutputPath(string outputPath) {
    bool isValid = false;
    while (!isValid) {
        // Check if the file extension is ".jpg", ".bmp", ".png", or ".tga"
        string extension = fs::path(outputPath).extension().string();
        if (extension != ".jpg" && extension != ".bmp" && extension != ".png" && extension != ".tga") {
            cout << "Invalid file extension. Extensions must be .jpg, .bmp, .png, or .tga.\n";
            cout << "Enter a valid output path: ";
            getline(cin, outputPath);
            continue; // Continue to the next iteration of the loop
        }
        isValid = true; // Set isValid to true to exit the loop
    }
    return outputPath;
}

// function for saving image
void SaveImage(string input_path){
    Image image(input_Path);
    cout << "Do you want to overwrite the original image or save a copy? " << endl;
    cout << "1- Overwrite the original image" << endl;
    cout << "2- Save a copy and keep the original image" << endl;
    cout << "3- Return to main menu" << endl;
    int saveChoice = getValidInput_3Choices();
    // consume the remaining newline character
    string dummy;
    getline(cin, dummy);
    string outputPath;
    if (saveChoice == 1) {
        outputPath = temp_path;
    }
    else if (saveChoice == 2) {
        cout << "Enter the output path to save the copy: ";
        getline(cin, outputPath);
    }
    else if (saveChoice == 3) {
        return;
    }
    image.saveImage(getValidOutputPath(outputPath));
}

// function for flip filter
void flip(string inputPath){
    Image image(inputPath);
    int width = image.width;
    int height = image.height;
    cout << "Choose the flip to apply:" << endl;
    cout << "1- Horizontal flip\n";
    cout << "2- Vertical flip\n";
    cout << "3- Return to main menu\n";
    int flip_choice = getValidInput_3Choices();
    // Function to flip image horizontally
    if (flip_choice == 1) {
        for (int i = 0; i < height; ++i) {
            int j_start = 0, j_end = width - 1;
            for (; j_start < j_end; ++j_start, --j_end) {
                // Swap pixel colors
                float temp0 = image(j_start, i, 0);
                float temp1 = image(j_start, i, 1);
                float temp2 = image(j_start, i, 2);
                image(j_start, i, 0) = image(j_end, i, 0);
                image(j_start, i, 1) = image(j_end, i, 1);
                image(j_start, i, 2) = image(j_end, i, 2);
                image(j_end, i, 0) = temp0;
                image(j_end, i, 1) = temp1;
                image(j_end, i, 2) = temp2;
            }
        }
    }
        // Function to flip image vertically
    else if (flip_choice == 2) {
        for (int j = 0; j < width; ++j) {
            int i_start = 0, i_end = height - 1;
            for (; i_start < i_end; ++i_start, --i_end) {
                // Swap pixel colors
                float temp0 = image(j, i_start, 0);
                float temp1 = image(j, i_start, 1);
                float temp2 = image(j, i_start, 2);
                image(j, i_start, 0) = image(j, i_end, 0);
                image(j, i_start, 1) = image(j, i_end, 1);
                image(j, i_start, 2) = image(j, i_end, 2);
                image(j, i_end, 0) = temp0;
                image(j, i_end, 1) = temp1;
                image(j, i_end, 2) = temp2;
            }
        }
    }
    else if (flip_choice == 3) {
        return;
    }
    string outputPath = "OMAR.jpg";
    string filename = getValidOutputPath(outputPath);
    image.saveImage(filename);
    input_Path = filename;
}

// Function for invert colours filter
void invert_image_color(string inputPath) {
    Image image(inputPath);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                // Invert the pixel by subtracting its intensity from 255
                unsigned int inverted = 255 - image(i, j, k);
                image(i, j, k) = inverted;
            }
        }
    }
    string outputPath = "OMAR.jpg";
    string filename = getValidOutputPath(outputPath);
    image.saveImage(filename);
    input_Path = filename;
}

// function for black and white filter
void blackAndwhite(string inputPath){
    Image image(inputPath);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // Initialize average value
            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k) {
                // Accumulate pixel values
                avg += image(i, j, k);
            }
            // Calculate average
            avg /= 3;
            // Set all channels to black if average is below threshold,
            // or white otherwise
            image(i, j, 0) = (avg < 116) ? 0 : 255;
            image(i, j, 1) = (avg < 116) ? 0 : 255;
            image(i, j, 2) = (avg < 116) ? 0 : 255;
        }
    }
    string outputPath = "OMAR.jpg";
    string filename = getValidOutputPath(outputPath);
    image.saveImage(filename);
    input_Path = filename;
}

// function for old tv filter.
void Tv_Filter(string inputPath) {
    Image image(inputPath);
    // Initialize random number generator
    mt19937 gen(random_device{}());
    uniform_int_distribution<> dis(10, 30);
    // Apply filter to the image both horizontally and vertically
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            if (i % 2 == 0 && j % 2 == 0) {
                // Even row and column, add up to 3 dots to each pixel
                for (int k = 0; k < image.channels; ++k) {
                    int numDots = rand() % 2; // Generate a random number between 0 and 2
                    for (int n = 0; n < numDots; ++n) {
                        unsigned int random = dis(gen);
                        image(i, j, k) = image(i, j, k) + random > 255 ? 255 : image(i, j, k) + random;
                    }
                }
            } else if (i % 2 == 1 && j % 2 == 0) {
                // Odd row and even column, subtract up to 3 dots from each pixel
                for (int k = 0; k < image.channels; ++k) {
                    int numDots = rand() % 2; // Generate a random number between 0 and 1
                    for (int n = 0; n < numDots; ++n) {
                        unsigned int random = dis(gen);
                        image(i, j, k) = image(i, j, k) + random > 255 ? 255 : image(i, j, k) + random;
                    }
                }
            } else if (i % 2 == 0 && j % 2 == 1) {
                // Even row and odd column, subtract up to 3 dots from each pixel
                for (int k = 0; k < image.channels; ++k) {
                    int numDots = rand() % 2; // Generate a random number between 0 and 1
                    for (int n = 0; n < numDots; ++n) {
                        unsigned int random = dis(gen);
                        image(i, j, k) = image(i, j, k) - random < 0 ? 0 : image(i, j, k) - random;
                    }
                }
            } else if (i % 2 == 1 && j % 2 == 1) {
                // Odd row and odd column, add up to 3 dots to each pixel
                for (int k = 0; k < image.channels; ++k) {
                    int numDots = rand() % 2; // Generate a random number between 0 and 2
                    for (int n = 0; n < numDots; ++n) {
                        unsigned int random = dis(gen);
                        image(i, j, k) = image(i, j, k) + random < 0 ? 0 : image(i, j, k) - random;
                    }
                }
            }
        }
    }
    string outputPath = "OMAR.jpg";
    string filename = getValidOutputPath(outputPath);
    image.saveImage(filename);
    input_Path = filename;
}

// function for rotate filter
void rotate(string inputPath) {
    try {
        Image image(inputPath); // Load the input image
        int width = image.width;
        int height = image.height;
        cout << "Which rotation do you want:" << endl;
        cout << "1- Rotate clockwise by 90 degrees" << endl;
        cout << "2- Rotate clockwise by 180 degrees" << endl;
        cout << "3- Rotate clockwise by 270 degrees" << endl;
        cout << "4- Return to main menu" << endl;
        int rotate_choice = getValidInput_4Choices();
        // Extracting filename without extension
        size_t dotIndex = inputPath.find_last_of(".");
        string baseFileName = inputPath.substr(0, dotIndex);
        string rotationString;
        if (rotate_choice == 1) {
            rotationString = "_90_degrees";
            Image rotatedImage(height, width); // Rotated image will have height and width swapped
            for (int i = 0; i < width; ++i) {
                for (int j = 0; j < height; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        rotatedImage(height - 1 - j, i, k) = image(i, j, k);
                    }
                }
            }
            string outputPath = "OMAR.jpg";
            string filename = getValidOutputPath(outputPath);
            rotatedImage.saveImage(filename);
            input_Path = filename;
        } else if (rotate_choice == 2) {
            rotationString = "_180_degrees";
            Image rotatedImage(width, height); // Rotated image will have the same dimensions
            for (int i = 0; i < width; ++i) {
                for (int j = 0; j < height; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        rotatedImage(width - 1 - i, height - 1 - j, k) = image(i, j, k);
                    }
                }
            }
            string outputPath = "OMAR.jpg";
            string filename = getValidOutputPath(outputPath);
            rotatedImage.saveImage(filename);
            input_Path = filename;
        } else if (rotate_choice == 3) {
            rotationString = "_270_degrees";
            Image rotatedImage(height, width); // Rotated image will have height and width swapped
            for (int i = 0; i < width; ++i) {
                for (int j = 0; j < height; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        rotatedImage(j, width - 1 - i, k) = image(i, j, k);
                    }
                }
            }
            string outputPath = "OMAR.jpg";
            string filename = getValidOutputPath(outputPath);
            rotatedImage.saveImage(filename);
            input_Path = filename;
        } else {
            cout << "Invalid choice\n" << endl;
            return;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

}

// function for infrared filter
void Infrared(string inputPath) {
    Image image(inputPath);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                if (k == 0) {
                    image(i, j, k) = 255; // set red channel to 255
                } else {
                    image(i, j, k) = 255 - image(i, j, k); // invert the rest of colors
                }
            }
        }
    }
    string outputPath = "OMAR.jpg";
    string filename = getValidOutputPath(outputPath);
    image.saveImage(filename);
    input_Path = filename;
}

// function for purple filter
void Purple(string inputPath) {
    Image image(inputPath);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                if (k == 1) {
                    image(i, j, k) *= 0.62;
                }
            }
        }
    }
    string outputPath = "OMAR.jpg";
    string filename = getValidOutputPath(outputPath);
    image.saveImage(filename);
    input_Path = filename;
}

// function for sunlight filter
void Sunlight(string inputPath) {
    Image image(inputPath);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                if (k == 0) {
                    image(i, j, k) *= 0.8;
                }
                if (k == 1) {
                    image(i, j, k) *= 0.8;
                }
                if (k == 2) {
                    image(i, j, k) *= 0.48;
                }
            }
        }
    }
    string outputPath = "OMAR.jpg";
    string filename = getValidOutputPath(outputPath);
    image.saveImage(filename);
    input_Path = filename;
}

// function for grayscale filter
void grayscale(string inputPath){
    Image image(inputPath);
    for(int i = 0; i < image.width; ++i){
        for(int j = 0; j < image.height; ++j){
            //initialize average value
            unsigned int avg = 0;
            for(int k = 0; k < image.channels; ++k){
                //accumulate pixel values
                avg += image(i, j, k);
            }
            //calculate average
            avg = avg / 3;
            //set all channels to the average value
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }
    string outputPath = "OMAR.jpg";
    string filename = getValidOutputPath(outputPath);
    image.saveImage(filename);
    input_Path = filename;
}

// function for crop filter
void cropImage(string inputPath) {
    Image image(inputPath);
    int width = image.width;
    int height = image.height;
    int x, y;
    int crop_width, crop_height;
    cout << "Enter the x-coordinate of the cropped area (smaller than or equal to " << width - 1 << "): ";
    cin >> x;
    while(true){
        if (x < 0 || x >= width) {
            cout << "Invalid x-coordinate, please enter a value between 0 and " << width - 1 << endl;
            cin >> x;
        } else {
            break;
        }
    }
    cout << "Enter the y-coordinate of the cropped area (smaller than or equal to " << height - 1 << "): ";
    cin >> y;
    while(true){
        if (y < 0 || y >= height) {
            cout << "Invalid y-coordinate, please enter a value between 0 and " << height - 1 << endl;
            cin >> y;
        } else {
            break;
        }
    }
    cout << "Enter the width of the cropped area (smaller than or equal to " << width << "): ";
    cin >> crop_width;
    while(true){
        if (crop_width <= 0 || crop_width > width) {
            cout << "Invalid width, please enter a value between 1 and " << width << endl;
            cin >> crop_width;
        } else {
            break;
        }
    }
    cout << "Enter the height of the cropped area (smaller than or equal to " << height << "): ";
    cin >> crop_height;
    while(true){
        if (crop_height <= 0 || crop_height > height) {
            cout << "Invalid height, please enter a value between 1 and " << height << endl;
            cin >> crop_height;
        } else {
            break;
        }
    }
    // Calculate the adjusted crop_height based on the given y-coordinate
    int adjusted_crop_height = crop_height;
    if (y + adjusted_crop_height > height) {
        adjusted_crop_height = height - y;
    }
    Image cropped_image(crop_width, adjusted_crop_height);
    for (int i = 0; i < adjusted_crop_height; ++i) {
        for (int j = 0; j < crop_width; ++j) {
            // Copy the cropped pixel values to the new image
            cropped_image(j, i, 0) = image(x + j, y + i, 0);
            cropped_image(j, i, 1) = image(x + j, y + i, 1);
            cropped_image(j, i, 2) = image(x + j, y + i, 2);
        }
    }
    string outputPath = "OMAR.jpg";
    string filename = getValidOutputPath(outputPath);
    cropped_image.saveImage(outputPath);
    input_Path = filename;
}

// function for resize image by dimensions.
void resizeImageByDimensions(string inputPath) {
    Image image(inputPath);
    cout << "Enter the new width: ";
    int new_width;
    cin >> new_width;
    cout << "Enter the new height: ";
    int new_height;
    cin >> new_height;
    int width = image.width;
    int height = image.height;
    while(true){
        if (new_width <= 0 || new_height <= 0) {
            cout << "Invalid dimensions, please enter values greater than zero" << endl;
            cin >> new_width;
            cin >> new_height;
        } else {
            break;
        }
    }
    // Calculate the ratio to resize
    float ratio_width = (float)new_width / width;
    float ratio_height = (float)new_height / height;
    Image resized_image(new_width, new_height);
    for (int i = 0; i < new_height; ++i) {
        for (int j = 0; j < new_width; ++j) {
            // Copy the source pixel to the new image
            int cx = (int)((j) * (width - 1.0) / (new_width - 1.0));
            int cy = (int)((i) * (height - 1.0) / (new_height - 1.0));
            float r = image(cx, cy, 0);
            float g = image(cx, cy, 1);
            float b = image(cx, cy, 2);
            resized_image(j, i, 0) = r;
            resized_image(j, i, 1) = g;
            resized_image(j, i, 2) = b;
        }
    }
    string outputPath = "OMAR.jpg";
    string filename = getValidOutputPath(outputPath);
    resized_image.saveImage(outputPath);
    input_Path = filename;
}

// function for resize image by ratio.
void resizeImageByRatio(string inputPath, float ratio) {
    Image image(inputPath);
    int width = image.width;
    int height = image.height;
    while (true) {
        if (ratio <= 0) {
            cout << "Invalid ratio, please enter a positive value." << endl;
            ratio = getValidInput_ratio();
        }
        else
        {
            break;
        }
    }
    // Calculate the new dimensions based on the ratio
    double new_width = width * ratio;
    double new_height = height * ratio;
    Image resized_image(static_cast<int>(new_width), static_cast<int>(new_height));
    for (int i = 0; i < static_cast<int>(new_height); ++i) {
        for (int j = 0; j < static_cast<int>(new_width); ++j) {
            // Copy the source pixel to the new image
            int cx = static_cast<int>((j) * (width - 1.0) / (new_width - 1.0));
            int cy = static_cast<int>((i) * (height - 1.0) / (new_height - 1.0));
            float r = image(cx, cy, 0);
            float g = image(cx, cy, 1);
            float b = image(cx, cy, 2);
            resized_image(j, i, 0) = r;
            resized_image(j, i, 1) = g;
            resized_image(j, i, 2) = b;
        }
    }
    string outputPath = "OMAR.jpg";
    string filename = getValidOutputPath(outputPath);
    resized_image.saveImage(outputPath);
    input_Path = filename;
}

// Function to choose between resize methods, with an additional option to return to main menu
void resizeImage(string inputPath) {
    Image image(inputPath);
    cout << "1. Resize by dimensions\n";
    cout << "2. Resize by ratio\n";
    cout << "3. Return to main menu\n";
    int resizeType = getValidInput_3Choices();
    cin.ignore();
    if (resizeType == 1) {
        resizeImageByDimensions(inputPath);
    }
    else if (resizeType == 2) {
        float ratio;
        ratio = getValidInput_ratio();
        cin.ignore();
        resizeImageByRatio(inputPath, ratio);
    }
    else if (resizeType == 3) {
        return;
    }
}

// Function for the darken filter
void darken(string inputPath) {
    Image image(inputPath);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                // Darken the pixel by reducing its intensity by half
                unsigned int darker = image(i, j, k) * 0.5;
                image(i, j, k) = darker;
            }
        }
    }
    string outputPath = "OMAR.jpg";
    string filename = getValidOutputPath(outputPath);
    image.saveImage(filename);
    input_Path = filename;
}

// Function for the lighten filter
void lighten(string inputPath) {
    Image image(inputPath);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                // Lighten the pixel by increasing its intensity by 1.5 times
                unsigned int lighter = static_cast<unsigned int>(image(i, j, k) * 1.5);
                // Ensure the intensity does not exceed 255 (maximum value)
                image(i, j, k) = (lighter > 255) ? 255 : lighter;
            }
        }
    }
    string outputPath = "OMAR.jpg";
    string filename = getValidOutputPath(outputPath);
    image.saveImage(filename);
    input_Path = filename;
}

// Function to choose betwwen darken and lighten filter
void DarkenAndLighten(string inputPath) {
    Image image(inputPath);
    cout << "1- Darken\n";
    cout << "2- Lighten\n";
    cout << "3- Return to main menu\n";
    int ChooseType = getValidInput_3Choices();
    cin.ignore();
    if (ChooseType == 1) {
        darken(inputPath);
    }
    else if (ChooseType == 2) {
        lighten(inputPath);
    }
    else if (ChooseType == 3) {
        return;
    }
}

// Function to apply a simple frame to the image
void SimpleFrame(string inputPath) {
    try {
        // Load the original image
        Image originalImage(inputPath);
        // Determine new dimensions for the frame
        int newWidth = originalImage.width + 30;
        int newHeight = originalImage.height + 30;
        // Create a new image with increased dimensions for the frame
        Image framedImage(newWidth, newHeight);
        // Set the entire image to blue
        for (int y = 0; y < newHeight; ++y) {
            for (int x = 0; x < newWidth; ++x) {
                framedImage.setPixel(x, y, 0, 0); // Set red channel to 0 (no red)
                framedImage.setPixel(x, y, 1, 0); // Set green channel to 0 (no green)
                framedImage.setPixel(x, y, 2, 255); // Set blue channel to 255 (full blue)
            }
        }
        // Copy the original image onto the new image leaving a 15-pixel border
        for (int y = 15; y < originalImage.height + 15; ++y) {
            for (int x = 15; x < originalImage.width + 15; ++x) {
                for (int c = 0; c < 3; ++c) {
                    framedImage.setPixel(x, y, c, originalImage.getPixel(x - 15, y - 15, c));
                }
            }
        }
        // Save the framed image
        string outputPath = "OMAR.jpg";
        string filename = getValidOutputPath(outputPath);
        framedImage.saveImage(filename);
        inputPath = filename;
    } catch (const std::exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
    }
}

// Function to apply a fancy frame to the image
void FancyFrame(string inputPath) {
    try {
        // Load the original image
        Image originalImage(inputPath);
        // Determine new dimensions for the frames
        int outerFrameWidth = 10; // 5 pixels for each frame layer
        int middleFrameWidth = 10; // 5 pixels for each frame layer
        int newWidth = originalImage.width + outerFrameWidth * 2 + middleFrameWidth * 2 + outerFrameWidth * 2;
        int newHeight = originalImage.height + outerFrameWidth * 2 + middleFrameWidth * 2 + outerFrameWidth * 2;
        // Create a new image with increased dimensions for the frames
        Image framedImage(newWidth, newHeight);
        // Set the entire image to blue with white corners
        for (int y = 0; y < newHeight; ++y) {
            for (int x = 0; x < newWidth; ++x) {
                if ((x < outerFrameWidth && y < outerFrameWidth) ||
                    (x >= newWidth - outerFrameWidth && y < outerFrameWidth) ||
                    (x < outerFrameWidth && y >= newHeight - outerFrameWidth) ||
                    (x >= newWidth - outerFrameWidth && y >= newHeight - outerFrameWidth)) {
                    // Set corners to white
                    for (int c = 0; c < 3; ++c) {
                        framedImage.setPixel(x, y, c, 255); // Set all channels to 255 (full white)
                    }
                } else {
                    // Set non-corner regions to blue
                    framedImage.setPixel(x, y, 0, 0); // Set red channel to 0 (no red)
                    framedImage.setPixel(x, y, 1, 0); // Set green channel to 0 (no green)
                    framedImage.setPixel(x, y, 2, 255); // Set blue channel to 255 (full blue)
                }
            }
        }
        // Set the middle frame to white
        for (int y = outerFrameWidth; y < newHeight - outerFrameWidth; ++y) {
            for (int x = outerFrameWidth; x < newWidth - outerFrameWidth; ++x) {
                if (x >= outerFrameWidth + middleFrameWidth && x < newWidth - outerFrameWidth - middleFrameWidth &&
                    y >= outerFrameWidth + middleFrameWidth && y < newHeight - outerFrameWidth - middleFrameWidth) {
                    // Inside the white frame
                    for (int c = 0; c < 3; ++c) {
                        framedImage.setPixel(x, y, c, 255); // Set all channels to 255 (full white)
                    }
                }
            }
        }
        // Copy the original image onto the new image leaving a 5-pixel border for each frame
        for (int y = outerFrameWidth * 2 + middleFrameWidth; y < originalImage.height + outerFrameWidth * 2 + middleFrameWidth; ++y) {
            for (int x = outerFrameWidth * 2 + middleFrameWidth; x < originalImage.width + outerFrameWidth * 2 + middleFrameWidth; ++x) {
                for (int c = 0; c < 3; ++c) {
                    framedImage.setPixel(x, y, c, originalImage.getPixel(x - outerFrameWidth * 2 - middleFrameWidth, y - outerFrameWidth * 2 - middleFrameWidth, c));
                }
            }
        }
        // Save the framed image
        string outputPath = "OMAR.jpg";
        string filename = getValidOutputPath(outputPath);
        framedImage.saveImage(filename);
        input_Path = filename;
    } catch (const std::exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
    }
}

// Function to choose the frame
void Frame(string inputPath){
    cout << "1- Simple frame\n";
    cout << "2- Fancy frame\n";
    cout << "3- Return to main menu\n";
    int frameType = getValidInput_3Choices();
    cin.ignore();
    if(frameType == 1){
        SimpleFrame(inputPath);
    }
    else if (frameType == 2){
        FancyFrame(inputPath);
    }
    else if (frameType == 3){
        return;
    }
}

// function to resize the image by crop.
void merge_crop(string inputPath1, string inputPath2) {
    // Load the two input images
    Image image1(inputPath1);
    Image image2(inputPath2);
    // Determine the dimensions of the merged image
    int minWidth = min(image1.width, image2.width);
    int minHeight = min(image1.height, image2.height);
    // Create an image for the merged result
    Image mergedImage(minWidth, minHeight);
    // Crop both images to match the dimensions of the smaller one
    for (int i = 0; i < minWidth; ++i) {
        for (int j = 0; j < minHeight; ++j) {
            for (int k = 0; k < mergedImage.channels; ++k) {
                mergedImage(i, j, k) = (image1(i, j, k) + image2(i, j, k)) / 2;
            }
        }
    }
    // Save the merged image
    string outputPath = "OMAR.jpg";
    string filename = getValidOutputPath(outputPath);
    mergedImage.saveImage(filename);
    input_Path = filename;
}

// function to resize the image to the specified dimensions.
Image merge_resize(string& imagePath, float newWidth, float newHeight){
    Image image(imagePath);
    // Calculate the scale factors for width and height
    float scaleWidth = (float)image.width / newWidth;
    float scaleHeight = (float)image.height / newHeight;
    // Create a new image with the desired dimensions
    Image resizedImage(newWidth, newHeight);
    // Loop over each pixel in the resized image
    for (int i = 0; i < newWidth; i++){
        for (int j = 0; j < newHeight; j++){
            // Calculate the corresponding coordinates in the original image
            int cx = round(i * scaleWidth);
            int cy = round(j * scaleHeight);
            // Retrieve the color components (R, G, B) from the original image
            float r = image(cx, cy, 0);
            float g = image(cx, cy, 1);
            float b = image(cx, cy, 2);
            // Set the color of the pixel in the resized image
            resizedImage(i, j, 0) = r;
            resizedImage(i, j, 1) = g;
            resizedImage(i, j, 2) = b;
        }
    }
    // Return the resized image
    return resizedImage;
}

// Function to resize two images to min dimensions
void merge_resize_min_dimensions(string& image1_path, string& image2_path){
    Image image1(image1_path);
    Image image2(image2_path);
    // Determine the min dimensions required to resize both images
    int minWidth = min(image1.width, image2.width);
    int minHeight = min(image1.height, image2.height);
    // Create a new image to store the merged result with the min dimensions
    Image mergedImage(minWidth, minHeight);
    // Resize both input images to the min dimensions
    Image newimage1 = merge_resize(image1_path, minWidth, minHeight);
    Image newimage2 = merge_resize(image2_path, minWidth, minHeight);
    // Loop over each pixel in the merged image
    for (int i = 0; i < minWidth; ++i) {
        for (int j = 0; j < minHeight; ++j) {
            for (int k = 0; k < newimage1.channels; ++k) {
                // Blend the pixel values from both images
                mergedImage(i, j, k) = (newimage1(i, j, k) + newimage2(i, j, k)) / 2;
            }
        }
    }
    // Save the merged image
    string outputPath = "OMAR.jpg";
    string filename = getValidOutputPath(outputPath);
    mergedImage.saveImage(filename);
    input_Path = filename;
}

// Function to resize two images to max dimensions
void merge_resize_max_dimensions(string& image1_path, string& image2_path){
    // Load the two input images
    Image image1(image1_path);
    Image image2(image2_path);
    // Determine the maximum dimensions required to resize both images
    int maxWidth = max(image1.width, image2.width);
    int maxHeight = max(image1.height, image2.height);
    // Create a new image to store the merged result with the maximum dimensions
    Image mergedImage(maxWidth, maxHeight);
    // Resize both input images to the maximum dimensions
    Image newimage1 = merge_resize(image1_path, maxWidth, maxHeight);
    Image newimage2 = merge_resize(image2_path, maxWidth, maxHeight);
    // Loop over each pixel in the merged image
    for (int i = 0; i < maxWidth; i++){
        for (int j = 0; j < maxHeight; j++){
            for (int k = 0; k < newimage1.channels; k++){
                // merge the two resized images
                mergedImage(i, j, k) = (newimage1(i, j, k) + newimage2(i, j, k)) / 2;
            }
        }
    }
    // Save the merged image
    string outputPath = "OMAR.jpg";
    string filename = getValidOutputPath(outputPath);
    mergedImage.saveImage(filename);
    input_Path = filename;
}

// function to merge two images by choose the method.
void merge(string image1_Path){
    cout << "enter the path of the second image: ";
    string image2path;
    getline(cin, image2path);
    string image2_path;
    image2_path = getValidInputPath(image2path);
    while (image2_path.empty()) {
        // The input path is not valid, so we prompt the user for a new input path
        getline(cin, image2path);
        image2_path = getValidInputPath(image2path);
    }
    cout << "How would you like to merge the two images?\n";
    cout << "1- Resize\n" << "2- Crop\n" << "3- Return to main menu\n";
    int mergeType = getValidInput_3Choices();
    if(mergeType == 1){
        cout << "Would you like to resize the merged image on MAX dimensions or MIN dimensions?\n";
        cout << "1- Resize on MIN dimensions\n" << "2- Resize on MAX dimensions\n";
        int resizeType = getValidInput_2Choices();
        if(resizeType == 1){
            merge_resize_min_dimensions(image1_Path, image2_path);
        }
        else if (resizeType == 2){
            merge_resize_max_dimensions(image1_Path, image2_path);
        }
    }
    else if(mergeType == 2) {
        merge_crop(image1_Path, image2_path);
    }
    else if (mergeType == 3) {
        return;
    }
}

// Apply oil paint effect to the image.
void oil_painting(string& inputPath, int brushSize, int levels) {
    Image image(inputPath);
    int width = image.width;
    int height = image.height;
    // Create temporary image to store result
    Image tempImage(width, height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int histR[256] = {0};
            int histG[256] = {0};
            int histB[256] = {0};
            // Collect histogram in the brush area
            for (int j = -brushSize; j <= brushSize; ++j) {
                for (int i = -brushSize; i <= brushSize; ++i) {
                    int nx = (x + i < 0) ? 0 : ((x + i >= width) ? width - 1 : x + i);
                    int ny = (y + j < 0) ? 0 : ((y + j >= height) ? height - 1 : y + j);
                    unsigned char r = image(nx, ny, 0);
                    unsigned char g = image(nx, ny, 1);
                    unsigned char b = image(nx, ny, 2);
                    histR[r]++;
                    histG[g]++;
                    histB[b]++;
                }
            }
            // Find the most common color in the brush area
            int maxR = 0, maxG = 0, maxB = 0;
            int maxIdxR = 0, maxIdxG = 0, maxIdxB = 0;
            for (int i = 0; i < 256; ++i) {
                if (histR[i] > maxR) {
                    maxR = histR[i];
                    maxIdxR = i;
                }
                if (histG[i] > maxG) {
                    maxG = histG[i];
                    maxIdxG = i;
                }
                if (histB[i] > maxB) {
                    maxB = histB[i];
                    maxIdxB = i;
                }
            }
            // Set the pixel to the most common color
            tempImage(x, y, 0) = maxIdxR;
            tempImage(x, y, 1) = maxIdxG;
            tempImage(x, y, 2) = maxIdxB;
        }
    }
    // Copy the result back to the original image
    for (int i = 0; i < width * height * 3; ++i) {
        image.imageData[i] = tempImage.imageData[i];
    }
    string outputPath = "OMAR.jpg";
    string filename = getValidOutputPath(outputPath);
    image.saveImage(filename);
    input_Path = filename;
}

// function for skewing image clockwise.
void skewImageClockwise(const string& fileName, double angle) {
    Image image(fileName);
    // Get image dimensions
    int width = image.width;
    int height = image.height;
    // Convert angle to radians
    double radians = angle * 3.14 / 180.0;
    // Calculate the tangent of the skew angle
    double tangent = tan(radians);
    // Calculate the new width after skewing
    int newWidth = width;
    // Iterate over each row in the original image
    for (int y = 0; y < height; ++y) {
        // Calculate the new width for this row based on the skew angle
        int rowWidth = static_cast<int>(width + (height - y) * tangent);
        // Update the new width if necessary
        if (rowWidth > newWidth) {
            newWidth = rowWidth;
        }
    }
    // Create a new image with the skewed dimensions
    Image skewedImage(newWidth, height);
    // Iterate over each pixel in the original image
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Calculate the new x position after skewing clockwise
            int newX = x + static_cast<int>((height - y) * tangent);
            // Ensure the new x position is within the bounds of the skewed image
            if (newX >= 0 && newX < newWidth) {
                // Copy the pixel color values from the original image to the skewed image
                for (int c = 0; c < image.channels; ++c) {
                    skewedImage(newX, y, c) = image(x, y, c);
                }
            }
        }
    }
    // Save the skewed image
    string outputPath = "OMAR.jpg";
    string filename = getValidOutputPath(outputPath);
    skewedImage.saveImage(filename);
    input_Path = filename;
}

// function for skewing image anticlockwise.
void skewImageAntiClockwise(const string& fileName, double angle) {
    Image image(fileName);
    // Get image dimensions
    int width = image.width;
    int height = image.height;
    // Convert angle to radians
    double radians = angle * 3.14 / 180.0;
    // Calculate the maximum horizontal displacement caused by the skewing angle
    int maxDisplacement = static_cast<int>(height * fabs(tan(radians)));
    // Calculate the new width of the skewed image to ensure the entire original image is visible
    int newWidth = width + maxDisplacement;
    // Create a new image with the skewed dimensions
    Image skewedImage(newWidth, height);
    // Iterate over each pixel in the original image
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Calculate the new x position after skewing anticlockwise
            int newX = x + static_cast<int>(y * tan(radians));
            // Ensure the new x position is within the bounds of the skewed image
            if (newX >= 0 && newX < newWidth) {
                // Copy the pixel color values from the original image to the skewed image
                for (int c = 0; c < image.channels; ++c) {
                    skewedImage(newX, y, c) = image(x, y, c);
                }
            }
        }
    }
    // Save the skewed image
    string outputPath = "OMAR.jpg";
    string filename = getValidOutputPath(outputPath);
    skewedImage.saveImage(filename);
    input_Path = filename;
}

// function for choosing the image to be skewed and the angle of skewing.
void skewImage(string imagePath){
    double angle;
    cout << "Enter the angle of skewing: ";
    cin >> angle;
    cout << "Enter the direction of skewing (c for clockwise, a for anticlockwise): ";
    while (true){
        char direction;
        cin >> direction;
        if (direction == 'c' || direction == 'C') {
            skewImageClockwise(imagePath, angle);
            break;
        } else if (direction == 'a' || direction == 'A') {
            skewImageAntiClockwise(imagePath, angle);
            break;
        } else {
            cout << "Invalid direction. Please enter 'c' for clockwise or 'a' for anticlockwise." << endl;
        }
    }
}

void convertToGrayscale(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < image.channels; k++){
                avg += image(i, j, k);
            }
            avg = avg / 3;
            // Assign grayscale value to all channels
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }
}

// Threshold the image to create binary image
void threshold(Image& image, unsigned char thresholdValue) {
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            unsigned char pixelValue = image(x, y, 0); // Assuming image is grayscale
            // Set pixel to white if value is below threshold, otherwise set to black
            image(x, y, 0) = (pixelValue < thresholdValue) ? 255 : 0;
            image(x, y, 1) = (pixelValue < thresholdValue) ? 255 : 0;
            image(x, y, 2) = (pixelValue < thresholdValue) ? 255 : 0;
        }
    }
}

// Detect edges using Sobel operator
void sobelEdgeDetection( Image& image, Image& edges) {
    for (int y = 1; y < image.height - 1; ++y) {
        for (int x = 1; x < image.width - 1; ++x) {
            int dx = image(x + 1, y - 1, 0) - image(x - 1, y - 1, 0) +
                     2 * (image(x + 1, y, 0) - image(x - 1, y, 0)) +
                     image(x + 1, y + 1, 0) - image(x - 1, y + 1, 0);
            int dy = image(x - 1, y + 1, 0) - image(x - 1, y - 1, 0) +
                     2 * (image(x, y + 1, 0) - image(x, y - 1, 0)) +
                     image(x + 1, y + 1, 0) - image(x + 1, y - 1, 0);
            int gradient = sqrt(dx * dx + dy * dy);
            // Reduce the gradient value to make edges less dark
            gradient /= 3; // Adjust the divisor as needed
            // Clamp gradient value to 255 (white) if it exceeds, otherwise set to gradient value
            edges(x, y, 0) = (gradient > 255) ? 255 : gradient;
            edges(x, y, 1) = (gradient > 255) ? 255 : gradient;
            edges(x, y, 2) = (gradient > 255) ? 255 : gradient;
        }
    }
}

// function for detecting edges using Sobel operator
void edgeDetection(string inputPath){
    // Load image
    Image image(inputPath);
    // Convert image to grayscale
    convertToGrayscale(image);
    // Threshold image to create binary image
    threshold(image, 117); // Adjust threshold value as needed
    // Create a copy of the binary image for edge detection
    Image edges(image.width, image.height);
    // Detect edges using Sobel operator
    sobelEdgeDetection(image, edges);
    // Invert edges to have black edges on white background
    for (int y = 0; y < edges.height; ++y) {
        for (int x = 0; x < edges.width; ++x) {
            edges(x, y, 0) = 255 - edges(x, y, 0);
            edges(x, y, 1) = 255 - edges(x, y, 1);
            edges(x, y, 2) = 255 - edges(x, y, 2);
        }
    }
    // Save the resulting edge-detected image
    string outputPath = "OMAR.jpg";
    string filename = getValidOutputPath(outputPath);
    edges.saveImage(filename);
    input_Path = filename;

}

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Apply Gaussian blur filter to the image
void gaussianBlur(string inputPath, float sigma) {
    Image image(inputPath);
    int width = image.width;
    int height = image.height;
    // Create a temporary image for storing the blurred result
    Image blurredImage(width, height);
    // Gaussian kernel size
    int kernelSize = static_cast<int>(ceil(3 * sigma));
    int kernelWidth = 2 * kernelSize + 1;
    // Generate Gaussian kernel
    float kernel[kernelWidth];
    float sigmaSquared = sigma * sigma;
    float sigmaRoot = sqrt(2 * M_PI * sigmaSquared);
    float sigmaFactor = 1.0f / (sigmaRoot);
    float sigmaFactor2 = 1.0f / (2 * sigmaSquared);
    float kernelSum = 0.0f;
    for (int i = -kernelSize; i <= kernelSize; ++i) {
        float distance = i * i;
        float weight = exp(-distance * sigmaFactor2) * sigmaFactor;
        kernel[i + kernelSize] = weight;
        kernelSum += weight;
    }
    // Normalize the kernel
    for (int i = 0; i < kernelWidth; ++i) {
        kernel[i] /= kernelSum;
    }
    // Apply horizontal blur
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float r = 0.0f, g = 0.0f, b = 0.0f;
            // Convolve with kernel
            for (int k = -kernelSize; k <= kernelSize; ++k) {
                int offsetX = x + k;
                if (offsetX < 0 || offsetX >= width) {
                    offsetX = min(max(offsetX, 0), width - 1);
                }
                r += kernel[k + kernelSize] * image(offsetX, y, 0);
                g += kernel[k + kernelSize] * image(offsetX, y, 1);
                b += kernel[k + kernelSize] * image(offsetX, y, 2);
            }
            blurredImage(x, y, 0) = static_cast<unsigned char>(r);
            blurredImage(x, y, 1) = static_cast<unsigned char>(g);
            blurredImage(x, y, 2) = static_cast<unsigned char>(b);
        }
    }
    // Apply vertical blur
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float r = 0.0f, g = 0.0f, b = 0.0f;
            // Convolve with kernel
            for (int k = -kernelSize; k <= kernelSize; ++k) {
                int offsetY = y + k;
                if (offsetY < 0 || offsetY >= height) {
                    offsetY = min(max(offsetY, 0), height - 1);
                }
                r += kernel[k + kernelSize] * blurredImage(x, offsetY, 0);
                g += kernel[k + kernelSize] * blurredImage(x, offsetY, 1);
                b += kernel[k + kernelSize] * blurredImage(x, offsetY, 2);
            }
            image(x, y, 0) = static_cast<unsigned char>(r);
            image(x, y, 1) = static_cast<unsigned char>(g);
            image(x, y, 2) = static_cast<unsigned char>(b);
        }
    }
    string outputPath = "OMAR.jpg";
    string filename = getValidOutputPath(outputPath);
    image.saveImage(filename);
    input_Path = filename;
}

string LoadImage(){
    if (!input_Path.empty()) {
        cout << "Do you want to save the current image before loading a new one? (y/n): ";
        string saveCurrentImage;
        getline(cin, saveCurrentImage);
        if (saveCurrentImage == "y" || saveCurrentImage == "Y") {
            SaveImage(input_Path);
        }
    }
    cout << "Enter the path of the input image to edit: ";
    getline(cin, input_Path);
    string validInputPath = getValidInputPath(input_Path);
    while (validInputPath.empty()) {
        // The input path is not valid, so we prompt the user for a new input path
        getline(cin, input_Path);
        validInputPath = getValidInputPath(input_Path);
    }
    return validInputPath; // Return the valid input path
}

// Main Function.
int main() {
    int choice;
    input_Path = LoadImage();
    temp_path = input_Path;
    do {
        // Display our menu.
        Menu();
        choice = getValidInput();
        // Ignore newline character after reading choice
        cin.ignore();
        switch (choice) {
            case 1: {
                blackAndwhite(input_Path);
                break;
            }
            case 2: {
                grayscale(input_Path);
                break;
            }
            case 3: {
                flip(input_Path);
                break;
            }
            case 4: {
                DarkenAndLighten(input_Path);
                break;
            }
            case 5: {
                Frame(input_Path);
                break;
            }
            case 6: {
                invert_image_color(input_Path);
                break;
            }
            case 7: {
                cropImage(input_Path);
                break;
            }
            case 8: {
                resizeImage(input_Path);
                break;
            }
            case 9: {
                merge(input_Path);
                break;
            }
            case 10: {
                oil_painting(input_Path, 2, 2);
                break;
            }
            case 11: {
                Infrared(input_Path);
                break;
            }
            case 12: {
                Purple(input_Path);
                break;
            }
            case 13: {
                Sunlight(input_Path);
                break;
            }
            case 14: {
                rotate(input_Path);
                break;
            }
            case 15: {
                edgeDetection(input_Path);
                break;
            }
            case 16: {
                gaussianBlur(input_Path, 10.0f);
                break;
            }
            case 17: {
                skewImage(input_Path);
                break;
            }
            case 18: {
                Tv_Filter(input_Path);
                break;
            }
            case 19: {
                LoadImage();
                break;
            }
            case 20: {
                SaveImage(input_Path);
                break;
            }
        }
        if (choice == 21) {
            cout << "Thanks for using our filter program!";
            break;
        }
    } while (choice != 21);
    return 0;
}