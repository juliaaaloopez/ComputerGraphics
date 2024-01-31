#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 



Application::Application(const char* caption, int width, int height) {

    this->window = createWindow(caption, width, height);
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    this->mouse_state = 0;
    this->time = 0.f;
    this->window_width = w;
    this->window_height = h;
    this->keystate = SDL_GetKeyboardState(nullptr);
    this->framebuffer.Resize(w, h);

}



Application::~Application() {

}



void Application::Init(void) {

    std::cout << "Initiating app..." << std::endl;
    //LAB 1
    borderWidth = 20;
    isFilled = false;
    bool Lab1 = false;
    drawingMode = DRAW_NONE;

    //LAB 2
    drawingMode2 = DRAW_NOTHING;
    bool Lab2 = true;

    if (Lab1) {
        std::cout << "Available Drawing Options:" << std::endl;
        std::cout << "1. Draw Lines (Press '1')" << std::endl;
        std::cout << "2. Draw Rectangles (Press '2')" << std::endl;
        std::cout << "3. Draw Circles (Press '3')" << std::endl;
        std::cout << "4. Draw Triangles (Press '4')" << std::endl;
        std::cout << "5. Paint (Press '5')" << std::endl;
        std::cout << "6. Animation (Press '6')" << std::endl;

        std::cout << "Additional Options:" << std::endl;
        std::cout << "'F' - Toggle Fill Mode" << std::endl;
        std::cout << "'+' - Increase Border Width" << std::endl;
        std::cout << "'-' - Decrease Border Width" << std::endl;
        std::cout << std::endl;

        // We initialize the buttons for the paint option
        line_button = Button("../res/images/line.png", 0, 0);
        rectangle_button = Button("../res/images/rectangle.png", 35, 0);
        circle_button = Button("../res/images/circle.png", 70, 0);
        black_button = Button("../res/images/black.png", 105, 0);
        pink_button = Button("../res/images/pink.png", 140, 0);
        red_button = Button("../res/images/red.png", 175, 0);
        green_button = Button("../res/images/green.png", 210, 0);
        blue_button = Button("../res/images/blue.png", 245, 0);
        cyan_button = Button("../res/images/cyan.png", 280, 0);

    }

    if (Lab2) {

        my_mesh = new Mesh(); // instantiate and assign a model matrix
        
        if (!my_mesh->LoadOBJ("meshes/lee.obj"))
            std::cout << "Model not found" << std::endl;

        //my_model.Rotate(3.14, Vector3(1, 0, 0)); //totate 180 degrees in the x axis //given an angle (radians) and an axis it rotates an object
        //my_model.Translate(1.0,2.0,0.0); //x,y,z- where we want our object to be


        //assigning a model matrix and mesh to entity
        my_entity.model = my_model;
        my_entity.mesh = my_mesh;

        my_camera = new Camera();
        //my_camera->LookAt(Vector3(0,0.2,0.75),Vector3(0,0.2,0), Vector3::UP); //construct the view matrix
        //my_camera->SetPerspective(60, window_width / (float)window_height, 0.01, 100); //60 degrees, aspect ratio, near and far plane

        //3.4
        //define 3 new entities

        //initialize entity 1 mesh
        my_mesh1 = new Mesh();
        if (!my_mesh1->LoadOBJ("meshes/lee.obj"))
            std::cout << "Model not found" << std::endl;
        entity1.mesh = my_mesh1;
        entity1.model = my_model1;
        my_model1.SetIdentity();


        my_mesh2 = new Mesh();
        if (!my_mesh2->LoadOBJ("meshes/lee.obj"))
            std::cout << "Model not found" << std::endl;
        entity2.mesh = my_mesh2;
        entity2.model = my_model2;
        my_model2.SetIdentity();

        my_mesh3 = new Mesh();
        if (!my_mesh3->LoadOBJ("meshes/lee.obj"))
            std::cout << "Model not found" << std::endl;
        entity3.mesh = my_mesh3;
        entity3.model = my_model3;
        my_model3.SetIdentity();

        entity1.model.SetTranslation(-0.5, -0.3, 0.0);
        entity2.model.SetTranslation(0.5, -0.3, 0.0);
        entity3.model.SetTranslation(0.0, 0.3, 0.0);

    }
}


// Render one frame

