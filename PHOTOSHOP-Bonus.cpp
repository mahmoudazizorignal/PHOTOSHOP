// Program: PHOTOSHOP-Bonus.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//          Program load a colored image and store in another file
//          then we ask the user which filter do you want then do the filter..
// Author - 1:  Abdelrhman Reda Mohammed
// Author - 2:  Mahmoud Mamdouh
// Author - 3:  Abo Bakr Ahmed
// Date:    13 / 4 / 2022
// Version: 2.5

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
#include <unistd.h>

using namespace std;
unsigned char image[SIZE][SIZE][RGB];
unsigned char saveimage[SIZE][SIZE][RGB];
unsigned char mergeimage[SIZE][SIZE][RGB];

void mainmessage();
int loadImage ();
void saveImage ();



int main()
{
    cout << "AHLAN YA USER !" <<endl;
    loadImage();
    cout << "Please select a filter to apply or 0 to exit: " <<endl;
    mainmessage();
    saveImage();


  return 0;
}
//_________________________________________

int loadImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Please enter file name of the image to process: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
    while(readRGBBMP(imageFileName, image) == 1)
    {
            return loadImage();
    }
    sleep(1);
    system("CLS");
    cout << "Image Added Successfully\n";

}

//_________________________________________

int loadMergeImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Please enter name of image file to merge with: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   while(readRGBBMP(imageFileName, mergeimage) == 1)
    {
                return loadMergeImage();
    }
    cout << "2nd Image Added Successfully\n";

}
//_________________________________________

void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeRGBBMP(imageFileName, saveimage);
}


//---------------------------------------------
//              Black & White FILTER
//---------------------------------------------
void black_white() {
  float avg=0;
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j< SIZE; j++)
    {
        avg = (image[i][j][0] + image[i][j][1]+ image[i][j][2]) /3; // TAKE THE AVERAGE OF EACH PIXEL
        if (avg < 127) // CHECK IF AVERAGE LESS THAN 127
        {
            for (int r =0 ; r<RGB ;r++)
            {
                image[i][j][r] = 0; // MAKE THE PIXEL WHITE
                saveimage[i][j][r] = image[i][j][r];
            }

        }
        else
        {
            for (int r =0 ; r<RGB ;r++)
            {
                image[i][j][r] = 255; // MAKE THE PIXEL BLACK
                saveimage[i][j][r] = image[i][j][r];
            }

        }
    }
  }
}

//---------------------------------------------
//              INVERT FILTER
//---------------------------------------------

void invert_photo() {
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE ;j++)
        {
            for (int r =0 ; r<RGB ;r++)
            {
                saveimage[i][j][r] = 255-(image[i][j][r]);
            }
        }
    }
}

//---------------------------------------------
//              Merge FILTER
//---------------------------------------------

void merge_photo() {
    loadMergeImage();
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE ;j++)
        {
            for (int r =0 ; r<RGB ;r++)
            {
                saveimage[i][j][r] = ((image[i][j][r])+(mergeimage[i][j][r]))/2;
            }
        }
    }
}


//---------------------------------------------
//              Flip FILTER
//---------------------------------------------

void flip_photo() {
    string choose;
    int z = 0 ;
    cout << "=> Flip (h)orizontally or (v)ertically ?\n=>";
    cin >> choose;
    if (choose == "h"){
        for (int i = 256; i >= 0; i--)
        {
            for (int j = 0; j < SIZE ;j++)
            {
                for (int r =0 ; r<RGB ;r++)
                {
                    saveimage[z][j][r] = (image[i][j][r]);
                }
            }
            z++;
        }
    }else if (choose == "v"){
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 256,y = 0; j >= 0 ;j-- , y++)
            {
                for (int r =0 ; r<RGB ;r++)
                {
                    saveimage[i][y][r] = (image[i][j][r]);
                }
            }
        }
    }else{
        cout << "BAD INPUT !" << endl;
        sleep(1);
        system("CLS");
        return flip_photo();
    }
}

//---------------------------------------------
//              Rotate FILTER
//---------------------------------------------

