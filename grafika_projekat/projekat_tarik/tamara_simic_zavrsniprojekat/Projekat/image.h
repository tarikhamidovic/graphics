#ifndef IMAGE_H
#define IMAGE_H
#include <fstream>
#include <assert.h>


struct Image {

	char* pixel;
	int width;
	int height;

	Image(char* data, int w, int h)
	{
	    pixel = data;
	    width  = w;
	    height = h;
	}

	~Image()
	{
	    delete [] pixel;
	}

};

GLuint Texture;
Image* planet;
GLUquadricObj *ball;

template<class T>
struct auto_array
{
    T* array;
    bool isReleased;

    auto_array(T* array_ = NULL) :
        array(array_), isReleased(false) {}

    ~auto_array()
    {
        if (!isReleased && array != NULL)
        {
        delete[] array;
        }
    }

    T* release()
    {
        isReleased = true;
        return array;
    }
};

int readInt(std::ifstream &ulaz)
{
    char buffer[4];
    ulaz.read(buffer, 4);
    return (int)(((unsigned char)buffer[3] << 24) |
        ((unsigned char)buffer[2] << 16) |
        ((unsigned char)buffer[1] << 8) |
        (unsigned char)buffer[0]);
}

Image* loadBMP(const char* file)
{
	std::ifstream ulaz;
	ulaz.open(file, std::ifstream::binary);
    char buffer[2];
	ulaz.read(buffer, 2);
	ulaz.ignore(8);

	int dataOffset = readInt(ulaz);
	int headerSize = readInt(ulaz);
	int width= readInt(ulaz);
    int height = readInt(ulaz);
    ulaz.ignore(2);

	int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
	int size = bytesPerRow * height;

	auto_array<char> pixels(new char[size]);
	ulaz.seekg(dataOffset, std::ios_base::beg);
	ulaz.read(pixels.array, size);

	auto_array<char> pixels2(new char[width * height * 3]);
	for (int y = 0; y < height; ++y)
    {
		for (int x = 0; x < width; ++x)
		{
			for (int c = 0; c < 3; ++c)
			{
				pixels2.array[3 * (width * y + x) + c] =
                pixels.array[bytesPerRow * y + 3 * x + (2 - c)];
			}
		}
	}

	ulaz.close();
	return new Image(pixels2.release(), width, height);
}

#endif