void Application::Render(void) {

    framebuffer.Fill(Color::BLACK); // by default the background of the framebuffer is black

    bool Lab1 = false;
    bool Lab2 = true;

    if (Lab1) {
        switch (drawingMode) {
        case DRAW_LINES:
            framebuffer.DrawLineDDA(x0, y0, x1, y1, lineColor);
            break;

        case DRAW_RECTANGLES:
            if (isFilled) {
                framebuffer.DrawRect(x0, y0, 100, 200, lineColor, borderWidth, 1, lineColor2);
            }
            else {
                framebuffer.DrawRect(x0, y0, 100, 200, lineColor, borderWidth, 0, lineColor2);
            }
            break;

        case DRAW_CIRCLES:
            if (isFilled) {
                framebuffer.DrawCircle(x0, y0, r, lineColor, borderWidth, 1, lineColor2);
            }
            else {
                framebuffer.DrawCircle(x0, y0, r, lineColor, borderWidth, 0, lineColor2);
            }
            break;

        case DRAW_TRIANGLES:
            if (isFilled) {
                framebuffer.DrawTriangle(point0, point1, point2, lineColor, 1, lineColor2);
            }
            else {
                framebuffer.DrawTriangle(point0, point1, point2, lineColor, 0, lineColor2);
            }
            break;

        case DRAW_PAINT:
            framebuffer.DrawImage(line_button.buttonImage, line_button.positionX, line_button.positionY, true);
            framebuffer.DrawImage(rectangle_button.buttonImage, rectangle_button.positionX, rectangle_button.positionY, true);
            framebuffer.DrawImage(circle_button.buttonImage, circle_button.positionX, circle_button.positionY, true);
            framebuffer.DrawImage(black_button.buttonImage, black_button.positionX, black_button.positionY, true);
            framebuffer.DrawImage(pink_button.buttonImage, pink_button.positionX, pink_button.positionY, true);
            framebuffer.DrawImage(red_button.buttonImage, red_button.positionX, red_button.positionY, true);
            framebuffer.DrawImage(green_button.buttonImage, green_button.positionX, green_button.positionY, true);
            framebuffer.DrawImage(blue_button.buttonImage, blue_button.positionX, blue_button.positionY, true);
            framebuffer.DrawImage(cyan_button.buttonImage, cyan_button.positionX, cyan_button.positionY, true);
            break;

        case DRAW_ANIMATION:
            particleSystem.Render(&framebuffer);
            break;

        }
    }

    if (Lab2) {
        switch (drawingMode2) {
        case DRAW_SINGLE_ENTITY:
            my_entity.Render(&framebuffer, my_camera, Color::RED);
            break;

        case DRAW_MULTIPLE_ANIMATED:


           entity1.Render(&framebuffer, my_camera, Color::RED);
           entity2.Render(&framebuffer, my_camera, Color::GREEN);
           entity3.Render(&framebuffer, my_camera, Color::WHITE);

            /*entity1.Update(time);
            entity2.Update(time);
            entity3.Update(time);*/

            break;

        }

    }

    framebuffer.Render();

}



// Called after render

void Application::Update(float seconds_elapsed)
{
    bool Lab1 = false;
    bool Lab2 = true;
    if (Lab1) {
        switch (drawingMode) {
        case DRAW_ANIMATION:
            particleSystem.Update(seconds_elapsed); // Update particle system
            break;
        }

    }
   
    if (Lab2) {

        switch (drawingMode2) {
        case DRAW_MULTIPLE_ANIMATED:

            //float angular_speed = 1.0f; //choose a speed in radians/second
            //my_model1.Rotate(PI, Vector3(0, 1, 0)); //rotate 180 eegrees in the x axis

            entity1.Update(seconds_elapsed);


            //my_model2.Translate(3, 2, 1); //translate three units to the right in x-axis, 2 units up in the y-axis 
            // and one unit to the front in the z-axis

            //scale model 3:
            Vector3 vector = (1, 2, 3);
            Matrix44 scale;
            scale.SetIdentity();

            scale.M[0][0] = vector.x;
            scale.M[1][1] = vector.y;
            scale.M[2][2] = vector.z;

            my_model3 = scale * my_model3;  //we multiply the scale matrix by the model matrix


            break;
        }

    }

  
        
}



//keyboard press event 

void Application::OnKeyPressed(SDL_KeyboardEvent event)