void rotate_photo() {
    int choose;
    int z = 0 ;
    cout << "Rotate (90), (180) or (360) degrees?\n=>";
    cin >> choose;
    if (choose == 180){
        for (int i = 256; i >= 0; i--)
        {
            for (int j = 0; j < SIZE ;j++)
            {
                for (int r =0 ; r<RGB;r++)
                {
                saveimage[z][j][r] = (image[i][256-j][r]);
                }
            }
            z++;
        }
    }
    else if (choose == 270){
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 256, y = 0 ; j >= 0 ; j-- , y++)
            {
                for (int r =0 ; r<RGB;r++)
                {
                    saveimage[i][y][r] = (image[j][i][r]);
                }
            }
        }
    }
    else if (choose == 90){
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE ;j++)
            {
                for (int r =0 ; r<RGB;r++)
                {
                saveimage[i][j][r] = (image[j][256-i][r]);
                }
            }
        }
    }
    else{
        cout << "BAD INPUT !";
        sleep(1);
        system("CLS");
        return rotate_photo();
    }
}
//---------------------------------------------
//              Darken Ligthen FILTER
//---------------------------------------------
void do_dark()
{
    int want;
    cout << "[1] Darken The Image\n[2] Lighten The Image\n=> ";
    cin >> want;
    if(want == 1)
    {
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                for(int x = 0; x < RGB; x++)
                {
                    image[i][j][x] = image[i][j][x] * 0.25;
                }
            }
        }
    }
    else if(want == 2)
    {
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                for(int x = 0; x < RGB; x++)
                {
                    image[i][j][x] += (255 - image[i][j][x]) * 0.75;
                }
            }
        }
    }
    else
    {
        cout << "BAD INPUT" << endl;
        sleep(1);
        system("CLS");
        return do_dark();
    }
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            for(int x = 0; x < RGB; x++)
            {
                saveimage[i][j][x] = image[i][j][x];
            }
        }
    }

}
//---------------------------------------------
//              Shrink FILTER
//---------------------------------------------
void do_shrink()
{
    int want;
    cout << "Shrink By:\n[1] 1/2\n[2] 1/3\n[3] 1/4\n=> ";
    cin >> want;
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            for(int x = 0; x < RGB; x++)
            {
                saveimage[i][j][x] = 255;
            }
        }
    }
    if(want == 1)
    {
        int c = 0, v = 0;
        for(int i = 0; i < SIZE / 2; i++)
        {
            for(int j = 0; j < SIZE / 2; j++)
            {
                for(int x = 0; x < RGB; x++)
                {
                    saveimage[i][j][x] = image[c][v][x];
                }
                v += 2;
                if(v > 255)
                {
                    v = 0; c += 2;
                }
            }
        }
    }
    else if(want == 2)
    {
        int c = 0, v = 0;
        for(int i = 0; i < SIZE / 3; i++)
        {
            for(int j = 0; j < SIZE / 3; j++)
            {
                for(int x = 0; x < RGB; x++)
                {
                    saveimage[i][j][x] = image[c][v][x];
                }
                v += 3;
                if(v > 252)
                {
                    v = 0; c += 3;
                }
            }
        }
    }
    else if(want == 3)
    {
        int c = 0, v = 0;
        for(int i = 0; i < SIZE / 4; i++)
        {
            for(int j = 0; j < SIZE / 4; j++)
            {
                for(int x = 0; x < RGB; x++)
                {
                    saveimage[i][j][x] = image[c][v][x];
                }
                v += 4;
                if(v > 252)
                {
                    v = 0; c += 4;
                }
            }
        }
    }
    else
    {
        cout << "BAD INPUT" << endl;
        sleep(1);
        system("CLS");
        return do_shrink();
    }
}
//---------------------------------------------
//              Enlarge FILTER
//---------------------------------------------
void enlarge_photo() {
    int choose;
    cout << "Which quarter to enlarge 1, 2, 3 or 4\n=>";
    cin >> choose;

    if (choose == 1)
    {
        for (int i = 0, y = 0; i < 128 ; i++,y+=2)
        {
            for (int j = 0 , k = 0 ; j < 128 ;k+=2,j++)
            {
                for (int r =0 ; r<RGB ; r++)
                {
                    saveimage[y][k][r] = image[i][j][r];
                    saveimage[y][k+1][r] = image[i][j][r];
                    saveimage[y+1][k][r] = image[i][j][r];
                    saveimage[y+1][k+1][r] = image[i][j][r];

                }

            }
        }
    }
    else if (choose == 2)
    {
        for (int i = 0, y = 0; i < 128 ; i++,y+=2)
        {
            for (int j = 127 , k = 0 ; j < 256 ;k+=2,j++)
            {
                for (int r =0 ; r<RGB ; r++)
                {
                saveimage[y][k][r] = image[i][j][r];
                saveimage[y][k+1][r] = image[i][j][r];
                saveimage[y+1][k][r] = image[i][j][r];
                saveimage[y+1][k+1][r] = image[i][j][r];
                }
            }
        }
    }
    else if (choose == 3)
    {
        for (int i = 128, y = 0; i < 256 ; i++,y+=2)
        {
            for (int j = 0 , k = 0 ; j < 128 ;k+=2,j++)
            {
                for (int r =0 ; r<RGB ; r++)
                {
                saveimage[y][k][r] = image[i][j][r];
                saveimage[y][k+1][r] = image[i][j][r];
                saveimage[y+1][k][r] = image[i][j][r];
                saveimage[y+1][k+1][r] = image[i][j][r];
                }
            }
        }
    }
    else if (choose == 4)
    {
        for (int i = 127, y = 0; i < 256 ; i++,y+=2)
        {
            for (int j = 127 , k = 0 ; j < 256 ;k+=2,j++)
            {
                for (int r =0 ; r<RGB ; r++)
                {
                saveimage[y][k][r] = image[i][j][r];
                saveimage[y][k+1][r] = image[i][j][r];
                saveimage[y+1][k][r] = image[i][j][r];
                saveimage[y+1][k+1][r] = image[i][j][r];
                }

            }
        }
    }
    else
    {
        cout << "BAD INPUT" << endl;
        sleep(1);
        system("CLS");
        return enlarge_photo();
    }
}
//---------------------------------------------
//            Blur Filter
//---------------------------------------------
void do_blur()
{
    int sum = 0;
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            for(int x = 0; x < RGB; x++)
            {
                saveimage[i][j][x] = image[i][j][x];
            }
        }
    }
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            for(int x = 0; x < RGB; x++)
            {
                sum = 0;
                for(int c = i - 5; c < i + 6; c++)
                {
                    for(int v = j - 5; v < j + 6; v++)
                    {
                        if(c >= 0 && v >= 0 && c < 256 && v < 256)
                            sum += image[c][v][x];
                    }
                }
                saveimage[i][j][x] = sum / 121;
            }
        }
    }

}
//---------------------------------------------
//            Shuffle Filter
//---------------------------------------------
void first_quarter(int quarter) // first quarter function..
{
    int y = 128;
    for (int i = 0; i < 128 ; i++)
    {
        int x = 128;
        for (int j = 0 ; j < 128 ;j++)
        {
            for (int r =0 ; r<RGB ;r++)
            {
                if (quarter == 0)
                {
                    saveimage[i][j][r] = image[i][j][r];// add first quarter into quarter 1
                }
                else if (quarter == 1)
                {
                    saveimage[i][x][r] = image[i][j][r];// add first quarter into quarter 2
                }
                else if (quarter == 2)
                {
                    saveimage[y][j][r] = image[i][j][r];// add first quarter into quarter 3
                }
                else if (quarter == 3)
                {
                    saveimage[y][x][r] = image[i][j][r];// add first quarter into quarter 4

                }
            }
            x++;
        }
    y++;
    }
}
void second_quarter(int quarter) // Second quarter function..
{
    int y = 128;
    for (int i = 0; i < 128 ; i++)
    {
        int x = 128;
        int l = 0;
        for (int j = 128 ; j <= 256 ;j++)
        {
            for (int r =0 ; r<RGB ;r++)
            {
                if (quarter == 1)
                {
                    saveimage[i][j][r] = image[i][j][r]; // add Second quarter into quarter 2
                }
                else if (quarter == 0)
                {
                    saveimage[i][l][r] = image[i][j][r]; // add Second quarter into quarter 1
                }
                else if (quarter == 3)
                {
                    saveimage[y][j][r] = image[i][j][r]; // add Second quarter into quarter 4
                }
                else if (quarter == 2)
                {
                    saveimage[y][l][r] = image[i][j][r]; // add Second quarter into quarter 3

                }
            }
            l++;
        }
    y++;
    }
}
void third_quarter(int quarter) // Third quarter function..
{
    int y = 0;
    for (int i = 128; i <= 256 ; i++)
    {
        int x = 128;
        int l = 0;
        for (int j = 0 ; j < 128 ;j++)
        {
            for (int r =0 ; r<RGB ;r++)
            {
                if (quarter == 2)
                {
                    saveimage[i][j][r] = image[i][j][r]; // add Third quarter into quarter 3
                }
                else if (quarter == 3)
                {
                    saveimage[i][x][r] = image[i][j][r]; // add Third quarter into quarter 4
                }
                else if (quarter == 0)
                {
                    saveimage[y][l][r] = image[i][j][r]; // add Third quarter into quarter 1

                }
                else if (quarter == 1)
                {
                    saveimage[y][x][r] = image[i][j][r]; // add Third quarter into quarter 2

                }
            }
            x++;
            l++;
        }
    y++;
    }
}
void fourth_quarter(int quarter) // Fourth quarter function..
{
    int y = 0;
    for (int i = 128; i <= 256 ; i++)
    {
        int x = 0;
        int l = 128;
        for (int j = 128 ; j <= 256 ;j++)
        {
            for (int r =0 ; r<RGB ;r++)
            {
                if (quarter == 3)
                {
                    saveimage[i][j][r] = image[i][j][r];// add Fourth quarter into quarter 4
                }
                else if (quarter == 2)
                {
                    saveimage[i][x][r] = image[i][j][r];// add Fourth quarter into quarter 3
                }
                else if (quarter == 0)
                {
                    saveimage[y][x][r] = image[i][j][r];// add Fourth quarter into quarter 1
                    x++;
                }
                else if (quarter == 1)
                {
                    saveimage[y][l][r] = image[i][j][r];// add Fourth quarter into quarter 2

                }
            }
        x++;
        l++;
        }
    y++;
    }
}

