#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <jpeglib.h>
#include <stdbool.h>
#include <getopt.h>
#include <ctype.h>

/**
 * @brief Contains color data for a single pixel.
 */
struct pixel_rgb_t {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

/**
 * @brief Defines an image size.
 */
struct image_size_t {
    unsigned int width;
    unsigned int height;
};
/**

 * @brief Defines an image scale.
 */
struct image_scale_t {
    float x;
    float y;
};

typedef struct pixel_rgb_t pixel_rgb_t;
typedef struct image_size_t image_size_t;
typedef struct image_scale_t image_scale_t;

/**
*
* Interpolates the value of a color.
*
* @param p00 color value at point00
* @param p01 color value at point01
* @param p10 color value at point10
* @param p11 color value at point11
* @param *scale scaling of the image
*
* @return bilinear interpolated color value
*/
int interpolate(int p00, int p01, int p10, int p11, image_scale_t *scale) {
  float dx = scale->x,
        dy = scale->y;

  if(dx > 1) {
    dx = 1 / dx;
  }
  if(dy > 1) {
    dy = 1 / dy;
  }
  int q0 = (1 - dx) * p00 + dx * p10,
      q1 = (1 - dx) * p01 + dx * p11;

  return (1 - dy) * q0 + dy * q1;
}

/**
 * @brief Scales an image by applying a billinear interpolation filter.
 *
 * @param in pixel data of input image
 * @param out  pixel data of output image. Has to be pre allocated.
 * @param src_sz the size of the input image
 * @param trgt_sz the desired output size.
 */
void resize_image(pixel_rgb_t *in, pixel_rgb_t *out, image_size_t src_sz, image_size_t trgt_sz) {

  image_scale_t scale;
  scale.x = (float) trgt_sz.width / src_sz.width;
  scale.y = (float) trgt_sz.height / src_sz.height;

  for(int i = 0; i < trgt_sz.height; i++) {
    // We need the current row in the target and the source image
    int current_row = i * trgt_sz.width,
        current_row_src = (int) (i / scale.y) * src_sz.width;

    for(int j = 0; j < trgt_sz.width; j++) {

      // find the corresponding current pixel in the source image
      pixel_rgb_t *p00 = &in[current_row_src + (int)(j / scale.x)],
                  *p01 = p00 + src_sz.width,
                  *p10 = p00 + 1,
                  *p11 = p01 + 1;

      // set the colors for the current pixel
      out[current_row + j].r = interpolate(p00->r, p01->r, p10->r, p11->r, &scale);
      out[current_row + j].g = interpolate(p00->g, p01->g, p10->g, p11->g, &scale);
      out[current_row + j].b = interpolate(p00->b, p01->b, p10->b, p11->b, &scale);
    }
  }

}

/**
 * @brief Loads pixels from a JPEG file into memory.
 * @param name the path of the file to read
 * @param img pointer to pixel data. Will be allocated.
 * @param size the size of the image. Will be set by this function
 */
void load_jpeg(const char *name, pixel_rgb_t **img, image_size_t *const size) {

    uint8_t r, g, b;
    int width, height;
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    FILE *infile;
    JSAMPARRAY pJpegBuffer;
    int row_stride;
    if ((infile = fopen(name, "rb")) == NULL) {
        fprintf(stderr, "can't open %s\n", name);
        exit(1);
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);
    (void) jpeg_read_header(&cinfo, TRUE);
    (void) jpeg_start_decompress(&cinfo);
    width = cinfo.output_width;
    height = cinfo.output_height;

    *img = calloc((size_t) width * height, sizeof(pixel_rgb_t));
    pixel_rgb_t *current_pixel = *img;
    if (!*img) {
        printf("NO MEM FOR JPEG CONVERT!\n");
        exit(1);
    }

    row_stride = width * cinfo.output_components;
    pJpegBuffer = (*cinfo.mem->alloc_sarray)
            ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);



    while (cinfo.output_scanline < cinfo.output_height) {
        (void) jpeg_read_scanlines(&cinfo, pJpegBuffer, 1);
        for (int x = 0; x < width; x++) {
            r = pJpegBuffer[0][cinfo.output_components * x];
            if (cinfo.output_components > 2) {
                g = pJpegBuffer[0][cinfo.output_components * x + 1];
                b = pJpegBuffer[0][cinfo.output_components * x + 2];
            } else {
                g = r;
                b = r;
            }

            //r, g and b contain the color information for the channels read, green and blue
            // current_pixel is your current pixel to fill with info from the jpeg.

            //set the color values for the current pixel
            current_pixel->r = r;
            current_pixel->g = g;
            current_pixel->b = b;

            current_pixel++;
        }
    }
    fclose(infile);
    (void) jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    size->height = (uint32_t) height;
    size->width = (uint32_t) width;
}