{
    bool Lab1 = false;
    bool Lab2 = true;

    // KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode

    if (Lab1) {
        switch (event.keysym.sym) {
        case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app

        case SDLK_1:
            drawingMode = DRAW_LINES;

            // Update line parameters as needed
            x0 = mouse_position.x;
            y0 = mouse_position.y;
            x1 = x0 + 100;
            y1 = y0 + 100;
            lineColor = Color(rand() % 256, rand() % 256, rand() % 256); // Random color 
            break;

        case SDLK_2:
            drawingMode = DRAW_RECTANGLES;
            x0 = mouse_position.x;
            y0 = mouse_position.y;
            lineColor = Color(rand() % 256, rand() % 256, rand() % 256);
            lineColor2 = Color(rand() % 256, rand() % 256, rand() % 256);
            break;

        case SDLK_3:
            drawingMode = DRAW_CIRCLES;
            x0 = mouse_position.x;
            y0 = mouse_position.y;
            r = rand() % 100; //random radius between 0 and 100
            lineColor = Color(rand() % 256, rand() % 256, rand() % 256);
            lineColor2 = Color(rand() % 256, rand() % 256, rand() % 256);
            break;

        case SDLK_4:
            drawingMode = DRAW_TRIANGLES;
            point0 = { mouse_position.x, mouse_position.y };
            point1 = { mouse_position.x + 50, mouse_position.y + 70 };
            point2 = { mouse_position.x + 100, mouse_position.y + 10 };
            lineColor = Color(rand() % 256, rand() % 256, rand() % 256);
            lineColor2 = Color(rand() % 256, rand() % 256, rand() % 256);
            break;

        case SDLK_5:
            drawingMode = DRAW_PAINT;
            break;

        case SDLK_6:
            drawingMode = DRAW_ANIMATION;
            particleSystem.Init();
            break;

        case SDLK_PLUS:
            borderWidth++;
            break;

        case SDLK_MINUS:
            borderWidth--;
            break;

        case SDLK_f:
            isFilled = !isFilled;
            break;
        }
    }

    if (Lab2) {
        switch (event.keysym.sym) {
        case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app

        case SDLK_1:
            drawingMode2 = DRAW_SINGLE_ENTITY;
            break;

        case SDLK_2:
            drawingMode2 = DRAW_MULTIPLE_ANIMATED;


            break;

        case SDLK_o:
            break;

        case SDLK_p:
            break;

        case SDLK_n:
            break;

        case SDLK_f:
            break;

        case SDLK_PLUS:
            break;

        case SDLK_MINUS:
            break;
        }

    }

}


void Application::OnMouseButtonDown(SDL_MouseButtonEvent event)

{
    bool Lab1 = false;
    bool Lab2 = true;

    if (Lab1) {
        if (event.button == SDL_BUTTON_LEFT) {

            Vector2 mousePosition = { (float)event.x, (float)event.y };

            if (black_button.isMouseInside(mousePosition)) {
                selectedColor = COLOR_BLACK;
            }
            else if (pink_button.isMouseInside(mousePosition)) {
                selectedColor = COLOR_PINK;
            }
            else if (red_button.isMouseInside(mousePosition)) {
                selectedColor = COLOR_RED;
            }
            else if (line_button.isMouseInside(mousePosition)) {
                selectedFigure = FIGURE_LINE;
            }
            else if (rectangle_button.isMouseInside(mousePosition)) {
                selectedFigure = FIGURE_RECTANGLE;
            }
            else if (circle_button.isMouseInside(mousePosition)) {
                selectedFigure = FIGURE_CIRCLE;
            }

            if (drawingMode == DRAW_PAINT && selectedFigure != FIGURE_NONE && selectedColor != COLOR_NONE) {
                switch (selectedFigure) {
                case FIGURE_LINE:
                    framebuffer.DrawLineDDA(event.x, event.y, event.x + 100, event.y + 100, GetSelectedColor());
                    break;
                case FIGURE_RECTANGLE:

                    framebuffer.DrawRect(event.x, event.y, 100, 200, GetSelectedColor(), borderWidth, 0, GetSelectedColor());
                    break;
                case FIGURE_CIRCLE:
                    float r = rand() % 100;
                    framebuffer.DrawCircle(event.x, event.y, r, GetSelectedColor(), borderWidth, 0, GetSelectedColor());
                    break;
                }
            }
        }
    }

    if (Lab2) {

    }

}



Color Application::GetSelectedColor() {
    switch (selectedColor) {
    case COLOR_BLACK:
        return Color(0, 0, 0);
    case COLOR_PINK:
        return Color(255, 192, 203);
    case COLOR_RED:
        return Color(255, 0, 0);
    case COLOR_GREEN:
        return Color(0, 255, 0);
    case COLOR_BLUE:
        return Color(0, 0, 255);
    case COLOR_CYAN:
        return Color(0, 255, 255);
    default:
        return Color(255, 255, 255);
    }
}


void Application::OnMouseButtonUp(SDL_MouseButtonEvent event)

{
    if (event.button == SDL_BUTTON_LEFT) {


    }

}



void Application::OnMouseMove(SDL_MouseButtonEvent event)

{



}



void Application::OnWheel(SDL_MouseWheelEvent event)

{

    float dy = event.preciseY;



    // ...

}



void Application::OnFileChanged(const char* filename)

{

    Shader::ReloadSingleShader(filename);

}
