#pragma once



#include "main/includes.h"
#include "image.h"
#include "framework.h"
#include "particles.h"
#include "button.h"
#include "entity.h"
#include "shader.h"
#include "material.h"




class Application {

public:

    // Window

    SDL_Window* window = nullptr;
    int window_width;
    int window_height;
    float time;

    //LAB 1

    int borderWidth;
    enum DrawingMode {

        DRAW_NONE,   // No drawing
        DRAW_LINES,
        DRAW_RECTANGLES,
        DRAW_CIRCLES,
        DRAW_TRIANGLES,
        DRAW_PAINT,
        DRAW_ANIMATION,
    };

    DrawingMode drawingMode;  // Current drawing mode
    bool isFilled;
    Color line_color;

    int x0;
    int y0;
    int x1;
    int y1;
    float r;

    Color lineColor;
    Color lineColor2;
    Color color1;
    Color color2;
    Color color3;

    Vector2 point0;
    Vector2 point1;
    Vector2 point2;

    Color GetSelectedColor();

    Button line_button;
    Button rectangle_button;
    Button circle_button;
    Button triangle_button;
    Button black_button;
    Button white_button;
    Button pink_button;
    Button yellow_button;
    Button red_button;
    Button blue_button;
    Button cyan_button;
    Button green_button;

    enum SelectedFigure {
        FIGURE_LINE,
        FIGURE_RECTANGLE,
        FIGURE_CIRCLE,
        FIGURE_TRIANGLE,
        FIGURE_NONE
    };

    enum SelectedColor {
        COLOR_BLACK,
        COLOR_PINK,
        COLOR_RED,
        COLOR_GREEN,
        COLOR_BLUE,
        COLOR_CYAN,
        COLOR_NONE
    };

    SelectedFigure selectedFigure = FIGURE_NONE;
    SelectedColor selectedColor = COLOR_NONE;
    ParticleSystem particleSystem;


    //LAB 2
    enum DrawingMode2 {
        DRAW_NOTHING,
        DRAW_SINGLE_ENTITY,
        DRAW_MULTIPLE_ANIMATED
    };

    DrawingMode2 drawingMode2;

    Camera* my_camera;
    //ex 3.4
    Entity entity1;
    Entity entity2;
    Entity entity3;

    enum Current_property {
        FAR_PLANE,
        NEAR_PLANE,
        FOV
    };
    Current_property current_property;

    //LAB 3

    enum DrawingMode3 {
        DRAW_NO,
        DRAW_TRIANGLE,
        DRAW_ENTITY

    };
    DrawingMode3 drawingMode3;
    FloatImage* zBuffer;
    bool isInterpolated;
    bool isOcluded;
    bool isTextured;

    Vector3 point3;
    Vector3 point4;
    Vector3 point5;

    // Input
    const Uint8* keystate;
    int mouse_state; // Tells which buttons are pressed
    Vector2 mouse_position; // Last mouse position
    Vector2 mouse_delta; // Mouse movement in the last frame

    void OnKeyPressed(SDL_KeyboardEvent event);
    void OnMouseButtonDown(SDL_MouseButtonEvent event);
    void OnMouseButtonUp(SDL_MouseButtonEvent event);
    void OnMouseMove(SDL_MouseButtonEvent event);
    void OnWheel(SDL_MouseWheelEvent event);
    void OnFileChanged(const char* filename);


    // CPU Global framebuffer
    Image framebuffer;

    //LAB 4
    Mesh myQuad;
    Shader* myQuadShader1;
    Shader* myQuadShader2;
    Shader* myQuadShader3;

    enum DrawingMode4 {
        TASK_1,
        TASK_2,
        TASK_3,
        TASK_4
    };

    DrawingMode4 drawingMode4;
    Texture* texture;
    float subtask;

    //LAB 5
    Material::sUniformData uniformData;
    Vector3 ambient_light;

    enum DrawingMode5 {
        GOURAUD,
        PHONG
    };

    DrawingMode5 drawingMode5;
    Vector3 texture_flag;
    // Constructor and main methods
    Application(const char* caption, int width, int height);
    ~Application();

    void Init(void);
    void Render(void);
    void Update(float dt);


    // Other methods to control the app

    void SetWindowSize(int width, int height) {
        glViewport(0, 0, width, height);
        this->window_width = width;
        this->window_height = height;
    }

    Vector2 GetWindowSize()
    {
        int w, h;
        SDL_GetWindowSize(window, &w, &h);
        return Vector2(float(w), float(h));
    }

};