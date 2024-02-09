#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "GL/glew.h"
#include "../extra/picopng.h"
#include "image.h"
#include "utils.h"
#include "camera.h"
#include "mesh.h"



Image::Image() {
	width = 0; height = 0;
	pixels = NULL;
}



Image::Image(unsigned int width, unsigned int height)

{
	this->width = width;
	this->height = height;
	pixels = new Color[width * height];
	memset(pixels, 0, width * height * sizeof(Color));
}


// Copy constructor
Image::Image(const Image& c)
{
	pixels = NULL;
	width = c.width;
	height = c.height;
	bytes_per_pixel = c.bytes_per_pixel;

	if (c.pixels)
	{

		pixels = new Color[width * height];
		memcpy(pixels, c.pixels, width * height * bytes_per_pixel);

	}
}



// Assign operator

Image& Image::operator = (const Image& c)

{

	if (pixels) delete pixels;

	pixels = NULL;



	width = c.width;

	height = c.height;

	bytes_per_pixel = c.bytes_per_pixel;



	if (c.pixels)

	{

		pixels = new Color[width * height * bytes_per_pixel];

		memcpy(pixels, c.pixels, width * height * bytes_per_pixel);

	}

	return *this;

}



Image::~Image()

{

	if (pixels)

		delete pixels;

}



void Image::Render()

{

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glDrawPixels(width, height, bytes_per_pixel == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, pixels);

}



// Change image size (the old one will remain in the top-left corner)

void Image::Resize(unsigned int width, unsigned int height)

{

	Color* new_pixels = new Color[width * height];

	unsigned int min_width = this->width > width ? width : this->width;

	unsigned int min_height = this->height > height ? height : this->height;



	for (unsigned int x = 0; x < min_width; ++x)

		for (unsigned int y = 0; y < min_height; ++y)

			new_pixels[y * width + x] = GetPixel(x, y);



	delete pixels;

	this->width = width;

	this->height = height;

	pixels = new_pixels;

}



// Change image size and scale the content

void Image::Scale(unsigned int width, unsigned int height)

{

	Color* new_pixels = new Color[width * height];



	for (unsigned int x = 0; x < width; ++x)

		for (unsigned int y = 0; y < height; ++y)

			new_pixels[y * width + x] = GetPixel((unsigned int)(this->width * (x / (float)width)), (unsigned int)(this->height * (y / (float)height)));



	delete pixels;

	this->width = width;

	this->height = height;

	pixels = new_pixels;

}



Image Image::GetArea(unsigned int start_x, unsigned int start_y, unsigned int width, unsigned int height)

{

	Image result(width, height);

	for (unsigned int x = 0; x < width; ++x)

		for (unsigned int y = 0; y < height; ++x)

		{

			if ((x + start_x) < this->width && (y + start_y) < this->height)

				result.SetPixel(x, y, GetPixel(x + start_x, y + start_y));

		}

	return result;

}



void Image::FlipY()

{

	int row_size = bytes_per_pixel * width;

	Uint8* temp_row = new Uint8[row_size];

#pragma omp simd

	for (int y = 0; y < height * 0.5; y += 1)

	{

		Uint8* pos = (Uint8*)pixels + y * row_size;

		memcpy(temp_row, pos, row_size);

		Uint8* pos2 = (Uint8*)pixels + (height - y - 1) * row_size;

		memcpy(pos, pos2, row_size);

		memcpy(pos2, temp_row, row_size);

	}

	delete[] temp_row;

}



bool Image::LoadPNG(const char* filename, bool flip_y)

{

	std::string sfullPath = absResPath(filename);

	std::ifstream file(sfullPath, std::ios::in | std::ios::binary | std::ios::ate);



	// Get filesize

	std::streamsize size = 0;

	if (file.seekg(0, std::ios::end).good()) size = file.tellg();

	if (file.seekg(0, std::ios::beg).good()) size -= file.tellg();



	if (!size)

		return false;



	std::vector<unsigned char> buffer;



	// Read contents of the file into the vector

	if (size > 0)

	{

		buffer.resize((size_t)size);

		file.read((char*)(&buffer[0]), size);

	}

	else

		buffer.clear();



	std::vector<unsigned char> out_image;



	if (decodePNG(out_image, width, height, buffer.empty() ? 0 : &buffer[0], (unsigned long)buffer.size(), true) != 0)

		return false;



	size_t bufferSize = out_image.size();

	unsigned int originalBytesPerPixel = (unsigned int)bufferSize / (width * height);



	// Force 3 channels

	bytes_per_pixel = 3;



	if (originalBytesPerPixel == 3) {

		pixels = new Color[bufferSize];

		memcpy(pixels, &out_image[0], bufferSize);

	}

	else if (originalBytesPerPixel == 4) {



		unsigned int newBufferSize = width * height * bytes_per_pixel;

		pixels = new Color[newBufferSize];



		unsigned int k = 0;

		for (unsigned int i = 0; i < bufferSize; i += originalBytesPerPixel) {

			pixels[k] = Color(out_image[i], out_image[i + 1], out_image[i + 2]);

			k++;

		}

	}



	// Flip pixels in Y

	if (flip_y)

		FlipY();



	return true;

}



