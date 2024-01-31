#pragma once

#include "image.h"



class Button {

public:


    Button() {};
    Button(const char* imageFilename, int x, int y);

    ~Button();



    void Render();

    bool isMouseInside(Vector2 mousePosition); //checks if mouse is inside of the bounds of the button


    //here, the button attributes
    Image buttonImage;
    int positionX;
    int positionY;



};