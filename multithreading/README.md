# Multithreading

### Resources
Read or watch:

[pthread.h](https://intranet.atlasschool.com/rltoken/_5i2XAWKXav-P1YKmH7l8w)
[Concurrency vs. Parallelism](https://intranet.atlasschool.com/rltoken/leOH34tPS_dBe8Ss8lq_9g)

### Learning Objectives

At the end of this project, you are expected to be able to explain to anyone, without the help of Google:

* What is a thread
* What are the differences between a thread and a process
* What is the difference between Concurrency and Parallelism
* How to create a thread
* How to properly exit a thread
* How to handle mutual execution
* What is a deadlock
* What is a race condition

### Requirements

[B] Allowed editors: vi, vim, emacs
* All your files will be compiled on Ubuntu 20.04 LTS
* Your C programs and functions will be compiled with gcc 9.4.0 using the flags -Wall -Werror -Wextra and -pedantic
* All your files should end with a new line
* A README.md file, at the root of the folder of the project, is mandatory
* Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
* You are not allowed to have more than 5 functions per file
* The prototypes of all your functions should be included in your header file called multithreading.h
* Don’t forget to push your header files
* All your header files should be include guarded
* You are allowed to use global variables
* You are allowed to use static functions and variables

## Betty Compliance
- All the C source files in your directory and subdirectories must be Betty-compliant
- Allowed Functions and System Calls
- Unless specified otherwise, you are allowed to use the C standard library
- Data structures
- Here are the data structures used throughout this project, make sure to include them in your header file multithreading.h.

        #include <stddef.h>
        #include <stdint.h>

        /**
        * struct pixel_s - RGB pixel
        *
        * @r: Red component
        * @g: Green component
        * @b: Blue component
        */
        typedef struct pixel_s
        {
            uint8_t r;
            uint8_t g;
            uint8_t b;
        } pixel_t;

        /**
        * struct img_s - Image
        *
        * @w:      Image width
        * @h:      Image height
        * @pixels: Array of pixels
        */
        typedef struct img_s
        {
            size_t w;
            size_t h;
            pixel_t *pixels;
        } img_t;

        /**
        * struct kernel_s - Convolution kernel
        *
        * @size:   Size of the matrix (both width and height)
        * @matrix: Kernel matrix
        */
        typedef struct kernel_s
        {
            size_t size;
            float **matrix;
        } kernel_t;

        /**
        * struct blur_portion_s - Information needed to blur a portion of an image
        *
        * @img:      Source image
        * @img_blur: Destination image
        * @x:        X position of the portion in the image
        * @y:        Y position of the portion in the image
        * @w:        Width of the portion
        * @h:        Height of the portion
        * @kernel:   Convolution kernel to use
        */
        typedef struct blur_portion_s
        {
            img_t const *img;
            img_t *img_blur;
            size_t x;
            size_t y;
            size_t w;
            size_t h;
            kernel_t const *kernel;
        } blur_portion_t;