// Loads an image from a TGA file

bool Image::LoadTGA(const char* filename, bool flip_y)

{

	unsigned char TGAheader[12] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	unsigned char TGAcompare[12];

	unsigned char header[6];

	unsigned int imageSize;

	unsigned int bytesPerPixel;



	std::string sfullPath = absResPath(filename);



	FILE* file = fopen(sfullPath.c_str(), "rb");

	if (file == NULL || fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare) ||

		memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) != 0 ||

		fread(header, 1, sizeof(header), file) != sizeof(header))

	{

		std::cerr << "File not found: " << sfullPath.c_str() << std::endl;

		if (file == NULL)

			return NULL;

		else

		{

			fclose(file);

			return NULL;

		}

	}



	TGAInfo* tgainfo = new TGAInfo;



	tgainfo->width = header[1] * 256 + header[0];

	tgainfo->height = header[3] * 256 + header[2];



	if (tgainfo->width <= 0 || tgainfo->height <= 0 || (header[4] != 24 && header[4] != 32))

	{

		fclose(file);

		delete tgainfo;

		return NULL;

	}



	tgainfo->bpp = header[4];

	bytesPerPixel = tgainfo->bpp / 8;

	imageSize = tgainfo->width * tgainfo->height * bytesPerPixel;



	tgainfo->data = new unsigned char[imageSize];



	if (tgainfo->data == NULL || fread(tgainfo->data, 1, imageSize, file) != imageSize)

	{

		if (tgainfo->data != NULL)

			delete tgainfo->data;

		fclose(file);

		delete tgainfo;

		return false;

	}



	fclose(file);



	// Save info in image

	if (pixels)

		delete pixels;



	width = tgainfo->width;

	height = tgainfo->height;

	pixels = new Color[width * height];



	// Convert to float all pixels

	for (unsigned int y = 0; y < height; ++y) {

		for (unsigned int x = 0; x < width; ++x) {

			unsigned int pos = y * width * bytesPerPixel + x * bytesPerPixel;

			// Make sure we don't access out of memory

			if ((pos < imageSize) && (pos + 1 < imageSize) && (pos + 2 < imageSize))

				SetPixel(x, height - y - 1, Color(tgainfo->data[pos + 2], tgainfo->data[pos + 1], tgainfo->data[pos]));

		}

	}



	// Flip pixels in Y

	if (flip_y)

		FlipY();



	delete tgainfo->data;

	delete tgainfo;



	return true;

}



// Saves the image to a TGA file

bool Image::SaveTGA(const char* filename)

{

	unsigned char TGAheader[12] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };



	std::string fullPath = absResPath(filename);

	FILE* file = fopen(fullPath.c_str(), "wb");

	if (file == NULL)

	{

		perror("Failed to open file: ");

		return false;

	}



	unsigned short header_short[3];

	header_short[0] = width;

	header_short[1] = height;

	unsigned char* header = (unsigned char*)header_short;

	header[4] = 24;

	header[5] = 0;



	fwrite(TGAheader, 1, sizeof(TGAheader), file);

	fwrite(header, 1, 6, file);



	// Convert pixels to unsigned char

	unsigned char* bytes = new unsigned char[width * height * 3];

	for (unsigned int y = 0; y < height; ++y)

		for (unsigned int x = 0; x < width; ++x)

		{

			Color c = pixels[y * width + x];

			unsigned int pos = (y * width + x) * 3;

			bytes[pos + 2] = c.r;

			bytes[pos + 1] = c.g;

			bytes[pos] = c.b;

		}



	fwrite(bytes, 1, width * height * 3, file);

	fclose(file);



	return true;

}