/**
 * @brief Writes pixel data to a JPEG file with 80% quality and defined image size.
 * @param pixel_data the pixel to compress
 * @param size the size of this image
 * @param filename paht to write this file to.
 */
 void save_jpeg(const pixel_rgb_t *pixel_data, const image_size_t size, const char *filename) {
     FILE *outfile = fopen(filename, "wb");

     if (!outfile) {
         fprintf(stderr, "can't open %s\n for write", filename);
         exit(1);
     }

     struct jpeg_compress_struct jpeg_info;
     struct jpeg_error_mgr jpeg_error;

     jpeg_info.err = jpeg_std_error(&jpeg_error);
     jpeg_create_compress(&jpeg_info);
     jpeg_stdio_dest(&jpeg_info, outfile);

     jpeg_info.image_width = size.width;
     jpeg_info.image_height = size.height;
     jpeg_info.input_components = 3;
     jpeg_info.in_color_space = JCS_RGB;

     jpeg_set_defaults(&jpeg_info);
     jpeg_set_quality(&jpeg_info, 80, true);
     jpeg_start_compress(&jpeg_info, true);

     JSAMPROW row_pointer;

     pixel_rgb_t p;

     unsigned char *row = malloc(sizeof(unsigned char) * 3 * size.width);

     while (jpeg_info.next_scanline < jpeg_info.image_height) {

         //current is your current scanline to fill with information.
         unsigned char *current = row;

         //this is the index of the beginning of the current row in your source array.
         unsigned int current_row = jpeg_info.next_scanline * size.width;

         /*
           Iterate over the width (every pixel) of the picture.
           For every pixel write to the current scanline. Since its 3 times 8 bit (char) we can write at i*3 + color offset.
           Our pixel data is found in the struct at the current_row index plus i as the pixel offset.
         */

         for(int i = 0; i < size.width; i++) {
           current[i*3] = pixel_data[current_row + i].r;
           current[i*3 +1] = pixel_data[current_row + i].g;
           current[i*3 +2] = pixel_data[current_row + i].b;
         }

         row_pointer = (JSAMPROW) row;
         jpeg_write_scanlines(&jpeg_info, &row_pointer, true);
     }

     free(row);

     jpeg_finish_compress(&jpeg_info);
 }

/**
*
* Returns 1 and prints error message.
*
* @param error Errorstring
*
* @return 1
*/
 int exit_with_error(char error[]) {
  printf("%s\n", error);
  return 1;
 };

 int main(int argc, char **argv) {
     int opt = 0;
     int name_flag = 0,
         name_out_flag = 0,
         width_flag = 0,
         height_flag = 0,
         keep_aspect = 0;

     char *name;
     char *name_out;
     image_size_t new_size = {0, 0};

     while ((opt = getopt(argc, argv,"i:o:w:h:")) != -1) {
       switch (opt) {
         case 'i':
           if(optarg != NULL) {
             name = optarg;
             name_flag = 1;
           }
           break;
         case 'o':
           if(optarg != NULL) {
             name_out = optarg;
             name_out_flag = 1;
           }
           break;
         case 'w':
           if(optarg != NULL) {
             int width = atoi(optarg); // cast to int number
             if(width != 0) { // only accept if parse succeeded
               new_size.width = width;
               width_flag = 1;
             } else {
               return exit_with_error("Your width is not a number.");
             }
           }
           break;
         case 'h':
           if(optarg != NULL) {
             int height = atoi(optarg); // cast to int number
             if(height != 0) { // only accept if parse succeeded
               new_size.height = height;
               height_flag = 1;
             } else {
               return exit_with_error("Your height is not a number.");
             }
           }
           break;
       }
     }

     // for easier make, only use the new size if we are in task02
     // exit if width or height are not set
     #ifdef CHECK_RESIZE
      if(width_flag == 0 || height_flag == 0) {
        return exit_with_error("Wrong input. Please use -i for input and -o for output. Also make sure to specify width and height by using -w and -h.");
      }
     #endif

     // for easier make, only use the new size if we are in task04
     #ifdef KEEP_ASPECT
      if(width_flag == 1 && height_flag == 0 || width_flag == 0 && height_flag == 1) {
        keep_aspect = 1;
      } else if(width_flag == 0 || height_flag == 0) {
        return exit_with_error("Wrong input. Please use -i for input and -o for output. You also have to at least specify one size using -w and -h.");
      }
     #endif

     // exit if input name or output name are not set
     if(name_flag == 0 || name_out_flag == 0) {
       return exit_with_error("Wrong input. Please use -i for input and -o for output.");
     } else {
       pixel_rgb_t *img;
       image_size_t image_size;

       image_size_t *using_size;
       pixel_rgb_t *using_img;

       load_jpeg(name, &img, &image_size);

       // if we want to keep our aspect ratio we have to use the proportion and apply it to the missing size.
       if(keep_aspect) {
         if(width_flag == 1) {
           new_size.height = ((float)new_size.width / image_size.width) * image_size.height;
         } else if(height_flag == 1) {
           new_size.width = ((float)new_size.height / image_size.height) * image_size.width;
         }
       }

       pixel_rgb_t *resize_img = calloc((size_t) new_size.width * new_size.height, sizeof(pixel_rgb_t));
       resize_image(img, resize_img, image_size, new_size);

       using_size = &image_size;
       using_img = img;

       // for easier make, only use the new size if we are in task03
       #ifdef DO_RESIZE
       using_size = &new_size;
       using_img = resize_img;
       #endif

       save_jpeg(using_img, *using_size, name_out);
     }

     return 0;
 }