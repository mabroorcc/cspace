#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include <string.h>

#define WIDTH 1000
#define HEIGHT 1000

void createImage(const char *filename, const char *hexColor)
{
    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        printf("Error: Unable to open the file for writing.\n");
        return;
    }

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png)
    {
        printf("Error: Failed to create the PNG write structure.\n");
        fclose(file);
        return;
    }

    png_infop info = png_create_info_struct(png);
    if (!info)
    {
        printf("Error: Failed to create the PNG info structure.\n");
        fclose(file);
        png_destroy_write_struct(&png, NULL);
        return;
    }

    if (setjmp(png_jmpbuf(png)))
    {
        printf("Error: Failed during the PNG creation process.\n");
        fclose(file);
        png_destroy_write_struct(&png, &info);
        return;
    }

    png_init_io(png, file);
    png_set_IHDR(
        png, info, WIDTH, HEIGHT, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    // Convert hexadecimal color to RGB values
    unsigned int rgbColor;
    sscanf(hexColor, "%x", &rgbColor);
    unsigned int red = (rgbColor >> 16) & 0xFF;
    unsigned int green = (rgbColor >> 8) & 0xFF;
    unsigned int blue = rgbColor & 0xFF;

    png_bytep row = (png_bytep)malloc(3 * WIDTH * sizeof(png_byte));
    for (int i = 0; i < 3 * WIDTH; i += 3)
    {
        row[i] = red;
        row[i + 1] = green;
        row[i + 2] = blue;
    }

    png_write_info(png, info);

    for (int y = 0; y < HEIGHT; ++y)
    {
        png_write_row(png, row);
    }

    png_write_end(png, NULL);

    fclose(file);
    png_destroy_write_struct(&png, &info);
    free(row);

    printf("Image created successfully.\n");
}

int main()
{
    createImage("output.png", "000000");

    return 0;
}