void Image::DrawRect(int x, int y, int w, int h, const Color& borderColor, int borderWidth, bool isFilled, const Color& fillColor)
{
	for (int border = 0; border < borderWidth; ++border) {
		// top border
		for (int i = 0; i < w + 2 * borderWidth; i++) {
			SetPixelSafe(x - borderWidth + i, y - borderWidth + border, borderColor);
		}

		// bottom border
		for (int i = 0; i < w + 2 * borderWidth; i++) {
			SetPixelSafe(x - borderWidth + i, y + h - 1 + border, borderColor);
		}

		// left border
		for (int j = 0; j < h + 2 * borderWidth; j++) {
			SetPixelSafe(x - borderWidth + border, y - borderWidth + j, borderColor);
		}

		// right border
		for (int j = 0; j < h + 2 * borderWidth; j++) {
			SetPixelSafe(x + w + border, y - borderWidth + j, borderColor);
		}
	}

	if (isFilled) {
		for (int dx = x; dx < x + w; ++dx) {
			for (int dy = y; dy < y + h; ++dy) {
				SetPixelSafe(dx, dy, fillColor);
			}
		}
	}
}


void Image::DrawLineDDA(int x0, int y0, int x1, int y1, const Color& c) {
	int dx = x1 - x0;
	int dy = y1 - y0;
	int steps = 0;

	if (abs(dx) > abs(dy)) {
		steps = abs(dx);
	}
	else {
		steps = abs(dy);
	}

	float xIncrement = dx / (float)steps;
	float yIncrement = dy / (float)steps;

	float x = (float)x0;
	float y = (float)y0;

	for (int i = 0; i <= steps; i++) {
		SetPixelSafe((int)x, (int)y, c);
		x += xIncrement;
		y += yIncrement;
	}
}



void Image::DrawCircle(int x, int y, int r, const Color& borderColor, int borderWidth, bool isFilled, const Color& fillColor) {
	const int numPixels = r * 16; // We have set the number of pixels by hand
	const double angleIncrement = 2 * M_PI / numPixels;

	for (int i = 0; i < numPixels; i++) {
		double angle = i * angleIncrement;
		for (int border = 0; border < borderWidth; border++) {
			int currentRadius = r + border;
			int x1 = (int)(x + currentRadius * cos(angle));
			int y1 = (int)(y + currentRadius * sin(angle));
			SetPixelSafe(x1, y1, borderColor);
		}
	}

	if (isFilled) {
		for (int rInner = 0; rInner < r; rInner++) {
			for (int i = 0; i < numPixels; i++) {
				double angle = i * angleIncrement;
				int x1 = (int)(x + rInner * cos(angle));
				int y1 = (int)(y + rInner * sin(angle));
				SetPixelSafe(x1, y1, fillColor);
			}
		}
	}
}


void Image::DrawTriangle(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Color& borderColor, bool isFilled, const Color& fillColor) {
	std::vector<Cell> AET;

	AET.resize(height);
	ScanLineDDA(p0.x, p0.y, p1.x, p1.y, AET);
	ScanLineDDA(p1.x, p1.y, p2.x, p2.y, AET);
	ScanLineDDA(p2.x, p2.y, p0.x, p0.y, AET);



	for (int i = 0; i < AET.size(); i++) {
		if (AET[i].minX < AET[i].maxX) {
			for (int j = AET[i].minX; j < AET[i].maxX; j++) {
				SetPixelSafe(j, i, fillColor);
			}
		}
	}

}

void Image::ScanLineDDA(int x0, int y0, int x1, int y1, std::vector<Cell>& table) {

	int dx = x1 - x0;
	int dy = y1 - y0;

	int d = std::max(abs(dx), abs(dy));

	Vector2 v(dx / (float)d, dy / (float)d);
	Vector2 A = Vector2(x0, y0);

	for (int i = 0; i < d; i++) {
		if (table[A.y].minX > A.x) {
			table[A.y].minX = A.x;
		}

		if (table[A.y].maxX < A.x) {
			table[A.y].maxX = A.x;
		}

		A = A + v;
	}

}


void Image::DrawImage(const Image& image, int x, int y, bool top) {

	int drawY;

	if (top) {
		drawY = y;
	}
	else {
		drawY = y - image.height;

	}

	for (int dx = 0; dx < image.width; dx++) {
		for (int dy = 0; dy < image.height; dy++) {
			if (x + dx >= 0 && x + dx < width && drawY + dy >= 0 && drawY + y < height) { //
				Color pixelColor = image.GetPixel(dx, dy);
				SetPixelSafe(x + dx, drawY + dy, pixelColor);
			}
		}
	}

}