void shuffle_photo() {                      // Main Filter function..
    string arr ={'1','2','3','4'};
    int check = 0;
    string choose;
    cout << "Enter New order of quarters : ";
    cin >> choose;
    //check if there's a duplication or no ...
    for (int i = 0 ; i < choose.length() ;i++)
        {
        for (int y = 0 ; y < 4 ; y++)
            {
                if ( choose[0] != choose[1] && choose[0] != choose[2] && choose[0] != choose[3])
                {
                    if (choose[1] != choose[2] && choose[1] != choose[3] && choose[2] != choose[3])
                    {
                        if ( choose[i] == arr[y])     // check if user add a correct numbers..
                        {
                                check += 1;
                                continue;
                        }
                    }
                }
            }
        }
    if (check == 4)
    {
        for ( int i = 0 ; i < choose.length() ; i++)
        {
            if (choose[i] == '1' ) // i => the place of the quarter 1
            {
                first_quarter(i);
            }
            else if (choose[i] == '2' ) // i => the place of the quarter 2
            {
                second_quarter(i);
            }
            else if (choose[i] == '3' ) // i => the place of the quarter 3
            {
                third_quarter(i);
            }
            else if (choose[i] == '4' ) // i => the place of the quarter 4
            {
                fourth_quarter(i);
            }
        }
    }
    else
    {
        cout << "BAD INPUT" << endl;
        sleep(1);
        system("CLS");
        return shuffle_photo();
    }

}

