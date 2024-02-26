#include "button.h"


Button::Button(const char* imageFilename, int x, int y) { //button constructor
    buttonImage.LoadPNG(imageFilename, true);
    this->positionX = x;
    this->positionY = y;
}

Button::~Button() {

    //destructor, but we have not implemented it

}



void Button::Render(){
   
  
}



bool Button::isMouseInside(Vector2 mousePosition) { //checks if mouse is inside the limits of the button

    return (mousePosition.x >= positionX && mousePosition.x < positionX + buttonImage.width && mousePosition.y >= positionY && mousePosition.y < positionY + buttonImage.height);
}