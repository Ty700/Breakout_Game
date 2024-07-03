/*
    First walk-through of OpenGL
    Compile:  g++ test.cpp glad.c -ldl -lglfw 
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

int main(){
    //Initializing glfw
    glfwInit();
    
    // Essentially, we are setting the version major and minor to 3, thus OpenGL version 3.3 is required
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    //Telling GLFW we explicitly want to use the core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /*
        Creating a GLFWwindow object
        
        Parameters:
        width
        height
        title
        monitor - the monitor to use for full screen mode, or NULL to use windowed mode
        share: The window whose context to share resources with, or NULL to not share resources
    */ 
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    // We need to init glaf before doing an OpenGL function calling
    // Why? GLAD manages the func pointers for OpenGL 

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to init GLAD" << std::endl;
        return -1;
    }
    
    /*
        One last thing before rendering can take place 
        We have to tell OpenGL the size of the rendering window so it knows 
        how we want to disply the data and coordinates with respect to the window.
        
        We can set those cordinates via the viewport function

        The first two parameters of glViewport set the location of the lower left corner of the window

        The third and fourth parammeter set the width and height of the rendering window in pixels, which should equal the glfw window's width and height
        that I created on line 26  
    */
    glViewport(0,0,800,800);

    /* What if user resizes window? Well we need a callback for that. This handles it. */
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* Render Loop */
    while(!glfwWindowShouldClose(window)){
        /* Checks if close instruction has been made every iteration */

        /* This processes any keyboard inputs made by the user */
        process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Will swap the color buffer that is used to render to during this render iteration and show it as output to the screen */
        glfwSwapBuffers(window);
        
        /* 
            Info on the buffers

            Windowed mode has two buffers
                - Buffers are these canvas OpenGL can render to

            If we only had a single buffer, we might experience artifacting since the render is not instant, rather gradual usually left to right, top to bottom

            The use of two buffers is so that OpenGL displays one that is written to, gets the next frame and renders it on the back buffer, then swaps the buffers
            Then renders the next frame on the new back buffer (the one that was displaying before the swap) where as the buffer that was being rendered before the swap is
            now being displayed

        */

        /* Poll Events checks if any event has happened like a keyboard input, mouse movement, window state updates, etc */
        glfwPollEvents();
    }
    
    /* Window clean up */
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window){
    /* If the ESC key is pressed, updates close instruction to true */
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}