//---------------------------------------------
//              Edge Detector Filter
//---------------------------------------------

/*
    Here We are using Sobel Edge Detector algorithm, but first
    we darken the image by 1/3 to make the edges more clear
*/

void dark() // Darken The Image
{
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                for(int x = 0; x < RGB; x++)
                {
                    image[i][j][x] = image[i][j][x] * 0.22999;

                }
            }
        }

}

void do_detect()
{
    dark();
    int ix[3][3]={{-1,0,1},{-2,0,2},{-1,0,1}}; // To detect the Horizontal Edges
    int iy[3][3]={{1,2,1},{0,0,0},{-1,-2,-1}}; // To detect the Vertical Edges
    for(int i = 0; i < 254; i++)
    {
        for(int j = 0; j < 254; j++)
        {
            for(int x = 0; x < RGB; x++)
            {
                float sumx = 0, sumy = 0;
                for(int f = i, c = 0; f < i+3 && c < 3; f++, c++)
                {
                    for(int y = j, v = 0; y < j+3 && v < 3; y++, v++)
                    {
                        sumx += (image[f][y][x] * ix[c][v]);
                        sumy += (image[f][y][x] * iy[c][v]);
                    }
                }
                saveimage[i][j][x] = sqrt(sumx * sumx + sumy * sumy);// Taking the Average of the horizontal and the vertical edges
            }
        }
    }
    for(int i = 1; i < 255; i++)
    {
        for(int j = 1 ; j < 255; j++)
        {
            for(int r = 0; r < RGB; r++)
            {
                saveimage[i][j][r] = 255 - saveimage[i][j][r];
            }

        }
    }

}
//---------------------------------------------
//              Mirror Filter
//---------------------------------------------
void mirror_image(){
    string choose;
    cout << "Left,Right,Upper or Lower mirror?\n=>";
    cin >> choose;
    if (choose == "Right")
    {
        for (int i=0; i<SIZE; i++)
        {
          for (int j=0; j<SIZE; j++)
          {
              for (int r =0 ; r<RGB ; r++)
              {
                    saveimage[i][j][r] = image[i][256-j][r];
              }
          }
        }
    }
    else if (choose == "Lower")
    {
        for (int i=0; i<SIZE; i++)
        {
            for (int j=0; j<SIZE; j++)
            {
                for (int r =0 ; r<RGB ; r++)
                {
                    saveimage[i][j][r] = image[256-i][j][r];
                }
            }
        }
    }
    else if (choose == "Left")
    {
        for (int i=0; i<SIZE; i++)
        {
            for (int j=0 ,y=0; j<SIZE; j++,y++)
            {
               for (int r =0 ; r<RGB ; r++)
               {
                   if (j < 128)
                    {
                        saveimage[i][y][r] = image[i][j][r];
                    }
                    else
                    {
                        saveimage[i][y][r] = image[i][256-j][r];
                    }
               }
            }
        }
    }
    else if (choose == "Upper")
    {
        for (int i=0,y=0; i<SIZE; i++,y++)
        {
            for (int j=0 ; j<SIZE; j++)
            {
                for (int r =0 ; r<RGB ; r++)
                {
                   if (i < 128)
                    {
                        saveimage[y][j][r] = image[i][j][r];
                    }
                    else
                    {
                        saveimage[y][j][r] = image[256-i][j][r];
                    }
                }
            }
        }
    }else
    {
        cout << "BAD INPUT" << endl;
        sleep(1);
        system("CLS");
        return mirror_image();
    }

}
//---------------------------------------------
//              CHOOSING FUNCTION
//---------------------------------------------