void Image::DrawTriangleInterpolated(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Color& c0, const Color& c1, const Color& c2, FloatImage* zbuffer) {

	//method to draw mesh but interpolating 3 colors
	//this method draws filled triangle but using barycentric interpolation between the colors of each vertex
	//we have to pass a color per vertex --> we need to reuse the AET min-max iterations per cell and include weights for barycentric interpolation, once we have weights we can compute the final pixel color
	//weight have to be between 0-1 and add up to 1, no weights can be negative!!!

	//we need to use the inverse of M to find the barycentric coordinates

	Matrix44 m;
	m.M[0][0] = p0.x;
	m.M[1][0] = p1.x;
	m.M[2][0] = p2.x;

	m.M[0][1] = p0.y;
	m.M[1][1] = p1.y;
	m.M[2][1] = p2.y;

	m.M[0][2] = 1;
	m.M[1][2] = 1;
	m.M[2][2] = 1;

	m.Inverse();

	std::vector<Cell> table;
	table.resize(height);

	ScanLineDDA((int)p0.x, (int)p0.y, (int)p1.x, (int)p1.y, table);
	ScanLineDDA((int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, table);
	ScanLineDDA((int)p2.x, (int)p2.y, (int)p0.x, (int)p0.y, table);

	for (int y = 0; y < table.size(); y++) {
		if (table[y].minX < table[y].maxX) {
			for (int x = table[y].minX; x < table[y].maxX; ++x) {

				Vector3 pixelBarycentricCoords = m * Vector3(x, y, 1);
				pixelBarycentricCoords.Clamp(0, 1);
				float sumPixel = pixelBarycentricCoords.x + pixelBarycentricCoords.y + pixelBarycentricCoords.z;
				pixelBarycentricCoords = pixelBarycentricCoords / sumPixel;

				// we need to make sure that the pixel is inside the triangle
				if (pixelBarycentricCoords.x >= 0 && pixelBarycentricCoords.y >= 0 && pixelBarycentricCoords.z >= 0) {
					float interpolatedZ = p0.z * pixelBarycentricCoords.x + p1.z * pixelBarycentricCoords.y + p2.z * pixelBarycentricCoords.z;

					if (interpolatedZ < zbuffer->GetPixel(x, y)) {
						// Update Z-buffer
						zbuffer->SetPixel(x, y, interpolatedZ);

						Color interpolatedColor = c0 * pixelBarycentricCoords.x + c1 * pixelBarycentricCoords.y + c2 * pixelBarycentricCoords.z;

						SetPixelSafe(x, y, interpolatedColor);
					}
				}
			}
		}
	}

}




#ifndef IGNORE_LAMBDAS



// You can apply and algorithm for two images and store the result in the first one

// ForEachPixel( img, img2, [](Color a, Color b) { return a + b; } );

template <typename F>

void ForEachPixel(Image& img, const Image& img2, F f) {

	for (unsigned int pos = 0; pos < img.width * img.height; ++pos)

		img.pixels[pos] = f(img.pixels[pos], img2.pixels[pos]);

}



#endif



FloatImage::FloatImage(unsigned int width, unsigned int height){

	this->width = width;
	this->height = height;
	pixels = new float[width * height];
	memset(pixels, 999999, width * height * sizeof(float)); //we set the buffer to a big value

}



// Copy constructor

FloatImage::FloatImage(const FloatImage& c) {

	pixels = NULL;

	width = c.width;

	height = c.height;

	if (c.pixels)
	{

		pixels = new float[width * height];
		memcpy(pixels, c.pixels, width * height * sizeof(float));

	}

}



// Assign operator

FloatImage& FloatImage::operator = (const FloatImage& c)

{

	if (pixels) delete pixels;

	pixels = NULL;

	width = c.width;

	height = c.height;

	if (c.pixels)

	{

		pixels = new float[width * height * sizeof(float)];

		memcpy(pixels, c.pixels, width * height * sizeof(float));

	}

	return *this;

}



FloatImage::~FloatImage()

{

	if (pixels)

		delete pixels;

}



// Change image size (the old one will remain in the top-left corner)

void FloatImage::Resize(unsigned int width, unsigned int height)

{

	float* new_pixels = new float[width * height];

	unsigned int min_width = this->width > width ? width : this->width;

	unsigned int min_height = this->height > height ? height : this->height;



	for (unsigned int x = 0; x < min_width; ++x)

		for (unsigned int y = 0; y < min_height; ++y)

			new_pixels[y * width + x] = GetPixel(x, y);



	delete pixels;

	this->width = width;

	this->height = height;

	pixels = new_pixels;

}