void mainmessage(){
    string choosing;
    while(true)
    {
        cout << "[1] Black And White Filter \n"
             << "[2] Invert Filter \n"
             << "[3] Merge Filter \n"
             << "[4] Flip Image \n"
             << "[5] Darken and Lighten Image \n"
             << "[6] Rotate Image \n"
             << "[7] Detect Image Edges \n"
             << "[8] Enlarge Image\n"
             << "[9] Shrink Image\n"
             << "[a] Mirror 1/2 Image\n"
             << "[b] Shuffle Image\n"
             << "[c] Blur Image\n"

             << "[0] Exit \n=> ";
        cin >> choosing;
        if(choosing == "0")
        {
            cout << "See You Next Time ..." << endl;
            break;
        }
        else if (choosing == "1")
        {
            cout << "\n=> Black And White Filter" << endl;
            black_white();
            break;
        }
        else if (choosing == "2")
        {
            cout << "\n=> Invert Filter" << endl;
            invert_photo();
            break;
        }
        else if (choosing == "3")
        {
            cout << "\n=> Merge Filter" << endl;
            merge_photo();
            break;
        }else if (choosing == "4")
        {
            cout << "\n=> Flip Filter" << endl;
            flip_photo();
            break;
        }
        else if(choosing == "5")
        {
            cout << "\n=> Darken Ligthen Filter" << endl;
            do_dark();
            break;
        }
        else if (choosing == "6")
        {
            cout << "\n=> Rotate Filter" << endl;
            rotate_photo();
            break;
        }
        else if(choosing == "7")
        {
            cout << "\n=> Edge Detector Filter" << endl;
            do_detect();
            break;
        }
        else if (choosing == "8")
        {
            cout << "\n=> Enlarge Filter" << endl;
            enlarge_photo();
            break;
        }

        else if(choosing == "9")
        {
            cout << "\n=> Shrink Filter" << endl;
            do_shrink();
            break;
        }
        else if (choosing == "a")
        {
            cout << "\n=> Mirror Filter" << endl;
            mirror_image();
            break;
        }

        else if (choosing == "b")
        {
            cout << "\n=> Shuffle Image" << endl;
            shuffle_photo();
            break;
        }
        else if(choosing == "c")
        {
            cout << "\n=> Blur Image" << endl;
            do_blur();
            break;
        }
        else
        {
            sleep(1);
            system("CLS");
            cout << "Wrong Choose !!" << endl;
            return mainmessage();
        }

    }
}
